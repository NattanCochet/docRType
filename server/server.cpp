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

    world.addClientInWorld(1, "0000");

    auto ennemy_t = reg.spawn_entity();
    reg.add_component(ennemy_t, Position(400, 400));
    reg.add_component(ennemy_t, LinearShooter(1.5f, true));
    reg.add_component(ennemy_t, Velocity(sf::Vector2i(0, 2), 0.0f, 0.0f));
    Vector <float, 4> rect(34, 33, 0, 0.4f);

    reg.add_component(ennemy_t, Drawable("./assets/sprite2.png", rect, true, sf::Vector2f(10,10), true, {4, 3}, {2, 1}));
    //reg.add_component(ennemy_t, Controllable(1));
    //reg.add_component(ennemy_t, Hitbox(Hitbox::CIRCULAR, Vector<int, 2>(400, 400), Vector<int, 2>(34, 33)));

    sf::RenderWindow window(sf::VideoMode(1000, 800), "Entity Simulation");
    window.setFramerateLimit(60);

    sf::Texture texture;
    if (!texture.loadFromFile(path + "server/Logic/assets/sprite2.png")) {
        return -1;
    }

    sf::Sprite sprite(texture);
    sprite.setScale(3, 3);
    sprite.setOrigin(0, 33/2);
    // sprite.setScale(sf::Vector2f(1,1));

    sf::RectangleShape rectangle(sf::Vector2f(30, 10));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        auto &positions = reg.get_components<Position>();
        auto &projectile = reg.get_components<Projectile>();
        auto &drawable = reg.get_components<Drawable>();
        auto &linear = reg.get_components<LinearShooter>();

        for (std::function<int (World &)> func : reg.get_systems()) {
            func(world);
        }

        std::size_t index = 0;
        std::size_t index2 = 0;
        window.clear(sf::Color::Black);
        for (auto &d: drawable) {
            if (positions[index] && positions[index].has_value()) {
                sprite.setPosition(positions[index]->getPosition().x, positions[index]->getPosition().y);
                sprite.setTextureRect(d->getTextRect());
                window.draw(sprite);
            }
            index++;
        }
        for (auto &p: projectile) {
            if (positions[index2] && positions[index2].has_value() && projectile[index2].has_value()) {
                rectangle.setPosition(positions[index2]->getPosition().x, positions[index2]->getPosition().y);
                window.draw(rectangle);
            }
            index2++;
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
