#pragma once
#include <string>

#include "node.hpp"
#include "../typing.hpp"

namespace deq {
	namespace ast {
		struct VarDeclareNode : public Node {
			typing::Type varType;
			std::string name;

			VarDeclareNode(typing::Type varType, std::string name);
		};
	}
}