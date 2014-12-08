#include "varNode.h"


VarNode::VarNode(QString varName, Calculable* value)
{
    this->varName = varName;
    this->value = value;
}


VarNode::~VarNode() {}


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


Calculable* VarNode::execute()
{
    if (this->value != NULL)
    {
        return this->value;
    }
    return NULL;
}


QString VarNode::toString() const
{
    return "VarNode name: " + this->getName() + " value: " + this->getValue()->toString();
}


void VarNode::setValue(Calculable *value)
{
    this->value = value;
}


Calculable* VarNode::getValue() const
{
    return this->value;
}


QString VarNode::getName() const
{
    return this->varName;
}
