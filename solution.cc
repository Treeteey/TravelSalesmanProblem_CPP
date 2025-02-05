#include "header.h"


#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <limits>
#include <algorithm>
#include <unordered_set>

using std::vector;
using std::queue;

/*
0______
|  \   \
1   2   3____________
    |______         |______
    |  \   \        |   \  \
    4   5   6       10  11  12
  __|__
 /  |  \
7   8   9

Поиск из 0 в 9
1. Добавим текущую точку в очередь: 0
2. Возьмем из очереди первый элемент: 0
3. Удалим его из очереди
4. И проверим его (0) соседей: 1 2 3
    4.1 Если кого то не посетили -> добавить в очередь: [1 2 3]
    4.2 Также добавим родителя у каждой добавленной точки в parent[i], 
        родителем будет текущий взятый элемент
2. Далее берем след элемент из начала очереди (1): [1,2,3] и смотрим его соседей: их нет, 
3. Удалим (1): [2,3]
4. Добавить нечего
2. Берем передний элемент очереди (2): [3]
3. Удалим его (2)
4. Добавляем его (2) соседей: [3 4 5 6]
2. Берем передний элемент очереди (3)
3. Удалим его (3): [4 5 6 ]
4. Добавим его (3) соседей: 10, 11, 12   -> [4 5 6 10 11 12]
...
4. Добавим соседей (4): 7,8,9
    4.1 Нашли конечный элемент end = 9

Теперь надо восстановить путь с end в start используя parent[]:
 path[] += 9
 path[] += parent[9] ~ 4
 path[] += parent[4] ~ parent[parent[9]] ~ 2
 path[] += 0
 path[]: 9 4 2 0
 ...
Потом развернуть этот путь, так как нужен был путь с start в end
 path[]: 0 2 4 9
*/

// Функция для нахождения пути между двумя точками с использованием BFS
vector<int> BFS(int start, int end, const Graph &graph) {
    int n = graph.points_.size();
    vector<int> parent(n, -1); // Для восстановления пути
    queue<int> q;
    vector<bool> visited(n, false);

    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        if (current == end) break;

        for (int neighbor : graph.points_[current].neighbours_) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                parent[neighbor] = current;
                q.push(neighbor);
            }
        }
    }

    // Восстановление пути
    vector<int> path;
    for (int v = end; v != -1; v = parent[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());

    // Если путь не найден, возвращаем пустой вектор
    if (path[0] != start) return {};
    return path;
}



/**
 * @brief Finds the shortest path between two points in a graph, 
 * visiting all points and returning the total length of the path.
 * @param graph The graph to search.
 * @param start The starting point.
 * @param end The ending point.
 * @param fullPath The vector to store the path.
 * @return The total length of the path.
 * @note Uses a breadth-first search (BFS) algorithm to find the shortest path.
 */
void FindShortestPath(Graph &graph, int start, int end, std::vector<int>& fullpath) {
    int n = graph.number_;
    // вектор посещенных точек
    std::vector<bool> visited(n, false);
    visited[start] = true;
    // вектор пути
    fullpath.clear();
    fullpath.push_back(start);

    /* Вектор back из точек, наблюдаемых по пути движения.
    будем добавлять точки и их соседей
    Вектор нужен, если настанет момент, когда все соседи
    текущей точки посещены -> Мы возьмем последнюю точку из Вектора,
    так как она будет самой ближайшей к current и проверим есть ли у нее
    непосещенные соседи. Если нет - удалить точку из вектора.
    */
    std::vector<int> back;
    int back_size = 1;
    back.push_back(start);

    double total_distance = 0.0;
    int current = start;

    for (int step = 1; step < n; ++step) {
        int next_point = -1;
        // поиск ближайшего соседа current точки
        SearchClosestNeighbour(graph, visited, back, back_size, next_point, current);

        // если нет свободных ближайших точек
        // то попытаемся найти ближайшего соседа
        // рассматривая точки из back. Проверить всех соседей
        // каждой точки из вектора. Если все посещены, то удалить точку
        if (next_point == -1) {
            SearchNextPoint(graph, back_size, next_point, visited, back);
        }else{
            // если нашли следующую точку, то добавляем ее в вектор
            fullpath.push_back(next_point);
            total_distance += graph.distances_[current][next_point];
            visited[next_point] = true;
            current = next_point;
            // RunByStep(graph, 800, fullpath);
            continue;
        }
        // если все же не нашли следующую точку, то плохо / либо прошли все точки = хорошо
        if(next_point == -1){
            bool all_visited = [&visited](){
                for (int i = 0; i < visited.size(); ++i) {
                    if (!visited[i]) return false;
                }
                return true;
            }();
            if (all_visited){
                std::cout << "All points are visited" << std::endl;
            }else
                std::cout << "Error: No available point to visit." << std::endl;
            break;
        }
        // ищем путь с текущей точки до ближайшей непосещенной точки
        // с промежуточными (возможно посещенными) точками
        std::vector<int> subPath = BFS(current, next_point, graph);
        if (subPath.empty()) {
            std::cout << "Error: Path from " << current << " to point " << next_point << " unreachable." << std::endl;
            break;
        }
        // считаем расстояние и добавляем путь от  current до next_point
        
        // std::cout << "Add subpath ";
        // for(int i = 0; i < subPath.size(); ++i){
        //     std::cout << subPath[i] << " ";            
        // }
        // std::cout << std::endl;

        // current = next_point;
        current = AddSubpath(fullpath, subPath, total_distance, graph, visited);
    }// конец цикла

    // если последняя рассматриваемая точка не является конечной
    // то построить путь между current и end
    if (current != end) {
        std::vector<int> subPath = BFS(current, end, graph);
        if (!subPath.empty()) {
            AddSubpath(fullpath, subPath, total_distance, graph, visited);
        }
    }

    graph.total_length_ = total_distance;
}


void SearchClosestNeighbour(Graph &graph, std::vector<bool> &visited, std::vector<int> &back,
                            int &back_size, int &next_point, int &current){
    double min_dist = std::numeric_limits<double>::max();
    // поиск ближайшего соседа current точки
    for (auto neighbour:  graph.points_[current].neighbours_) {
        //add to 'back' neighbours of current
        if (!visited[neighbour]) {  
            if(!ContainsIndex(back, neighbour)){
                back.push_back(neighbour);
                back_size += 1;
            }             
            double dist = graph.distances_[current][neighbour];
            if (dist < min_dist) {
                min_dist = dist;
                next_point = neighbour;
            }
        }
    }
    // std::cout << "next_point = " << next_point << std::endl;
}

void SearchNextPoint(Graph &graph, int &back_size, int &next_point, 
                     std::vector<bool>& visited, std::vector<int>& back){
    bool found = false;
    while(back_size > 0 && !found){
        if(!visited[back[back_size-1]]){
            next_point = back[back_size-1];
            break;
        }
        double min_dist = std::numeric_limits<double>::max();
        for(auto neighbour:  graph.points_[back_size-1].neighbours_){
            if(visited[neighbour] == false){
                if(graph.distances_[back[back_size-1]][neighbour] < min_dist){
                    min_dist = graph.distances_[back[back_size-1]][neighbour];
                    next_point = neighbour;
                }
                back.push_back(next_point);
                back_size += 1;
                found = true;
            }
        }

        if(next_point == -1){
            back.pop_back();
            back_size -= 1;
        }
    }
    // std::cout << "next_point = " << next_point << std::endl;
}


bool ContainsIndex(std::vector<int>& v, int index) {
    for(auto n : v){
        if(n == index){ return true;}
    }
    return false;
}

int AddSubpath(std::vector<int>& fullpath, std::vector<int>& subpath,
                double& total_distance, Graph& graph, std::vector<bool>& visited){
    int stop = subpath[subpath.size() - 1];
    double min_dist = std::numeric_limits<double>::max();
    for (size_t i = 1; i < subpath.size(); ++i) {
        total_distance += graph.distances_[subpath[i - 1]][subpath[i]];
        if (!visited[subpath[i]]) {
            visited[subpath[i]] = true;
            stop = subpath[i];
            std::cout << "stop = " << stop << std::endl;
            fullpath.push_back(subpath[i]);
            break;
        }
        fullpath.push_back(subpath[i]);
        // поиск ближайшего соседа current точки
        for(auto neighbour:  graph.points_[subpath[i]].neighbours_){
            if(visited[neighbour] == false){
                if(graph.distances_[subpath[i]][neighbour] < min_dist){
                    min_dist = graph.distances_[subpath[i]][neighbour];
                    stop = neighbour;
                }
            }
        }
        if(i < subpath.size() - 1 && graph.distances_[subpath[i]][subpath[i]+1] > min_dist){
            visited[stop] = true;
            fullpath.push_back(stop);
            break;
        }
        std::cout << "next_point = " << subpath[i] << std::endl;
        // RunByStep(graph, 800, fullpath);
    }  
    return stop;
}