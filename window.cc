/*
g++ window.cc graph.cc -lsfml-graphics -lsfml-window -lsfml-system

*/
#include <SFML/Graphics.hpp>
#include "header.h"



const double WINDOW_SIZE = 800;


void Run(Graph& g){
    // Инициализация SFML
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Graph");
    window.setFramerateLimit(30);

    // Создаем шрифт
    sf::Font font; // to add text
    font.loadFromFile("CalibriSchool.ttf");
    if(!font.loadFromFile("CalibriSchool.ttf")){ // if file not found
        std::cout << "File not found" << std::endl;
    }
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(10);
    text.setFillColor(sf::Color::Black);
    int circle_raduis_ = WINDOW_SIZE/100;

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

        // Рисуем ребра
        for (int i = 0; i < g.points_.size(); ++i){
            double x = WINDOW_SIZE / 2 + g.points_[i].x_;
            double y = WINDOW_SIZE / 2 + g.points_[i].y_;
            
            for (int neighbor_index : g.points_[i].neighbours_) {
                auto& neighbor = g.points_[neighbor_index];
                sf::Vertex line[] = {
                    sf::Vertex(sf::Vector2f(x + circle_raduis_, y + circle_raduis_), sf::Color::Blue),
                    sf::Vertex(sf::Vector2f(WINDOW_SIZE / 2 + neighbor.x_ + circle_raduis_, WINDOW_SIZE / 2 + neighbor.y_ + circle_raduis_), sf::Color::Blue)
                };
                window.draw(line, 2, sf::Lines);
            }
        }

        // Рисуем точки
        for (int i = 0; i < g.points_.size(); ++i) {
            
            sf::CircleShape pointShape(circle_raduis_);
            double x = WINDOW_SIZE / 2 + g.points_[i].x_;
            double y = WINDOW_SIZE / 2 + g.points_[i].y_;
            pointShape.setPosition(x, y);
            pointShape.setFillColor(sf::Color::Red);
            window.draw(pointShape);

            // // Рисуем ребра
            // for (int neighbor_index : g.points_[i].neighbours_) {
            //     auto& neighbor = g.points_[neighbor_index];
            //     sf::Vertex line[] = {
            //         sf::Vertex(sf::Vector2f(x + circle_raduis_, y + circle_raduis_), sf::Color::Blue),
            //         sf::Vertex(sf::Vector2f(WINDOW_SIZE / 2 + neighbor.x_ + circle_raduis_, WINDOW_SIZE / 2 + neighbor.y_ + circle_raduis_), sf::Color::Blue)
            //     };
            //     window.draw(line, 2, sf::Lines);
            // }            

            // // добавим номер точки
            // text.setString(std::to_string(i));
            // // text.setPosition(x + circle_raduis_/2, y + circle_raduis_/2);
            // text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
            // text.setPosition(x + circle_raduis_, y + circle_raduis_);
            // window.draw(text);
        }

        // добавим номер точки
        for (int i = 0; i < g.points_.size(); ++i) {
            double x = WINDOW_SIZE / 2 + g.points_[i].x_;
            double y = WINDOW_SIZE / 2 + g.points_[i].y_;

            text.setString(std::to_string(i));
            // text.setPosition(x + circle_raduis_/2, y + circle_raduis_/2);
            text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
            text.setPosition(x + circle_raduis_, y + circle_raduis_);
            window.draw(text);
        }

        // добавим цену
        sf::Text text; // to add text
        text.setFont(font);
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::Black);
        text.setString("Price" + std::to_string(g.price_) + "$");
        text.setPosition(10, 10);
        window.draw(text);

        window.display();
    }
}