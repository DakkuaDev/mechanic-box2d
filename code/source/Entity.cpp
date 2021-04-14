
/*
    @Author: Daniel Guerra Gallardo
    @program: Mechanism - 3D Animation
    @Date: 04/2021
    @Description: Desarollo mecánico de primitivas animadas fisicamente en un entorno de renderizado 2D
*/

#include "Entity.h"

using namespace sf;
using namespace std;

class World;

namespace 
{
    class Entity
    {

    private:


        enum Body_Shape
        {
            Polygon,
            Triangle,
            Circle,
        };

        World world;

        b2Body* body;
        b2BodyDef body_definition;
        b2FixtureDef body_fixture;

        float cordX = 0, cordY = 0;
        float width = 1, height = 1;
        float radius = 1;

    public:
        Entity(b2BodyType _body_type, Body_Shape _body_shape)
        {   
            // body definition
            body_definition.type = _body_type;
            body_definition.position.Set(cordX, cordY);

            // get into world
            body = world.get_world()->CreateBody(&body_definition);

            // generate body
            generate_body(_body_shape, width, height);

            // adding fixture
            body_fixture.density = 1.00f;
            body_fixture.restitution = 0.75f;
            body_fixture.friction = 0.50f;

            body->CreateFixture(&body_fixture);

        }
        Entity(b2BodyType _body_type, Body_Shape _body_shape, float _cordX, float _cordY, float _width, float _height)
        {
            // body definition
            body_definition.type = _body_type;
            body_definition.position.Set(_cordX, _cordY);

            // get into world
            body = world.get_world()->CreateBody(&body_definition);

            // generate body
            generate_body(_body_shape, _width, _height);

            // adding fixture
            body_fixture.density = 1.00f;
            body_fixture.restitution = 0.75f;
            body_fixture.friction = 0.50f;

            body->CreateFixture(&body_fixture);
        }

    private:

        void generate_body(Body_Shape _body_shape, float w, float h)
        {
            if (_body_shape == Body_Shape::Polygon)
            {
                b2PolygonShape body_shape;
                body_fixture.shape = &body_shape;

                body_shape.SetAsBox(width, height);
            }
            else if (_body_shape == Body_Shape::Triangle)
            {
                b2PolygonShape body_shape;
                body_fixture.shape = &body_shape;

                b2Vec2 vertices[3];

                vertices[0].Set(0.0f, 0.0f);
                vertices[1].Set(1.0f, 0.0f);
                vertices[2].Set(0.0f, 1.0f);

                int32 count = 3;

                body_shape.Set(vertices, count);
            }
            else if (_body_shape == Body_Shape::Circle)
            {
                b2CircleShape body_shape;
                body_fixture.shape = &body_shape;

                body_shape.m_radius = radius;
            }
        }

    };
}
