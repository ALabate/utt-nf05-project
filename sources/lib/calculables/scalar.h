#ifndef SCALAR_H
#define SCALAR_H

#include "../calculable.h"
#include "matrix.h"
#include <cmath>

class Scalar : public Calculable
{
public:

    /**
     * @brief constructor
     *
     * @param value - the string value
     */
    Scalar(QString value);

    /**
     * @brief constructor
     *
     * @param value the raw value
     */
    Scalar(double value);

    /**
     * @brief Copy constructor
     *
     * @param value the raw value
     */
    Scalar(Scalar &value);

    /**
     * @brief value accessor
     *
     * @return the value of the Calculable
     */
    QString getValue();

    /**
     * @brief value accessor
     *
     * @return the raw value of the Calculable
     */
    double getRawValue();

    /**
     * @brief value setter
     *
     * @param newValue the value to set
     */
    void setValue(QString newValue);
    /**
     * @brief value setter
     *
     * @param newValue the value to set
     */
    void setRawValue(double newValue);

    /**
     * @brief overload operator * between two Calculable
     *
     * @param a a Calculable
     * @return a Calculable
     */
    Calculable* operator*(Calculable &a);

    /**
     * @brief overload operator / between two Calculable
     *
     * @param a a Calculable
     * @return a Calculable
     */
    Calculable* operator/(Calculable &a);

    /**
     * @brief overload operator + between two Calculable
     *
     * @param a a Calculable
     * @return a Calculable
     */
    Calculable* operator+(Calculable &a);

    /**
     * @brief overload operator - between two Calculable
     *
     * @param a a Calculable
     * @return a Calculable
     */
    Calculable* operator-(Calculable &a);

    /**
     * @brief overload operator % between two Calculable
     *
     * @param a a Calculable
     * @return a Calculable
     */
    Calculable* operator%(Calculable &a);

    /**
     * @brief overload operator ^ between two Calculable
     *
     * @param a a Calculable
     * @return a Calculable
     */
    Calculable* operator^(Calculable &a);


    /**
     * @brief Define the type of the element as a string
     */
     std::string getTypeStr();

    /**
     * @brief Define the type of the element as a TokenKind from token.h
     */
     TokenKind getType();

protected:
    double value;
};

#endif // SCALAR_H
