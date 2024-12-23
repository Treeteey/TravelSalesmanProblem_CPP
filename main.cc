#include "header.h"


int main() {
    /*Радиус окружности в пикселях
    1 пиксель = единица длины
     */ 
    double radius = 380; 
    int number = 100;
    double price = 10;
    Graph g(number, radius, price);

    int start = 0;
    int end = 99;
    do{
        std::cout << "Input start point: "; 
        std::cin >> start;
    }while(start < 0 || start > 99);
    do{
        std::cout << "Input end point: "; 
        std::cin >> end;
    }while(end < 0 || end > 99);
    g.PrintGraph();

    std::vector<int> path;
    FindShortestPath(g, start, end, path);
    std::cout << "Radius = " << g.radius_ << std::endl;
    std::cout << "Number of points = " << g.number_ << std::endl;
    std::cout << "Number of visited points = " << path.size() << std::endl;
    
    // path
    std::cout << "Path: ";
    for(auto i : path) std::cout << " " << i;
    std::cout << std::endl;

    // total distance to travel through all points
    std::cout << "Total distance = " << g.total_length_ << std::endl;
    // show graph
    int window_size = 800;
    Run(g, window_size, path);  
    return 0;
}


