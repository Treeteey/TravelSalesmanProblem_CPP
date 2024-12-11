#include "header.h"


int main() {
    /*Радиус окружности в пикселях
    1 пиксель = единица длины
     */ 
    double radius = 380; 
    int number = 10;
    double price = 10;
    Graph g(number, radius, price);

    int start = 0;
    int end = number-1;

    g.PrintGraph();

    std::vector<int> path;
    FindShortestPath(g, start, end, path);
    
    std::cout << "Number of visited points = " << path.size();
    
    // path
    for(auto i : path) std::cout << " " << i;
    std::cout << std::endl;

    // total distance to travel through all points
    std::cout << "Total distance = " << g.total_length_ << std::endl;

    // g.PrintDistances();

    // show graph
    int window_size = 800;
    Run(g, window_size, path);  
    return 0;
}