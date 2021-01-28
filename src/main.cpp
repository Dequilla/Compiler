#include <iostream>
#include <sstream>
#include <fstream>

#include "lexer.hpp"

int main(int argc, char** argv) {
	std::ifstream file("../scripts/simple.deq", std::ios::in);
	if (!file.is_open() || !file.good()) return -1;
	std::stringstream ss;
	ss << file.rdbuf();
	std::string buffer = ss.str();

	deq::Lexer lexer(buffer);
	auto tokens = lexer.run();

	return 0;
}