#include "Geometry.hh"
#include <iostream>
#include <stdlib.h>
#include <array>

#define IMAGE_WIDTH  512 
#define IMAGE_HEIGHT 512 

int main(){

    // World Coordinates
    std::array<Point,8> Cube = {Point{ 1, -1, -5},
                                Point{ 1, -1, -3},
                                Point{ 1,  1, -5},
                                Point{ 1,  1, -3},
                                Point{-1, -1, -5},
                                Point{-1, -1, -3},
                                Point{-1,  1, -5},
                                Point{-1,  1, -3}};
    std::array<Point,8> cCube;
    for(int i =0; i < Cube.size() ; i++){
        // Perform Perspective Divide
        cCube[i] = Point{Cube[i].x/-Cube[i].z,Cube[i].y/-Cube[i].z,Cube[i].z/-Cube[i].z};
        // Normalized Device coordinates
        cCube[i].x =  (1 + cCube[i].x)/2;
        cCube[i].y = (1 + cCube[i].y)/2;

        // Raster coordinates
        cCube[i].x =   cCube[i].x *IMAGE_WIDTH ;

        cCube[i].y = cCube[i].y*IMAGE_HEIGHT;
    }


    for(auto it = cCube.begin() ; it != cCube.end() ; it++){
        std::cout<<"Normal coordinate :"<<it->x << "\t"<<it->y<<"\t"<<it->z<<std::endl;
    }

    return 0;
}