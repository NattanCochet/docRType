#pragma once

#include <array>
#include <boost/array.hpp>
#include <asio.hpp>
#include <boost/thread.hpp>
#include <memory>
#include "Message.hpp"
#include "Locked_queue.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using asio::ip::udp;

class World;

enum class SceneScreen : uint32_t;

class NetworkClient {
  public:
    NetworkClient(std::string host, std::string server_port, unsigned short local_port = 0);
    ~NetworkClient();
    void send(const std::string &message);
    void send(const Message<Protocol> &message);
    bool HasMessages();
    Message<Protocol> PopMessage();
    bool is_connected() const;
    void set_launch_game(bool launch);
    bool get_launch_game() const;
    void set_players_ready(bool ready);
    bool get_players_ready() const;
    void set_nb_players(int nb_players);
    int get_nb_players() const;

  private:
    asio::io_service io_service;
    udp::socket socket;
    udp::endpoint server_endpoint;
    udp::endpoint remote_endpoint;
    std::array<char, 1024> recv_buffer;
    boost::thread service_thread;
    bool _players_ready;
    bool _launch_game;
    int _nb_players;
    float _sound_volume;

    LockedQueue<Message<Protocol>> incomingMessages;

    void start_receive();
    void handle_receive(const std::error_code &error, std::size_t bytes_transferred);
    void run_service();

    NetworkClient(NetworkClient &);
};

void new_entity(World &world, NetworkClient &client, Message<Protocol> msg, SceneScreen &current_screen);
