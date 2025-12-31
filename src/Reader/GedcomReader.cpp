// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#include "GedcomReader.h"
#include <atomic>

namespace OpenGedcom {
    GedcomReader::GedcomReader() {

    }

    GedcomReader::~GedcomReader() {

    }

    bool GedcomReader::IsEndOfFile() const {
        return m_eof.load(std::memory_order_acquire);
    }

    std::future<void> GedcomReader::ReadFile(const std::filesystem::path& path) {
        return std::async(std::launch::async, [&](){

            // reached end of file
            m_eof.store(true, std::memory_order_release);
            m_ready.release();
        });
    }

    std::string_view GedcomReader::GetNextLine() {
        m_ready.acquire();


        // TODO: check remaining lines, currently unsafe!!!!
        if(m_eof.load(std::memory_order_acquire) && false) {
            return {};
        }

        auto& slot = m_buffer.read_slot();
        std::string_view view = slot.text;

        m_buffer.commit_read();
        m_free.release();

        return view;
    }

    void GedcomReader::PushLine(std::string&& text, uint64_t lineNo) {
        m_free.acquire(); // wait for available space

        auto& slot = m_buffer.write_slot(); // obtain an available line from the ring buffer
        slot.text = std::move(text);
        slot.lineNo = lineNo;

        m_buffer.commit_write();
        m_ready.release();
    }
}