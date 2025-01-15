/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Vitality
*/

#pragma once
#ifndef VITALITY_HPP_
#define VITALITY_HPP_

#include <iostream>

/**
 * @class Vitality
 * @brief Represents the vitality (health) of an entity in the game.
 *
 * The `Vitality` class is responsible for managing an entity's life, including the current life,
 * the maximum life, and the ability to heal or damage the entity.
 */
class Vitality {
public:
    /**
     * @brief Default constructor that initializes the vitality with default values.
     */
    Vitality();

    /**
     * @brief Constructor that initializes the vitality with specified values.
     *
     * @param nbrLife The current number of life points the entity has.
     * @param entityID The ID of the entity to know which one is it (for score)
     * @param nbrLifeMax The maximum number of life points the entity can have (defaults to -1, meaning no maximum).
     */
    Vitality(int nbrLife, std::size_t entityID, int nbrLifeMax = -1);

    /**
     * @brief Destructor.
     *
     * The destructor does not need to perform any special cleanup.
     */
    ~Vitality() = default;

    /**
     * @brief Gets the current life of the entity.
     *
     * @return The current number of life points the entity has.
     */
    int getLife() const;

    /**
     * @brief Gets the default life of the entity.
     *
     * @return The default number of life points the entity had when created.
     */
    int getDefaultLife() const;

    /**
     * @brief Gets the ID of the entity
     *
     * @return The ID of the entity
     */
    std::size_t getEntityID();

    /**
     * @brief Sets the entity's current life to a new value.
     *
     * @param newLife The new number of life points.
     * @param nbrLifeMax The maximum number of life points (defaults to -1, meaning no maximum).
     */
    void setNewLife(int newLife, int nbrLifeMax = -1);

    /**
     * @brief Sets the new ID of the entity
     *
     * @param newEntityID The new ID of the entity
     */
    void setEntityID(std::size_t newEntityID);

    /**
     * @brief Heals the entity by a specified amount.
     *
     * @param heal The amount of life to heal the entity.
     */
    void healEntity(int heal);

    /**
     * @brief Damages the entity by a specified amount.
     *
     * @param damage The amount of life to subtract from the entity.
     */
    void damageEntity(int damage);

    /**
     * @brief Checks if the entity is dead.
     *
     * @return `true` if the entity's life is 0 or less, `false` otherwise.
     */
    bool isDead() const;

private:
    int _nbrLife;      ///< The current life of the entity.
    int _nbrLifeMax;   ///< The maximum life the entity can have (defaults to -1 if unlimited).
    int _defaultLife;  ///< The default life the entity had when it was created.
    std::size_t _entityID; ///< The ID of entity
};

#endif // VITALITY_HPP_
