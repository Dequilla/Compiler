#include "ast.hpp"

deq::ast::Node::Node(deq::ast::Node::Type type) 
	: type(type) {};

deq::ast::StatementsNode::StatementsNode(std::vector<Node*>& stmts)
	: Node(Node::STATEMENTS)
{
	for (auto& node : stmts) {
		statements.push_back(node);
	}
}

deq::ast::StatementsNode::~StatementsNode() {
	for (auto& node : statements) {
		delete node;
	}
}

deq::ast::ExpressionNode::ExpressionNode(Node::Type type) 
	: Node(type) {};

deq::ast::OperatorNode::OperatorNode(ExpressionNode* left, ExpressionNode* right, std::string op)
	: ExpressionNode(Node::OP_EXPR),
	left(left),
	right(right),
	op(op)
{};

deq::ast::OperatorNode::~OperatorNode() {
	delete left;
	delete right;
}

deq::ast::LiteralNode::LiteralNode(std::string value)
	: ExpressionNode(Node::LIT_EXPR),
	value(value)
{};

deq::ast::AssignNode::AssignNode(std::string name, ExpressionNode* value)
	: ExpressionNode(Node::ASS_EXPR),
	name(name),
	value(value)
{};

deq::ast::AssignNode::~AssignNode() {
	delete value;
}

deq::ast::VarDeclareNode::VarDeclareNode(typing::Type varType, std::string name)
	: Node(Node::DECL_VAR),
	varType(varType),
	name(name)
{};

deq::ast::Node* deq::ast::AstBuilder::checkVarDeclare(unsigned long& index) {
	if(index + 1 >= m_tokens.size()) return nullptr;

	if (
		m_tokens[index].type == Token::KEYWORD &&
		deq::typing::isValidType(m_tokens[index].value) &&
		m_tokens[index + 1].type == Token::IDENTIFIER
	) {
		index += 1;
		return new VarDeclareNode(
			typing::fromString(m_tokens[index - 1].value), m_tokens[index].value
		);
	}

	return nullptr;
}

deq::ast::Node* deq::ast::AstBuilder::checkAssignExpression(unsigned long& index) {
	if (
		index + 1 >= m_tokens.size() &&
		index - 1 <= 0
	) return nullptr;

	if (
		m_tokens[index].type == Token::ASSIGN &&
		m_tokens[index - 1].type == Token::IDENTIFIER &&
		(
			m_tokens[index + 1].type == Token::NUM_LITERAL ||
			m_tokens[index + 1].type == Token::STR_LITERAL ||
			m_tokens[index + 1].type == Token::IDENTIFIER
		)
	) {
		unsigned long i = index + 1; // Nästa token måste identifieras
		Node* expr = interpret(i);
		if (expr == nullptr) expr = new LiteralNode("NULL");

		unsigned long offset = i - index;
		index += offset - 1;

		return new AssignNode(
			m_tokens[index - offset].value,
			static_cast<ExpressionNode*>(expr)
		);
	}

	return nullptr;
}

deq::ast::Node* deq::ast::AstBuilder::checkOperatorExpression(unsigned long& index) {
	const unsigned long ileft = index, iop = index + 1, iright = index +2;
	
	if (
		ileft >= m_tokens.size() &&
		iop >= m_tokens.size() &&
		iright >= m_tokens.size()
	) return nullptr;

	/*if (

		m_tokens[ileft].value = deq::Token::NUM_LITERAL ||
		m_tokens[ileft].value = deq::Token::STR_LITERAL 
	) {

	}*/

	return nullptr;
}

deq::ast::AstBuilder::AstBuilder(std::vector<deq::Token> tokens) {
	m_tokens = tokens;
}

deq::ast::Node* deq::ast::AstBuilder::interpret(unsigned long& index) {
	Node* statement = checkVarDeclare(index);
	if (statement != nullptr) {
		return statement;
	}

	statement = checkAssignExpression(index);
	if (statement != nullptr) {
		return statement;
	}

	statement = checkOperatorExpression(index);
	if (statement != nullptr) {
		return statement;
	}

	return nullptr;
}

deq::ast::StatementsNode* deq::ast::AstBuilder::build() {
	StatementsNode* root = new StatementsNode();
	
	for (unsigned long index = 0; index < m_tokens.size(); index++) {
		Node* statement = interpret(index);
		if (statement != nullptr) 
			root->statements.push_back(statement);
	}

	return root;
}