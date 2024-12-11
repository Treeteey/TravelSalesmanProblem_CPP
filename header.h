/*
sudo apt-get install libsfml-dev
sudo apt -y install build-essential
*/


#pragma

#include <iostream>
#include <vector>
#include <unordered_set>
#include <map>
#include <random>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <iomanip>




class Point{
    public:
        double x_;
        double y_;
        std::vector<int> neighbours_;
        
        Point(double x, double y) : x_(x), y_(y) {}
        void print();

    private:
        bool operator==(const Point& other) const {
            return x_ == other.x_ && y_ == other.y_;
        }

};



class Graph{
    public:        
        std::vector<Point> points_;
        int number_;
        double radius_;
        double price_;
        std::vector<std::vector<double>> distances_;

        Graph();
        Graph(int number, double radius, double price);
        void PrintGraph();
        void PrintDistances();

    private:
        void ClearDistances();
        void CreatePoints(double radius, int count);
        double Distance(const Point& a, const Point& b);
        void CreateNeighbours(int min_neighbors, int max_neighbors);
        void FillDistances();
        
};


// solution.cc functions
std::vector<int> BFS(int start, int end, const Graph &graph);
double FindShortestPath(Graph &graph, int start, int end, std::vector<int>& fullPath);
void SearchClosestNeighbour(Graph &graph, std::vector<bool> &visited,std::vector<int> &back,
                            int &back_size, int &next_point, int& current);
void SearchNextPoint(Graph &graph, int &back_size, int &next_point, 
                     std::vector<bool>& visited, std::vector<int>& back);
bool ContainsIndex(std::vector<int>& v, int index);
void AddSubpath(std::vector<int>& fullpath, std::vector<int>& subpath,
                double& total_distance, Graph& graph, std::vector<bool>& visited);

// window.cc functions
void Run(Graph& g);

