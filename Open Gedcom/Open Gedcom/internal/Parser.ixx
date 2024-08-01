export module OpenGedcom:Parser;
import :Settings;
import :DataStructure;
import :FileStream;

import std;

namespace OpenGedcom {
	export class Parser {
	public:
		Parser() {}
		~Parser() {}

		void ParseFile(const std::filesystem::path& filePath, const ParseSettings& settings) {
			/// parsing a file takes many steps. Each line should be consumed individually,
			/// then line should be fed to a line parser, which will identify the current 'state' or number
			/// at the start of the line. The line will then be tokenized, then depending on the state of
			/// the token, it will find and be added to the relavent parent token. A parser should then
			/// either go through the tokens when completed, or once the state reaches level 0 again.
			/// This should populate the registry with the data.


			// check validity of file
			if (!std::filesystem::exists(filePath)) {
				throw std::exception("File does not exist");
			}
			if (filePath.extension() != ".ged") {
				throw std::exception("File is not '.ged' file type");
			}

			// stream testing
			FileStream myStream{ filePath };
			std::string buffer{};
			myStream.ReadWholeFile(buffer);
			std::print("{}", buffer);
		}

	private:
		

	private:
		
	};
}