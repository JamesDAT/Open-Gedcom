// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#pragma once
#include <array>
#include <atomic>
#include <cstdint>
#include <string>
#include <optional>

namespace OpenGedcom {
    struct LineObject {
        std::atomic<bool> valid = false;
        std::string line;
    };

    class LineRingBuffer {
    public:
        LineRingBuffer()
            : m_readerIndex(0), m_writerIndex(0) {}

        ~LineRingBuffer() {}

        void MarkEOF() {
            m_eof.store(true, std::memory_order_release);
            for (auto& slot : m_buffer) {
                slot.valid.store(true);
                slot.valid.notify_all();
            }
        }
        
        void PushLine(std::string line) {
            LineObject& slot = m_buffer[m_writerIndex % BUFFER_SIZE];

            // wait for slot
            while (slot.valid.load(std::memory_order_acquire)) {
                slot.valid.wait(true, std::memory_order_relaxed);
            }

            // store and notify the reader
            slot.line = std::move(line);
            slot.valid.store(true, std::memory_order_release);
            slot.valid.notify_one();

            ++m_writerIndex;
            m_bufferCount.fetch_add(1, std::memory_order_relaxed);
        }

        std::optional<std::string> GetLine() {
            LineObject& slot = m_buffer[m_readerIndex % BUFFER_SIZE];

            // wait for slot
            while (!slot.valid.load(std::memory_order_acquire)) {
                if(m_eof.load(std::memory_order_acquire)) {
                    return std::nullopt;
                }
                slot.valid.wait(false, std::memory_order_relaxed);
            }

            // store and notify the writer
            std::string result = std::move(slot.line);
            slot.valid.store(false, std::memory_order_release);
            slot.valid.notify_one();

            ++m_readerIndex;
            m_bufferCount.fetch_sub(1, std::memory_order_relaxed);

            return result;
        }

    private:
        static constexpr size_t BUFFER_SIZE = 1024;

        std::atomic<bool> m_eof{false};
        std::atomic<uint32_t> m_bufferCount{0};

        uint32_t m_readerIndex;
        uint32_t m_writerIndex;

        std::array<LineObject, BUFFER_SIZE> m_buffer;
    };
}