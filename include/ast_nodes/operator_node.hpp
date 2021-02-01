#pragma once
#include <string>

#include "expression_node.hpp"

namespace deq {
	namespace ast {
		struct OperatorNode : public ExpressionNode {
			std::string op;
			ExpressionNode* left;
			ExpressionNode* right;

			OperatorNode(ExpressionNode* left, ExpressionNode* right, std::string op);
			~OperatorNode();
		};
	}
}