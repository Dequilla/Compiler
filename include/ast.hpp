#pragma once
#include <string>
#include <memory>
#include <utility>
#include <vector>
#include <type_traits>
#include <iostream>

#include "typing.hpp"
#include "lexer.hpp"

#include "ast_nodes/node.hpp"
#include "ast_nodes/expression_node.hpp"

#include "ast_nodes/vardecl_node.hpp"
#include "ast_nodes/assign_node.hpp"
#include "ast_nodes/literal_node.hpp"
#include "ast_nodes/operator_node.hpp"
#include "ast_nodes/statements_node.hpp"

namespace deq {
	namespace ast {
		class AstTree {
		protected:
			std::shared_ptr<Statements> m_root;

			AstTree();

		public:
			std::shared_ptr<Statements> getRoot();

			friend class AstBuilder;
		};

		class AstBuilder {
			std::vector<deq::Token> m_tokens;

			Node* checkVarDeclare(unsigned long& index);
			Node* checkAssignExpression(unsigned long& index);
			Node* checkOperatorExpression(unsigned long& index);

		public:
			AstBuilder(std::vector<deq::Token> tokens);

			Node* interpret(unsigned long& index);

			AstTree build();
		};
	}
}