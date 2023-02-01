#include <stdint.h>
#include "Screen.hpp"
#include "Shape.hpp"

//Temporary vertical line function
void Shape::vline(const Vec2& p1, const Shape::Vec2& p2, const uint32_t& color, Screen& screen) {
    Vec2 top, bot;
    if (p1.y > p2.y) {
        top = p2;
        bot = p1;
    } else {
        top = p1;
        bot = p2;
    }

    for (int y = top.y; y <= bot.y; y++) {
        screen.pixels[ (y*screen.width) + (int)p1.x ] = color;
    }
};

//Last point not included
void Shape::line(const Vec2& p1, const Vec2& p2, const uint32_t& color, Screen& screen) {

    //Slope target
    float m = (p2.y - p1.y)/(p2.x - p1.x);

    //Iterate through the screen
    for (int xValue = p1.x; xValue < p2.x; xValue++) {
        int yValue = m*(xValue-p1.x)+p1.y;
        if ((yValue*screen.width) + xValue >= screen.size)
            return;

        screen.pixels[ (yValue*screen.width) + xValue ] = color;
    }
}

//Plots some points for given circle radius and origin
void Shape::circle (const Vec2& center, const float radius, const uint32_t color, Screen& screen) {
    for (int y = 0; y < screen.height; y++) {
        for (int x = 0; x < screen.width; x++) {
            
            //std::cout << (y-center.y)*(y-center.y) + (x-center.x)*(x-center.x) << ' ' << radius*radius << ' ' << ((y-center.y)*(y-center.y) + (x-center.x)*(x-center.x) == radius*radius) << '\n';

            if ((y-center.y)*(y-center.y) + (x-center.x)*(x-center.x) == radius*radius)
                screen.pixels[ y*screen.width+x ] = color;

        }
    }
}

//Wireframe triangle
//Points must be defined in clockwise order
void Shape::triangle(const Vec2& p1, const Vec2& p2, const Vec2& p3, const uint32_t& color, Screen& screen) {
    line(p1, p2, color, screen);
    line(p2, p3, color, screen);
    line(p1, p3, color, screen);
}