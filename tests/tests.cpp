#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../Geometry.hh"
#include <math.h>

TEST_CASE("Vector operations work","[vector]"){
    // Test Vectors
    Vec3f v1 = Vec3f{5,4,3};
    Vec3f v2 = Vec3f{5};
    Vec3f v3 = Vec3f{4};


    // Norm Test
    REQUIRE(v1.length() == sqrt(pow(5,2) + pow(4,2) + pow(3,2) ) );
    REQUIRE(v2.length() == sqrt(pow(5,2)*3) );
    REQUIRE(v3.length() == sqrt(pow(4,2)*3) );


    // Scaling test

    REQUIRE(v3*2 == Vec3f{8});
}

