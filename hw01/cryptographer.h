#pragma once
#include <string>
#include <vector>
#include "mbedtls/aes.h"
#include "mbedtls/sha512.h"

class Cryptographer {
	std::vector<unsigned char> key;
	std::vector<std::pair<std::string, std::vector<unsigned char>>> ivs;
	mbedtls_aes_context aesCtx;
	mbedtls_sha512_context shaCtx;



	const std::vector<unsigned char> generateIv();

	void pairIvToFilename(const std::string& filename, std::vector<unsigned char> iv);

	std::vector<unsigned char> findIv(const std::string& filename);

public:
	Cryptographer(std::vector<unsigned char> newKey);

	void encryptFile(const std::string& inputFile, const std::string& outputFile);

	void decryptFile(const std::string& inputFile, const std::string& outputFile);

	const std::string hashFile(const std::string& inputFile);
	
	bool compareHashToFile(const std::string& hash, const std::string& file);

	bool compareHashFileToFile(const std::string& fstFile, const std::string& sndFile);
};