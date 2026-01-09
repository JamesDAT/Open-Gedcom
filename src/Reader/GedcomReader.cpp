// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#include "GedcomReader.h"
#include "Reader/SourceReaders/Utf8SourceReader.h"
#include <atomic>
#include <iostream>
#include <stdexcept>

namespace OpenGedcom {
    GedcomReader::GedcomReader() {
        
    }

    GedcomReader::~GedcomReader() {

    }

    std::future<void> GedcomReader::ReadFile(const std::filesystem::path& path) {
        return std::async(std::launch::async, [this, path](){
            // create stream
            std::ifstream file(path, std::ios::binary);

            // get the encoding from the BOM
            auto encoding = DetectEncoding(file);

            switch(encoding.encoding) {
                case TextEncoding::Utf8:
                    m_sourceReader = std::make_unique<UTF8SourceReader>(file, encoding.bomSize);
                break;

                case TextEncoding::Utf16LE:
                    throw std::runtime_error("Utf16LE is not supported yet!");
                break;

                case TextEncoding::Utf16BE:
                    throw std::runtime_error("Utf16BE is not supported yet!");
                break;
            }

            std::string buffer;
            buffer.reserve(ISourceReader::CHUNK_SIZE);
            while(m_sourceReader->ReadChunk(buffer)) {
                size_t start = 0;

                while(true) {
                    size_t newline = buffer.find('\n', start);
                    if(newline == std::string::npos) {
                        break;
                    }

                    // \r\n
                    size_t lineEnd = newline;
                    if(lineEnd > start && buffer[lineEnd - 1] == '\r') {
                        --lineEnd;
                    }

                    std::string line;
                    line.assign(buffer.data() + start, lineEnd - start);
                    PushLine(std::move(line));
                    start = newline + 1;
                }

                buffer.erase(0, start);
            }

            if(!buffer.empty()) {
                PushLine(std::move(buffer));
                buffer.clear();
            }

            // reached end of file
            {
                std::unique_lock lock(m_mutex);
                m_eof = true;
            }
            m_notEmpty.notify_all();
            m_notFull.notify_all();
        });
    }

    std::optional<std::string> GedcomReader::GetNextLine() {
        std::unique_lock lock(m_mutex);
        m_notEmpty.wait(lock, [this]() { return !m_lineQueue.empty() || m_eof; });

        if (m_lineQueue.empty()) return std::nullopt;

        std::string line = std::move(m_lineQueue.front());
        m_lineQueue.pop();

        lock.unlock();
        m_notFull.notify_one();

        return line;
    }

    void GedcomReader::PushLine(std::string&& text) {
        std::unique_lock lock(m_mutex);
        m_notFull.wait(lock, [this]() { return m_lineQueue.size() < m_maxQueueSize; });

        if(m_eof)
            return;

        m_lineQueue.push(std::move(text));
        lock.unlock();
        m_notEmpty.notify_one();
    }

    EncodingInfo GedcomReader::DetectEncoding(std::ifstream& file) {
        uint8_t bom[3] = {0};

        file.read(reinterpret_cast<char*>(bom), 3);
        size_t n = file.gcount();

        file.clear();           // clear EOF flags
        file.seekg(0);          // rewind

        if (n >= 3 &&
            bom[0] == 0xEF &&
            bom[1] == 0xBB &&
            bom[2] == 0xBF) {
            return { TextEncoding::Utf8, 3 };
        }

        if (n >= 2 &&
            bom[0] == 0xFF &&
            bom[1] == 0xFE) {
            return { TextEncoding::Utf16LE, 2 };
        }

        if (n >= 2 &&
            bom[0] == 0xFE &&
            bom[1] == 0xFF) {
            return { TextEncoding::Utf16BE, 2 };
        }

        // no BOM
        return { TextEncoding::Utf8, 0 };
    }
}