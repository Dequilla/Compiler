#include "ast_nodes/operator_node.hpp"

deq::ast::OperatorNode::OperatorNode(ExpressionNode* left, ExpressionNode* right, std::string op)
	: ExpressionNode(Node::OP_EXPR),
	left(left),
	right(right),
	op(op)
{};

deq::ast::OperatorNode::~OperatorNode() {
	delete left;
	delete right;
}