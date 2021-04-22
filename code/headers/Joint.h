#pragma once

/*
    @Author: Daniel Guerra Gallardo
    @program: Mechanism - 3D Animation
    @Date: 04/2021
    @Description: Desarollo mec�nico de primitivas animadas fisicamente en un entorno de renderizado 2D
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

        inline b2DistanceJointDef get_distance_jointDef()
        {
            return distance_jointDef;
        }

        inline b2RevoluteJointDef get_revolute_jointDef()
        {
            return revolute_jointDef;
        }

    public:

        /// <summary>
        /// Crea una uni�n entre dos cuerpos
        /// <param name="type"> tipo de uni�n. Distance = 1, Revolute = 2 </param>
        /// <param name="_length"> fuerza de distancia entre entidades </param>
        /// <param name="_stiffness"> par�metro que tiene que ver con el componente de resorte entre uniones </param>
        /// <param name="_damping"> par�metro que tiene que ver con el componente de resorte entre uniones </param>
        /// <param name="_enable_motor"> hacer que la uni�n sea capaz de actuar como componente mec�nico (motor) </param>
        /// <param name="_motor_speed"> velocidad del motor </param>
        /// <param name="_max_motor_torque"> fuerza del motor </param>
        /// </summary>
        void generate_joint
        (
            Joint_Type type,
            float _length = 10,
            float _stiffness = 3,
            float _damping = 0.1,
            bool _block_joint = false,
            bool _enable_motor = false,
            float _motor_speed = 0.0f, 
            float _max_motor_torque = 10.0f
        );

    };
}