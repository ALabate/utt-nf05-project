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

        /**
         * @brief constructor
         *
         * @param precedence precedence of the operator
         * @param associativity associativity type of the operator
         */
        Operator(int precedence, Associativity associativity);

        /**
         * @brief destructor
         */
        ~Operator();


    public:

        /**
         * @brief determine if a token is an operator or a function
         *
         * @param token token to test
         * @return nature of the token
         */
        static bool isOperator(Token token);

        static QMap<int, Operator*> operators;


   protected:

        /**
         * @brief fill the operators QMap
         *
         * @return a filled QMap containing all operators
         */
        static QMap<int, Operator *> initializeOperators();


    public:

        /**
         * @brief predecence accessor
         *
         * @return predecence
         */
        int getPrecedence();

        /**
         * @brief associativity accessor
         *
         * @return associativity type
         */
        Associativity getAssociativity();

        int precedence;
        Associativity associativity;
};

#endif // OPERATOR_H