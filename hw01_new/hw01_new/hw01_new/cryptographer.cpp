#include "cryptographer.h"
#include <iostream>
#include <fstream>
#include <sstream>

Cryptographer::Cryptographer(std::vector<unsigned char> newKey) {
	if (newKey.size() != 16) {
		throw "invalid size of key";
	}
	key = newKey;
}

const std::vector<unsigned char> Cryptographer::generateIv() {
	std::vector<unsigned char> result;
	for (int i = 0; i < 16; ++i) {
		result.push_back((char)('0' + std::rand() % 256));
	}
	return result;
}

std::vector<unsigned char> Cryptographer::findIv(const std::string& filename) {
	for (int i = 0; i < ivs.size(); ++i) {
		if (ivs.at(i).first == filename) {
			return ivs.at(i).second;
		}
	}
	throw "IV not found for this file";
}

void Cryptographer::pairIvToFilename(const std::string& filename, std::vector<unsigned char> iv) {
	ivs.emplace_back(std::make_pair(filename, iv));
}

void Cryptographer::encryptFile(const std::string& inputFile, const std::string& outputFile) {
	// open files - possibly refactor
	std::ifstream input(inputFile, std::ifstream::binary);
	if (!input)
	{
		std::cerr << "error while opening the input file" << std::endl;
		return;
	}
	std::ofstream output(outputFile, std::ofstream::binary);

	// initialize key and iv
	const std::vector<unsigned char> keyCopy = key;
	mbedtls_aes_setkey_enc(&aesCtx, &*keyCopy.begin(), 128);
	std::vector<unsigned char> iv = generateIv();
	pairIvToFilename(outputFile, iv);

	// find the length of the input
	input.seekg(0, input.end);
	int inputLength = input.tellg();
	input.seekg(0, input.beg);

	// create buffers
	unsigned char inputBuffer[16] = {};
	unsigned char outputBuffer[16] = {};
	memset(inputBuffer, '\0', 16);
	memset(outputBuffer, '\0', 16);

	// read file
	for (int i = 0; i < inputLength; i += 16) {

		// encrypt filled buffer
		input.read((char*)inputBuffer, 16);
		mbedtls_aes_crypt_cbc(&aesCtx, MBEDTLS_AES_ENCRYPT, 16, &*iv.begin(), inputBuffer, outputBuffer);
		output.write((char*)outputBuffer, 16);

		// clear the buffers
		memset(inputBuffer, '\0', 16);
		memset(outputBuffer, '\0', 16);
	}
	if (input.read((char*)inputBuffer, 16)) {
		mbedtls_aes_crypt_cbc(&aesCtx, MBEDTLS_AES_ENCRYPT, 16, &*iv.begin(), inputBuffer, outputBuffer);
		output.write((char*)outputBuffer, 16);
	}
}

void Cryptographer::decryptFile(const std::string& inputFile, const std::string& outputFile) {

	//open files - possibly refactor
	std::ifstream input(inputFile, std::ifstream::binary);
	if (!input)
	{
		std::cerr << "error while opening the input file" << std::endl;
		return;
	}
	std::ofstream output(outputFile, std::ofstream::binary);

	// initialize key and iv
	std::vector<unsigned char> keyCopy = key;
	mbedtls_aes_setkey_dec(&aesCtx, &*keyCopy.begin(), 128);
	std::vector<unsigned char> iv = findIv(inputFile);

	// find length of the input - possibly delete
	input.seekg(0, input.end);
	int inputLength = input.tellg();
	input.seekg(0, input.beg);

	// create buffers
	unsigned char inputBuffer[16] = {};
	unsigned char outputBuffer[16] = {};
	memset(inputBuffer, '\0', 16);
	memset(outputBuffer, '\0', 16);

	// decrypt
	for (int i = 0; i < inputLength; i += 16) {
		// decrypt filled buffer
		input.read((char*)inputBuffer, 16);
		mbedtls_aes_crypt_cbc(&aesCtx, MBEDTLS_AES_DECRYPT, 16, &*iv.begin(), inputBuffer, outputBuffer);
		output.write((char*)outputBuffer, 16);

		// clear the buffers
		memset(inputBuffer, '\0', 16);
		memset(outputBuffer, '\0', 16);
	}
	if (input.read((char*)inputBuffer, 16)) {
		mbedtls_aes_crypt_cbc(&aesCtx, MBEDTLS_AES_DECRYPT, 16, &*iv.begin(), inputBuffer, outputBuffer);
		output.write((char*)outputBuffer, 16);
	}
}

const std::string Cryptographer::hashFile(const std::string& inputFile) {
	// open file
	std::ifstream input(inputFile, std::ifstream::binary);
	if (!input)
	{
		std::cerr << "error while opening the input file" << std::endl;
		return "";
	}

	// init sha
	mbedtls_sha512_init(&shaCtx);
	mbedtls_sha512_starts(&shaCtx, 0);

	// find the length of the input
	input.seekg(0, input.end);
	int inputLength = input.tellg();
	input.seekg(0, input.beg);

	// create buffers
	unsigned char inputBuffer[16] = {};
	unsigned char outputBuffer[64] = {};
	memset(inputBuffer, '\0', 16);
	memset(outputBuffer, '\0', 64);

	// compute hash
	for (int i = 0; i < inputLength; i += 16) {
		input.read((char*)inputBuffer, 16);
		mbedtls_sha512_update(&shaCtx, inputBuffer, 16);

		// clear buffer
		memset(inputBuffer, '\0', 16);
	}
	bool hasTail = false;
	for (int i = 0; i < inputLength % 16; ++i) {
		inputBuffer[i] = input.get();
		hasTail = true;
	}
	if (hasTail) {
		mbedtls_sha512_update(&shaCtx, inputBuffer, inputLength % 16);
	}

	mbedtls_sha512_finish(&shaCtx, outputBuffer);

	std::stringstream result;

	for (int i = 0; i < 64; ++i) {
		result << std::hex << (int)outputBuffer[i];
	}
	
	return result.str();
}

bool Cryptographer::compareHashToFile(const std::string& hash, const std::string& file) {
	std::string hashed = hashFile(file);
	return hash == hashed;
}

bool Cryptographer::compareHashFileToFile(const std::string& fstFile, const std::string& sndFile) {
	std::string fstHash = hashFile(fstFile);
	std::string sndHash = hashFile(sndFile);
	return fstHash == sndHash;
}