#pragma once

/*
    @Author: Daniel Guerra Gallardo
    @program: Mechanism - 3D Animation
    @Date: 04/2021
    @Description: Desarollo mecánico de primitivas animadas fisicamente en un entorno de renderizado 2D
*/

#include <Box2D/Box2D.h>

#include "Scene.h"
#include <string>

using namespace std;

namespace Physics
{
    class CollisionHandle : public b2ContactListener
    {

    public:

        CollisionHandle();

    public:

        /// <summary>
        /// Registra una colisión entrante
        /// </summary>
        /// <param name="contact"> contacto que se produce entre fixtures de cuerpos </param>
        void BeginContact(b2Contact* contact); 

        /// <summary>
        /// Registra una salida de colisión
        /// </summary>
        /// <param name="contact">contacto que se produce entre fixtures de cuerpos </param>
        void EndContact(b2Contact* contact);


    };
};

