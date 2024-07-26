export module OpenGedcom:Settings;
import std;

export namespace OpenGedcom {
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