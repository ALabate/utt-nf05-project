#ifndef EXPRESSIONNODE_H
#define EXPRESSIONNODE_H

#include <QDebug>
#include <QString>
#include <QList>
#include <QMap>

#include "lib/node.h"
#include "lib/calculable.h"
#include "lib/token.h"
#include "lib/operator.h"


class VarNode;

class ExpressionNode : public Node
{
    public:
        ExpressionNode(QList<Token> expression, QList<VarNode *>* registry);
        ~ExpressionNode();

        Calculable* execute();
        QString toString() const;


    protected:
        void convertToRPN();
        bool isFunction(Token token);

        QList<VarNode*>* registry;
        QList<Token> expression;
        Calculable* value;
};

#endif // EXPRESSIONNODE_H
