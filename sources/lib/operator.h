#ifndef OPERATOR_H
#define OPERATOR_H

#include <QMap>
#include "token.h"


enum Associativity
{
    LEFT_ASSOC,
    RIGHT_ASSOC
};


class Operator
{
    public:
        Operator(int precedence, Associativity associativity);
        ~Operator();


        static bool isOperator(Token token);
        static QMap<int, Operator*> operators;

        int getPrecedence();
        Associativity getAssociativity();


   protected:
        static QMap<int, Operator *> initializeOperators();

        int precedence;
        Associativity associativity;
};

#endif // OPERATOR_H
