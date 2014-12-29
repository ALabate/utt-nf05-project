#ifndef MATRIX_H
#define MATRIX_H

#include <QList>
#include <QStringList>
#include <stdexcept>
#include <QGenericMatrix>
#include "../calculable.h"
#include "../parser.h"

class Matrix : public Calculable
{

public:

    /**
     * @brief constructor
     *
     * @param value - the string value
     */
    Matrix(QString value);

    /**
     * @brief Construct a matrix of one per one with the value 0
     */
    Matrix();

    /**
     * @brief value accessor
     *
     * @return the value of the Calculable
     */
    QString getValue();

   /**
    * @brief value setter
    *
    * @param newValue the value to set
    */
   void setValue(QString newValue);

    /**
     * @brief overload operator * between two Calculable
     *
     * @param a a Calculable
     * @return a Calculable
     */
    Calculable* operator*(Calculable &a);

    /**
     * @brief overload operator / between two Calculable
     *
     * @param a a Calculable
     * @return a Calculable
     */
    Calculable* operator/(Calculable &a);

    /**
     * @brief overload operator - between two Calculable
     *
     * @param a a Calculable
     * @return a Calculable
     */
    Calculable* operator+(Calculable &a);

    /**
     * @brief overload operator + between two Calculable
     *
     * @param a a Calculable
     * @return a Calculable
     */
    Calculable* operator-(Calculable &a);


    /**
     * @brief Define the type of the element
     */
    std::string getType();


    /**
     * @brief Get the number of rows of the matrix
     *
     * @return The number of rows
     */
    int getM();
    /**
     * @brief Get the number of columns of the matrix
     *
     * @return The number of columns
     */
    int getN();
    /**
     * @brief Set the number of rows of the matrix
     *
     * @param The new number of rows.
     */
    void setM(int M);
    /**
     * @brief Set the number of columns of the matrix
     *
     * @param The new number of columns.
     */
    void setN(int N);

    /**
     * @brief Get the raw value of cellule
     *
     * @param i - The row of the cell between 0 and M-1
     * @param j - The row of the cell between 0 and N-1
     * @return The raw value of the cellule
     */
    double getCell(const int i, const int j);

    /**
     * @brief Set the raw value of cellule
     *
     * @param i - The row of the cell between 0 and M-1
     * @param j - The row of the cell between 0 and N-1
     * @param value - The new raw value of the cellule
     */
    void setCell(const int i, const int j, const double value);

protected:
    /**
     * @brief Handle the matrix raw value
     */
    QVector< QVector<double> > value;

    /**
     * @brief Give the number of rows of the matrix
     */
    int M;

    /**
     * @brief Give the number of columns of the matrix
     */
    int N;
};

#endif // MATRIX_H
