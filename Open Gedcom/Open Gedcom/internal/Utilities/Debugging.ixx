export module OpenGedcom:Debugging;
import <cstdio>; // for stderr macro
import std;

namespace OpenGedcom {
	export class Debugging {
	public:
		static inline void Assert(const bool expression, const std::string_view errorMessage, const std::source_location source = std::source_location::current()) {
#ifdef _DEBUG
			if (!expression) {
				PrintMessage(errorMessage, source.file_name(), source.function_name(), source.line());
				std::abort();
			}
#endif
		}

		static inline void ReleaseAssert(const bool expression, const std::string_view errorMessage, const std::source_location source = std::source_location::current()) {
			if (!expression) {
				PrintMessage(errorMessage, source.file_name(), source.function_name(), source.line());
				std::abort();
			}
		}

		static inline void GenerateWarning(const std::string_view warning) {
#ifdef _DEBUG
			if (DisableOutput) return;
			std::println(stderr, "\033[1;31mWarning!\033[0m \033[1;33m{}\033[0m", warning);
#endif // _DEBUG
		}

		static void PrintMessage(std::string_view assertText, std::string_view file, std::string_view function, uint_least32_t line) {
			if (DisableOutput) return;
			// the ansi escape sequences do make this difficult to read, but it should be fine
			std::println(stderr, "\033[1;31mAssertion failed:\033[0m (\033[1;33m{}\033[0m)", assertText);
			std::println(stderr, "\033[1;34mFile:\033[0m \033[1;33m{}\033[0m", file);
			std::println(stderr, "\033[1;34mFunction:\033[0m \033[1;33m{}\033[0m", function);
			std::println(stderr, "\033[1;34mLine:\033[0m \033[1;33m{}\033[0m", line);
		}

		static bool DisableOutput;
	};

	bool Debugging::DisableOutput = false;
}