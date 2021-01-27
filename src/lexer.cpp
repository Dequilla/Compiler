#include "../include/lexer.hpp"

deq::Token::Token(Type type, std::string value, unsigned long position)
	: type(type), value(value), position(position)
{
	
}

deq::Lexer::Lexer(std::string source)
	: m_source(source)
{
}

deq::Token deq::Lexer::checkKeywords(unsigned long& index) {
	std::string keywords[] = {
		"fn",
		"scope",
		"type",
		"returns",
		"return"
	};

	for (auto& keyword : keywords) {
		bool isSame = true;

		for (unsigned long i = 0; index + i < this->m_source.size() && i < keyword.size(); i++) {
			if (keyword[i] != this->m_source[index + i]) {
				isSame = false;
				break;
			}
		}

		if (isSame) {
			Token token = Token(
				Token::KEYWORD,
				keyword,
				index
			);
			index += keyword.size() - 1;
			return token;
		}
	}

	return Token();
}

deq::Token deq::Lexer::checkDividers(unsigned long& index) {
	switch (this->m_source.at(index))
	{
	case '{':
		return Token(
			Token::BRACE,
			"{",
			index
		);
	case '}':
		return Token(
			Token::BRACE,
			"}",
			index
		);

	case '(':
		return Token(
			Token::PARAN,
			"(",
			index
		);
	case ')':
		return Token(
			Token::PARAN,
			")",
			index
		);

	case '.':
		return Token(
			Token::DOT,
			".",
			index
		);

	case '=':
		if (this->m_source.size() > index + 1 && this->m_source.at(index + 1) == '=') return Token();

		index += 1;
		return Token(
			Token::ASSIGN,
			"=",
			index
		);
		
	default: 
		return Token();
	}
}

deq::Token deq::Lexer::checkIdentifiers(unsigned long& index) {
	static const std::string allowed = "_abcdefghijklmonpqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	static const std::string allowedOthers = "0123456789";
	static const unsigned long maxLength = 31;

	unsigned long length = 0;
	for (unsigned long i = 0; i < 31 && i + index < m_source.size(); i++) {
		char c = m_source.at(index + i);

		if (allowed.find(c) != std::string::npos) {
			length += 1;
		}
		else if (i > 0 && allowedOthers.find(c) != std::string::npos) {
			length += 1;
		}
		else break;
	}

	if (length == 0) return Token();
	else {
		Token token = Token(
			Token::IDENTIFIER,
			m_source.substr(index, length),
			index
		);
		index += length - 1;
		return token;
	}
}


deq::Token deq::Lexer::interpret(unsigned long& index) {
	const char c = m_source[index];
	if (c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == '\v' || c == '\f') {
		return Token(); // Effectivly skip
	}

	Token token = checkKeywords(index);
	if (token.type != Token::UNKNOWN) {
		return token;
	}

	token = checkDividers(index);
	if (token.type != Token::UNKNOWN) {
		return token;
	}

	token = checkIdentifiers(index);
	if (token.type != Token::UNKNOWN) {
		return token;
	}

	return Token();
}

std::vector<deq::Token> deq::Lexer::run() {
	std::vector<Token> tokens;
	for (unsigned long index = 0; index < this->m_source.size(); index++) {
		Token token = this->interpret(index);
		if(token.type != Token::UNKNOWN)
			tokens.push_back(token);
	}
	return tokens;
}