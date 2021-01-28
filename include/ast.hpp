#pragma once
#include <string>
#include <memory>

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
				DECL_VAR
			};

			Type type;
		};

		struct ExpressionNode : public Node {
		};

		struct OperatorNode : public ExpressionNode {
			std::string op;
			std::unique_ptr<ExpressionNode> left;
			std::unique_ptr<ExpressionNode> right;
		};

		struct LiteralNode : public ExpressionNode {
			std::string value;
		};

		struct AssignNode : public Node {
			std::string name;
			std::unique_ptr<ExpressionNode> value;
		};

		struct VarDeclareNode : public Node 
			VarType type;
			std::string name;
		};
	}
}