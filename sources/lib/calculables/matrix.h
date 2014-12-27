#ifndef MATRIX_H
#define MATRIX_H

#include <QList>
#include "../calculable.h"

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


//    /**
//     * @brief value setter
//     *
//     * @param newValue the value to set
//     */
//    void setValue(QString newValue);



    /**
     * @brief Define the type of the element
     */
    std::string getType() const;

protected:
   QList<QList<double> > value;
};

#endif // MATRIX_H
