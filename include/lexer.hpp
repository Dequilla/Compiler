#pragma once
#include <string>
#include <vector>

namespace deq {
	struct Token {
		enum Type {
			UNKNOWN,

			KEYWORD,
			
			LPARAN,
			RPARAN,
			LCURL_BRACE,
			RCURL_BRACE,
			LSQ_BRACE,
			RSQ_BRACE,
			
			DOT,

			ASSIGN,
			OPERATOR,
			
			IDENTIFIER,
			STR_LITERAL,
			NUM_LITERAL,

			LAST
		};

		Type type;
		std::string value;

		unsigned long position; 

		Token(Type type = Token::UNKNOWN, std::string value = "", unsigned long position = 0);
	};

	class Lexer {
		std::string m_source;

		Token checkKeywords(unsigned long& index);
		Token checkDividers(unsigned long& index);
		Token checkIdentifiers(unsigned long& index);
		Token checkStringLiterals(unsigned long& index);
		Token checkNumberLiterals(unsigned long& index);

	public:
		Lexer(std::string source);

		Token interpret(unsigned long& index);

		std::vector<Token> run();
	};
}