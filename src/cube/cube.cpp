#include "include/cube/cube.hpp"

#include <iostream>
#include <sstream>


namespace solver
{
    Cube Cube::_solvedCube = Cube::_initSolvedCube();

    constexpr Cube Cube::_initSolvedCube() {
        Cube cube{};
        cube.cubies[0].init(WHITE, RED, EMPTY, EMPTY, EMPTY, GREEN);
        cube.cubies[1].init(WHITE, RED, EMPTY, EMPTY, EMPTY, EMPTY);
        cube.cubies[2].init(WHITE, RED, BLUE, EMPTY, EMPTY, EMPTY);
        cube.cubies[3].init(WHITE, EMPTY, EMPTY, EMPTY, EMPTY, GREEN);
        cube.cubies[4].init(WHITE, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY);
        cube.cubies[5].init(WHITE, EMPTY, BLUE, EMPTY, EMPTY, EMPTY);
        cube.cubies[6].init(WHITE, EMPTY, EMPTY, EMPTY, ORANGE, GREEN);
        cube.cubies[7].init(WHITE, EMPTY, EMPTY, EMPTY, ORANGE, EMPTY);
        cube.cubies[8].init(WHITE, EMPTY, BLUE, EMPTY, ORANGE, EMPTY);
        cube.cubies[9].init(EMPTY, RED, EMPTY, EMPTY, EMPTY, GREEN);
        cube.cubies[10].init(EMPTY, RED, EMPTY, EMPTY, EMPTY, EMPTY);
        cube.cubies[11].init(EMPTY, RED, BLUE, EMPTY, EMPTY, EMPTY);
        cube.cubies[12].init(EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, GREEN);
        cube.cubies[13].init(EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY);
        cube.cubies[14].init(EMPTY, EMPTY, BLUE, EMPTY, EMPTY, EMPTY);
        cube.cubies[15].init(EMPTY, EMPTY, EMPTY, EMPTY, ORANGE, GREEN);
        cube.cubies[16].init(EMPTY, EMPTY, EMPTY, EMPTY, ORANGE, EMPTY);
        cube.cubies[17].init(EMPTY, EMPTY, BLUE, EMPTY, ORANGE, EMPTY);
        cube.cubies[18].init(EMPTY, RED, EMPTY, YELLOW, EMPTY, GREEN);
        cube.cubies[19].init(EMPTY, RED, EMPTY, YELLOW, EMPTY, EMPTY);
        cube.cubies[20].init(EMPTY, RED, BLUE, YELLOW, EMPTY, EMPTY);
        cube.cubies[21].init(EMPTY, EMPTY, EMPTY, YELLOW, EMPTY, GREEN);
        cube.cubies[22].init(EMPTY, EMPTY, EMPTY, YELLOW, EMPTY, EMPTY);
        cube.cubies[23].init(EMPTY, EMPTY, BLUE, YELLOW, EMPTY, EMPTY);
        cube.cubies[24].init(EMPTY, EMPTY, EMPTY, YELLOW, ORANGE, GREEN);
        cube.cubies[25].init(EMPTY, EMPTY, EMPTY, YELLOW, ORANGE, EMPTY);
        cube.cubies[26].init(EMPTY, EMPTY, BLUE, YELLOW, ORANGE, EMPTY);
        return cube;
    }

    Cube& Cube::getSolvedCube() {
        return _solvedCube;
    }

    Cube Cube::readCube() {
        return readCube(std::cin);
    }

    Cube Cube::readCube(std::istream& input) {
        Cube cube;
        std::string line;

        std::cout << "Start with top face" << std::endl;
        input >> line;

        for (int i = 0; i < 9; i++) {
            int index = (2 - (i / 3)) * 3 + (i % 3);
            cube.cubies[index].setColor(static_cast<Color>(line[i]), 0);
        }

        std::cout << "Now continue with the front face" << std::endl;
        input >> line;

        for (int i = 0; i < 9; i++) {
            int index = (i / 3) * 9 + (i % 3);
            cube.cubies[index].setColor(static_cast<Color>(line[i]), 1);
        }

        std::cout << "Now comes the right face" << std::endl;
        input >> line;

        for (int i = 0; i < 9; i++) {
            int index = (i / 3) * 9 + (i % 3) * 3 + 2;
            cube.cubies[index].setColor(static_cast<Color>(line[i]), 2);
        }

        std::cout << "The left face, you are halfway through" << std::endl;
        input >> line;

        for (int i = 0; i < 9; i++) {
            int index = (i / 3) * 9 + (2 - (i % 3)) * 3;
            cube.cubies[index].setColor(static_cast<Color>(line[i]), 5);
        }

        std::cout << "Now the back face, almost done" << std::endl;
        input >> line;

        for (int i = 0; i < 9; i++) {
            int index = (i / 3) * 9 + 6 + (2 - (i % 3));
            cube.cubies[index].setColor(static_cast<Color>(line[i]), 4);
        }

        std::cout << "And finally, the bottom face" << std::endl;
        input >> line;

        for (int i = 0; i < 9; i++) {
            int index = 18 + (i / 3) * 3 + (i % 3);
            cube.cubies[index].setColor(static_cast<Color>(line[i]), 3);
        }

        return cube;
    }

    int Cube::numOfMismatchedCubies() {
        int distance = 0;

        for (size_t i = 0; i < cubies.size(); i++) {
            if (this->cubies[i] == _solvedCube.cubies[i]) {
                continue;
            } else if (this->cubies[i].isPermutated(_solvedCube.cubies[i])) {
                distance += 2;
            } else {
                distance++;
            }
        }

        return distance;
    }

    void Cube::rotateHelper(int index1, int index2, int index3, int index4) {
        Cubie temp = std::move(cubies[index1]);
        cubies[index1] = std::move(cubies[index2]);
        cubies[index2] = std::move(cubies[index3]);
        cubies[index3] = std::move(cubies[index4]);
        cubies[index4] = std::move(temp);
    }

    void Cube::rotateU(bool cw) {
        if (cw) {
            rotateHelper(0, 2, 8, 6); // corners
            rotateHelper(1, 5, 7, 3); // edges
        } else {
            rotateHelper(6, 8, 2, 0); // corners
            rotateHelper(3, 7, 5, 1); // edges
        }

        for (int i = 0; i < 9; i++) {
            cubies[i].rotateY(cw);
        }
    }

    void Cube::rotateF(bool cw) {
        if (cw) {
            rotateHelper(0, 18, 20, 2); // corners
            rotateHelper(1, 9, 19, 11); // edges
        } else {
            rotateHelper(2, 20, 18, 0); // corners
            rotateHelper(11, 19, 9, 1); // edges
        }

        for (int i = 0; i < 9; i++) {
            int index = (i / 3) * 9 + (i % 3);
            cubies[index].rotateZ(cw);
        }
    }

    void Cube::rotateR(bool cw) {
        if (cw) {
            rotateHelper(2, 20, 26, 8); // corners
            rotateHelper(5, 11, 23, 17); // edges
        } else {
            rotateHelper(8, 26, 20, 2); // corners
            rotateHelper(17, 23, 11, 5); // edges
        }

        for (int i = 0; i < 9; i++) {
            int index = (i / 3) * 9 + (i % 3) * 3 + 2;
            cubies[index].rotateX(cw);
        }
    }

    void Cube::rotateD(bool cw) {
        if (cw) {
            rotateHelper(18, 24, 26, 20); // corners
            rotateHelper(19, 21, 25, 23); // edges
        } else {
            rotateHelper(20, 26, 24, 18); // corners
            rotateHelper(23, 25, 21, 19); // edges
        }

        for (int i = 0; i < 9; i++) {
            int index = 18 + i;
            cubies[index].rotateY(!cw);
        }
    }

    void Cube::rotateB(bool cw) {
        if (cw) {
            rotateHelper(6, 8, 26, 24); // corners
            rotateHelper(7, 17, 25, 15); // edges
        } else {
            rotateHelper(24, 26, 8, 6); // corners
            rotateHelper(15, 25, 17, 7); // edges
        }

        for (int i = 0; i < 9; i++) {
            int index = (i / 3) * 9 + 6 + (i % 3);
            cubies[index].rotateZ(!cw);
        }
    }

    void Cube::rotateL(bool cw) {
        if (cw) {
            rotateHelper(0, 6, 24, 18); // corners
            rotateHelper(3, 15, 21, 9); // edges
        } else {
            rotateHelper(18, 24, 6, 0); // corners
            rotateHelper(9, 21, 15, 3); // edges
        }

        for (int i = 0; i < 9; i++) {
            int index = (i / 3) * 9 + (i % 3) * 3;
            cubies[index].rotateX(!cw);
        }
    }

    std::string Cube::toString() {
        std::stringstream ss;

        ss << "[";
        for (Cubie& c : cubies) {
            ss << c.toString() << " ";
        }
        ss << "]";

        return ss.str();
    }
} // namespace solver


