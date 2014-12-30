#include "lib/operator.h"


Operator::Operator(int precedence, Associativity associativity)
{
    this->precedence = precedence;
    this->associativity = associativity;
}


Operator::~Operator()
{
}


int Operator::getPrecedence()
{
    return this->precedence;
}


Associativity Operator::getAssociativity()
{
    return this->associativity;
}


QMap<int, Operator*> Operator::initializeOperators()
{
    QMap<int, Operator*> operators;

    operators.insert(T_SUM, new Operator(1, LEFT_ASSOC));
    operators.insert(T_SUB, new Operator(1, LEFT_ASSOC));
    operators.insert(T_MULTIPLY, new Operator(5, LEFT_ASSOC));
    operators.insert(T_DIVIDE, new Operator(5, LEFT_ASSOC));
    operators.insert(T_MODULO, new Operator(5, LEFT_ASSOC));
    operators.insert(T_POW, new Operator(10, LEFT_ASSOC));

    return operators;
}


bool Operator::isOperator(Token token)
{
    return operators.keys().contains(token.getKind());
}


QMap<int, Operator*> Operator::operators = Operator::initializeOperators();
