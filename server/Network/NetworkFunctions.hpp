/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** NetworkFunctions
*/

#ifndef NETWORKFUNCTIONS_HPP_
#define NETWORKFUNCTIONS_HPP_
#define BOOST_BIND_GLOBAL_PLACEHOLDERS
#include <map>
#include <functional>
#include "Message.hpp"
#include "NetworkServer.hpp"
#include "../Logic/include/WorldsIndex.hpp"

class NetworkFunctions {
    public:
        NetworkFunctions();
        ~NetworkFunctions();

        const bool executeProtocol(ClientMessage &clientMessage, WorldsIndex &worldIndex, NetworkServer &networkServer);
        void sendPositions(WorldsIndex &worldIndex, NetworkServer &networkServer);

    private:
        static void getRoom(WorldsIndex &worldIndex, ClientMessage &clientMessage, NetworkServer &networkServer);
        static void joinRoom(WorldsIndex &worldIndex, ClientMessage &clientMessage, NetworkServer &networkServer);
        static void leaveRoom(WorldsIndex &worldIndex, ClientMessage &clientMessage, NetworkServer &networkServer);
        static void createRoom(WorldsIndex &worldIndex, ClientMessage &clientMessage, NetworkServer &networkServer);
        static void player_left(WorldsIndex &worldIndex, ClientMessage &clientMessage, NetworkServer &networkServer);
        static void clientReady(WorldsIndex &worldIndex, ClientMessage &clientMessage, NetworkServer &networkServer);
        static void clientUnReady(WorldsIndex &worldIndex, ClientMessage &clientMessage, NetworkServer &networkServer);
        static void player_joined(WorldsIndex &worldIndex, ClientMessage &clientMessage, NetworkServer &networkServer);
        static void clientKeyboard(WorldsIndex &worldIndex, ClientMessage &clientMessage, NetworkServer &networkServer);

        static void sendToAllClientInWorld(World &world, Message<Protocol> message, NetworkServer &networkServer);

    private:
        std::map<Protocol, std::function<void(WorldsIndex &, ClientMessage &, NetworkServer &)>> mapFunc;
};

#endif /* !NETWORKFUNCTIONS_HPP_ */
