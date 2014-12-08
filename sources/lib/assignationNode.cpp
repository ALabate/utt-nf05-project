#include "assignationNode.h"


/**
 * @brief Constructor
 * @param variable reference to the VarNode to set
 * @param expression reference to the expression to execute
 */  
   
AssignationNode::AssignationNode(VarNode *variable, ExpressionNode *expression)
{
    this->variable = variable;
    this->expression = expression;
}


/**
 * @brief Put expression value in memory as varName 
 * @return expression value
 */

Calculable* AssignationNode::execute()
{
    Calculable *value = this->expression->execute();
    this->variable->setValue(value);

    return value;
}


/**
 * @brief variable Node accessor
 * @return a pointer to the variable Node associated to this assocation Node
 */

VarNode* AssignationNode::getVariable() const
{
    return this->variable;
}


/**
 * @brief expression Node accessor
 * @return a pointer to the expression Node associated to this association Node
 */

ExpressionNode* AssignationNode::getExpression() const
{
    return this->expression;
}


/**
 * @brief toString method
 * 
 * @return a QString representation of the Node
 */

QString AssignationNode::toString() const
{
    return "VarNode name: " + this->getVariable()->toString() + " value: " + this->getExpression()->toString();
}
