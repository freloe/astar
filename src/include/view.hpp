
/**
 * @file view.hpp
 * @author Frederick Loeffel
 * @brief This file contains the necessary framework for viewing the program
 * @version 0.1
 * @date 2023-06-29
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include <SFML/Graphics.hpp>

class View {
    private:
        sf::RenderWindow w;
        sf::Image img;
        sf::Texture texture;
        sf::Sprite sprite;

        template<typename Matrix>
        sf::Color getColorAt(Matrix data, int x, int y) {
            switch (data(x,y))
            {
            case -1:
                return sf::Color::Red;
            case 1:
                return sf::Color::Magenta;
            case 2:
                return sf::Color::Green;
            default:
                return sf::Color::White;
            }
        }

    public:
        View(int width, int height) : w{sf::VideoMode(width,height),"A Star"} {
            img.create(width,height,sf::Color::Black);
            texture.loadFromImage(img);
            sprite.setTexture(texture);
        }

        size_t getWidth() {
            return w.getSize().x;
        }

        size_t getHeight() {
            return w.getSize().y;
        }

        sf::RenderWindow& getWindow() {
            return w;
        }

        bool isOpen() {
            return w.isOpen();
        }

        void pollEvents() {
            sf::Event event;
            while (w.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    w.close();
            }
        }

        template<typename Matrix>
        void drawMatrix(Matrix& data) {
            int width = data.getWidth();
            int height = data.getHeight();

            int boxSizeX = w.getSize().x/width;
            int boxSizeY = w.getSize().y/height;

            float offsetX = (w.getSize().x - (boxSizeX * width))/2.0;
            float offsetY = (w.getSize().y - (boxSizeY * height))/2.0;
            
            int countX = 0, countY = 0;

            for(float i = offsetX; i < w.getSize().x-offsetX; i += boxSizeX) {
                for(float j = offsetY; j < w.getSize().y-offsetY; j += boxSizeY) {
                    for(int bx = 1; bx < boxSizeX-1; ++bx) 
                        for(int by = 1; by < boxSizeY-1; ++by)
                            img.setPixel(i+bx,j+by,getColorAt(data,countX,countY));
                    ++countY;    
                }
                ++countX;
                countY = 0;
            }
            
        }

        void draw() {
            texture.loadFromImage(img);
            w.draw(sprite);
            w.display();
        }





};