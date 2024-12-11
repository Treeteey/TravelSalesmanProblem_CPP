/*
g++ window.cc graph.cc -lsfml-graphics -lsfml-window -lsfml-system

*/


#include "header.h"





void Run(Graph& g, int window_size, std::vector<int>& path) {
    // Инициализация SFML
    sf::RenderWindow window(sf::VideoMode(window_size*1.5, window_size), "Graph");
    window.setFramerateLimit(30);

    // Создаем шрифт
    sf::Font font; // to add text
    font.loadFromFile("CalibriSchool.ttf");
    if(!font.loadFromFile("CalibriSchool.ttf")){ // if file not found
        std::cout << "File not found" << std::endl;
    }
    sf::Text text_points;
    text_points.setFont(font);
    text_points.setCharacterSize(10);
    text_points.setFillColor(sf::Color::Black);

    sf::Text text_cost;
    text_cost.setFont(font);
    text_cost.setCharacterSize(20);
    text_cost.setFillColor(sf::Color::Black);

    int circle_raduis_ = window_size/100;
    int counter = 0;

    std::vector<sf::Color> colors(g.number_, sf::Color::Red);
    colors[path[counter]] = sf::Color::Green;

    // Основной цикл
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }else if(event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::Escape){
                    window.close();
                }else if(event.key.code == sf::Keyboard::Right){
                    if(counter < path.size() - 1){
                        counter++;
                        colors[path[counter]] = sf::Color::Green;   
                    }
                }else if(event.key.code == sf::Keyboard::Left){
                    if(counter > 0){
                        colors[path[counter]] = sf::Color::Red;
                        counter--;
                    }
                }
            }
        }
        window.clear(sf::Color::White);
        // Рисуем круг
        DrawCircle(g, window_size, window);
        // Рисуем ребра
        DrawRibs(g, window, window_size, circle_raduis_);
        // Рисуем точки
        DrawPoints(g, window, window_size, circle_raduis_, colors);
        // Выделяем соседей текущей точки, чтоб видно было куда можно идти
        DrawCurrentNeighbours(g, window, window_size, circle_raduis_, counter, path);
        // Выделяем текущую точку
        DrawCurrentPoint(g, window, window_size, circle_raduis_, counter, path);
        // добавим номер точки
        AddPointsNumber(g, window, window_size, circle_raduis_, text_points);
        // добавим цену
        AddCost(g, window, text_cost);

        text_cost.setString(std::to_string(counter));
        text_cost.setPosition(10, 40);
        window.draw(text_cost);

        DrawColorInfo(g, window, text_cost, circle_raduis_);

        window.display();
    }
}



void DrawCircle(Graph& g, int window_size, sf::RenderWindow& window){
    sf::CircleShape circle(g.radius_);
    circle.setOrigin(g.radius_, g.radius_);
    circle.setPosition(window_size / 2, window_size / 2);
    circle.setFillColor(sf::Color(240, 240, 240));
    circle.setOutlineThickness(2);
    circle.setOutlineColor(sf::Color::Black);
    window.draw(circle);
}


void DrawRibs(Graph& g, sf::RenderWindow& window, 
              int window_size, int circle_raduis_){
    for (int i = 0; i < g.points_.size(); ++i){
        double x = window_size / 2 + g.points_[i].x_;
        double y = window_size / 2 + g.points_[i].y_;
        
        for (int neighbor_index : g.points_[i].neighbours_) {
            auto& neighbor = g.points_[neighbor_index];
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(x + circle_raduis_, y + circle_raduis_), sf::Color::Blue),
                sf::Vertex(sf::Vector2f(window_size / 2 + neighbor.x_ + circle_raduis_, window_size / 2 + neighbor.y_ + circle_raduis_), sf::Color::Blue)
            };
            window.draw(line, 2, sf::Lines);
        }
    }
}

void DrawPoints(Graph& g, sf::RenderWindow& window, 
                int window_size, int circle_raduis_, std::vector<sf::Color>& colors){
    for (int i = 0; i < g.points_.size(); ++i) {        
        sf::CircleShape pointShape(circle_raduis_);
        double x = window_size / 2 + g.points_[i].x_;
        double y = window_size / 2 + g.points_[i].y_;
        pointShape.setPosition(x, y);
        // pointShape.setFillColor(sf::Color::Red);
        pointShape.setFillColor(colors[i]);
        window.draw(pointShape);
    }
}

void AddPointsNumber(Graph& g, sf::RenderWindow& window, 
                    int window_size, int circle_raduis_, sf::Text &text){
    for (int i = 0; i < g.points_.size(); ++i) {
        double x = window_size / 2 + g.points_[i].x_;
        double y = window_size / 2 + g.points_[i].y_;

        text.setString(std::to_string(i));
        // text.setPosition(x + circle_raduis_/2, y + circle_raduis_/2);
        text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
        text.setPosition(x + circle_raduis_, y + circle_raduis_);
        window.draw(text);
    }
}

void AddCost(Graph& g, sf::RenderWindow& window, sf::Text &text){
    text.setString("Price" + std::to_string(g.price_) + "$");
    text.setPosition(10, 10);
    window.draw(text);
}


void DrawCurrentNeighbours(Graph& g, sf::RenderWindow& window, 
                           int window_size, int circle_raduis_,
                           int counter, std::vector<int> &path) {
    for (auto neighbour : g.points_[path[counter]].neighbours_){
        sf::CircleShape pointShape(circle_raduis_* 1.2);
        double x = window_size / 2 + g.points_[neighbour].x_;
        double y = window_size / 2 + g.points_[neighbour].y_;
        pointShape.setPosition(x, y);
        // pointShape.setFillColor(sf::Color::Red);
        pointShape.setFillColor(sf::Color(128, 128, 128));
        window.draw(pointShape);
    }   
}

void DrawCurrentPoint(Graph& g, sf::RenderWindow& window, 
                      int window_size, int circle_raduis_, 
                      int counter, std::vector<int> &path){
    sf::CircleShape pointShape(circle_raduis_* 1.2);
    double x = window_size / 2 + g.points_[path[counter]].x_;
    double y = window_size / 2 + g.points_[path[counter]].y_;
    pointShape.setPosition(x, y);
    pointShape.setFillColor(sf::Color(0, 255,255));
    window.draw(pointShape);
}

void DrawColorInfo(Graph& g, sf::RenderWindow& window, 
                   sf::Text &text, double circle_raduis_){
    sf::CircleShape pointShape(circle_raduis_* 1.2);
    std::vector<sf::Color> colors = {sf::Color::Red, sf::Color::Green, sf::Color(0, 255,255), sf::Color(128, 128, 128)};
    std::vector<std::string> color_names = {"Not visited", "Visited", "Current", "Neighbours"};
    for (int i = 0; i < colors.size(); ++i) {
        text.setString(color_names[i]);
        text.setPosition(30, 40 + i * 20);
        window.draw(text);
        pointShape.setPosition(10, 40 + i * 20);
        pointShape.setFillColor(colors[i]);
        window.draw(pointShape);
    }
}