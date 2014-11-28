#include "calculable.h"


/**
 * @brief constructor
 * 
 * @param value the calculable value
 */

Calculable::Calculable(double value)
{
    this->value = value;
}


/**
 * @brief value accessor
 * 
 * @return the value of the Calculable
 */

double Calculable::getValue() const
{
    return this->value;
}


/**
 * @brief value setter
 * 
 * @param newValue the value to set
 */

void Calculable::setValue(double newValue)
{
    this->value = newValue;
}


/**
 * @brief toString method
 * 
 * @return a QString representation of the Node
 */

QString Calculable::toString() const
{
    return "Calculable value: " + QString::number(this->getValue());
}


/**
 * @brief overload operator * between two Calculable
 * 
 * @param a a Calculable
 * @return a Calculable
 */

Calculable Calculable::operator*(Calculable const &a)
{
    return Calculable(this->getValue() * a.getValue());
}


/**
 * @brief overload operator / between two Calculable
 * 
 * @param a a Calculable
 * @return a Calculable
 */

Calculable Calculable::operator/(Calculable const &a)
{
    return Calculable(this->getValue() / a.getValue());
}


/**
 * @brief overload operator - between two Calculable
 * 
 * @param a a Calculable
 * @return a Calculable
 */

Calculable Calculable::operator-(Calculable const &a)
{
    return Calculable(this->getValue() - a.getValue());
}


/**
 * @brief overload operator + between two Calculable
 * 
 * @param a a Calculable
 * @return a Calculable
 */

Calculable Calculable::operator+(Calculable const &a)
{
    return Calculable(this->getValue() + a.getValue());
}