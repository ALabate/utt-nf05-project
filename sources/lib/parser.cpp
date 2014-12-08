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


        if (kind == T_DOUBLE || kind == T_STRING)
        {
            ExpressionNode* node = new ExpressionNode(tokens);
            return node;
        }
        else
        {
            return NULL;
        }
    }
    else
    {
        //Search for an assignement
        for (int i = 0; i < tokens.length(); i++)
        {
            if (tokens[i].getKind() == T_ASSIGNMENT)
            {
                QList<Token> varName = tokens.mid(0, i);

                if (varName.length() > 1 || varName[0].getKind() != T_STRING)
                {
                    qDebug() << "Invalid syntax for assignment";
                    return NULL;
                }

                ExpressionNode* right = (ExpressionNode*) generateTree(tokens.mid(i+1, tokens.length()-1));
                VarNode *varNode = VarNode::getVar(varName[0].getValue(), this->registry);


                AssignationNode *assignationNode = new AssignationNode(varNode, right);
                return assignationNode;
            }
        }

        return new ExpressionNode(tokens);
    }

}
