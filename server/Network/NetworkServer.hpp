#define BOOST_BIND_GLOBAL_PLACEHOLDERS

#include <array>
#include <boost/array.hpp>
#include <asio.hpp>
#include <boost/bimap.hpp>
#include <boost/thread.hpp>
#include <string>
#include "Message.hpp"
#include "Locked_queue.hpp"

#pragma once

#define MAX_CLIENTS 16

using asio::ip::udp;

typedef boost::bimap<std::size_t, udp::endpoint> ClientList;
typedef ClientList::value_type Client;
typedef std::pair<Message<Protocol>, std::size_t> ClientMessage;

class NetworkServer {
    private:
        asio::io_service io_service;
        udp::socket socket;
        udp::endpoint server_endpoint;
        udp::endpoint remote_endpoint;
        std::array<char, 1024> recv_buffer;
        boost::thread service_thread;
        std::size_t nextClientID;

        void handle_send(std::string, const boost::system::error_code &, std::size_t){};
        void run_service();
        std::size_t get_client_id(udp::endpoint endpoint);

        void send(std::string pmessage, udp::endpoint target_endpoint);
        void send(const Message<Protocol> &message, udp::endpoint target_endpoint);


        LockedQueue<ClientMessage> incomingMessages;

        NetworkServer(NetworkServer &);

    public:
        void start_receive();
        void handle_receive(const boost::system::error_code &error, std::size_t bytes_transferred);
        void on_client_disconnected(std::size_t id);

        NetworkServer(unsigned short local_port);
        ~NetworkServer();
        bool HasMessages();
        ClientMessage PopMessage();
        void SendToClient(std::string message, std::size_t clientID);
        void SendToAll(std::string message);
        void SendToAllExcept(std::string message, std::size_t clientID);
        void SendToClient(const Message<Protocol> &message, std::size_t clientID);
        void SendToAll(const Message<Protocol> &message);
        void SendToAllExcept(const Message<Protocol> &message, std::size_t clientID);
        std::vector<std::function<void(std::size_t)>> clientDisconnectedHandlers;
        ClientList clients;
};