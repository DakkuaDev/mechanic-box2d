/*
    @Author: Daniel Guerra Gallardo
    @program: Mechanism - 3D Animation
    @Date: 04/2021
    @Description: Desarollo mecánico de primitivas animadas fisicamente en un entorno de renderizado 2D
*/

#include "CollisionHandle.h"

namespace Physics
{

    void CollisionHandle::BeginContact(b2Contact* contact)
    { 
        b2Fixture* fixtureA = contact->GetFixtureA();
        b2Fixture* fixtureB = contact->GetFixtureB();

        b2Body* bodyA = fixtureA->GetBody();
        b2Body* bodyB = fixtureB->GetBody();

        Entity* entityA = (Entity*)bodyA->GetUserData().pointer;
        Entity* entityB = (Entity*)bodyB->GetUserData().pointer;

    }

    void CollisionHandle::EndContact(b2Contact* contact)
    { 

    }
}