#include <iostream>
#include <sstream>
#include <fstream>

#include "lexer.hpp"
#include "ast.hpp"

int main(int argc, char** argv) {
	std::ifstream file("../scripts/simple.deq", std::ios::in);
	if (!file.is_open() || !file.good()) return -1;
	std::stringstream ss;
	ss << file.rdbuf();
	std::string buffer = ss.str();

	deq::Lexer lexer(buffer);
	auto tokens = lexer.run();

	deq::ast::AstBuilder builder(tokens);
	auto ast = builder.run();

	return 0;
}