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

        /**
         * @brief constructor
         */
        Node();

        /**
         * @brief destructor
         */
        ~Node();

        /**
         * @brief Pure virtual method. Execute the node depending on its type (use polymorphism)
         */
        virtual Calculable* execute() = 0;


        /**
         * @brief Pur virtual method. Return a string-based representation of the node.
         */
        virtual QString toString() const = 0 ;
};

#endif // NODE_H
