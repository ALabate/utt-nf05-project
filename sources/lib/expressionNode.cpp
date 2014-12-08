#include "expressionNode.h"


/**
 * @brief Constructor
 * 
 * @param value a pointer to the Calculable
 */

ExpressionNode::ExpressionNode(QList<Token> expression)
{
    this->expression = expression;
    this->value = NULL;

    convertToRPN();
}


ExpressionNode::~ExpressionNode() {}


/**
 * @brief Execute the node
 * 
 * @return a Calculable pointer
 */

Calculable* ExpressionNode::execute()
{
    QString string;

    foreach (Token token, this->expression)
    {
        string += token.getValue();
    }

    qDebug() << string;
    return this->value;
}


void ExpressionNode::convertToRPN()
{
    QMap<int, Operator*> operators = Operator::operators;
    QList<Token> newExpression;
    QList<Token> stack;

    foreach (Token token, this->expression)
    {
        TokenKind kind = token.getKind();

        if (kind == T_DOUBLE)
        {
            newExpression.append(token);
        }
        else if (kind == T_STRING)
        {
            if (isFunction(token))
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
                qDebug() << "PARENTHESIS ERROR 2";
                return;
            }

            stack.removeLast();

            if (stack.length() != 0 && stack[stack.length()-1].getKind() == T_STRING && isFunction(stack[stack.length()-1]))
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


bool ExpressionNode::isFunction(Token token)
{
    QString value = token.getValue();

    return (value == "NORME" || value == "DET" || value == "SOLVE");
}

/**
 * @brief toString method
 * 
 * @return a QString representation of the Node
 */

QString ExpressionNode::toString() const
{
    if (this->value == NULL)
    {
        return "";
    }

    return "Expression node value: " + this->value->toString();
}
