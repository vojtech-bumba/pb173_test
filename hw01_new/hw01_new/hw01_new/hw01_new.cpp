#include <iostream>
#include "mbedtls/aes.h"
#include "cryptographer.h"

int main()
{
    std::vector<unsigned char> theKey{ '1', '2', '3', '4', '5', '6', '7', '8', '1', '2', '3', '4', '5', '6', '7', '8' };

    Cryptographer crypto(theKey);
    crypto.encryptFile("test.txt", "out.txt");
    crypto.encryptFile("test2.txt", "out2.txt");
    crypto.encryptFile("test3.txt", "out3.txt");
    crypto.decryptFile("out2.txt", "decrypted2.txt");
    crypto.decryptFile("out.txt", "decrypted.txt");
    crypto.decryptFile("out3.txt", "decrypted3.txt");

    const std::string hash = crypto.hashFile("test.txt");
    std::cout << "HASH:" << hash << std::endl;
    bool a = crypto.compareHashToFile(hash, "test.txt");
    std::cout << "hash == file " << a << std::endl;

    std::cout << "file == file " << crypto.compareHashFileToFile("test.txt", "test.txt") << std::endl;
    std::cout << "file == file " << crypto.compareHashFileToFile("test.txt", "test2.txt") << std::endl;
}
