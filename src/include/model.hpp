/**
 * @file model.hpp
 * @author Frederick Loeffel
 * @brief This file contains the A* Pathfinding Algorithm
 * @version 0.1
 * @date 2023-06-19
 * 
 * @copyright Copyright (c) 2023
 */
#pragma once
#include <map>
#include <set>
#include <queue>
#include "matrix.hpp"


namespace {
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
    };
}

template<float (&heuristic)(Position a, Position b)>
class AStar {
    private:
        std::map<Position,float> gScore;
        std::map<Position,float> fScore;
        std::map<Position,Position> cameFrom;
        std::set<Position> openSet;

        std::vector<Position> reversePath(Position& start, Position cur) {
            std::vector<Position> path;
            while(cur != start) {
                path.insert(path.begin(),cur);
                cur = cameFrom.at(cur);
            }
            return path;
        }

    public:
        template<typename Matrix>
        std::vector<Position> calculatePath(Matrix data) {
            Position start{data.xStart,data.yStart};
            Position goal{data.xGoal,data.yGoal};
            
            openSet.emplace(start);
            gScore.emplace(std::make_pair(start,0));
            fScore.emplace(std::make_pair(start,heuristic(start,goal)));

            while(!openSet.empty()) {
                float smallest = __FLT_MAX__;
                Position cur;
                std::for_each(fScore.begin(),fScore.end(),
                    [&](auto p){ if(p.second < smallest) { smallest = p.second; cur = p.first; } });
                fScore.erase(cur);
                
                if(cur == goal)
                    return reversePath(start,cur);

                openSet.erase(cur);

                for(Position p : cur.getNeighbours(data.getWidth(),data.getHeight())) {
                    float tent_gScore = gScore.at(cur) + data.notWall(p.x,p.y) * heuristic(cur,p);
                    gScore.emplace(std::make_pair(p,__FLT_MAX__));
                    if(tent_gScore < gScore.at(p)) {
                        cameFrom.emplace(std::make_pair(p,cur));
                        cameFrom.at(p) = cur;
                        gScore.at(p) = tent_gScore;
                        fScore.insert_or_assign(p,tent_gScore + heuristic(p,goal));
                        openSet.emplace(p);
                    }
                }
            }
        
            return std::vector<Position>{};

        }



};