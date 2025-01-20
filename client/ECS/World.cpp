/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** World
*/

#include "World.hpp"

World::World(bool isClient, sf::RenderWindow *window) :
    _client("127.0.0.1", "4242", 0) // 0 pour que le système choisisse un port local automatiquement
{
    _isClient = isClient;
    _r = Registry();
    _rOnline = Registry();
    this->_r.register_components<Position>();
    this->_r.register_components<Drawable>();
    this->_r.register_components<Clickable>();
    this->_r.register_components<Controllable>();
    this->_rOnline.register_components<Position>();
    this->_rOnline.register_components<Drawable>();
    this->_rOnline.register_components<Clickable>();
    this->_rOnline.register_components<Controllable>();
    _assets = Assets();
    _window = window;
    _state = MENU;
    _roomName = "";
    _roomPassword = "";
    _roomIndex = 0;
    _nbInRoom = {0, 0};
    _buttonsTextInputs["roomPasswordUser"] = 0;
    _controlsMap[CONTROL::SHOOT] = sf::Keyboard::Space;
    _controlsMap[CONTROL::FORCE] = sf::Keyboard::Enter;
    _controlsMap[CONTROL::UP] = sf::Keyboard::Up;
    _controlsMap[CONTROL::DOWN] = sf::Keyboard::Down;
    _controlsMap[CONTROL::LEFT] = sf::Keyboard::Left;
    _controlsMap[CONTROL::RIGHT] = sf::Keyboard::Right;
    _textWritting = -1;
    _controlWritting = -1;
    _nbEntities = 0;
    _nbEntitiesOnline = 0;
    _keysIndex["roomNameCreate"] = -1;
    _keysIndex["roomPasswordCreate"] = -1;
    _keysIndex["roomIsPublicCreate"] = -1;
    _keysIndex["roomFillAI"] = -1;
    _keysIndex["roomMaxNbrPlayerCreate"] = -1;
    _keysIndex["roomErrorCreate"] = -1;
    _keysIndex["roomPassword"] = -1;
    _keysIndex["roomErrorText"] = -1;
    _keysIndex["LobbyPlayerCountText"] = -1;
    _keysIndex["scoreGameText"] = -1;
    _keysIndex["levelGameText"] = -1;
    _pageNumber = {0, 0};
    _indexLocalPlayer = -1;
    _serverConnection = false;
}

sf::Sprite *World::getSprite(std::string filepath)
{
    return (_assets.getSprite(filepath));
}

sf::Text *World::getText(std::string filepath)
{
    return (_assets.getText(filepath));
}

sf::RectangleShape *World::getRectangle(std::string name)
{
    return (_assets.getRectangle(name));
}

sf::RenderWindow *World::getWindow()
{
    return (_window);
}

Registry &World::getRegistry()
{
    return (this->_r);
}

Registry &World::getOnlineRegistry()
{
    return (this->_rOnline);
}

sf::Clock &World::getClock()
{
    return (this->_clock);
}

void World::addKeyAction(PRESS press, sf::Keyboard::Key key)
{
    _keyActions.push_back({press, key});
}

void World::clearKeyAction()
{
    _keyActions.clear();
}

std::vector<std::pair<World::PRESS, sf::Keyboard::Key>> World::getKeyActions()
{
    return (_keyActions);
}

void World::addMouseAction(PRESS press, sf::Vector2i pos)
{
    _mouseActions.push_back({press, pos});
}

void World::clearMouseAction()
{
    _mouseActions.clear();
}

std::vector<std::pair<World::PRESS, sf::Vector2i>> &World::getMouseAction()
{
    return (_mouseActions);
}

void World::setState(GAME_STATE state)
{
    _state = state;
}

World::GAME_STATE World::getState(void)
{
    return (_state);
}

void World::setPreviousState(GAME_STATE state)
{
    _prevState = state;
}

World::GAME_STATE World::getPreviousState(void)
{
    return (_prevState);
}

void World::setRoomName(std::string roomName)
{
    _roomName = roomName;
}

std::string World::getRoomName(void)
{
    return (_roomName);
}

void World::setRoomPassword(std::string roomPassword)
{
    _roomPassword = roomPassword;
}

std::string World::getRoomPassword(void)
{
    return (_roomPassword);
}

void World::setInputButtonIndex(const std::string &name, std::size_t index)
{
    _buttonsTextInputs[name] = index;
}

std::size_t World::getInputButtonIndex(const std::string &name)
{
    return _buttonsTextInputs[name];
}

void World::setTextWritting(int textWritting)
{
    _textWritting = textWritting;
}

int World::getTextWritting(void)
{
    return (_textWritting);
}

void World::setControlWritting(int controlWritting)
{
    _controlWritting = controlWritting;
}

int World::getControlWritting(void)
{
    return _controlWritting;
}

int World::getNbEntities()
{
    return (_nbEntities);
}

void World::setNbEntities(int nbEntities)
{
    _nbEntities = nbEntities;
}

int World::getNbEntitiesOnline()
{
    return (_nbEntitiesOnline);
}

void World::setNbEntitiesOnline(int nbEntities)
{
    _nbEntitiesOnline = nbEntities;
}

NetworkClient &World::getClient()
{
    return (_client);
}

std::map<std::string, int> &World::getKeysIndex()
{
    return _keysIndex;
}

void World::resetKeysIndex()
{
    for (auto it = _keysIndex.begin(); it != _keysIndex.end(); it++) {
        it->second = -1;
    }
}

void World::addRoomsList(std::tuple<std::size_t, bool, std::size_t, std::size_t, std::string> newRoom)
{
    _roomsList.push_back(newRoom);
}

void World::clearRoomsList()
{
    _roomName = "";
    _roomPassword = "";
    _roomIndex = 0;
    _nbInRoom = {0, 0};
    _pageNumber = {_pageNumber.first, 0};
    _roomsList.clear();
}

std::vector<std::tuple<std::size_t, bool, std::size_t, std::size_t, std::string>> World::getRoomsList()
{
    return (_roomsList);
}

void World::setPageNumber(std::pair<int, std::size_t> newPageNumber)
{
    _pageNumber = newPageNumber;
}

std::pair<int, std::size_t> World::getPageNumber()
{
    return (_pageNumber);
}

void World::setRoomIndex(std::size_t newIndex)
{
    _roomIndex = newIndex;
}

std::size_t World::getRoomIndex()
{
    return (_roomIndex);
}

void World::setNbInRoom(std::pair<std::size_t, std::size_t> newNb)
{
    _nbInRoom = newNb;
}

std::pair<std::size_t, std::size_t> World::getNbInRoom()
{
    return (_nbInRoom);
}

void World::setLocalPlayer(int newIndex)
{
    _indexLocalPlayer = newIndex;
}

int World::getLocalPlayer()
{
    return (_indexLocalPlayer);
}

bool World::getServerConnection()
{
    return (_serverConnection);
}

void World::setServerConnection(bool newServerConnection)
{
    _serverConnection = newServerConnection;
}
