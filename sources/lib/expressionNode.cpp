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
                //det(Matrix) : Determinant
                if(token.getValue().toLower() == "det")
                {
                    if(stack.length() >= 1 && stack[stack.length()-1]->getType() == T_MATRIX)
                    {
                        //Get params
                        Matrix* mat = dynamic_cast<Matrix*>(stack[stack.length()-1]);
                        stack.removeLast();
                        //Calculate
                        stack.append(MatrixLib::determinant(mat));
                    }
                    else
                    {
                        throw std::runtime_error("Help : det(<b>Matrix</b> mat)");
                    }
                }
                //cof(Matrix mat, Scalar i, Scalar j) : Cofactor
                else if(token.getValue().toLower() == "cof")
                {
                    if(stack.length() >= 3
                            && stack[stack.length()-1]->getType() == T_SCALAR
                            && stack[stack.length()-2]->getType() == T_SCALAR
                            && stack[stack.length()-3]->getType() == T_MATRIX)
                    {
                        //Get params
                        Scalar* j = dynamic_cast<Scalar*>(stack[stack.length()-1]);
                        stack.removeLast();
                        Scalar* i = dynamic_cast<Scalar*>(stack[stack.length()-1]);
                        stack.removeLast();
                        Matrix* mat = dynamic_cast<Matrix*>(stack[stack.length()-1]);
                        stack.removeLast();

                        //Checks
                        if(i->getRawValue() < 1 || i->getRawValue() > mat->getM())
                            throw std::runtime_error("Help : cof(matrix mat, scalar i, scalar j)<br/> And 1 &le; i &le; " + QString::number(mat->getM()).toStdString());
                        else if(j->getRawValue() < 1 || j->getRawValue() > mat->getN())
                            throw std::runtime_error("Help : cof(matrix mat, scalar i, scalar j)<br/> And 1 &le; j &le; " + QString::number(mat->getN()).toStdString());

                        //Calculate
                        stack.append(MatrixLib::cofactor(mat, i->getRawValue()-1, j->getRawValue()-1));
                    }
                    else
                    {
                        throw std::runtime_error("Help : cof(<b>Matrix</b> mat, <b>Scalar</b> i, <b>Scalar</b> j)");
                    }
                }
                //trans(Matrix) : Transpose
                else if(token.getValue().toLower() == "trans")
                {
                    if(stack.length() >= 1 && stack[stack.length()-1]->getType() == T_MATRIX)
                    {
                        //Get params
                        Matrix* mat = dynamic_cast<Matrix*>(stack[stack.length()-1]);
                        stack.removeLast();
                        //Calculate
                        stack.append(MatrixLib::transpose(mat));
                    }
                    else
                    {
                        throw std::runtime_error("Help : det(<b>Matrix</b> mat)");
                    }
                }
                //co(Matrix) : Cofactor matrix
                else if(token.getValue().toLower() == "co")
                {
                    if(stack.length() >= 1 && stack[stack.length()-1]->getType() == T_MATRIX)
                    {
                        //Get params
                        Matrix* mat = dynamic_cast<Matrix*>(stack[stack.length()-1]);
                        stack.removeLast();
                        //Calculate
                        stack.append(MatrixLib::coMatrix(mat));
                    }
                    else
                    {
                        throw std::runtime_error("Help : co(<b>Matrix</b> mat)");
                    }
                }
                //I(Scalar n) : Generate the identity matrix of size n
                else if(token.getValue().toLower() == "i")
                {
                    if(stack.length() >= 1 && stack[stack.length()-1]->getType() == T_SCALAR)
                    {
                        //Get params
                        Scalar* n = dynamic_cast<Scalar*>(stack[stack.length()-1]);
                        stack.removeLast();
                        //Calculate
                        stack.append(MatrixLib::identity(n->getRawValue()));
                    }
                    else
                    {
                        throw std::runtime_error("Help : I(<b>Scalar</b> n)");
                    }
                }
                //inv(Matrix mat) : Generate the inverted matrix of mat
                else if(token.getValue().toLower() == "inv")
                {
                    if(stack.length() >= 1 && stack[stack.length()-1]->getType() == T_MATRIX)
                    {
                        //Get params
                        Matrix *mat = dynamic_cast<Matrix*>(stack[stack.length()-1]);
                        stack.removeLast();
                        //Calculate
                        stack.append(MatrixLib::inv(mat));
                    }
                    else
                    {
                        throw std::runtime_error("Help : inv(<b>Matrix</b> mat)");
                    }
                }
                //trace(Matrix mat) : Generate the trace matrix of mat
                else if(token.getValue().toLower() == "trace")
                {
                    if(stack.length() >= 1 && stack[stack.length()-1]->getType() == T_MATRIX)
                    {
                        //Get params
                        Matrix *mat = dynamic_cast<Matrix*>(stack[stack.length()-1]);
                        stack.removeLast();
                        //Calculate
                        Scalar *tmp = new Scalar(MatrixLib::trace(mat));
                        stack.append(tmp);
                    }
                    else
                    {
                        throw std::runtime_error("Help : trace(<b>Matrix</b> mat)");
                    }
                }
                //norm(Matrix mat) : Calculate the norm of a column or row matrix
                else if(token.getValue().toLower() == "norm")
                {
                    if(stack.length() >= 1 && stack[stack.length()-1]->getType() == T_MATRIX)
                    {
                        //Get params
                        Matrix *mat = dynamic_cast<Matrix*>(stack[stack.length()-1]);
                        stack.removeLast();
                        //Calculate
                        Scalar *tmp = new Scalar(MatrixLib::norm(mat));
                        stack.append(tmp);
                    }
                    else
                    {
                        throw std::runtime_error("Help : norm(<b>Matrix</b> mat)");
                    }
                }
                //solve(Matrix|Scalar A, Matrix|Scalar B) : Solve a linear equation of type A*x=B
                else if(token.getValue().toLower() == "solve")
                {
                    if(stack.length() >= 2
                            && ((stack[stack.length()-1]->getType() == T_MATRIX && stack[stack.length()-2]->getType() == T_MATRIX)
                            || (stack[stack.length()-1]->getType() == T_SCALAR && stack[stack.length()-2]->getType() == T_SCALAR)))
                    {
                        //Scalar
                        if(stack[stack.length()-1]->getType() == T_SCALAR)
                        {
                            //Get params
                            Calculable &B = *(stack[stack.length()-1]);
                            stack.removeLast();
                            Calculable &A = *(stack[stack.length()-1]);
                            stack.removeLast();
                            //Result
                            stack.append(A/B);
                        }
                        else
                        {
                            //Get params
                            Calculable &B = *(stack[stack.length()-1]);
                            stack.removeLast();
                            //Get params
                            Matrix *A = dynamic_cast<Matrix*>(stack[stack.length()-1]);
                            stack.removeLast();
                            //Result
                            stack.append(B*(*MatrixLib::inv(A)));

                        }
                    }
                    else
                    {
                        throw std::runtime_error("Help : Solve a linear equation of type A*x=B<br/>solve(<b>Matrix</b> A, <b>Matrix</b> B)<br/>solve(<b>Scalar</b> A, <b>Scalar</b> B)");
                    }
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

                case T_MODULO:
                    stack.append(a%b);
                    break;

                case T_POW:
                    stack.append(a^b);
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
