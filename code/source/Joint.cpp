
/*
    @Author: Daniel Guerra Gallardo
    @program: Mechanism - 3D Animation
    @Date: 04/2021
    @Description: Desarollo mecánico de primitivas animadas fisicamente en un entorno de renderizado 2D
*/

#include "Joint.h"

namespace Physics
{
    Joint::Joint(b2World& _world, b2Body& _body_a, b2Body& _body_b)
        : world(&_world), body_a(&_body_a), body_b(&_body_b) {}

    void Joint::generate_joint(Joint_Type type, float _length, float _stiffness, float _damping, bool _block_joint, bool _enable_motor, float _motor_speed, float _max_motor_torque)
    {
        if (type == Joint_Type::Distance)
        {
            distance_jointDef.bodyA = body_a;
            distance_jointDef.bodyB = body_b;

            // Longitud de equilibrio
            distance_jointDef.length = _length;

            // Propiedades de resorte
            distance_jointDef.stiffness = _stiffness;
            distance_jointDef.damping = _damping;

            distance_jointDef.Initialize(body_a, body_b, body_a->GetWorldCenter(), body_b->GetWorldCenter());

            distance_joint = (b2DistanceJoint*)world->CreateJoint(&distance_jointDef);

            
        }
        else if (type == Joint_Type::Revolute)
        {
            revolute_jointDef.bodyA = body_a;
            revolute_jointDef.bodyB = body_b;

            if (_block_joint)
            {
                revolute_jointDef.lowerAngle = 0;
                revolute_jointDef.upperAngle = 0;
                revolute_jointDef.enableLimit = true;
            }

            // El motor de la joint se encuentra activado
            if (_enable_motor)
            {
                revolute_jointDef.enableMotor = true;
                revolute_jointDef.motorSpeed = _motor_speed;
                revolute_jointDef.maxMotorTorque = _max_motor_torque;
            }

            // Inicializo el joint con los cuerpos y los puntos de unión
            revolute_jointDef.Initialize(body_a, body_b, body_a->GetWorldCenter());

            revolute_joint = (b2RevoluteJoint*)world->CreateJoint(&revolute_jointDef);
        }
    }
}