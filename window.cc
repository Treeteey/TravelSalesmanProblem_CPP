/*
g++ window.cc graph.cc -lsfml-graphics -lsfml-window -lsfml-system

*/

#include <SFML/Graphics.hpp>
#include "graph.h"

const double WINDOW_SIZE = 800;
void Run(Graph& g);

int main(){
    double radius = 350; // Радиус окружности в пикселях
    int number = 100;
    double price = 10;
    Graph g(number, radius, price);
    Run(g);  
    return 0;
}


void Run(Graph& g){
    // Инициализация SFML
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Graph");
    window.setFramerateLimit(60);

    // Основной цикл
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::White);

        // Рисуем круг
        sf::CircleShape circle(g.radius_);
        circle.setOrigin(g.radius_, g.radius_);
        circle.setPosition(WINDOW_SIZE / 2, WINDOW_SIZE / 2);
        circle.setFillColor(sf::Color(240, 240, 240));
        circle.setOutlineThickness(2);
        circle.setOutlineColor(sf::Color::Black);
        window.draw(circle);

        // Рисуем точки и ребра
        for (auto& point : g.points_) {
            sf::CircleShape pointShape(3);
            double x = WINDOW_SIZE / 2 + point.x_;
            double y = WINDOW_SIZE / 2 + point.y_;
            pointShape.setPosition(x, y);
            pointShape.setFillColor(sf::Color::Red);
            window.draw(pointShape);

            // Рисуем ребра
            for (int neighbor_index : point.neighbours_) {
                auto& neighbor = g.points_[neighbor_index];
                sf::Vertex line[] = {
                    sf::Vertex(sf::Vector2f(x + 3, y + 3), sf::Color::Black),
                    sf::Vertex(sf::Vector2f(WINDOW_SIZE / 2 + neighbor.x_ + 3, WINDOW_SIZE / 2 + neighbor.y_ + 3), sf::Color::Black)
                };
                window.draw(line, 2, sf::Lines);
            }
        }
        window.display();
    }
}