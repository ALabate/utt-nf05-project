#include "operatorNode.h"


/**
 * @brief Constructor
 * 
 * @param kind kind of operator
 * @param left left Node
 * @param right left right
 */

OperatorNode::OperatorNode(OperatorKind kind, Node *left, Node *right)
{
    if (dynamic_cast<AssignationNode*>(left) || dynamic_cast<AssignationNode*>(right))
    {
        qDebug() << "Error: operator node instancied with an AssignationNode";
    }

    this->kind = kind;
    this->left = left;
    this->right = right;
}


/**
 * @brief Execute the node
 * 
 * @return a Calculable pointer
 */

Calculable* OperatorNode::execute()
{
    Calculable *left = this->left->execute();
    Calculable *right = this->right->execute();

    if (left == NULL || right == NULL)
    {
        return NULL;
    }

    switch(this->kind)
    {
        case O_MULTIPLY:
        {
            Calculable *result = new Calculable(*left * *right);
            return result;
        }


        case O_DIVIDE:
        {
            Calculable *result = new Calculable(*left / *right);
            return result;
        }

        case O_SUM:
        {
            Calculable *result = new Calculable(*left + *right);
            return result;
        }

        case O_SUB:
        {
            Calculable *result = new Calculable(*left - *right);
            return result;
        }
    }
}


/**
 * @brief left node accessor
 *
 * @return a pointer to the left node
 */

Node* OperatorNode::getLeft() const
{
    return this->left;
}


/**
 * @brief right node accessor       
 *
 * @return a pointer to the right node
 */

Node* OperatorNode::getRight() const
{
    return this->right;
}


/**
 * @brief toString method
 * 
 * @return a QString representation of the Node
 */

QString OperatorNode::toString() const
{
    return "OperatorNode left: " + this->getLeft()->toString() + " right: " + this->getRight()->toString();
}
