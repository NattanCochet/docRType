# How to add content

## Ennemies

To create a new ennemy you'll need to follow these steps :

- Creating a [ABot](./classABot.html) child class

- Choosing the sprite sheet of the ennemy

- Adding the entity

### Child class

Go to the folder `server/Logic/include/Components/Bots/` then create a file named as you want here it will be newShooter.hpp

```cpp

#include "../ABot.hpp"

#ifndef NEWSHOOTER_HPP_
#define NEWSHOOTER_HPP_

class NewShooter : public ABot {
    public:
        NewShooter();
        ~NewShooter();

    protected:
    private:
};

#endif /* !NEWSHOOTER_HPP_ */

```

When done correctly it should look like this.

When inhereting from the [ABot](./classABot.html) class you get two members by default :

- _clock which is a clock that tracks the bots actions such as when it shoots, etc...
- _delay which is a float that tells how much time before it shoots

You can add as many members as you see fit, **don't forget to initialize the setters/getters methods if you add any private members**.

```cpp
#include "../ABot.hpp"

#ifndef NEWSHOOTER_HPP_
#define NEWSHOOTER_HPP_

class NewShooter : public ABot {
    public:
        NewShooter(float delay);
        ~NewShooter();

    private:
};

#endif /* !NEWSHOOTER_HPP_ */
```

Here's a very simple implementation of the class

Now you'll need to make the cpp file to make all the methods you need :

```cpp
#include "../../../include/Components/Bots/NewShooter.hpp"

NewShooter::NewShooter(float delay)
{
    _delay = delay;
}

NewShooter::~NewShooter()
{
}
```

Once done, we can make the **system** that will edit these values and make the ennemy's behaviour.

Create a new cpp file in `server/Logic/src/Systems/` and add its declaration to the `server/Logic/include/Systems.hpp` file

```cpp
    /**
    * @brief A system that processes a new shooter for tutorial purposes.
    *
    * This system is responsible for creating an ennemy that teleports randomly on the screen
    *
    * @param world A reference to the World object containing the entities to update.
    * @return An integer indicating the success or status of the system.
    */
    static int NewShooterSystem(World &world);
```

Make sure to include the NewShooter component in the `server/Logic/include/ECS/World.hpp` file and to add it to the register in `server/Logic/src/ECS/World.cpp`

```cpp
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
    this->_r.register_components<NewShooter>(); // THIS LINE RIGHT HERE
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
    this->_r.register_components<NewShooter>(); // THIS LINE RIGHT HERE
}
```

After that you can finally make the system

```cpp
#include "../../include/Systems.hpp"

#include <boost/random.hpp>

int Systems::NewShooterSystem(World &world)
{
    static boost::random::mt19937 rng;
    static boost::random::uniform_int_distribution<> x_dist(20, 900);
    static boost::random::uniform_int_distribution<> y_dist(20, 700);

    auto &r = world.getRegistry();
    ComponentArray<Position> &position = r.get_components<Position>();
    ComponentArray<NewShooter> &new_shooters = r.get_components<NewShooter>();

    std::size_t index = 0;

    if (position.size() != 0 && new_shooters.size() != 0) {
        for (auto &ns : new_shooters) {
            if (ns && ns.has_value()
                && position[index] && position[index].has_value()
            ) {
                auto &posAct = position[index];
                sf::Vector2f &coordsAct = posAct->getPosition();
                sf::Clock &clockAct = ns->getClock();

                if (clockAct.getElapsedTime().asSeconds() >= ns->getDelay()) {
                    auto laser = r.spawn_entity();
                    r.add_component(laser, Velocity(sf::Vector2i(-9, 0), 0.0, 0.0));
                    r.add_component(laser, Position(coordsAct.x, coordsAct.y));
                    r.add_component(laser, Projectile(20.0f, 0.6f, false, false, 0.0f, 0.4f));
                    int new_x = x_dist(rng);
                    int new_y = y_dist(rng);
                    posAct->setPosition(new_x, new_y);
                    clockAct.restart();
                }
            }
            index++;
        }
    }
    return 0;
}
```

Here's a system that handles an ennemy that teleports on the screen randomly after a delay

### Choosing a sprite sheet

To do that download the sprite sheet you want, just make sure that **all the frames are displayed honrizontally**

Once done put it in the `server/Logic/assets` folder

### Adding the entity

Add the entity to the world and voila you got your new ennemy!
