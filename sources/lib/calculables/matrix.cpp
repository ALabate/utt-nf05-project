#include "matrix.h"



Matrix::Matrix(QString value)
{
    this->value = new QVector< QVector<double>* >();
    this->setValue(value);
}

void Matrix::setValue(QString newValue)
{
    this->rowCount = 0;
    //Parse matrix 1;2!2;3
    QStringList rows = newValue.split('!');
    foreach (QString row, rows)
    {
        value->resize(this->rowCount + 1);
        value->insert(this->rowCount, new QVector<double>());
        int column = 0;
        QStringList cols = newValue.split(';');
        foreach (QString colStr, cols)
        {

            //Parse cell
            Parser parser(colStr, NULL);
            Calculable &colVal = *(parser.run());

            //Errors
            if(colVal.getType() != "scalar") //TODO add T_SCALAR value to replace string
                throw std::runtime_error("Only scalar types can be inside matrix");
            else if(colVal.getValue() == NULL)
                throw std::runtime_error("Unknown error happend during matrix computation");

            //Resize matrix
            if(this->rowCount == 0)
                value->at(this->rowCount)->resize(column + 1);

            //insert value
            if(column < value->at(this->rowCount)->size())
                value->at(this->rowCount)->insert(column, dynamic_cast<const Scalar&>(colVal).getRawValue());

            column++;
        }
        //Check if same column count for each rows
        if(this->rowCount == 0)
            this->columnCount = column;
        else if(this->columnCount != column)
            throw std::runtime_error("Matrix (" +  newValue.toStdString() + ") cannot be parsed : Row " + QString::number(this->rowCount+1).toStdString()  + " doens't have the same column number as the row before");

        this->rowCount++;
    }
}



std::string Matrix::getType() const
{
    return "matrix";
}

