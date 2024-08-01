module;
export module OpenGedcom;
export import :DataStructure;
export import :Settings;
import :Parser;
import :Debugging;
import std;

export namespace OpenGedcom {
	class Registry {

		// public functions
	public:
		Registry() : Registry(RegistrySettings{}) {}
		Registry(const RegistrySettings& settings)
			:
			m_Settings(settings),
			m_Individuals(std::make_unique<std::map<GedID, Individual>>()),
			m_Parser(Parser{})
		{}

		~Registry() = default;

		void ReadFile(const std::filesystem::path& filePath, ParseSettings settings = {}) {
			m_Parser.ParseFile(filePath, settings);
		}

		void AddIndividual(Individual indi, GedID id, bool explicitOverride = false) noexcept {
			Debugging::Assert(m_Individuals->find(id) == m_Individuals->end() || explicitOverride, std::format("Individual with ID '{}' already exists. Set 'explicitOverride' to 'true' if this was intended.", id).c_str());
			indi.ID = id;
			(*m_Individuals)[indi.ID] = indi;
		}

		void AddIndividual(Individual indi) noexcept {
			auto nextId = [this]() {
				if (m_Individuals->empty()) {
					return GedID(0);
				}
				else {
					return static_cast<GedID>(m_Individuals->rbegin()->first + 1); // next unique id
				}
				};
			indi.ID = nextId();
			(*m_Individuals)[indi.ID] = indi;
		}

		// get individual with indi ID
		[[nodiscard]] IndividualView GetIndividual(GedID id) const {
			if (!(*m_Individuals).contains(id)) {
				throw std::exception(std::format("No individual with id `{}` exists", id).c_str());
			}
			IndividualView view{ &(*m_Individuals)[id], id };
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

		[[nodiscard]] IndividualRangeView GetIndividualRange(GedID begin, GedID end) {
			IndividualRangeView view{ m_Individuals->lower_bound(begin), m_Individuals->upper_bound(end) };
			return view;
		}

		// returns entire individual view, non resizable
		[[nodiscard]] IndividualRangeView GetIndividualRange() {
			IndividualRangeView view{ m_Individuals->lower_bound(0), m_Individuals->upper_bound(static_cast<int>(m_Individuals->size())) };
			return view;
		}
		
		[[nodiscard]] inline std::map<GedID, Individual>* Data() {
			Debugging::GenerateWarning("Usage of Registry.Data() is potentially unsafe. The registry data will be cleared when the registry goes out of scope.");
			return m_Individuals.get();
		}

		static inline void ToggleDebugMessages(bool showMessages = Debugging::DisableOutput) {
			Debugging::DisableOutput = !showMessages;
		}

		// public member
	public:


		// private members
	private:
		const RegistrySettings m_Settings;
		Parser m_Parser;
		std::unique_ptr<std::map<GedID, Individual>> m_Individuals;
	};

	export class StreamRegistry {
	public:

	private:
	};
}