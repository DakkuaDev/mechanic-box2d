#pragma once

/*
    @Author: Daniel Guerra Gallardo
    @program: Mechanism - 3D Animation
    @Date: 04/2021
    @Description: Desarollo mecánico de primitivas animadas fisicamente en un entorno de renderizado 2D
*/

#include "World.h"
#include "Entity.h"

#include <SFML/Graphics.hpp>

class Entity;
class World;

using namespace sf;
using namespace std;
using namespace Physics;

namespace Graphics
{

    class Scene
    {
    private:

        b2World* physics_world;
        //sf::RenderWindow* window;

        int scene_id;
        float delta_time;

    public:

        Scene(b2World& _physics_world, int _scene_id);

    private:
        void scene_init();

    public:
        void run_scene1();
        void update(b2World& _physics_world, float _delta_time);

        /** En Box2D las coordenadas Y crecen hacia arriba y en SFML crecen hacia abajo desde el borde superior.
        * Esta función se encarga de convertir el sistema de coordenadas para que la escena no se vea invertida.
        */
        inline Vector2f box2d_position_to_sfml_position(const b2Vec2& box2d_position, float window_height, float scale)
        {
            return Vector2f(box2d_position.x * scale, window_height - box2d_position.y * scale);
        }

        // Renderiza la escena
        void render(b2World& physics_world, RenderWindow& window, float scale);
    };
   
}

