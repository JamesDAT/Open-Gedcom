#pragma once
#include "pch.h"
#include "Objects.h"
#include "lexer.h"

namespace gedcom {
class Gedcom
{
public:
	Gedcom();
	~Gedcom();

	static std::unique_ptr<std::vector<Individual>> readFile(const std::string& filePath);

private:
	static std::ifstream getFile(const std::string& filePath);

	Lexer m_lexer{};
};
}

