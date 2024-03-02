#pragma once
#include "pch.h"
#include "Objects.h"

namespace gedcom {
class GedcomObject
{
public:
	GedcomObject();
	~GedcomObject();

	inline std::vector<Individual>* getIndividuals() const { return _Individuals; }

private:
	std::vector<Individual>* _Individuals;
};
}

