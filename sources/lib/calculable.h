#ifndef CALCULABLE_H
#define CALCULABLE_H

#include <QDebug>
#include <stdexcept>
#include <typeinfo>


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
        virtual QString getValue() const;

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
        virtual QString toString() const;

        /**
         * @brief overload operator * between two Calculable
         *
         * @param a a Calculable
         * @return a Calculable
         */
        virtual Calculable* operator*(Calculable const &a);

        /**
         * @brief overload operator / between two Calculable
         *
         * @param a a Calculable
         * @return a Calculable
         */
        virtual Calculable* operator/(Calculable const &a);

        /**
         * @brief overload operator - between two Calculable
         *
         * @param a a Calculable
         * @return a Calculable
         */
        virtual Calculable* operator+(Calculable const &a);

        /**
         * @brief overload operator + between two Calculable
         *
         * @param a a Calculable
         * @return a Calculable
         */
        virtual Calculable* operator-(Calculable const &a);

        /**
         * @brief Define the type of the element
         */
         virtual std::string getType() const = 0;

};

#endif // CALCULABLE_H
