#include "matrixlib.h"

Matrix *MatrixLib::identity(int n)
{
    Matrix *out = new Matrix();
    out->setM(n);
    out->setN(n);
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(i == j)
                out->setCell(i, j, 1);
            else
                out->setCell(i, j, 0);
        }
    }
    return out;
}

Scalar *MatrixLib::cofactor(Matrix *source, int i, int j)
{
    //Checks
    if(source->getM() < 1)
        throw std::runtime_error("Cannot calculate determinant of an empty matrix");
    if(source->getM() != source->getN())
        throw std::runtime_error("Cannot calculate cofactor of a non-sqare matrix");


    //Generate submatrix without line i and column j
    Matrix *sub = new Matrix();
    sub->setM(source->getM()-1);
    sub->setN(source->getN()-1);
    for(int i_set=0; i_set<sub->getM(); i_set++)
    {
        for(int j_set=0; j_set<sub->getN(); j_set++)
        {
            int i_get = i_set, j_get = j_set;
            if(i_set >= i)
                i_get++;
            if(j_set >= j)
                j_get++;

            sub->setCell(i_set, j_set, source->getCell(i_get, j_get));
        }
    }

    //Calculate sign
    int sign = 1;
    if((i+j)%2 != 0)
        sign = -1;

    //Calculate det of submatrix
    Scalar *out = MatrixLib::determinant(sub);
    out->setRawValue(out->getRawValue() * sign);
    return out;
}

Scalar *MatrixLib::determinant(Matrix *source)
{

    //Checks
    if(source->getM() < 1)
        throw std::runtime_error("Cannot calculate determinant of an empty matrix");
    else if(source->getM() != source->getN())
        throw std::runtime_error("Cannot calculate determinant of a non-sqare matrix");

    //Check if case need recursivity
    if(source->getM() == 1)
    {
        return new Scalar(source->getCell(0,0));
    }
    else if(source->getM() == 2)
    {

        return new Scalar(source->getCell(0,0)*source->getCell(1,1) - source->getCell(0,1)*source->getCell(1,0));
    }
    else
    {
        //sum of cofactors of the first column
        double out = 0;
        for(int i=0; i<source->getM(); i++)
        {
            out += source->getCell(i,0)*MatrixLib::cofactor(source, i, 0)->getRawValue();
        }
        return new Scalar(out);
    }
}

Matrix *MatrixLib::transpose(Matrix *source)
{

    //Checks
    if(source->getM() < 1 || source->getN() < 1)
        throw std::runtime_error("Cannot transpose an empty matrix");

    //transpose
    Matrix *out = new Matrix();
    out->setM(source->getN());
    out->setN(source->getM());
    for(int i=0; i<source->getM(); i++)
    {
        for(int j=0; j<source->getN(); j++)
        {
            out->setCell(j, i, source->getCell(i, j));
        }
    }
    return out;
}

Matrix *MatrixLib::coMatrix(Matrix *source)
{

    //Checks
    if(source->getM() < 1 || source->getN() < 1)
        throw std::runtime_error("Cannot find cofactor matrix of an empty matrix");

    //Adjugate matrix calculation
    Matrix *out = new Matrix();
    out->setM(source->getN());
    out->setN(source->getM());
    for(int i=0; i<source->getM(); i++)
    {
        for(int j=0; j<source->getN(); j++)
        {
            out->setCell(i, j, cofactor(source, i, j)->getRawValue());
        }
    }
    return out;
}

Matrix *MatrixLib::inv(Matrix *source)
{
    //Checks
    if(source->getM() < 1)
        throw std::runtime_error("Cannot calculate determinant of an empty matrix");
    else if(source->getM() != source->getN())
        throw std::runtime_error("Cannot calculate determinant of a non-sqare matrix");

    //Det and check if invertible
    double det = MatrixLib::determinant(source)->getRawValue();
    if(det == 0)
        throw std::runtime_error("Matrix not invertible because determinant is 0");

    Matrix *out = new Matrix();
    out->setM(source->getM());
    out->setN(source->getN());

    Scalar* scal = new Scalar(1.0/det);
    out->setValue(dynamic_cast<Matrix*>(*transpose(coMatrix(source))*(*scal)));
    return out;

}

double MatrixLib::trace(Matrix *source)
{

    //Checks
    if(source->getM() < 1)
        throw std::runtime_error("Cannot calculate trace of an empty matrix");
    else if(source->getM() != source->getN())
        throw std::runtime_error("Cannot calculate trace of a non-sqare matrix");

    //Calculate
    double out = 0;
    for(int i=0; i<source->getM(); i++)
    {
        out += source->getCell(i,i);
    }
    return out;
}

double MatrixLib::norm(Matrix *source)
{

    //Checks
    if(source->getM() < 1 || source->getN() < 1)
        throw std::runtime_error("Cannot calculate norm of an empty matrix");
    else if(source->getM() != 1 && source->getN() != 1)
        throw std::runtime_error("Can only calculate norm of column matrix and row matrix");
    //Calculate
    double sum = 0;
    if(source->getM() == 1)//row matrix
    {
        for(int j=0; j<source->getN(); j++)
            sum += source->getCell(0, j)*source->getCell(0, j);
    }
    else//column matrix
    {
        for(int i=0; i<source->getM(); i++)
            sum += source->getCell(i, 0)*source->getCell(i, 0);
    }
    return sqrt(sum);
}
