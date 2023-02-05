# RGBCubes demo (SDL2)
An extension of the previous code but reorganized to deal with 3D points. This code acts as a way for me to experiment with OOP in C++ as well as a way to help me understand how to work with 3D objects in computer graphics. While most of the code is inefficient, I wanted to at least get it to a point where I could interact with it to make debugging easier. This demo uses SDL2 to interact with the 3D objects and display them in a window.
This folder adds:

## Stuff3D.hpp & Stuff3D.cpp
This file consists of all the structures I used to represent 3D objects as well as functions to rasterize them. Only the object vertices can be rasterized as of now.

# Compilation (Windows)
`g++ Screen.cpp -c`
`g++ Shape.cpp -c`
`g++ RGBCubes.cpp -c -I {SDL Includes folder} -L {SDL lib folder} -lmingw32 -lSDL2main -lSDL2`
`g++ RGBCubes.o Stuff3D.o Shape.o Screen.o -o RGBCubes_Rotation -lmingw32 -lSDL2main -lSDL2`

# Compilation (Linux)
`g++ Screen.cpp -c`
`g++ Shape.cpp -c`
`g++ RGBCubes.cpp -c`
`g++ RGBCubes.o Stuff3D.o Shape.o Screen.o -o RGBCubes_Rotation`

# Enums
## AxisType
`Z_AXIS, X_AXIS, Y_AXIS`

# Classes
More detailed documentation of each can be found within the header/implementation files

## class ConsoleReadable
### Pure virtual functions
```c++
virtual void show() = 0;
```

## struct Vec4 : implements ConsoleReadable
### Public instance variables
```c++
double x, y, z, w;
```
        
### Public constructors
```c++
Vec4();
Vec4(double xi, double yi, double zi);
Vec4(double xi, double yi, double zi, double wi);
```

### Public functions
```c++
void show() override;
Vec4 operator+ (Vec4 v2);
Vec4 operator+ (T number);
Vec4 operator- (Vec4 v2);
Vec4 operator- (T number);
Vec4 operator* (Vec4 v2);
Vec4 operator* (T number);
Vec4 normalize();
double getLength();
```

## class Matrix : implements ConsoleReadable
### Private instance variables
```c++
double* mat;
```

### Public instance variables
```c++
int rows;
int columns;
int size;
```
        
### Public constructor & destructor
```c++
Matrix(int r, int c);
~Matrix();
```

### Public functions
```c++
void show() override;
static Matrix translation(double x, double y, double z);
static Matrix rZ(double angle);
static Matrix rX(double angle);
static Matrix rY(double angle);
Vec4 operator* (Vec4 v1);
Matrix operator* (Matrix m2);
double operator[] (int index);
void operator() (int index, double value);
```

## struct PerspectiveCamera
### Public instance variables
```c++
Vec4 position;
Vec4 up;
Vec4 aimDirection;
double vfov;
double near;
double far;
int sWidth;
int sHeight;
Matrix mat_Perspective;
Matrix mat_Position;
```
        
### Public constructor
```c++
PerspectiveCamera(Vec4 p, Vec4 u, Vec4 ad, double fov, double n, double f, Screen& screen);
```

### Public functions
```c++
void calculateMatrix();
```

## class Object3D : implements ConsoleReadable
### Private instance variables
```c++
Vec4* vertices;
```

### Public instance variables
```c++
Vec4 position;
int vertexCount;
unsigned int color;
```
        
### Public constructor & destructor
```c++
Object3D(Vec4* vertexBuffer, int vCount, unsigned int col);
Object3D(Vec4* vertexBuffer, int vCount, Vec4 pos, unsigned int col);
~Object3D();
```

### Public functions
```c++
virtual void translate(Vec4 v);
virtual void rotate(AxisType axis, double angle);
Vec4 getVertex(int i);
void show() override;
void drawOn(Screen& screen, PerspectiveCamera& cam);
```

## class UnitCube : extends Object3D
### Private instance variables
```c++
Vec4* vertices;
```

### Public instance variables
```c++
Vec4 position;
int vertexCount;
unsigned int color;
```
        
### Public constructors
```c++
UnitCube(unsigned int col);
UnitCube(unsigned int col, int sf);
```

### Public functions
```c++
Vec4* createVB(int scaleFactor);
```
