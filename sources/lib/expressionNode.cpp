#include "expressionNode.h"
#include "parser.h"


ExpressionNode::ExpressionNode(QList<Token> expression, QList<VarNode*>* registry)
{
    this->expression = expression;
    this->value = NULL;
    this->registry = registry;

    convertToRPN();
}


ExpressionNode::~ExpressionNode() {}


Calculable* ExpressionNode::execute()
{
    QList<Calculable*> stack;
    QList<Token> expression = this->expression;

    foreach (Token token, expression)
    {
        TokenKind kind = token.getKind();

        if (kind == T_STRING)
        {
            if (Parser::isFunction(token))
            {
                if (token.getValue() == "TEST")
                {
                    Calculable* arg1 = stack[stack.length()-1];
                    stack.removeLast();
                    stack.append(arg1);
                }
            }
            else
            {
                VarNode* var = VarNode::getVar(token.getValue(), this->registry);

                if (var->getValue() == NULL)
                {
                    return NULL;
                }

                stack.append(var->getValue());
            }
        }
        else if (kind == T_DOUBLE)
        {
            stack.append(new Calculable(token.getValue().toDouble()));
        }
        else if (Operator::isOperator(token))
        {
            Calculable a = *(stack[stack.length()-1]);
            stack.removeLast();

            Calculable b = *(stack[stack.length()-1]);
            stack.removeLast();

            switch (token.getKind())
            {
                case T_SUM:
                    stack.append(a+b);
                    break;

                case T_SUB:
                    stack.append(a-b);
                    break;

                case T_MULTIPLY:
                    stack.append(a*b);
                    break;

                case T_DIVIDE:
                    stack.append(a/b);
                    break;
            }
        }
    }

    return stack[0];
}


QString ExpressionNode::toString() const
{
    if (this->value == NULL)
    {
        return "";
    }

    return "Expression node value: " + this->value->toString();
}


void ExpressionNode::convertToRPN()
{
    //We search for negatives numbers i.e "T_SUB" not used as operator
    for (int i = 0; i < this->expression.length(); i++)
    {
        if (this->expression[i].getKind() == T_SUB)
        {
            // qDebug() << "la";
            //Beginning of expression || parenthesis to the left
            if (i == 0)
            {
                qDebug() << "darace";
            }
            if (i == 0 || this->expression[i-1].getKind() == T_PARENTHESIS_LEFT)
            {
                qDebug() << "alabate";
                TokenKind rightTokenKind = this->expression[i+1].getKind();

                //Scalar or string to the right
                if (rightTokenKind == T_DOUBLE || rightTokenKind == T_STRING) // || T_MATRIX ? => TODO T_CALCULABLE needs to be implemented
                {
                    qDebug() << "icaaaaai";
                    QList<Token> newExpression;

                    //Add "-1 *"
                    newExpression.append(this->expression.mid(0, i));
                    newExpression.append(Token(T_DOUBLE, "-1"));
                    newExpression.append(Token(T_MULTIPLY, "*"));
                    newExpression.append(this->expression.mid(i+1, this->expression.length()));
                    this->expression = newExpression;
                    qDebug() << "hihi";
                }
            }
        }
    }


    QMap<int, Operator*> operators = Operator::operators;
    QList<Token> newExpression;
    QList<Token> stack;

    foreach (Token token, this->expression)
    {
        qDebug() << token.getValue();

        TokenKind kind = token.getKind();

        if (kind == T_DOUBLE) // || kind == T_MATRIX
        {
            newExpression.append(token);
        }
        else if (kind == T_STRING)
        {
            if (Parser::isFunction(token))
            {
                stack.append(token);
            }
            else
            {
                newExpression.append(token);
            }
        }
        else if (kind == T_COMMA)
        {
            while (stack.length () != 0 && stack[stack.length()-1].getKind() != T_PARENTHESIS_LEFT)
            {
                newExpression.append(stack[stack.length()-1]);
                stack.removeLast();
            }

            if (stack.length() == 0)
            {
                qDebug() << "PARENTHESIS OR COMMA ERROR";
                return;
            }
        }
        else if (Operator::isOperator(token))
        {
            Operator* currentOperator = operators[token.getKind()];

            while (stack.length() != 0 && Operator::isOperator(stack[stack.length()-1]))
            {
                Operator* stackOperator = operators[stack[stack.length()-1].getKind()];

                if ((currentOperator->getAssociativity() == LEFT_ASSOC &&
                   currentOperator->getPrecedence() - stackOperator->getPrecedence() <= 0) ||
                   (currentOperator->getAssociativity() == RIGHT_ASSOC  &&
                   currentOperator->getPrecedence() - stackOperator->getPrecedence() < 0))
                {
                    newExpression.append(stack[stack.length()-1]);
                    stack.removeLast();
                    continue;
                }

                break;
            }

            stack.append(token);
        }
        else if (token.getKind() == T_PARENTHESIS_LEFT)
        {
            stack.append(token);
        }
        else if (token.getKind() == T_PARENTHESIS_RIGHT)
        {
            while (stack.length() != 0 && stack[stack.length()-1].getKind() != T_PARENTHESIS_LEFT)
            {
                newExpression.append(stack[stack.length()-1]);
                stack.removeLast();
            }

            if (stack.length() == 0)
            {
                qDebug() << "PARENTHESIS ERROR";
                return;
            }

            stack.removeLast();

            if (stack.length() != 0 && stack[stack.length()-1].getKind() == T_STRING && Parser::isFunction(stack[stack.length()-1]))
            {
                newExpression.append(stack[stack.length()-1]);
                stack.removeLast();
            }
        }
        else
        {
            newExpression.append(token);
        }
    }

    while (stack.length() != 0)
    {
        newExpression.append(stack[stack.length()-1]);
        stack.removeLast();
    }

    this->expression = newExpression;
}
