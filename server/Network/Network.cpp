/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Network
*/

#include "Network.hpp"

Network::Network() {}

Network::Network(World *world)
{
    _world = world;
}

Network::~Network() {}

void Network::print_hex(const std::vector<unsigned char>& buffer) {
    for (unsigned char byte : buffer) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte) << " ";
    }
    std::cout << std::dec << std::endl;
}

std::string Network::buffer_to_string(const std::vector<unsigned char>& buffer) {
    return std::string(buffer.begin(), buffer.end());
}

void Network::print_message(const std::vector<unsigned char>& buffer) {
    std::string message = buffer_to_string(buffer);
    std::cout << "Message reçu : " << message << std::endl;
}

void Network::killEntity(Message<Protocol> msg)
{
    // try {
    //     int index;
    //     bool explosion;
    //     msg >> explosion;
    //     msg >> index;
    //     Registry &reg = _world->getRegistry();
    //     Registry &regOnline = _world->getOnlineRegistry();
    //     ComponentArray<Drawable> &drawables = reg.get_components<Drawable>();
    //     ComponentArray<Drawable> &drawablesOnline = regOnline.get_components<Drawable>();
    //     int entities = _world->getNbEntities();
    //     sf::IntRect rectSprite = sf::IntRect(0, 0, 36, 36);
    //     if (!drawablesOnline[index] || !drawablesOnline[index].has_value())
    //         throw std::length_error("error");
    //     if (!drawablesOnline[index]->getKind() == Drawable::SPRITE || explosion == false) {
    //         regOnline.kill_entity(regOnline.entity_from_index(index));
    //     } else {
    //         drawables[index]->setPath("explosion");
    //         drawables[index]->setAngle(0);
    //         drawables[index]->setRect(rectSprite);
    //     }
    // } catch (std::length_error) {
    //     throw Error(Error::MISTAKE::ERROR_IN_RECEIVE_MESSAGE);
    // }
}

void Network::createEntity(Message<Protocol> msg)
{
    // try {
    //     float rotation, posx, posy;
    //     sf::IntRect rectSprite;
    //     char name[10];
    //     int index;
    //     msg >> rotation;
    //     msg >> rectSprite.width;
    //     msg >> rectSprite.height;
    //     msg >> rectSprite.top;
    //     msg >> rectSprite.left;
    //     msg >> posy;
    //     msg >> posx;
    //     msg >> name;
    //     msg >> index;
    //     Registry &reg = _world->getRegistry();
    //     int entities = _world->getNbEntities();
    //     index += entities;
    //     ComponentArray<Position> &positions = reg.get_components<Position>();
    //     ComponentArray<Drawable> &drawables = reg.get_components<Drawable>();
    //     if (drawables[index] && drawables[index].has_value() && positions[index] && positions[index].has_value()) {
    //         positions[index]->setPosition(posx, posy);
    //         drawables[index]->setAngle(rotation);
    //         drawables[index]->setRect(rectSprite);
    //         drawables[index]->setPath(name);
    //     } else {
    //         Entity player = reg.spawn_entity();
    //         positions.insert_at(entities, Position(posx, posy));
    //         drawables.insert_at(entities, Drawable(name, Drawable::SPRITE, {1,1}, rectSprite, rotation));
    //         entities = _world->getTestEntities() + 1;
    //         _world->setTestEntities(entities);
    //     }
    // } catch (std::length_error) {
    //     throw Error(Error::MISTAKE::ERROR_IN_RECEIVE_MESSAGE);
    // }
}

void Network::receive_string(Message<Protocol> msg)
{
    try {
        uint32_t stringSize;
        msg >> stringSize;
        if (msg.body.size() < stringSize) {
            throw std::runtime_error("Taille de chaîne invalide ou corruption du message !");
        }
        std::string receivedString(stringSize, '\0');
        std::memcpy(&receivedString[0], msg.body.data() + msg.body.size() - stringSize, stringSize);
        msg.body.resize(msg.body.size() - stringSize);
        std::cout << "String reçu : " << receivedString << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Erreur lors de la désérialisation : " << e.what() << std::endl;
    }
}

void Network::receive_messages(NetworkClient& client, World& world, std::atomic<bool>& running)
{
    // while (running.load()) {
    //     if (client.HasMessages()) {
    //         auto msg = client.PopMessage();
    //         std::cout << "Message reçu du serveur avec ID : " << static_cast<uint32_t>(msg.header.id) << std::endl;

    //         //print_message(msg.body);
    //         try {
    //             switch (msg.header.id) {
    //                 case Protocol::SERVER_OK: {
    //                     std::cout << "Connexion réussie avec le serveur !" << std::endl;
    //                     receive_string(msg);
    //                     break;
    //                 }
    //                 case Protocol::SERVER_ENTITY_NEW: {
    //                     SceneScreen currentScreen;
    //                     createEntity(msg);
    //                     std::cout << "Nouvelle entité ajoutée dans le monde." << std::endl;
    //                     break;
    //                 }
    //                 case Protocol::SERVER_ENTITY_HIT: {
    //                     SceneScreen currentScreen;
    //                     killEntity(msg);
    //                     std::cout << "Nouvelle entité tuées dans le monde." << std::endl;
    //                     break;
    //                 }
    //                 default:
    //                     std::cout << "Message inconnu reçu avec ID : " << static_cast<uint32_t>(msg.header.id) << std::endl;
    //                     break;
    //             }
    //         } catch (Error &e) {
    //             std::cerr << e.what() << std::endl;
    //         }
    //     }
    //     std::this_thread::sleep_for(std::chrono::milliseconds(10));
    // }
}

void Network::send_join_message(NetworkClient& client) {
    Message<Protocol> joinMsg;
    joinMsg.header.id = Protocol::CLIENT_JOIN;
    joinMsg << "join";
    client.send(joinMsg);
    std::cout << "Message de connexion envoyé au serveur." << std::endl;
}

void Network::send_leave_message(NetworkClient& client) {
    Message<Protocol> leaveMsg;
    leaveMsg.header.id = Protocol::CLIENT_LEAVE;
    leaveMsg << "leave";
    client.send(leaveMsg);
    std::cout << "Message de déconnexion envoyé au serveur." << std::endl;
}

void Network::sendGetRoomMessage(NetworkClient& client)
{
    // Message<Protocol> getRoomMsg;
    // getRoomMsg.header.id = Protocol::CLIENT_GET_ROOM;
    // getRoomMsg << _world->getTestEntities();
    // client.send(getRoomMsg);
    // std::cout << "Get room." << std::endl;
}

void Network::sendKillEntity(NetworkClient& client)
{
    // Message<Protocol> getRoomMsg;
    // getRoomMsg.header.id = Protocol::CLIENT_KILL_ENTITY;
    // getRoomMsg << _world->getTestEntities();
    // client.send(getRoomMsg);
    // std::cout << "Kill entity." << std::endl;
}

void Network::sendCreateRoom(NetworkClient& client, std::string name, std::string password, bool isPublic, size_t maxPlayer)
{
    Message<Protocol> createRoomMsg;
    std::size_t nameSize = name.size();
    std::size_t passwordSize = password.size();

    createRoomMsg.header.id = Protocol::CLIENT_CREATE_ROOM;
    for (int i = name.length() - 1; i >= 0 ; i--)
        createRoomMsg << name.at(i);
    createRoomMsg << nameSize;
    for (int i = password.length() - 1; i >= 0 ; i--)
        createRoomMsg << password.at(i);
    createRoomMsg << passwordSize;
    createRoomMsg << isPublic;
    createRoomMsg << maxPlayer;
    client.send(createRoomMsg);
    std::cout << "Send create message." << std::endl;
}

void Network::sendJoinRoom(NetworkClient& client)
{
    // Message<Protocol> joinRoomMsg;
    // joinRoomMsg.header.id = Protocol::CLIENT_JOIN_ROOM;
    // joinRoomMsg << _world->getRoomName();
    // client.send(joinRoomMsg);
    // std::cout << "Join room." << std::endl;
}

void Network::interactive_send(NetworkClient& client, std::atomic<bool>& running) {
    std::string input;
    while (running.load()) {
        std::cout << "Entrez un message à envoyer (ou 'exit' pour quitter) : ";
        std::getline(std::cin, input);

        if (input == "exit") {
            running.store(false);
            break;
        }

        Message<Protocol> userMsg;
        userMsg << input;
        client.send(userMsg);

        std::cout << "Message envoyé : " << input << std::endl;
    }
}
