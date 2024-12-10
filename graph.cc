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

#include "header.h"


int RandomInt(int min, int max){
    static std::default_random_engine e;
    static std::uniform_int_distribution<> dis(min, max);
    return dis(e);
}


void Graph::CreatePoints(double radius, int count){
    int temp = count;    

    while (temp > 0) {
        std::random_device rd;
        std::mt19937 e(rd());
        std::uniform_real_distribution<> dis(-radius_, radius_);

        double x = dis(e);
        double y = dis(e);

        // Optional: Recheck to ensure the point is within the circle
        if ((x * x + y * y) <= (radius * radius)) {
            points_.push_back(Point(x, y));
            temp--;
        }
    }
}

double Graph::Distance(const Point& a, const Point& b){
    return sqrt((a.x_ - b.x_) * (a.x_ - b.x_) + (a.y_ - b.y_) * (a.y_ - b.y_));
}

void Graph::CreateNeighbours(int min_neighbors, int max_neighbors) {
    std::random_device rd;
    std::mt19937 e(rd());
    std::uniform_int_distribution<> dis(0, points_.size() - 1);
    std::uniform_int_distribution<> dis_int(min_neighbors, max_neighbors);

    for (int i = 0; i < points_.size(); ++i) {
        // Случайное число соседей для текущей точки
        // int rand_number_neighbors = RandomInt(min_neighbors, max_neighbors);
        int rand_number_neighbors = dis_int(e);
        std::cout << rand_number_neighbors << std::endl;

        while (points_[i].neighbours_.size() < rand_number_neighbors) {
            int index = dis(e);
            if (i != index // Исключаем саму точку
                && points_[index].neighbours_.size() < max_neighbors) { // Проверяем, что индекс ещё не добавлен
                // Добавляем связь симметрично
                points_[i].neighbours_.push_back(index);
                points_[index].neighbours_.push_back(i);;
            }
        }
    }
}



void Graph::FillDistances(){
    for(int i = 0; i < number_; i++){
        for(int j = 0; j < number_; j++){
            distances_[i][j] = Distance(points_[i], points_[j]);
        }
    }
}