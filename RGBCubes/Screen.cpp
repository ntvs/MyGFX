//includes
#include <iostream>
#include <stdint.h>
#include <fstream>
#include "Screen.hpp"

//Constructors
Screen::Screen() {
    width = 640;
    height = 360;
    size = width*height;
    pixels = new unsigned int[size];
}
Screen::Screen(unsigned int w, unsigned int h) {
    width = w;
    height = h;
    size = width*height;
    pixels = new unsigned int[size];
}

//Destructor
Screen::~Screen() {
    delete pixels;
}

//Get color channel functions (slower but more convenient)
uint8_t Screen::colorGetRed(const uint32_t& color) {
    return (char)((color >> 16) & 0xFF);
}
uint8_t Screen::colorGetGreen(const uint32_t& color) {
    return (char)((color >> 8) & 0xFF);
}
uint8_t Screen::colorGetBlue(const uint32_t& color) {
    return (char)(color & 0xFF);
}
uint8_t Screen::colorGetAlpha(const uint32_t& color) {
    return (char)((color >> 24) & 0xFF);
}

//Convert pixels array to a PPM file
void Screen::toPPM(const char* name) {
    std::ofstream fileStream(name, std::ios_base::out | std::ios_base::binary);

    /* Header:

        P6 #indicates binary format with RGB channels 0-255
        640 480 #image resolution
        255
        ... #pixel list
    */
    fileStream << "P6" << std::endl << width << ' ' << height << std::endl << "255" << std::endl;
    
    for (int i = 0; i < width*height; i++) {
        fileStream << (char)((pixels[i] >> 16) & 0xFF) << (char)((pixels[i] >> 8) & 0xFF) << (char)(pixels[i] & 0xFF);
        //fileStream << colorGetRed(pixels[i]) << colorGetGreen(pixels[i]) << colorGetBlue(pixels[i]);
    }

    // Render a rainbow PPM
    // for (auto j = 0u; j < height; j++)
    //     for (auto i = 0u; i < width; i++)
    //         fileStream << (char) (i % 256) << (char) (j % 256) << (char) ((i*j) % 256);

    fileStream.close();
}

//Fill entire screen with the given color
void Screen::fillBG(uint32_t color) {
    for (int i = 0; i < (width*height); i++) {
        pixels[i] = color;
    }
}

//Naive approach to filling screen with linear gradient top -> bottom
//Involves many function calls and divisions + a double for loop - can be optimized
//Note that this also skips the very last color of the gradient, which should be 100% the bottom color
void Screen::fillBGgradient(uint32_t top, uint32_t bottom) {

    for (int row = 0; row < height; row++) {
        
        uint32_t fill = 0xff00;

        uint32_t red = ((colorGetRed(top) * ((height - row)/(float)height)*100) + (colorGetRed(bottom) * ((row)/(float)height)*100))/(float)((((height - row)/(float)height)*100)+(((row)/(float)height)*100));
        fill = fill | red;
        fill = fill << 8;

        uint32_t green = ((colorGetGreen(top) * ((height - row)/(float)height)*100) + (colorGetGreen(bottom) * ((row)/(float)height)*100))/(float)((((height - row)/(float)height)*100)+(((row)/(float)height)*100));
        fill = fill | green;
        fill = fill << 8;

        uint32_t blue = ((colorGetBlue(top) * ((height - row)/(float)height)*100) + (colorGetBlue(bottom) * ((row)/(float)height)*100))/(float)((((height - row)/(float)height)*100)+(((row)/(float)height)*100));
        fill = fill | blue;

        //std::cout << (void*)fill << '\n'; 

        for (int col = 0; col < width; col++) {
            pixels[row*width+col] = fill;
        }
    }

}