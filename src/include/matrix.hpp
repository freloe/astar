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
 *          Path  ==  3 \n
 * 
 * @tparam width 
 * @tparam height 
 */
template<int width,int height>
struct Matrix {
    private:
        size_t w = width,h = height;
        std::array<std::array<int,height>,width> data{0};
    public:
        int xStart = -1, yStart = -1, xGoal = -1, yGoal = -1;
        
        int operator()(int x, int y) {
            return data.at(x).at(y);
        }
        bool isWall(int x, int y) {
            return (*this)(x,y) == -1;
        }
        size_t getWidth() {
            return w;
        }

        size_t getHeight() {
            return h;
        }

        void clearPath() {
            for(auto& a : data)
                for(int& i : a) 
                    if(i == 3)
                        i = 0;
        }

        void setStart(int x, int y) {
            if(x < 0 || x >= width || y < 0 || y >= height)
                return;
            if(xStart != -1)
                data.at(xStart).at(yStart) = 0;
            data.at(x).at(y) = 1;
            xStart = x;
            yStart = y;
        }

        void setGoal(int x, int y) {
            if(x < 0 || x >= width || y < 0 || y >= height)
                return;
            if(xGoal != -1)
                data.at(xGoal).at(yGoal) = 0;
            data.at(x).at(y) = 2;
            xGoal = x;
            yGoal = y;
        }

        void setWall(int x, int y) {
            if(x < 0 || x >= width || y < 0 || y >= height)
                return;
            data.at(x).at(y) = -1;
        }

        void setEmpty(int x, int y) {
            if(x < 0 || x >= width || y < 0 || y >= height)
                return;
            data.at(x).at(y) = 0;
        }

        void setPath(int x, int y) {
            if(x < 0 || x >= width || y < 0 || y >= height)
                return;
            data.at(x).at(y) = 3;
        }
};