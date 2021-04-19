/*
    @Author: Daniel Guerra Gallardo
    @program: Mechanism - 3D Animation
    @Date: 04/2021
    @Description: Desarollo mecánico de primitivas animadas fisicamente en un entorno de renderizado 2D
*/

#include "CollisionHandle.h"

namespace Physics
{

    CollisionHandle::CollisionHandle() : b2ContactListener() {}


    void CollisionHandle::BeginContact(b2Contact* contact)
    { 
        b2Fixture* fixtureA = contact->GetFixtureA();
        b2Fixture* fixtureB = contact->GetFixtureB();

        b2Body* bodyA = fixtureA->GetBody();
        b2Body* bodyB = fixtureB->GetBody();

        Entity* entityA = (Entity*)bodyA->GetUserData().pointer;
        Entity* entityB = (Entity*)bodyB->GetUserData().pointer;

        if (entityA != NULL && entityB != NULL)
        {
            // DONT WORK!!
            //if (entityA->get_tag() == "player" && entityB->get_tag() == "platform")
            //{
            //    bodyA->SetLinearVelocity({ 0, 1.5 });
            //}

            // Plataformas
            if (entityA && entityB)
            {
                // TODO: Crear más precisión para las plataformas. Quizá debamos ponerlas en un update de la escena
                if (bodyA->GetPosition().y <= 3.25)
                {
                    bodyA->SetLinearVelocity({ 0, 1.75 });
                }
                else bodyA->SetLinearVelocity({ 0, 0 });
               
            }
        }




    }

    void CollisionHandle::EndContact(b2Contact* contact)
    { 

    }
}