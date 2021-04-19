#pragma once

/*
    @Author: Daniel Guerra Gallardo
    @program: Mechanism - 3D Animation
    @Date: 04/2021
    @Description: Desarollo mecánico de primitivas animadas fisicamente en un entorno de renderizado 2D
*/

#include <Box2D/Box2D.h>
#include <memory>
#include <string>

namespace Physics
{

    enum Body_Shape
    {
        Polygon,
        Triangle,
        Circle,
    };

    class Entity
    {

    private:

        b2World* world = nullptr;

        b2Body* body = nullptr;
        b2BodyType body_type;
        b2BodyDef body_definition;

        b2FixtureDef body_fixture;

        Body_Shape body_shape;
        b2PolygonShape polygon_shape;
        b2CircleShape circle_shape;

        float cordX = 0, cordY = 0;
        float width = 1, height = 1;
        float radius = 0.5;

        std::string entity_tag = "";

    public:
        Entity(b2World& _world, b2BodyType _body_type, Body_Shape _body_shape);
        Entity(b2World& _world, b2BodyType _body_type, Body_Shape _body_shape, float _cordX, float _cordY, float _radius);
        Entity(b2World& _world, b2BodyType _body_type, Body_Shape _body_shape, float _cordX, float _cordY, float _width, float _height);

    public:

        inline b2Body* get_body()
        {
            return body;
        }

        /// <summary>
        /// Crea una escucha necesaria para registrar eventos de colisiones sobre la entidad
        /// </summary>
        inline void set_userdata()
        {
            body->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);
        }

        /// <summary>
        /// Añade a la entidad un tag que puedas usar para identificarlo
        /// </summary>
        /// <param name="new_tag"></param>
        inline void set_tag(std::string new_tag)
        {
            entity_tag = new_tag;
        }

        /// <summary>
        /// Devuelve el tag asociado a la entidad
        /// </summary>
        /// <returns> tag de la entidad. Si no se la ha asignado ninguno estará vacio</returns>
        inline std::string get_tag()
        {
            return entity_tag;
        }

    public:

        /// <summary>
        /// Contruye el cuerpo añadiéndole fixtures y propiedades
        /// </summary>
        /// <param name="density"> Densidad del body </param>
        /// <param name="restitution"> Coeficiente de restitución del body</param>
        /// <param name="friction"> Coeficiente de fricción del body</param>
        void build_body(float density = 1.00f, float restitution = 0.75f, float friction = 0.50);

    private:
        /// <summary>
        /// En base a su BodyShape, se genera la forma del cuerpo que luego se van a dibujar
        /// </summary>
        /// <param name="_body_shape"> forma del cuerpo. Polygon = 0, Triangle = 1, Circle = 2</param>
        /// <param name="w"> ancho del cuerpo generado</param>
        /// <param name="h"> alto del cuerpo generado</param>
        void generate_body(Body_Shape _body_shape, float w, float h);

        // TODO: Obtener el color y otras propiedades de sfml asociadas a cada entidad
    };
}
