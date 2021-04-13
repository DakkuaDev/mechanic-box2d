/*
    @Author: Daniel Guerra Gallardo
    @program: Mechanism - 3D Animation
    @Date: 04/2021
    @Description: Desarollo mecánico de primitivas animadas fisicamente en un entorno de renderizado 2D
*/

#pragma once

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;


namespace physics
{
    // Crea un nuevo mundo físico a partir de los datos de SFML y Box2D
    unique_ptr< b2World > create_physics_world();
}
