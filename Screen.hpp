#pragma once
#ifndef SCREEN_HPP
#define SCREEN_HPP

/*
    Name: 
        Simple Screen class

    Author:
        ntvs
        02-01-2023

    Purpose:
        To represent a screen using an array
        To convert that array to various image formats

    Notes:
        This class also contains some functions to fill the entire array's
        background or to create a linear gradient. Currently, the screen
        can only be converted to the PPM image format.
        
    Implementation:
        Screen.cpp 
*/

//Screen Operations
class Screen {
    public:
        //Instance variables
        unsigned int width;
        unsigned int height;
        unsigned int size;
        unsigned int* pixels;
        
        //Constructors & destructor
        Screen();
        Screen(unsigned int& w, unsigned int& h);
        ~Screen();

        //Get color channel functions (slower but more convenient)
        unsigned char colorGetRed(const unsigned int& color);
        unsigned char colorGetGreen(const unsigned int& color);
        unsigned char colorGetBlue(const unsigned int& color);
        unsigned char colorGetAlpha(const unsigned int& color);

        //Convert pixels array to a PPM file
        void toPPM(const char* name);

        //Fill entire screen with the given color
        void fillBG(unsigned int color);

        //Naive approach to filling screen with linear gradient top -> bottom
        //Involves many function calls and divisions + a double for loop - can be optimized
        //Note that this also skips the very last color of the gradient, which should be 100% the bottom color
        void fillBGgradient(const unsigned int& top, const unsigned int& bottom);
};

#endif