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
    Matrix<100,100> m;
    AStar<heuristic> A1;
    View v(1000,1000);
    Controller<decltype(A1),decltype(v),decltype(m)> c{A1,v,m};
    v.drawMatrix<decltype(m)>(m);

    while(v.isOpen()) {
        c.pollInput();
        c.pollEvents();
        for(auto p : c.getChanges()) {
            if(p.x == -1 && p.y == -1)
                v.drawMatrix<decltype(m)>(m);
            else
                v.updateMatrix(m,p.x,p.y);
        }
        c.getChanges().clear();
        v.draw();
    }

    return 0;
}