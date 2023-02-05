#include <SDL2/SDL.h>
#include <iostream>
#include "Stuff3D.hpp"
#include "Screen.hpp"

//Screen dimensions
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 360

//Entrypoint - Must contain args
int main(int argc, char* args[]) {
    
    //Window, renderer
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    //Surface inside the window
    SDL_Surface* screenSurface = NULL;
    
    //Init SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Error initializing SDL Video: " << SDL_GetError() << '\n';
    } else {

        //Create the window
        //window = SDL_CreateWindow("3D Cubes", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN, &window, &renderer);

        if (window == NULL) {
            std::cout << "Error creating window: " << SDL_GetError() << '\n';
        } else {


            //My stuff 3D setup
            UnitCube cube(0xff00ff00u); //G
            UnitCube cube2(0xffff5959u); //Light R
            UnitCube cube3(0xff348cebu); //Light B

            //Create screen object to keep track of screen state
            Screen myScreen(SCREEN_WIDTH, SCREEN_HEIGHT);

            //Camera with position, up vector, aim direction, FOV, near plane, far plane
            PerspectiveCamera cam({0.0, 0.0, 10.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, -1.0}, 0.01, 0.1, 100.0, myScreen);
            
            //Setup cubes... negative X is right?
            cube2.position = Matrix::translation(5.0, 0.0, 0.0) * cube2.position;
            cube3.position = Matrix::translation(-5.0, 0.0, 0.0) * cube3.position;

            //Get window to stay up
            SDL_Event e;
            bool quit = false;
            while (quit == false) {

                //Main loop starts here - "Rendering" cube to screen array

                //Fill screen state with linear gradient - dark -> light gray
                myScreen.fillBGgradient(0xff111111u, 0xff363636u);

                //Draw cube vertex coordinates to the screen based on the camera's POV
                cube.drawOn(myScreen, cam);
                cube2.drawOn(myScreen, cam);
                cube3.drawOn(myScreen, cam);
                
                //Clear SDL backbuffer
                SDL_RenderClear(renderer);

                //Translate screen state from my own screen structure to SDL
                for (int i = 0; i < myScreen.size; i++) {
                    SDL_SetRenderDrawColor(renderer, myScreen.colorGetRed(myScreen.pixels[i]), myScreen.colorGetGreen(myScreen.pixels[i]), myScreen.colorGetBlue(myScreen.pixels[i]), 0xffu);
                    SDL_RenderDrawPoint(renderer, (i%myScreen.width), (i/myScreen.width));
                }

                //Display SDL backbuffer to the window
                SDL_RenderPresent(renderer);

                //Capture polled events
                while( SDL_PollEvent( &e ) ){
                    
                    //Switch to handle event cases
                    switch (e.type) {
                        case SDL_QUIT:
                            quit = true;
                            break;

                        case SDL_KEYDOWN:
                            // std::cout << "A key was pressed: " << SDL_GetKeyName(e.key.keysym.sym) << ' ' << e.key.keysym.scancode << '\n';
                            // W:26, A:4, S:22, D:7, Up:82, Down:81, Right:79, Left:80
                            if (e.key.keysym.scancode == 26) {
                                cube.position = Matrix::translation(0.0, 0.0, 0.1) * cube.position;
                                cube2.position = Matrix::translation(0.0, 0.0, 0.1) * cube2.position;
                                cube3.position = Matrix::translation(0.0, 0.0, 0.1) * cube3.position;
                            } else if (e.key.keysym.scancode == 22) {
                                cube.position = Matrix::translation(0.0, 0.0, -0.1) * cube.position;
                                cube2.position = Matrix::translation(0.0, 0.0, -0.1) * cube2.position;
                                cube3.position = Matrix::translation(0.0, 0.0, -0.1) * cube3.position;
                            } else if (e.key.keysym.scancode == 7) {
                                cube.position = Matrix::translation(0.1, 0.0, 0.0) * cube.position;
                                cube2.position = Matrix::translation(0.1, 0.0, 0.0) * cube2.position;
                                cube3.position = Matrix::translation(0.1, 0.0, 0.0) * cube3.position;
                            } else if (e.key.keysym.scancode == 4) {
                                cube.position = Matrix::translation(-0.1, 0.0, 0.0) * cube.position;
                                cube2.position = Matrix::translation(-0.1, 0.0, 0.0) * cube2.position;
                                cube3.position = Matrix::translation(-0.1, 0.0, 0.0) * cube3.position;
                            } else if (e.key.keysym.scancode == 82) {
                                // cube.position = Matrix::translation(0.0, -0.1, 0.0) * cube.position;
                                // cube2.position = Matrix::translation(0.0, -0.1, 0.0) * cube2.position;
                                // cube3.position = Matrix::translation(0.0, -0.1, 0.0) * cube3.position;
                                cube.rotate(X_AXIS, -0.01);
                                cube2.rotate(X_AXIS, -0.01);
                                cube3.rotate(X_AXIS, -0.01);
                            } else if (e.key.keysym.scancode == 81) {
                                // cube.position = Matrix::translation(0.0, 0.1, 0.0) * cube.position;
                                // cube2.position = Matrix::translation(0.0, 0.1, 0.0) * cube2.position;
                                // cube3.position = Matrix::translation(0.0, 0.1, 0.0) * cube3.position;
                                cube.rotate(X_AXIS, 0.01);
                                cube2.rotate(X_AXIS, 0.01);
                                cube3.rotate(X_AXIS, 0.01);
                            } else if (e.key.keysym.scancode == 79) {
                                cube.rotate(Y_AXIS, -0.01);
                                cube2.rotate(Y_AXIS, -0.01);
                                cube3.rotate(Y_AXIS, -0.01);
                            } else if (e.key.keysym.scancode == 80) {
                                cube.rotate(Y_AXIS, 0.01);
                                cube2.rotate(Y_AXIS, 0.01);
                                cube3.rotate(Y_AXIS, 0.01);
                            }
                            break;
                    }

                }
            }

        }

    }

    //Destroy the renderer
    SDL_DestroyRenderer(renderer);

    //Destroy the window
    SDL_DestroyWindow(window);

    //Quit SDL subsystems
    SDL_Quit();

    return 0;
}