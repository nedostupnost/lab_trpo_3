#include "MyParser.h"

ShapeData parseShapeData(const std::string& input)
{
    ShapeData data;
    std::istringstream iss(input);
    std::string typeStr;
    char tmp;
    iss >> typeStr >> tmp;

    if (typeStr == "circle") {
        data.type = ShapeType::Circle;
        data.name = "Circle";
        if (tmp != '(') {
            throw std::invalid_argument("Ошибка: отсуствует символ '('");
        }
        iss >> data.center.x >> data.center.y >> tmp;

        if (tmp != ',') {
            throw std::invalid_argument("Ошибка: отстуствует символ','");
        }

        iss >> data.radius >> tmp;

        if (tmp != ',') {
            throw std::invalid_argument("Ошибка: отстуствует символ','");
        }

        iss >> data.color.r >> data.color.g >> data.color.b >> tmp;

        if (tmp != ')') {
            throw std::invalid_argument("Ошибка: отстуствует символ ')'");
        }
        return data;
    } else if (typeStr == "triangle") {
        data.type = ShapeType::Triangle;
        data.name = "Triangle";
        data.vertices.resize(3);
        if (tmp != '(') {
            throw std::invalid_argument("Ошибка: отсуствует символ '('");
        }
        for (int i = 0; i < 3; i++) {
            iss >> data.vertices[i].x >> data.vertices[i].y >> tmp;
            if (tmp != ',') {
                throw std::invalid_argument("Ошибка: отстуствует символ','");
            }
        }
        iss >> data.color.r >> data.color.g >> data.color.b >> tmp;
        if (tmp != ')') {
            throw std::invalid_argument("Ошибка: отстуствует символ ')'");
        }
        return data;
    } else if (typeStr == "polygon") {
        data.type = ShapeType::Polygon;
        int numVertices;
        data.name = "Polygon";
        if (tmp != '(') {
            throw std::invalid_argument("Ошибка: отсуствует символ '('");
        }
        iss >> numVertices >> tmp;
        if (tmp != ',') {
            throw std::invalid_argument("Ошибка: отстуствует символ','");
        }
        data.vertices.resize(numVertices);
        for (int i = 0; i < numVertices; i++) {
            iss >> data.vertices[i].x >> data.vertices[i].y >> tmp;
            if (tmp != ',') {
                throw std::invalid_argument("Ошибка: отстуствует символ','");
            }
        }
        iss >> data.color.r >> data.color.g >> data.color.b >> tmp;
        if (tmp != ')') {
            throw std::invalid_argument("Ошибка: отстуствует символ ')'");
        }
        return data;
    }
    if (typeStr != "circle" or typeStr != "triangle" or typeStr != "polygon") {
        throw std::invalid_argument(
                "Ошибка: отстуствует ключевое слово \"circle или triangle или "
                "polygon\"");
    }
    return data;
}