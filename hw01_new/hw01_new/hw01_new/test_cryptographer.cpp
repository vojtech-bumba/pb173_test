#include "cryptographer.h"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("sha 512 test vector") {
	std::vector<unsigned char> theKey{ '1', '2', '3', '4', '5', '6', '7', '8', '1', '2', '3', '4', '5', '6', '7', '8' };

	Cryptographer crypto(theKey);

	std::string input = "abc"; 
	std::string hashedInput = crypto.hashFile(input);

	CHECK(hashedInput == "ddaf35a193617abacc417349ae20413112e6fa4e89a97ea20a9eeee64b55d39a2192992a274fc1a836ba3c23a3feebbd454d4423643ce80e2a9ac94fa54ca49f");
}
