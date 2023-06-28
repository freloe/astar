/**
 * @file data.hpp
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
        std::array<std::array<int,height>,width> data;
    public:
        int& operator()(int x, int y) {
            return data.at(x).at(y);
        }
};