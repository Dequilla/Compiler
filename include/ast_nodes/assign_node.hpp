#pragma once
#include <string>

#include "expression_node.hpp"

namespace deq {
	namespace ast {
		struct VariableAssignment : public Expression {
			std::string name;
			Expression* value;

			VariableAssignment(std::string name, Expression* value);
			~VariableAssignment();
		};
	}
}