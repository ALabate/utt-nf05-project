#include "varNode.h"


VarNode::VarNode(QString varName, Calculable* value)
{
    this->varName = varName;
    this->value = value;
}


VarNode::~VarNode() {}


VarNode* VarNode::getVar(QString reference)
{
    foreach (VarNode *node, *(VarNode::getRegistry()))
    {
        if (node->getName() == reference)
        {
            return node;
        }
    }

    VarNode *newNode = new VarNode(reference, NULL);
    VarNode::getRegistry()->append(newNode);
    return newNode;
}


QList<VarNode *>* VarNode::getRegistry()
{
    return VarNode::registry;
}


QList<VarNode *>* VarNode::initializeRegistry()
{
    return new QList<VarNode *>();
}

QList<VarNode *>* VarNode::registry = VarNode::initializeRegistry();


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
