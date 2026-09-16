#include "include/cube/cubie.hpp"

#include <sstream>

solver::Cubie::Cubie(std::array<Color, 6>& faces) : faces(std::move(faces)) {
}

void solver::Cubie::setColor(Color col, int index) {
    faces[index] = col;
}

bool solver::Cubie::operator==(Cubie& other) {
    return this->faces == other.faces;
}

bool solver::Cubie::isPermutated(Cubie& other) {
    int xorResult = 0;

    for (size_t i = 0; i < this->faces.size(); i++) {
        xorResult ^= static_cast<char>(this->faces[i]);
        xorResult ^= static_cast<char>(other.faces[i]);
    }

    return xorResult == 0;
}

void solver::Cubie::rotateHelper(int index1, int index2, int index3, int index4) {
    Color temp = faces[index1];
    faces[index1] = faces[index2];
    faces[index2] = faces[index3];
    faces[index3] = faces[index4];
    faces[index4] = temp;
}

void solver::Cubie::rotateX(bool cw) {
    if (cw) {
        rotateHelper(0, 1, 3, 4);
    } else {
        rotateHelper(4, 3, 1, 0);
    }
}

void solver::Cubie::rotateY(bool cw) {
    if (cw) {
        rotateHelper(1, 2, 4, 5);
    } else {
        rotateHelper(5, 4, 2, 1);
    }
}

void solver::Cubie::rotateZ(bool cw) {
    if (cw) {
        rotateHelper(5, 3, 2, 0);
    } else {
        rotateHelper(0, 2, 3, 5);
    }
}

std::string solver::Cubie::toString() {
    std::stringstream ss;

    ss << "[";
    for (Color c : faces) {
        ss << static_cast<char>(c);
    }
    ss << "]";

    return ss.str();
}