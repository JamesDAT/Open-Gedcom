import OpenGedcom;
import std;

int main() {
	OpenGedcom::Registry registry{};
	registry.AddIndividual({1, "bob"}, 1);
	registry.AddIndividual({2, "bob"}, 2);
	registry.AddIndividual({7, "bob"}, 7);
	registry.AddIndividual({8, "bob"}, 8);
	registry.AddIndividual({9, "bob"}, 9);
	registry.AddIndividual({10, "bob"}, 10);
	

	auto view = registry.GetIndividualRange(1, 5);

	for (auto& [id, indi] : view) {
		std::println("Name: {}\nID: {}", indi.Name, id);
	}

	return 0;
}