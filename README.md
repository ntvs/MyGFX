# MyGFX
Simple graphics programming done in order to help me understand C, C++ and the inner workings of computer graphics.
This repository contains:

## Main.cpp
Driver program to test functionality of graphics functions
Includes namespace LibTest to conduct these tests

## Screen.hpp & Screen.cpp
Screen class which represents a "screen" as an array and can convert that screen to an image.
This class also contains some functions to fill the entire array's background or to create a linear gradient. Currently, the screen can only be converted to the PPM image format. Includes the class Screen.

## Shape.hpp & Shape.cpp
Functions which rasterize mathematical descriptions of basic geometry.
Lines are drawn naively according to the function y=mx+b and circles plotted based on (r)^2=(x+origin_x)^2+(y+origin_y)^2. Circles are not yet rasterized properly. Triangles are drawn simply by drawing 3 lines. Includes the namespace Shape.

# Classes/namespaces
Full documentation of each can be found within the header/implementation files
## class Screen
### Public instance variables
```c++
uint32_t width
uint32_t height
uint32_t size
uint32_t* pixels
```
        
### Public constructors & destructor
```c++
Screen();
Screen(uint32_t& w, uint32_t& h);
~Screen();
```

### Public functions
```c++
uint8_t colorGetRed(const uint32_t& color);
uint8_t colorGetGreen(const uint32_t& color);
uint8_t colorGetBlue(const uint32_t& color);
uint8_t colorGetAlpha(const uint32_t& color);
void toPPM(const char* name);
void fillBG(uint32_t color);
void fillBGgradient(const uint32_t& top, const uint32_t& bottom);
```

## namespace Shape
### Structs
```c++
struct Vec2 {
    float x = 0.0f;
    float y = 0.0f;
};

struct Vec3 {
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
};
```

### Functions
```c++
void vline(const Vec2& p1, const Vec2& p2, const uint32_t& color, Screen& screen);
void line(const Vec2& p1, const Vec2& p2, const uint32_t& color, Screen& screen);
void circle (const Vec2& center, const float radius, const uint32_t color, Screen& screen);
void triangle(const Vec2& p1, const Vec2& p2, const Vec2& p3, const uint32_t& color, Screen& screen);
```

## namespace LibTest
### Functions
```c++
void BGFill(Screen& screen);
void RGB(Screen& screen);
void VLine(Screen& screen);
void Line(Screen& screen);
void TriangleWireFrame(Screen& screen);
void BGFillGradient(Screen& screen);
void Triforce(Screen& screen);
void Circle(Screen& screen);
void RunAll();
```