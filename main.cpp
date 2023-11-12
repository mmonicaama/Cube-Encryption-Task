#include <iostream>
#include <string>
#include <fstream>
#include "Cube.h"

int main()
{
    seedRandomGenerator();
    std::string filename = "example.txt";
    char mode;

    std::cout << "Encrypt(e) or Decrypt(d) ? ";
    std::cin >> mode;

    if (mode == 'e' || mode == 'E') {
        encode(filename);
        std::cout << "File encoded successfully.\n";
    } else if (mode == 'd' || mode == 'D') {
        decode();
        std::cout << "File decoded successfully.\n";
    }

    return 0;
}