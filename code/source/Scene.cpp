/*
    @Author: Daniel Guerra Gallardo
    @program: Mechanism - 3D Animation
    @Date: 04/2021
    @Description: Desarollo mecánico de primitivas animadas fisicamente en un entorno de renderizado 2D
*/

#include "Scene.h"

namespace Graphics
{

    Scene::Scene(b2World& _physics_world, int _scene_id) : physics_world (&_physics_world), scene_id(_scene_id)
    {
        scene_init();
    }

    void Scene::scene_init()
    {

        switch (scene_id)
        {
        case 0: 
            run_scene1();
            break;
            
        default:
            break;
        }
        
    }

    void Scene::run_scene1()
    {
        Physics::Entity entity1(*physics_world, b2_staticBody, Body_Shape::Triangle, 2, 2, 0.5, 0.5);
        entity1.build_body();

        Physics::Entity entity2(*physics_world, b2_dynamicBody, Body_Shape::Polygon, 3.5, 2, 1, 0.5);
        entity2.build_body();
    }

    void Scene::update(b2World& _physics_world, float _delta_time)
    {
        physics_world->Step(delta_time, 8, 4);
    }

    void Scene::render(b2World& physics_world, RenderWindow& window, float scale)
    {
        // Se cachea el alto de la ventana en una variable local:

        float window_height = (float)window.getSize().y;

        // Se recorre toda la lista de bodies de physics_world:

        for (b2Body* body = physics_world.GetBodyList(); body != nullptr; body = body->GetNext())
        {
            // Se obtiene el transform del body:

            const b2Transform& body_transform = body->GetTransform();

            // Se recorre la lista de fixtures del body:

            for (b2Fixture* fixture = body->GetFixtureList(); fixture != nullptr; fixture = fixture->GetNext())
            {
                // Se obtiene el tipo de forma de la fixture:

                b2Shape::Type shape_type = fixture->GetShape()->GetType();

                if (shape_type == b2Shape::e_circle)
                {
                    // Se crea un CircleShape a partir de los atributos de la forma de la fixture y del body:
                    // En SFML el centro de un círculo no está en su position. Su position es la esquina superior izquierda
                    // del cuadrado en el que está inscrito. Por eso a position se le resta el radio tanto en X como en Y.

                    b2CircleShape* circle = dynamic_cast<b2CircleShape*>(fixture->GetShape());

                    float  radius = circle->m_radius * scale;
                    b2Vec2 center = circle->m_p;

                    CircleShape shape;

                    // Enlaza la posición del objeto creado en SFML (renderizado) y el objeto de físicas creado en Box2D (valores)
                    shape.setPosition(box2d_position_to_sfml_position(b2Mul(body_transform, center), window_height, scale) - Vector2f(radius, radius));
                    shape.setFillColor(Color::Blue);
                    shape.setRadius(radius);

                    window.draw(shape);
                }
                else
                    if (shape_type == b2Shape::e_polygon)
                    {
                        // Se toma la forma poligonal de Box2D (siempre es convexa) y se crea a partir de sus vértices un
                        // ConvexShape de SFML. Cada vértice de Box2D hay que transformarlo usando el transform del body.

                        b2PolygonShape* box2d_polygon = dynamic_cast<b2PolygonShape*>(fixture->GetShape());
                        ConvexShape       sfml_polygon;

                        int number_of_vertices = box2d_polygon->m_count;

                        sfml_polygon.setPointCount(number_of_vertices);
                        sfml_polygon.setFillColor(Color::Blue);

                        for (int index = 0; index < number_of_vertices; index++)
                        {
                            sfml_polygon.setPoint
                            (
                                index,
                                box2d_position_to_sfml_position(b2Mul(body_transform, box2d_polygon->m_vertices[index]), window_height, scale)
                            );
                        }

                        window.draw(sfml_polygon);
                    }
                    else
                        if (shape_type == b2Shape::e_chain)
                        {
                            // Se toma la forma poligonal de Box2D (siempre es convexa) y se crea a partir de sus vértices un
                            // ConvexShape de SFML. Cada vértice de Box2D hay que transformarlo usando el transform del body.

                            b2ChainShape* box2d_polygon = dynamic_cast<b2ChainShape*>(fixture->GetShape());
                            ConvexShape       sfml_polygon;

                            int number_of_vertices = box2d_polygon->m_count;

                            sfml_polygon.setPointCount(number_of_vertices);
                            sfml_polygon.setFillColor(Color::Blue);

                            for (int index = 0; index < number_of_vertices; index++)
                            {
                                sfml_polygon.setPoint
                                (
                                    index,
                                    box2d_position_to_sfml_position(b2Mul(body_transform, box2d_polygon->m_vertices[index]), window_height, scale)
                                );
                            }

                            window.draw(sfml_polygon);
                        }
            }
        }
    }
};

