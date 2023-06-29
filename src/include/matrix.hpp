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
#include <vector>

struct Position {
        int x;
        int y;

        friend bool operator==(Position& a, Position& b) {
            return a.x == b.x && a.y == b.y;
        }
        friend bool operator!=(Position& a, Position& b) {
            return !(a == b);
        }
        friend bool operator<(const Position a,const Position b) {
            return (a.y < b.y) || (a.y == b.y && a.x < b.x);
        }

        std::set<Position> getNeighbours(size_t width,size_t height) {
            std::set<Position> p;
            for(int i = -1; i < 2; ++i)
                for(int j = -1; j < 2; ++j)
                    if(x+i >= 0 && x+i < width && y+j >= 0 && y+j < height && !(i == 0 && j == 0)) 
                        p.emplace(Position{x+i,y+j});
            return p;
        }

        std::set<Position> getDirectNeighbours(size_t width,size_t height) {
            std::set<Position> p;
            if(x+1 < width)
                p.emplace(Position{x+1,y});
            if(x-1 >= 0)
                p.emplace(Position{x-1,y});
            if(y+1 < height)
                p.emplace(Position{x,y+1});
            if(y-1 >= 0)
                p.emplace(Position{x,y-1});
            return p;
        }

    };

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
        Position start{-1,-1}, goal{-1,-1};
    public:

        Position getStart(){
            return start;
        }

        Position getGoal() {
            return goal;
        }
        
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
            if(start.x != -1)
                data.at(start.x).at(start.y) = 0;
            data.at(x).at(y) = 1;
            start.x = x;
            start.y = y;
        }

        void setGoal(int x, int y) {
            if(x < 0 || x >= width || y < 0 || y >= height)
                return;
            if(goal.x != -1)
                data.at(goal.x).at(goal.y) = 0;
            data.at(x).at(y) = 2;
            goal.x = x;
            goal.y = y;
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