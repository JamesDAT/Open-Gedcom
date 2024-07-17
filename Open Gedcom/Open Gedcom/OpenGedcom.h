#pragma once
#include "internal/Settings.h"
#include "internal/Parser.h"
#include "internal/DataStructure.h"
import std;

namespace OpenGedcom {
	class Registry {

	// public functions
	public:
		Registry() : Registry(RegistrySettings{}) {}
		Registry(const RegistrySettings& settings) 
			: 
			m_Settings(settings), 
			m_Individuals(std::make_unique<std::unordered_map<GedID, Individual>>())
		{}

		~Registry() = default;

		void ReadFile(const std::string& fileName, ParseSettings settings = {}) {

		}

		void AddIndividual(GedID id,const Individual& indi) {
			(*m_Individuals)[id] = indi;
		}

		// get individual with indi ID
		[[nodiscard]] IndividualView GetIndividual(GedID id) const {
			if (!(*m_Individuals).contains(id)) {
				throw std::exception(std::format("No individual with id `{}` exists", id).c_str());
			}
			IndividualView view{&(*m_Individuals)[id], id};
			return view;
		}

		// get first individual with the name
		[[nodiscard]] IndividualView GetIndividual(const std::string& name) const {
			auto it = std::find_if(std::begin(*m_Individuals), std::end(*m_Individuals),
				[&name](const std::pair<GedID, Individual>& pair) { return pair.second.Name == name; });
			if (it == std::end(*m_Individuals)) {
				throw std::exception(std::format("No individual with name `{}` exists", name).c_str());
			}

			IndividualView view{ &it->second, it->first };
			return view;
		}

	// public member
	public:
		

	private:
		const RegistrySettings m_Settings;

		std::unique_ptr<std::unordered_map<GedID, Individual>> m_Individuals{};
	};
}
