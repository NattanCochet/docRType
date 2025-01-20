/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Hitbox
*/

#pragma once
#ifndef HITBOX_HPP_
#define HITBOX_HPP_
#include "../Error/ErrorKeyNotFound.hpp"
#include "../Error/ErrorNoObject.hpp"
#include "../Vector.hpp"
#include <SFML/System/Vector2.hpp>
#include <map>
#include <vector>

namespace Hitbox {
/**
 * @enum TYPE
 * @brief Represents the possible types of hitboxes.
 */
enum TYPE {
    RECTANGLE = 0, ///< A rectangular hitbox.
    CIRCULAR = 1   ///< A circular hitbox.
};

/**
 * @enum DIRECTION
 * @brief Represents the possible directions for collision detection.
 */
enum DIRECTION {
    UP = 0,         ///< Collision from the upward direction.
    UP_RIGHT = 1,   ///< Collision from the upward-right direction.
    RIGHT = 2,      ///< Collision from the right direction.
    DOWN_RIGHT = 3, ///< Collision from the downward-right direction.
    DOWN = 4,       ///< Collision from the downward direction.
    DOWN_LEFT = 5,  ///< Collision from the downward-left direction.
    LEFT = 6,       ///< Collision from the left direction.
    UP_LEFT = 7     ///< Collision from the upward-left direction.
};

/**
 * @enum TEAM
 * @brief Represents the different team belong.
 */
enum TEAM { NEITHER = 0, PLAYER = 1, ENNEMY = 2 };

class RectHitbox
{
  public:
    RectHitbox(const TYPE &type, const float &XHitbox, const float &YHitbox, const int &widthHitbox,
        const int &heightHitbox, const float &rotation, const bool &isActivate = true);
    RectHitbox(const TYPE &type, const sf::Vector2f &position, const int &widthHitbox, const int &heightHitbox,
        const float &rotation, const bool &isActivate = true);
    ~RectHitbox();

  public:
    TYPE type;
    float XHitbox;
    float YHitbox;
    int widthHitbox;
    int heightHitbox;
    float rotation;
    bool isActivate;
};

/**
 * @class Hitbox
 * @brief A class representing a hitbox for collision detection.
 *
 * This class defines a hitbox, which can be either a rectangle or a circle. It stores
 * the position, size, rotation, and collision information, and provides methods to
 * check for collisions and manage collision data.
 */
class Hitbox
{
  public:
    Hitbox(const sf::Vector2f &position, const std::vector<RectHitbox> &hitboxs, const std::size_t &idBelong,
        const TEAM &isInPlayerTeam);

    Hitbox(const float &XEntity, const float &YEntity, const std::vector<RectHitbox> &hitboxs,
        const std::size_t &idBelong, const TEAM &isInPlayerTeam);

    ~Hitbox();

    /**
     * @brief Gets the type of the hitbox.
     *
     * @return The type of the hitbox (RECTANGLE or CIRCULAR).
     */
    TYPE getType(const std::size_t &indexHitbox) const;

    /**
     * @brief Gets the position of the hitbox.
     *
     * @return The position of the hitbox as a Vector.
     */
    sf::Vector2f &getPosition() noexcept;

    /**
     * @brief Gets the position of the hitbox.
     *
     * @return The position of the hitbox as a Vector.
     */
    sf::Vector2f getPositionHitbox(const std::size_t &indexHitbox) const;

    /**
     * @brief Gets the size of the hitbox.
     *
     * @return The size (dimensions) of the hitbox as a Vector.
     */
    sf::Vector2i getSizeHitbox(const std::size_t &indexHitbox) const;

    /**
     * @brief Gets the collision information for a specific ID.
     *
     * This method returns the collision status for each of the 8 directions
     * for a given ID. The result is stored as an array of 8 booleans.
     *
     * @param id The ID for which to retrieve the collision data.
     * @return An array of 8 booleans representing the collision data for the specified ID.
     */
    std::array<bool, 8> getEightAngleCollisionByID(const std::size_t &indexHitbox, const std::size_t &id);

    /**
     * @brief Gets the rotation of the hitbox.
     *
     * @return The rotation of the hitbox in degrees.
     */
    const float &getRotation(const std::size_t &indexHitbox) const;

    RectHitbox &getDataOfHitbox(const std::size_t &indexHitbox);

    /**
     * @brief Checks if the hitbox is friendly
     *
     * @return 1 the hitbox is friendly, 2 not or -1 if neither
     */
    const TEAM &getTeam() const noexcept;

    /**
     * @brief Gets linked entity ID
     *
     * @return Linked entity ID
     */
    const std::size_t &getEntityID() const noexcept;

    /**
     * @brief Sets the type of the hitbox.
     *
     * @param newType The new type to set (RECTANGLE or CIRCULAR).
     */
    void setType(const std::size_t &indexHitbox, const TYPE &newType);

    /**
     * @brief Sets the position of the hitbox.
     *
     * @param newPosition The new position to set as a Vector.
     */
    void setPosition(const sf::Vector2f &newPosition) noexcept;

    /**
     * @brief Sets the position of the hitbox with integer coordinates.
     *
     * @param newXPosition The new X-coordinate to set.
     * @param newYPosition The new Y-coordinate to set.
     */
    void setPosition(const float &newXPosition, const float &newYPosition) noexcept;

    /**
     * @brief Sets the position of the hitbox.
     *
     * @param newPosition The new position to set as a Vector.
     */
    void setPositionHitbox(const std::size_t indexHitbox, const sf::Vector2f &newPosition);

    /**
     * @brief Sets the position of the hitbox with integer coordinates.
     *
     * @param newXPosition The new X-coordinate to set.
     * @param newYPosition The new Y-coordinate to set.
     */
    void setPositionHitbox(const std::size_t &indexHitbox, const float &newXPosition, const float &newYPosition);

    /**
     * @brief Sets the size of the hitbox.
     *
     * @param newSize The new size (dimensions) to set as a Vector.
     */
    void setSizeHitbox(const std::size_t &indexHitbox, const sf::Vector2i &newSize);

    /**
     * @brief Sets the size of the hitbox with integer dimensions.
     *
     * @param newXSize The new X-dimension to set.
     * @param newYSize The new Y-dimension to set.
     */
    void setSizeHitbox(const std::size_t &indexHitbox, const int &newXSize, const int &newYSize);

    /**
     * @brief Sets the rotation of the hitbox.
     *
     * @param newRotation The new rotation to set in degrees.
     */
    void setRotationHitbox(const std::size_t &indexHitbox, const float &newRotation);

    /**
     * @brief Sets the player collaboration boolean
     *
     * @param isInPlayerTeams The new player collaboration boolean
     */
    void setTeam(const TEAM &newTeam) noexcept;

    /**
     * @brief Sets the linked entity ID
     *
     * @param newEntityID The new linked entity  ID
     */
    void setEntityID(const std::size_t &newEntityID) noexcept;

    /**
     * @brief Adds collision data for a specific ID.
     *
     * This method adds collision information (an array of booleans for each direction)
     * for a specific ID. The collision data is stored for future checks.
     *
     * @param id The ID to associate with the collision data.
     * @param collisionData The collision data to store for the specified ID.
     */
    void addCollisionWithIDAndHitbox(
        const std::size_t &indexHitbox, const std::size_t &id, const std::array<bool, 8> &collisionData);

    void resetCollisions() noexcept;

    void deleteCollisions(const std::size_t &indexHitbox, const std::size_t &id);

    /**
     * @brief Checks if there is a collision for a specific ID.
     *
     * This method checks if there is any collision data associated with the given ID.
     *
     * @param id The ID to check for collision data.
     * @return True if there is a collision with the specified ID, false otherwise.
     */
    bool isCollisionWithID(const std::size_t &id) const noexcept;

    /**
     * @brief Checks if there is a collision for a specific ID.
     *
     * This method checks if there is any collision data associated with the given ID.
     *
     * @param id The ID to check for collision data.
     * @return True if there is a collision with the specified ID, false otherwise.
     */
    bool isCollisionWithID(const std::size_t &indexHitbox, const std::size_t &id) const noexcept;

    /**
     * @brief Checks if the hitbox is in a collision state.
     *
     * This method checks if the hitbox has any collision detected.
     *
     * @return True if there is any collision, false otherwise.
     */
    bool isCollision() const noexcept;

    /**
     * @brief Checks if the hitbox is colliding in a specific direction.
     *
     * This method checks if the hitbox is colliding in a specific direction.
     *
     * @param direction The direction to check for collision.
     * @return True if the hitbox is colliding in the specified direction, false otherwise.
     */
    bool isCollisionInDirection(const DIRECTION &direction) const noexcept;

    /**
     * @brief Checks if the hitbox is colliding in a specific direction.
     *
     * This method checks if the hitbox is colliding in a specific direction.
     *
     * @param direction The direction to check for collision.
     * @return True if the hitbox is colliding in the specified direction, false otherwise.
     */
    bool isCollisionInDirection(const std::size_t &indexHitbox, const DIRECTION &direction) const noexcept;

    /**
     * @brief Checks if the hitbox is colliding with a specific ID in a specific direction.
     *
     * This method checks if the hitbox has a collision with a specific ID in a specific direction.
     *
     * @param id The ID to check for collision.
     * @param direction The direction to check for collision.
     * @return True if there is a collision with the specified ID and direction, false otherwise.
     */
    bool isCollisionWithIDInDirection(const std::size_t &id, const DIRECTION &direction) const noexcept;

    /**
     * @brief Checks if the hitbox is colliding with a specific ID in a specific direction.
     *
     * This method checks if the hitbox has a collision with a specific ID in a specific direction.
     *
     * @param id The ID to check for collision.
     * @param direction The direction to check for collision.
     * @return True if there is a collision with the specified ID and direction, false otherwise.
     */
    bool isCollisionWithIDInDirection(
        const std::size_t &indexHitbox, const std::size_t &id, const DIRECTION &direction) const noexcept;

    /**
     * This method retun all the entity ID for each collision
     *
     * @return List of all ID as vector
     */
    std::vector<std::size_t> getAllCollisionIDs() const noexcept;

    std::vector<RectHitbox> &getAllHitboxs() noexcept;

    const std::size_t &getNbrHitboxs() const noexcept;

    const bool getIsActivate(const std::size_t &indexHitbox) const;

    void setIsActivate(const std::size_t &indexHitbox, const bool &isActivate);

    const std::vector<std::size_t> getHitboxsIndexInCollisions() const noexcept;

    const std::size_t getHitboxsIndexInCollisionsWithEntityID(std::size_t entityID) const;

  private:
    sf::Vector2f _positions;
    std::vector<RectHitbox> _hitboxs;
    std::size_t _idBelong;
    TEAM _team;
    std::vector<std::map<std::size_t, std::array<bool, 8>>> _eightAnglesCollisionByIDAndHitboxs;
    std::size_t _sizeVectorHitboxs;
};
} // namespace Hitbox

#endif /* !HITBOX_HPP_ */
