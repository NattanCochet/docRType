/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** World
*/

#include "../../include/ECS/World.hpp"
#include "../../include/ECS/CreateEntity.hpp"

World::World(bool isClient, bool isPublic, int nbrPlayerMax, std::string nameRoom, std::size_t clientID,
    std::string password) : _clock(), _clockGenerationWorld(), _dist(0, 5)
{
    _stateWorld = NOTHING;
    _widthWindow = 1920;
    _heightWindow = 1080;
    _isLevelFinishedToSpawn = false;
    _isLevelFinished = false;
    _spawnAfterWindow = _widthWindow;
    _isClient = isClient;
    _isPublic = isPublic;
    _nbrPlayerMax = nbrPlayerMax;
    _nameRoom = nameRoom;
    _password = password;
    _maxLevel = 0;
    _currentLevel = 0;
    _isForceInWorld = false;
    _rng.seed(0);
    _lastSeedGenerate = 0;
    _r = Registry();
    _gw = GenerateWorld();
    _srg = SpawnRule::Generator();
    _ce = std::shared_ptr<CreateEntity>();
    this->addEntityInWorldSpawnRuleGenerator();
    this->generateNextSeedForNextLevel();
    this->_r.register_components<Position>();
    this->_r.register_components<Velocity>();
    this->_r.register_components<Vitality>();
    this->_r.register_components<Projectile>();
    this->_r.register_components<Controllable>();
    this->_r.register_components<LinearShooter>();
    this->_r.register_components<Hitbox::Hitbox>();
    this->_r.register_components<Drawable::Drawable>();
    this->_r.register_components<Clock>();
    this->_r.register_components<TpShooter>();
    this->_r.register_components<Ennemy>();
    this->_r.register_components<SpawnAfterDead>();
    this->_r.register_components<Force>();
    this->_r.register_components<Area>();
    this->_r.register_components<Bonus>();
    this->_r.register_components<PlayerAI>();
    this->addClientInWorld(clientID, password);
}

World::World() : _clock(), _clockGenerationWorld(), _dist(0, 5)
{
    _stateWorld = NOTHING;
    _widthWindow = 1920;
    _heightWindow = 1080;
    _isLevelFinishedToSpawn = false;
    _isLevelFinished = false;
    _spawnAfterWindow = _widthWindow;
    _isClient = false;
    _isClient = false;
    _isPublic = false;
    _nbrPlayerMax = 1;
    _nameRoom = "Unknown";
    _password = "0000";
    _maxLevel = 0;
    _currentLevel = 0;
    _isForceInWorld = false;
    _rng.seed(0);
    _lastSeedGenerate = 0;
    _r = Registry();
    _gw = GenerateWorld();
    _srg = SpawnRule::Generator();
    _ce = std::shared_ptr<CreateEntity>();
    this->addEntityInWorldSpawnRuleGenerator();
    this->generateNextSeedForNextLevel();
    this->_r.register_components<Position>();
    this->_r.register_components<Velocity>();
    this->_r.register_components<Vitality>();
    this->_r.register_components<Projectile>();
    this->_r.register_components<Controllable>();
    this->_r.register_components<LinearShooter>();
    this->_r.register_components<Hitbox::Hitbox>();
    this->_r.register_components<Drawable::Drawable>();
    this->_r.register_components<Clock>();
    this->_r.register_components<TpShooter>();
    this->_r.register_components<Ennemy>();
    this->_r.register_components<SpawnAfterDead>();
    this->_r.register_components<Force>();
    this->_r.register_components<Area>();
    this->_r.register_components<Bonus>();
    this->_r.register_components<PlayerAI>();
}

bool World::isWorldIsClient() const noexcept
{
    return (_isClient);
}

bool World::isWorldIsPublic() const noexcept
{
    return (_isPublic);
}

bool World::isSamePassword(std::string password) const noexcept
{
    return (password == _password);
}

bool World::isWorldFull() const noexcept
{
    return (_idClients.size() >= _nbrPlayerMax);
}

const std::size_t World::getNbrClientInWorld() const noexcept
{
    return (this->_idClients.size());
}

const std::size_t World::getNbrClientMaxInWorld() const noexcept
{
    return (this->_nbrPlayerMax);
}

std::string World::getNameOfWorld() const noexcept
{
    return (_nameRoom);
}

void World::changeParametersOfWorld(
    bool client, bool isPublic, int nbrPlayerMax, std::string nameRoom, std::string password) noexcept
{
    _isClient = client;
    _isPublic = isPublic;
    _nbrPlayerMax = nbrPlayerMax;
    _nameRoom = nameRoom;
    _password = password;
}

std::unordered_map<std::size_t, ClientInWorld> &World::getClientsID() noexcept
{
    return (_idClients);
}

/*
    @return The number of client in current World
    @throw When password is incorrect
    @throw When the world is full
*/
std::size_t World::addClientInWorld(std::size_t clientID, std::string password)
{
    if (!_isPublic) {
        if (!this->isSamePassword(password)) {
            throw ErrorPasswordIncorrect(password);
        }
    }
    if (this->isWorldFull()) {
        throw ErrorWorldFull(_nbrPlayerMax);
    }
    if (this->isClientIDPresentAsBool(clientID)) {
        throw(ErrorClientAlreadyPresentInWorld(clientID));
    }
    _idClients[clientID] = ClientInWorld(clientID);
    _idClients[clientID].setRowSkin(_idClients.size() - 1);
    _ce->createPlayer(
        sf::Vector2f(_widthWindow / 4, _heightWindow / 2), clientID, _r, _idClients[clientID].getRowSkin());
    return (_idClients.size());
}

/*
    @return The ClientID deleted
    @throw When clientID is not in vector
*/
ClientInWorld World::deleteClientInWorld(std::size_t clientID)
{
    ClientInWorld clientIDDeleted;
    if (!this->isClientIDPresentAsBool(clientID)) {
        throw ErrorVector("ClientID " + std::to_string(clientID) + " not found.");
    }
    clientIDDeleted = _idClients[clientID];
    _idClients.erase(clientID);

    std::size_t index = 0;
    ComponentArray<Controllable> &controllables = _r.get_components<Controllable>();
    for (std::optional<Controllable> &controllable : controllables) {
        if (controllable && controllable.has_value() && controllable->getClientID() == clientID) {
            _r.kill_entity(_r.entity_from_index(index));
            break;
        }
        index++;
    }

    return (clientIDDeleted);
}

bool World::isClientIDPresentAsBool(std::size_t clientID) noexcept
{
    return (this->_idClients.contains(clientID));
}

int World::getClientIDPresenceAsInt(std::size_t clientID) noexcept
{
    std::size_t index = 0;
    for (const auto &it : _idClients) {
        if (it.first == clientID) {
            break;
        }
        index += 1;
    }
    return (index == _idClients.size() ? -1 : index);
}

Registry &World::getRegistry()
{
    return (this->_r);
}

sf::Clock &World::getClock()
{
    return (this->_clock);
}

void World::changeValueOfKeyPerClientID(std::size_t clientID, VirtualKeyBoard::CONTROL key, bool isPressed)
{
    ComponentArray<Controllable> &controllables = _r.get_components<Controllable>();

    for (std::optional<Controllable> &controllable : controllables) {
        if (controllable.has_value() && controllable->getClientID() == clientID) {
            controllable->getVirtualKeyboard().changeValueKeyboard(key, isPressed);
            return;
        }
    }
}

void World::changeValueOfKeyPerClientID(std::tuple<std::size_t, VirtualKeyBoard::CONTROL, bool> action)
{
    std::size_t clientID = std::get<0>(action);
    ComponentArray<Controllable> controllables = _r.get_components<Controllable>();

    for (std::optional<Controllable> controllable : controllables) {
        if (controllable && controllable.has_value() && controllable->getClientID() == clientID) {
            controllable->getVirtualKeyboard().changeValueKeyboard(std::get<1>(action), std::get<2>(action));
            return;
        }
    }
    throw ErrorKeyNotFound(std::to_string(clientID), "World::changeValueOfKeyPerClientID");
}

void World::generateNextSeedForNextLevel()
{
    std::random_device rd;

    std::mt19937_64 generator(rd());

    std::uniform_int_distribution<std::size_t> distribution(0, std::numeric_limits<std::size_t>::max());

    std::size_t randomValue = distribution(generator);
    _seedByLevel[_maxLevel] = randomValue;

    _maxLevel += 1;

    // SEED test -> 5460082509066555437
}

std::size_t World::getMaxLevel() const noexcept
{
    return (_maxLevel);
}

std::size_t World::getSeedForLevel(const std::size_t &level)
{
    if (!_seedByLevel.contains(level)) {
        throw ErrorKeyNotFound(std::to_string(level), "World::getSeedForLevel");
    }
    return (_seedByLevel[level]);
}

std::vector<std::vector<int>> World::generateWorldWithID(std::size_t level,
    std::pair<float, float> &beginAndEndGenerationInX, std::pair<float, float> &beginAndEndGenerationInY)
{
    std::size_t seed = this->getSeedForLevel(level);
    std::function<int(float)> funtPerLevel = _srg.createFunctionForRuleWithID(level);
    return (_gw.generateWorld<int>(beginAndEndGenerationInX, beginAndEndGenerationInY, seed, funtPerLevel));
}

std::vector<std::vector<int>> World::generateWorldWithID(
    std::size_t level, std::pair<int, int> &beginAndEndGenerationInX, std::pair<int, int> &beginAndEndGenerationInY)
{
    std::size_t seed = this->getSeedForLevel(level);
    std::function<int(float)> funtPerLevel = _srg.createFunctionForRuleWithID(level);
    return (_gw.generateWorld<int>(beginAndEndGenerationInX, beginAndEndGenerationInY, seed, funtPerLevel));
}

std::vector<std::vector<SpawnRule::Generator::ENTITIES>> World::generateWorldWithEnum(
    std::size_t level, std::pair<int, int> &beginAndEndGenerationInX, std::pair<int, int> &beginAndEndGenerationInY)
{
    std::size_t seed = this->getSeedForLevel(level);
    std::function<SpawnRule::Generator::ENTITIES(float)> funtPerLevel = _srg.createFunctionForRuleWithEnum(level);
    return (_gw.generateWorld<SpawnRule::Generator::ENTITIES>(
        beginAndEndGenerationInX, beginAndEndGenerationInY, seed, funtPerLevel));
}

std::vector<std::vector<SpawnRule::Generator::ENTITIES>> World::generateWorldWithEnum(std::size_t level,
    std::pair<float, float> &beginAndEndGenerationInX, std::pair<float, float> &beginAndEndGenerationInY)
{
    std::size_t seed = this->getSeedForLevel(level);
    std::function<SpawnRule::Generator::ENTITIES(float)> funtPerLevel = _srg.createFunctionForRuleWithEnum(level);
    return (_gw.generateWorld<SpawnRule::Generator::ENTITIES>(
        beginAndEndGenerationInX, beginAndEndGenerationInY, seed, funtPerLevel));
}

void World::addEntityInWorldSpawnRuleGenerator()
{
    _srg.addEntity(0, -0.2f, 0.0f, 0.0f, 1);             ///< VOID
    _srg.addEntity(1, 0.3f, 0.0f, 0.0f, 20);             ///< DECOR
    _srg.addEntity(2, 0.4f, 0.02f, 0.1f, 27, 100);       ///< LinearShooterVertical
    _srg.addEntity(6, 0.03f, 0.02f, 0.02f, 24, 100);     ///< LinearShooterVerticalShinny
    _srg.addEntity(3, 0.3f, 0.04f, 0.03f, 34, 200, 10);  ///< LinearShooterHorizontal
    _srg.addEntity(7, 0.03f, 0.04f, 0.03f, 34, 200, 10); ///< LinearShooterHorizontalShinny
    _srg.addEntity(4, 0.32f, 0.03f, 0.03f, 36, 300, 20); ///< TPShooter
    _srg.addEntity(8, 0.04f, 0.03f, 0.03f, 36, 300, 20); ///< TPShooterShinny
    _srg.addEntity(5, 0.1f, 0.01f, 0.5f, 50, 25);        ///< SinusoidaleShooter
    _srg.addEntity(9, 0.6f, 0.01f, 0.0f, 80, 25);        ///< SinusoidaleShooterShinny
    _srg.addEntity(15, -2.0f, 0.0f, 0.0f, 0, 5000);      ///< AlienBoss
    _srg.addEntity(16, -2.0f, 0.0f, 0.0f, 0, 5000);      ///< Spacial
    _srg.addEntity(17, -2.0f, 0.0f, 0.0f, 0, 5000);      ///< Big ship
    _srg.addEntity(18, 0.2f, 0.01f, 0.2f, 90, 500, 30);  ///< KamikazeShooter
}

std::list<std::tuple<std::size_t, std::string, float, float, int, int, int, int, float>>
World::getInformationOfEachEntity()
{
    ComponentArray<Position> &positions = _r.get_components<Position>();
    ComponentArray<Drawable::Drawable> &drawables = _r.get_components<Drawable::Drawable>();

    std::list<std::tuple<std::size_t, std::string, float, float, int, int, int, int, float>> result;

    std::size_t index = 0;

    for (std::optional<Position> position : positions) {
        if (position.has_value() && index < drawables.size() && drawables[index].has_value()) {
            const Drawable::FrameRect &rect = drawables[index]->getCurrentRect();
            result.push_back(std::make_tuple(index, drawables[index]->getType(), position->getPosition().x,
                position->getPosition().y, rect._rectTop, rect._rectLeft, rect._rectWidth, rect._rectHeight, 0.0f));
        }
        index += 1;
    }
    return (result);
}

bool World::spawnEntitiesInWorld()
{
    return (this->spawnEntitiesInWorld(_currentLevel, SPAWN_AFTER_WINDOW, SIZE_WORLD));
}

bool World::spawnEntitiesInWorld(std::size_t level, std::size_t spawnAfterWindow, int sizeWorld)
{
    if (_isLevelFinishedToSpawn) {
        return (true);
    }

    std::size_t seed = this->getSeedForLevel(level);

    if (_spawnAfterWindow + spawnAfterWindow >= sizeWorld) {
        _isLevelFinishedToSpawn = true;
        spawnAfterWindow = sizeWorld - _spawnAfterWindow;
    }
    std::pair<int, int> x_axis = std::make_pair(_spawnAfterWindow, _spawnAfterWindow + spawnAfterWindow);
    std::pair<int, int> y_axis = std::make_pair(0, _heightWindow);
    std::vector<std::vector<int>> world = this->generateWorldWithID(level, x_axis, y_axis);
    _spawnAfterWindow += spawnAfterWindow;

    for (std::size_t y = 0; y < spawnAfterWindow; y++) {
        for (std::size_t x = 0; x < _heightWindow; x++) {
            SpawnRule::EntityType entity;
            try {
                entity = _srg.getEntity(world[y][x]);
            }
            catch (ErrorKeyNotFound &e) {
                std::cout << e.what() << std::endl;
                continue;
            }
            if (entity.id != 0 && _srg.hasEnoughtPlaceForEnemy(world, y, x, entity.sizeEntity)) {
                std::size_t indexNewEntityAfterDead = this->generateRandomValueForEntityAfterDead(seed);
                std::cout << "je fais spawn avec id = " << entity.id << ", avec sad = " << indexNewEntityAfterDead
                          << std::endl;
                this->spawnEntityFromGeneratedWorld(entity.id, _widthWindow + y, x, indexNewEntityAfterDead);
            }
        }
    }

    if (_isLevelFinishedToSpawn) {
        if (seed % 2 == 0) {
            _bossIDAtTheEnd = seed % 3; // pour 3 boss;
            this->spawnEntityFromGeneratedWorld(
                15 + _bossIDAtTheEnd, _widthWindow + spawnAfterWindow + 20, _heightWindow / 2);
        } else {
            _bossIDAtTheEnd = -1;
        }
    }

    return (_isLevelFinishedToSpawn);
}

std::size_t World::generateRandomValueForEntityAfterDead(std::size_t seed) noexcept
{
    if (this->_lastSeedGenerate != seed) {
        _rng.seed(seed);
        this->_lastSeedGenerate = seed;
    }

    int res = _dist(_rng);

    if (res == 0) {
        return (res);
    }
    return (res + 9);
}

void World::resetFinishedLevel(bool isWin, NetworkServer &server)
{
    this->_isLevelFinishedToSpawn = false;
    this->_isLevelFinished = false;
    this->_spawnAfterWindow = _widthWindow;
    this->_stateWorld = NOTHING;
    this->_bossIDAtTheEnd = -1;
    this->_isForceInWorld = false;
    if (isWin) {
        if (this->_currentLevel == this->_maxLevel - 1) {
            this->generateNextSeedForNextLevel();
        }
        this->_currentLevel += 1;
    }
    for (std::pair<const std::size_t, ClientInWorld> &eachClient : this->_idClients) {
        eachClient.second.saveScore();
        Message<Protocol> endMessage;
        endMessage.header.id = Protocol::SERVER_GAME_END;
        endMessage << isWin;
        endMessage << eachClient.second.getScore();
        server.SendToClient(endMessage, eachClient.first);
        eachClient.second.resetScore();
    }
}

void World::spawnEntityFromGeneratedWorld(std::size_t id, int spawnInX, int spawnInY, std::size_t idAfterDead)
{
    Entity newEntity = _r.spawn_entity();
    _r.add_component(newEntity, Position(spawnInX, spawnInY));
    sf::Vector2f pos = sf::Vector2f(static_cast<float>(spawnInX), static_cast<float>(spawnInY));
    switch (id) {
    case 1:
        _ce->createDecor(pos, _r);
        break;
    case 2:
        _ce->createLinearShooterVertical(pos, _r);
        break;
    case 3:
        _ce->createLinearShooterHorizontal(pos, _r);
        break;
    case 4:
        _ce->createTpShooter(pos, _r);
        break;
    case 5:
        _ce->createSinusoidaleShooter(pos, _r);
        break;
    case 6:
        _ce->createLinearShooterVerticalShinny(pos, _r, idAfterDead);
        break;
    case 7:
        _ce->createLinearShooterHorizontalShinny(pos, _r, idAfterDead);
        break;
    case 8:
        _ce->createTpShooterShinny(pos, _r, idAfterDead);
        break;
    case 9:
        _ce->createSinusoidaleShooterShinny(pos, _r, idAfterDead);
        break;
    case 10:
        {
            if (!this->_isForceInWorld) {
                _ce->createForce(pos, _r);
                this->_isForceInWorld = true;
            }
            break;
        }
    case 11:
        _ce->createSpeedBonus(pos, _r);
        break;
    case 12:
        _ce->createOneUpBonus(pos, _r);
        break;
    case 13:
        {
            if (this->_isForceInWorld)
                _ce->createUpgradeForceBonus(pos, _r);
            break;
        }
    case 14:
        _ce->createStarBonus(pos, _r);
        break;
    case 15:
        _ce->createAlienEmperor(sf::Vector2f(pos.x, 100), _r, id);
        break;
    case 16:
        _ce->createSpatialDustman(sf::Vector2f(pos.x, 400), _r, id);
        break;
    case 17:
        _ce->createBigShip(sf::Vector2f(pos.x, 100), _r, id);
        break;
    case 18:
        _ce->createKamikazeShooter(pos, _r);
        break;
    default:
        break;
    }
}

CreateEntity &World::getClassCreateEntity() noexcept
{
    return (*_ce);
}

const std::size_t World::getWidthWindow() const noexcept
{
    return (this->_widthWindow);
}

const std::size_t World::getHeightWindow() const noexcept
{
    return (this->_heightWindow);
}

const std::pair<std::size_t, std::size_t> World::getSizeWindow() const noexcept
{
    return (std::make_pair(this->_widthWindow, this->_heightWindow));
}

void World::setWidthWindow(const std::size_t &newWidthWindow) noexcept
{
    this->_widthWindow = newWidthWindow;
}

void World::setHeightWindow(const std::size_t &newHeightWindow) noexcept
{
    this->_heightWindow = newHeightWindow;
}

void World::setSizeWindow(const std::pair<std::size_t, std::size_t> &newSizeWindow) noexcept
{
    this->_widthWindow = newSizeWindow.first;
    this->_heightWindow = newSizeWindow.second;
}

std::size_t World::getCurrentLevel() const noexcept
{
    return (this->_currentLevel);
}

void World::setCurrentLevel(const std::size_t &newLevel) noexcept
{
    if (newLevel > _maxLevel) {
        return;
    }
    _currentLevel = newLevel;
}

void World::setStateOfTheWorld(const STATE &newState) noexcept
{
    _stateWorld = newState;
}

const World::STATE World::getStateOfTheWorld() const noexcept
{
    return (this->_stateWorld);
}

SpawnRule::Generator &World::getClassSpawnRuleGenerator() noexcept
{
    return (this->_srg);
}

const bool &World::getIsLevelFinishedToSpawn() const noexcept
{
    return (this->_isLevelFinishedToSpawn);
}

void World::setIsLevelFinishedToSpawn(const bool &newState)
{
    this->_isLevelFinishedToSpawn = newState;
}

MyClock &World::getClockGenerationWorld() noexcept
{
    return (this->_clockGenerationWorld);
}

const int World::getBossIDAtTheEnd() const noexcept
{
    return (this->_bossIDAtTheEnd);
}

const bool World::isBeginingOfSpwan() const noexcept
{
    return (_spawnAfterWindow == _widthWindow);
}

const float World::getSpawnTimeThreshold() const noexcept
{
    return (SPAWN_TIME_THRESHOLD);
}

const bool &World::getIsForceInWorld() const noexcept
{
    return (this->_isForceInWorld);
}

void World::setIsForceInWorld(const bool &newState) noexcept
{
    this->_isForceInWorld = newState;
}

const bool World::isEntityPresent(const std::size_t &entityIndex) noexcept
{
    ComponentArray<Position> &positions = _r.get_components<Position>();

    return (entityIndex < positions.size() && positions[entityIndex].has_value());
}

const bool World::isAllClientReady() noexcept
{
    for (std::pair<const std::size_t, ClientInWorld> idClient : this->_idClients) {
        if (!idClient.second.isReady()) {
            if (this->_stateWorld == STATE::PLAY) {
                this->_stateWorld = STATE::HOLD;
            } else if (this->_stateWorld != STATE::HOLD) {
                this->_stateWorld = STATE::NOTHING;
            }
            return (false);
        }
    }
    this->_stateWorld = STATE::PLAY;
    return (true);
}

void World::sendToAllClientEntityDead(
    NetworkServer &server, const std::size_t index, const bool isExploded) const noexcept
{
    for (const std::pair<const int, ClientInWorld> &client : this->_idClients) {
        Message<Protocol> entityDead;
        entityDead.header.id = Protocol::SERVER_ENTITY_DEAD;
        entityDead << index;
        entityDead << isExploded;
        server.SendToClient(entityDead, client.first);
    }
}

void World::applyFonctionInWorld(NetworkServer &server)
{
    if (_stateWorld != PLAY) {
        if (_stateWorld == HOLD) {
            _clockGenerationWorld.pause();
        } else {
            _clockGenerationWorld.restartAndPause();
        }
        return;
    }
    _clockGenerationWorld.start();
    for (const std::function<int(World &, NetworkServer &)> &func : this->_r.get_systems()) {
        func(*this, server);
    }
}
