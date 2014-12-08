#ifndef CALCULABLE_H
#define CALCULABLE_H

#include <QDebug>


class Calculable
{
    public:

        /**
         * @brief constructor
         *
         * @param value the calculable value
         */
        Calculable(double value);

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
        double getValue() const;

        /**
         * @brief value setter
         *
         * @param newValue the value to set
         */
        void setValue(double newValue);

        /**
         * @brief toString method
         *
         * @return a QString representation of the Node
         */
        QString toString() const;

        /**
         * @brief overload operator * between two Calculable
         *
         * @param a a Calculable
         * @return a Calculable
         */
        Calculable* operator*(Calculable const &a);

        /**
         * @brief overload operator / between two Calculable
         *
         * @param a a Calculable
         * @return a Calculable
         */
        Calculable* operator/(Calculable const &a);

        /**
         * @brief overload operator - between two Calculable
         *
         * @param a a Calculable
         * @return a Calculable
         */
        Calculable* operator+(Calculable const &a);

        /**
         * @brief overload operator + between two Calculable
         *
         * @param a a Calculable
         * @return a Calculable
         */
        Calculable* operator-(Calculable const &a);


    protected:
       double value;
};

#endif // CALCULABLE_H
