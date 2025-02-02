/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** NetworkServer
*/

#define _WIN32_WINNT 0x0601
#define BOOST_BIND_GLOBAL_PLACEHOLDERS

#include <boost/bind.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/serialization/vector.hpp>
#include <sstream>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include "NetworkServer.hpp"
#include "Message.hpp"

NetworkServer::NetworkServer(unsigned short local_port)
    : socket(io_service, udp::endpoint(udp::v4(), local_port)),
      service_thread(std::bind(&NetworkServer::run_service, this)), nextClientID(0L)
{
}

NetworkServer::~NetworkServer()
{
    io_service.stop();
    service_thread.join();
}

void NetworkServer::start_receive()
{
    if (clients.size() < MAX_CLIENTS) {
        socket.async_receive_from(asio::buffer(recv_buffer), remote_endpoint,
            boost::bind(&NetworkServer::handle_receive, this, asio::placeholders::error,
                asio::placeholders::bytes_transferred));
    }
}

void NetworkServer::handle_receive(const boost::system::error_code &error, std::size_t bytes_transferred)
{
    if (!error) {
        try {
            Message<Protocol> gameMsg;

            std::string recv_str(recv_buffer.data(), recv_buffer.data() + bytes_transferred);

            boost::iostreams::basic_array_source<char> device(recv_str.data(), recv_str.size());
            boost::iostreams::stream<boost::iostreams::basic_array_source<char>> s(device);
            boost::archive::binary_iarchive ia(s);
            ia >> gameMsg;

            auto message = ClientMessage(gameMsg, get_client_id(remote_endpoint));
            if (incomingMessages.size() >= incomingMessages.max_size && gameMsg.header.id == Protocol::SERVER_UPDATE_POSITION) {
                std::cerr << "Message ignored due to queue size limit and SERVER_UPDATE_POSITION type." << std::endl;
            } else {
                incomingMessages.push(message);
            }
        } catch (const std::exception &ex) {
            std::cerr << "Exception during message handling: " << ex.what() << std::endl;
        } catch (...) {
            std::cerr << "Unknown error during message handling." << std::endl;
        }
    } else {
        std::cerr << "Error during receive: " << error.message() << std::endl;
    }

    start_receive();
}

void NetworkServer::send(std::string message, udp::endpoint target_endpoint)
{
    socket.send_to(asio::buffer(message), target_endpoint);
}

void NetworkServer::send(const Message<Protocol> &message, udp::endpoint target_endpoint)
{
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string>> s(inserter);
    boost::archive::binary_oarchive oa(s);

    oa << message;

    s.flush();

    send(serial_str, target_endpoint);
}

void NetworkServer::run_service()
{
    start_receive();
    while (!io_service.stopped()) {
        try {
            io_service.run();
        } catch (const std::exception &e) {
        } catch (...) {
        }
    }
}

std::size_t NetworkServer::get_client_id(udp::endpoint endpoint)
{
    auto cit = clients.right.find(endpoint);
    if (cit != clients.right.end())
        return (*cit).second;

    nextClientID++;
    clients.insert(Client(nextClientID, endpoint));
    return nextClientID;
}

void NetworkServer::SendToClient(std::string message, std::size_t clientID)
{
    try {
        send(message, clients.left.at(clientID));
    } catch (std::out_of_range const &) {
    }
}

void NetworkServer::SendToClient(const Message<Protocol> &message, std::size_t clientID)
{
    try {
        send(message, clients.left.at(clientID));
    } catch (std::out_of_range const &) {
    }
}

void NetworkServer::SendToAll(std::string message)
{
    for (auto client : clients)
        send(message, client.right);
}

void NetworkServer::SendToAll(const Message<Protocol> &message)
{
    for (auto client : clients)
        send(message, client.right);
}

void NetworkServer::SendToAllExcept(std::string message, std::size_t clientID)
{
    for (auto client : clients) {
        if (client.left == clientID)
            continue;
        send(message, client.right);
    }
}

void NetworkServer::SendToAllExcept(const Message<Protocol> &message, std::size_t clientID)
{
    for (auto client : clients) {
        if (client.left == clientID)
            continue;
        send(message, client.right);
    }
}

void NetworkServer::on_client_disconnected(std::size_t id)
{
    for (auto &handler : clientDisconnectedHandlers)
        if (handler)
            handler(id);
}

ClientMessage NetworkServer::PopMessage()
{
    return incomingMessages.pop();
}

bool NetworkServer::HasMessages()
{
    return !incomingMessages.empty();
}
