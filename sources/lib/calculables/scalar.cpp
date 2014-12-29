#include "scalar.h"


Scalar::Scalar(QString value)
{
    this->setValue(value);
}
Scalar::Scalar(double value)
{
    this->setRawValue(value);
}

QString Scalar::getValue()
{
    return QString::number(this->value);
}
double Scalar::getRawValue()
{
    return this->value;
}

void Scalar::setValue(QString newValue)
{
    bool ok;
    this->value = newValue.toDouble(&ok);
    if(!ok)
    {
        throw std::runtime_error("Could not convert " + newValue.toStdString() + " to scalar type");
    }
}

void Scalar::setRawValue(double newValue)
{
    this->value = newValue;
}

Calculable* Scalar::operator*(Calculable &a)
{
    if(this->getType() == a.getType())
    {
        return new Scalar(dynamic_cast<Scalar&>(a).getRawValue() * this->value);
    }
    else
    {
        throw std::runtime_error("Cannot use the operator * between a " + a.getTypeStr() + " and a " + this->getTypeStr());
        return NULL;
    }
}

Calculable* Scalar::operator/(Calculable &a)
{
    if(this->getType() == a.getType())
    {
        return new Scalar(dynamic_cast<Scalar&>(a).getRawValue() / this->value);
    }
    else
    {
        throw std::runtime_error("Cannot use the operator / between a " + a.getTypeStr() + " and a " + this->getTypeStr());
        return NULL;
    }
}

Calculable* Scalar::operator-(Calculable &a)
{
    if(this->getType() == a.getType())
    {
        return new Scalar(dynamic_cast<Scalar&>(a).getRawValue() - this->value);
    }
    else
    {
        throw std::runtime_error("Cannot use the operator - between a " + a.getTypeStr() + " and a " + this->getTypeStr());
        return NULL;
    }
}
Calculable* Scalar::operator+(Calculable &a)
{
    if(this->getType() == a.getType())
    {
        return new Scalar(dynamic_cast<Scalar&>(a).getRawValue() + this->value);
    }
    else
    {
        throw std::runtime_error("Cannot use the operator + between a " + a.getTypeStr() + " and a " + this->getTypeStr());
        return NULL;
    }
}


std::string Scalar::getTypeStr()
{
    return "scalar";
}

TokenKind Scalar::getType()
{
    return T_SCALAR;
}
