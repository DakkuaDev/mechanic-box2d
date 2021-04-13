/*
    @Author: Daniel Guerra Gallardo
    @program: Mechanism - 3D Animation
    @Date: 04/2021
    @Description: Desarollo mecánico de primitivas animadas fisicamente en un entorno de renderizado 2D
*/

#include "WorldGenerator.h";
#include "Shape.h"

namespace physics
{
    unique_ptr< b2World > create_physics_world()
    {
        // Se crea el mundo físico:

        unique_ptr< b2World > physics_world
        {
            new b2World{ b2Vec2{ 0, -10.f } }
        };

        // JUGADOR
        create_circle(*physics_world, b2_dynamicBody, 2, 4, 0.25f);

        // ESCENARIO
        // --------- Piso Inferior ----------------

        // Estáticos (Izquierda a derecha)
        create_box(*physics_world, b2_staticBody, 2.20f, -0.2f, 1.1f, 0.75f);
        create_box(*physics_world, b2_staticBody, 6.85f, -0.75f, 3.5f, 0.20f);
        create_triangle(*physics_world, b2_staticBody, 3.35f, -0.5f, 1, 1);

        // Kinemáticos
        create_box(*physics_world, b2_kinematicBody, 11.65f, -0.75f, 1.25f, 0.20f);

        // --------- Piso Superior ----------------

        // Estáticos (Dercha a izquierda)
        create_box(*physics_world, b2_staticBody, 9.38f, 4.35f, 0.85f, 0.20f);

        auto rotate_body = create_box(*physics_world, b2_staticBody, 7.65f, 3.5f, 1.4f, 0.15f);
        rotate_body->SetTransform(rotate_body->GetPosition(), 95.f);

        create_box(*physics_world, b2_staticBody, 6.20f, 2.5f, 0.55f, 0.20f);
       
         // Kinemáticos
        create_box(*physics_world, b2_kinematicBody, 4.5f, 2.5f, 1.10f, 0.20f);

        return physics_world;
    }

}