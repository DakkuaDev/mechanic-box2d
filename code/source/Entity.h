
/*
    @Author: Daniel Guerra Gallardo
    @program: Mechanism - 3D Animation
    @Date: 04/2021
    @Description: Desarollo mecánico de primitivas animadas fisicamente en un entorno de renderizado 2D
*/

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "World.h"

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

        float cordX, cordY;
        float width, height;
        float radius;

    public:
        Entity(b2BodyType _body_type, Body_Shape _body_shape);
        Entity(b2BodyType _body_type, Body_Shape _body_shape, float _cordX, float _cordY, float _width, float _height);

    private:

        void generate_body(Body_Shape _body_shape, float w, float h);


    };
}
