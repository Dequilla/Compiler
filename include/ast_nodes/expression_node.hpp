#pragma once
#include "node.hpp"

namespace deq {
	namespace ast {
		struct Expression : public Node {
			Expression(Node::Type type) : Node(type) {};
		};
	}
}