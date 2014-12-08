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
    QString string;

    foreach (Token token, this->expression)
    {
        string = "";
        foreach (Token token, newExpression)
        {
            string += token.getValue();
        }

       // qDebug() << string;
        string = "";

        foreach (Token token, stack)
        {
            string += token.getValue();
        }

       // qDebug() << string;

        if (Operator::isOperator(token))
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
            stack.removeLast();
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
