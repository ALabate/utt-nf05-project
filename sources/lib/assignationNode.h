#ifndef ASSIGNATIONNODE_H
#define ASSIGNATIONNODE_H

#include <QDebug>
#include <QString>
#include <QList>
#include <QMap>

#include "lib/node.h"
#include "lib/varNode.h"
#include "lib/token.h"


class AssignationNode : public Node
{
    public:
        AssignationNode(VarNode *variable, Node *expression);

        virtual Calculable* execute();
        virtual QString toString() const;

        VarNode* getVariable() const;
        Node* getExpression() const;


    protected:
        VarNode *variable;
        Node *expression;
};

#endif // ASSIGNATIONNODE_H
