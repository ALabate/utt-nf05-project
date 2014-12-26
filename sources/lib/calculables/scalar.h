#ifndef SCALAR_H
#define SCALAR_H

#include "../calculable.h"

class Scalar : public Calculable
{
public:

    //Inherit constructor
//    using Calculable::Calculable;

    /**
     * @brief constructor
     *
     * @param value - the string value
     */
    Scalar(QString value);

    /**
     * @brief constructor
     *
     * @param value the raw value
     */
    Scalar(double value);


    /**
     * @brief value accessor
     *
     * @return the value of the Calculable
     */
    virtual QString getValue() const;

    /**
     * @brief value accessor
     *
     * @return the raw value of the Calculable
     */
    virtual double getRawValue() const;

    /**
     * @brief value setter
     *
     * @param newValue the value to set
     */
    virtual void setValue(QString newValue);
    /**
     * @brief value setter
     *
     * @param newValue the value to set
     */
    virtual void setRawValue(double newValue);

    /**
     * @brief overload operator * between two Calculable
     *
     * @param a a Calculable
     * @return a Calculable
     */
    virtual Calculable* operator*(Calculable const &a);

    /**
     * @brief overload operator / between two Calculable
     *
     * @param a a Calculable
     * @return a Calculable
     */
    virtual Calculable* operator/(Calculable const &a);

    /**
     * @brief overload operator - between two Calculable
     *
     * @param a a Calculable
     * @return a Calculable
     */
    virtual Calculable* operator+(Calculable const &a);

    /**
     * @brief overload operator + between two Calculable
     *
     * @param a a Calculable
     * @return a Calculable
     */
    virtual Calculable* operator-(Calculable const &a);



    /**
     * @brief Define the type of the element
     */
    std::string getType() const;

protected:
    double value;
};

#endif // SCALAR_H
