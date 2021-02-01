#include "ast_nodes/vardecl_node.hpp"

deq::ast::VarDeclareNode::VarDeclareNode(typing::Type varType, std::string name)
	: Node(Node::DECL_VAR),
	varType(varType),
	name(name)
{};