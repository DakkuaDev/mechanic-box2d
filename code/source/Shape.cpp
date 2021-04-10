/*
    @Author: Daniel Guerra Gallardo
    @program: Mechanism - 3D Animation
    @Date: 04/2021
    @Description: Desarollo mec�nico de primitivas animadas fisicamente en un entorno de renderizado 2D
*/

#include "Shape.h"

namespace world_render
{

    b2Body* create_box(b2World& physics_world, b2BodyType body_type, float x, float y, float width, float height)
    {
        // Se crea el body a partir de una definici�n de sus caracter�sticas:

        b2BodyDef body_definition;

        body_definition.type = b2_dynamicBody;
        body_definition.position.Set(x, y);                                    // Posici�n inicial absoluta

        b2Body* body = physics_world.CreateBody(&body_definition);

        // Se a�ande una fixture al body:

        b2PolygonShape body_shape;

        body_shape.SetAsBox(width, height);

        b2FixtureDef body_fixture;

        body_fixture.shape = &body_shape;
        body_fixture.density = 1.00f;
        body_fixture.restitution = 0.50f;
        body_fixture.friction = 0.50f;


        body->CreateFixture(&body_fixture);

        return body;
    }
    
}