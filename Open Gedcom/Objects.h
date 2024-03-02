#pragma once
#include "pch.h"

namespace gedcom {
enum class GenderEnum {
	NONE,
	MALE,
	FEMALE
};

struct Individual {
	int ID = 0;
	std::string Name = "No Name";
	std::string DateOfBirth = "dd/mm/yyyy";
	std::string DateOfDeath = "dd/mm/yyyy";
	bool IsDead = false;
	GenderEnum Gender = GenderEnum::NONE;

	std::vector<Individual*> Parents{};
	std::vector<Individual*> Children{};
};
}
