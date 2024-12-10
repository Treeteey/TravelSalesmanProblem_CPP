#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include <unordered_set>
#include "header.h"

// Структура для приоритетной очереди
struct Node {
    int point;
    double cost;

    bool operator>(const Node& other) const {
        return cost > other.cost;
    }
};

// Поиск кратчайшего пути через все точки
std::vector<int> FindPathThroughAllPoints(Graph& g, int start) {
    int n = g.number_;
    std::vector<bool> visited(n, false); // Отслеживаем посещённые вершины
    std::vector<int> path;              // Итоговый путь
    double total_cost = 0;

    int current = start;
    path.push_back(current);
    visited[current] = true;

    while (true) {
        double min_distance = std::numeric_limits<double>::infinity();
        int next_point = -1;

        // Ищем ближайшего соседа
        for (int neighbor : g.points_[current].neighbours_) {
            if (visited[neighbor] == false && g.distances_[current][neighbor] > 0 && g.distances_[current][neighbor] < min_distance) {
                min_distance = g.distances_[current][neighbor];
                next_point = neighbor;
            }
        }

        if (next_point == -1) break; // Если нет доступных соседей

        // Добавляем точку в путь
        path.push_back(next_point);
        visited[next_point] = true;
        total_cost += min_distance;
        current = next_point;

        // Если все точки посещены, заканчиваем
        if (std::all_of(visited.begin(), visited.end(), [](bool v) { return v; })) {
            break;
        }
    }

    return path;
}

// Подсчёт полной стоимости пути
double CalculatePathCost(const Graph& g, const std::vector<int>& path) {
    double total_cost = 0.0;
    for (size_t i = 0; i < path.size() - 1; ++i) {
        total_cost += g.distances_[path[i]][path[i + 1]];
    }
    return total_cost * g.price_; // Стоимость в USD
}

// Вывод пути
void PrintPath(const std::vector<int>& path, double cost) {
    std::cout << "Путь: ";
    for (int point : path) {
        std::cout << point << " -> ";
    }
    std::cout << "END" << std::endl;
    std::cout << "Общая стоимость: " << cost << " USD" << std::endl;
}
