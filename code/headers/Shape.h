#pragma once

/*
    @Author: Daniel Guerra Gallardo
    @program: Mechanism - 3D Animation
    @Date: 04/2021
    @Description: Desarollo mec�nico de primitivas animadas fisicamente en un entorno de renderizado 2D
*/

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

namespace world_render
{

    b2Body* create_box(b2World& physics_world, b2BodyType body_type, float x, float y, float width, float height);

}