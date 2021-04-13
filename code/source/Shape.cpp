/*
    @Author: Daniel Guerra Gallardo
    @program: Mechanism - 3D Animation
    @Date: 04/2021
    @Description: Desarollo mecánico de primitivas animadas fisicamente en un entorno de renderizado 2D
*/

#include "Shape.h"

namespace physics
{
    b2Body* create_circle(b2World& physics_world, b2BodyType body_type, float x, float y, float radius)
    {
            // Se crea el body a partir de una definición de sus características:

            b2BodyDef body_definition;

            body_definition.type = b2_dynamicBody;
            body_definition.position.Set(x, y);                                    // Posición inicial absoluta

            b2Body* body = physics_world.CreateBody(&body_definition);

            // Se añande una fixture al body:

            b2CircleShape body_shape;

            body_shape.m_radius = radius;

            b2FixtureDef body_fixture;

            body_fixture.shape = &body_shape;
            body_fixture.density = 1.00f;
            body_fixture.restitution = 0.75f;
            body_fixture.friction = 0.50f;

            body->CreateFixture(&body_fixture);

            return body;
    }

    b2Body* create_box(b2World& physics_world, b2BodyType body_type, float x, float y, float width, float height)
    {
        // Se crea el body a partir de una definición de sus características:

        b2BodyDef body_definition;

        body_definition.type = body_type;
        body_definition.position.Set(x, y);                                    // Posición inicial absoluta

        b2Body* body = physics_world.CreateBody(&body_definition);

        // Se añande una fixture al body:

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

    b2Body* create_triangle(b2World& physics_world, b2BodyType body_type, float x, float y, float width, float height)
    {
        // Se crea el body a partir de una definición de sus características:

        b2BodyDef body_definition;

        body_definition.type = body_type;
        body_definition.position.Set(x, y);                                    // Posición inicial absoluta

        b2Body* body = physics_world.CreateBody(&body_definition);

        // Se añande una fixture al body:

        b2PolygonShape body_shape;

        b2Vec2 vertices[3];

        vertices[0].Set(0.0f, 0.0f);
        vertices[1].Set(1.0f, 0.0f);
        vertices[2].Set(0.0f, 1.0f);

        int32 count = 3;

        body_shape.Set(vertices, count);

        b2FixtureDef body_fixture;

        body_fixture.shape = &body_shape;
        body_fixture.density = 1.00f;
        body_fixture.restitution = 0.50f;
        body_fixture.friction = 0.50f;


        body->CreateFixture(&body_fixture);

        return body;
    }
    
}