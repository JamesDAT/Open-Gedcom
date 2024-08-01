export module OpenGedcom:DataStructure;
import :Debugging;
import std;

export namespace OpenGedcom {
	using GedID = std::uint32_t;

	struct Individual {
		Individual() {}
		Individual(GedID id) : ID(id) {}
		Individual(std::string name) : Name(name) {}
		Individual(GedID id, std::string name) : ID(id), Name(name) {}

		GedID ID;
		std::string Name;
		bool Alive;
	};

	class IndividualView {
	public:
		IndividualView(Individual* indi, GedID id) : m_Data(indi), ID(id) {}

		~IndividualView() {}

		Individual* operator->() {
			Debugging::Assert(m_Data != nullptr, "Individual was nullptr");
			return m_Data;
		}

		GedID ID;
	private:
		Individual* m_Data = nullptr;
	};

	class IndividualRangeView {
	public:
		using InternalIterator = std::map<GedID, Individual>::iterator;
		using RevInternalIterator = std::map<GedID, Individual>::reverse_iterator;

		IndividualRangeView(InternalIterator begin, InternalIterator end) : m_Begin(begin), m_End(end)  {}

		IndividualView operator[](const GedID& key) const {
			auto it = std::find_if(m_Begin, m_End, [&](const auto& pair) {
				return pair.first == key;
				});
			if (it != m_End) {
				return IndividualView(&it->second, key);
			}
			Debugging::Assert(it != m_End, "IndividualRangeView index out of range. Index is relative to the views begin() iterator");
			// Return an empty IndividualView or handle as needed
			return IndividualView(nullptr, key);
		}

		InternalIterator begin() const { return m_Begin; }
		InternalIterator end() const { return m_End; }

		RevInternalIterator rbegin() const { return RevInternalIterator(m_End); }
		RevInternalIterator rend() const { return RevInternalIterator(m_Begin); }
	private:
		InternalIterator m_Begin;
		InternalIterator m_End;
	};
}