#ifndef VARNODE_H
#define VARNODE_H

#include <QDebug>
#include <QString>
#include <QList>
#include <QMap>

#include "lib/node.h"
#include "lib/token.h"
#include "lib/calculableNode.h"

class VarNode : public Node
{
    public:
        VarNode(QString varName, Calculable *value);

        virtual Calculable* execute();
        virtual QString toString() const;

        void setValue(Calculable *value);
        Calculable* getValue() const;
        QString getName() const;

        static VarNode* getVar(QString reference, QList<VarNode *> *registry);
        
        
    protected:
        QString varName;
        Calculable *value;
        QMap<QString, Calculable *> registry;
};

#endif // VARNODE_H
