#include <iostream>
#include <cmath>
#include "Screen.hpp"
#include "Shape.hpp"
#include "Stuff3D.hpp"

//Struct representing a 4D point (aka a 4x1 matrix)

Vec4::Vec4() {
    x = y = z = 0.0;
    w = 1.0;
}
Vec4::Vec4(double xi, double yi, double zi) {
    x = xi;
    y = yi;
    z = zi;
    w = 1.0;
}
Vec4::Vec4(double xi, double yi, double zi, double wi) {
    x = xi;
    y = yi;
    z = zi;
    w = wi;
}

void Vec4::show() {
    std::cout << "[ " << x << ' ' << y << ' ' << z << ' ' << w << " ]\n";
}

Vec4 Vec4::operator+ (Vec4 v2) {
    Vec4 v3;
    v3.x = this->x + v2.x;
    v3.y = this->y + v2.y;
    v3.z = this->z + v2.z;
    v3.w = this->w + v2.w;
    return v3;
}
template <typename T>
Vec4 Vec4::operator+ (T number) {
    Vec4 v3;
    v3.x = this->x + number;
    v3.y = this->y + number;
    v3.z = this->z + number;
    v3.w = this->w + number;
    return v3;
}

Vec4 Vec4::operator- (Vec4 v2) {
    Vec4 v3;
    v3.x = this->x - v2.x;
    v3.y = this->y - v2.y;
    v3.z = this->z - v2.z;
    v3.w = this->w - v2.w;
    return v3;
}
template <typename T>
Vec4 Vec4::operator- (T number) {
    Vec4 v3;
    v3.x = this->x - number;
    v3.y = this->y - number;
    v3.z = this->z - number;
    v3.w = this->w - number;
    return v3;
}

Vec4 Vec4::operator* (Vec4 v2) {
    Vec4 v3;
    v3.x = this->x * v2.x;
    v3.y = this->y * v2.y;
    v3.z = this->z * v2.z;
    v3.w = this->w * v2.w;
    return v3;
}
template <typename T>
Vec4 Vec4::operator* (T number) {
    Vec4 v3;
    v3.x = this->x * number;
    v3.y = this->y * number;
    v3.z = this->z * number;
    v3.w = this->w * number;
    return v3;
}

//Returns normalized version of a vector
Vec4 Vec4::normalize() {
    double length = sqrt((x*x) + (y*y) + (z*z) + (w*w));
    return {x/length, y/length, z/length, w/length};
}

double Vec4::getLength() {
    return sqrt((x*x) + (y*y) + (z*z) + (w*w));
}


//Class which represents a matrix

//Constructor
Matrix::Matrix(int r, int c) {
    rows = r;
    columns = c;
    size = r*c;
    mat = new double[size];
}

//Destructor
Matrix::~Matrix() {
    delete mat;
}

//Display the matrix in the terminal
void Matrix::show() {
    std::cout << '\n';
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < columns; c++) {
            std::cout << mat[r*columns+c] << ' ';
        }
        std::cout << '\n';
    }
}

//Returns a matrix that, when multiplying, results in a point translated by the amount specified
Matrix Matrix::translation(double x, double y, double z) {
    Matrix m(4, 4);
    m(0, 1.0);
    m(1, 0.0);
    m(2, 0.0);
    m(3, 0.0);
    m(4, 0.0);
    m(5, 1.0);
    m(6, 0.0);
    m(7, 0.0);
    m(8, 0.0);
    m(9, 0.0);
    m(10, 1.0);
    m(11, 0.0);
    m(12, x);
    m(13, y);
    m(14, z);
    m(15, 1.0);
    return m;
}

//Returns a matrix that, when multiplying, results in a point rotated by the amount specified about the Z axis
Matrix Matrix::rZ(double angle) {
    Matrix m(4, 4);
    m(0, cos(angle));
    m(1, sin(angle));
    m(2, 0.0);
    m(3, 0.0);
    m(4, -sin(angle));
    m(5, cos(angle));
    m(6, 0.0);
    m(7, 0.0);
    m(8, 0.0);
    m(9, 0.0);
    m(10, 1.0);
    m(11, 0.0);
    m(12, 0.0);
    m(13, 0.0);
    m(14, 0.0);
    m(15, 1.0);
    return m;
}

//Returns a matrix that, when multiplying, results in a point rotated by the amount specified about the X axis
Matrix Matrix::rX(double angle) {
    Matrix m(4, 4);
    m(0, 1.0);
    m(1, 0.0);
    m(2, 0.0);
    m(3, 0.0);
    m(4, 0.0);
    m(5, cos(angle));
    m(6, sin(angle));
    m(7, 0.0);
    m(8, 0.0);
    m(9, -sin(angle));
    m(10, cos(angle));
    m(11, 0.0);
    m(12, 0.0);
    m(13, 0.0);
    m(14, 0.0);
    m(15, 1.0);
    return m;
}

//Returns a matrix that, when multiplying, results in a point rotated by the amount specified about the Y axis
Matrix Matrix::rY(double angle) {
    Matrix m(4, 4);
    m(0, cos(angle));
    m(1, 0.0);
    m(2, -sin(angle));
    m(3, 0.0);
    m(4, 0.0);
    m(5, 1.0);
    m(6, 0.0);
    m(7, 0.0);
    m(8, sin(angle));
    m(9, 0.0);
    m(10, cos(angle));
    m(11, 0.0);
    m(12, 0.0);
    m(13, 0.0);
    m(14, 0.0);
    m(15, 1.0);
    return m;
}

//Calculates the dot product of a 4x1 vector by a 4x4 matrix
Vec4 Matrix::operator* (Vec4 v1) {
    Vec4 v2;
    v2.x = (v1.x*mat[0]) + (v1.y*mat[4]) + (v1.z*mat[8]) + (v1.w*mat[12]);
    v2.y = (v1.x*mat[1]) + (v1.y*mat[5]) + (v1.z*mat[9]) + (v1.w*mat[13]);
    v2.z = (v1.x*mat[2]) + (v1.y*mat[6]) + (v1.z*mat[10]) + (v1.w*mat[14]);
    v2.w = (v1.x*mat[3]) + (v1.y*mat[7]) + (v1.z*mat[11]) + (v1.w*mat[15]);
    return v2;
}

//Calculates the cross product of two matrices of the same exact dimensions
Matrix Matrix::operator* (Matrix m2) {
    if (rows != m2.rows || columns != m2.columns)
        return Matrix(1, 1);
    
    Matrix m3(rows, columns);
    
    for (int r = 0; r < rows; r++) {
        double value;
        for (int c = 0; c < columns; c++) {
            for (int m2it = 0; m2it < columns; m2it++) {
                value += mat[r+c] * m2.mat[m2it*rows+c];
            }
        }

        m3(r, value);
    }

    return m3;
}

//Matrix accessor
double Matrix::operator[] (int index) {
    if (index > size || index < 0)
        return mat[0];

    return mat[index];
}

//Matrix mutator
void Matrix::operator() (int index, double value) {
    if (index > size || index < 0)
        return;

    mat[index] = value;
}


//Struct describing a perspective camera

PerspectiveCamera::PerspectiveCamera(Vec4 p, Vec4 u, Vec4 ad, double fov, double n, double f, Screen& screen) : mat_Perspective(4, 4), mat_Position(4, 4) {
    
    position = p;
    up = u;
    aimDirection = ad;
    vfov = fov;
    near = n;
    far = f;

    sWidth = screen.width;
    sHeight = screen.height;

    calculateMatrix();
}

void PerspectiveCamera::calculateMatrix() {
    double a = ((far + near)/(far-near));
    double b = ((2*near*far)/(far-near));

    //"FOV"
    double cot = 1/(tan(vfov/2.0));
    
    mat_Perspective(0, cot * (sWidth/(double)sHeight));
    mat_Perspective(1, 0.0);
    mat_Perspective(2, 0.0);
    mat_Perspective(3, 0.0);

    mat_Perspective(4, 0.0);
    mat_Perspective(5, cot * (sWidth/(double)sHeight));
    mat_Perspective(6, 0.0);
    mat_Perspective(7, 0.0);

    mat_Perspective(8, 0.0);
    mat_Perspective(9, 0.0);
    mat_Perspective(10, a);
    mat_Perspective(11, -1.0);

    mat_Perspective(12, 0.0);
    mat_Perspective(13, 0.0);
    mat_Perspective(14, b);
    mat_Perspective(15, 0.0);

    // Matrix undoPosition = Matrix::translation(-position.x, -position.y, -position.z);
    // Matrix undoRY = Matrix::rY(atan(position.x/position.z));
    // Matrix undoRX = Matrix::rX(atan(position.y/(sqrt(position.x*position.x+position.z*position.z))));
    // Matrix undoRZ = Matrix::rZ(-atan(up.x/up.y));

    // mat_Position = Matrix::translation(-position.x, -position.y, -position.z); //* undoRY * undoRX * undoRZ;
}


//Represents a 3D object which can be rotated and translated. Contains a vertex buffer which is a Vec4 array of all points which constitute the object

Object3D::Object3D(Vec4* vertexBuffer, int vCount, unsigned int col) {
    vertices = vertexBuffer;
    vertexCount = vCount;
    color = col;
}
Object3D::Object3D(Vec4* vertexBuffer, int vCount, Vec4 pos, unsigned int col) {
    vertices = vertexBuffer;
    vertexCount = vCount;
    position = pos;
    color = col;
}

Object3D::~Object3D() {
    delete vertices;
}

//Translate the origin of this object
void Object3D::translate(Vec4 v) {
    position = Matrix::translation(v.x, v.y, v.z) * position;
}

//Rotate each vertex of the object about its origin
void Object3D::rotate(AxisType axis, double angle) {
    for (int i = 0; i < vertexCount; i++) {

        //vertices[i].show();

        switch (axis)
        {
        case Z_AXIS:
            vertices[i] = Matrix::rZ(angle)*vertices[i];
            break;

        case X_AXIS:
            vertices[i] = Matrix::rX(angle)*vertices[i];
            break;

        case Y_AXIS:
            vertices[i] = Matrix::rY(angle)*vertices[i];
            break;
        
        default:
            break;
        }

        //vertices[i].show();

    }
}

//Retrieve the location of a vertex + the position of the object
Vec4 Object3D::getVertex(int i) {
    if (i < 0 || i > vertexCount)
        return {};

    return Matrix::translation(position.x, position.y, position.z) * vertices[i];
};

//Display each vertex in order
void Object3D::show() {
    for (int i = 0; i < vertexCount; i++) {
        getVertex(i).show();
    }
}

void Object3D::drawOn(Screen& screen, PerspectiveCamera& cam) {

    //For each vertex of the object
    for (int i = 0; i < vertexCount; i++) {
        
        //Offset the vertex by the camera position and then apply the distortion matrix 
        Vec4 imageSpace = cam.mat_Perspective * (Matrix::translation(-cam.position.x, -cam.position.y, -cam.position.z) * getVertex(i)); //Matrix::translation(-cam.position.x, -cam.position.y, -cam.position.z)
        
        //Does not clip the rest yet
        if (imageSpace.w > 0.0 && imageSpace.z < cam.near) {
            
            //Convert to 3D space
            Vec4 space3D = {imageSpace.x/imageSpace.w, imageSpace.y/imageSpace.w, imageSpace.z/imageSpace.w};
            
            //Convert the 3D point into 2D and then offset it by 1/2 screen width and height (3D world origin is in the center of the screen)
            Shape::Vec2 screenCoord = {(space3D.x/space3D.z)+(screen.width/2.0), (space3D.y/space3D.z)+(screen.height/2.0)};

            //Draw the pixel to the pixels array if it is within the screen bounds
            if (screenCoord.x >= 0 && screenCoord.x < screen.width && screenCoord.y >= 0 && screenCoord.y < screen.height) {
                screen.pixels[(int)screenCoord.y*screen.width+(int)screenCoord.x] = color;
            }
        }
    }
}


//Creates an Object3D with vertices defined as the unit cube

Vec4* UnitCube::createVB(int scaleFactor) {
    Vec4* vb = new Vec4[8];

    vb[0].x = -1.0f * scaleFactor;
    vb[0].y = -1.0f * scaleFactor;
    vb[0].z = 1.0f * scaleFactor;

    vb[1].x = -1.0f * scaleFactor;
    vb[1].y = 1.0f * scaleFactor;
    vb[1].z = 1.0f * scaleFactor;

    vb[2].x = 1.0f * scaleFactor;
    vb[2].y = 1.0f * scaleFactor;
    vb[2].z = 1.0f * scaleFactor;

    vb[3].x = 1.0f * scaleFactor;
    vb[3].y = -1.0f * scaleFactor;
    vb[3].z = 1.0f * scaleFactor;

    vb[4].x = 1.0f * scaleFactor;
    vb[4].y = 1.0f * scaleFactor;
    vb[4].z = -1.0f * scaleFactor;

    vb[5].x = 1.0f * scaleFactor;
    vb[5].y = -1.0f * scaleFactor;
    vb[5].z = -1.0f * scaleFactor;

    vb[6].x = -1.0f * scaleFactor;
    vb[6].y = 1.0f * scaleFactor;
    vb[6].z = -1.0f * scaleFactor;

    vb[7].x = -1.0f * scaleFactor;
    vb[7].y = -1.0f * scaleFactor;
    vb[7].z = -1.0f * scaleFactor;
    return vb;
}

UnitCube::UnitCube(unsigned int col) : Object3D(createVB(1), 8, col) {}
UnitCube::UnitCube(unsigned int col, int sf) : Object3D(createVB(sf), 8, col) {}