/*
    @Author: Daniel Guerra Gallardo
    @program: Mechanism - 3D Animation
    @Date: 04/2021
    @Description: Desarollo mecánico de primitivas animadas fisicamente en un entorno de renderizado 2D
*/

#include "World.h"

using namespace std;

namespace Physics
{

    World::World()
    {
        gravity = b2Vec2(0.0f, -10.0f);

        if (!physics_world)
        {
            physics_world = unique_ptr< b2World > 
            {
                new b2World{ b2Vec2{ gravity } }
            };
        }
    };

    World::World(b2Vec2 _gravity)
    {
        gravity = _gravity;

        if (!physics_world)
        {
            physics_world = unique_ptr< b2World >
            {
                new b2World{ b2Vec2{ _gravity } }
            };
        }
    }

    b2World* World::get_world()
    {
        return physics_world.get();
    }
    
}
