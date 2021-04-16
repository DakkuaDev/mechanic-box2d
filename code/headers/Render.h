/*
    @Author: Daniel Guerra Gallardo
    @program: Mechanism - 3D Animation
    @Date: 04/2021
    @Description: Desarollo mecánico de primitivas animadas fisicamente en un entorno de renderizado 2D
*/

#pragma once

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "World.h"

using namespace sf;
using namespace std;

namespace drawing
{
    /** En Box2D las coordenadas Y crecen hacia arriba y en SFML crecen hacia abajo desde el borde superior.
    * Esta función se encarga de convertir el sistema de coordenadas para que la escena no se vea invertida.
    */
    inline Vector2f box2d_position_to_sfml_position(const b2Vec2& box2d_position, float window_height, float scale)
    {
        return Vector2f(box2d_position.x * scale, window_height - box2d_position.y * scale);
    }

    // Renderiza la escena
    void render(b2World& physics_world, RenderWindow& window, float scale);
    
}