#include "header.h"


int main() {
    double radius = 370; // Радиус окружности в пикселях
    int number = 100;
    double price = 10;
    Graph g(number, radius, price);
    g.PrintGraph();
    std::vector<int> path;
    double total_cost = FindShortestPath(g, 0, number-1, path);
    std::cout << "Number of visited points = " << path.size();
    // g.PrintDistances();
    // Run(g);  
    return 0;
}