#pragma once

#ifndef cube_hpp
#define cube_hpp

#include "cubie.hpp"
#include <array>

namespace solver
{
    class Cube {
        public:
        static Cube& getSolvedCube();
        static Cube readCube();
        static Cube readCube(std::istream& input);

        int numOfMismatchedCubies();
        
        void rotateU(bool cw);
        void rotateF(bool cw);
        void rotateR(bool cw);
        void rotateD(bool cw);
        void rotateB(bool cw);
        void rotateL(bool cw);
        
        std::string toString();

        private:
        static constexpr Cube _initSolvedCube();
        void rotateHelper(int index1, int index2, int index3, int index4);

        static Cube _solvedCube;

        /**
         * index = layer * 9 + line * 3 + index
         * 
         * layer counting from top to bottom
         * line counting from front to back
         * index counting from left to right
         */
        std::array<solver::Cubie, 27> cubies{};
    };
} // namespace rubiks_cube_solver

#endif // cube_hpp