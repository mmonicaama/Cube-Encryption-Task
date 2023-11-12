#ifndef CUBE_H
#define CUBE_H

#include <string>

class Cube
{
public:
    Cube();
    void fillCube(const std::string&, int size);
    std::string readFromCube() const;
    void rotateUp();
    void rotateDown();
    void rotateLeft();
    void rotateRight();

private:
    char vertices[8];
};

void seedRandomGenerator();
char generateRandomDirection();
int generateRandomNumber();
void encode(const std::string&);
void decode();

#endif // CUBE_H