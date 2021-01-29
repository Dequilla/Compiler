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

			Node(Type type = Type::UNKNOWN) : type(type) {};
		};

		struct StatementsNode : public Node {
			std::vector<std::unique_ptr<Node>> statements;

			StatementsNode(std::vector<std::unique_ptr<Node>>& stmts = std::vector<std::unique_ptr<Node>>())
				:	Node(Node::STATEMENTS)
			{
				for (auto& node : stmts) {
					statements.push_back(std::move(node));
				}
			}
		};

		struct ExpressionNode : public Node {
			ExpressionNode(Node::Type type) : Node(type) {};
		};

		struct OperatorNode : public ExpressionNode {
			std::string op;
			std::unique_ptr<ExpressionNode> left;
			std::unique_ptr<ExpressionNode> right;

			OperatorNode(std::unique_ptr<ExpressionNode> left, std::unique_ptr<ExpressionNode> right, std::string op) 
				:	ExpressionNode(Node::OP_EXPR), 
					left(std::move(left)),
					right(std::move(right)),
					op(op)
				{};
		};

		struct LiteralNode : public ExpressionNode {
			std::string value;

			LiteralNode(std::string value)
				:	ExpressionNode(Node::LIT_EXPR),
					value(value)
				{};
		};

		struct AssignNode : public ExpressionNode {
			std::string name;
			std::unique_ptr<ExpressionNode> value;

			AssignNode(std::string name, std::unique_ptr<ExpressionNode> value)
				:	ExpressionNode(Node::ASS_EXPR),
					name(name),
					value(std::move(value))
				{};
		};

		struct VarDeclareNode : public Node {
			typing::Type varType;
			std::string name;

			VarDeclareNode(typing::Type varType, std::string name)
				:	Node(Node::DECL_VAR),
					varType(varType),
					name(name)
				{};
		};

		class AstBuilder {
			std::vector<deq::Token> m_tokens;

			std::unique_ptr<Node> checkVarDeclare(unsigned long& index);
			std::unique_ptr<Node> checkAssignExpression(unsigned long& index);

		public:
			AstBuilder(std::vector<deq::Token> tokens);

			std::unique_ptr<Node> interpret(unsigned long& index);

			StatementsNode run();
		};
	}
}