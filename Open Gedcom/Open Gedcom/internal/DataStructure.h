#pragma once
import std;

using GedID = std::uint32_t;

namespace OpenGedcom {
	struct Individual {
		std::string Name;
		bool Alive;
	};

	class IndividualView {
	public:
		IndividualView(Individual* indi, GedID id) : m_Data(indi), ID(id) {}

		~IndividualView() {}

		Individual* operator->() {
			return m_Data;
		}

		GedID ID;
	private:
		Individual* m_Data = nullptr;
	};
}
