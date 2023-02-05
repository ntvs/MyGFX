To compile RGBCubes.cpp
g++ RGBCubes.cpp -c -I win\include -L win\lib 

then compile Shape.cpp, Screen.cpp Stuff3D.cpp to object -c

then link them with all with
g++ .\RGBCubes.o .\Stuff3D.o .\Shape.o .\Screen.o -o RGBCubes -lmingw32 -lSDL2main -lSDL2