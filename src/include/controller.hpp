/**
 * @file controller.hpp
 * @author Frederick Loeffel
 * @brief This file handles user input and passes that to model and view
 * @version 0.1
 * @date 2023-06-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <vector>

template<typename Model, typename View, typename Matrix>
class Controller {
    private:
        Model& model;
        View& view;
        Matrix& data;
        std::vector<Position> changes;
    public:

        Controller(Model& model, View& view, Matrix& data) : model{model}, view{view}, data{data} {

        }

        void getMatrixPos(sf::Vector2i& pos) {
            int width = data.getWidth();
            int height = data.getHeight();

            int boxSizeX = view.getWidth() /width;
            int boxSizeY = view.getHeight()/height;

            float offsetX = (view.getWidth()  - (boxSizeX * width))/2.0;
            float offsetY = (view.getHeight() - (boxSizeY * height))/2.0;

            pos.x = (pos.x-offsetX) / boxSizeX;            
            pos.y = (pos.y-offsetY) / boxSizeY;
        }

        void pollEvents() {
            auto& w = view.getWindow();
            sf::Event event;
            while (w.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    w.close();
                if (event.type == sf::Event::KeyPressed) 
                    if(event.key.code == sf::Keyboard::Space) {
                        data.clearPath();
                        auto path = model.calculatePath(data);
                        if(path.size() > 0) {
                            for(Position pos : path) {
                                data.setPath(pos.x,pos.y);
                                changes.emplace_back(Position{pos.x,pos.y});
                            }
                        }
                    }

            }
        }

        void pollInput() {
            sf::Vector2i pos = sf::Mouse::getPosition(view.getWindow());
            if(!(pos.x >= view.getWidth() || pos.y >= view.getHeight() || pos.x < 0 || pos.y < 0)) {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
                        getMatrixPos(pos);
                        data.setWall(pos.x,pos.y);
                        changes.emplace_back(Position{pos.x,pos.y});
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) {
                        getMatrixPos(pos);
                        data.setEmpty(pos.x,pos.y);
                        changes.emplace_back(Position{pos.x,pos.y});
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::G)){
                        getMatrixPos(pos);
                        changes.emplace_back(Position{data.getGoal().x,data.getGoal().y});
                        data.setGoal(pos.x,pos.y);
                        changes.emplace_back(Position{pos.x,pos.y});
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
                        getMatrixPos(pos);
                        changes.emplace_back(Position{data.getStart().x,data.getStart().y});
                        data.setStart(pos.x,pos.y);
                        changes.emplace_back(Position{pos.x,pos.y});
                    }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C)) {
                        data.clearPath();
                        changes.emplace_back(Position{-1,-1});
                    }
            }
   
        }

        std::vector<Position>& getChanges() {
            return changes;
        }
};