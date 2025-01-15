#include <iostream>
#include "server.hpp"
#include "../client/client.hpp"

#ifdef _WIN32
    #define PATH "../../"
#else
    #define PATH "../"
#endif

#include "Logic/include/ECS/World.hpp"
#include "Logic/include/ECS/Registry.hpp"
#include "Logic/include/ECS/Entity.hpp"
#include "Logic/include/Systems.hpp"
#include "Logic/include/ECS/ComponentArray.hpp"
#include "Logic/include/Components/Position.hpp"

#include <SFML/Graphics.hpp>
#include <thread>

UDPServer::UDPServer(uint16_t port) : server_socket(io_context, udp::endpoint(udp::v4(), port)), receive_buffer(1024) {
    std::cout << "Server is listening on port " << port << "...\n";
}

void UDPServer::start() {
    try {
        while (true) {
            udp::endpoint client_endpoint;
            size_t length = server_socket.receive_from(asio::buffer(receive_buffer), client_endpoint);
            std::cout << "Received binary data from " << client_endpoint << ": ";
            printHex(receive_buffer, length);

            processPacket(receive_buffer);
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}
void UDPServer::printHex(const std::vector<uint8_t>& data, size_t length) {
    for (size_t i = 0; i < length; ++i) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(data[i]) << " ";
    }
    std::cout << std::dec << std::endl;
}

void UDPServer::processPacket(const std::vector<uint8_t>& packet) {
    if (packet.empty()) {
        std::cerr << "Received an empty packet.\n";
        return;
    }

    uint8_t action_type = packet[0];
    switch (action_type) {
        case 1:
            handleMovement(packet);
            break;
        case 2:
            handleShoot(packet);
            break;
        default:
            std::cerr << "Unknown action type: " << static_cast<int>(action_type) << std::endl;
    }
}

void UDPServer::handleMovement(const std::vector<uint8_t>& packet) {
    if (packet.size() < 17) {
        std::cerr << "Invalid packet size for movement.\n";
        return;
    }
    float posX, posY, speedX, speedY;

    std::memcpy(&posX, &packet[1], sizeof(float));
    std::memcpy(&posY, &packet[5], sizeof(float));
    std::memcpy(&speedX, &packet[9], sizeof(float));
    std::memcpy(&speedY, &packet[13], sizeof(float));

    std::cout << "Player moving to X: " << posX << ", Y: " << posY
              << " with speed X: " << speedX << ", Y: " << speedY << std::endl;
}


void UDPServer::handleShoot(const std::vector<uint8_t>& packet) {
    if (packet.size() < 9) {
        std::cerr << "Invalid packet size for shoot.\n";
        return;
    }

    float posX, posY;
    uint8_t type;

    std::memcpy(&posX, &packet[1], sizeof(float));
    std::memcpy(&posY, &packet[5], sizeof(float));
    type = packet[9];

    std::cout << "Player shooting from X: " << posX << ", Y: " << posY
              << " with type: " << static_cast<int>(type) << std::endl;
}


int main(void)
{
    World world;

    Systems systems;

    systems.loadSystemsInWorld(world);

    Registry &reg = world.getRegistry();

    std::string path = PATH;

    //todo Maybe fix this, otherwise leave this beautiful code alone
    //auto debug = reg.spawn_entity();
    //reg.add_component(debug, Projectile(20, 0.6, false, false, 0.0f, 0.4));
    //reg.kill_entity(debug);


    //auto ennemy = reg.spawn_entity();
    //reg.add_component(ennemy, Velocity(sf::Vector2i(0, 2), 0.0f, 0.0f));
    //reg.add_component(ennemy, Position(sf::Vector2f(600, 0)));
    //reg.add_component(ennemy, LinearShooter(1.5f, true));

    world.addClientInWorld(0, "0000");
    // world.addClientInWorld(1, "0000");

    auto ennemy_t = reg.spawn_entity();
    //world.spawnEntityFromGeneratedWorld(7, 1900, 570, 10);
    //world.spawnEntityFromGeneratedWorld(5, 1990, 570);
    reg.add_component(ennemy_t, Position(1200, 100));
    reg.add_component(ennemy_t, Ennemy(2, std::make_shared<BigShip>(0.1f)));
    //reg.add_component(ennemy_t, Position(1900, 570));
    // reg.add_component(ennemy_t, Ennemy(2, std::make_shared<SinusoidalShooter>(1.6f, 6.0f, 0.08f, -8.0f)));
    // reg.add_component(ennemy_t, Ennemy(4, std::make_shared<LinearShooter>()));
    // reg.add_component(ennemy_t, Ennemy(2, new LinearShooter(2, true, 2)));
    // reg.add_component(ennemy_t, TpShooter(2.0));
    //reg.add_component(ennemy_t, Hitbox(Hitbox::RECTANGLE, Vector<int, 2>(1900, 510), Vector<int, 2>(99, 99), ennemy_t, false));
    reg.add_component(ennemy_t, Velocity(sf::Vector2i(-2, 1), 0.0, 0.01));
    reg.add_component(ennemy_t, Hitbox(Hitbox::RECTANGLE, Vector<int, 2>(1400, 3000), Vector<int, 2>(180 * 4, 148 * 4), ennemy_t, false));

    reg.add_component(ennemy_t, Drawable::Drawable(
         //"tpshooter", true, sf::Vector2f(3, 3),
         //{Drawable::FrameRect(0, 0, 33, 33), Drawable::FrameRect(33, 0, 33, 33)}, 0.6f,
         //{}, 0.6f, {}, 0.6f, {}, 0.6f, {}, 0.6f
         //)
        //"boss", true, sf::Vector2f(4, 4),
        //{Drawable::FrameRect(0, 0, 162, 213), Drawable::FrameRect(162, 0, 162, 213), Drawable::FrameRect(324, 0, 162, 213),
        //Drawable::FrameRect(324, 213, 162, 213), Drawable::FrameRect(162, 213, 162, 213), Drawable::FrameRect(0, 213, 162, 213)}, 0.6f,
        //{}, 0.6f, {}, 0.6f, {}, 0.6f, {}, 0.6f
        //)
        "boss", true, sf::Vector2f(4, 4),
        {Drawable::FrameRect(0, 0, 180, 148), Drawable::FrameRect(189, 0, 180, 148)}, 0.2f,
        {}, 0.6f, {}, 0.6f, {}, 0.6f, {}, 0.6f
        )
    );
    //reg.add_component(ennemy_t, Controllable(1));
    //reg.add_component(ennemy_t, Hitbox(Hitbox::CIRCULAR, Vector<int, 2>(400, 400), Vector<int, 2>(34, 33)));

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Entity Simulation");
    window.setFramerateLimit(60);

    sf::Texture texture;
    if (!texture.loadFromFile(path + "server/Logic/assets/sprite2.png")) {
        return -1;
    }

    sf::Texture texture2;
    if (!texture2.loadFromFile(path + "server/Logic/assets/sprite_third_boss.png")) {
        return -1;
    }


    sf::Sprite sprite(texture);
    sprite.setScale(3, 3);
    sf::Sprite sprite2(texture2);
    sprite2.setScale(4, 4);
    // sprite.setOrigin(0, 33/2); NATTAN TU M'AS FAIS GALERER ICI
    // sprite.setScale(sf::Vector2f(1,1));

    world.setStateOfTheWorld(World::STATE::PLAY);

    sf::RectangleShape rectangle;
    sf::RectangleShape hi(sf::Vector2f(33, 33));
    sf::CircleShape c;

    auto &controllables = reg.get_components<Controllable>();

    VirtualKeyBoard &testkb = controllables[0]->getVirtualKeyboard();

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
        auto &hitboxsR = reg.get_components<Hitbox>();
        auto &ennemies = reg.get_components<Ennemy>();
        auto &areas = reg.get_components<Area>();

        world.applyFonctionInWorld();

        std::size_t index = 0;
        std::size_t index2 = 0;
        window.clear(sf::Color::Black);

        for (auto &d : drawable) {
            if (d && d.has_value() && positions[index] && positions[index].has_value()) {
                if (index < ennemies.size() && ennemies[index].has_value()) {
                    sprite2.setPosition(positions[index]->getPosition().x, positions[index]->getPosition().y);
                    Drawable::FrameRect &rect = d->getCurrentRect();
                    sprite2.setTextureRect(sf::IntRect(rect._rectLeft, rect._rectTop, rect._rectWidth, rect._rectHeight));
                    window.draw(sprite2);
                } else {
                    sprite.setPosition(positions[index]->getPosition().x, positions[index]->getPosition().y);
                    Drawable::FrameRect &rect = d->getCurrentRect();
                    sprite.setTextureRect(sf::IntRect(rect._rectLeft, rect._rectTop, rect._rectWidth, rect._rectHeight));
                    window.draw(sprite);
                }
            }
            index++;
        }

        for (auto &p : projectile) {
            if (p && p.has_value() && positions[index2] && positions[index2].has_value() && projectile[index2].has_value()) {
                rectangle.setSize(sf::Vector2f(hitboxsR[index2]->getSize()[0], hitboxsR[index2]->getSize()[1]));
                rectangle.setPosition(positions[index2]->getPosition().x, positions[index2]->getPosition().y);
                window.draw(rectangle);
            }
            index2++;
        }

        for (auto &h : hitboxsR) {
            if (h && h.has_value()) {
                hi.setPosition(h->getPosition()[0], h->getPosition()[1]);
                hi.setRotation(h->getRotation());
                hi.setSize(sf::Vector2f(h->getSize()[0], h->getSize()[1]));
                hi.setFillColor(sf::Color::Transparent);
                hi.setOutlineColor(sf::Color::Cyan);
                hi.setOutlineThickness(1.0f);
                window.draw(hi);
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
