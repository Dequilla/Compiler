#pragma once
#include "node.hpp"

namespace deq {
	namespace ast {
		struct ExpressionNode : public Node {
			ExpressionNode(Node::Type type) : Node(type) {};
		};
	}
}