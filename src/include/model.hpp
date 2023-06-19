/**
 * @file model.hpp
 * @author Frederick Loeffel
 * @brief This file contains the A* Pathfinding Algorithm
 * @version 0.1
 * @date 2023-06-19
 * 
 * @copyright Copyright (c) 2023
 */

namespace {
    struct Position {
        int x;
        int y;

        friend bool operator==(Position& a, Position& b) {
            return a.x == b.x && a.y == b.y;
        }
    };
}

class AStar {
    private:

    public:
};