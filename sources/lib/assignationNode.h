#ifndef ASSIGNATIONNODE_H
#define ASSIGNATIONNODE_H

#include <QDebug>
#include <QString>
#include <QList>
#include <QMap>

#include "lib/node.h"
#include "lib/varNode.h"
#include "lib/expressionNode.h"
#include "lib/token.h"

class ExpressionNode;
class VarNode;

class AssignationNode : public Node
{
    public:

    /**
     * @brief constructor
     *
     * @param variable VarNode to set
     * @param expression expression to execute
     */
    AssignationNode(VarNode *variable, ExpressionNode *expression);

    /**
     * @brief destructor
     */
    ~AssignationNode();

    /**
     * @brief put expression value in memory as varName
     * @return expression value
     */
    virtual Calculable* execute();

    /**
     * @brief variable Node accessor
     *
     * @return a pointer to the variable Node associated to this assocation Node
     */
    VarNode* getVariable() const;

    /**
     * @brief expression Node accessor
     * @return a pointer to the expression Node associated to this association Node
     */
    ExpressionNode* getExpression() const;

    /**
     * @brief toString method
     *
     * @return a QString representation of the Node
     */
    virtual QString toString() const;


    protected:
        VarNode *variable;
        ExpressionNode *expression;
};

#endif // ASSIGNATIONNODE_H
