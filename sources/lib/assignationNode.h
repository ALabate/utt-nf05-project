#ifndef ASSIGNATIONNODE_H
#define ASSIGNATIONNODE_H

#include <QDebug>
#include <QString>
#include <QList>
#include <QMap>

#include "lib/node.h"
#include "lib/varNode.h"
#include "lib/expressionNode.h"
#include "lib/token.h"


class AssignationNode : public Node
{
    public:
        AssignationNode(VarNode *variable, ExpressionNode *expression);

        virtual Calculable* execute();
        virtual QString toString() const;

        VarNode* getVariable() const;
        ExpressionNode* getExpression() const;


    protected:
        VarNode *variable;
        ExpressionNode *expression;
};

#endif // ASSIGNATIONNODE_H
