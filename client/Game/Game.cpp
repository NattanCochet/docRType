/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Game
*/

#include "Game.hpp"

Game::Game()
{
    _window.create(sf::VideoMode(1920, 1080), "R-TYPE", sf::Style::Fullscreen);
    _window.setFramerateLimit(60);
    srand(time(NULL));
    _world = new World(true, &_window);
    _network = Network(_world);
    _buttons = Buttons(_world, &_network);
    _nbRooms = 0;
    _roomsPage = 0;
}

Game::~Game()
{
}

int Game::init()
{
    NetworkClient &client = _world->getClient();
    try {

        std::atomic<bool> running(true);

        // Thread pour recevoir les messages
        std::thread receive_thread(
            [this](NetworkClient &client, World &world, std::atomic<bool> &running) {
                _network.receive_messages(client, world, running);
            },
            std::ref(client), std::ref(*_world), std::ref(running));

        // Envoyer un message de connexion
        _network.send_join_message(client);

        try {
            play();
        }
        catch (Error &e) {
            std::cerr << e.what() << std::endl;
        }

        // Déconnexion propre après la boucle
        _network.send_leave_message(client);

        running.store(false);
        receive_thread.join();
    }
    catch (...) {
        _network.send_leave_message(client);
        return 84;
    }
    return 0;
}

void Game::play()
{
    Systems systems = Systems();
    systems.loadSystemsInWorld(*_world);
    Registry &r = _world->getRegistry();
    ComponentArray<Clickable> &clickables = r.get_components<Clickable>();
    initMenuEntities(r);
    World::GAME_STATE currentState = _world->getState();
    sf::Clock clock;
    sf::Sound sound;
    sf::SoundBuffer sounfBuffer;
    sounfBuffer.loadFromFile(std::string(PATH) + "client/Assets/backgroundMusic.mp3");
    sound.setBuffer(sounfBuffer);
    sound.setLoop(true);
    // sound.play();
    int begin = 0;
    while (_window.isOpen()) {
        currentState = _world->getState();
        if (event() == -1)
            break;
        allProcess(r, currentState, begin);
        if (begin == 0 && _world->getState() == World::NETWORK_MENU)
            begin = 1;
        _window.clear();
        for (std::function<int(World &, Network *)> func : r.get_systems()) {
            func(*_world, &_network);
        }
        for (std::function<int(World &, Network *)> func : _world->getOnlineRegistry().get_systems()) {
            func(*_world, &_network);
        }
        _window.display();
        if (currentState != _world->getState()) {
            killAllEntities(r);
            if (currentState != World::LOBBY_MENU || _world->getState() != World::IN_GAME)
                killAllEntities(_world->getOnlineRegistry());
            _world->resetKeysIndex();
            _world->setNbEntities(0);
            _world->setTextWritting(-1);
            _world->setControlWritting(-1);
            _world->setPreviousState(currentState);
            initNewEntities(r, _world->getState());
        }
        if (_world->getState() != World::NETWORK_MENU)
            begin = 0;
        float seconds = clock.getElapsedTime().asSeconds();
        if (_world->getServerConnection() == false && seconds > 5) {
            _network.send_join_message(_world->getClient());
            clock.restart();
        }
    }
    sound.stop();
}

int Game::event(void)
{
    _world->clearMouseAction();
    while (_window.pollEvent(_event)) {
        switch (_event.type) {
        case sf::Event::Closed:
            return (-1);
        case sf::Event::KeyPressed:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                return (-1);
            _world->addKeyAction(World::PRESSED, _event.key.code);
            break;
        case sf::Event::KeyReleased:
            _world->addKeyAction(World::RELEASED, _event.key.code);
            break;
        case sf::Event::MouseButtonPressed:
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                _world->addMouseAction(World::PRESSED, sf::Mouse::getPosition(_window));
            break;
        default:
            break;
        }
    }
    return 0;
}

void Game::initNewEntities(Registry &r, World::GAME_STATE newState)
{
    switch (newState) {
    case World::MENU:
        initMenuEntities(r);
        break;
    case World::NETWORK_MENU:
        initNetworkMenuEntities(r);
        break;
    case World::CREATE_ROOM:
        initCreateRoomEntities(r);
        break;
    case World::IN_GAME:
        initInGameEntities(r);
        break;
    case World::CONTROLS_MENU:
        initControlsMenuEntities(r);
        break;
    case World::LOBBY_MENU:
        initLobbyMenuEntities(r);
        break;
    default:
        break;
    }
}

void Game::initMenuEntities(Registry &r)
{
    for (size_t i = 0; i < 6; i++) {
        r.spawn_entity();
    }
    ComponentArray<Position> &positions = r.get_components<Position>();
    ComponentArray<Drawable> &drawables = r.get_components<Drawable>();
    ComponentArray<Clickable> &clickable = r.get_components<Clickable>();
    ComponentArray<Controllable> &control = r.get_components<Controllable>();
    positions.insert_at(0, Position(965, 540));
    drawables.insert_at(0, Drawable("background", Drawable::SPRITE, {2.5, 2.5}, {0, 0, 800, 430}, 180));
    positions.insert_at(1, Position(960, 100));
    drawables.insert_at(1, Drawable("titleMenuTTF", Drawable::TEXT, {1, 1}, "R-TYPE", 65, {74, 246, 38}, 0));
    positions.insert_at(2, Position(960, 350));
    drawables.insert_at(
        2, Drawable("robotoTTF", Drawable::BUTTON, {1, 1}, "Play", 38, {0, 0, 0}, {0, 250, 0}, {380, 80}, 0));
    clickable.insert_at(
        2, Clickable([this](std::size_t idx) { _buttons.playButton(idx); }, 2, NULL, Clickable::BASICBUTTON));
    positions.insert_at(3, Position(960, 450));
    drawables.insert_at(
        3, Drawable("robotoTTF", Drawable::BUTTON, {1, 1}, "Controls", 38, {0, 0, 0}, {0, 0, 250}, {380, 80}, 0));
    clickable.insert_at(
        3, Clickable([this](std::size_t idx) { _buttons.controlsButton(idx); }, 3, NULL, Clickable::BASICBUTTON));
    positions.insert_at(4, Position(960, 550));
    drawables.insert_at(
        4, Drawable("robotoTTF", Drawable::BUTTON, {1, 1}, "Quit", 38, {0, 0, 0}, {250, 0, 0}, {380, 80}, 0));
    clickable.insert_at(
        4, Clickable([this](std::size_t idx) { _buttons.quitButton(idx); }, 3, NULL, Clickable::BASICBUTTON));
    _world->setNbEntities(5);
}

void Game::initNetworkMenuEntities(Registry &r)
{
    for (size_t i = 0; i < 10; i++) {
        r.spawn_entity();
    }
    ComponentArray<Position> &positions = r.get_components<Position>();
    ComponentArray<Drawable> &drawables = r.get_components<Drawable>();
    ComponentArray<Clickable> &clickable = r.get_components<Clickable>();
    ComponentArray<Controllable> &control = r.get_components<Controllable>();
    positions.insert_at(0, Position(965, 540));
    drawables.insert_at(0, Drawable("background", Drawable::SPRITE, {2.5, 2.5}, {0, 0, 800, 430}, 0));
    positions.insert_at(1, Position(960, 950));
    drawables.insert_at(
        1, Drawable("robotoTTF", Drawable::BUTTON, {1, 1}, "Back", 38, {0, 0, 0}, {250, 0, 0}, {380, 80}, 0));
    Buttons::BackButton_t *backButton = _buttons.setBackButton(1, World::MENU);
    clickable.insert_at(
        1, Clickable([this](std::size_t idx) { _buttons.backButton(idx); }, 1, backButton, Clickable::BACKBUTTON));
    positions.insert_at(2, Position(960, 850));
    drawables.insert_at(
        2, Drawable("robotoTTF", Drawable::BUTTON, {1, 1}, "Join", 38, {0, 0, 0}, {0, 250, 0}, {380, 80}, 0));
    clickable.insert_at(
        2, Clickable([this](std::size_t idx) { _buttons.joinButton(idx); }, 2, NULL, Clickable::BASICBUTTON));
    positions.insert_at(3, Position(960, 750));
    drawables.insert_at(
        3, Drawable("robotoTTF", Drawable::BUTTON, {1, 1}, "Create", 38, {0, 0, 0}, {51, 153, 255}, {380, 80}, 0));
    clickable.insert_at(
        3, Clickable([this](std::size_t idx) { _buttons.createMenuButton(idx); }, 3, NULL, Clickable::BASICBUTTON));
    positions.insert_at(4, Position(1320, 400));
    drawables.insert_at(
        4, Drawable("arrowsTTF", Drawable::BUTTON, {1, 1}, /*"↻"*/ "y", 38, {0, 0, 0}, {77, 77, 77}, {60, 60}, 0));
    clickable.insert_at(
        4, Clickable([this](std::size_t idx) { _buttons.reloadButton(idx); }, 4, NULL, Clickable::BASICBUTTON));
    positions.insert_at(5, Position(1260, 400));
    drawables.insert_at(
        5, Drawable("arrowsTTF", Drawable::BUTTON, {1, 1}, /*"<-"*/ "b", 38, {0, 0, 0}, {77, 77, 77}, {60, 60}, 0));
    clickable.insert_at(
        5, Clickable([this](std::size_t idx) { _buttons.previousRoomsPage(idx); }, 4, NULL, Clickable::BASICBUTTON));
    positions.insert_at(6, Position(1380, 400));
    drawables.insert_at(
        6, Drawable("arrowsTTF", Drawable::BUTTON, {1, 1}, /*"->"*/ "a", 38, {0, 0, 0}, {77, 77, 77}, {60, 60}, 0));
    clickable.insert_at(
        6, Clickable([this](std::size_t idx) { _buttons.nextRoomsPage(idx); }, 4, NULL, Clickable::BASICBUTTON));
    positions.insert_at(7, Position(9999, 9999));
    drawables.insert_at(
        7, Drawable("robotoTTF", Drawable::BUTTON, {1, 1}, "", 38, {0, 0, 0}, {250, 250, 250}, {380, 80}, 0));
    Buttons::textButton_t *passwordButtonText = _buttons.setTextButton("roomPassword", "Password of Room", 7);
    clickable.insert_at(7,
        Clickable([this](std::size_t idx) { _buttons.textButton(idx); }, 7, passwordButtonText, Clickable::TEXTBUTTON));
    positions.insert_at(8, Position(960, 550));
    drawables.insert_at(8, Drawable("robotoTTF", Drawable::TEXT, {1, 1}, " ", 50, {255, 0, 0}, 0));
    _world->setNbEntities(9);
    std::map<std::string, int> &keys = _world->getKeysIndex();
    keys["roomPassword"] = 7;
    keys["roomErrorText"] = 8;
    _network.sendGetRoomMessage(_world->getClient());
}

void Game::initCreateRoomEntities(Registry &r)
{
    ComponentArray<Position> &positions = r.get_components<Position>();
    ComponentArray<Drawable> &drawables = r.get_components<Drawable>();
    ComponentArray<Clickable> &clickable = r.get_components<Clickable>();
    ComponentArray<Controllable> &control = r.get_components<Controllable>();
    for (size_t i = 0; i < 12; i++) {
        r.spawn_entity();
    }
    positions.insert_at(0, Position(965, 540));
    drawables.insert_at(0, Drawable("background", Drawable::SPRITE, {2.5, 2.5}, {0, 0, 800, 430}, 0));
    positions.insert_at(1, Position(960, 850));
    drawables.insert_at(
        1, Drawable("robotoTTF", Drawable::BUTTON, {1, 1}, "Create", 38, {0, 0, 0}, {51, 153, 255}, {380, 80}, 0));
    clickable.insert_at(
        1, Clickable([this](std::size_t idx) { _buttons.createRoomButton(idx); }, 1, NULL, Clickable::BASICBUTTON));
    positions.insert_at(2, Position(960, 250));
    drawables.insert_at(
        2, Drawable("robotoTTF", Drawable::BUTTON, {1, 1}, "", 38, {0, 0, 0}, {250, 250, 250}, {380, 80}, 0));
    Buttons::textButton_t *nameButtonText = _buttons.setTextButton("roomName", "Name of room", 2);
    clickable.insert_at(
        2, Clickable([this](std::size_t idx) { _buttons.textButton(idx); }, 2, nameButtonText, Clickable::TEXTBUTTON));
    positions.insert_at(3, Position(9999, 9999));
    drawables.insert_at(
        3, Drawable("robotoTTF", Drawable::BUTTON, {1, 1}, "", 38, {0, 0, 0}, {250, 250, 250}, {380, 80}, 0));
    Buttons::textButton_t *passwordButtonText = _buttons.setTextButton("createRoomPassword", "Password of Room", 3);
    clickable.insert_at(3,
        Clickable([this](std::size_t idx) { _buttons.textButton(idx); }, 3, passwordButtonText, Clickable::TEXTBUTTON));
    positions.insert_at(4, Position(860, 450));
    drawables.insert_at(
        4, Drawable("robotoTTF", Drawable::BUTTON, {1, 1}, "Public", 38, {0, 0, 0}, {200, 255, 200}, {180, 80}, 0));
    Buttons::SplitButton_t *publicButtonSplit = _buttons.setSplitButton(
        {211, 211, 211}, {200, 255, 200}, 4, nullptr,
        [this](std::size_t idx) { moveCreateRoomPasswordButtonAway(idx); }, 3);
    clickable.insert_at(4, Clickable([this](std::size_t idx) { _buttons.toggleButton(idx); }, 4, publicButtonSplit,
                               Clickable::SPLITBUTTON));
    positions.insert_at(5, Position(1060, 450));
    drawables.insert_at(
        5, Drawable("robotoTTF", Drawable::BUTTON, {1, 1}, "Private", 38, {0, 0, 0}, {211, 211, 211}, {180, 80}, 0));
    Buttons::SplitButton_t *privateButtonSplit = _buttons.setSplitButton(
        {211, 211, 211}, {255, 200, 200}, 5, nullptr,
        [this](std::size_t idx) { moveCreateRoomPasswordButtonBack(idx); }, 3);
    clickable.insert_at(5, Clickable([this](std::size_t idx) { _buttons.toggleButton(idx); }, 5, privateButtonSplit,
                               Clickable::SPLITBUTTON));
    Buttons::linkSplitButton(publicButtonSplit, privateButtonSplit);
    positions.insert_at(6, Position(960, 550));
    drawables.insert_at(
        6, Drawable("robotoTTF", Drawable::BUTTON, {1, 1}, "", 38, {0, 0, 0}, {250, 250, 250}, {380, 80}, 0));
    Buttons::NumButton_t *levelButtonNum = _buttons.setNumButton("Number of players", 6);
    clickable.insert_at(
        6, Clickable([this](std::size_t idx) { _buttons.textButton(idx); }, 6, levelButtonNum, Clickable::NUMBUTTON));
    positions.insert_at(7, Position(960, 650));
    drawables.insert_at(7, Drawable("robotoTTF", Drawable::TEXT, {1, 1}, " ", 50, {255, 0, 0}, 0));
    positions.insert_at(8, Position(90, 55));
    drawables.insert_at(
        8, Drawable("robotoTTF", Drawable::BUTTON, {1, 1}, "BACK", 38, {0, 0, 0}, {211, 211, 211}, {140, 70}, 0));
    Buttons::BackButton_t *backButton = _buttons.setBackButton(8, World::NETWORK_MENU);
    clickable.insert_at(
        8, Clickable([this](std::size_t idx) { _buttons.backButton(idx); }, 8, backButton, Clickable::BACKBUTTON));

    positions.insert_at(9, Position(860, 650));
    drawables.insert_at(
        9, Drawable("robotoTTF", Drawable::BUTTON, {1, 1}, "Fill", 38, {0, 0, 0}, {200, 255, 200}, {180, 80}, 0));
    Buttons::SplitButton_t *noFillButtonSplit = _buttons.setSplitButton(
        {211, 211, 211}, {200, 255, 200}, 9, nullptr,
        nullptr, 9);
    clickable.insert_at(9, Clickable([this](std::size_t idx) { _buttons.toggleButton(idx); }, 9, noFillButtonSplit,
                               Clickable::SPLITBUTTON));
    positions.insert_at(10, Position(1060, 650));
    drawables.insert_at(
        10, Drawable("robotoTTF", Drawable::BUTTON, {1, 1}, "Do not fill", 38, {0, 0, 0}, {211, 211, 211}, {180, 80}, 0));
    Buttons::SplitButton_t *fillButtonSplit = _buttons.setSplitButton(
        {211, 211, 211}, {255, 200, 200}, 10, nullptr,
        nullptr, 10);
    clickable.insert_at(10, Clickable([this](std::size_t idx) { _buttons.toggleButton(idx); }, 10, fillButtonSplit,
                               Clickable::SPLITBUTTON));
    Buttons::linkSplitButton(noFillButtonSplit, fillButtonSplit);

    _world->setNbEntities(11);
    std::map<std::string, int> &keys = _world->getKeysIndex();
    keys["roomNameCreate"] = 2;
    keys["roomPasswordCreate"] = 3;
    keys["roomIsPublicCreate"] = 4;
    keys["roomFillAI"] = 9;
    keys["roomMaxNbrPlayerCreate"] = 6;
    keys["roomErrorCreate"] = 7;
}

void Game::initInGameEntities(Registry &r)
{
    for (size_t i = 0; i <= 4; i++) {
        r.spawn_entity();
    }
    ComponentArray<Position> &positions = r.get_components<Position>();
    ComponentArray<Drawable> &drawables = r.get_components<Drawable>();
    ComponentArray<Clickable> &clickable = r.get_components<Clickable>();
    ComponentArray<Controllable> &control = r.get_components<Controllable>();
    positions.insert_at(0, Position(965, 540));
    drawables.insert_at(0, Drawable("background", Drawable::SPRITE, {2.5, 2.5}, {0, 0, 800, 430}, 0));
    positions.insert_at(1, Position(960, 50));
    drawables.insert_at(1, Drawable("robotoTTF", Drawable::TEXT, {1, 1}, "Score: 0", 50, {250, 250, 250}, 0));
    positions.insert_at(2, Position(1700, 50));
    drawables.insert_at(2, Drawable("robotoTTF", Drawable::TEXT, {1, 1}, "Level: 1", 50, {250, 250, 250}, 0));
    _world->setNbEntities(3);
    std::map<std::string, int> &keys = _world->getKeysIndex();
    keys["scoreGameText"] = 1;
    keys["levelGameText"] = 2;
}

void Game::initControlsMenuEntities(Registry &r)
{
    for (size_t i = 0; i <= 13; i++) {
        r.spawn_entity();
    }
    ComponentArray<Position> &positions = r.get_components<Position>();
    ComponentArray<Drawable> &drawables = r.get_components<Drawable>();
    ComponentArray<Clickable> &clickable = r.get_components<Clickable>();
    ComponentArray<Controllable> &control = r.get_components<Controllable>();
    positions.insert_at(0, Position(965, 540));
    drawables.insert_at(0, Drawable("background", Drawable::SPRITE, {2.5, 2.5}, {0, 0, 800, 430}, 0));
    positions.insert_at(1, Position(90, 55));
    drawables.insert_at(
        1, Drawable("robotoTTF", Drawable::BUTTON, {1, 1}, "BACK", 38, {0, 0, 0}, {211, 211, 211}, {140, 70}, 0));
    Buttons::BackButton_t *backButton = _buttons.setBackButton(1, World::MENU);
    clickable.insert_at(
        1, Clickable([this](std::size_t idx) { _buttons.backButton(idx); }, 1, backButton, Clickable::BACKBUTTON));
    positions.insert_at(2, Position(600, 350));
    drawables.insert_at(2, Drawable("robotoTTF", Drawable::TEXT, {1, 1}, "ATTACK", 30, {250, 250, 250}, 0));
    positions.insert_at(3, Position(600, 450));
    drawables.insert_at(3, Drawable("robotoTTF", Drawable::TEXT, {1, 1}, "MOVE UP", 30, {250, 250, 250}, 0));
    positions.insert_at(4, Position(600, 550));
    drawables.insert_at(4, Drawable("robotoTTF", Drawable::TEXT, {1, 1}, "MOVE DOWN", 30, {250, 250, 250}, 0));
    positions.insert_at(5, Position(600, 650));
    drawables.insert_at(5, Drawable("robotoTTF", Drawable::TEXT, {1, 1}, "MOVE LEFT", 30, {250, 250, 250}, 0));
    positions.insert_at(6, Position(600, 750));
    drawables.insert_at(6, Drawable("robotoTTF", Drawable::TEXT, {1, 1}, "MOVE RIGHT", 30, {250, 250, 250}, 0));
    positions.insert_at(13, Position(600, 850));
    drawables.insert_at(13, Drawable("robotoTTF", Drawable::TEXT, {1, 1}, "FORCE", 30, {250, 250, 250}, 0));
    positions.insert_at(7, Position(900, 350));
    drawables.insert_at(
        7, Drawable("robotoTTF", Drawable::BUTTON, {1, 1}, "SPACE", 30, {0, 0, 0}, {211, 211, 211}, {240, 70}, 0));
    Buttons::KeyButton_t *attackButtonKey =
        _buttons.setKeyButton(7, &(_world->_controlsMap[CONTROL::SHOOT]), {211, 211, 211}, {255, 255, 200});
    clickable.insert_at(
        7, Clickable([this](std::size_t idx) { _buttons.keyButton(idx); }, 7, attackButtonKey, Clickable::KEYBUTTON));
    positions.insert_at(8, Position(900, 450));
    drawables.insert_at(
        8, Drawable("robotoTTF", Drawable::BUTTON, {1, 1}, "UP ARROW", 30, {0, 0, 0}, {211, 211, 211}, {240, 70}, 0));
    Buttons::KeyButton_t *upButtonKey =
        _buttons.setKeyButton(8, &(_world->_controlsMap[CONTROL::UP]), {211, 211, 211}, {255, 255, 200});
    clickable.insert_at(
        8, Clickable([this](std::size_t idx) { _buttons.keyButton(idx); }, 8, upButtonKey, Clickable::KEYBUTTON));
    positions.insert_at(9, Position(900, 550));
    drawables.insert_at(
        9, Drawable("robotoTTF", Drawable::BUTTON, {1, 1}, "DOWN ARROW", 30, {0, 0, 0}, {211, 211, 211}, {240, 70}, 0));
    Buttons::KeyButton_t *downButtonKey =
        _buttons.setKeyButton(9, &(_world->_controlsMap[CONTROL::DOWN]), {211, 211, 211}, {255, 255, 200});
    clickable.insert_at(
        9, Clickable([this](std::size_t idx) { _buttons.keyButton(idx); }, 9, downButtonKey, Clickable::KEYBUTTON));
    positions.insert_at(10, Position(900, 650));
    drawables.insert_at(10,
        Drawable("robotoTTF", Drawable::BUTTON, {1, 1}, "LEFT ARROW", 30, {0, 0, 0}, {211, 211, 211}, {240, 70}, 0));
    Buttons::KeyButton_t *leftButtonKey =
        _buttons.setKeyButton(10, &(_world->_controlsMap[CONTROL::LEFT]), {211, 211, 211}, {255, 255, 200});
    clickable.insert_at(
        10, Clickable([this](std::size_t idx) { _buttons.keyButton(idx); }, 10, leftButtonKey, Clickable::KEYBUTTON));
    positions.insert_at(11, Position(900, 750));
    drawables.insert_at(11,
        Drawable("robotoTTF", Drawable::BUTTON, {1, 1}, "RIGHT ARROW", 30, {0, 0, 0}, {211, 211, 211}, {240, 70}, 0));
    Buttons::KeyButton_t *rightButtonKey =
        _buttons.setKeyButton(11, &(_world->_controlsMap[CONTROL::RIGHT]), {211, 211, 211}, {255, 255, 200});
    clickable.insert_at(
        11, Clickable([this](std::size_t idx) { _buttons.keyButton(idx); }, 11, rightButtonKey, Clickable::KEYBUTTON));
    positions.insert_at(12, Position(900, 850));
    drawables.insert_at(
        12, Drawable("robotoTTF", Drawable::BUTTON, {1, 1}, "ENTER", 30, {0, 0, 0}, {211, 211, 211}, {240, 70}, 0));
    Buttons::KeyButton_t *forcetButtonKey =
        _buttons.setKeyButton(12, &(_world->_controlsMap[CONTROL::FORCE]), {211, 211, 211}, {255, 255, 200});
    clickable.insert_at(
        12, Clickable([this](std::size_t idx) { _buttons.keyButton(idx); }, 11, forcetButtonKey, Clickable::KEYBUTTON));
    _world->setNbEntities(13);
}

void Game::initLobbyMenuEntities(Registry &r)
{
    size_t nb_entities = 5;
    for (size_t i = 0; i < nb_entities + 1; i++) {
        r.spawn_entity();
    }
    ComponentArray<Position> &positions = r.get_components<Position>();
    ComponentArray<Drawable> &drawables = r.get_components<Drawable>();
    ComponentArray<Clickable> &clickable = r.get_components<Clickable>();
    ComponentArray<Controllable> &control = r.get_components<Controllable>();
    positions.insert_at(0, Position(965, 540));
    drawables.insert_at(0, Drawable("background", Drawable::SPRITE, {2.5, 2.5}, {0, 0, 800, 430}, 0));
    positions.insert_at(1, Position(90, 55));
    drawables.insert_at(
        1, Drawable("robotoTTF", Drawable::BUTTON, {1, 1}, "BACK", 38, {0, 0, 0}, {211, 211, 211}, {140, 70}, 0));
    Buttons::BackButton_t *backButton = _buttons.setBackButton(1, World::NETWORK_MENU);
    clickable.insert_at(
        1, Clickable([this](std::size_t idx) { _buttons.backButton(idx); }, 1, backButton, Clickable::BACKBUTTON));
    positions.insert_at(2, Position(960, 750));
    drawables.insert_at(
        2, Drawable("robotoTTF", Drawable::BUTTON, {1, 1}, "Ready", 38, {0, 0, 0}, {0, 250, 0}, {380, 80}, 0));
    clickable.insert_at(
        2, Clickable([this](std::size_t idx) { _buttons.startButton(idx); }, 2, NULL, Clickable::BASICBUTTON));
    positions.insert_at(3, Position(960, 100));
    std::string roomNameMessage = "Room: " + _world->getRoomName();
    drawables.insert_at(3, Drawable("robotoTTF", Drawable::TEXT, {1, 1}, roomNameMessage, 100, {250, 250, 250}, 0));
    std::stringstream ss;
    ss << std::get<0>(_world->getNbInRoom()) << " / " << std::get<1>(_world->getNbInRoom());
    positions.insert_at(4, Position(960, 200));
    drawables.insert_at(4, Drawable("robotoTTF", Drawable::TEXT, {1, 1}, ss.str(), 100, {250, 250, 250}, 0));
    std::map<std::string, int> &keys = _world->getKeysIndex();
    keys["LobbyPlayerCountText"] = 4;
    _world->setNbEntities(nb_entities);
}

void Game::killAllEntities(Registry &r)
{
    std::size_t idx = 0;
    ComponentArray<Position> &positions = r.get_components<Position>();
    ComponentArray<Drawable> &drawables = r.get_components<Drawable>();
    ComponentArray<Clickable> &clickable = r.get_components<Clickable>();
    ComponentArray<Controllable> &control = r.get_components<Controllable>();
    for (auto it = positions.end(); it != positions.begin(); it--) {
        r.kill_entity(r.entity_from_index(idx));
        idx++;
    }
    positions.compaction();
    drawables.compaction();
    clickable.compaction();
    control.compaction();
}

void Game::allProcess(Registry &r, World::GAME_STATE state, int begin)
{
    switch (state) {
    case World::NETWORK_MENU:
        printRooms(r, begin);
        break;
    default:
        break;
    }
}

void Game::printRooms(Registry &r, int begin)
{
    Registry &rOnline = _world->getOnlineRegistry();
    ComponentArray<Position> &positions = rOnline.get_components<Position>();
    ComponentArray<Drawable> &drawables = rOnline.get_components<Drawable>();
    ComponentArray<Clickable> &clickable = rOnline.get_components<Clickable>();
    std::size_t i = 0;
    std::vector<std::tuple<std::size_t, bool, std::size_t, std::size_t, std::string>> rooms = _world->getRoomsList();
    std::size_t nbRoom = rooms.size();
    std::pair<int, std::size_t> nbPage = _world->getPageNumber();
    std::size_t sizeRoomList = rooms.size() - nbPage.second;
    if (begin == 0) {
        int nbEntities = _world->getNbEntitiesOnline();
        _world->setPageNumber({nbEntities, 0});
        _nbRooms = nbRoom;
        for (i = 0; i < sizeRoomList && i < 5; i++) {
            Entity roomEntity = rOnline.spawn_entity();
            positions.insert_at(nbEntities + i, Position(960, 60 * i + 150));
            drawables.insert_at(
                nbEntities + i, Drawable("robotoTTF", Drawable::BUTTON, {1, 1}, std::get<4>(rooms.at(i + _roomsPage)),
                                    25, {0, 0, 0}, {102, 153, 153}, {300, 40}, 0));
            Buttons::RoomButton_t *roomdButton =
                _buttons.setRoomButton(i + nbEntities, std::get<1>(rooms.at(i + _roomsPage)));
            clickable.insert_at(nbEntities + i, Clickable([this](std::size_t idx) { _buttons.selectRoomButton(idx); },
                                                    nbEntities + i, roomdButton, Clickable::ROOMBUTTON));
            Entity lockEntity = rOnline.spawn_entity();
            if (!std::get<1>(rooms.at(i + _roomsPage))) {
                positions.insert_at(nbEntities + i + 5, Position(1070, 60 * i + 150));
            } else {
                positions.insert_at(nbEntities + i + 5, Position(9999, 9999));
            }
            drawables.insert_at(
                nbEntities + i + 5, Drawable("lock", Drawable::SPRITE, {0.1, 0.1}, {0, 0, 512, 512}, 0));
        }
        while (i < 5) {
            Entity roomEntity = rOnline.spawn_entity();
            positions.insert_at(nbEntities + i, Position(9999, 9999));
            drawables.insert_at(nbEntities + i,
                Drawable("robotoTTF", Drawable::BUTTON, {1, 1}, "", 25, {0, 0, 0}, {102, 153, 153}, {300, 40}, 0));
            Buttons::RoomButton_t *roomdButton = _buttons.setRoomButton(i + nbEntities, true);
            clickable.insert_at(nbEntities + i, Clickable([this](std::size_t idx) { _buttons.selectRoomButton(idx); },
                                                    nbEntities + i, roomdButton, Clickable::ROOMBUTTON));
            Entity lockEntity = rOnline.spawn_entity();
            positions.insert_at(nbEntities + i + 5, Position(9999, 9999));
            drawables.insert_at(
                nbEntities + i + 5, Drawable("lock", Drawable::SPRITE, {0.07, 0.07}, {0, 0, 512, 512}, 0));
            i++;
        }
        _world->setNbEntitiesOnline(nbEntities + i);
    }
    if (_roomsPage != nbPage.second || nbRoom != _nbRooms) {
        _roomsPage = nbPage.second;
        _nbRooms = nbRoom;
        for (i = 0; i < sizeRoomList && i < 5; i++) {
            positions.insert_at(nbPage.first + i, Position(960, 60 * i + 150));
            if (_world->getRoomName() != "" && _world->getRoomIndex() == std::get<0>(rooms.at(i + nbPage.second)))
                drawables.insert_at(nbPage.first + i,
                    Drawable("robotoTTF", Drawable::BUTTON, {1, 1}, std::get<4>(rooms.at(i + nbPage.second)), 25,
                        {0, 0, 0}, {51, 204, 51}, {300, 40}, 0));
            else
                drawables.insert_at(nbPage.first + i,
                    Drawable("robotoTTF", Drawable::BUTTON, {1, 1}, std::get<4>(rooms.at(i + nbPage.second)), 25,
                        {0, 0, 0}, {102, 153, 153}, {300, 40}, 0));
            Buttons::RoomButton_t *roomdButton =
                _buttons.setRoomButton(nbPage.first + i, std::get<1>(rooms.at(i + _roomsPage)));
            clickable.insert_at(nbPage.first + i, Clickable([this](std::size_t idx) { _buttons.selectRoomButton(idx); },
                                                      nbPage.first + i, roomdButton, Clickable::ROOMBUTTON));
            if (!std::get<1>(rooms.at(i + nbPage.second))) {
                positions.insert_at(nbPage.first + i + 5, Position(1070, 60 * i + 150));
            } else {
                positions.insert_at(nbPage.first + i + 5, Position(9999, 9999));
            }
            drawables.insert_at(
                nbPage.first + i + 5, Drawable("lock", Drawable::SPRITE, {0.07, 0.07}, {0, 0, 512, 512}, 0));
        }
        while (i < 5) {
            positions.insert_at(nbPage.first + i, Position(9999, 9999));
            positions.insert_at(nbPage.first + i + 5, Position(9999, 9999));
            i++;
        }
    }
}

void Game::moveCreateRoomPasswordButtonAway(std::size_t index)
{
    ComponentArray<Position> &positions = _world->getRegistry().get_components<Position>();
    ComponentArray<Drawable> &drawables = _world->getRegistry().get_components<Drawable>();

    if (_world->getTextWritting() == (int)index) {
        _world->setTextWritting((int)(-1));
    }
    if (drawables[index]) {
        drawables[index]->setMessage("");
    }
    if (positions[index]) {
        positions[index]->setPosition({9999, 9999});
    }
}

void Game::moveCreateRoomPasswordButtonBack(std::size_t index)
{
    ComponentArray<Position> &positions = _world->getRegistry().get_components<Position>();

    if (positions[index]) {
        positions[index]->setPosition(960, 350);
    }
}

// int Game::print_message_box(std::string title, std::string message)
//{
//     const SDL_MessageBoxButtonData buttons[] = {
//         { 1, 0, "no" },
//         { 1, 1, "yes" },
//     };
//     const SDL_MessageBoxColorScheme colorScheme = {
//         {
//             /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
//             { 5, 5, 5},
//             /* [SDL_MESSAGEBOX_COLOR_TEXT] */
//             { 250, 250, 250},
//             /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
//             { 25, 25, 25},
//             /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
//             { 128, 128, 128},
//             /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
//             { 0, 0, 255}
//         }
//     };
//     const SDL_MessageBoxData messageBoxData = {
//         SDL_MESSAGEBOX_INFORMATION, /* .flags */
//         NULL, /* .window */
//         title.c_str(), /* .title */
//         message.c_str(), /* message */
//         SDL_arraysize(buttons), /* .numbuttons */
//         buttons, /* .buttons */
//         &colorScheme /* .colorScheme */
//     };
//     int buttonid;
//     SDL_ShowMessageBox(&messageBoxData, &buttonid);
//     return(buttonid);
// }*/
