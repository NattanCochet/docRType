/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Network
*/

#pragma once
#ifndef NETWORK_HPP_
#define NETWORK_HPP_
    // #include "../ECS/Client.hpp"
    #include "../Logic/include/ECS/World.hpp"
    #include "Message.hpp"
    #include "client.hpp"

class Network {
    public:
        Network();
        Network(World *world);
        ~Network();
        void print_hex(const std::vector<unsigned char>& buffer);
        std::string buffer_to_string(const std::vector<unsigned char>& buffer);
        void print_message(const std::vector<unsigned char>& buffer);
        void killEntity(Message<Protocol> msg);
        void createEntity(Message<Protocol> msg);
        void receive_messages(NetworkClient& client, World& world, std::atomic<bool>& running);
        void send_join_message(NetworkClient& client);
        void send_leave_message(NetworkClient& client);
        void sendGetRoomMessage(NetworkClient& client);
        void sendKillEntity(NetworkClient& client);
        void sendCreateRoom(NetworkClient& client, std::string name, std::string password, bool isPublic, size_t maxPlayer);
        void sendJoinRoom(NetworkClient& client);
        void interactive_send(NetworkClient& client, std::atomic<bool>& running);
        void receive_string(Message<Protocol> msg);

    protected:
    private:
        World *_world;
};

#endif /* !NETWORK_HPP_ */
