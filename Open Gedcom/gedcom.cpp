#include "pch.h"
#include "gedcom.h"

using namespace gedcom;
#define VALIDATE_BYTE_ORDER_MASK(bom)  (bom[0] == (char)0xEF) && (bom[1] == (char)0xBB) && (bom[2] == (char)0xBF)
#define GEDCOM_VERSION "5.5.5"

Gedcom::Gedcom()
{

}

std::unique_ptr<std::vector<Individual>> Gedcom::readFile(const std::string& filePath) {
	auto individuals = std::make_unique<std::vector<Individual>>();

	auto inFile = getFile(filePath);

	return std::move(individuals);
}

std::ifstream Gedcom::getFile(const std::string& filePath) {
	if (filePath.substr(filePath.length() - 4) != ".ged") {
		throw std::runtime_error("File is not .ged type!");
	}

	std::ifstream inFile(filePath, std::ios::binary);
	if (!inFile) {
		throw std::runtime_error("Error opening file!");
	}

	// read in bom
	char bom[3];
	inFile.read(bom, 3);

	if (!VALIDATE_BYTE_ORDER_MASK(bom)) { // not a fatal error
		std::cerr << "Invalid byte order mask" << std::endl;
	}

	// re-open file in text mode
	inFile.close();
	inFile.open(filePath);
	if (!inFile) {
		throw std::runtime_error("Error opening file!");
	}


	return inFile;
}

Gedcom::~Gedcom() {
	
}
