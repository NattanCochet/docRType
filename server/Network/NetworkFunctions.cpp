/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** NetworkFunctions
*/

#include "NetworkFunctions.hpp"
#define BOOST_BIND_GLOBAL_PLACEHOLDERS

NetworkFunctions::NetworkFunctions()
{
    this->mapFunc = {
        {Protocol::CLIENT_JOIN, this->player_joined},
        {Protocol::CLIENT_LEAVE, this->player_left},
        {Protocol::CLIENT_GET_ROOM, this->getRoom},
        {Protocol::CLIENT_JOIN_ROOM, this->joinRoom},
        {Protocol::CLIENT_LEAVE_ROOM, this->leaveRoom},
        {Protocol::CLIENT_CREATE_ROOM, this->createRoom},
        {Protocol::CLIENT_READY, this->clientReady},
        {Protocol::CLIENT_UNREADY, this->clientUnReady},
        {Protocol::CLIENT_KEYBOARD, this->clientKeyboard},
    };
}

NetworkFunctions::~NetworkFunctions()
{
}

const bool NetworkFunctions::executeProtocol(
    ClientMessage &clientMessage, WorldsIndex &worldIndex, NetworkServer &networkServer)
{
    if (this->mapFunc.contains(clientMessage.first.header.id)) {
        this->mapFunc[clientMessage.first.header.id](worldIndex, clientMessage, networkServer);
        return (true);
    }
    return (false);
}

void NetworkFunctions::player_joined(
    WorldsIndex &worldIndex, ClientMessage &clientMessage, NetworkServer &networkServer)
{
    std::cout << "Un joueur " << clientMessage.second << " a rejoint le serveur" << std::endl;
    Message<Protocol> welcomeMsg;
    welcomeMsg.header.id = Protocol::SERVER_OK;
    welcomeMsg << "";
    networkServer.SendToClient(welcomeMsg, clientMessage.second);
    return;
}

void NetworkFunctions::player_left(WorldsIndex &worldIndex, ClientMessage &clientMessage, NetworkServer &networkServer)
{
    const std::size_t clientID = clientMessage.second;
    std::unordered_map<std::size_t, World> &allWorld = worldIndex.getWorld();
    int index = -1;

    for (std::pair<const std::size_t, World> &eachWorld : allWorld) {
        if (eachWorld.second.isClientIDPresentAsBool(clientID)) {
            eachWorld.second.deleteClientInWorld(clientID);
            index = eachWorld.first;
            break;
        }
    }
    if (index != -1) {
        if (allWorld[index].getNbrClientInWorld() == 0) {
            worldIndex.deleteWorld(index);
            std::cout << "je delete le world" << std::endl;
        }
    }

    std::cout << "Un joueur " << clientID << " a quitté le serveur" << std::endl;
    networkServer.on_client_disconnected(clientID);
}

void NetworkFunctions::getRoom(WorldsIndex &worldIndex, ClientMessage &clientMessage, NetworkServer &networkServer)
{
    std::unordered_map<std::size_t, World> &allWorld = worldIndex.getWorld();
    for (std::pair<const std::size_t, World> &eachWorld : allWorld) {
        if (eachWorld.second.isWorldFull() || eachWorld.second.getStateOfTheWorld() == World::STATE::PLAY) {
            continue;
        }
        Message<Protocol> dataRoom;
        dataRoom.header.id = Protocol::SERVER_SEND_ROOM;
        dataRoom << eachWorld.first;
        dataRoom << eachWorld.second.isWorldIsPublic();
        dataRoom << eachWorld.second.getNbrClientInWorld();
        dataRoom << eachWorld.second.getNbrClientMaxInWorld();
        std::string nameRoom = eachWorld.second.getNameOfWorld();
        for (int i = nameRoom.length() - 1; i >= 0; i--)
            dataRoom << nameRoom.at(i);
        dataRoom << nameRoom.length();
        networkServer.SendToClient(dataRoom, clientMessage.second);
    }
}

void NetworkFunctions::joinRoom(WorldsIndex &worldIndex, ClientMessage &clientMessage, NetworkServer &networkServer)
{
    std::unordered_map<std::size_t, World> &allWorld = worldIndex.getWorld();
    Message<Protocol> returnMessage;
    std::size_t idRoomJoin = 0;
    try {
        std::string passWord = "";
        std::size_t passWordSize = 0;

        clientMessage.first >> passWordSize;
        for (std::size_t i = 0; i < passWordSize; ++i) {
            char c;
            clientMessage.first >> c;
            passWord.push_back(c);
        }
        clientMessage.first >> idRoomJoin;
        if (!allWorld.contains(idRoomJoin)) {
            returnMessage.header.id = Protocol::SERVER_KO;
            std::string error = "Error: ID Room Unknown\n";
            for (int i = error.length() - 1; i >= 0; i--)
                returnMessage << error.at(i);
            returnMessage << error.size();
            networkServer.SendToClient(returnMessage, clientMessage.second);
            return;
        }

        try {
            allWorld[idRoomJoin].addClientInWorld(clientMessage.second, passWord);
        }
        catch (const ErrorPasswordIncorrect &e) {
            returnMessage.header.id = Protocol::SERVER_KO;
            std::string error = e.what();
            for (int i = error.length() - 1; i >= 0; i--)
                returnMessage << error.at(i);
            returnMessage << error.size();
            networkServer.SendToClient(returnMessage, clientMessage.second);
            return;
        }
        catch (const ErrorWorldFull &e) {
            returnMessage.header.id = Protocol::SERVER_KO;
            std::string error = e.what();
            for (int i = error.length() - 1; i >= 0; i--)
                returnMessage << error.at(i);
            returnMessage << error.size();
            networkServer.SendToClient(returnMessage, clientMessage.second);
            return;
        }
        catch (const ErrorClientAlreadyPresentInWorld &e) {
            returnMessage.header.id = Protocol::SERVER_KO;
            std::string error = e.what();
            for (int i = error.length() - 1; i >= 0; i--)
                returnMessage << error.at(i);
            returnMessage << error.size();
            networkServer.SendToClient(returnMessage, clientMessage.second);
            return;
        }
    }
    catch (const std::exception &e) {
        returnMessage.header.id = Protocol::SERVER_KO;
        std::string error = e.what();
        for (int i = error.length() - 1; i >= 0; i--)
            returnMessage << error.at(i);
        returnMessage << error.size();
        networkServer.SendToClient(returnMessage, clientMessage.second);
        return;
    }
    returnMessage.header.id = Protocol::SERVER_OK;
    returnMessage << "";
    networkServer.SendToClient(returnMessage, clientMessage.second);
    Message<Protocol> nbrClient;
    nbrClient.header.id = Protocol::SERVER_NBR_CLIENT_IN_ROOM;
    nbrClient << allWorld[idRoomJoin].getNbrClientInWorld();
    sendToAllClientInWorld(allWorld[idRoomJoin], nbrClient, networkServer);
}

void NetworkFunctions::leaveRoom(WorldsIndex &worldIndex, ClientMessage &clientMessage, NetworkServer &networkServer)
{
    std::unordered_map<std::size_t, World> &allWorld = worldIndex.getWorld();
    std::size_t idRoom = 0;
    Message<Protocol> returnMessage;
    try {
        clientMessage.first >> idRoom;
    }
    catch (const std::exception &e) {
        returnMessage.header.id = Protocol::SERVER_KO;
        std::string error = "ID room missing.";
        for (int i = error.length() - 1; i >= 0; i--)
            returnMessage << error.at(i);
        returnMessage << error.size();
        networkServer.SendToClient(returnMessage, clientMessage.second);
        return;
    }

    for (std::pair<const std::size_t, World> &eachWorld : allWorld) {
        std::cout << eachWorld.first << "," << idRoom << std::endl;
        if (eachWorld.first == idRoom) {
            eachWorld.second.deleteClientInWorld(clientMessage.second);
            if (eachWorld.second.getNbrClientInWorld() == 0) {
                worldIndex.deleteWorld(idRoom);
                std::cout << "je le deletee world" << std::endl;
            }
            returnMessage.header.id = Protocol::SERVER_NBR_CLIENT_IN_ROOM;
            returnMessage << eachWorld.second.getNbrClientInWorld();
            sendToAllClientInWorld(eachWorld.second, returnMessage, networkServer);
            return;
        }
    }
}

void NetworkFunctions::createRoom(WorldsIndex &worldIndex, ClientMessage &clientMessage, NetworkServer &networkServer)
{
    Message<Protocol> returnMessage;
    try {
        std::size_t maxPlayer = 0;
        bool isPublic = false;
        std::size_t stringSize = 0;
        std::string passWord = "";
        std::size_t passWordSize = 0;

        clientMessage.first >> maxPlayer;
        clientMessage.first >> isPublic;
        clientMessage.first >> stringSize;
        std::string receivedPassword = "";

        for (size_t i = 0; i < stringSize; ++i) {
            char c;
            clientMessage.first >> c;
            receivedPassword.push_back(c);
        }
        clientMessage.first >> stringSize;
        std::string receivedName = "";
        for (size_t i = 0; i < stringSize; ++i) {
            char c;
            clientMessage.first >> c;
            receivedName.push_back(c);
        }
        std::size_t newID =
            worldIndex.addWorld(false, isPublic, maxPlayer, receivedName, clientMessage.second, receivedPassword);
        returnMessage.header.id = Protocol::SERVER_WELL_CREATED_ROOM;
        returnMessage << newID;
        networkServer.SendToClient(returnMessage, clientMessage.second);
    }
    catch (const std::exception &e) {
        returnMessage.header.id = Protocol::SERVER_KO;
        std::string error = e.what();
        for (int i = error.length() - 1; i >= 0; i--)
            returnMessage << error.at(i);
        returnMessage << error.size();
        networkServer.SendToClient(returnMessage, clientMessage.second);
    }
}

void NetworkFunctions::sendPositions(WorldsIndex &worldIndex, NetworkServer &networkServer)
{
    std::unordered_map<std::size_t, World> &allWorld = worldIndex.getWorld();

    for (std::pair<const std::size_t, World> &eachWorld : allWorld) {
        auto posAllEntity = eachWorld.second.getInformationOfEachEntity();
        auto clientsID = eachWorld.second.getClientsID();
        for (auto posEntity : posAllEntity) {
            Message<Protocol> posMessage;
            posMessage.header.id = Protocol::SERVER_UPDATE_POSITION;
            posMessage << std::get<0>(posEntity);
            for (int i = std::get<1>(posEntity).size() - 1; i >= 0; i--)
                posMessage << std::get<1>(posEntity).at(i);
            posMessage << std::get<1>(posEntity).size();
            posMessage << std::get<2>(posEntity);
            posMessage << std::get<3>(posEntity);
            posMessage << std::get<4>(posEntity);
            posMessage << std::get<5>(posEntity);
            posMessage << std::get<6>(posEntity);
            posMessage << std::get<7>(posEntity);
            posMessage << std::get<8>(posEntity);
            sendToAllClientInWorld(eachWorld.second, posMessage, networkServer);
        }
    }
}

void NetworkFunctions::clientReady(WorldsIndex &worldIndex, ClientMessage &clientMessage, NetworkServer &networkServer)
{
    std::unordered_map<std::size_t, World> &allWorld = worldIndex.getWorld();

    for (std::pair<const std::size_t, World> &eachWorld : allWorld) {
        if (eachWorld.second.isClientIDPresentAsBool(clientMessage.second)) {
            std::unordered_map<std::size_t, ClientInWorld> &clientsID = eachWorld.second.getClientsID();
            clientsID[clientMessage.second].clientIsReady();
            if (eachWorld.second.isAllClientReady()) {
                Message<Protocol> allIsReady;
                allIsReady.header.id = Protocol::SERVER_START_GAME;
                allIsReady << "";
                sendToAllClientInWorld(eachWorld.second, allIsReady, networkServer);
            }
            return;
        }
    }
}

void NetworkFunctions::clientUnReady(
    WorldsIndex &worldIndex, ClientMessage &clientMessage, NetworkServer &networkServer)
{
    std::unordered_map<std::size_t, World> &allWorld = worldIndex.getWorld();

    for (std::pair<const std::size_t, World> &eachWorld : allWorld) {
        if (eachWorld.second.isClientIDPresentAsBool(clientMessage.second)) {
            std::unordered_map<std::size_t, ClientInWorld> &clientsID = eachWorld.second.getClientsID();
            clientsID[clientMessage.second].clientIsntReady();
            return;
        }
    }
}

void NetworkFunctions::clientKeyboard(
    WorldsIndex &worldIndex, ClientMessage &clientMessage, NetworkServer &networkServer)
{
    std::unordered_map<std::size_t, World> &allWorld = worldIndex.getWorld();
    for (std::pair<const std::size_t, World> &eachWorld : allWorld) {
        if (eachWorld.second.isClientIDPresentAsBool(clientMessage.second)) {
            int key = 0;
            bool isPressed = false;
            clientMessage.first >> key;
            clientMessage.first >> isPressed;
            eachWorld.second.changeValueOfKeyPerClientID(
                clientMessage.second, static_cast<VirtualKeyBoard::CONTROL>(key), isPressed);
            return;
        }
    }
}

void NetworkFunctions::sendToAllClientInWorld(World &world, Message<Protocol> message, NetworkServer &networkServer)
{
    std::unordered_map<std::size_t, ClientInWorld> &clientsID = world.getClientsID();

    for (std::pair<std::size_t, ClientInWorld> clientID : clientsID) {
        networkServer.SendToClient(message, clientID.first);
    }
}
