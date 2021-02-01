#pragma once
#include <string>
#include <memory>
#include <utility>
#include <vector>
#include <type_traits>
#include <iostream>

#include "typing.hpp"
#include "lexer.hpp"

namespace deq {
	namespace ast {
		struct Node {
			enum Type {
				UNKNOWN,

				DECL_VAR,
				STATEMENTS,

				OP_EXPR,
				LIT_EXPR,
				ASS_EXPR
			};

			Type type;

			Node(Type type = Type::UNKNOWN);
		};

		struct StatementsNode : public Node {
			std::vector<Node*> statements;

			StatementsNode(std::vector<Node*>& stmts = std::vector<Node*>());
			~StatementsNode();
		};

		struct ExpressionNode : public Node {
			ExpressionNode(Node::Type type);
		};

		struct OperatorNode : public ExpressionNode {
			std::string op;
			ExpressionNode* left;
			ExpressionNode* right;

			OperatorNode(ExpressionNode* left, ExpressionNode* right, std::string op);
			~OperatorNode();
		};

		struct LiteralNode : public ExpressionNode {
			std::string value;

			LiteralNode(std::string value);
		};

		struct AssignNode : public ExpressionNode {
			std::string name;
			ExpressionNode* value;

			AssignNode(std::string name, ExpressionNode* value);
			~AssignNode();
		};

		struct VarDeclareNode : public Node {
			typing::Type varType;
			std::string name;

			VarDeclareNode(typing::Type varType, std::string name);
		};

		class AstBuilder {
			std::vector<deq::Token> m_tokens;

			Node* checkVarDeclare(unsigned long& index);
			Node* checkAssignExpression(unsigned long& index);
			Node* checkOperatorExpression(unsigned long& index);

		public:
			AstBuilder(std::vector<deq::Token> tokens);

			Node* interpret(unsigned long& index);

			StatementsNode* build();
		};
	}
}