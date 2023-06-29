/**
 * @file matrix.hpp
 * @author Frederick Loeffel
 * @brief Consistent data model across different controlles, models and views
 * @version 0.1
 * @date 2023-06-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include <array>

/**
 * @brief For consistency: \n
 *          Walls == -1 \n
 *          Empty ==  0 \n
 *          Start ==  1 \n
 *          Goal  ==  2 \n
 * 
 * @tparam width 
 * @tparam height 
 */
template<int width,int height>
struct Matrix {
    private:
        size_t w = width,h = height;
        std::array<std::array<int,height>,width> data;
    public:
        int xStart = 0, yStart = 0, xGoal = 1, yGoal = 0;
        
        int operator()(int x, int y) {
            return data.at(x).at(y);
        }
        bool notWall(int x, int y) {
            return (*this)(x,y) != -1;
        }
        size_t getWidth() {
            return w;
        }

        size_t getHeight() {
            return h;
        }

        void setStart(int x, int y) {
            data.at(xStart).at(yStart) = 0;
            data.at(x).at(y) = 1;
            xStart = x;
            yStart = y;
        }

        void setGoal(int x, int y) {
            data.at(xGoal).at(yGoal) = 0;
            data.at(x).at(y) = 2;
            xGoal = x;
            yGoal = y;
        }

        void setWall(int x, int y) {
            data.at(x).at(y) = -1;
        }

        void setEmpty(int x, int y) {
            data.at(x).at(y) = 0;
        }
};