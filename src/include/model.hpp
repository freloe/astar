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

template<float (&heuristic)(Position a, Position b)>
class AStar {
    private:

        std::vector<Position> reversePath(std::map<Position,Position>& cameFrom, Position& start, Position cur) {
            std::vector<Position> path;
            cur = cameFrom.at(cur); //Dont include goal pos in path
            while(cur != start) {
                path.insert(path.begin(),cur);
                cur = cameFrom.at(cur);
            }
            return path;
        }

    public:
        template<typename Matrix>
        std::vector<Position> calculatePath(Matrix& data) {
            std::map<Position,float> gScore;
            std::map<Position,float> fScore;
            std::map<Position,Position> cameFrom;
            std::set<Position> openSet;

            Position start = data.getStart();
            Position goal = data.getGoal();
            
            if(start.x == -1 || goal.x == -1)
                return std::vector<Position>{};

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
                    return reversePath(cameFrom, start,cur);

                openSet.erase(cur);

                for(Position p : cur.getNeighbours(data.getWidth(),data.getHeight())) {
                    if(data.isWall(p.x,p.y))
                        continue;
                    float tent_gScore = gScore.at(cur) +  heuristic(cur,p);
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