#include "header.h"


int main() {
    double radius = 370; // Радиус окружности в пикселях
    int number = 100;
    double price = 10;
    Graph g(number, radius, price);
    g.PrintGraph();

    // Run(g);  
    return 0;
}