#pragma once
#include <vector>

#include "node.hpp"

namespace deq {
	namespace ast {
		
		struct Statements : public Node {
			std::vector<Node*> statements;

			Statements(std::vector<Node*>& stmts = std::vector<Node*>())
				: Node(Node::STATEMENTS)
			{
				for (auto& node : stmts) {
					statements.push_back(node);
				}
			};

			~Statements() {
				for (auto& node : statements) {
					delete node;
				}
			};
		};

	}
}