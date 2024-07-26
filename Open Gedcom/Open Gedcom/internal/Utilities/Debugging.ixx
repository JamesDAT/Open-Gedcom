export module Debugging;
import <cstdio>;
import std;

namespace OpenGedcom {
	export class Debugging {
	public:
		static inline void Assert(const bool expression, const std::string_view errorMessage, const std::source_location source = std::source_location::current()) {
#ifdef _DEBUG
			if (!expression) {
				std::println(stderr, "Assertion failed: ({}),\nFile: {},\nFunction: {},\nLine: {}", errorMessage, source.file_name(), source.function_name(), source.line());
				std::abort();
			}
#endif
		}
	};
}