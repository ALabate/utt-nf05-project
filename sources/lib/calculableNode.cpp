#include "calculableNode.h"


/**
 * @brief Constructor
 * 
 * @param value a pointer to the Calculable
 */

CalculableNode::CalculableNode(Calculable *value)
{
    this->value = value;
}


/**
 * @brief Execute the node
 * 
 * @return a Calculable pointer
 */

Calculable* CalculableNode::execute()
{
    return this->value;
}


/**
 * @brief toString method
 * 
 * @return a QString representation of the Node
 */

QString CalculableNode::toString() const
{
    return "Calculable node value: " + this->value->toString();
}
