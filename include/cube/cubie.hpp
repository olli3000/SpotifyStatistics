#pragma once

#ifndef cubie_hpp
#define cubie_hpp

#include "include/cube/color.hpp"

#include <iostream>
#include <array>

namespace solver
{
    class Cubie {        
        public:
        Cubie() = default;
        Cubie(std::array<Color, 6>& faces);
        
        constexpr void init(Color u, Color f, Color r, Color d, Color b, Color l) {
            faces[0] = u;
            faces[1] = f;
            faces[2] = r;
            faces[3] = d;
            faces[4] = b;
            faces[5] = l;
        }
        
        void setColor(Color col, int index);
        
        /**
         * Check if two Cubies are the same
         */
        bool operator==(Cubie& other);
        
        /**
         * Check if Cubies are permutations of each other
         */
        bool isPermutated(Cubie& other);
        
        /**
         * Rotate along x-axis (left and right side of cube)
         */
        void rotateX(bool cw);
        
        /**
         * Rotate along y-axis (up and down side of cube)
         */
        void rotateY(bool cw);
        
        /**
         * Rotate along z-axis (front and back side of cube)
         */
        void rotateZ(bool cw);
        
        std::string toString();

        private:
        /**
         * [0] up
         * [1] front
         * [2] right
         * [3] down
         * [4] back
         * [5] left
         */
        std::array<Color, 6> faces{EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY};
        void rotateHelper(int index1, int index2, int index3, int index4);
    };
}

#endif // cubie_hpp