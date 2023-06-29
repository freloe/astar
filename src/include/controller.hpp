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

template<typename Model, typename View, typename Matrix>
class Controller {
    private:
        Model& model;
        View& view;
        Matrix& data;
    public:

        Controller(Model& model, View& view, Matrix& data) : model{model}, view{view}, data{data} {

        }

        sf::Vector2i getMatrixPos(sf::Vector2i pos) {
            if(pos.x >= view.getWidth() || pos.y >= view.getHeight() || pos.x < 0 || pos.y < 0)
                return;

            int width = data.getWidth();
            int height = data.getHeight();

            int boxSizeX = view.getWidth() /width;
            int boxSizeY = view.getHeight()/height;

            float offsetX = (view.getWidth()  - (boxSizeX * width))/2.0;
            float offsetY = (view.getHeight() - (boxSizeY * height))/2.0;

            int x = (pos.x-offsetX) / boxSizeX;
            int y = (pos.y-offsetY) / boxSizeY;
        }

        void pollInput() {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
                sf::Vector2i pos = sf::Mouse::getPosition(view.getWindow());
                pos = getMatrixPos(pos)
                data.setWall(pos.x,pos.y);
            }


                
        }
};