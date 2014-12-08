#ifndef VARNODE_H
#define VARNODE_H

#include <QDebug>
#include <QString>
#include <QList>
#include <QMap>

#include "lib/node.h"
#include "lib/token.h"
#include "lib/expressionNode.h"


class VarNode : public Node
{
    public:

        /**
         * @brief constructor
         *
         * @param varName QString of the varName
         * @param registry Map containing memory
         */
        VarNode(QString varName, Calculable *value);

        /**
         * @brief destructor
         */
        ~VarNode();


    public:

        /**
         * @brief return a var if it exists or a new one if it doesn't
         *
         * @param reference var name
         * @param registry memory where to find/create the var
         *
         * @return a pointer to the new/already existing VarNode
         */
        static VarNode* getVar(QString reference, QList<VarNode *> *registry);


    public:

        /**
         * @brief Execute the node
         *
         * @return a Calculable pointer
         */
        virtual Calculable* execute();

        /**
         * @brief toString method
         * @return a QString representation of the Node
         */
        virtual QString toString() const;


        /**
         * @brief Set a value in the registry
         *
         * @param value Calculable to set
         */
        void setValue(Calculable *value);

        /**
         * @brief value accessor
         *
         * @return a pointer to the node's value
         */
        Calculable* getValue() const;

        /**
         * @brief varName accessor
         * @return the var name
         */
        QString getName() const;


    protected:
        QString varName;
        Calculable *value;
        QMap<QString, Calculable *> registry;
};

#endif // VARNODE_H
