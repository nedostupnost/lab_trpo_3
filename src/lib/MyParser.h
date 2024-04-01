#pragma once
#ifndef PARSER_H
#define PARSER_H

#include <sstream>
#include <string>
#include <vector>

struct coordinate {
    double x;
    double y;
};

struct Color {
    int r;
    int g;
    int b;
};

enum class ShapeType { Circle, Triangle, Polygon };

struct ShapeData {
    ShapeType type;
    std::string name;
    coordinate center;
    double radius;
    std::vector<coordinate> vertices;
    Color color;
};

ShapeData parseShapeData(const std::string& input);

#endif
