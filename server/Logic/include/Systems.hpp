/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Systems
*/

#pragma once

#ifndef SYSTEMS_HPP_
#define SYSTEMS_HPP_
#include "ECS/World.hpp"
#include "ECS/ComponentArray.hpp"
#include "ECS/Registry.hpp"
#include "Components/Vitality.hpp"
#include "Components/Position.hpp"
#include "Components/Velocity.hpp"
#include "Components/Hitbox.hpp"
#include "Components/Clock.hpp"
#include "GJKAlgorithm.hpp"

/**
 * @class Systems
 * @brief A class that contains all the systems for managing game logic related to entities in the ECS architecture.
 *
 * This class handles various game systems like vitality, velocity, damage, controllable input, hitbox collision, and drawable entities.
 * Each system is responsible for updating or processing certain components associated with entities in the world.
 */
class Systems {
    public:
        /**
         * @brief Constructor for the Systems class.
         *
         * Initializes any necessary variables or state for the systems.
         */
        Systems();

        /**
         * @brief Destructor for the Systems class.
         *
         * Cleans up any resources allocated during the lifetime of the class.
         */
        ~Systems();

        /**
         * @brief Loads all systems into the world.
         *
         * This method registers all available systems into the world, allowing them to be executed during the game loop.
         *
         * @param world A reference to the World object to load the systems into.
         */
        void loadSystemsInWorld(World &world);

        /**
         * @brief A system that processes the vitality components of entities.
         *
         * This system is responsible for updating and managing the vitality (health) of entities.
         *
         * @param world A reference to the World object containing the entities to update.
         * @return An integer indicating the success or status of the system (typically 0 for success).
         */
        static int vitalitySystem(World &world);

        /**
         * @brief A system that processes the velocity components of entities.
         *
         * This system is responsible for updating the velocity and position of entities based on their current velocity.
         *
         * @param world A reference to the World object containing the entities to update.
         * @return An integer indicating the success or status of the system.
         */
        static int velocitySystem(World &world);

        /**
         * @brief A system that handles damage calculations and application to entities.
         *
         * This system is responsible for applying damage to entities based on collisions or events.
         *
         * @param world A reference to the World object containing the entities to update.
         * @return An integer indicating the success or status of the system.
         */
        static int damageSystem(World &world);

        /**
         * @brief A system that processes controllable components for player input.
         *
         * This system updates entities that can be controlled by the player, like moving or rotating entities based on input.
         *
         * @param world A reference to the World object containing the entities to update.
         * @return An integer indicating the success or status of the system.
         */
        static int controllableSystem(World &world);

        /**
         * @brief A system that processes the hitbox components for entities.
         *
         * This system handles the detection and processing of hitbox interactions, such as collisions.
         *
         * @param world A reference to the World object containing the entities to update.
         * @return An integer indicating the success or status of the system.
         */
        static int hitboxSystem(World &world);

        /**
         * @brief A system that processes the linear motion of entities, like movement or shooting.
         *
         * This system updates entities' positions or actions along a linear trajectory.
         *
         * @param world A reference to the World object containing the entities to update.
         * @return An integer indicating the success or status of the system.
         */
        static int linearSystem(World &world);

        /**
         * @brief A system that processes drawable entities for rendering.
         *
         * This system is responsible for updating or managing the graphical representations of entities to be rendered on screen.
         *
         * @param world A reference to the World object containing the entities to update.
         * @return An integer indicating the success or status of the system.
         */
        static int drawableSystem(World &world);

        /**
         * @brief A system that processes projectile and its collisions.
         *
         * This system is responsible for checking collisions between a projectile and an entity
         *
         * @param world A reference to the World object containing the entities to update.
         * @return An integer indicating the success or status of the system.
         */
        static int ProjectileSystem(World &world);

    private:
        /**
         * @brief A helper function that moves a controllable player based on keyboard input.
         *
         * This function updates the player's position based on the current keyboard input and the entity's hitbox.
         *
         * @param pos The current position of the player.
         * @param hitbox The hitbox of the player entity.
         * @param keyboard The current state of the virtual keyboard.
         * @param clock The clock to avoid player to move too fast
         */
        static void movePlayerFromControllable(sf::Vector2f &pos, const Hitbox &hitbox, VirtualKeyBoard &keyboard, Clock &clock);

        /**
         * @brief A helper function that calculates collisions between hitboxes using the GJK algorithm.
         *
         * This function checks for collisions between multiple hitboxes in the world.
         *
         * @param hitboxs A reference to the array of hitboxes.
         * @param indexToAnalyse The index of the hitbox to analyze.
         * @param algoCollision The GJK collision algorithm instance to perform the collision check.
         * @return A vector of pairs, each containing an index and an array of collision states.
         */
        static std::vector<std::pair<std::size_t, std::array<bool, 8>>> calculateCollision(ComponentArray<Hitbox> &hitboxs, std::size_t &indexToAnalyse, GJKAlgorithm &algoCollision);

        /**
         * @brief A function that handles player input for projectile shooting
         *
         * @param r A reference to the Registry object containing the entities to update.
         * @param keyboard A reference to the keyboard to the client to know if the user is pressed a key
         * @param currentPosition The position of the player to create a projectile at his position
         * @param clocks The clocks to know when the player is available to shoot and if the player shoot a laser or a beam
         *
         */
        static void shootHandling(Registry &r, VirtualKeyBoard &keyboard, Position &currentPosition, Clock &clocks);
};

#endif /* !SYSTEMS_HPP_ */
