/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Systems
*/

#pragma once

#ifndef SYSTEMS_HPP_
#define SYSTEMS_HPP_
#include <optional>
#include "ECS/World.hpp"
#include "ECS/CreateEntity.hpp"
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
         * @brief A system that processes drawable entities for rendering.
         *
         * This system is responsible for updating or managing the graphical representations of entities to be rendered on screen.
         *
         * @param world A reference to the World object containing the entities to update.
         * @return An integer indicating the success or status of the system.
         */
        static int drawableSystem(World &world);

        /**
         * @brief A system that processes projectiles and their collisions.
         *
         * This system is responsible for checking collisions between a projectile and an entity.
         *
         * @param world A reference to the World object containing the entities to update.
         * @return An integer indicating the success or status of the system.
         */
        static int ProjectileSystem(World &world);

        /**
         * @brief A system that destroys entities when too far away from the game screen.
         *
         * This system is responsible for deleting entities to avoid entity overflow.
         *
         * @param world A reference to the World object containing the entities to update.
         * @return An integer indicating the success or status of the system.
         */
        static int positionSystem(World &world);

        /**
         * @brief A system that checks if the player has won the game.
         *
         * This system checks the game conditions for victory and updates the world accordingly.
         *
         * @param world A reference to the World object containing the entities to update.
         * @return An integer indicating the success or status of the system.
         */
        static int winSystem(World &world);

        /**
         * @brief A system that checks if the player has lost the game.
         *
         * This system checks the game conditions for failure and updates the world accordingly.
         *
         * @param world A reference to the World object containing the entities to update.
         * @return An integer indicating the success or status of the system.
         */
        static int looseSystem(World &world);

        /**
         * @brief A system responsible for spawning entities.
         *
         * This system handles the spawning of new entities into the world based on certain conditions or events.
         *
         * @param world A reference to the World object containing the entities to update.
         * @return An integer indicating the success or status of the system.
         */
        static int spawnSystem(World &world);

        /**
         * @brief A system that processes enemy behaviors and actions.
         *
         * This system is responsible for updating enemy entities in the game.
         *
         * @param world A reference to the World object containing the entities to update.
         * @return An integer indicating the success or status of the system.
         */
        static int ennemySystem(World &world);

        /**
         * @brief A system that handles spawning of entities after their death.
         *
         * This system ensures that after a death event, new entities are created, keeping the game flow intact.
         *
         * @param world A reference to the World object containing the entities to update.
         * @return An integer indicating the success or status of the system.
         */
        static int spawnAfterDeadSystem(World &world);

        /**
         * @brief A system that processes the force components for entities.
         *
         * This system is responsible for updating the forces acting on entities, affecting their movement or behavior.
         *
         * @param world A reference to the World object containing the entities to update.
         * @return An integer indicating the success or status of the system.
         */
        static int forceSystem(World &world);

        /**
         * @brief A system that processes area components for entities.
         *
         * This system is responsible for managing areas of influence or effect, such as power-ups or environmental hazards.
         *
         * @param world A reference to the World object containing the entities to update.
         * @return An integer indicating the success or status of the system.
         */
        static int areaSystem(World &world);


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
         * @param sizeWindow The pair including the size of the window (width, height)
         */
        static void movePlayerFromControllable(sf::Vector2f &pos, const Hitbox &hitbox, VirtualKeyBoard &keyboard, Clock &clock, const std::pair<std::size_t, std::size_t> &sizeWindow);

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
         * @brief A function that handles player input for projectile shooting.
         *
         * This function processes player input to create and shoot projectiles from the player's position,
         * depending on the player's state (e.g., if they are allowed to shoot based on cooldown).
         *
         * @param ce A reference to the class which can create entities.
         * @param r A reference to the Registry object containing the entities to update.
         * @param keyboard A reference to the keyboard to the client to know if the user has pressed a key.
         * @param currentPosition The position of the player to create a projectile at their position.
         * @param clocks The clocks to know when the player is available to shoot and if the player is shooting a laser or a beam.
         * @param index The index of the shooter (or ID).
         * @param forces A reference to the forces that may affect the projectile.
         */
        static void shootHandling(
            CreateEntity &ce, Registry &r, VirtualKeyBoard &keyboard, Position &currentPosition,
            Clock &clocks, const std::size_t &index, Force &forces
        );

        /**
         * @brief A version of shootHandling without the 'forces' parameter.
         *
         * This variant of the shootHandling function does not take the forces parameter.
         */
        static void shootHandling(
            CreateEntity &ce, Registry &r, VirtualKeyBoard &keyboard, Position &currentPosition,
            Clock &clocks, const std::size_t &index
        );

        /**
         * @brief Checks if a rectangle is within the boundaries of the window.
         *
         * This function ensures that the projectile (or any entity) stays within the window's boundaries.
         *
         * @param windowWidth The width of the window.
         * @param windowHeight The height of the window.
         * @param pos The position of the rectangle.
         * @param size The size of the rectangle.
         * @param rotation The rotation of the rectangle (used to determine the rotated bounding box).
         * @return True if the rectangle is within the window, false otherwise.
         */
        static bool isRectangleInWindow(
            const std::size_t &windowWidth, const std::size_t &windowHeight, const sf::Vector2f &pos,
            const Vector<int, 2> &size, const float &rotation
        );

        /**
         * @brief Updates the score of the player based on vitality and projectile components.
         *
         * This function updates the score based on changes in the player's vitality or projectile status.
         *
         * @param world A reference to the World object containing entities to update.
         * @param vitality An optional reference to the Vitality component of the player.
         * @param projectile An optional reference to the Projectile component.
         */
        static void attributeScore(World &world, std::optional<Vitality> &vitality, std::optional<Projectile> &projectile);

        /**
         * @brief Retrieves the direction of the controllable entity based on the keyboard input.
         *
         * This function gets the direction the player is attempting to move based on keyboard input.
         *
         * @param keyBoard A reference to the VirtualKeyBoard object to check key states.
         * @return A pair representing the direction (X, Y) the player is moving.
         */
        static const std::pair<int, int> getDirectionControllable(VirtualKeyBoard &keyBoard);

        /**
         * @brief Moves a force entity next to the player.
         *
         * This function moves a force entity to a position adjacent to the player.
         *
         * @param r A reference to the Registry object to access the forces.
         * @param index The index of the force entity.
         * @param indexBelong The index of the player to move the force next to.
         */
        static void moveForceNextToThePlayer(Registry &r, const std::size_t &index, const std::size_t &indexBelong);

        /**
         * @brief Executes a shooting action with a force applied.
         *
         * This function handles shooting behavior where a force is involved, affecting the trajectory or behavior of the shot.
         *
         * @param world A reference to the World object containing entities to update.
         * @param index The index of the shooter entity.
         * @param indexBelong The index of the entity associated with the shooting force.
         */
        static void shootWithForce(World &world, const std::size_t &index, const std::size_t &indexBelong);

        /**
         * @brief Calculates the area of influence of a controllable entity.
         *
         * This function determines the area of influence or effect that a controllable entity has.
         *
         * @param areas A reference to the ComponentArray of Area components.
         * @param indexArea The index of the area to calculate.
         */
        static void calculateArea(ComponentArray<Area> &areas, const std::size_t &indexArea);

        /**
         * @brief Handles force-related actions such as applying or moving forces.
         *
         * This function processes input related to forces, such as moving them or applying them based on player controls.
         *
         * @param keyboard A reference to the VirtualKeyBoard object for input.
         * @param clocks A reference to the Clock object for time-based actions.
         * @param areaControllable The area the player can control.
         * @param forces A reference to the array of Force components.
         * @param position A reference to the array of Position components.
         * @param idBelong The index of the entity associated with the forces.
         * @param drawable A reference to the array of Drawable components for rendering.
         */
        static void forceHandling(
            VirtualKeyBoard &keyboard, Clock &clocks, Area &areaControllable, ComponentArray<Force> &forces,
            ComponentArray<Position> &position, const std::size_t &idBelong, ComponentArray<Drawable::Drawable> &drawable
        );

        /**
         * @brief Shoots a forward force with damage applied.
         *
         * This function simulates shooting a force forward, applying damage to entities hit by the projectile.
         *
         * @param forces A reference to the array of Force components.
         * @param damage The amount of damage to apply with the force.
         */
        static void shootForwardForce(ComponentArray<Force> &forces, const float &damage);

        /**
         * @brief Equips a force to the controllable entity.
         *
         * This function associates a force with an entity that is controllable by the player, affecting their actions.
         *
         * @param areaControllable The area that the controllable entity can affect.
         * @param forces A reference to the array of Force components.
         * @param position A reference to the array of Position components.
         * @param idBelong The index of the entity to equip the force.
         * @param drawable A reference to the array of Drawable components for rendering.
         */
        static void equipedForce(
            const Area &areaControllable, ComponentArray<Force> &forces, ComponentArray<Position> &position,
            const std::size_t &idBelong, ComponentArray<Drawable::Drawable> &drawable
        );

        /**
         * @brief Checks if a force is equipped on an entity.
         *
         * This function determines whether a specific force is currently equipped on the entity.
         *
         * @param forces A reference to the array of Force components.
         * @param index The index of the entity to check.
         * @return A value indicating whether the force is equipped (typically 1 if equipped, 0 otherwise).
         */
        static int isForceEquipped(ComponentArray<Force> &forces, const std::size_t &index);

        /**
         * @brief Checks if an entity is positioned to the right of another entity.
         *
         * This function checks whether one entity is positioned to the right of another based on their respective positions.
         *
         * @param position A reference to the array of Position components.
         * @param idBelong The index of the first entity.
         * @param index The index of the second entity.
         * @param sizeForce The size of the force entity.
         * @param sizeControllable The size of the controllable entity.
         * @return True if the second entity is to the right of the first, false otherwise.
         */
        static bool isToTheRight(
            ComponentArray<Position> &position, const std::size_t &idBelong, const std::size_t &index,
            const float &sizeForce, const float &sizeControllable
        );

        /**
         * @brief Checks if an entity touches the border of the screen.
         *
         * This function checks if the entity has moved beyond the screen's boundaries or touched its edges.
         *
         * @param posX The X position of the entity.
         * @param sizeWindow The width and height of the window.
         * @param drawables A reference to the array of Drawable components.
         * @param index The index of the entity to check.
         * @return True if the entity touches the border, false otherwise.
         */
        static bool touchTheBorderScreen(
            float posX, std::pair<std::size_t, std::size_t> sizeWindow,
            ComponentArray<Drawable::Drawable> &drawables, std::size_t index
        );

};

#endif /* !SYSTEMS_HPP_ */
