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

    //Inherit constructor
//    using Calculable::Calculable;

    /**
     * @brief constructor
     *
     * @param value the calculable value
     */
    Matrix(QString value);


    /**
     * @brief value setter
     *
     * @param newValue the value to set
     */
    void setValue(QString newValue);



    /**
     * @brief Define the type of the element
     */
    std::string getType() const;

protected:
    /**
     * @brief Handle the matrix raw value
     */
    QVector< QVector<double>* >* value;
    /**
     * @brief Give the number of rows of the matrix
     */
    int rowCount;

    /**
     * @brief Give the number of columns of the matrix
     */
    int columnCount;
};

#endif // MATRIX_H
