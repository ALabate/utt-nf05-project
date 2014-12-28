#include "matrix.h"



Matrix::Matrix(QString value)
{
    this->setValue(value);
}

void Matrix::setValue(QString newValue)
{
    qDebug() << "Matrix : " + newValue;
    int line = -1;
    //Parse matrix
//    for(int i = 0; i < value.length(); i++)
//    {

//    }
}



std::string Matrix::getType() const
{
    return "matrix";
}

