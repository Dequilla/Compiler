#include "ast.hpp"

std::unique_ptr<deq::ast::Node> deq::ast::AstBuilder::checkVarDeclare(unsigned long& index) {
	if(index + 1 >= m_tokens.size()) return std::make_unique<Node>();

	if (
		m_tokens[index].type == Token::KEYWORD &&
		deq::typing::isValidType(m_tokens[index].value) &&
		m_tokens[index + 1].type == Token::IDENTIFIER
	) {
		return std::make_unique<VarDeclareNode>(
			typing::fromString(m_tokens[index].value), m_tokens[index + 1].value
		);
	}

	// TODO: error
	return std::make_unique<Node>();
}

std::unique_ptr<deq::ast::Node> deq::ast::AstBuilder::checkAssignExpression(unsigned long& index) {
	if (
		index + 1 >= m_tokens.size() &&
		index - 1 > 0
	) return std::make_unique<Node>();

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
		std::unique_ptr<Node> expr = std::move(interpret(i));

		return std::make_unique<AssignNode>(
			m_tokens[index - 1].value,
			std::make_unique<ExpressionNode>(std::move(expr))
		);
	}

	return std::make_unique<Node>();
}


deq::ast::AstBuilder::AstBuilder(std::vector<deq::Token> tokens) {
	m_tokens = tokens;
}

std::unique_ptr<deq::ast::Node> deq::ast::AstBuilder::interpret(unsigned long& index) {
	std::unique_ptr<Node> statement = checkVarDeclare(index);
	if (statement->type != Node::UNKNOWN) {
		return statement;
	}

	statement = checkAssignExpression(index);
	if (statement->type != Node::UNKNOWN) {
		return statement;
	}

	return std::make_unique<Node>();
}

deq::ast::StatementsNode deq::ast::AstBuilder::run() {
	StatementsNode root;
	
	for (unsigned long index = 0; index < m_tokens.size(); index++) {
		std::unique_ptr<Node> statement = interpret(index);
		if (statement->type != Node::UNKNOWN) 
			root.statements.push_back(std::move(statement));
	}

	return root;
}