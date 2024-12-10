#include "header.h"


int main() {
    double radius = 370; // Радиус окружности в пикселях
    int number = 100;
    double price = 10;
    Graph g(number, radius, price);
    g.PrintGraph();
    std::vector<int> path;
    double total_cost = FindShortestPath(g, 0, 99, path);
    Run(g);  
    return 0;
}