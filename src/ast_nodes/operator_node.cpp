#include "ast_nodes/operator_node.hpp"

deq::ast::Operator::Operator(Expression* left, Expression* right, std::string op)
	: Expression(Node::OP_EXPR),
	left(left),
	right(right),
	op(op)
{};

deq::ast::Operator::~Operator() {
	delete left;
	delete right;
}