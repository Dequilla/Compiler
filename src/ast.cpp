#include "ast.hpp"

deq::ast::AstTree::AstTree() {
	m_root = std::make_shared<StatementsNode>();
}

std::shared_ptr<deq::ast::StatementsNode> deq::ast::AstTree::getRoot() {
	return m_root;
}

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
		unsigned long i = index + 1;
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

deq::ast::AstTree deq::ast::AstBuilder::build() {
	AstTree tree;
	
	for (unsigned long index = 0; index < m_tokens.size(); index++) {
		Node* statement = interpret(index);
		if (statement != nullptr) 
			tree.getRoot()->statements.push_back(statement);
	}

	return tree;
}