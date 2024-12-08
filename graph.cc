/*
Случайным образом задаются сто точек точки внутри окружности. 
Соединить их таким образом, чтобы каждая точка была соединена
как минимум с двумя соседними, как максимум - с шестью.

Теперь представим, что мы путешествуем из первой точки в какую-то
(задаётся пользователем). Но мы хотим посетить все точки и потратить
как можно меньше денег. Скажем, единица расстояния будет стоить 10 USD. 
Найти путь, который будет стоить минимум (или близкое к нему количество) денег.

В качестве результата хотелось бы видеть граф, построенный из точек. 
Стоимости переходов. Найденный путь. 
Будет плюсом, если сможете доказать правильность решения
*/

#include "graph.h"


int RandomInt(int min, int max){
    static std::default_random_engine e;
    static std::uniform_int_distribution<> dis(min, max);
    return dis(e);
}


void Graph::CreatePoints(double radius, int count){
    int temp = count;

    static std::default_random_engine e;
    static std::uniform_real_distribution<> dis(-radius, radius);

    while(temp > 0){
        double x = dis(e);
        double y = dis(e);
        if (x * x + y * y <= radius * radius) {
            points_.push_back(Point(x, y));
            temp--;    
        }            
    }
}

double Graph::Distance(const Point& a, const Point& b){
    return sqrt((a.x_ - b.x_) * (a.x_ - b.x_) + (a.y_ - b.y_) * (a.y_ - b.y_));
}

void Graph::CreateNeighbours(int min_neighbors, int max_neighbors){
    for (int i = 0; i < points_.size(); ++i) {
        static std::default_random_engine e;
        static std::uniform_int_distribution<> dis(0, points_.size() - 1);
        static std::uniform_int_distribution<> num(min_neighbors, min_neighbors);

        int rand_number_neighbors = num(e);   
        while(points_[i].neighbours_.size() < rand_number_neighbors) {
            int index = dis(e);
            if(points_[i].neighbours_.size() >= max_neighbors){
                break;
            }
            if (i != index 
                && std::find(points_[i].neighbours_.begin(), points_[i].neighbours_.end(), index) == points_[i].neighbours_.end()) {

                points_[i].neighbours_.push_back(index); // Добавляем индекс
                points_[index].neighbours_.push_back(i); // Соседство симметрично
                distances_[i][index] = Distance(points_[i], points_[index]);
            }
        }
        std::cout << i << " neighbors: " << points_[i].neighbours_.size() << std::endl;
    }
    std::cout << std::endl;
}
