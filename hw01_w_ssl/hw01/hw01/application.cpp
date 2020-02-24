#include <iostream>
#include "application.h"
#include "cryptographer.h"

void Application::printMenu() {
	std::cout << "Choose an option\n";
	std::cout << "1 - Read file\n";
	std::cout << "2 - Encrypt file\n";
	std::cout << "3 - Decrypt file\n";
	std::cout << "4 - Create hash from file\n";
	std::cout << "5 - Check hash of a file\n";
	std::cout << "6 - Exit" << std::endl;
}

void Application::doReadFile() {
	std::string fname = "";
	std::cout << "Path to the file:" << std::endl;
	std::cin >> fname;
	readFile(fname);
}

void Application::doEncryptFile() {
	std::string fname = "";
	std::cout << "Path to the file to be encrypted:" << std::endl;
	std::cin >> fname;
	std::string ofname = "";
	std::cout << "Output file:" << std::endl;
	std::cin >> ofname;
	encryptFile(fname, ofname, (unsigned char*)"0123456789012345", (unsigned char*)"0123456789012345");
}

void Application::doDecryptFile() {
	std::string fname = "";
	std::cout << "Path to the file to be decrypted:" << std::endl;
	std::cin >> fname;
	std::string ofname = "";
	std::cout << "Output file:" << std::endl;
	std::cin >> ofname;
	decryptFile(fname, ofname, (unsigned char*)"0123456789012345", (unsigned char*)"0123456789012345");
	
}

void Application::doCreateHashFromFile() {
	std::string fname = "";
	std::cout << "Path to the file to be hashed:" << std::endl;
	std::cin >> fname;
	std::string ofname = "";
	std::string answer = "";
	while (answer != "y" && answer != "n" && answer != "Y" && answer != "N") {
		std::cout << "Do you want to store the hash in a file? (y/n)" << std::endl;
		std::cin >> answer;
	}
	if (answer == "y" || answer == "Y") {
		std::cout << "Path to the file to store the hash in (press Enter to only print the hash):" << std::endl;
		std::cin >> ofname;
	}
	hashFile(fname, ofname);
}

void Application::doCheckHashOfAFile() {
	std::string fname = "";
	std::cout << "Path to the file to check the hash of:" << std::endl;
	std::cin >> fname;
	std::string hashOrHashFile = "";
	std::string answer = "";
	bool result;
	while (answer != "y" && answer != "n" && answer != "Y" && answer != "N") {
		std::cout << "Do you want to load the check hash from a file? (y/n):" << std::endl;
		std::cin >> answer;
	}
	if (answer == "y" || answer == "Y") {
		std::cout << "Path to the file with the check hash:" << std::endl;
		std::cin >> hashOrHashFile;
		result = checkFileHash(fname, hashOrHashFile, "");
	}
	else {
		std::cout << "Insert the check hash:" << std::endl;
		std::cin >> hashOrHashFile;
		result = checkFileHash(fname, "", hashOrHashFile);
	}
	if (result) {
		std::cout << "PASS: hashes are the same" << std::endl;
	}
	else {
		std::cout << "FAIL: hashes are NOT the same" << std::endl;
	}
}

int Application::run() {
	while (true) {
		int chosen;
		printMenu();
		std::cin >> chosen;
		switch (chosen) {
		case 1:
			doReadFile();
			break;
		case 2:
			std::cout << "not implemented" << std::endl;
			break;
			//doEncryptFile();
			//break;
		case 3:
			std::cout << "not implemented" << std::endl;
			break;
			//doDecryptFile();
			//break;
		case 4:
			doCreateHashFromFile();
			break;
		case 5:
			doCheckHashOfAFile();
			break;
		case 6:
			return 0;
		default:
			std::cout << "Invalid option" << std::endl;
			break;
		}
	}
}