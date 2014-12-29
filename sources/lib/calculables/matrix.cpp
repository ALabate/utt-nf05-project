#include "matrix.h"



Matrix::Matrix(QString value)
{
    N=-1;M=-1;
    this->setValue(value);
}

Matrix::Matrix()
{
    N=-1;M=-1;
    this->setM(1);
    this->setN(1);
}

QString Matrix::getValue()
{

    QString out = "[";

    for(int i=0; i < this->getM(); i++)
    {
        if(i != 0)
            out += " !\n ";

        for(int j=0; j < this->getN(); j++)
        {
            if(j != 0)
                out += " ; ";

            out += QString::number(this->getCell(i, j));
        }
    }


    return (out + ']');
}

void Matrix::setValue(QString newValue)
{

    //Remove []
    newValue.remove('[');
    newValue.remove(']');

    //Parse matrix format a;b!c;d
    QStringList rows = newValue.split('!');
    this->setM(rows.size());

    //iterate over rows
    for(int i=0; i < this->getM(); i++)
    {
        QStringList cols = rows[i].split(';');

        //Resize matrix if first line
        if(i == 0)
            this->setN(cols.size());
        else if(cols.size() != this->N)
            throw std::runtime_error("Matrix [" +  newValue.toStdString() + "] cannot be parsed : Row " + QString::number(i+1).toStdString()  + " doens't have the same column number as the precedent row");

        //iterate over columns
        for(int j=0; j<this->getN() ; j++)
        {
            //Parse cell
            //TODO GET VARS VALUES
            Parser parser(cols[j], NULL);
            Calculable &colVal = *(parser.run());

            //Errors
            if(colVal.getType() != "scalar") //TODO add T_SCALAR value to replace string
                throw std::runtime_error("Only scalar types can be inside matrix");
            else if(colVal.getValue() == NULL)
                throw std::runtime_error("Unknown error happend during matrix computation");

            //insert value
            this->setCell(i, j, dynamic_cast<Scalar&>(colVal).getRawValue());

        }
    }
}

Calculable* Matrix::operator*(Calculable &a)
{
    if(this->getType() == a.getType())
    {
        Matrix& a2 = dynamic_cast<Matrix&>(a);
        Matrix *out = new Matrix();

        //Set new matrix size
        if(this->getM() == a2.getN())
        {
            out->setM(a2.getM());
            out->setN(this->getN());
        }
        else
        {
            throw std::runtime_error("Cannot multiply a matrix "
                                     + QString::number(a2.getM()).toStdString() + "x" + QString::number(a2.getN()).toStdString()
                                     + " with a matrix "
                                     + QString::number(this->getM()).toStdString() + "x" + QString::number(this->getN()).toStdString());
        }

        //set values
        for(int i=0; i < out->getM(); i++)
        {
            for(int j=0; j < out->getN() ; j++)
            {
                double sum = 0;
                for(int k=0; k < this->getM(); k++)
                {
                    sum += a2.getCell(i, k) * this->getCell(k, j);
                }
                out->setCell(i, j, sum);
            }
        }
        return out;
    }
    else
    {
        throw std::runtime_error("Cannot use the operator * between a " + a.getType() + " and a " + this->getType());
    }
    return NULL;
}

Calculable* Matrix::operator/(Calculable &a)
{
    return NULL;
}

Calculable* Matrix::operator+(Calculable &a)
{
    return NULL;
}

Calculable* Matrix::operator-(Calculable &a)
{
    return NULL;
}




int Matrix::getM() {
    return this->M;
}
int Matrix::getN() {
    return this->N;
}
void Matrix::setM(int M) {

    if(M >= 1)
    {
        this->M = M;
        value.resize(M);
        if(N > 0)
        {
            for(int i = 0; i<M; i++)
            {
                value[i].resize(N);
            }
        }
    }
}
void Matrix::setN(int N) {
    if(N >= 1)
    {
        this->N = N;
        if(this->M > 0)
        {
            for(int i = 0; i<M; i++)
                value[i].resize(N);
        }
    }
}
double Matrix::getCell(const int i, const int j) {
    if(0 <= i && i < this->M && 0 <= j && j < this->N)
        return this->value[i][j];
    return 0;
}
void Matrix::setCell(const int i, const int j, const double value)
{
    if(0 <= i && i < this->M && 0 <= j && j < this->N)
        this->value[i][j] = value;
}

std::string Matrix::getType()
{
    return "matrix";
}
