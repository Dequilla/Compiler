#pragma once
#include <string>

#include "expression_node.hpp"

namespace deq {
	namespace ast {
		struct LiteralNode : public ExpressionNode {
			std::string value;

			LiteralNode(std::string value)
				: ExpressionNode(Node::LIT_EXPR),
				value(value)
			{};
		};
	}
}