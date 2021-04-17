#pragma once

/*
    @Author: Daniel Guerra Gallardo
    @program: Mechanism - 3D Animation
    @Date: 04/2021
    @Description: Desarollo mecánico de primitivas animadas fisicamente en un entorno de renderizado 2D
*/

#include <Box2D/Box2D.h>

using namespace std;

namespace Physics
{
    enum Joint_Type
    {
        Distance,
        Revolute
    };

    class Joint
    {
    private:

        b2World* world = nullptr;

        b2Body* body_a = nullptr;
        b2Body* body_b = nullptr;

        b2DistanceJointDef distance_jointDef;
        b2DistanceJoint* distance_joint = nullptr;
  
        b2RevoluteJointDef revolute_jointDef;
        b2RevoluteJoint* revolute_joint = nullptr;

        b2Vec2 anchor_a = b2Vec2(0,0);
        b2Vec2 anchor_b = b2Vec2(0,0);

    public:

        Joint(b2World& _world, b2Body& _body_a, b2Body& _body_b);

    public:

        void generate_joint(Joint_Type type, float _length = 10);

    };
}