#include "Cube.h"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

Cube::Cube()
{
    for (int i = 0; i <8; ++i) {
        vertices[i] = '$';
    }
}

void Cube::fillCube(const std::string& data, int size)
{
    for (int i = 0; i < size; ++i) {
        vertices[i] = data[i];
    }
}

std::string Cube::readFromCube() const
{
    std::string res;
    for (int i = 0; i < 8; ++i) {
        if (vertices[i] == '$') {
            continue;
        }
        res += vertices[i];
    }
    return res;
}

void Cube::rotateRight()
{
    char temp[8];
    for (int i = 0; i < 8; ++i) {
        temp[i] = vertices[i];
    }

    vertices[0] = temp[4];
    vertices[1] = temp[0];
    vertices[2] = temp[3];
    vertices[3] = temp[7];
    vertices[4] = temp[5];
    vertices[5] = temp[1];
    vertices[6] = temp[2];
    vertices[7] = temp[6];
}

void Cube::rotateLeft()
{
    char temp[8];
    for (int i = 0; i < 8; ++i) {
        temp[i] = vertices[i];
    }

    vertices[0] = temp[1];
    vertices[1] = temp[5];
    vertices[2] = temp[6];
    vertices[3] = temp[2];
    vertices[4] = temp[0];
    vertices[5] = temp[4];
    vertices[6] = temp[7];
    vertices[7] = temp[3];
}

void Cube::rotateUp()
{
    char temp[8];
    for (int i = 0; i < 8; ++i) {
        temp[i] = vertices[i];
    }

    vertices[0] = temp[3];
    vertices[1] = temp[2];
    vertices[2] = temp[6];
    vertices[3] = temp[7];
    vertices[4] = temp[0];
    vertices[5] = temp[1];
    vertices[6] = temp[5];
    vertices[7] = temp[4];
}

void Cube::rotateDown()
{
    char temp[8];
    for (int i = 0; i < 8; ++i) {
        temp[i] = vertices[i];
    }

    vertices[0] = temp[4];
    vertices[1] = temp[5];
    vertices[2] = temp[1];
    vertices[3] = temp[0];
    vertices[4] = temp[7];
    vertices[5] = temp[6];
    vertices[6] = temp[2];
    vertices[7] = temp[3];
}

void seedRandomGenerator() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

int generateRandomNumber() {
    //std::srand(static_cast<unsigned>(std::time(nullptr)));

    return std::rand() % 4; 
}

char generateRandomDirection() {
    //std::srand(static_cast<unsigned>(std::time(nullptr)));

    int randomIndex = std::rand() % 4;

    char directions[] = {'U', 'D', 'L', 'R'};
    return directions[randomIndex];
}

void encode(const std::string& filename)
{
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }
    std::string content((std::istreambuf_iterator<char>(fin)), std::istreambuf_iterator<char>());

    int cubesCount = (content.size() % 8 ) ? (content.size() / 8 + 1) : (content.size() / 8);

    Cube* cubes = new Cube[cubesCount];

    int j = 0;
    for (int i = 0; i < content.size(); i += 8) {
        std::string str = content.substr(i, 8);
        cubes[j++].fillCube(str, str.size()); 
    }


    std::string key;
    for (int i = 0; i < cubesCount; ++i) {
        key += generateRandomDirection();
        //key += generateRandomNumber() + '0';
        key += static_cast<char>(generateRandomNumber() + '0');
        key += ":";
    }

    std::cout << key << std::endl;

    int k{0};
    for (int i = 0; i < cubesCount; ++i) {
        if (key[k] == 'U') {
            for (int j = 0; j < key[k + 1] - '0'; ++j) {
                cubes[i].rotateUp();
            }
            k += 3;
        } else if (key[k] == 'D') {
            for (int j = 0; j < key[k + 1]  - '0'; ++j) {
                cubes[i].rotateDown();
            }
            k += 3;
        } else if (key[k] == 'R') {
            for (int j = 0; j < key[k + 1]  - '0'; ++j) {
                cubes[i].rotateRight();
            }
            k += 3;
        } else if (key[k] == 'L') {
            for (int j = 0; j < key[k + 1]  - '0'; ++j) {
                cubes[i].rotateLeft();
            }
            k += 3;
        }
    }
    fin.close();

    std::ofstream fout("encoded.txt", std::ios::trunc);
    if (!fout.is_open()) {
        std::cerr << "Error opening file encoded.txt" << std::endl;
        return;
    }

    fout << key << "\n";
    for (int i = 0; i < cubesCount; ++i) {
        fout << cubes[i].readFromCube();
    }

    fout.close();
    delete[] cubes;
}

void decode()
{
    std::ifstream fin("encoded.txt");
    if (!fin.is_open()) {
        std::cerr << "Error opening file encoded.txt" << std::endl;
        return;
    }

    std::string key;
    std::getline(fin, key);

    int cubesCount = key.size() / 3;
    Cube* cubes = new Cube[cubesCount];

    std::string content((std::istreambuf_iterator<char>(fin)), std::istreambuf_iterator<char>());

    int j = 0;
    for (int i = 0; i < content.size(); i += 8) {
        std::string str = content.substr(i, 8);
        cubes[j++].fillCube(str, str.size()); 
    }
     
    int k = key.size() - 1;
    for (int i = 0; i < cubesCount; ++i) {
        if (key[k - 2] == 'U') {
            for (int j = 0; j < key[k - 1] - '0'; ++j) {
                cubes[i].rotateDown();
            }
            k -= 3;
        } else if (key[k - 2] == 'D') {
            for (int j = 0; j < key[k - 1] - '0'; ++j) {
                cubes[i].rotateUp();
            }
            k -= 3;
        } else if (key[k - 2] == 'R') {
            for (int j = 0; j < key[k - 1] - '0'; ++j) {
                cubes[i].rotateLeft();
            }
            k -= 3;
        } else if (key[k - 2] == 'L') {
            for (int j = 0; j < key[k - 1] - '0'; ++j) {
                cubes[i].rotateRight();
            }
            k -= 3;
        }
    }
    
    fin.close();


    std::ofstream fout("decoded.txt", std::ios::trunc);
    if (!fout.is_open()) {
        std::cerr << "Error opening file decoded.txt" << std::endl;
        return;
    }
     
    for (int i = 0; i < cubesCount; ++i) {
        fout << cubes[i].readFromCube();
    }


    fout.close();
    delete[] cubes;
}