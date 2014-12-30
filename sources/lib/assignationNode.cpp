#include "assignationNode.h"


AssignationNode::AssignationNode(VarNode *variable, ExpressionNode *expression)
{
    this->variable = variable;
    this->expression = expression;
}


AssignationNode::~AssignationNode() {
    // delete this->variable;
    delete this->expression;
}


Calculable* AssignationNode::execute()
{
    Calculable *value = this->expression->execute();
    this->variable->setValue(value);

    return value;
}


VarNode* AssignationNode::getVariable() const
{
    return this->variable;
}


ExpressionNode* AssignationNode::getExpression() const
{
    return this->expression;
}

QString AssignationNode::toString() const
{
    return "VarNode name: " + this->getVariable()->toString() + " value: " + this->getExpression()->toString();
}


