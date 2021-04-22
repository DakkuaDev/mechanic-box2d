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
            run_test_scene();
            break;
        case 1:
            run_exercise_scene();
            
        default:
            break;
        }
        
    }


    void Scene::BeginContact(b2Contact* contact)
    {
        b2Fixture* fixtureA = contact->GetFixtureA();
        b2Fixture* fixtureB = contact->GetFixtureB();

        b2Body* bodyA = fixtureA->GetBody();
        b2Body* bodyB = fixtureB->GetBody();

        Physics::Entity* entityA = (Physics::Entity*)bodyA->GetUserData().pointer;
        Physics::Entity* entityB = (Physics::Entity*)bodyB->GetUserData().pointer;

        if (entityA != NULL && entityB != NULL)
        {
            if (entityA->get_tag() == "platform_1" && entityB->get_tag() == "player")
            {
                platform1_moving = true;
            }

            if (entityA->get_tag() == "platform_2" && entityB->get_tag() == "player")
            {
                platform2_moving = true;
            }
        }
    }

    void Scene::run_test_scene()
    {

        Physics::Entity player(*physics_world, b2_dynamicBody, Body_Shape::Circle, 6.2, 8, 0.25);
        player.build_body(1, 0.2, 0.5);

        Physics::Entity triangle(*physics_world, b2_staticBody, Body_Shape::Triangle, 4.5, 0.5, 0.25);
        triangle.build_body(1, 0.05, 0.5);

        Physics::Entity wheel1(*physics_world, b2_dynamicBody, Body_Shape::Circle, 5, 5, 0.2);
        wheel1.build_body(1, 0.2, 0.5);
        Physics::Entity wheel2(*physics_world, b2_dynamicBody, Body_Shape::Circle, 5.6, 5, 0.2);
        wheel2.build_body(1, 0.2, 0.5);

        Physics::Entity car(*physics_world, b2_dynamicBody, Body_Shape::Polygon, 5.3, 5.40, 0.6, 0.10);
        car.build_body(1, 0.2, 0.5);
        Physics::Entity car_i(*physics_world, b2_dynamicBody, Body_Shape::Polygon, 4.75, 5.60, 0.05, 0.3);
        car_i.build_body(1, 0.2, 0.5);
        Physics::Entity car_d(*physics_world, b2_dynamicBody, Body_Shape::Polygon, 5.85, 5.60, 0.05, 0.3);
        car_d.build_body(1, 0.2, 0.5);

        Physics::Entity floor(*physics_world, b2_staticBody, Body_Shape::Polygon, 6, 0, 10, 0.5);
        floor.build_body();

        Physics::Joint joint1(*physics_world, *wheel1.get_body(), *car.get_body());
        joint1.generate_joint(Joint_Type::Revolute, 0.5, 0.5);
        Physics::Joint joint2(*physics_world, *wheel2.get_body(), *car.get_body());
        joint2.generate_joint(Joint_Type::Revolute, 0.5, 0.5);
        Physics::Joint joint3(*physics_world, *car.get_body(), *car_i.get_body());
        joint3.generate_joint(Joint_Type::Revolute, 0.5, 0.5);
        Physics::Joint joint4(*physics_world, *car.get_body(), *car_d.get_body());
        joint4.generate_joint(Joint_Type::Revolute, 0.5, 0.5);

    }

    void Scene::run_exercise_scene()
    {
        physics_world->SetContactListener(this);

        // JUGADOR
        entities["player"].reset(new Physics::Entity(*physics_world, b2_dynamicBody, Body_Shape::Circle, 2, 2.8, 0.25));
        auto &player = *entities["player"];
        player.set_tag("player");

        // PLATAFORMAS
        entities["platform_1"].reset(new Physics::Entity(*physics_world, b2_kinematicBody, Body_Shape::Polygon, 11.65, -0.75f, 1.25f, 0.20f));
        auto& platform_1 = *entities["platform_1"];
        platform_1.set_tag("platform_1");

        entities["platform_2"].reset(new Physics::Entity(*physics_world, b2_kinematicBody, Body_Shape::Polygon, 4.5f, 2.5f, 1.10f, 0.20f));
        auto& platform_2 = *entities["platform_2"];
        platform_2.set_tag("platform_2");


        // MECANISMOS
        // ----------- Trasnbordador --------------
        Physics::Entity wheel1(*physics_world, b2_dynamicBody, Body_Shape::Circle, 1.7, 1.7, 0.2);
        wheel1.build_body(1, 0.2, 0.5);
        Physics::Entity wheel2(*physics_world, b2_dynamicBody, Body_Shape::Circle, 2.3, 1.7, 0.2);
        wheel2.build_body(1, 0.2, 0.5);

        Physics::Entity car(*physics_world, b2_dynamicBody, Body_Shape::Polygon, 2, 2.1, 0.6, 0.10);
        car.build_body(1, 0.2, 0.5);
        Physics::Entity car_i(*physics_world, b2_dynamicBody, Body_Shape::Polygon, 1.45, 2.3, 0.05, 0.3);
        car_i.build_body(1, 0.2, 0.5);
        Physics::Entity car_d(*physics_world, b2_dynamicBody, Body_Shape::Polygon, 2.55, 2.3, 0.05, 0.3);
        car_d.build_body(1, 0.2, 0.5);

        // Joints
        Physics::Joint car_joint1(*physics_world, *wheel1.get_body(), *car.get_body());
        car_joint1.generate_joint(Joint_Type::Revolute, 0.5, 0.5);
        Physics::Joint car_joint2(*physics_world, *wheel2.get_body(), *car.get_body());
        car_joint2.generate_joint(Joint_Type::Revolute, 0.5, 0.5);
        Physics::Joint car_joint3(*physics_world, *car.get_body(), *car_i.get_body());
        car_joint3.generate_joint(Joint_Type::Revolute, 0.5, 0.5);
        Physics::Joint car_joint4(*physics_world, *car.get_body(), *car_d.get_body());
        car_joint4.generate_joint(Joint_Type::Revolute, 0.5, 0.5);

        // -------------- Rotor ------------------
        Physics::Entity rotor_engine(*physics_world, b2_dynamicBody, Body_Shape::Circle, 1.15, 1.05, 0.1);
        rotor_engine.build_body();
        Physics::Entity rotor(*physics_world, b2_dynamicBody, Body_Shape::Polygon, 1.25, 1.05, 0.225, 0.025);
        rotor.build_body();

        Physics::Entity rotor_engine2(*physics_world, b2_dynamicBody, Body_Shape::Circle, 5.15, 5.05, 0.1);
        rotor_engine2.build_body();
        Physics::Entity rotor2(*physics_world, b2_dynamicBody, Body_Shape::Polygon, 5.25, 5.05, 0.5, 0.025);
        rotor2.build_body();

        // Joints
        Physics::Joint rotor_joint(*physics_world, *rotor_engine.get_body(), *rotor.get_body());
        rotor_joint.generate_joint(Joint_Type::Revolute, 10, 3, 0.1, false, true, 12.7, 25);

        Physics::Joint rotor_joint2(*physics_world, *rotor_engine2.get_body(), *rotor2.get_body());
        rotor_joint2.generate_joint(Joint_Type::Revolute, 10, 3, 0.1, false, true, 12.5, 20);


        // ESCENARIO
        // --------- Piso Inferior ----------------

        // Estáticos (Izquierda a derecha)
        Physics::Entity floor_1(*physics_world, b2_staticBody, Body_Shape::Polygon, 2.20f, -0.2, 1.1f, 0.75f);
        Physics::Entity floor_2(*physics_world, b2_staticBody, Body_Shape::Polygon, 6.85f, -0.75f, 3.5f, 0.20f);
        Physics::Entity floor_3(*physics_world, b2_staticBody, Body_Shape::Triangle, 3.35f, -0.5f, 1, 1);

        // --------- Piso Superior ----------------

        // Estáticos (Derecha a izquierda)
        Physics::Entity floor_4(*physics_world, b2_staticBody, Body_Shape::Polygon, 9.38f, 4.35f, 0.85f, 0.20f);
        Physics::Entity floor_5(*physics_world, b2_staticBody, Body_Shape::Polygon, 7.65f, 3.49f, 1.4f, 0.15f);
        Physics::Entity floor_6(*physics_world, b2_staticBody, Body_Shape::Polygon, 6.20f, 2.5f, 0.55f, 0.20f);

        Physics::Entity goal_1(*physics_world, b2_staticBody, Body_Shape::Polygon, 2.8, 4.f, 0.75f, 0.05f);
        Physics::Entity goal_2(*physics_world, b2_staticBody, Body_Shape::Polygon, 1.7, 4.f, 0.75f, 0.05f);

        Physics::Entity wall_d(*physics_world, b2_staticBody, Body_Shape::Polygon, 13.25, 2.5f, 0.25f, 5);
        Physics::Entity wall_i(*physics_world, b2_staticBody, Body_Shape::Polygon, 0.9, 5.f, 0.10f, 1.25);

        // Construimos los cuerpos y su perfil de datos (para poder identificarlos)

        player.build_body(1,0.3,0.25);
        player.set_userdata();

        platform_1.build_body();
        platform_2.build_body();
        platform_1.set_userdata();
        platform_2.set_userdata();

        floor_1.build_body();
        floor_2.build_body();
        floor_3.build_body();
        floor_4.build_body();
        floor_5.build_body();
        floor_6.build_body();

        goal_1.build_body();
        goal_2.build_body();

        wall_d.build_body();
        wall_i.build_body();

        // Trasformaciones de giro
        floor_5.get_body()->SetTransform(floor_5.get_body()->GetPosition(), 95.f);
        goal_1.get_body()->SetTransform(goal_1.get_body()->GetPosition(), 95.f);
        goal_2.get_body()->SetTransform(goal_2.get_body()->GetPosition(), -95.f);

        // Joints extras para bloquear primitivas
        Physics::Joint rotor_joint_union(*physics_world, *rotor_engine.get_body(), *floor_1.get_body());
        rotor_joint_union.generate_joint(Joint_Type::Revolute, 0.5, 1, 1, true);

        Physics::Joint rotor_joint_union2(*physics_world, *rotor_engine2.get_body(), *floor_6.get_body());
        rotor_joint_union2.generate_joint(Joint_Type::Revolute, 0.5, 1, 1, true);

        Physics::Joint wall_i_union3(*physics_world, *wall_i.get_body(), *floor_1.get_body());
        wall_i_union3.generate_joint(Joint_Type::Revolute, 0.5, 1, 1, true);

        Physics::Joint wall_d_union4(*physics_world, *wall_d.get_body(), *floor_4.get_body());
        wall_d_union4.generate_joint(Joint_Type::Revolute, 0.5, 1, 1, true);
        
    }

    void Scene::update(b2World& _physics_world, float _delta_time)
    {
        // Plataforma inferior
        if (platform1_moving)
        {
           
            if (entities["platform_1"]->get_body()->GetPosition().y <= 4.35)
            {
                entities["platform_1"]->get_body()->SetLinearVelocity({ 0, 1.8 });
            }
            else
            {
                entities["platform_1"]->get_body()->SetLinearVelocity({ 0, 0 });
                platform1_moving = false;
            }
        }
        else
        {
            if (entities["platform_1"]->get_body()->GetPosition().y >= -0.7)
            {
                entities["platform_1"]->get_body()->SetLinearVelocity({ 0, -1.8 });
            }
            else entities["platform_1"]->get_body()->SetLinearVelocity({ 0, 0 });
        }

        // Plataforma superior
        if (platform2_moving)
        {

            if (entities["platform_2"]->get_body()->GetPosition().y <= 4.35)
            {
                entities["platform_2"]->get_body()->SetLinearVelocity({ 0, 3.75 });
            }
            else
            {
                entities["platform_2"]->get_body()->SetLinearVelocity({ 0, 0 });
                platform2_moving = false;
            }
        }
        else
        {
            if (entities["platform_2"]->get_body()->GetPosition().y >= 2.55)
            {
                entities["platform_2"]->get_body()->SetLinearVelocity({ 0, -2.2 });
            }
            else entities["platform_2"]->get_body()->SetLinearVelocity({ 0, 0 });
        }
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

