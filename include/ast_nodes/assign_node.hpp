#pragma once
#include <string>

#include "expression_node.hpp"

namespace deq {
	namespace ast {
		struct AssignNode : public ExpressionNode {
			std::string name;
			ExpressionNode* value;

			AssignNode(std::string name, ExpressionNode* value);
			~AssignNode();
		};
	}
}