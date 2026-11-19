#pragma once

#include <string>
#include <unordered_map>

struct CompressionResult {
    std::unordered_map<char, int> frequencies;
    std::unordered_map<char, std::string> codes;
    std::string compressedText;
};

CompressionResult compress(const std::string& plaintext);

std::string decompress(
    const std::string& compressedText,
    const std::unordered_map<char, std::string>& codes
);

