#ifndef PARSER_H
#define PARSER_H

#include <QString>
#include <QList>
#include <QObject>
#include <QDebug>
#include <QList>

#include "lib/calculable.h"
#include "lib/lexer.h"
#include "lib/token.h"
#include "lib/expressionNode.h"
#include "lib/assignationNode.h"
#include "lib/varNode.h"


class Parser : public QObject
{
    Q_OBJECT

    public:

        /**
         * @brief constructor
         *
         * @param source QString to parse
         * @param registry memory where to set the variables
         */
        Parser(QString source, QList<VarNode *> *registry);

        /**
         * @brief destructor
         */
        ~Parser();

        /**
         * @brief run the parser
         *
         * @return a Calculable
         */
        Calculable* run();


    private:

        /**
         * @brief generate a Node tree representation of a tokenList
         *
         * @param tokens the tokenList to parse
         * @return a Node tree representation of the tokenlist
         */
        Node* generateTree(QList<Token> tokens);

        QString source;
        Lexer *lexer;
        QList<VarNode *> *registry;


    signals:
        void parenthesisError();
};

#endif // PARSER_H
