#pragma once

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

			Node(deq::ast::Node::Type type)
				: type(type) {};
		};
	}
}