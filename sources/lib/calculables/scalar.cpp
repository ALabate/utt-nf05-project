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
    else if(a.getType() == T_MATRIX)
    {
        return a.operator*(*this);
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
    else if(a.getType() == T_MATRIX)
    {

        Matrix& a2 = dynamic_cast<Matrix&>(a);
        Matrix *out = new Matrix();

        //Set new matrix size
        out->setM(a2.getM());
        out->setN(a2.getN());

        //set values
        for(int i=0; i < out->getM(); i++)
        {
            for(int j=0; j < out->getN() ; j++)
            {
                out->setCell(i, j, a2.getCell(i, j) / this->getRawValue());
            }
        }
        return out;
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
