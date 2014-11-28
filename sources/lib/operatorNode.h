#ifndef OPERATORNODE_H
#define OPERATORNODE_H

#include <QDebug>
#include <QString>
#include <QList>
#include <QMap>

#include "lib/calculable.h"
#include "lib/node.h"
#include "lib/assignationNode.h"
#include "lib/token.h"


enum OperatorKind
{
    O_MULTIPLY,
    O_DIVIDE,
    O_SUM,
    O_SUB
};


class OperatorNode : public Node
{
    public:
        OperatorNode(OperatorKind kind, Node *left, Node *right);
        
        virtual Calculable* execute();
        virtual QString toString() const;
        
        Node* getLeft() const;
        Node* getRight() const;
        

    protected:
        OperatorKind kind;
        Node *left;
        Node *right;
};

#endif // OPERATORNODE_H
