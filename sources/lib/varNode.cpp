#include "varNode.h"


/**
 * @brief Constructor
 * 
 * @param varName QString of the varName
 * @param registry Map containing memory
 */  
   
VarNode::VarNode(QString varName, Calculable* value)
: Node()
{
    this->varName = varName;
    this->value = value;
}


/**
 * @brief Execute the node
 * 
 * @return a Calculable pointer
 */

Calculable* VarNode::execute()
{
    if (this->value != NULL)
    {
        return this->value;
    }

    return NULL;
}


/**
 * @brief Set a value in the registry
 * 
 * @param value Calculable to set
 */

void VarNode::setValue(Calculable *value)
{
    this->value = value;
}


/**
 * @brief value accessor
 * @return a pointer to the node's value
 */

Calculable* VarNode::getValue() const
{
    return this->value;
}


/**
 * @brief varName accessor
 * @return the var name
 */

QString VarNode::getName() const
{
    return this->varName;
}


/**
 * @brief toString method
 * @return a QString representation of the Node
 */

QString VarNode::toString() const
{
    return "VarNode name: " + this->getName() + " value: " + this->getValue()->toString();
}


VarNode* VarNode::getVar(QString reference, QList<VarNode *> *registry)
{
    foreach (VarNode *node, *(registry))
    {
        if (node->getName() == reference)
        {
            return node;
        }
    }

    VarNode *newNode = new VarNode(reference, NULL);
    registry->append(newNode);

    return newNode;
}
