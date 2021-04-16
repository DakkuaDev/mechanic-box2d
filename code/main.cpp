/*
    @Author: Daniel Guerra Gallardo
    @program: Mechanism - 3D Animation
    @Date: 04/2021
    @Description: Desarollo mecánico de primitivas animadas fisicamente en un entorno de renderizado 2D
*/

#include <iostream>
#include <memory>
#include <vector>

#include "WorldGenerator.h"
#include "Render.h"
#include "Shape.h"

#include "World.h"
#include "Entity.h"
#include "Scene.h"

using namespace std;

// Método hardcoreado (old)
using namespace physics; 
using namespace drawing; 

// Método POO, ordenado
using namespace Physics; // classes: World, Entity (Box2D PHYSICS)
using namespace Graphics;

const int WIDTH = 1200;
const int HEIGHT = 720;

int main ()
{

    // Creo la ventana
    RenderWindow window(VideoMode(WIDTH, HEIGHT), "Mechanism - 3D Animation. Daniel Guerra Gallardo", Style::Titlebar | Style::Close, ContextSettings(32));
    window.setVerticalSyncEnabled(true);

    // Creo una vista, que me va a permitir adaptar el contenido de la pantalla para que al cambiar su resolución se ajusten sus coordenadas (fixed)
    View view;
    view.reset(sf::FloatRect(100, 100, WIDTH, HEIGHT));
    window.setView(view);


    // Creo el mundo (donde se van a gestionar las físicas)
    Physics::World physics_world;

    // Creo la escena de mundo, la cual va a ser visualizada en el viewport
    Graphics::Scene scene(*physics_world.get_world(), 1);

    const float physics_to_graphics_scale = 100.f;      // Escala para pasar de unidades de física a unidades de gráficos

    const float target_fps  = 60.f;                     // Cuántos fotogramas por segundo se busca conseguir
    const float target_time = 1.f / target_fps;         // Duración en segundos de un fotograma a la tasa deseada
    
    float delta_time = target_time;                     // Previsión de la duración del fotograma actual
    bool  running    = true;

    Clock timer;

    do
    {
        timer.restart ();

        // Process window events:

        Event event;

        while (window.pollEvent (event))
        {
            if (event.type == Event::Closed)
            {
                running = false;
            }
        }

        // Update:

        physics_world.get_world()->Step(delta_time, 8, 4);
        // DONT WORK ???
        //scene.update(*physics_world.get_world(), delta_time);

        // Render:

        window.clear ();

        scene.render(*physics_world.get_world(), window, physics_to_graphics_scale);

        window.display ();

        // Si resulta necesario se detiene la ejecución unos instantes para no exceder la tasa de
        // fotogramas por segundo deseada:

        float elapsed = timer.getElapsedTime ().asSeconds ();

        if (elapsed < target_time)
        {
            sleep (seconds (target_time - elapsed));
        }

        // Se restablece la estimación de la duración del siguiente fotograma:

        delta_time = timer.getElapsedTime ().asSeconds ();
    }
    while (running);

    return EXIT_SUCCESS;
}
