/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** World
*/

#include "../../include/ECS/World.hpp"

World::World(
bool isClient, bool isPublic, int nbrPlayerMax, std::string nameRoom,
std::size_t clientID, std::string password)
{
    _isClient = isClient;
    _isPublic = isPublic;
    _nbrPlayerMax = nbrPlayerMax;
    _nameRoom = nameRoom;
    _idClients.push_back(clientID);
    _password = password;
    _maxLevel = 0;
    _r = Registry();
    _gw = GenerateWorld();
    _srg = SpawnRuleGenerator();
    this->addEntityInWroldSpawnRuleGenerator();
    this->_r.register_components<Position>();
    this->_r.register_components<Velocity>();
    this->_r.register_components<Vitality>();
    this->_r.register_components<Projectile>();
    this->_r.register_components<Controllable>();
    this->_r.register_components<LinearShooter>();
    this->_r.register_components<Hitbox>();
    this->_r.register_components<Drawable>();
    this->_r.register_components<Clock>();
}

World::World()
{
    _isClient = false;
    _isClient = false;
    _isPublic = false;
    _nbrPlayerMax = 1;
    _nameRoom = "Unknown";
    _password = "0000";
    _maxLevel = 0;
    _r = Registry();
    _gw = GenerateWorld();
    _srg = SpawnRuleGenerator();
    this->addEntityInWroldSpawnRuleGenerator();
    this->_r.register_components<Position>();
    this->_r.register_components<Velocity>();
    this->_r.register_components<Vitality>();
    this->_r.register_components<Projectile>();
    this->_r.register_components<Controllable>();
    this->_r.register_components<LinearShooter>();
    this->_r.register_components<Hitbox>();
    this->_r.register_components<Drawable>();
    this->_r.register_components<Clock>();
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

std::string World::getNameOfWorld() const noexcept
{
    return (_nameRoom);
}

void World::changeParametersOfWorld(
bool client, bool isPublic, int nbrPlayerMax, std::string nameRoom, std::string password
) noexcept
{
    _isClient = client;
    _isPublic = isPublic;
    _nbrPlayerMax = nbrPlayerMax;
    _nameRoom = nameRoom;
    _password = password;
}

std::vector<std::size_t> World::getClientsID() const noexcept
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
        throw (ErrorClientAlreadyPresentInWorld(clientID));
    }
    _idClients.push_back(clientID);
    return (_idClients.size());
}

/*
    @return The ClientID deleted
    @throw When clientID is not in vector
*/
std::size_t World::deleteClientInWorld(std::size_t clientID)
{
    int index = this->getClientIDPresenceAsInt(clientID);
    std::size_t clientIDDeleted = 0;
    if (index < 0) {
        throw ErrorVector("ClientID " + std::to_string(clientID) + " not found.");
    }
    clientIDDeleted = _idClients[index];
    _idClients.erase(_idClients.begin() + index);
    return (clientIDDeleted);
}

bool World::isClientIDPresentAsBool(std::size_t clientID) noexcept
{
    for (std::size_t idClient : _idClients) {
        if (idClient == clientID) {
            return (true);
        }
    }
    return (false);
}

int World::getClientIDPresenceAsInt(std::size_t clientID) noexcept
{
    std::size_t index = 0;
    for (std::size_t idClient : _idClients) {
        if (idClient == clientID) {
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

void World::changeValueOfKeyPerClientID(std::size_t clienID, VirtualKeyBoard::CONTROL key, bool isPressed)
{
    if (!this->isClientIDPresentAsBool(clienID)) {
        throw ErrorKeyNotFound(std::to_string(clienID), "World::changeValueOfKeyPerClientID");
    }
    _virtualKeyBoardPerClientID[clienID].changeValueKeyboard(key, isPressed);
}

void World::changeValueOfKeyPerClientID(std::tuple<std::size_t, VirtualKeyBoard::CONTROL, bool> action)
{
    std::size_t clientID = std::get<0>(action);
    if (!this->isClientIDPresentAsBool(clientID)) {
        throw ErrorKeyNotFound(std::to_string(clientID), "World::changeValueOfKeyPerClientID");
    }
    _virtualKeyBoardPerClientID[clientID].changeValueKeyboard(std::get<1>(action), std::get<2>(action));
}

VirtualKeyBoard &World::getVirtualKeyBoardFromClientID(std::size_t clientID)
{
    if (!this->isClientIDPresentAsBool(clientID)) {
        throw ErrorKeyNotFound(std::to_string(clientID), "World::getVirtualKeyBoardFromClientID");
    }
    return (_virtualKeyBoardPerClientID[clientID]);
}

std::unordered_map<std::size_t, VirtualKeyBoard> &World::getVirtualKeyBoard() noexcept
{
    return (_virtualKeyBoardPerClientID);
}

void World::generateNextSeedForNextLevel()
{
    std::random_device rd;

    std::mt19937_64 generator(rd());

    std::uniform_int_distribution<std::size_t> distribution(0, std::numeric_limits<std::size_t>::max());

    std::size_t randomValue = distribution(generator);
    _seedByLevel[_maxLevel] = randomValue;

    _maxLevel += 1;

    //SEED test -> 5460082509066555437
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

std::vector<std::vector<int>> World::generateWorldWithID(
        std::size_t level,
        std::pair<float, float> &beginAndEndGenerationInX,
        std::pair<float, float> &beginAndEndGenerationInY
    )
{
    std::size_t seed = this->getSeedForLevel(level);
    std::function<int(float)> funtPerLevel = _srg.createFunctionForRuleWithID(level);
    return (_gw.generateWorld<int>(beginAndEndGenerationInX, beginAndEndGenerationInY, seed, funtPerLevel));
}

std::vector<std::vector<int>> World::generateWorldWithID(
        std::size_t level,
        std::pair<int, int> &beginAndEndGenerationInX,
        std::pair<int, int> &beginAndEndGenerationInY
    )
{
    std::size_t seed = this->getSeedForLevel(level);
    std::function<int(float)> funtPerLevel = _srg.createFunctionForRuleWithID(level);
    return (_gw.generateWorld<int>(beginAndEndGenerationInX, beginAndEndGenerationInY, seed, funtPerLevel));
}

std::vector<std::vector<SpawnRuleGenerator::ENTITIES>> World::generateWorldWithEnum(
    std::size_t level,
    std::pair<int, int> &beginAndEndGenerationInX,
    std::pair<int, int> &beginAndEndGenerationInY
)
{
    std::size_t seed = this->getSeedForLevel(level);
    std::function<SpawnRuleGenerator::ENTITIES(float)> funtPerLevel = _srg.createFunctionForRuleWithEnum(level);
    return (_gw.generateWorld<SpawnRuleGenerator::ENTITIES>(beginAndEndGenerationInX, beginAndEndGenerationInY, seed, funtPerLevel));
}

std::vector<std::vector<SpawnRuleGenerator::ENTITIES>> World::generateWorldWithEnum(
    std::size_t level,
    std::pair<float, float> &beginAndEndGenerationInX,
    std::pair<float, float> &beginAndEndGenerationInY
)
{
    std::size_t seed = this->getSeedForLevel(level);
    std::function<SpawnRuleGenerator::ENTITIES(float)> funtPerLevel = _srg.createFunctionForRuleWithEnum(level);
    return (_gw.generateWorld<SpawnRuleGenerator::ENTITIES>(beginAndEndGenerationInX, beginAndEndGenerationInY, seed, funtPerLevel));
}

void World::addEntityInWroldSpawnRuleGenerator()
{
    _srg.addEntity(0, -0.2f, 0.0f, 0.0f);
    _srg.addEntity(1, 0.3f, 0.02f, 0.2f);
    _srg.addEntity(2, 0.4f, 0.02f, 0.02f);
    _srg.addEntity(3, 0.3f, 0.04f, 0.03f, 2);
}

std::list<std::tuple<std::string, float, float, float, float, float>> World::getInformationOfEachEntity()
{
    ComponentArray<Position> &positions = _r.get_components<Position>();
    ComponentArray<Drawable> &drawables = _r.get_components<Drawable>();

    std::list<std::tuple<std::string, float, float, float, float, float>> result;

    std::size_t index = 0;

    for (std::optional<Position> position : positions) {
        if (position && position.has_value()) {
            if (drawables[index] && drawables[index].has_value()) {
                result.push_back(std::make_tuple(
                    drawables[index]->getPath(),
                    position->getPosition().x,
                    position->getPosition().y,
                    drawables[index]->getRect()[0],
                    drawables[index]->getRect()[1],
                    0 // rotation a changer peut-etre
                ));
            }
        }
        index += 1;
    }
    return (result);
}
