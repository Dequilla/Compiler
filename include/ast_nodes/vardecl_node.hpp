#pragma once
#include <string>

#include "node.hpp"
#include "../typing.hpp"

namespace deq {
	namespace ast {
		struct VariableDeclaration : public Node {
			typing::Type varType;
			std::string name;

			VariableDeclaration(typing::Type varType, std::string name);
		};
	}
}