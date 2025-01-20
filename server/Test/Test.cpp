/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Test
*/

#include <iostream>

#include "../Logic/include/Components/Position.hpp"
#include "../Logic/include/ECS/ComponentArray.hpp"
#include "../Logic/include/ECS/Entity.hpp"
#include "../Logic/include/ECS/Registry.hpp"
#include "../Logic/include/ECS/World.hpp"
#include "../Logic/include/Systems.hpp"
#include <SFML/Graphics.hpp>

#ifdef _WIN32
#define PATH "../../"
#else
#define PATH "../"
#endif

int flagTest(void)
{
    World world(false, false, 2, "Test", 0, "0000");

    Systems systems;

    systems.loadSystemsInWorld(world);

    Registry &reg = world.getRegistry();

    std::string path = PATH;

    // todo Maybe fix this, otherwise leave this beautiful code alone
    // auto debug = reg.spawn_entity();
    // reg.add_component(debug, Projectile(20, 0.6, false, false, 0.0f, 0.4));
    // reg.kill_entity(debug);

    // auto ennemy = reg.spawn_entity();
    // reg.add_component(ennemy, Velocity(sf::Vector2i(0, 2), 0.0f, 0.0f));
    // reg.add_component(ennemy, Position(sf::Vector2f(600, 0)));
    // reg.add_component(ennemy, LinearShooter(1.5f, true));

    // world.addClientInWorld(0, "0000");
    world.addClientInWorld(1, "0000");

    CreateEntity &ce = world.getClassCreateEntity();

    //ce.createPlayerAI(sf::Vector2f(1200, 100), 10, reg, 2);

    // ce.createAlienEmperor(sf::Vector2f(1200, 100), reg, 10);
    // ce.createSpatialDustman(sf::Vector2f(1650, 400), reg, 10);
    // ce.createBigShip(sf::Vector2f(1200, 100), reg, 10);
    //    ce.createSinusoidaleShooterShinny(sf::Vector2f(2000, 540), reg, 10);
    //    ce.createSinusoidaleShooterShinny(sf::Vector2f(4000, 540), reg, 13);
    //    ce.createSinusoidaleShooterShinny(sf::Vector2f(6000, 540), reg, 13);
    // auto ennemy_t = reg.spawn_entity();
    //  world.spawnEntityFromGeneratedWorld(7, 1900, 570, 10);
    //  world.spawnEntityFromGeneratedWorld(5, 1990, 570);
    // reg.add_component(ennemy_t, Position(1200, 100));
    // reg.add_component(ennemy_t, Ennemy(2, std::make_shared<BigShip>(0.2f)));
    // reg.add_component(
    //    ennemy_t, Hitbox::Hitbox(sf::Vector2f(1650, 400),
    //                  {Hitbox::RectHitbox(Hitbox::RECTANGLE, sf::Vector2f(1650, 400), 180 * 4, 148 * 4, false)}, 10,
    //                  Hitbox::ENNEMY));
    // reg.add_component(ennemy_t, Velocity(sf::Vector2i(-2, 1), 0.0, 0.01));
    // reg.add_component(ennemy_t, Drawable::Drawable("boss", true, sf::Vector2f(4, 4),
    //                                {Drawable::FrameRect(0, 0, 180, 148), Drawable::FrameRect(189, 0, 180, 148)},
    //                                0.2f,
    //                                {}, 0.6f, {}, 0.6f, {}, 0.6f, {}, 0.6f));
    //{Drawable::FrameRect(0, 0, 162, 213), Drawable::FrameRect(162, 0, 162, 213),
    //     Drawable::FrameRect(324, 0, 162, 213), Drawable::FrameRect(324, 213, 162, 213),
    //     Drawable::FrameRect(162, 213, 162, 213), Drawable::FrameRect(0, 213, 162, 213)},
    // 0.6f, {}, 0.6f, {}, 0.6f, {}, 0.6f, {}, 0.6f)
    // reg.add_component(ennemy_t, Controllable(1));
    // reg.add_component(ennemy_t, Hitbox(Hitbox::CIRCULAR, Vector<int, 2>(400, 400), Vector<int, 2>(34, 33)));

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Entity Simulation");
    window.setFramerateLimit(60);

    sf::Texture texture2;
    if (!texture2.loadFromFile(path + "server/Logic/assets/sprite_third_boss.png")) {
        return -1;
    }

    sf::Texture texture3;
    if (!texture3.loadFromFile(path + "server/Logic/assets/players_sking.png")) {
        return -1;
    }

    sf::Sprite sprite2(texture2);
    sprite2.setScale(4, 4);
    sf::Sprite sprite3(texture3);
    sprite3.setScale(2.5, 2.5);
    // sprite.setOrigin(0, 33/2); NATTAN TU M'AS FAIS GALERER ICI
    // sprite.setScale(sf::Vector2f(1,1));

    world.setStateOfTheWorld(World::STATE::PLAY);

    sf::RectangleShape rectangle;
    sf::RectangleShape hi(sf::Vector2f(33, 33));
    sf::CircleShape c;

    auto &controllables = reg.get_components<Controllable>();

    VirtualKeyBoard &testkb = controllables[0]->getVirtualKeyboard();

    NetworkServer server(0);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (controllables[0].has_value()) {
                if (event.type == sf::Event::KeyPressed) {
                    switch (event.key.code) {
                    case sf::Keyboard::Z:
                        testkb.changeValueKeyboard(VirtualKeyBoard::UP, true);
                        break;
                    case sf::Keyboard::Q:
                        testkb.changeValueKeyboard(VirtualKeyBoard::LEFT, true);
                        break;
                    case sf::Keyboard::S:
                        testkb.changeValueKeyboard(VirtualKeyBoard::DOWN, true);
                        break;
                    case sf::Keyboard::D:
                        testkb.changeValueKeyboard(VirtualKeyBoard::RIGHT, true);
                        break;
                    case sf::Keyboard::Space:
                        testkb.changeValueKeyboard(VirtualKeyBoard::SHOOT, true);
                        break;
                    case sf::Keyboard::F:
                        testkb.changeValueKeyboard(VirtualKeyBoard::FORCE, true);
                        break;
                    default:
                        break;
                    }
                }

                if (event.type == sf::Event::KeyReleased) {
                    switch (event.key.code) {
                    case sf::Keyboard::Z:
                        testkb.changeValueKeyboard(VirtualKeyBoard::UP, false);
                        break;
                    case sf::Keyboard::Q:
                        testkb.changeValueKeyboard(VirtualKeyBoard::LEFT, false);
                        break;
                    case sf::Keyboard::S:
                        testkb.changeValueKeyboard(VirtualKeyBoard::DOWN, false);
                        break;
                    case sf::Keyboard::D:
                        testkb.changeValueKeyboard(VirtualKeyBoard::RIGHT, false);
                        break;
                    case sf::Keyboard::Space:
                        testkb.changeValueKeyboard(VirtualKeyBoard::SHOOT, false);
                        break;
                    case sf::Keyboard::F:
                        testkb.changeValueKeyboard(VirtualKeyBoard::FORCE, false);
                        break;
                    default:
                        break;
                    }
                }
            }
        }
        auto &positions = reg.get_components<Position>();
        auto &projectile = reg.get_components<Projectile>();
        auto &drawable = reg.get_components<Drawable::Drawable>();
        auto &linear = reg.get_components<LinearShooter>();
        auto &hitboxsR = reg.get_components<Hitbox::Hitbox>();
        auto &ennemies = reg.get_components<Ennemy>();
        auto &areas = reg.get_components<Area>();

        world.applyFonctionInWorld(server);

        std::size_t index = 0;
        std::size_t index2 = 0;
        window.clear(sf::Color::Black);

        for (auto &d : drawable) {
            if (d && d.has_value() && positions[index] && positions[index].has_value()) {
                if (index < ennemies.size() && ennemies[index].has_value()) {
                    Drawable::FrameRect &rect = d->getCurrentRect();
                    sprite2.setPosition(positions[index]->getPosition().x, positions[index]->getPosition().y);
                    sprite2.setTextureRect(
                        sf::IntRect(rect._rectLeft, rect._rectTop, rect._rectWidth, rect._rectHeight));
                    window.draw(sprite2);
                } else {
                    Drawable::FrameRect &rect = d->getCurrentRect();
                    sprite3.setPosition(positions[index]->getPosition());
                    sprite3.setTextureRect(
                        sf::IntRect(rect._rectLeft, rect._rectTop, rect._rectWidth, rect._rectHeight));
                    window.draw(sprite3);
                }
            }
            index++;
        }

        for (auto &p : projectile) {
            if (p && p.has_value() && positions[index2] && positions[index2].has_value() &&
                projectile[index2].has_value()) {
                rectangle.setSize(
                    sf::Vector2f(hitboxsR[index2]->getSizeHitbox(0).x, hitboxsR[index2]->getSizeHitbox(0).y));
                rectangle.setPosition(positions[index2]->getPosition().x, positions[index2]->getPosition().y);
                window.draw(rectangle);
            }
            index2++;
        }

        for (auto &h : hitboxsR) {
            if (h && h.has_value()) {
                for (const Hitbox::RectHitbox &r : h->getAllHitboxs()) {
                    hi.setPosition(r.XHitbox, r.YHitbox);
                    hi.setRotation(r.rotation);
                    hi.setSize(sf::Vector2f(r.widthHitbox, r.heightHitbox));
                    hi.setFillColor(sf::Color::Transparent);
                    hi.setOutlineColor(sf::Color::Cyan);
                    hi.setOutlineThickness(1.0f);
                    window.draw(hi);
                }
            }
        }
        for (auto &area : areas) {
            if (area && area.has_value()) {
                c.setRadius(area->getRadius());
                c.setPosition(sf::Vector2f(area->getPosition()[0], area->getPosition()[1]));
                c.setFillColor(sf::Color::Transparent);
                c.setOutlineColor(sf::Color::Magenta);
                c.setOutlineThickness(2.0f);
                window.draw(c);
            }
        }

        window.display();
    }

    //    try {
    //        UDPServer server(9000);
    //        server.start();
    //    } catch (const UDPClient::ClientError& e) {
    //        std::cerr << "Error: " << e.what() << "\nDetails: " << e.details() << std::endl;
    //    }
    //
    return 0;
}
