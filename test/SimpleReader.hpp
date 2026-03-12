#pragma once

#include <string>
#include <fstream>

class SimpleReader {
public:
    static std::string ReadWholeFile(const std::string& path) {
        std::ifstream file(path, std::ios::binary | std::ios::ate);
        if(!file)
            throw std::runtime_error("Failed to open file: " + path);

        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);

        std::string buffer(size, '\0');

        if(!file.read(buffer.data(), size))
            throw std::runtime_error("Failed to read file: " + path);

        return buffer;
    }
};