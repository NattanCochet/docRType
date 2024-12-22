/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** WorldsIndex
*/

#include "../include/WorldsIndex.hpp"

WorldsIndex::WorldsIndex() : _nbrWorlds(0), _wordMap(), _nextIDWorld(0)
{
}

WorldsIndex::~WorldsIndex()
{
}

World &WorldsIndex::getWorldByID(std::size_t worldID)
{
    if (!_wordMap.contains(worldID)) {
        throw ErrorKeyNotFound(std::to_string(worldID), "WorldsIndex::getWorldByID");
    }
    return (_wordMap[worldID]);
}

std::unordered_map<std::size_t, World> &WorldsIndex::getWorld()
{
    return (_wordMap);
}

std::size_t WorldsIndex::addWorld(
    bool isClient, bool isPublic, int nbrPlayerMax, std::string nameRoom,
    std::size_t clientID, std::string password
)
{
    _wordMap[_nextIDWorld] = World(isClient, isPublic, nbrPlayerMax, nameRoom, clientID, password);
    _nbrWorlds += 1;
    _nextIDWorld += 1;
    return (_nbrWorlds);
}

World WorldsIndex::deleteWorld(std::size_t index)
{
    World deletedWorld = _wordMap[index];
    _wordMap.erase(index);
    _nbrWorlds -= 1;
    return (deletedWorld);
}

World WorldsIndex::deleteWorld(std::unordered_map<std::size_t, World>::iterator it)
{
    std::pair<std::size_t, World> deletedWorld = *it;
    _wordMap.erase(it);
    _nbrWorlds -= 1;
    return (deletedWorld.second);
}

std::size_t WorldsIndex::getNbrWorlds() const noexcept
{
    return (_nbrWorlds);
}
