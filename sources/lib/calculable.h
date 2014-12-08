#ifndef CALCULABLE_H
#define CALCULABLE_H

#include <QDebug>


class Calculable
{
    public:
        Calculable(double value);

        double getValue() const;
        QString toString() const;
        void setValue(double newValue);

        Calculable* operator*(Calculable const &a);
        Calculable* operator/(Calculable const &a);
        Calculable* operator+(Calculable const &a);
        Calculable* operator-(Calculable const &a);


    protected:
       double value;
};

#endif // CALCULABLE_H
