#pragma once
#include <vector>

#include "node.hpp"

namespace deq {
	namespace ast {
		
		struct StatementsNode : public Node {
			std::vector<Node*> statements;

			StatementsNode(std::vector<Node*>& stmts = std::vector<Node*>())
				: Node(Node::STATEMENTS)
			{
				for (auto& node : stmts) {
					statements.push_back(node);
				}
			};

			~StatementsNode() {
				for (auto& node : statements) {
					delete node;
				}
			};
		};

	}
}