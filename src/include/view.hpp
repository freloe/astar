
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
        void drawMatrix(Matrix data) {
            int width = data.getWidth();
            int height = data.getHeight();

            int boxSizeX = w.getSize().x/width;
            int boxSizeY = w.getSize().y/height;

            for(int i = 0; i < w.getSize().x; i += boxSizeX) 
                for(int j = 0; j < w.getSize().y; j += boxSizeY)
                    for(int bx = 1; bx < boxSizeX-1; ++bx) 
                        for(int by = 1; by < boxSizeY-1; ++by)
                            img.setPixel(i+bx,j+by,getColorAt(data,i/boxSizeX,j/boxSizeY));
            
        }

        void draw() {
            texture.loadFromImage(img);
            w.draw(sprite);
            w.display();
        }





};