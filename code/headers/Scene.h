#pragma once

/*
    @Author: Daniel Guerra Gallardo
    @program: Mechanism - 3D Animation
    @Date: 04/2021
    @Description: Desarollo mecánico de primitivas animadas fisicamente en un entorno de renderizado 2D
*/

#include "World.h"
#include "Entity.h"
#include "Joint.h"
#include "CollisionHandle.h"

#include <SFML/Graphics.hpp>

class Entity;
class World;
class Joint;
class CollisionHandle;


using namespace sf;
using namespace std;
using namespace Physics;

namespace Graphics
{

    class Scene
    {
    private:

        Physics::Entity* player = nullptr;

        b2World* physics_world = nullptr;

        int scene_id;                           // Identificador de escena 
        float delta_time;                       // Refresco del bucle

    public:
        bool collision = false;

    public:

        Scene(b2World& _physics_world, int _scene_id);

    private:
        void scene_init();

    public:

        /// <summary>
        /// Escena de prueba
        /// </summary>
        void run_test_scene();

        /// <summary>
        /// Escena del escenario final
        /// </summary>
        void run_exercise_scene();

        void collision_test();

        /// <summary>
        /// Bucle principal de la escena. Llama a las físicas y luego al dibujado de sprites
        /// </summary>
        void update(b2World& _physics_world, float _delta_time);

        /** En Box2D las coordenadas Y crecen hacia arriba y en SFML crecen hacia abajo desde el borde superior.
        * Esta función se encarga de convertir el sistema de coordenadas para que la escena no se vea invertida.
        */
        inline Vector2f box2d_position_to_sfml_position(const b2Vec2& box2d_position, float window_height, float scale)
        {
            return Vector2f(box2d_position.x * scale, window_height - box2d_position.y * scale);
        }

        /// <summary>
        /// Renderizado de escena en el viewport
        /// <param name="physics_world"> instancia de b2World del mundo físico </param>
        /// <param name="window"> ventana del viewport de la aplicación </param>
        /// <param name="scale"> factor de escanal entre las unidades de sfml (renderizado) y box2d (fisicas) </param>
        /// </summary>
        void render(b2World& physics_world, RenderWindow& window, float scale);
    };
   
}

