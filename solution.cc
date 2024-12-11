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


// База
// double FindShortestPath(Graph &graph, int start, int end, std::vector<int>& fullPath) {
//     int n = graph.number_;
//     // вектор посещенных точек
//     std::vector<bool> visited(n, false);
//     visited[start] = true;
//     // вектор пути
//     fullPath.clear();
//     fullPath.push_back(start);
//     /* Стек из точек, наблюдаемых по пути движения
//     будем добавлять точки и их соседей
//     Стек нужен, если настанет момент, когда все соседи
//     текущей точки посещены -> Мы возьмем первую точку из стека,
//     так как она будет самой ближайшей к current и проверим есть ли у нее
//     непосещенные соседи
//     */
//     std::stack<int> backtrack;
//     backtrack.push(start);

//     double total_distance = 0.0;
//     int current = start;

//     for (int step = 1; step < n; ++step) {
//         double min_dist = std::numeric_limits<double>::infinity();
//         int next_point = -1;
//         // поиск ближайшего соседа current точки
//         for (auto neighbour:  graph.points_[current].neighbours_) {
//             //add to q neighbours of current
//             if (!visited[neighbour]) {  
//                 backtrack.push(neighbour);              
//                 double dist = graph.distances_[current][neighbour];
//                 if (dist < min_dist) {
//                     min_dist = dist;
//                     next_point = neighbour;
//                 }
//             }
//         }
//         // если нет свободных ближайших точек
//         // то попытаемся найти ближайшего соседа
//         // рассматривая точки из стека. Проверить всех соседей
//         // каждой точки из стека. Если все посещены, то удалить точку из стека
//         if (next_point == -1) {
//             while(!backtrack.empty()){
//                 int top = backtrack.top();
//                 for(auto neighbour:  graph.points_[top].neighbours_){
//                     if(visited[neighbour] == false){
//                         next_point = neighbour;
//                         break;
//                     }else{
//                         backtrack.pop();
//                     } 
//                 }
//             }
//         }else{
//             fullPath.push_back(next_point);
//             visited[next_point] = true;
//             current = next_point;
//             continue;
//         }
        
//         if(next_point == -1){
//             std::cout << "Ошибка: Нет доступных точек для посещения." << std::endl;
//             break;
//         }
//         // ищем путь с текущей точки до ближайшей непосещенной точки
//         // с промежуточными (возможно посещенными) точками
//         std::vector<int> subPath = BFS(current, next_point, graph);
//         if (subPath.empty()) {
//             std::cout << "Ошибка: Путь до точки " << next_point << " недостижим." << std::endl;
//             break;
//         }

//         for (size_t i = 1; i < subPath.size(); ++i) {
//             total_distance += graph.distances_[subPath[i - 1]][subPath[i]];
//             if (!visited[subPath[i]]) {
//                 visited[subPath[i]] = true;
//             }
//             fullPath.push_back(subPath[i]);
//         }
//         current = next_point;
//     }

//     if (current != end) {
//         std::vector<int> subPath = BFS(current, end, graph);
//         if (!subPath.empty()) {
//             for (size_t i = 1; i < subPath.size(); ++i) {
//                 total_distance += graph.distances_[subPath[i - 1]][subPath[i]];
//                 if (!visited[subPath[i]]) {
//                     visited[subPath[i]] = true;
//                     fullPath.push_back(subPath[i]);
//                 }
//             }
//         }
//     }

//     std::cout << "Путь:" << std::endl;
//     for (int p : fullPath) {
//         std::cout << p << " ";
//     }
//     std::cout << std::endl;
//     std::cout << "Общая длина пути: " << total_distance << std::endl;

//     return total_distance;
// }


double FindShortestPath(Graph &graph, int start, int end, std::vector<int>& fullPath) {
    int n = graph.number_;
    // вектор посещенных точек
    std::vector<bool> visited(n, false);
    visited[start] = true;
    // вектор пути
    fullPath.clear();
    fullPath.push_back(start);
    /* Стек из точек, наблюдаемых по пути движения
    будем добавлять точки и их соседей
    Стек нужен, если настанет момент, когда все соседи
    текущей точки посещены -> Мы возьмем первую точку из стека,
    так как она будет самой ближайшей к current и проверим есть ли у нее
    непосещенные соседи
    */

    auto contains = [](vector<int>& v, int index){
        for(auto n : v){
            if(n == index){ return true;}
        }
        return false;
    };

    std::vector<int> back;
    int back_size = 1;
    back.push_back(start);

    double total_distance = 0.0;
    int current = start;

    for (int step = 1; step < n; ++step) {
        double min_dist = std::numeric_limits<double>::infinity();
        int next_point = -1;
        // поиск ближайшего соседа current точки
        for (auto neighbour:  graph.points_[current].neighbours_) {
            //add to q neighbours of current
            if (!visited[neighbour]) {  
                // if([std::find(back.begin(), back.end(), neighbour) != back.end()]){
                if(!contains(back, neighbour)){
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
        // если нет свободных ближайших точек
        // то попытаемся найти ближайшего соседа
        // рассматривая точки из стека. Проверить всех соседей
        // каждой точки из стека. Если все посещены, то удалить точку из стека
        if (next_point == -1) {
            bool found = false;
            while(back_size > 0 && !found){
                for(auto neighbour:  graph.points_[back_size-1].neighbours_){
                    if(visited[neighbour] == false){
                        next_point = neighbour;
                        back.push_back(next_point);
                        back_size += 1;
                        found = true;
                        break;
                    }
                }
                if(next_point == -1){
                    std::cout << "s: ";
                    for(int i = 0; i < back_size; ++i){
                        std::cout << back[i] << " ";
                    } 
                    std::cout << std::endl;
                    back.pop_back();
                    back_size -= 1;
                }
            }
        }else{
            std::cout << "f: ";
            for(int i = 0; i < back_size; ++i) {
                std::cout << back[i] << " ";
            }
            std::cout << std::endl;
            fullPath.push_back(next_point);
            visited[next_point] = true;
            current = next_point;
            continue;
        }
        
        if(next_point == -1){
            std::cout << "Error: No available point to visit." << std::endl;
            break;
        }
        // ищем путь с текущей точки до ближайшей непосещенной точки
        // с промежуточными (возможно посещенными) точками
        std::vector<int> subPath = BFS(current, next_point, graph);
        if (subPath.empty()) {
            std::cout << "Error: Path to point " << next_point << " unreachable." << std::endl;
            break;
        }

        for (size_t i = 1; i < subPath.size(); ++i) {
            total_distance += graph.distances_[subPath[i - 1]][subPath[i]];
            if (!visited[subPath[i]]) {
                visited[subPath[i]] = true;
            }
            fullPath.push_back(subPath[i]);
        }
        current = next_point;
    }

    if (current != end) {
        std::vector<int> subPath = BFS(current, end, graph);
        if (!subPath.empty()) {
            for (size_t i = 1; i < subPath.size(); ++i) {
                total_distance += graph.distances_[subPath[i - 1]][subPath[i]];
                if (!visited[subPath[i]]) {
                    visited[subPath[i]] = true;
                    
                }
                fullPath.push_back(subPath[i]);
            }
        }
    }

    std::cout << "Path:" << std::endl;
    for (int p : fullPath) {
        std::cout << std::setw(3) << p << " ";
    }
    std::cout << std::endl;

    std::cout << "Visited:" << std::endl;
    for(auto visit : visited){
        std::cout << visit << " ";
    }
    std::cout << std::endl;
    std::cout << "Total lengh of path: " << total_distance << std::endl;

    return total_distance;
}


/*
std::vector<int> BFS(int start, int end, const Graph &graph) {
    int n = graph.points_.size();
    std::vector<int> parent(n, -1);
    std::vector<bool> visited(n, false);
    std::queue<int> q;

    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        if (current == end)
            break;

        for (int neighbor : graph.points_[current].neighbours_) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                parent[neighbor] = current;
                q.push(neighbor);
            }
        }
    }

    std::vector<int> path;
    for (int v = end; v != -1; v = parent[v]) {
        path.push_back(v);
    }
    std::reverse(path.begin(), path.end());

    if (path[0] != start)
        return {};
    return path;
}

double FindShortestPath(Graph &graph, int start, int end) {
    int n = graph.points_.size();
    std::vector<bool> visited(n, false);
    visited[start] = true;

    std::vector<int> path;
    path.push_back(start);

    double totalDistance = 0.0;
    int current = start;

    for (int step = 1; step < n; ++step) {
        double minDist = std::numeric_limits<double>::infinity();
        int nextPoint = -1;

        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                double dist = graph.distances_[current][i];
                if (dist < minDist) {
                    minDist = dist;
                    nextPoint = i;
                }
            }
        }

        if (nextPoint == -1) {
            std::cout << "Ошибка: Нет доступных точек для посещения." << std::endl;
            break;
        }

        std::vector<int> subPath = BFS(current, nextPoint, graph);
        if (subPath.empty()) {
            std::cout << "Ошибка: Путь до точки " << nextPoint << " недостижим." << std::endl;
            break;
        }

        for (size_t i = 1; i < subPath.size(); ++i) {
            totalDistance += graph.distances_[subPath[i - 1]][subPath[i]];
            if (!visited[subPath[i]]) {
                visited[subPath[i]] = true;
                path.push_back(subPath[i]);
            }
        }
        current = nextPoint;
    }

    if (current != end) {
        std::vector<int> subPath = BFS(current, end, graph);
        if (!subPath.empty()) {
            for (size_t i = 1; i < subPath.size(); ++i) {
                totalDistance += graph.distances_[subPath[i - 1]][subPath[i]];
                if (!visited[subPath[i]]) {
                    visited[subPath[i]] = true;
                    path.push_back(subPath[i]);
                }
            }
        }
    }

    std::cout << "Путь:" << std::endl;
    for (int p : path) {
        std::cout << p << " ";
    }
    std::cout << std::endl;
    std::cout << "Общая длина пути: " << totalDistance << std::endl;

    return totalDistance;
}

*/