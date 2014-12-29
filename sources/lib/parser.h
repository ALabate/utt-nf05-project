#ifndef PARSER_H
#define PARSER_H

#include <QString>
#include <QList>
#include <QObject>
#include <QDebug>
#include <QList>

#include "lib/lexer.h"
#include "lib/token.h"
#include "lib/expressionNode.h"
#include "lib/assignationNode.h"
#include "lib/varNode.h"
#include "lib/calculable.h"


class VarNode;

class Parser : public QObject
{
    Q_OBJECT

    public:

        /**
         * @brief constructor
         *
         * @param source QString to parse
         */
        Parser(QString source);

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


    public:

        /**
         * @brief isFunction check if a token is a function
         * @param token to test
         * @return type of token
         */
        static bool isFunction(Token token);


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


    signals:
        void parenthesisError();
};

#endif // PARSER_H
