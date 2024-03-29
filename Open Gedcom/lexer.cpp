#include "pch.h"
#include "lexer.h"

using namespace gedcom;

void Lexer::lex(std::ifstream& stream) {
	std::vector<Token> tokens{};

	char character;
	std::string token{};
	stream.get(character);

	while (!stream.eof()) {

		if (std::isspace(character)) {
			stream.get();
		}
		else if (character == '0') {
			Token tok{};
			Token* prevTok = &tok;


		}
		else if (std::isalnum(character)) {
			token = "";

			while (!stream.eof() && std::isalnum(character)) {
				token += character;
				stream.get();
			}
		}
	}
}

void Lexer::lexLine(std::ifstream& stream) {

}
