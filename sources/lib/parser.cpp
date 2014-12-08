#include "parser.h"



Parser::Parser(QString source, QList<VarNode *> *registry)
{
    this->source = source;
    this->lexer = new Lexer(source);
    this->registry = registry;
}


Parser::~Parser() {}


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


Node* Parser::generateTree(QList<Token> tokens)
{
    if (tokens.length() == 1)
    {
        Token token = tokens[0];
        TokenKind kind = token.getKind();


        if (kind == T_DOUBLE || kind == T_STRING)
        {
            ExpressionNode* node = new ExpressionNode(tokens, this->registry);
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

        return new ExpressionNode(tokens, this->registry);
    }

}
