#pragma once
#include <string>
#include <vector>

namespace deq {
	struct Token {
		enum Type {
			UNKNOWN,

			KEYWORD,
			PARAN,
			BRACE,
			FUNC,
			EXPRESSION,
			IDENTIFIER,
			STR_LITERAL,
			NUM_LITERAL,

			LAST
		};

		Type type;
		std::string value;

		Token(Type type = Token::UNKNOWN, std::string value = "");
	};

	class Lexer {
		std::string m_source;

		Token checkKeywords(unsigned long& index);

	public:
		Lexer(std::string source);

		Token interpret(unsigned long& index);

		std::vector<Token> run();
	};
}