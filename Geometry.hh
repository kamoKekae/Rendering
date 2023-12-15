#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <vector>
#include <array>
#include<math.h>


template<typename T> 
class Vec3{
public:
    T x,y,z;
    Vec3(): x(T(0)) ,y(T(0)),z(T(0)){}
    Vec3(const T &xx) : x(xx), y(xx), z(xx) {}
    Vec3(T rx, T ry, T rz){this->x =rx ; this->y = ry ; this->z = rz;}

    bool operator==(const Vec3<T> _v) const{
        return x==_v.x && y==_v.y && z==_v.z;
    }
    Vec3<T> operator+ (const Vec3<T> _v) const{
        return Vec3<T>{this->x + _v.x,this->y + _v.y,this->z + _v.z};
    }


    Vec3<T> operator- (const Vec3<T> _v) const {
        return Vec3<T>{this->x - _v.x,this->y - _v.y,this->z - _v.z};
    }

    Vec3<T> operator*(const T scalar) const{
        return Vec3<T>{x*scalar,y*scalar,z*scalar};
    }
    
    double length()const {return sqrt(pow(x,2) + pow(y,2) + pow(z,2)) ;}

    double dot(Vec3<T>& _v)const{
        return this->x*_v.x + this->y*_v.y + this->z * _v.z;
    }

    Vec3<T>& normalize(){
        double len = sqrt(dot(*this));
        if(len>0){
            double mult = 1/len;
            this->x *= mult;
            this->y *= mult;
            this->z *= mult;
        }
        return *this;
    }

    Vec3<T> cross(Vec3<T>& _v)const {
        return Vec3<T>{
            this->y *_v.z - this->z*_v.y, this->z*_v.x - _v.z*this->x,this->x*_v.y - this->y*_v.x
        };
    }


};


typedef std::pair<float,float> Coordinate_2D;
typedef Vec3<float> Vec3f;
typedef Vec3<int> Vec3i;


template<typename T>
class Matrix4 {
private:

    std::vector<std::vector<T>> _matrix{
                                        { 1, 0, 0, 0},
                                        { 0, 1, 0, 0},
                                        { 0, 0, 1, 0},
                                        { 0, 0, 0, 1}
                                        };
public:
    
    Matrix4(){}
    bool operator ==(const Matrix4<T>& _m) const{
        for(int row =0; row < 4; row++){
            for(int column =0; column<4; column++){
                if( this->_matrix[row][column] != _m._matrix[row][column]){
                    return false;
                }
            }
        }
        return true;
    }

    Matrix4<T> operator*(const T _m){
        for(int row =0; row < 4; row++){
            for(int column =0; column < 4; column++){
                this->_matrix[row][column] *= _m;
            }   
        }
    }

    Matrix4<T> operator*(const Matrix4<T>& _m) const{
        Matrix4<T> result;

        for(int row =0; row < 4 ; row++){
            for( int column=0 ; column< 4; column++){
                for(int k = 0; k < 4;k++){
                    result._matrix[row][column] += this->_matrix[row][column] *_m._matrix[row][column];
                }
            }
        }
    }

    Matrix4<T> operator+(const Matrix4<T>& _m){
        Matrix4<T> result;
        for(int row =0; row < 4; row++){
            for(int column =0; column < 4; column++){
                result._matrix[row][column]= this->_matrix[row][column] + _m._matrix[row][column];
            }   
        }

        return result;
    }

    std::vector<std::vector<T>> get(){
        return _matrix;
    }

    // make all elements zero
    void zero(){
        _matrix = std::vector<std::vector<T>>(4,std::vector<T>(4,0));
    }

    void identity(){
        this->_matrix = {
                        { 1, 0, 0, 0},
                        { 0, 1, 0, 0},
                        { 0, 0, 1, 0},
                        { 0, 0, 0, 1}
                        };
        return;
    }

    // Linear Operations

    // Scales on all axes
    void scale(T sx, T sy, T sz){
        _matrix[0][0] *= sx;
        _matrix[1][1] *= sy;
        _matrix[2][2] *= sz;
    }

    /**
     * TODO: FIND DERIVATION OF ROTATION MATRIX WITH RESPECT TO AN ARBITRARY AXIS VECTOR
    */
    void rotate(Vec3<T> axis, T angle){
    }

    // Acts on Current Matrix
    void translate(T dx, T dy , T dz){
        _matrix[0][3] += dx;
        _matrix[1][3] += dy;
        _matrix[2][3] += dz;
    }
};

typedef Matrix4<float> Matrix4f;

class Rectangle{
private:
    
    std::array<Coordinate_2D,4> coordinates;
public:
    float width,height;
    Rectangle():width(1),height(1){
        this->coordinates = std::array<Coordinate_2D,4>({std::make_pair(0.0f,0.0f),std::make_pair(width,0.0f),std::make_pair(width,height),std::make_pair(0.0f,height)});
    };

    Rectangle(float _width, float _height) {
    this->width = _width;
    this->height = _height;
    
    this->coordinates = std::array<Coordinate_2D,4>({std::make_pair(0.0f,0.0f),std::make_pair(width,0.0f),std::make_pair(width,height),std::make_pair(0.0f,height)});
    }

    std::array<Coordinate_2D,4> getCoords() {return this->coordinates;}
};

class Circle{
    int n_sides;
    float radius;
    std::vector<Coordinate_2D> coordinates;
public:
    // Everything in radians
    Circle():radius(1) , n_sides(20){
        const float delta  = 2*M_PI / n_sides;
        for(float angle = 0; angle <2*M_PI ; angle += delta ){
            coordinates.push_back(std::make_pair(radius*cos(angle) , radius* sin(angle) ) );
        }
    }

    Circle(float r_radius , float r_nsides){
        this->radius = r_radius;
        this->n_sides = r_nsides;
        const float delta  = 2*M_PI / n_sides;
        for(float angle = 0; angle <2*M_PI ; angle += delta ){
            coordinates.push_back(std::make_pair(radius*cos(angle) , radius* sin(angle) ) );
        }
    }
    std::vector<Coordinate_2D> getCoords(){return this->coordinates;}
};


template<typename T>
class Sphere{
private:
    float n_sides;
    T radius;
    std::vector<Vec3<T>> coordinates;
    
public:

    
    Sphere():radius(1),n_sides(8){
        const float delta  = 2*M_PI / n_sides;
        float num_circles = 5;
        // num circels
        for(float height = 0; height < 2*radius ; height += radius/num_circles )    {
            for(float angle = 0; angle <2*M_PI ; angle += delta ){
                coordinates.push_back(Vec3<T>(radius*cos(angle) , radius* sin(angle),height ) );
            }
        }
    }

    std::vector<Vec3f> getCoords(){return this->coordinates;}
};




#endif