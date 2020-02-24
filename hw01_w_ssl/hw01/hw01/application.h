#pragma once

#ifndef HW01_APPLICATION_HPP
#define HW01_APPLICATION_HPP

#include <string>

class Application {

	void checkAuth();

	void printMenu();

	void doReadFile();

	void doEncryptFile();

	void doDecryptFile();

	void doCreateHashFromFile();

	void doCheckHashOfAFile();

public:

	int run();
};
#endif //HW01_APPLICATION_HPP
