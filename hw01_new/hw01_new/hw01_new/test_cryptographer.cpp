#include "cryptographer.h"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("sha 512 test") {
	std::vector<unsigned char> theKey{ '1', '2', '3', '4', '5', '6', '7', '8', '1', '2', '3', '4', '5', '6', '7', '8' };

	Cryptographer crypto(theKey);
		
	std::string hashedFile = crypto.hashFile("test.txt");
	CHECK(crypto.compareHashToFile(hashedFile, "test.txt") == 1);
	CHECK(crypto.compareHashFileToFile("test2.txt", "test2.txt") == 1);
	CHECK(crypto.compareHashToFile(hashedFile, "test2.txt") == 0);
	CHECK(crypto.compareHashFileToFile("test.txt", "test2.txt") == 0);
}

TEST_CASE("aes 128 cbc test file with content len ANY*16bytes") {
	std::vector<unsigned char> theKey{ '1', '2', '3', '4', '5', '6', '7', '8', '1', '2', '3', '4', '5', '6', '7', '8' };

	Cryptographer crypto(theKey);

	std::ifstream input("test.txt");
	std::stringstream ss;
	while (auto chr = input.get()) {
		ss << chr;
	}
	std::string content = ss.str();
	
	crypto.encryptFile("test.txt", "out.txt");
	crypto.decryptFile("out.txt", "dec.txt");

	std::ifstream dec("dec.txt");
	std::stringstream ds;
	while (auto chr = dec.get()) {
		ds << chr;
	}
	CHECK(content == ds.str());
}

TEST_CASE("aes 128 cbc test file with content not len ANY*16bytes") {
	std::vector<unsigned char> theKey{ '1', '2', '3', '4', '5', '6', '7', '8', '1', '2', '3', '4', '5', '6', '7', '8' };

	Cryptographer crypto(theKey);

	std::ifstream input("test2.txt");
	std::stringstream ss;
	while (auto chr = input.get()) {
		ss << chr;
	}
	std::string content = ss.str();

	crypto.encryptFile("test2.txt", "out2.txt");
	crypto.decryptFile("out2.txt", "dec2.txt");

	std::ifstream dec("dec2.txt");
	std::stringstream ds;
	while (auto chr = dec.get()) {
		ds << chr;
	}
	CHECK(content == ds.str());
}

TEST_CASE("aes 128 cbc test file with content shorter than 16bytes") {
	std::vector<unsigned char> theKey{ '1', '2', '3', '4', '5', '6', '7', '8', '1', '2', '3', '4', '5', '6', '7', '8' };

	Cryptographer crypto(theKey);

	std::ifstream input("test3.txt");
	std::stringstream ss;
	while (auto chr = input.get()) {
		ss << chr;
	}
	std::string content = ss.str();

	crypto.encryptFile("test3.txt", "out3.txt");
	crypto.decryptFile("out3.txt", "dec3.txt");

	std::ifstream dec("dec3.txt");
	std::stringstream ds;
	while (auto chr = dec.get()) {
		ds << chr;
	}
	CHECK(content == ds.str());
}