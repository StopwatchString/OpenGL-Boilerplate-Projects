#ifndef UTILS_H
#define UTILS_H

#include <fstream>
#include <vector>
#include <string>

const char* loadFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        return nullptr; // File couldn't be opened
    }

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<char> buffer(size + 1);
    if (!file.read(buffer.data(), size)) {
        return nullptr; // Read failed
    }

    buffer[size] = '\0'; // Null-terminate the buffer

    char* result = new char[size + 1];
    std::copy(buffer.begin(), buffer.end(), result);

    return result;
}

#endif