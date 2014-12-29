#ifndef CALCULABLE_H
#define CALCULABLE_H

#include <QDebug>
#include <stdexcept>
#include <typeinfo>
#include "token.h"


class Calculable
{
    public:

        /**
         * @brief constructor
         *
         * @param value the calculable value
         */
        Calculable(QString value);

        /**
         * @brief constructor
         */
        Calculable();

        /**
         * @brief destructor
         * @details [long description]
         */
        ~Calculable();

        /**
         * @brief value accessor
         *
         * @return the value of the Calculable
         */
        virtual QString getValue();

        /**
         * @brief value setter
         *
         * @param newValue the value to set
         */
        virtual void setValue(QString newValue);

        /**
         * @brief toString method
         *
         * @return a QString representation of the Node
         */
        virtual QString toString();

        /**
         * @brief overload operator * between two Calculable
         *
         * @param a a Calculable
         * @return a Calculable
         */
        virtual Calculable* operator*(Calculable &a);

        /**
         * @brief overload operator / between two Calculable
         *
         * @param a a Calculable
         * @return a Calculable
         */
        virtual Calculable* operator/(Calculable &a);

        /**
         * @brief overload operator - between two Calculable
         *
         * @param a a Calculable
         * @return a Calculable
         */
        virtual Calculable* operator+(Calculable &a);

        /**
         * @brief overload operator + between two Calculable
         *
         * @param a a Calculable
         * @return a Calculable
         */
        virtual Calculable* operator-(Calculable &a);

        /**
         * @brief Define the type of the element as a string
         */
         virtual std::string getTypeStr() = 0;

        /**
         * @brief Define the type of the element as a TokenKind from token.h
         */
         virtual TokenKind getType() = 0;

};

#endif // CALCULABLE_H
