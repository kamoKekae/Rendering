#ifndef POINT_H
#define POINT_H

class Point{
public:
    float x,y,z;
    Point(): x(0) ,y(0),z(0){}
    Point(float rx, float ry, float rz){
        x =rx ; y = ry ; z = rz;
    }
};

#endif