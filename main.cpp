#include "Geometry.hh"
#include <iostream>
#include <stdlib.h>
#include <array>

#define IMAGE_WIDTH  512 
#define IMAGE_HEIGHT 512 

template<typename T>
void printTo(Matrix4<T>& _m){
    std::cout<<"Printing Matrix Now ... \n\n";
    for(int row =0; row < 4; row++){
        
            for(int column =0; column < 4; column++){
                _m.get()[row][column] = 1;
                std::cout<<_m.get()[row][column] << ' ';
            }   
            std::cout<<std::endl;
        }
}

int main(){

    // World Coordinates
    std::array<Vec3i,8> Cube = {Vec3i{ 1, -1, -5},
                                Vec3i{ 1, -1, -3},
                                Vec3i{ 1,  1, -5},
                                Vec3i{ 1,  1, -3},
                                Vec3i{-1, -1, -5},
                                Vec3i{-1, -1, -3},
                                Vec3i{-1,  1, -5},
                                Vec3i{-1,  1, -3}};
    std::array<Vec3f,8> cCube;

    
    for(int i =0; i < Cube.size() ; i++){
        // Perform Perspective Divide
        cCube[i] = Vec3f{Cube[i].x/-float(Cube[i].z),float(Cube[i].y)/-Cube[i].z,float(Cube[i].z) /-Cube[i].z};
        // Normalized Device coordinates
        cCube[i].x =  (1 + cCube[i].x)/2;
        cCube[i].y = (1 + cCube[i].y)/2;

        // Raster coordinates
        cCube[i].x =   cCube[i].x *IMAGE_WIDTH ;

        cCube[i].y = cCube[i].y*IMAGE_HEIGHT;
    }


    // for(auto it = cCube.begin() ; it != cCube.end() ; it++){
    //     std::cout<<"Normal coordinate :"<<it->x << "\t"<<it->y<<"\t"<<it->z<<std::endl;
    // }

    Matrix4f a;

    printTo(a);

    return 0;
}