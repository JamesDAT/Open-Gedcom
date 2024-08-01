export module OpenGedcom:FileStream;
import std;

using Buffer = std::vector<char>;

namespace OpenGedcom {
	enum class BOM {
		None,
		Utf8,
		Utf16LE
	};

	export class FileStream {
	public:
		FileStream() {}
		FileStream(const std::filesystem::path& path) {
			m_InternalStream = std::ifstream(path, std::ios::binary | std::ios::ate);
			ScanBOM();
		}

		void ReadWholeFile(std::string& output) {
			m_InternalStream.seekg(0, std::ios::end);
			std::size_t size = m_InternalStream.tellg();
			m_InternalStream.seekg(0, std::ios::beg);
			if (m_FileEncoding != BOM::None) {
				m_InternalStream.seekg(2, std::ios::beg);
				size -= 2;
			}

			Buffer buffer{};
			buffer.resize(size);
			m_InternalStream.read(buffer.data(), size);

			GetBufferContent(output, buffer);
		}

	private:
		std::ifstream m_InternalStream{};
		BOM m_FileEncoding = BOM::None;

		void GetBufferContent(std::string& output, const Buffer& buffer) {
			switch (m_FileEncoding) {
			case BOM::None:
				output = std::string(buffer.begin(), buffer.end());
				break;
			case BOM::Utf8:
				output = std::string(buffer.begin(), buffer.end());
				break;
			case BOM::Utf16LE:
				WideStringToString(output, buffer);
				break;
			}
		}

		void WideStringToString(std::string& output, const Buffer& buffer) {
			std::size_t wcharCount = buffer.size() / sizeof(wchar_t);

			std::wstring utf16Str(reinterpret_cast<const wchar_t*>(buffer.data()), wcharCount);

			output = utf16Str | std::ranges::views::transform([](wchar_t wc) {
				return static_cast<char>(wc);
				}) | std::ranges::to<std::string>();
		}

		void WideStringToString(std::string& output, const std::wstring& wstr) {
			output = wstr | std::ranges::views::transform([](wchar_t wc) {
				return static_cast<char>(wc);
				}) | std::ranges::to<std::string>();
		}

		void ScanBOM() {
			m_InternalStream.seekg(0, std::ios::beg);
			std::array<unsigned char, 4> bom{};
			m_InternalStream.read(reinterpret_cast<char*>(bom.data()), bom.size());
			m_InternalStream.seekg(0, std::ios::beg);

			if (bom[0] == 0xEF && bom[1] == 0xBB && bom[2] == 0xBF) {
				// utf8
				m_FileEncoding = BOM::Utf8;
			}
			else if (bom[0] == 0xFF && bom[1] == 0xFE && bom[2] != 0x00) {
				// utf16le
				m_FileEncoding = BOM::Utf16LE;
			}
			else if (bom[0] == 0xFE && bom[1] == 0xFF) {
				// utf16be
				throw std::exception("UTF-16BE file encoding not supported!");
			}
			else if (bom[0] == 0xFF && bom[1] == 0xFE && bom[2] == 0x00 && bom[3] == 0x00) {
				// utf32le
				throw std::exception("UTF-32LE file encoding not supported!");
			}
			else if (bom[0] == 0x00 && bom[1] == 0x00 && bom[2] == 0xFE && bom[3] == 0xFF) {
				// utf32be
				throw std::exception("UTF-32BE file encoding not supported!");
			}
			else {
				// none, assume utf8
				// technically doesn't follow spec, but a lot of utf8 files don't have a BOM
				m_FileEncoding = BOM::None;
			}
		}
	};
}