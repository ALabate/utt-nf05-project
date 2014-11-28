#include "parser.h"


/**
 * @brief Constructor
 * 
 * @param source QString to parse
 * @param registry memory where to set the variables
 */

Parser::Parser(QString source, QList<VarNode *> *registry)
{
    this->source = source;
    this->lexer = new Lexer(source);
    this->registry = registry;
}


/**
 * @brief Initialize the operator list ordered by priority
 * @return the operator list 
 */

QList<TokenKind> Parser::initializeOperators()
{
    QList<TokenKind> operators;
    operators.append(T_ASSIGNMENT);
    operators.append(T_SUM);
    operators.append(T_SUB);
    operators.append(T_MULTIPLY);
    operators.append(T_DIVIDE);

    return operators;
}

QList<TokenKind> Parser::operators = Parser::initializeOperators();


/**
 * @brief run the parser
 * @return a Calculable
 */

Calculable* Parser::run()
{
    QList<Token> tokens = this->lexer->run();

    if (tokens.length() == 0)
    {
        return NULL;
    }

    int assignationNumber = 0;

    foreach (Token token, tokens)
    {
        if (token.getKind() == T_ASSIGNMENT)
        {
            assignationNumber++;
        }
    }

    if (assignationNumber > 1)
    {
        qDebug() << "Error: multiple assignation";
        return NULL;
    }
    else
    {
        Node *tree = this->generateTree(tokens);
        return tree->execute();    
    }
}


/**
 * @brief generate a Node tree representation of a tokenList
 * 
 * @param tokens the tokenList to parse
 * @return a Node tree representation of the tokenlist
 */

Node* Parser::generateTree(QList<Token> tokens)
{

    if (tokens.length() == 1)
    {
        Token token = tokens[0];
        TokenKind kind = token.getKind();


        if (kind == T_DOUBLE)
        {
            double value = token.getValue().toDouble();
            Calculable *calculable = new Calculable(value);
            CalculableNode *node = new CalculableNode(calculable);
            return node;
        }
        else if (kind == T_STRING)
        {
            QString reference = token.getValue();

            VarNode *varNode = VarNode::getVar(reference, this->registry);
            qDebug() << varNode->getName();
            return varNode;
        }
        else
        {
            qDebug() << "Token not at the right place";
        }

    }
    else
    {
        int currentLevel = 0;
        bool isThereRootToken = false;

        for (int i = 0; i < Parser::operators.length(); i++)
        {
            TokenKind operator_ = Parser::operators[i];

            for (int j = tokens.length()-1; j >= 0; j--)
            {
                Token token = tokens[j];
                TokenKind kind = token.getKind();

                if (kind == T_PARENTHESIS_LEFT)
                {  
                    currentLevel++;
                }
                else if (kind == T_PARENTHESIS_RIGHT)
                {
                    currentLevel--;
                }
                else
                {
                    if (currentLevel == 0)
                    {
                        isThereRootToken = true;

                        if (kind == operator_)
                        {
                            Node *right = Parser::generateTree(tokens.mid(j+1, tokens.length()-1));

                            if (kind == T_ASSIGNMENT) 
                            {
                                QList<Token> varName = tokens.mid(0, j);

                                if (varName.length() > 1 || varName[0].getKind() != T_STRING)
                                {
                                    qDebug() << "Invalid syntax for assignment";
                                    return NULL;
                                }

                                VarNode *varNode = VarNode::getVar(varName[0].getValue(), this->registry);
                                AssignationNode *assignationNode = new AssignationNode(varNode, right);
                                return assignationNode;
                            }

                           Node *left = Parser::generateTree(tokens.mid(0, j));

                            switch (kind)
                            {
                                case T_SUM:
                                {
                                    OperatorNode *operatorNode = new OperatorNode(O_SUM, left, right);
                                    return operatorNode;
                                    break;

                                }
                                 
                                case T_SUB:
                                {
                                    OperatorNode *operatorNode = new OperatorNode(O_SUB, left, right);
                                    return operatorNode;
                                    break;
                                }
                                    
                                case T_MULTIPLY:
                                {
                                    OperatorNode *operatorNode = new OperatorNode(O_MULTIPLY, left, right);
                                    return operatorNode;
                                    break;
                                }
                                    
                                case T_DIVIDE:
                                {
                                    OperatorNode *operatorNode = new OperatorNode(O_DIVIDE, left, right);
                                    return operatorNode;
                                    break;   
                                }
                                 
                            }
                        }
                    }                    
                }
            }        
        }   

        if (!isThereRootToken && tokens[0].getKind() == T_PARENTHESIS_LEFT
            && tokens[tokens.length()-1].getKind() == T_PARENTHESIS_RIGHT)
        {
            return Parser::generateTree(tokens.mid(1, tokens.length()-2));
        }
    }
}
