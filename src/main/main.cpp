#include "../lib/MyParser.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <cmath>
#include <fstream>
#include <iostream>

using namespace sf;

bool parse_circle(ShapeData circle);

bool parse_triangle(ShapeData triangle);

bool parse_polygon(ShapeData polygon);

void error_check(
        int rad, int c_x, int c_y, int color_r, int color_g, int color_b);

void program_stop(int type_error);

void trinagle_error_check(std::vector<coordinate> v);

void polygon_error_check(int size, std::vector<coordinate> v);
int main(int args, char* argv[])
{
    std::string line;

    ShapeData circleData[10];
    int countCircles = 0;

    ShapeData triangleData[10];
    int countTriangles = 0;

    ShapeData polygonData[10];
    int countPolygons = 0;

    bool entered = false;

    if (args != 2) {
        char ch = 'a';
        while (ch != 'q') {
            std::cout << "Введите букву 'w', если хотите добавь "
                         "фигуру\nВведите букву "
                         "'h', если вам нужна справка по работе с "
                         "программой\nВведите "
                         "букву 'q', если хотите прекратить ввод фигур"
                      << std::endl;
            std::cin >> ch;
            std::cin.ignore();
            entered = true;
            if (ch == 'w') {
                std::cout << "Введите фигуру и ее параметры в формате wkt: ";
                std::getline(std::cin, line);
                if (line[0] == 'c') {
                    circleData[countCircles] = parseShapeData(line);
                    if (parse_circle(circleData[countCircles])) {
                        countCircles++;
                    };
                } else if (line[0] == 't') {
                    triangleData[countTriangles] = parseShapeData(line);
                    if (parse_triangle(triangleData[countTriangles])) {
                        countTriangles++;
                    };
                } else if (line[0] == 'p') {
                    polygonData[countPolygons] = parseShapeData(line);
                    if (parse_polygon(polygonData[countPolygons])) {
                        countPolygons++;
                    }
                }
            } else if (ch == 'h') {
                std::cout << "\n\nПример ввода фигур в формате wkt:\n\ncircle "
                             "(1200 "
                             "600, 140.0, 80 0 40)"
                             "\ntriangle (300 450, 800 300, 130 60, 0 200 180)"
                             "\npolygon (6, 300 450, 450 600, 600 750, 750 "
                             "600, 900 450, 600 150, 255 255 255)"
                          << std::endl;
                std::cout
                        << "\nВ приведенном примере рассмотрим фигуры по "
                           "порядку:\n\ncircle - окружность (координата по x  "
                           "координата по y, радиус окружности, цвет в формате "
                           "RGB)\n\ntriangle - треугольник (координата по x "
                           "(первой вершины) координата по y(первой вершины), "
                           "координата по x (второй вершины)\nкоордината по y "
                           "(второй вершины), координата по x (третьей "
                           "вершины) координа по y (третьей вершины), цвет в "
                           "формате RGB)\n\npolygon - полигон или многоульник "
                           "(количество вершин-n, координата по x(n-вершины) "
                           "координата по y(n-вершины), цвет в формате RGB)\n\n"
                        << std::endl;
                std::cout
                        << "Код цвета граничит в значеньях от 0 до 255, "
                           "включая границы.\nКоординаты не могут иметь "
                           "отрицательные значения\nРазрешение окна 1500 x 900 "
                           "точек.\nВвод в программу осуществляется при "
                           "помощи печатного ввода или указания текстового "
                           "файла,\nкак аргумент при запуске "
                           "программы (либо текстовый файл находится в "
                           "директории с программой,\nлибо вы указываете "
                           "путь до этого файла при запуске программы)\n\n"
                        << std::endl;
            } else if (ch == 'q') {
                break;
            }
        }
    }
    std::ifstream file(argv[1]);

    if (!file.is_open() & !entered) {
        std::cout << "Ошибка: файл не найден" << std::endl;
        return 1;
    }

    while (std::getline(file, line)) {
        if (line[0] == 'c') {
            circleData[countCircles] = parseShapeData(line);
            if (parse_circle(circleData[countCircles])) {
                countCircles++;
            };
        } else if (line[0] == 't') {
            triangleData[countTriangles] = parseShapeData(line);
            if (parse_triangle(triangleData[countTriangles])) {
                countTriangles++;
            };
        } else if (line[0] == 'p') {
            polygonData[countPolygons] = parseShapeData(line);
            if (parse_polygon(polygonData[countPolygons])) {
                countPolygons++;
            }
        }
        std::cout << "\nНажмите \"Enter\" чтобы продолжить" << std::endl;
        getchar();
    }

    RenderWindow window(
            VideoMode(1500, 900), L"trpo_lab_voronov", Style::Titlebar);

    CircleShape circle(0);

    CircleShape triangle(100);

    for (int i = 0; i < countCircles; i++) {
        circle.setPosition(circleData[i].center.x, circleData[i].center.y);
        circle.setRadius(circleData[i].radius);
        circle.setFillColor(sf::Color(
                circleData[i].color.r,
                circleData[i].color.g,
                circleData[i].color.b));
        window.draw(circle);
    }

    ConvexShape triangleShape;
    triangleShape.setPointCount(3);
    Vector2f points[3];
    for (int i = 0; i < countTriangles; i++) {
        for (int j = 0; j < 3; j++) {
            points[j].x = triangleData[i].vertices[j].x;
            points[j].y = triangleData[i].vertices[j].y;
            triangleShape.setPoint(j, points[j]);
            triangleShape.setFillColor(sf::Color(
                    triangleData[i].color.r,
                    triangleData[i].color.g,
                    triangleData[i].color.b));
        }
        window.draw(triangleShape);
    }

    ConvexShape polygon;
    for (int i = 0; i < countPolygons; i++) {
        for (int j = 0; j < polygonData[i].vertices.size(); i++) {
            polygon.setPointCount(polygonData[i].vertices.size());
            for (int k = 0; k < polygonData[i].vertices.size(); k++) {
                polygon.setPoint(
                        k,
                        Vector2f(
                                polygonData[i].vertices[k].x,
                                polygonData[i].vertices[k].y));
            }
            polygon.setFillColor(sf::Color(
                    polygonData[i].color.r,
                    polygonData[i].color.g,
                    polygonData[i].color.b));
            window.draw(polygon);
        }
    }

    window.display();

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
    }
    return 0;
}

void error_check(
        int rad, int c_x, int c_y, int color_r, int color_g, int color_b)
{
    if (rad < 0) {
        program_stop(0);
    }
    if (c_x < 0) {
        program_stop(1);
    }
    if (c_y < 0) {
        program_stop(2);
    }
    if (color_r < 0 || color_g < 0 || color_b < 0) {
        program_stop(3);
    }
    if (color_r > 255 || color_g > 255 || color_b > 255) {
        program_stop(4);
    }
}

void program_stop(int type_error)
{
    switch (type_error) {
    case 0:
        std::cout << "Ошибка ввода: радиус не может быть меньше нуля"
                  << std::endl;
        exit(0);
        break;
    case 1:
        std::cout << "Ошибка ввода: координата X не может быть меньше нуля"
                  << std::endl;
        exit(0);
        break;
    case 2:
        std::cout << "Ошибка ввода: координата Y не может быть меньше нуля"
                  << std::endl;
        exit(0);
        break;
    case 3:
        std::cout << "Ошибка ввода: код цвета не может быть меньше нуля"
                  << std::endl;
        exit(0);
        break;
    case 4:
        std::cout << "Ошибка ввода: код цвета не может быть больше 255"
                  << std::endl;
        exit(0);
        break;
    }
}

void trinagle_error_check(std::vector<coordinate> v)
{
    for (int i = 0; i < 3; i++) {
        if (v[i].x < 0) {
            program_stop(1);
        }
        if (v[i].y < 0) {
            program_stop(2);
        }
    }
}

void polygon_error_check(int size, std::vector<coordinate> v)
{
    for (int i = 0; i < size; i++) {
        if (v[i].x < 0) {
            program_stop(1);
        }
        if (v[i].y < 0) {
            program_stop(2);
        }
    }
}

bool parse_circle(ShapeData circle)
{
    error_check(
            circle.radius,
            circle.center.x,
            circle.center.y,
            circle.color.r,
            circle.color.g,
            circle.color.b);
    std::cout << "Проверка на корректность введенных данных прошла "
                 "успешна..."
              << std::endl;
    std::cout << "\nПериметр вашей окружности: "
              << float(2.0 * 3.14 * circle.radius) << std::endl;
    std::cout << "\nПлощадь ваше окружности: "
              << float(3.14 * (circle.radius * circle.radius)) << std::endl;
    return true;
}

bool parse_triangle(ShapeData triangle)
{
    trinagle_error_check(triangle.vertices);
    error_check(
            20, 30, 30, triangle.color.r, triangle.color.g, triangle.color.b);
    std::cout << "Проверка на корректность введенных данных прошла "
                 "успешна...\n"
              << std::endl;
    float a = std::sqrt(
            std::pow(triangle.vertices[1].x - triangle.vertices[0].x, 2)
            + std::pow((triangle.vertices[1].y - triangle.vertices[0].y), 2));

    float b = std::sqrt(
            std::pow(triangle.vertices[2].x - triangle.vertices[1].x, 2)
            + std::pow((triangle.vertices[2].y - triangle.vertices[1].y), 2));
    float c = std::sqrt(
            std::pow(triangle.vertices[2].x - triangle.vertices[0].x, 2)
            + std::pow((triangle.vertices[2].y - triangle.vertices[0].y), 2));
    std::cout << "Периметр вашего треугольник: " << (a + b + c) << std::endl;
    float s = (a + b + c) / 2;
    std::cout << "\nПлощадь вашего треугольника: "
              << (s * (s - a) * (s - b) * (s - c)) / 1000000 << std::endl;
    return true;
}

bool parse_polygon(ShapeData polygon)
{
    polygon_error_check(polygon.vertices.size(), polygon.vertices);
    error_check(
            30, 100, 100, polygon.color.r, polygon.color.g, polygon.color.b);
    std::cout << "Проверка на корректность введенных данных прошла "
                 "успешна...\n"
              << std::endl;
    int* arr = new int(polygon.vertices.size());
    for (int i = 0; i < polygon.vertices.size(); i++) {
        arr[i] = std::sqrt(
                std::pow(polygon.vertices[1].x - polygon.vertices[0].x, 2)
                + std::pow(polygon.vertices[1].y - polygon.vertices[0].y, 2));
    }
    size_t per = 0;
    for (int i = 0; i < polygon.vertices.size(); i++) {
        per += arr[i];
    }
    std::cout << "Периметр вашего полигона: " << per << std::endl;
    std::cout << "\nПлощадь вашего полигона: "
              << (per * (per - arr[0]) * (per - arr[1]) * (per - arr[2]))
                    / 1000000
              << std::endl;
    return true;
}