
/*
    @Author: Daniel Guerra Gallardo
    @program: Mechanism - 3D Animation
    @Date: 04/2021
    @Description: Desarollo mecánico de primitivas animadas fisicamente en un entorno de renderizado 2D
*/

#include "Entity.h"

using namespace std;

namespace Physics
{

    Entity::Entity(b2World& _world, b2BodyType _body_type, Body_Shape _body_shape)
        : world(&_world), body_type(_body_type), body_shape(_body_shape) {}

    Entity::Entity(b2World& _world, b2BodyType _body_type, Body_Shape _body_shape, float _cordX, float _cordY, float _radius)
        : world(&_world), body_type(_body_type), body_shape(_body_shape), cordX(_cordX), cordY(_cordY), radius (_radius) {}


    Entity::Entity(b2World& _world, b2BodyType _body_type, Body_Shape _body_shape, float _cordX, float _cordY, float _width, float _height)
        : world(&_world), body_type(_body_type), body_shape(_body_shape), cordX(_cordX), cordY(_cordY), width(_width), height(_height) {}


    void Entity::build_body(float density, float restitution, float friction)
    {
        // body definition
        body_definition.type = body_type;
        body_definition.position.Set(cordX, cordY);

        // lo añado al mundo
        body = world->CreateBody(&body_definition);

        // genero el body en base a su BodyShape
        generate_body(body_shape, width, height);

        // le añado fixtures
        body_fixture.density = density;
        body_fixture.restitution = restitution;
        body_fixture.friction = friction;

        body->CreateFixture(&body_fixture);
    }

    void Entity::generate_body(Body_Shape _body_shape, float w, float h)
    {
        if (_body_shape == Body_Shape::Polygon)
        {
            body_fixture.shape = &polygon_shape;

            polygon_shape.SetAsBox(width, height);
        }
        else if (_body_shape == Body_Shape::Triangle)
        {
            body_fixture.shape = &polygon_shape;

            b2Vec2 vertices[3];

            vertices[0].Set(0.0f, 0.0f);
            vertices[1].Set(1.0f, 0.0f);
            vertices[2].Set(0.0f, 1.0f);

            int32 count = 3;

            polygon_shape.Set(vertices, count);
        }
        else if (_body_shape == Body_Shape::Circle)
        {
            body_fixture.shape = &circle_shape;

            circle_shape.m_radius = radius;
        }
    }   
}
