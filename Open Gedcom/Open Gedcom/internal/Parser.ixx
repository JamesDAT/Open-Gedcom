export module OpenGedcom:Parser;
import :Settings;
import :DataStructure;

import std;

namespace OpenGedcom {
	export class Parser {
	public:
		Parser() {}
		~Parser() {}

		void ParseFile(const std::filesystem::path& filePath,const ParseSettings& settings) {

			// check validity of file
			if (filePath.extension() != ".ged") {
				throw std::exception("File is not '.ged' file type");
			}
			if (!std::filesystem::exists(filePath)) {
				throw std::exception("Gedcom file does not exist");
			}

			std::ifstream fileStream{ filePath };

			if (!fileStream.is_open()) {
				throw std::exception(std::format("Unable to open file with path `{}`", filePath.string()).c_str());
			}
			
			std::string buf{};
			buf.resize(30);
			fileStream.read(reinterpret_cast<char*>(buf.data()), 30);
			std::cout << buf.c_str() << std::endl;
		}

	private:
		

	private:
		
	};
}