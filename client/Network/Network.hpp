/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Network
*/

#pragma once
#ifndef NETWORK_HPP_
#define NETWORK_HPP_
#include "../ECS/Client.hpp"
#include "../ECS/World.hpp"

class Network
{
  public:
    Network();
    Network(World *world);
    ~Network();
    void print_hex(const std::vector<unsigned char> &buffer);
    std::string buffer_to_string(const std::vector<unsigned char> &buffer);
    void print_message(const std::vector<unsigned char> &buffer);
    static void killEntity(World *world, Message<Protocol> msg);
    static void gameEnd(World *world, Message<Protocol> msg);
    static void createEntity(World *world, Message<Protocol> msg);
    static void getRoomsServer(World *world, Message<Protocol> msg);
    static void roomCreated(World *world, Message<Protocol> msg);
    static void clientsInRoom(World *world, Message<Protocol> msg);
    static void startGame(World *world, Message<Protocol> msg);
    static void okAnswer(World *world, Message<Protocol> msg);
    static void koAnswer(World *world, Message<Protocol> msg);
    void receive_messages(NetworkClient &client, World &world, std::atomic<bool> &running);
    void send_join_message(NetworkClient &client);
    void send_leave_message(NetworkClient &client);
    void sendKeyboard(NetworkClient &client, bool isPressed, int key);
    void sendGetRoomMessage(NetworkClient &client);
    void sendJoinRoom(NetworkClient &client, size_t roomId, std::string password);
    void sendLeaveRoom(NetworkClient &client, size_t roomId);
    void sendCreateRoom(NetworkClient &client, std::string name, std::string password, bool isPublic, size_t maxPlayer);
    void sendReady(NetworkClient &client);
    void sendUnReady(NetworkClient &client);
    void interactive_send(NetworkClient &client, std::atomic<bool> &running);
    void receive_string(Message<Protocol> msg);

  protected:
  private:
    World *_world;
    std::map<Protocol, std::function<void(World *world, Message<Protocol>)>> _mapFunc;
};

#endif /* !NETWORK_HPP_ */
