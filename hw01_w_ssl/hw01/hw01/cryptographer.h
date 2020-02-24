#pragma once

#ifndef HW01_CRYPTOGRAPHER_HPP
#define HW01_CRYPTOGRAPHER_HPP

#include <string>

const std::string computeSha512(const std::string& input);

void encryptFile(const std::string& inputPath, const std::string& outputPath, unsigned char* key, unsigned char* ivv);

void decryptFile(const std::string& inputPath, const std::string& outputPath, unsigned char* key, unsigned char* iv);

void hashFile(const std::string& inputPath, const std::string& outputPath);

bool checkFileHash(const std::string& inputPath, const std::string& hashFilePath, const std::string& hash);

void readFile(const std::string& filePath);

#endif //HW01_CRYPTOGRAPHER_HPP
