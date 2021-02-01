#pragma once
#include <string>

#include "expression_node.hpp"

namespace deq {
	namespace ast {
		struct Literal : public Expression {
			std::string value;

			Literal(std::string value)
				: Expression(Node::LIT_EXPR),
				value(value)
			{};
		};
	}
}