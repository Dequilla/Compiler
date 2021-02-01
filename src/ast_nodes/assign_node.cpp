#include "ast_nodes/assign_node.hpp"

deq::ast::VariableAssignment::VariableAssignment(std::string name, Expression* value)
	: Expression(Node::ASS_EXPR),
	name(name),
	value(value)
{};

deq::ast::VariableAssignment::~VariableAssignment() {
	delete value;
}