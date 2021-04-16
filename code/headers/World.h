#pragma once

/*
    @Author: Daniel Guerra Gallardo
    @program: Mechanism - 3D Animation
    @Date: 04/2021
    @Description: Desarollo mecánico de primitivas animadas fisicamente en un entorno de renderizado 2D
*/

#include <Box2D/Box2D.h>
#include <memory>

using namespace std;

namespace Physics
{

    class World
    {
    private:
        b2Vec2 gravity;
        unique_ptr< b2World > physics_world;

    public:
        World();
        World(b2Vec2 _gravity);

    public:

        /// <summary>
        ///  Obtiene una instancia singleton del mundo
        /// </summary>
        /// <returns> devuelve un puntero a b2World </returns>
        b2World* get_world();
    };
}
