/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** CreateEntity
*/

#ifndef CREATEENTITY_HPP_
#define CREATEENTITY_HPP_
#include <SFML/System.hpp>
#include "Registry.hpp"
#include "../Components/Position.hpp"
#include "../Components/Velocity.hpp"
#include "../Components/Vitality.hpp"
#include "../Components/Projectile.hpp"
#include "../Components/Hitbox.hpp"
#include "../Components/Drawable.hpp"
#include "../Components/Bots/LinearShooter.hpp"
#include "../Components/Bots/TpShooter.hpp"
#include "../Components/Controllable.hpp"
#include "../Components/Clock.hpp"
#include "../Components/Ennemy.hpp"

/**
 * @class CreateEntity
 * @brief Factory class for creating various in-game entities.
 * 
 * This class is responsible for generating different types of entities,
 * such as lasers, bombs, players, and shooters. It helps encapsulate 
 * the creation logic, making the code cleaner and more modular.
 */
class CreateEntity
{
    public:
        /**
         * @brief Default constructor for CreateEntity.
         */
        CreateEntity() = default;

        /**
         * @brief Default destructor for CreateEntity.
         */
        ~CreateEntity() = default;

    public:
        /**
         * @brief Creates a laser entity.
         * 
         * @param pos The position where the laser is created.
         * @param r The registry that holds the entities.
         * @param entityIDBelong The ID of the entity the laser belongs to.
         * @param inThePlayerTeam Flag indicating if the laser is from the player's team.
         * @param toTheRight Flag indicating the direction of the laser.
         * @return The created laser entity.
         */
        Entity createLaser(sf::Vector2f pos, Registry &r, const std::size_t &entityIDBelong, bool inThePlayerTeam, bool toTheRight);

        /**
         * @brief Creates a laser boss entity.
         * 
         * @param pos The position where the laser boss is created.
         * @param r The registry that holds the entities.
         * @param entityIDBelong The ID of the entity the laser boss belongs to.
         * @param damage The damage dealt by the laser boss.
         * @param velocity The velocity of the laser boss.
         * @param size The size of the laser boss.
         * @return The created laser boss entity.
         */
        Entity createLaserBoss(sf::Vector2f pos, Registry &r, const std::size_t &entityIDBelong, float damage, sf::Vector2i velocity, Vector<int, 2> size);

        /**
         * @brief Creates a bomb entity.
         * 
         * @param pos The position where the bomb is created.
         * @param r The registry that holds the entities.
         * @param entityIDBelong The ID of the entity the bomb belongs to.
         * @param isInPlayerTeam Flag indicating if the bomb belongs to the player's team.
         * @return The created bomb entity.
         */
        Entity createBomb(sf::Vector2f pos, Registry &r, const std::size_t &entityIDBelong, bool isInPlayerTeam);

        /**
         * @brief Creates a boss bomb entity.
         * 
         * @param pos The position where the boss bomb is created.
         * @param r The registry that holds the entities.
         * @param entityIDBelong The ID of the entity the boss bomb belongs to.
         * @return The created boss bomb entity.
         */
        Entity createBossBomb(sf::Vector2f pos, Registry &r, const std::size_t &entityIDBelong);

        /**
         * @brief Creates a beam entity.
         * 
         * @param pos The position where the beam is created.
         * @param r The registry that holds the entities.
         * @param damageDependHolding The damage of the beam depending on how long it is held.
         * @param entityIDBelong The ID of the entity the beam belongs to.
         * @param toTheRight Flag indicating the direction of the beam.
         * @param isInPlayerTeam Flag indicating if the beam belongs to the player's team.
         * @return The created beam entity.
         */
        Entity createBeam(sf::Vector2f pos, Registry &r, float damageDependHolding, const std::size_t &entityIDBelong, bool toTheRight, bool isInPlayerTeam);

        /**
         * @brief Creates a kamikaze entity.
         * 
         * @param pos The position where the kamikaze is created.
         * @param r The registry that holds the entities.
         * @param damage The damage dealt by the kamikaze.
         * @param entityIDBelong The ID of the entity the kamikaze belongs to.
         * @param toTheRight Flag indicating the direction of the kamikaze.
         * @return The created kamikaze entity.
         */
        Entity createKamikaze(sf::Vector2f pos, Registry &r, float damage, const std::size_t &entityIDBelong, bool toTheRight);

        /**
         * @brief Creates a decorative entity.
         * 
         * @param pos The position where the decorative entity is created.
         * @param r The registry that holds the entities.
         * @return The created decorative entity.
         */
        Entity createDecor(sf::Vector2f pos, Registry &r);

        /**
         * @brief Creates a player entity.
         * 
         * @param pos The position where the player is created.
         * @param clientID The client ID of the player.
         * @param r The registry that holds the entities.
         * @return The created player entity.
         */
        Entity createPlayer(sf::Vector2f pos, std::size_t clientID, Registry &r);

        /**
         * @brief Creates a linear shooter entity (horizontal).
         * 
         * @param pos The position where the linear shooter is created.
         * @param r The registry that holds the entities.
         * @return The created linear shooter entity (horizontal).
         */
        Entity createLinearShooterHorizontal(sf::Vector2f pos, Registry &r);

        /**
         * @brief Creates a shiny linear shooter entity (horizontal).
         * 
         * @param pos The position where the shiny linear shooter is created.
         * @param r The registry that holds the entities.
         * @param idAfterDead The ID of the entity after it dies.
         * @return The created shiny linear shooter entity (horizontal).
         */
        Entity createLinearShooterHorizontalShinny(sf::Vector2f pos, Registry &r, std::size_t idAfterDead);

        /**
         * @brief Creates a linear shooter entity (vertical).
         * 
         * @param pos The position where the linear shooter is created.
         * @param r The registry that holds the entities.
         * @return The created linear shooter entity (vertical).
         */
        Entity createLinearShooterVertical(sf::Vector2f pos, Registry &r);

        /**
         * @brief Creates a shiny linear shooter entity (vertical).
         * 
         * @param pos The position where the shiny linear shooter is created.
         * @param r The registry that holds the entities.
         * @param idAfterDead The ID of the entity after it dies.
         * @return The created shiny linear shooter entity (vertical).
         */
        Entity createLinearShooterVerticalShinny(sf::Vector2f pos, Registry &r, std::size_t idAfterDead);

        /**
         * @brief Creates a teleporting shooter entity.
         * 
         * @param pos The position where the teleporting shooter is created.
         * @param r The registry that holds the entities.
         * @return The created teleporting shooter entity.
         */
        Entity createTpShooter(sf::Vector2f pos, Registry &r);

        /**
         * @brief Creates a shiny teleporting shooter entity.
         * 
         * @param pos The position where the shiny teleporting shooter is created.
         * @param r The registry that holds the entities.
         * @param idAfterDead The ID of the entity after it dies.
         * @return The created shiny teleporting shooter entity.
         */
        Entity createTpShooterShinny(sf::Vector2f pos, Registry &r, std::size_t idAfterDead);

        /**
         * @brief Creates a sinusoidal shooter entity.
         * 
         * @param pos The position where the sinusoidal shooter is created.
         * @param r The registry that holds the entities.
         * @return The created sinusoidal shooter entity.
         */
        Entity createSinusoidaleShooter(sf::Vector2f pos, Registry &r);

        /**
         * @brief Creates a shiny sinusoidal shooter entity.
         * 
         * @param pos The position where the shiny sinusoidal shooter is created.
         * @param r The registry that holds the entities.
         * @param idAfterDead The ID of the entity after it dies.
         * @return The created shiny sinusoidal shooter entity.
         */
        Entity createSinusoidaleShooterShinny(sf::Vector2f pos, Registry &r, std::size_t idAfterDead);

        /**
         * @brief Creates a force entity.
         * 
         * @param pos The position where the force is created.
         * @param r The registry that holds the entities.
         * @return The created force entity.
         */
        Entity createForce(sf::Vector2f pos, Registry &r);
};

#endif /* !CREATEENTITY_HPP_ */
