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
#include "lib/calculables/scalar.h"
#include "lib/calculables/matrix.h"


class VarNode;

class ExpressionNode : public Node
{
    public:

        /**
         * @brief constructor
         *
         * @param value a pointer to the Calculable
         */
        ExpressionNode(QList<Token> expression, QList<VarNode *>* registry);

        /**
         * @brief destructor
         */
        ~ExpressionNode();

        /**
         * @brief Execute the node
         *
         * @return a Calculable pointer
         */
        Calculable* execute();

        /**
         * @brief toString method
         *
         * @return a QString representation of the Node
         */
        QString toString() const;


    protected:

        /**
         * @brief Convert current expression to a RPN notation
         */
        void convertToRPN();

        /**
         * @brief Determine if a token is a function or a variable
         *
         * @param token token
         * @return nature of the token
         */
        bool isFunction(Token token);

        QList<VarNode*>* registry;
        QList<Token> expression;
        Calculable* value;
};

#endif // EXPRESSIONNODE_H
