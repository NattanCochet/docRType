/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Network
*/

#include "Network.hpp"
#include "../ECS/Message.hpp"

Network::Network()
{
}

/*SERVER_ENTITY_DEAD,        // Server notifies of an entity's destruction
    SERVER_GAME_END,           // Server notifies the end of the game
    SERVER_UPDATE_POSITION,       // Server updates player or game statistics
*/

Network::Network(World *world)
{
    _world = world;
    _mapFunc = {
        {Protocol::SERVER_OK, okAnswer},
        {Protocol::SERVER_KO, koAnswer},
        {Protocol::SERVER_UPDATE_POSITION, createEntity}, // A réparer
        {Protocol::SERVER_ENTITY_DEAD, killEntity},
        {Protocol::SERVER_SEND_ROOMS, getRoomsServer},
        {Protocol::SERVER_WELL_CREATED_ROOM, roomCreated},
        {Protocol::SERVER_NBR_CLIENT_IN_ROOM, clientsInRoom},
        {Protocol::SERVER_START_GAME, startGame},
        {Protocol::SERVER_GAME_END, gameEnd},
    };
}

Network::~Network()
{
}

void Network::print_hex(const std::vector<unsigned char> &buffer)
{
    for (unsigned char byte : buffer) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte) << " ";
    }
    std::cout << std::dec << std::endl;
}

std::string Network::buffer_to_string(const std::vector<unsigned char> &buffer)
{
    return std::string(buffer.begin(), buffer.end());
}

void Network::print_message(const std::vector<unsigned char> &buffer)
{
    std::string message = buffer_to_string(buffer);
    std::cout << "Message reçu : " << message << std::endl;
}

void Network::killEntity(World *world, Message<Protocol> msg)
{
    try {
        std::size_t index;
        bool explosion;
        msg >> explosion;
        msg >> index;
        Registry &reg = world->getRegistry();
        Registry &regOnline = world->getOnlineRegistry();
        ComponentArray<Drawable> &drawables = reg.get_components<Drawable>();
        ComponentArray<Drawable> &drawablesOnline = regOnline.get_components<Drawable>();
        std::cout << "kill: " << index << std::endl;
        sf::IntRect rectSprite = sf::IntRect(0, 0, 36, 36);
        if (!drawablesOnline[index] || !drawablesOnline[index].has_value())
            throw std::length_error("error");
        if (!drawablesOnline[index]->getKind() == Drawable::SPRITE || explosion == false) {
            std::cout << "KILLLLL !!!" << std::endl;
            regOnline.kill_entity(regOnline.entity_from_index(index));
        } else {
            drawables[index]->setPath("explosion");
            drawables[index]->setAngle(0);
            drawables[index]->setRect(rectSprite);
        }
    }
    catch (std::length_error) {
        throw Error(Error::MISTAKE::ERROR_IN_RECEIVE_MESSAGE);
    }
}

void Network::gameEnd(World *world, Message<Protocol> msg)
{
    world->setState(World::LOBBY_MENU);
}

void Network::createEntity(World *world, Message<Protocol> msg)
{
    try {
        float rotation = 0, posx = 0, posy = 0;
        sf::IntRect rectSprite;
        std::string name;
        std::size_t index = 0;
        std::size_t stringSize = 0;
        msg >> rotation;
        msg >> rectSprite.height;
        msg >> rectSprite.width;
        msg >> rectSprite.left;
        msg >> rectSprite.top;
        msg >> posy;
        msg >> posx;
        msg >> stringSize;
        for (size_t i = 0; i < stringSize; ++i) {
            char c;
            msg >> c;
            name.push_back(c);
        }
        /*std::cout << name << ", " << posx << ", " << posy << ", " << rectSprite.left << ", " << rectSprite.top << ", "
                  << rectSprite.height << ", " << rectSprite.width << ", " << rotation << std::endl;*/
        msg >> index;
        Registry &reg = world->getOnlineRegistry();
        ComponentArray<Position> &positions = reg.get_components<Position>();
        ComponentArray<Drawable> &drawables = reg.get_components<Drawable>();
        ComponentArray<Controllable> &controls = reg.get_components<Controllable>();
        size_t indexCheck = 0;
        if (drawables.size() > index && drawables[index] && drawables[index].has_value() && positions[index] &&
            positions[index].has_value()) {
            positions[index]->setPosition(posx, posy);
            drawables[index]->setAngle(rotation);
            drawables[index]->setRect(rectSprite);
            drawables[index]->setPath(name);
            return;
        }
        /*for (std::optional<Drawable> &drawable : drawables) {
            if (index == indexCheck && drawable && drawable.has_value() && positions[index] &&
                positions[index].has_value()) {
                positions[index]->setPosition(posx, posy);
                drawable->setAngle(rotation);
                drawable->setRect(rectSprite);
                drawable->setPath(name);
                return;
            }
            indexCheck++;
        }*/
        std::cout << "Entity created: " << index << std::endl;
        Entity player = reg.spawn_entity();
        if (world->getLocalPlayer() == -1 && name == "Player") { // world->getLocalPlayer() == -1 &&
            std::cout << "Player Index: " << index << std::endl;
            controls.insert_at(index, Controllable());
            world->setLocalPlayer(index);
        }
        positions.insert_at(index, Position(posx, posy));
        drawables.insert_at(index, Drawable(name, Drawable::SPRITE, {1, 1}, rectSprite, rotation));
    }
    catch (std::length_error) {
        throw Error(Error::MISTAKE::ERROR_IN_RECEIVE_MESSAGE);
    }
}

void Network::getRoomsServer(World *world, Message<Protocol> msg)
{
    try {
        std::size_t index = 0;
        bool isPublic = true;
        std::size_t clientInRoom = 0;
        std::size_t maxPlayer = 0;
        std::size_t sizeName;
        std::string name;
        msg >> sizeName;
        for (size_t i = 0; i < sizeName; ++i) {
            char c;
            msg >> c;
            name.push_back(c);
        }
        msg >> maxPlayer;
        msg >> clientInRoom;
        msg >> isPublic;
        msg >> index;
        world->addRoomsList({index, isPublic, maxPlayer, clientInRoom, name});
    }
    catch (std::length_error) {
        throw Error(Error::MISTAKE::ERROR_IN_RECEIVE_MESSAGE);
    }
}

void Network::roomCreated(World *world, Message<Protocol> msg)
{
    try {
        std::size_t index = 0;
        msg >> index;
        world->setRoomIndex(index);
        world->setState(World::LOBBY_MENU);
        std::cout << "Room created." << std::endl;
    }
    catch (std::length_error) {
        throw Error(Error::MISTAKE::ERROR_IN_RECEIVE_MESSAGE);
    }
}

void Network::clientsInRoom(World *world, Message<Protocol> msg)
{
    try {
        size_t nbInRoom = 0;
        msg >> nbInRoom;
        std::pair<std::size_t, std::size_t> nbInRoomPair = world->getNbInRoom();
        world->setNbInRoom({nbInRoom, nbInRoomPair.second});
        std::map<std::string, int> keys = world->getKeysIndex();
        if (keys["LobbyPlayerCountText"] >= 0) {
            std::stringstream ss;
            ss << nbInRoom << " / " << nbInRoomPair.second;
            world->getRegistry().get_components<Drawable>()[keys["LobbyPlayerCountText"]]->setMessage(ss.str());
        }
    }
    catch (std::length_error) {
        throw Error(Error::MISTAKE::ERROR_IN_RECEIVE_MESSAGE);
    }
}

void Network::startGame(World *world, Message<Protocol> msg)
{
    try {
        world->setState(World::IN_GAME);
        std::cout << "Game start." << std::endl;
    }
    catch (std::length_error) {
        throw Error(Error::MISTAKE::ERROR_IN_RECEIVE_MESSAGE);
    }
}

void Network::okAnswer(World *world, Message<Protocol> msg)
{
    try {
        World::GAME_STATE gameState = world->getState();
        if (gameState == World::MENU)
            world->setServerConnection(true);
        if (gameState == World::NETWORK_MENU)
            world->setState(World::LOBBY_MENU);
    }
    catch (std::length_error) {
        throw Error(Error::MISTAKE::ERROR_IN_RECEIVE_MESSAGE);
    }
}

void Network::koAnswer(World *world, Message<Protocol> msg)
{
    try {
        std::size_t sizeString = 0;
        msg >> sizeString;
        std::string receivedMessage = "";
        for (size_t i = 0; i < sizeString; ++i) {
            char c;
            msg >> c;
            receivedMessage.push_back(c);
        }
        World::GAME_STATE gameState = world->getState();
        if (gameState == World::NETWORK_MENU) {
            ComponentArray<Drawable> &drawables = world->getRegistry().get_components<Drawable>();
            drawables[world->getKeysIndex()["roomErrorText"]]->setMessage(receivedMessage);
        }
        world->setRoomName("");
        world->setRoomIndex(0);
        world->setNbInRoom({0, 0});
    }
    catch (std::length_error) {
        throw Error(Error::MISTAKE::ERROR_IN_RECEIVE_MESSAGE);
    }
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
    }
    catch (const std::exception &e) {
        std::cerr << "Erreur lors de la désérialisation : " << e.what() << std::endl;
    }
}

void Network::receive_messages(NetworkClient &client, World &world, std::atomic<bool> &running)
{
    while (running.load()) {
        if (client.HasMessages()) {
            auto msg = client.PopMessage();
            // std::cout << "Message reçu du serveur avec ID : " << static_cast<uint32_t>(msg.header.id) << std::endl;

            // print_message(msg.body);
            /*const std::vector<boost::asio::detail::buffered_stream_storage::byte_type> recup;
            msg >> recup;
            std::string recupStr = buffer_to_string(recup);*/
            try {
                if (_mapFunc.contains(msg.header.id)) {
                    _mapFunc[msg.header.id](_world, msg);
                }
            }
            catch (Error &e) {
                std::cerr << e.what() << std::endl;
            }
        }
        // std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void Network::send_join_message(NetworkClient &client)
{
    Message<Protocol> joinMsg;
    joinMsg.header.id = Protocol::CLIENT_JOIN;
    joinMsg << "join";
    client.send(joinMsg);
    std::cout << "Connection message sent to server." << std::endl;
}

void Network::send_leave_message(NetworkClient &client)
{
    Message<Protocol> leaveMsg;
    leaveMsg.header.id = Protocol::CLIENT_LEAVE;
    leaveMsg << "leave";
    client.send(leaveMsg);
    std::cout << "Deconnection message sent to server." << std::endl;
}

void Network::sendKeyboard(NetworkClient &client, bool isPressed, int key)
{
    Message<Protocol> keyBoardMsg;
    keyBoardMsg.header.id = Protocol::CLIENT_KEYBOARD;
    keyBoardMsg << isPressed;
    keyBoardMsg << key;
    client.send(keyBoardMsg);
}

void Network::sendGetRoomMessage(NetworkClient &client)
{
    Message<Protocol> getRoomMsg;
    getRoomMsg.header.id = Protocol::CLIENT_GET_ROOM;
    getRoomMsg << "";
    _world->clearRoomsList();
    client.send(getRoomMsg);
    std::cout << "Get room." << std::endl;
}

void Network::sendJoinRoom(NetworkClient &client, size_t roomId, std::string password)
{
    Message<Protocol> joinRoomMsg;
    joinRoomMsg.header.id = Protocol::CLIENT_JOIN_ROOM;
    joinRoomMsg << roomId;
    for (int i = password.length() - 1; i >= 0; i--)
        joinRoomMsg << password.at(i);
    joinRoomMsg << password.length();
    client.send(joinRoomMsg);
    std::cout << "Join room." << std::endl;
}

void Network::sendLeaveRoom(NetworkClient &client, size_t roomId)
{
    Message<Protocol> leaveRoomMsg;
    leaveRoomMsg.header.id = Protocol::CLIENT_LEAVE_ROOM;
    leaveRoomMsg << roomId;
    client.send(leaveRoomMsg);
    std::cout << "Leave room." << std::endl;
}

void Network::sendCreateRoom(
    NetworkClient &client, std::string name, std::string password, bool isPublic, size_t maxPlayer)
{
    Message<Protocol> createRoomMsg;
    std::size_t nameSize = name.size();
    std::size_t passwordSize = password.size();

    createRoomMsg.header.id = Protocol::CLIENT_CREATE_ROOM;
    for (int i = name.length() - 1; i >= 0; i--)
        createRoomMsg << name.at(i);
    createRoomMsg << nameSize;
    for (int i = password.length() - 1; i >= 0; i--)
        createRoomMsg << password.at(i);
    createRoomMsg << passwordSize;
    createRoomMsg << isPublic;
    createRoomMsg << maxPlayer;
    client.send(createRoomMsg);
    std::cout << "Send create room." << std::endl;
}

void Network::sendReady(NetworkClient &client)
{
    Message<Protocol> readyMsg;
    readyMsg.header.id = Protocol::CLIENT_READY;
    readyMsg << "";
    client.send(readyMsg);
    std::cout << "Ready." << std::endl;
}

void Network::sendUnReady(NetworkClient &client)
{
    Message<Protocol> unReadyMsg;
    unReadyMsg.header.id = Protocol::CLIENT_UNREADY;
    unReadyMsg << "";
    client.send(unReadyMsg);
    std::cout << "Unready." << std::endl;
}

void Network::interactive_send(NetworkClient &client, std::atomic<bool> &running)
{
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
