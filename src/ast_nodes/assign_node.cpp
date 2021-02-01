#include "ast_nodes/assign_node.hpp"

deq::ast::AssignNode::AssignNode(std::string name, ExpressionNode* value)
	: ExpressionNode(Node::ASS_EXPR),
	name(name),
	value(value)
{};

deq::ast::AssignNode::~AssignNode() {
	delete value;
}