/*
    @Author: Daniel Guerra Gallardo
    @program: Mechanism - 3D Animation
    @Date: 04/2021
    @Description: Desarollo mec�nico de primitivas animadas fisicamente en un entorno de renderizado 2D
*/

#include "WorldGenerator.h";
#include "Shape.h"

namespace world_render
{
    unique_ptr< b2World > create_physics_world()
    {
        // Se crea el mundo f�sico:

        unique_ptr< b2World > physics_world
        {
            new b2World{ b2Vec2{ 0, -10.f } }
        };

        //// C�RCULO
        //{
        //    // Se crea el body a partir de una definici�n de sus caracter�sticas:

        //    b2BodyDef body_definition;

        //    body_definition.type = b2_dynamicBody;
        //    body_definition.position.Set(4, 3);                                    // Posici�n inicial absoluta

        //    b2Body* body = physics_world->CreateBody(&body_definition);

        //    // Se a�ande una fixture al body:

        //    b2CircleShape body_shape;

        //    body_shape.m_radius = .5f;

        //    b2FixtureDef body_fixture;

        //    body_fixture.shape = &body_shape;
        //    body_fixture.density = 1.00f;
        //    body_fixture.restitution = 0.75f;
        //    body_fixture.friction = 0.50f;

        //    body->CreateFixture(&body_fixture);
        //}

        // CUADRADO
        create_box(*physics_world, b2_dynamicBody, 4, 3, .5f, .5f);

        // SUELO
        {
            // Se crea el body a partir de una definici�n de sus caracter�sticas:

            b2BodyDef body_definition;

            body_definition.type = b2_staticBody;
            body_definition.position.Set(0.f, 1.f);                                // Posici�n inicial absoluta
            body_definition.angle = 0.f;

            b2Body* body = physics_world->CreateBody(&body_definition);

            // Se a�ande una fixture al body:

            b2EdgeShape body_shape;

            body_shape.SetTwoSided(b2Vec2(0.f, 1.f), b2Vec2(10, 1.f));                     // Coordenadas locales respecto al centro del body

            b2FixtureDef body_fixture;

            body_fixture.shape = &body_shape;

            body->CreateFixture(&body_fixture);
        }

        return physics_world;
    }

}