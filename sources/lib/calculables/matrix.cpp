#include "matrix.h"



Matrix::Matrix(QString value)
{
    N=-1;M=-1;
    this->setValue(value);
}

Matrix::Matrix(Matrix &value)
{
    N=-1;M=-1;
    this->setValue(&value);
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
            out += " |\n ";

        for(int j=0; j < this->getN(); j++)
        {
            if(j != 0)
                out += " ; ";

            out += QString::number(this->getCell(i, j));
        }
    }


    return (out + ']');
}

QVector< QVector<double> > Matrix::getRawValue()
{
    return this->value;
}

void Matrix::setRawValue(QVector< QVector<double> > newValue)
{
    this->value = newValue;
    //Update matrix size
    this->setM(this->getM());
    this->setN(this->getN());
}

void Matrix::setValue(QString newValue)
{

    //Remove []
    newValue.remove('[');
    newValue.remove(']');

    //Parse matrix format a;b!c;d
    QStringList rows = newValue.split(QRegExp("[!\\|]"));
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
            Parser parser(cols[j]);
            Calculable &colVal = *(parser.run());

            //Errors
            if(colVal.getType() != T_SCALAR)
            {
                throw std::runtime_error("Only scalar types can be inside matrix not " + colVal.getTypeStr() + " (=" + colVal.getValue().toStdString() + ")");

            }
            else if(colVal.getValue() == NULL)
                throw std::runtime_error("Unknown error happend during matrix computation");

            //insert value
            this->setCell(i, j, dynamic_cast<Scalar&>(colVal).getRawValue());

        }
    }
}

void Matrix::setValue(Matrix *A)
{
    this->setM(A->getM());
    this->setN(A->getN());
    this->setRawValue(A->getRawValue());
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
    else if(a.getType() == T_SCALAR)
    {
        Scalar& a2 = dynamic_cast<Scalar&>(a);
        Matrix *out = new Matrix();

        //Set new matrix size
        out->setM(this->getM());
        out->setN(this->getN());

        //set values
        for(int i=0; i < out->getM(); i++)
        {
            for(int j=0; j < out->getN() ; j++)
            {
                out->setCell(i, j, this->getCell(i, j) * a2.getRawValue());
            }
        }
        return out;
    }
    else
    {
        throw std::runtime_error("Cannot use the operator * between a " + a.getTypeStr() + " and a " + this->getTypeStr());
    }
    return NULL;
}

Calculable* Matrix::operator+(Calculable &a)
{
    if(this->getType() == a.getType())
    {
        Matrix& a2 = dynamic_cast<Matrix&>(a);
        Matrix *out = new Matrix();

        //Set new matrix size
        if(this->getM() == a2.getM() && this->getN() == a2.getN())
        {
            out->setM(this->getM());
            out->setN(this->getN());
        }
        else
        {
            throw std::runtime_error("Cannot sum a matrix "
                                     + QString::number(a2.getM()).toStdString() + "x" + QString::number(a2.getN()).toStdString()
                                     + " with a matrix "
                                     + QString::number(this->getM()).toStdString() + "x" + QString::number(this->getN()).toStdString());
        }

        //set values
        for(int i=0; i < out->getM(); i++)
        {
            for(int j=0; j < out->getN() ; j++)
            {
                out->setCell(i, j, this->getCell(i, j) + a2.getCell(i, j));
            }
        }
        return out;
    }
    else
    {
        throw std::runtime_error("Cannot use the operator + between a " + a.getTypeStr() + " and a " + this->getTypeStr());
    }
    return NULL;
}

Calculable* Matrix::operator-(Calculable &a)
{
    if(this->getType() == a.getType())
    {
        Matrix& a2 = dynamic_cast<Matrix&>(a);
        Matrix *out = new Matrix();

        //Set new matrix size
        if(this->getM() == a2.getM() && this->getN() == a2.getN())
        {
            out->setM(this->getM());
            out->setN(this->getN());
        }
        else
        {
            throw std::runtime_error("Cannot sum a matrix "
                                     + QString::number(a2.getM()).toStdString() + "x" + QString::number(a2.getN()).toStdString()
                                     + " with a matrix "
                                     + QString::number(this->getM()).toStdString() + "x" + QString::number(this->getN()).toStdString());
        }

        //set values
        for(int i=0; i < out->getM(); i++)
        {
            for(int j=0; j < out->getN() ; j++)
            {
                out->setCell(i, j, a2.getCell(i, j) - this->getCell(i, j));
            }
        }
        return out;
    }
    else
    {
        throw std::runtime_error("Cannot use the operator - between a " + a.getTypeStr() + " and a " + this->getTypeStr());
    }
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

std::string Matrix::getTypeStr()
{
    return "matrix";
}

TokenKind Matrix::getType()
{
    return T_MATRIX;
}
