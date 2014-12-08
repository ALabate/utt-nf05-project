#include "node.h"


/**
 * @brief Constructor
 *
 * @param children List of Node children
 */

Node::Node()
{
}


/**
 * @brief Pure virtual method. Execute the node depending on its type (use polymorphism)
 * @details [long description]
 * @return [description]
 */

Calculable* Node::execute(){ return NULL; }
