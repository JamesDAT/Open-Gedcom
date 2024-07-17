export module Main;
import <OpenGedcom.h>;
import std;

export int main() {
	OpenGedcom::Registry registry{};
	OpenGedcom::Individual myIndividual{};
	myIndividual.Name = "Terrance";

	registry.AddIndividual(0, myIndividual);

	//auto view = registry.GetIndividual(0);
	auto view = registry.GetIndividual("Terrance");

	std::print("Name: {}\nID: {}", view->Name, view.ID);

	return 0;
}