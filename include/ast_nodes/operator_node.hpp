#pragma once
#include <string>

#include "expression_node.hpp"

namespace deq {
	namespace ast {
		struct Operator : public Expression {
			std::string op;
			Expression* left;
			Expression* right;

			Operator(Expression* left, Expression* right, std::string op);
			~Operator();
		};
	}
}