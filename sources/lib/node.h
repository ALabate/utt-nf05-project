#ifndef NODE_H
#define NODE_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QList>
#include <QMap>


#include <lib/calculable.h>
#include <lib/token.h>


class Node : public QObject
{
    Q_OBJECT

    public:
        Node();

        virtual Calculable* execute() = 0;
        virtual QString toString() const = 0 ;
};

#endif // NODE_H
