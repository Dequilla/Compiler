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
		"return",
		"const",
		"ref",

		"bool",

		"byte",
		"int8",
		"int16",
		"int32",
		"int64",
		"uint8",
		"uint16",
		"uint32",
		"uint64",

		"string",
		
		"float",
		"double"
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
			Token::LCURL_BRACE,
			"{",
			index
		);
	case '}':
		return Token(
			Token::RCURL_BRACE,
			"}",
			index
		);

	case '(':
		return Token(
			Token::LPARAN,
			"(",
			index
		);
	case ')':
		return Token(
			Token::RPARAN,
			")",
			index
		);

	case '[':
		return Token(
			Token::LSQ_BRACE,
			"[",
			index
		);
	case ']':
		return Token(
			Token::RSQ_BRACE,
			"]",
			index
		);

	case '.':
		return Token(
			Token::DOT,
			".",
			index
		);

	case '=':
		if (this->m_source.size() > index + 1 && this->m_source.at(index + 1) == '=') {
			index += 1;
			return Token(
				Token::OPERATOR,
				"==",
				index - 1
			);
		}
		else if (index < m_source.size() && m_source[index] == '=') {
			return Token(
				Token::ASSIGN,
				"=",
				index - 1
			);
		}

	case '+':
	case '*':
	case '/':
	case '-':
		if (index >= m_source.size()) return Token();

		return Token(
			Token::OPERATOR,
			std::string(1, m_source[index]),
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

deq::Token deq::Lexer::checkStringLiterals(unsigned long& index) {
	if (m_source[index] != '"') return Token();
	auto second = this->m_source.find_first_of('"', index + 1);

	if (
		second != m_source.npos && 
		second > index
	) {
		auto substring = m_source.substr(index + 1, second - index - 1);
		Token token = Token(
			Token::STR_LITERAL,
			substring,
			index + 1
		);
		index += substring.length();
		return token;
	}

	return Token();
}

deq::Token deq::Lexer::checkNumberLiterals(unsigned long& index) {
	unsigned int numLength = 0;
	for (unsigned int i = 0; i + index < m_source.length(); i++) {
		if(std::string("0123456789").find(m_source[index + i]) != m_source.npos) {
			numLength += 1;
		}
		else if (i > 0 && m_source[index + i] == '.') {
			numLength += 1;
		}
		else {
			break;
		}
	}

	if (numLength > 0) {
		Token token = Token(
			Token::NUM_LITERAL,
			m_source.substr(index, numLength),
			index
		);
		index += numLength;
		return token;
	}

	return Token();
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

	token = checkStringLiterals(index);
	if (token.type != Token::UNKNOWN) {
		return token;
	}

	token = checkNumberLiterals(index);
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