#include "calculable.h"

Calculable::Calculable(QString value)
{
    this->setValue(value);
}

Calculable::Calculable()
{
}


Calculable::~Calculable() {}

QString Calculable::getValue()
{
    throw std::runtime_error("Cannot get value of an element of type " + getType());
}


void Calculable::setValue(QString newValue)
{
    throw std::runtime_error("Cannot set value of an element of type " + getType());
}

QString Calculable::toString()
{
     return QString(getType().c_str()) + " value: " + this->getValue();
}

Calculable* Calculable::operator*(Calculable &a)
{
    throw std::runtime_error("Cannot use the operator * with an element of type " + getType());
}


Calculable* Calculable::operator/(Calculable &a)
{
    throw std::runtime_error("Cannot use the operator / with an element of type " + getType());
}


Calculable* Calculable::operator-(Calculable &a)
{
    throw std::runtime_error("Cannot use the operator - with an element of type " + getType());
}


Calculable* Calculable::operator+(Calculable &a)
{
    throw std::runtime_error("Cannot use the operator +  with an element of type " + getType());
}
