/*
    Name: 
        Simple graphics functions driver program

    Author:
        ntvs
        02-01-2023

    Purpose:
        To demonstrate working visualization of certain mathematical functions
        To demonstrate working rasterization of those mathematical phenomena
*/

//Includes
#include <iostream>
#include "Screen.hpp"
#include "Shape.hpp"

//Definitions
#define COLOR_BG 0xff111111u //0xffffc600u

//Library tests - functions which call routines in order to test the library's functions
namespace LibTest {
    //Test filling the screen with the background color
    void BGFill(Screen& screen) {
        screen.fillBG(COLOR_BG);
        screen.toPPM("test_BGFill.ppm");
        std::cout << "BGFill complete\n";
    }

    //Test filling screen with pure RGB
    void RGB(Screen& screen) {
        screen.fillBG(0xffff0000u);
        screen.toPPM("test_Channel_Red.ppm");

        screen.fillBG(0xff00ff00u);
        screen.toPPM("test_Channel_Green.ppm");

        screen.fillBG(0xff0000ffu);
        screen.toPPM("test_Channel_Blue.ppm");
        std::cout << "RGB complete\n";
    }

    //Test simple vertical line
    void VLine(Screen& screen) {
        screen.fillBG(COLOR_BG);

        Shape::vline({150.6f, 250.5}, {150.8, 30.3}, 0xffff0000u, screen);

        screen.toPPM("test_VLine.ppm");
        std::cout << "VLine complete\n";
    }

    //Test naive line algorithm
    void Line(Screen& screen) {
        screen.fillBG(COLOR_BG);

        Shape::line({2.0f, 8.0f}, {4.0f, 1.0f}, 0xffc3ff00u, screen);
        Shape::line({4.0f, 1.0f}, {11.0f, 5.0f}, 0xffc3ff00u, screen);
        Shape::line({2.0f, 8.0f}, {11.0f, 5.0f}, 0xffc3ff00u, screen);

        screen.toPPM("test_Line.ppm");
        std::cout << "Line complete\n";
    }

    //Test creating triangle with naive line algorithm
    void TriangleWireFrame(Screen& screen) {
        screen.fillBG(COLOR_BG);

        Shape::triangle({100.0f, 310.0f}, {320.0f, 70.0f}, {570.0f, 190.0f}, 0xff0000ffu, screen);
        Shape::triangle({95.0f, 305.0f}, {315.0f, 65.0f}, {565.0f, 185.0f}, 0xff00ff00u, screen);
        Shape::triangle({90.0f, 300.0f}, {310.0f, 60.0f}, {560.0f, 180.0f}, 0xffff0000u, screen);

        screen.toPPM("test_TriangleWireFrame.ppm");
        std::cout << "TriangleWireFrame complete\n";
    }

    //Test filling screen with linear gradient top -> bottom
    void BGFillGradient(Screen& screen) {
        screen.fillBGgradient(0xff0000ffu, 0xffff0000u);
        screen.toPPM("test_BGFillGradient.ppm");
        std::cout << "BGFillGradient complete\n";
    }

    //Test making an image using triangles and gradients on the screen
    void Triforce(Screen& screen) {

        screen.fillBGgradient(0xff101b3bu, 0xff0000ffu);
        
        Shape::triangle({(screen.width/(float)3), (screen.height/(float)2)}, {(screen.width/(float)2), 0.0f}, {(screen.width*2/(float)3), (screen.height/(float)2)}, 0xffff0000u, screen);
        Shape::triangle({(screen.width/(float)5), (float)screen.height-1}, {(screen.width/(float)3), (screen.height/(float)2)}, {(screen.width/(float)2), (float)screen.height}, 0xffb657ffu, screen);
        Shape::triangle({(screen.width/(float)2), (float)screen.height-1}, {(screen.width*2/(float)3), (screen.height/(float)2)}, {(screen.width*4/(float)5), (float)screen.height-1}, 0xff00ff00u, screen);
        
        screen.toPPM("test_Triforce.ppm");
        std::cout << "Triforce complete\n";

    }

    //Test very basic plotting of points on screen according to mathematical description of a circle
    void Circle(Screen& screen) {
        screen.fillBG(0xff000022u);

        Shape::circle({screen.width/2.0f, screen.height/2.0f}, 100.0f, 0xffc3ff00u, screen);

        screen.toPPM("test_Circle.ppm");
        std::cout << "Circle complete\n";
    }

    //Execute all tests
    void RunAll() {

        Screen screen;

        BGFill(screen);
        RGB(screen);
        VLine(screen);
        Line(screen);
        TriangleWireFrame(screen);
        BGFillGradient(screen);
        Triforce(screen);
        Circle(screen);

        std::cout << "Done\n";
    }
}

//Entrypoint
int main() {
    LibTest::RunAll();
    std::cin.get();
    return 0;
}