#include "expressionNode.h"
#include "parser.h"


ExpressionNode::ExpressionNode(QList<Token> expression)
{
    this->expression = expression;
    this->value = NULL;

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
                VarNode* var = VarNode::getVar(token.getValue());

                if (var->getValue() == NULL)
                {
                    throw std::runtime_error("Var " + token.getValue().toStdString() + " is not defined.");
                    return NULL;
                }

                stack.append(var->getValue());
            }
        }
        else if (kind == T_SCALAR)
        {
            stack.append(new Scalar(token.getValue()));
        }
        else if (kind == T_MATRIX)
        {
            stack.append(new Matrix(token.getValue()));
        }
        else if (Operator::isOperator(token))
        {
            if (stack.length() < 2)
            {
                throw std::runtime_error("Not enough argument for operator " + token.getValue().toStdString());
                return NULL;
            }

            Calculable &a = *(stack[stack.length()-1]);
            stack.removeLast();

            Calculable &b = *(stack[stack.length()-1]);
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
                default:
                    throw std::runtime_error("An operator doesn't have its operation");
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
            //Beginning of expression || parenthesis to the left
            if (i == 0 || this->expression[i-1].getKind() == T_PARENTHESIS_LEFT)
            {
                TokenKind rightTokenKind = this->expression[i+1].getKind();

                //Scalar or string to the right
                if (rightTokenKind == T_SCALAR || rightTokenKind == T_STRING) // || T_MATRIX ? => TODO T_CALCULABLE needs to be implemented
                {
                    QList<Token> newExpression;

                    //Add "-1 *"
                    newExpression.append(this->expression.mid(0, i));
                    newExpression.append(Token(T_SCALAR, "-1"));
                    newExpression.append(Token(T_MULTIPLY, "*"));
                    newExpression.append(this->expression.mid(i+1, this->expression.length()));
                    this->expression = newExpression;
                }
            }
        }
    }


    QMap<int, Operator*> operators = Operator::operators;
    QList<Token> newExpression;
    QList<Token> stack;

    foreach (Token token, this->expression)
    {
        TokenKind kind = token.getKind();

        if (kind == T_SCALAR || kind == T_MATRIX)
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
                throw std::runtime_error("Parenthesis or comma error");
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
                throw std::runtime_error("Parenthesis error");
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
