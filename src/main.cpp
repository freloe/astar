#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "include/view.hpp"
#include "include/model.hpp"
#include "include/matrix.hpp"
#include "include/controller.hpp"

float heuristic(Position a, Position b){
    float x = a.x - b.x;
    float y = a.y - b.y;
    return sqrt(x*x+y*y);
};

int main(){
    Matrix<17,13> m;
    AStar<heuristic> A1;
    View v(1000,1000);
    Controller<decltype(A1),decltype(v),decltype(m)> c{A1,v,m};

    while(v.isOpen()) {
        c.pollInput();
        c.pollEvents();
        v.drawMatrix<decltype(m)>(m);
        v.draw();
    }

    return 0;
}