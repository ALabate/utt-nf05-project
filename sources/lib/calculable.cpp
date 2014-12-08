#include "calculable.h"


Calculable::Calculable(double value)
{
    this->value = value;
}


Calculable::~Calculable() {}


double Calculable::getValue() const
{
    return this->value;
}


void Calculable::setValue(double newValue)
{
    this->value = newValue;
}


QString Calculable::toString() const
{
    return "Calculable value: " + QString::number(this->getValue());
}


Calculable* Calculable::operator*(Calculable const &a)
{
    return new Calculable(this->getValue() * a.getValue());
}


Calculable* Calculable::operator/(Calculable const &a)
{
    return new Calculable(this->getValue() / a.getValue());
}


Calculable* Calculable::operator-(Calculable const &a)
{
    return new Calculable(this->getValue() - a.getValue());
}


Calculable* Calculable::operator+(Calculable const &a)
{
    return new Calculable(this->getValue() + a.getValue());
}