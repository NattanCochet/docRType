#include <boost/serialization/serialization.hpp>
#include <boost/serialization/vector.hpp>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#pragma once

enum class Protocol : uint32_t {
    CLIENT_JOIN,     // Client requests to join the game
    CLIENT_LEAVE,    // Client requests to leave the game
    CLIENT_KEYBOARD, // Client sends movement data
    CLIENT_GET_ROOM,
    CLIENT_JOIN_ROOM,
    CLIENT_LEAVE_ROOM,
    CLIENT_CREATE_ROOM,
    CLIENT_READY,
    CLIENT_UNREADY,

    SERVER_ENTITY_DEAD, // Server notifies of an entity's destruction
    SERVER_GAME_END,    // Server notifies the end of the game
    SERVER_OK,          // Server acknowledges a client request
    SERVER_KO,
    SERVER_START_GAME,      // Server notifies the start of the game
    SERVER_UPDATE_POSITION, // Server updates player or game statistics
    SERVER_SEND_ROOMS,
    SERVER_NBR_CLIENT_IN_ROOM,
    SERVER_WELL_CREATED_ROOM,
};

enum class WaveStatus : uint32_t { START, BOSS, END };

enum class GameObject : uint32_t {
    LASER,
    ENEMY,
    PLAYER,
    SHIP_1,
    SHIP_2,
    SHIP_3,
    BOSS_1,
    BONUS_ATTACK,
    BONUS_HEAL,
    BONUS_SPEED,
};

enum class GameStat : uint32_t { HEALTH, DAMAGE, SPEED };

template <typename T> struct MessageHeader {
    T id{};
    std::size_t size = 0;
    friend class boost::serialization::access;
    template <class Archive> void serialize(Archive &ar, const unsigned int version)
    {
        ar & id;
        ar & size;
        (void)version;
    }
};

template <typename T> struct Message {
    MessageHeader<T> header;

    std::vector<uint8_t> body;

    std::size_t size() const
    {
        return body.size();
    }

    template <typename ContentType> friend Message<T> &operator<<(Message<T> &m, const ContentType &content)
    {
        static_assert(std::is_standard_layout<ContentType>::value, "Not standard layout : Can't push into vector");

        std::size_t currentSize = m.body.size();
        m.body.resize(currentSize + sizeof(ContentType));
        std::memcpy(m.body.data() + currentSize, &content, sizeof(ContentType));
        m.header.size = m.size();
        return m;
    }

    template <typename ContentType> friend Message<T> &operator>>(Message<T> &m, ContentType &content)
    {
        static_assert(std::is_standard_layout<ContentType>::value, "Not standard layout : Can't retrieve from vector");

        std::size_t finalSize = m.body.size() - sizeof(ContentType);
        m.body.resize(finalSize);
        std::memcpy(&content, m.body.data() + finalSize, sizeof(ContentType));
        m.header.size = m.size();
        return m;
    }

    friend class boost::serialization::access;

    template <class Archive> void serialize(Archive &ar, const unsigned int version)
    {
        ar & header;
        ar & body;
        (void)version;
    }
};
