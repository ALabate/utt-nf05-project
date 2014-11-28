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
#include "lib/node.h"
#include "lib/varNode.h"
#include "lib/calculableNode.h"
#include "lib/assignationNode.h"
#include "lib/operatorNode.h"
#include "lib/varNode.h"


class Parser : public QObject
{
    Q_OBJECT

    public:
        Parser(QString source, QList<VarNode *> *registry);
        Calculable* run();

    private:
        static QList<TokenKind> operators;
        static QList<TokenKind> initializeOperators();
        
        Node* generateTree(QList<Token> tokens);
        QString source;
        Lexer *lexer;
        QList<VarNode *> *registry;

    signals:
        void parenthesisError();
};

#endif // PARSER_H
