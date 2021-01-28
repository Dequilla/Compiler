#pragma once
#include <string>
#include <memory>
#include <utility>

namespace deq {
	namespace ast {
		enum VarType {
			INT8,
			INT16,
			INT32,
			INT64,

			UINT8,
			UINT16,
			UINT32,
			UINT64,

			BYTE,
			STRING,

			FLOAT,
			DOUBLE,

			BOOL
		};

		struct Node {
			enum Type {
				DECL_VAR,

				OP_EXPR,
				LIT_EXPR,
				ASS_EXPR
			};

			Type type;

			Node(Type type) : type(type) {};
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
			VarType varType;
			std::string name;

			VarDeclareNode(VarType varType, std::string name)
				:	Node(Node::DECL_VAR),
					varType(varType),
					name(name)
				{};
		};
	}
}