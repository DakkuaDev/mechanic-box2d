/*
    @Author: Daniel Guerra Gallardo
    @program: Mechanism - 3D Animation
    @Date: 04/2021
    @Description: Desarollo mec�nico de primitivas animadas fisicamente en un entorno de renderizado 2D
*/

#include "Render.h";

namespace world_render
{
    void render(b2World& physics_world, RenderWindow& window, float scale)
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
                    // En SFML el centro de un c�rculo no est� en su position. Su position es la esquina superior izquierda
                    // del cuadrado en el que est� inscrito. Por eso a position se le resta el radio tanto en X como en Y.

                    b2CircleShape* circle = dynamic_cast<b2CircleShape*>(fixture->GetShape());

                    float  radius = circle->m_radius * scale;
                    b2Vec2 center = circle->m_p;

                    CircleShape shape;

                    // Enlaza la posici�n del objeto creado en SFML (renderizado) y el objeto de f�sicas creado en Box2D (valores)
                    shape.setPosition(box2d_position_to_sfml_position(b2Mul(body_transform, center), window_height, scale) - Vector2f(radius, radius));
                    shape.setFillColor(Color::Blue);
                    shape.setRadius(radius);

                    window.draw(shape);
                }
                else
                    if (shape_type == b2Shape::e_edge)
                    {
                        // Se toman los dos v�rtices del segmento y se ajusta su posici�n usando el transform del body.
                        // Los v�rtices resultantes se convierten y se ponen en un array para finalmente dibujar el segmento
                        // que los une usando la sobrecarga del m�todo draw() que permite dibujar primitivas de OpenGL a
                        // partir de datos de v�rtices.

                        b2EdgeShape* edge = dynamic_cast<b2EdgeShape*>(fixture->GetShape());

                        b2Vec2 start = b2Mul(body_transform, edge->m_vertex1);
                        b2Vec2 end = b2Mul(body_transform, edge->m_vertex2);

                        Vertex line[] =
                        {
                            Vertex(box2d_position_to_sfml_position(start, window_height, scale), Color::Green),
                            Vertex(box2d_position_to_sfml_position(end, window_height, scale), Color::Green),
                        };

                        window.draw(line, 2, Lines);
                    }
                    else
                        if (shape_type == b2Shape::e_polygon)
                        {
                            // Se toma la forma poligonal de Box2D (siempre es convexa) y se crea a partir de sus v�rtices un
                            // ConvexShape de SFML. Cada v�rtice de Box2D hay que transformarlo usando el transform del body.

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
            }
        }
    }
}