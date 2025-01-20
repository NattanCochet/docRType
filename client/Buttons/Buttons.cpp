/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Buttons
*/

#include "Buttons.hpp"

Buttons::Buttons()
{
}

Buttons::Buttons(World *world, Network *network)
{
    _world = world;
    _network = network;
}

Buttons::~Buttons()
{
}

void Buttons::quitButton(std::size_t index)
{
    _world->getWindow()->close();
}

void Buttons::playButton(std::size_t index)
{
    if (_world->getServerConnection() == false)
        return;
    _world->setState(World::NETWORK_MENU);
}

void Buttons::controlsButton(std::size_t index)
{
    _world->setState(World::CONTROLS_MENU);
}

void Buttons::backButton(std::size_t index)
{
    Registry &r = _world->getRegistry();
    ComponentArray<Clickable> &clickables = r.get_components<Clickable>();
    void *buttonT = clickables[index]->getInfos();
    if (buttonT && clickables[index]->getKindButton() == Clickable::BACKBUTTON) {
        Buttons::BackButton_t *button = static_cast<Buttons::BackButton_t *>(buttonT);
        if (_world->getState() == World::LOBBY_MENU) {
            _network->sendLeaveRoom(_world->getClient(), _world->getRoomIndex());
            _world->setRoomIndex(0);
            _world->setRoomName("");
            _world->setRoomPassword("");
            _world->setNbInRoom({0, 0});
        }
        _world->setState(button->_previousState);
    }
}

void Buttons::createMenuButton(std::size_t index)
{
    _world->setState(World::CREATE_ROOM);
}

void Buttons::reloadButton(std::size_t index)
{
    _network->sendGetRoomMessage(_world->getClient());
}

void Buttons::createRoomButton(std::size_t index)
{
    Registry &r = _world->getRegistry();
    std::map<std::string, int> &keys = _world->getKeysIndex();
    ComponentArray<Drawable> &drawables = r.get_components<Drawable>();
    ComponentArray<Clickable> &clickables = r.get_components<Clickable>();
    std::string roomName = drawables[keys["roomNameCreate"]]->getMessage();
    std::string roomPassword = drawables[keys["roomPasswordCreate"]]->getMessage();
    std::string roomMaxStr = drawables[keys["roomMaxNbrPlayerCreate"]]->getMessage();
    bool isPublic = true;
    void *buttonT = clickables[keys["roomIsPublicCreate"]]->getInfos();
    if (roomName.empty()) {
        drawables[keys["roomErrorCreate"]]->setMessage("Room must have a name");
        return;
    }
    if (buttonT && clickables[keys["roomIsPublicCreate"]]->getKindButton() == Clickable::SPLITBUTTON) {
        Buttons::SplitButton_t *button = static_cast<Buttons::SplitButton_t *>(buttonT);
        isPublic = button->_active;
    } else {
        drawables[keys["roomErrorCreate"]]->setMessage("Public button error");
        return;
    }
    if (roomPassword.empty() && !isPublic) {
        drawables[keys["roomErrorCreate"]]->setMessage("Private room must have a password");
        return;
    }
    if (roomMaxStr.empty()) {
        drawables[keys["roomErrorCreate"]]->setMessage("Must set the maximum number of players");
        return;
    }
    std::size_t maxPlayers = 0;
    std::stringstream stream(roomMaxStr);
    stream >> maxPlayers;
    if (maxPlayers < 1) {
        drawables[keys["roomErrorCreate"]]->setMessage("Maximum number of players must be at least 1");
        return;
    }
    _network->sendCreateRoom(_world->getClient(), roomName, roomPassword, isPublic, maxPlayers);
    _world->setRoomName(roomName);
    _world->setNbInRoom({1, maxPlayers});
}

void Buttons::joinButton(std::size_t index)
{
    std::size_t indexRoom = _world->getRoomIndex();
    if (_world->getRoomName() == "")
        return;
    Registry &r = _world->getRegistry();
    ComponentArray<Drawable> &drawables = r.get_components<Drawable>();
    std::string password = drawables[_world->getKeysIndex().find("roomPassword")->second]->getMessage();

    _network->sendJoinRoom(_world->getClient(), indexRoom, password);
}

void Buttons::startButton(std::size_t index)
{
    ComponentArray<Drawable> &drawables = _world->getRegistry().get_components<Drawable>();
    ComponentArray<Clickable> &clickables = _world->getRegistry().get_components<Clickable>();
    drawables[index]->setColor({240, 0, 0});
    drawables[index]->setMessage("Cancel");
    clickables[index]->setAction([this](std::size_t idx) { unReadyButton(idx); });
    _network->sendReady(_world->getClient());
}

void Buttons::unReadyButton(std::size_t index)
{
    ComponentArray<Drawable> &drawables = _world->getRegistry().get_components<Drawable>();
    ComponentArray<Clickable> &clickables = _world->getRegistry().get_components<Clickable>();
    drawables[index]->setColor({0, 250, 0});
    drawables[index]->setMessage("Ready");
    clickables[index]->setAction([this](std::size_t idx) { startButton(idx); });
    _network->sendUnReady(_world->getClient());
}

void Buttons::selectButton(std::size_t index)
{
    ComponentArray<Drawable> &drawables = _world->getOnlineRegistry().get_components<Drawable>();
    for (std::optional<Drawable> &drawable : drawables) {
        if (drawable && drawable.has_value() && drawable->getMessage() == _world->getRoomName()) {
            drawable->setColor({102, 153, 153});
        }
    }
    drawables[index]->setColor({51, 204, 51});
    int onlineEntities = _world->getNbEntitiesOnline();
    std::pair<int, std::size_t> nbPages = _world->getPageNumber();
    std::vector<std::tuple<std::size_t, bool, std::size_t, std::size_t, std::string>> roomList = _world->getRoomsList();
    std::size_t indexRoom = std::get<0>(roomList.at(index - nbPages.first + nbPages.second));
    std::size_t nbMaxInRoom = std::get<2>(roomList.at(index - nbPages.first + nbPages.second));
    _world->setRoomIndex(indexRoom);
    _world->setRoomName(drawables[index]->getMessage());
    _world->setNbInRoom({0, nbMaxInRoom});
}

void Buttons::selectRoomButton(std::size_t index)
{
    ComponentArray<Drawable> &drawables = _world->getOnlineRegistry().get_components<Drawable>();
    ComponentArray<Drawable> &drawablesOffline = _world->getRegistry().get_components<Drawable>();
    ComponentArray<Position> &positionsOffline = _world->getRegistry().get_components<Position>();
    ComponentArray<Clickable> &clickables = _world->getOnlineRegistry().get_components<Clickable>();
    for (std::optional<Drawable> &drawable : drawables) {
        if (drawable && drawable.has_value() && drawable->getMessage() == _world->getRoomName()) {
            drawable->setColor({102, 153, 153});
        }
    }
    drawables[index]->setColor({51, 204, 51});
    int onlineEntities = _world->getNbEntitiesOnline();
    std::pair<int, std::size_t> nbPages = _world->getPageNumber();
    std::vector<std::tuple<std::size_t, bool, std::size_t, std::size_t, std::string>> roomList = _world->getRoomsList();
    std::size_t indexRoom = std::get<0>(roomList.at(index - nbPages.first + nbPages.second));
    std::size_t nbMaxInRoom = std::get<2>(roomList.at(index - nbPages.first + nbPages.second));
    _world->setRoomIndex(indexRoom);
    _world->setRoomName(drawables[index]->getMessage());
    _world->setNbInRoom({0, nbMaxInRoom});
    std::map<std::string, int> &keys = _world->getKeysIndex();
    if (keys["roomPassword"] >= 0) {
        void *roomButtonT = clickables[index]->getInfos();
        if (roomButtonT && clickables[index]->getKindButton() == Clickable::ROOMBUTTON) {
            Buttons::RoomButton_t *button = static_cast<Buttons::RoomButton_t *>(roomButtonT);
            drawablesOffline[keys["roomPassword"]]->setMessage("");
            if (button->_isPublic) {
                positionsOffline[keys["roomPassword"]]->setPosition({9999, 9999});
            } else {
                positionsOffline[keys["roomPassword"]]->setPosition({960, 650});
            }
        }
    }
}

void Buttons::textButton(std::size_t index)
{
    _world->setTextWritting(index);
}

void Buttons::toggleButton(std::size_t index)
{
    ComponentArray<Clickable> &clickables = _world->getRegistry().get_components<Clickable>();
    ComponentArray<Drawable> &drawables = _world->getRegistry().get_components<Drawable>();
    void *buttonT = clickables[index]->getInfos();
    if (buttonT && clickables[index]->getKindButton() == Clickable::SPLITBUTTON) {
        Buttons::SplitButton_t *button = static_cast<Buttons::SplitButton_t *>(buttonT);
        if (button->_active) {
            return;
        }
        button->_active = true;
        if (button->_activePt != nullptr) {
            *button->_activePt = true;
        }
        Buttons::SplitButton_t *other = button->_other;
        other->_active = false;
        if (other->_activePt != nullptr) {
            *other->_activePt = false;
        }
        if (button->_actionActivation) {
            button->_actionActivation(button->_actionActivationParam);
        }
        drawables[button->_index]->setColor(button->_activerColor);
        drawables[other->_index]->setColor(other->_defaultColor);
    }
}

void Buttons::keyButton(std::size_t index)
{
    ComponentArray<Clickable> &clickables = _world->getRegistry().get_components<Clickable>();
    ComponentArray<Drawable> &drawables = _world->getRegistry().get_components<Drawable>();
    if (_world->getControlWritting() >= 0) {
        void *oldButtonT = clickables[_world->getControlWritting()]->getInfos();
        if (oldButtonT && clickables[_world->getControlWritting()]->getKindButton() == Clickable::KEYBUTTON) {
            Buttons::KeyButton_t *button = static_cast<Buttons::KeyButton_t *>(oldButtonT);
            if (*button->_key == sf::Keyboard::Unknown) {
                drawables[_world->getControlWritting()]->setMessage("EMPTY");
            }
            drawables[_world->getControlWritting()]->setColor(button->_defaultColor);
        }
    }
    _world->setControlWritting(index);
    _world->setTextWritting(-1);
    void *buttonT = clickables[index]->getInfos();
    if (buttonT && clickables[index]->getKindButton() == Clickable::KEYBUTTON) {
        Buttons::KeyButton_t *button = static_cast<Buttons::KeyButton_t *>(buttonT);
        *button->_key = sf::Keyboard::Unknown;
        drawables[index]->setMessage("");
        drawables[index]->setColor(button->_activeColor);
    }
}

void Buttons::nextRoomsPage(std::size_t index)
{
    std::pair<int, std::size_t> pageNumber = _world->getPageNumber();
    size_t indexPageNumber = pageNumber.second + 5;
    if (indexPageNumber >= _world->getRoomsList().size())
        return;
    _world->setPageNumber({pageNumber.first, indexPageNumber});
}

void Buttons::previousRoomsPage(std::size_t index)
{
    std::pair<int, std::size_t> pageNumber = _world->getPageNumber();
    size_t indexPageNumber = pageNumber.second;
    if (indexPageNumber == 0)
        return;
    _world->setPageNumber({pageNumber.first, indexPageNumber - 5});
}

Buttons::textButton_t *Buttons::setTextButton(std::string name, std::string messageDefault, std::size_t index)
{
    Buttons::textButton_t node;
    node._name = name;
    node._messageDefault = messageDefault;
    _listTextButton[index] = node;
    return &(_listTextButton[index]);
}

Buttons::NumButton_t *Buttons::setNumButton(std::string messageDefault, std::size_t index)
{
    Buttons::NumButton_t node;
    node._messageDefault = messageDefault;
    _listNumButton[index] = node;
    return &(_listNumButton[index]);
}

Buttons::SplitButton_t *Buttons::setSplitButton(sf::Color defaultColor, sf::Color activerColor, std::size_t index,
    bool *activePt, std::function<void(std::size_t)> actionActivation, std::size_t actionActivationParam)
{
    Buttons::SplitButton_t node;
    node._active = false;
    node._defaultColor = defaultColor;
    node._activerColor = activerColor;
    node._index = index;
    node._other = nullptr;
    node._activePt = activePt;
    node._actionActivation = actionActivation;
    node._actionActivationParam = actionActivationParam;
    _listSplitButton[index] = node;
    return &(_listSplitButton[index]);
}

Buttons::KeyButton_t *Buttons::setKeyButton(
    std::size_t index, sf::Keyboard::Key *key, sf::Color defaultColor, sf::Color activerColor)
{
    Buttons::KeyButton_t node;
    node._key = key;
    node._activeColor = activerColor;
    node._defaultColor = defaultColor;
    if (!writeKeyButton(*key, *_world, index)) {
        *node._key = sf::Keyboard::Unknown;
    }
    _listKeyButton[index] = node;
    return &(_listKeyButton[index]);
}

Buttons::BackButton_t *Buttons::setBackButton(std::size_t index, World::GAME_STATE previousState)
{
    Buttons::BackButton_t node;
    node._previousState = previousState;
    _listBackButton[index] = node;
    return &(_listBackButton[index]);
}

Buttons::RoomButton_t *Buttons::setRoomButton(std::size_t index, bool isPublic)
{
    Buttons::RoomButton_t node;
    node._isPublic = isPublic;
    _listRoomButton[index] = node;
    return &(_listRoomButton[index]);
}

bool Buttons::writeKeyButton(sf::Keyboard::Key key, World &world, std::size_t index)
{
    ComponentArray<Drawable> &drawables = world.getRegistry().get_components<Drawable>();

    std::string message = "";
    if (key == sf::Keyboard::Unknown) {
        drawables[index]->setMessage("EMPTY");
        return false;
    }
    if (key < 26) {
        char c = key + 'A';
        drawables[index]->setMessage(message + c);
        return true;
    }
    if (key >= 26 && key <= 35) {
        char c = key - 26 + '0';
        drawables[index]->setMessage(message + c);
        return true;
    }
    if (key >= 75 && key <= 84) {
        char c = key - 75 + '0';
        drawables[index]->setMessage(message + c);
        return true;
    }
    if (key == sf::Keyboard::Space) {
        drawables[index]->setMessage("SPACE");
        return true;
    }
    if (key == sf::Keyboard::Tab) {
        drawables[index]->setMessage("TAB");
        return true;
    }
    if (key == sf::Keyboard::LAlt) {
        drawables[index]->setMessage("L ALT");
        return true;
    }
    if (key == sf::Keyboard::LControl) {
        drawables[index]->setMessage("L CTRL");
        return true;
    }
    if (key == sf::Keyboard::LShift) {
        drawables[index]->setMessage("L SHIFT");
        return true;
    }
    if (key == sf::Keyboard::RAlt) {
        drawables[index]->setMessage("R ALT");
        return true;
    }
    if (key == sf::Keyboard::RControl) {
        drawables[index]->setMessage("R CTRL");
        return true;
    }
    if (key == sf::Keyboard::RShift) {
        drawables[index]->setMessage("R SHIFT");
        return true;
    }
    if (key == sf::Keyboard::Enter) {
        drawables[index]->setMessage("ENTER");
        return true;
    }
    if (key == sf::Keyboard::Left) {
        drawables[index]->setMessage("LEFT ARROW");
        return true;
    }
    if (key == sf::Keyboard::Right) {
        drawables[index]->setMessage("RIGHT ARROW");
        return true;
    }
    if (key == sf::Keyboard::Up) {
        drawables[index]->setMessage("UP ARROW");
        return true;
    }
    if (key == sf::Keyboard::Down) {
        drawables[index]->setMessage("DOWN ARROW");
        return true;
    }
    drawables[index]->setMessage("EMPTY");
    return false;
}

void Buttons::writeNumButton(sf::Keyboard::Key key, World &world, std::size_t index)
{
    ComponentArray<Drawable> &drawables = world.getRegistry().get_components<Drawable>();

    std::string message = drawables[index]->getMessage();
    if (key >= 26 && key <= 35) {
        char c = key - 26 + '0';
        drawables[index]->setMessage(message + c);
    }
    if (key >= 75 && key <= 84) {
        char c = key - 75 + '0';
        drawables[index]->setMessage(message + c);
    }
    if (key == sf::Keyboard::BackSpace) {
        if (message.size() > 0)
            message.pop_back();
        drawables[index]->setMessage(message);
    }
}

void Buttons::linkSplitButton(SplitButton_t *button_1, SplitButton_t *button_2)
{
    button_1->_active = true;
    button_2->_active = false;
    button_1->_other = button_2;
    button_2->_other = button_1;
}
