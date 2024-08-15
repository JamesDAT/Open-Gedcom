import OpenGedcom;
import std;

int main() {
	OpenGedcom::Registry registry{};
	registry.AddIndividual({"bob"});
	registry.AddIndividual({"bob"});
	registry.AddIndividual({"bob"});
	registry.AddIndividual({"bob"});
	registry.AddIndividual({"bob"});
	registry.AddIndividual({"bob"});
	registry.ReadFile("D:\\github\\Repo\\Open-Gedcom\\Samples\\555SAMPLE16LE.ged");
	
	OpenGedcom::Registry::ToggleDebugMessages();
	auto data = registry.Data();

	auto view = registry.GetIndividualRange();

	for (auto& [id, indi] : view) {
		//std::println("Name: {}\nID: {}", indi.Name, id);
	}

	__debugbreak();

	return 0;
}