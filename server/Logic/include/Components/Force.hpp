/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Force
*/

#ifndef FORCE_HPP_
#define FORCE_HPP_
#include <SFML/System/Clock.hpp>
#include <iostream>

/**
 * @class Force
 * @brief Represents a force that can be equipped, upgraded, and used in the game.
 *
 * This class handles a force's behavior, such as equipping it, upgrading its level,
 * managing shooting actions, and determining its final position and damage.
 */
class Force
{
  public:
    /**
     * @brief Constructor for the Force class.
     *
     * Initializes a Force object with a given position value (x).
     *
     * @param x The position of the force.
     */
    Force(int x);

    /**
     * @brief Destructor for the Force class.
     *
     * Cleans up any resources used by the Force object.
     */
    ~Force();

    /**
     * @brief Checks if the force is currently equipped.
     *
     * @return True if the force is equipped, false otherwise.
     */
    const bool &isEquipped() const noexcept;

    /**
     * @brief Gets the ID that belongs to the force.
     *
     * @return The ID of the force's owner.
     */
    const int &getIdBelongForce() const noexcept;

    /**
     * @brief Gets the current level of the force.
     *
     * @return The level of the force.
     */
    const std::size_t &getLevelForce() const noexcept;

    /**
     * @brief Equips the force to a new ID and determines its orientation (right or left).
     *
     * @param idBelongForce The ID that owns the force.
     * @param isToTheRight Whether the force is oriented to the right (true) or left (false).
     */
    void equipped(const std::size_t &idBelongForce, const bool &isToTheRight);

    /**
     * @brief Sets the force to shoot.
     *
     * Activates the shooting behavior for the force.
     */
    void haveToShoot() noexcept;

    /**
     * @brief Stops the force from shooting.
     *
     * Deactivates the shooting behavior for the force.
     */
    void stopShoot() noexcept;

    /**
     * @brief Checks if the force is currently set to shoot.
     *
     * @return True if the force is set to shoot, false otherwise.
     */
    const bool &getHaveIToShoot() const noexcept;

    /**
     * @brief Un-equips the force, making it no longer active.
     */
    void unEquipped() noexcept;

    /**
     * @brief Upgrades the force's level.
     *
     * Increases the force's level to improve its capabilities.
     */
    void upgrade() noexcept;

    /**
     * @brief Checks the orientation of the shooting direction.
     *
     * @return True if the force is set to shoot to the right, false otherwise.
     */
    const bool &getIsShootToTheRight() const noexcept;

    /**
     * @brief Gets the final position of the force.
     *
     * @return The final position of the force.
     */
    int &getFinalPosition() noexcept;

    /**
     * @brief Gets the clock used for managing shooting intervals.
     *
     * @return A reference to the SFML clock that tracks shooting time.
     */
    sf::Clock &getClockShoot() noexcept;

    /**
     * @brief Shoots the force forward, applying initial damage.
     *
     * @param initialDamage The damage value to apply when shooting forward.
     */
    void shootForwardForce(const float &initialDamage) noexcept;

    /**
     * @brief Stops the force from shooting forward.
     *
     * Deactivates the forward shooting behavior.
     */
    void stopShootingForward() noexcept;

    /**
     * @brief Checks if the force is currently shooting forward.
     *
     * @return True if the force is shooting forward, false otherwise.
     */
    const bool &isShootForward() const noexcept;

    /**
     * @brief Gets the initial damage value applied when shooting the force.
     *
     * @return The initial damage value.
     */
    const float &getInitialDamage() const noexcept;

    /**
     * @brief Reattaches the force, making it ready for use again.
     */
    void reattachedForce() noexcept;

    const bool HaveIToCheckSkin() const noexcept;
    const void checkSkinDone() noexcept;

  private:
    int _xFinal;             /**< The final position of the force */
    int _idBelong;           /**< The ID of the force's owner */
    std::size_t _levelForce; /**< The level of the force */
    bool _toTheRight;        /**< Orientation of the force (true for right, false for left) */
    bool _haveToShoot;       /**< Flag to check if the force should shoot */
    sf::Clock _clockShoot;   /**< Clock to manage the shooting intervals */
    bool _isShootForward;    /**< Flag to check if the force is shooting forward */
    float _initialeDamage;   /**< Initial damage when shooting the force */
    bool _isEquipped;        /**< Flag to check if the force is equipped */
    bool _haveToCheckSkin;   /**< Flag to check the skin and I have to change */
};

#endif /* !FORCE_HPP_ */
