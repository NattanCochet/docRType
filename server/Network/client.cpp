#include "client.hpp"
#include "../Logic/include/ECS/Entity.hpp"
#include <boost/iostreams/stream.hpp>
#include <boost/serialization/vector.hpp>
#include <sstream>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include "../Logic/include/ECS/World.hpp"

NetworkClient::NetworkClient(std::string host, std::string server_port, unsigned short local_port)
    : socket(io_service, udp::endpoint(udp::v4(), local_port)), service_thread(&NetworkClient::run_service, this)
{
    this->_nb_players = 0;
    this->_players_ready = false;
    this->_launch_game = false;
    this->_sound_volume = 50.0f;
    udp::resolver resolver(io_service);
    udp::resolver::query query(udp::v4(), host, server_port);
    server_endpoint = *resolver.resolve(query);
    NetworkClient::send("");
}

NetworkClient::~NetworkClient()
{
    io_service.stop();
    service_thread.join();
}

bool NetworkClient::is_connected() const {
    return socket.is_open();
}


void NetworkClient::start_receive()
{
    socket.async_receive_from(
        asio::buffer(recv_buffer), remote_endpoint, [this](std::error_code ec, std::size_t bytes_recvd) {
            this->handle_receive(ec, bytes_recvd);
        });
}

void NetworkClient::handle_receive(const std::error_code &error, std::size_t bytes_transferred)
{
    if (!error) {
        try {
            Message<Protocol> gameMsg;

            std::string recv_str(recv_buffer.data(), recv_buffer.data() + bytes_transferred);

            boost::iostreams::basic_array_source<char> device(recv_str.data(), recv_str.size());
            boost::iostreams::stream<boost::iostreams::basic_array_source<char>> s(device);
            boost::archive::binary_iarchive ia(s);
            ia >> gameMsg;

            if (gameMsg.size() != 0)
                incomingMessages.push(gameMsg);
        } catch (...) {
        }
    } else {
    }

    start_receive();
}

void NetworkClient::send(const std::string &message)
{
    socket.send_to(asio::buffer(message), server_endpoint);
}

void NetworkClient::send(const Message<Protocol> &message)
{
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string>> s(inserter);
    boost::archive::binary_oarchive oa(s);

    oa << message;
    s.flush();
    send(serial_str);
}

bool NetworkClient::HasMessages()
{
    return !incomingMessages.empty();
}

Message<Protocol> NetworkClient::PopMessage()
{
    if (incomingMessages.empty())
        throw std::logic_error("No messages to pop");
    return incomingMessages.pop();
}

void NetworkClient::run_service()
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

void NetworkClient::set_launch_game(bool launch)
{
    this->_launch_game = launch;
}

bool NetworkClient::get_launch_game() const
{
    return (this->_launch_game);
}

void NetworkClient::set_players_ready(bool ready)
{
    this->_players_ready = ready;
}

bool NetworkClient::get_players_ready() const
{
    return (this->_players_ready);
}

void NetworkClient::set_nb_players(int nb_players)
{
    this->_nb_players = nb_players;
}

int NetworkClient::get_nb_players() const
{
    return (_nb_players);
}

void new_player(World &world, size_t srv_entity_id, sf::Vector2f pos, NetworkClient &client)
{
    // size_t new_entity_id = 0;
    // Position position(pos);
    // (void)client;

    // new_entity_id = world.create_player(position.pos, sf::Vector2i{0, 0}, 0.04f);
    // world.getRegistry().add_component<Entity>(
    //     world.getRegistry().entity_from_index(new_entity_id), Entity{srv_entity_id});
}

static std::map<GameObject, std::function<void(World &, size_t, sf::Vector2f, NetworkClient &)>> newEntity = {
    {GameObject::PLAYER, new_player},
};

void new_entity(World &world, NetworkClient &client, Message<Protocol> msg, SceneScreen &current_screen)
{
    (void)client;
    (void)current_screen;
    sf::Vector2f pos;
    size_t srv_entity_id;
    GameObject object;

    std::cout << "Bonchoir" << std::endl;

    // msg >> pos >> srv_entity_id >> object;
    // newEntity[object](world, srv_entity_id, pos, client);
}

void dead_entity(World &world, NetworkClient &client, Message<Protocol> msg, SceneScreen &current_screen)
{
    // (void)client;
    // (void)current_screen;
    // Entity id_entity;
    // auto &entityIdCompo = world.getRegistry().get_components<Entity>();
    // size_t index = 0;

    // msg >> id_entity;
    // for (auto &entityId : entityIdCompo) {
    //     if (entityId && entityId.has_value()) {
    //         if (entityId->id == id_entity.id) {
    //             world.getRegistry().kill_entity(world.getRegistry().entity_from_index(index));
    //             break;
    //         }
    //     }
    //     index++;
    // }
}

void game_end(sf::RenderWindow &window)
{
    window.close();
}

void movement(World &world, NetworkClient &client, Message<Protocol> msg, SceneScreen &current_screen)
{
    // (void)client;
    // (void)current_screen;
    // registry &r = world.getRegistry();
    // auto &velocityCompo = r.get_components<Velocity>();
    // auto &entityId = r.get_components<Entity>();
    // Entity moved_id;
    // sf::Vector2i velocity = {0, 0};
    // size_t index = 0;

    // msg >> velocity >> moved_id;
    // for (auto &idCompo : entityId) {
    //     if (idCompo && idCompo.has_value()) {
    //         if (idCompo->id == moved_id.id) {
    //             velocityCompo[index]->speed.x = velocity.x;
    //             velocityCompo[index]->speed.y = velocity.y;
    //             break;
    //         }
    //     }
    //     index++;
    // }
}

void ok_packet(World &world, NetworkClient &client, Message<Protocol> msg, SceneScreen &current_screen)
{
    (void)world;
    (void)client;
    (void)msg;
    (void)current_screen;
}

void players_numbers(World &world, NetworkClient &client, Message<Protocol> msg, SceneScreen &current_screen)
{
    (void)world;
    (void)current_screen;
    std::size_t nb_players;

    msg >> nb_players;
    client.set_nb_players((int)nb_players);
}

void players_ready(World &world, NetworkClient &client, Message<Protocol> msg, SceneScreen &current_screen)
{
    (void)world;
    (void)current_screen;
    bool ready;

    msg >> ready;
    client.set_players_ready(ready);
}
