#pragma once
import std;

namespace OpenGedcom {
	struct RegistrySettings {

	};

	enum class ParseWriteFlag {
		Discard,
		Append
	};

	struct ParseSettings {
		ParseWriteFlag WriteFlag;
	};
}
