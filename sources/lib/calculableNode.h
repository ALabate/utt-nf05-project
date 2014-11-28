#ifndef CALCULABLENODE_H
#define CALCULABLENODE_H

#include <QDebug>
#include <QString>
#include <QList>
#include <QMap>

#include "lib/calculable.h"
#include "lib/node.h"


class CalculableNode : public Node
{
    public:
        CalculableNode(Calculable *value);

        virtual Calculable* execute();
        virtual QString toString() const;


    protected:
        Calculable *value;
};

#endif // CALCULABLENODE_H
