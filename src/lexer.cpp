#include "../include/lexer.hpp"

deq::Token::Token(Type type, std::string value) 
	: type(type), value(value)
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
			index += keyword.size();
			return Token(
				Token::KEYWORD,
				keyword
			);
		}
	}

	return Token();
}

deq::Token deq::Lexer::interpret(unsigned long& index) {
	Token token = checkKeywords(index);
	if (token.type != Token::UNKNOWN) {
		return token;
	}

	return token;
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