#include "Screen.hpp"

//Interface guaranteeing that everything which implements it shall be viewable in the terminal
class ConsoleReadable {
    virtual void show() = 0;
};

//Enum for the 3D axes
enum AxisType {
    Z_AXIS,
    X_AXIS,
    Y_AXIS
};

//Struct representing a 4D point (aka a 4x1 matrix)
struct Vec4 : public ConsoleReadable {
    double x, y, z, w;

    Vec4();
    Vec4(double xi, double yi, double zi);
    Vec4(double xi, double yi, double zi, double wi);

    void show() override;

    Vec4 operator+ (Vec4 v2);
    template <typename T>
    Vec4 operator+ (T number);

    Vec4 operator- (Vec4 v2);
    template <typename T>
    Vec4 operator- (T number);
    
    Vec4 operator* (Vec4 v2);
    template <typename T>
    Vec4 operator* (T number);

    //Returns normalized version of a vector
    Vec4 normalize();
    double getLength();
};

//Class which represents a matrix
class Matrix : public ConsoleReadable {

    //Private members
    private:
        double* mat;

    //Public members
    public:
        int rows;
        int columns;
        int size;

        //Constructor
        Matrix(int r, int c);

        //Destructor
        ~Matrix();

        //Display the matrix in the terminal
        void show() override;

        //Returns a matrix that, when multiplying, results in a point translated by the amount specified
        static Matrix translation(double x, double y, double z);

        //Returns a matrix that, when multiplying, results in a point rotated by the amount specified about the Z axis
        static Matrix rZ(double angle);
        
        //Returns a matrix that, when multiplying, results in a point rotated by the amount specified about the X axis
        static Matrix rX(double angle);

        //Returns a matrix that, when multiplying, results in a point rotated by the amount specified about the Y axis
        static Matrix rY(double angle);

        //Calculates the dot product of a 4x1 vector by a 4x4 matrix
        Vec4 operator* (Vec4 v1);

        //Calculates the cross product of two matrices of the same exact dimensions
        Matrix operator* (Matrix m2);

        //Matrix accessor
        double operator[] (int index);

        //Matrix mutator
        void operator() (int index, double value);

};

//Struct representing a pinhole camera - used to generate perspective matrix
struct PerspectiveCamera {

    //Where the camera is, which direction is up, and which direction its looking at
    Vec4 position;
    Vec4 up;
    Vec4 aimDirection;

    //Vertical FOV
    double vfov;
    
    //Near and far planes
    double near;
    double far;

    //Screen W, H
    int sWidth;
    int sHeight;

    //The perspective matrix
    Matrix mat_Perspective;
    Matrix mat_Position;

    //Position, up vector, aim direction, FOV, near plane, far plane
    PerspectiveCamera(Vec4 p, Vec4 u, Vec4 ad, double fov, double n, double f, Screen& screen);

    //Sets up the perspective matrix based on the information passed into the constructor
    private: void calculateMatrix();

};


//Represents a 3D object which can be rotated and translated. Contains a vertex buffer which is a Vec4 array of all points which constitute the object
class Object3D : public ConsoleReadable {

    Vec4* vertices;

    public:
        Vec4 position;
        int vertexCount;
        unsigned int color;

        Object3D(Vec4* vertexBuffer, int vCount, unsigned int col);
        Object3D(Vec4* vertexBuffer, int vCount, Vec4 pos, unsigned int col);
        
        ~Object3D();

        //Translate the origin of this object
        virtual void translate(Vec4 v);

        //Rotate each vertex of the object about its origin
        virtual void rotate(AxisType axis, double angle);

        //Retrieve the location of a vertex + the position of the object
        Vec4 getVertex(int i);

        //Display each vertex in order
        void show() override;

        void drawOn(Screen& screen, PerspectiveCamera& cam);
};


//Creates an Object3D with vertices defined as the unit cube
class UnitCube : public Object3D {

    Vec4* createVB(int scaleFactor);

    public: 
        UnitCube(unsigned int col);
        UnitCube(unsigned int col, int sf);
};

// class World3D {
//     Vec4 position;
//     Vec4 orientation;

//     World3D() {
//         position = {0.0, 0.0, 0.0};
//         orientation = {0.0, 0.0, 1.0};
//     }
// };