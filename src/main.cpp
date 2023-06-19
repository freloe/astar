#include <iostream>
#include <SFML/Graphics.hpp>

int main(){
    auto w = sf::RenderWindow(sf::VideoMode(1000,1000),"A Star");

    while(w.isOpen()){

        sf::Event event;
        while (w.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                w.close();
        }
    }
    return 0;
}