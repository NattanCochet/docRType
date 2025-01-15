# How to add content

## Ennemies

To create a new ennemy you'll need to follow these steps :

- Creating a [ABot](../html/classABot.html) child class

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

When inhereting from the [ABot](../html/classABot.html) class you get two members by default :

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

        /**
         * @brief Shoots a projectile in the world.
         * @param world Reference to the game world.
         * @param myIndexEntity Index of this entity in the world.
         */
        void shootProjectile(World &world, std::size_t myIndexEntity) override
        {
            return;
        }

        /**
         * @brief Moves the bot within the world.
         * @param world Reference to the game world.
         * @param myIndexEntity Index of this entity in the world.
         */
        void moveBot(World &world, std::size_t myIndexEntity) override
        {
            return;
        }

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

Create a new cpp file in `server/Logic/src/Systems/` and add its include path to the `server/Logic/World.hpp` file

You're free to write the `moveBot` and `shootProjectile` as you see fit.

### Choosing a sprite sheet

To do that download the sprite sheet you want.

Once done put it in the `server/Logic/assets` folder

### Adding the entity

Add the entity to the world and voila you got your new ennemy!
