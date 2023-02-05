#pragma once
#ifndef SHAPE_HPP
#define SHAPE_HPP

/*
    Name: 
        Simple Shape namespace

    Author:
        ntvs
        02-01-2023

    Purpose:
        To rasterize various mathematical phenomena onto a screen

    Notes:
        This namespace also contains functions to draw/rasterize some
        mathematical descriptions of lines and shapes. Lines are drawn naively according
        to the function y=mx+b and circles plotted based on (r)^2=(x+origin_x)^2+(y+origin_y)^2.
        Circles are not yet rasterized properly. Triangles are drawn simply by drawing 3 lines.
        
    Implementation:
        Shape.cpp 
*/

namespace Shape {
    //"Vector" structs to represent "points"
    struct Vec2 {
        double x = 0.0;
        double y = 0.0;
    };

    struct Vec3 {
        double x = 0.0;
        double y = 0.0;
        double z = 0.0;
    };

    //Temporary vertical line function
    void vline(const Vec2& p1, const Vec2& p2, const unsigned int& color, Screen& screen);

    //Draws a line given 2 points to a screen using the naive line algorithm
    //Last point not included
    void line(const Vec2& p1, const Vec2& p2, const unsigned int& color, Screen& screen);

    //Plots some points for given circle radius and origin to a screen
    void circle (const Vec2& center, const float radius, const unsigned int color, Screen& screen);

    //Draws a triangle using the naive line algorithm to a screen
    //Wireframe triangle
    //Points must be defined in clockwise order
    void triangle(const Vec2& p1, const Vec2& p2, const Vec2& p3, const unsigned int& color, Screen& screen);
}

#endif