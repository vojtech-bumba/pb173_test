#include <iostream>
#include <fstream>
#include <sstream>
#include "cryptographer.h"
#include <openssl/sha.h>
#include <openssl/aes.h>
#include <vector>

const std::string computeSha512(const std::string& input) {
	unsigned char hash[SHA512_DIGEST_LENGTH];
	SHA512_CTX sha512;
	SHA512_Init(&sha512);
	SHA512_Update(&sha512, input.c_str(), input.size());
	SHA512_Final(hash, &sha512);
	std::stringstream tmp;
	for (int i = 0; i < SHA512_DIGEST_LENGTH; ++i) {
		tmp << std::hex << (int)hash[i];
	}
	return tmp.str();
}

void encryptFile(const std::string& inputPath, const std::string& outputPath, unsigned char* key, unsigned char* ivv) {
	/*try {
		std::ifstream fileStream(inputPath);
		std::string fileContent((std::istreambuf_iterator<char>(fileStream)), (std::istreambuf_iterator<char>()));
		const unsigned char* content = reinterpret_cast<const unsigned char*>(fileContent.c_str());


		std::ofstream outFile;
		outFile.open(outputPath);
		outFile << /*enc_out << std::endl;
		outFile.close();
	}
	catch (std::exception & error) {
		std::cerr << "An error occured " << error.what() << std::endl;
	}*/
}

void decryptFile(const std::string& inputPath, const std::string& outputPath, unsigned char* key, unsigned char* iv) {
	/*try {
		std::ifstream fileStream(inputPath);
		std::string fileContent((std::istreambuf_iterator<char>(fileStream)), (std::istreambuf_iterator<char>()));
		const unsigned char* content = reinterpret_cast<const unsigned char*>(fileContent.c_str());

		std::ofstream outFile;
		outFile.open(outputPath);
		//outFile << decrypted << std::endl;
		outFile.close();
	}
	catch (std::exception& error) {
		std::cerr << "An error occured " << error.what() << std::endl;
	}*/
}


void hashFile(const std::string& inputPath, const std::string& outputPath) {
	std::string hash = "";
	try {
		std::ifstream fileStream(inputPath);
		std::string fileContent((std::istreambuf_iterator<char>(fileStream)), (std::istreambuf_iterator<char>()));
		hash += computeSha512(fileContent);
	}
	catch (std::exception &error) {
		std::cerr << "An error occured " << error.what() << std::endl;
		return;
	}
	if (outputPath.size() > 0) {
		try {
			std::ofstream outFile;
			outFile.open(outputPath);
			outFile << hash << std::endl;
			outFile.close();
		}
		catch (std::exception & error) {
			std::cerr << "An error occured " << error.what() << std::endl;
			return;
		}
	}
	else {
		std::cout << hash << std::endl;
	}
}

bool checkFileHash(const std::string& inputPath, const std::string& hashFilePath, const std::string& expectedHash) {
	if (!hashFilePath.empty() && !expectedHash.empty()) {
		std::cerr << "Undefined behaviour, can't check against two different hashes" << std::endl;
		return false;
	}
	if (hashFilePath.empty() && expectedHash.empty()) {
		std::cerr << "Invalid argument, no check-hash given" << std::endl;
	}
	std::string hash = "";
	try {
		std::ifstream fileStream(inputPath);
		std::string fileContent((std::istreambuf_iterator<char>(fileStream)), (std::istreambuf_iterator<char>()));
		hash += computeSha512(fileContent);
	}
	catch (std::exception & error) {
		std::cerr << "An error occured " << error.what() << std::endl;
		return false;
	}
	if (!hashFilePath.empty()) {
		std::string hashFromFile = "";
		try {
			std::ifstream hashFile;
			hashFile.open(hashFilePath);
			hashFile >> hashFromFile;
			hashFile.close();
			return hashFromFile == hash;
		}
		catch (std::exception & error) {
			std::cerr << "An error occured " << error.what() << std::endl;
		}
	}
	else {
		return expectedHash == hash;
	}
	return false;
}

void readFile(const std::string& filePath) {
	try {
		std::ifstream fileStream(filePath);
		std::string fileContent((std::istreambuf_iterator<char>(fileStream)), (std::istreambuf_iterator<char>()));
		std::cout << fileContent << std::endl;
	}
	catch (std::exception & error) {
		std::cerr << "An Error occured: " << error.what() << std::endl;
	}
}