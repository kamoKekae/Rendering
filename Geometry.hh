#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <vector>
#include <array>
#include<math.h>
#include <tuple>

typedef std::pair<float,float> Coordinate_2D;
typedef std::tuple<float,float,float> Coordinate_3D;

class Point{
public:
    float x,y,z;
    Point(): x(0) ,y(0),z(0){}
    Point(float rx, float ry, float rz){
        this->x =rx ; this->y = ry ; this->z = rz;
    }
};

// template<typename T> 
// class Vec3 
// { 
// public: 
//     // 3 most basic ways of initializing a vector
//     Vec3() : x(T(0)), y(T(0)), z(T(0)) {} 
//     Vec3(const T &xx) : x(xx), y(xx), z(xx) {} 
//     Vec3(T xx, T yy, T zz) : x(xx), y(yy), z(zz) {} 
//     T x, y, z; 
// }; 
 
// typedef Vec3<float> Vec3f; 


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

class Sphere{
private:
    float n_sides;
    float radius;
    std::vector<Coordinate_3D> coordinates;
public:

    Sphere():radius(1),n_sides(8){
        const float delta  = 2*M_PI / n_sides;
        float num_circles = 5;
        // num circels
        for(float height = 0; height < 2*radius ; height += radius/num_circles )    {
            for(float angle = 0; angle <2*M_PI ; angle += delta ){
                coordinates.push_back(std::make_tuple(radius*cos(angle) , radius* sin(angle),height ) );
            }
        }
    }

    std::vector<Coordinate_3D> getCoords(){return this->coordinates;}
};

#endif