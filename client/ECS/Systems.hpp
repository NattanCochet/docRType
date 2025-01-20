/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Systems
*/

/**
 * @file Systems.hpp
 * @brief Header file for the Systems class, responsible for managing the game systems.
 *
 * The Systems class defines the game systems that operate on the components of entities in the world.
 * Systems process entities and their components to implement game logic such as rendering or interaction.
 */

#pragma once

#ifndef SYSTEMS_HPP_
#define SYSTEMS_HPP_

#include "../Buttons/Buttons.hpp"
#include "ComponentArray.hpp"
#include "Components/Clickable.hpp"
#include "Components/Controllable.hpp"
#include "Components/Drawable.hpp"
#include "Components/Position.hpp"
#include "Registry.hpp"
#include "World.hpp"

class Systems
{
  public:
    /**
     * @brief Constructor for the Systems class.
     *
     * Initializes any necessary data or systems.
     */
    Systems();
    Systems(Network *network);

    /**
     * @brief Destructor for the Systems class.
     *
     * Cleans up any resources used by the systems.
     */
    ~Systems();

    /**
     * @brief Loads the systems into the world.
     *
     * This function registers all systems to the world and sets them up for use.
     * It allows the systems to access entities and components within the world.
     *
     * @param world The world instance in which the systems will operate.
     */
    void loadSystemsInWorld(World &world);

    /**
     * @brief The drawable system that handles rendering drawable components.
     *
     * This system processes entities that have a `Position` and `Drawable` component and renders them accordingly.
     *
     * @param world The world instance in which the entities are processed.
     * @return An integer indicating the result of the system's execution (e.g., success or failure).
     */
    static int drawableSystem(World &world, Network *network);

    /**
     * @brief The clickable system that handles interaction with clickable components.
     *
     * This system processes entities with a `Position` and `Clickable` component to determine interactions
     * with user input, such as clicks or mouse events.
     *
     * @param world The world instance in which the entities are processed.
     * @return An integer indicating the result of the system's execution (e.g., success or failure).
     */
    static int clickableSystem(World &world, Network *network);

    static int controllableSystem(World &world, Network *network);

  private:
    /**
     * @brief Draws sprites for entities that have a `Position` and `Drawable` component.
     *
     * This function is responsible for rendering sprite components at the appropriate position in the world.
     *
     * @param index The index of the entity being processed.
     * @param position The position component of the entity.
     * @param drawable The drawable component of the entity.
     * @param world The world instance where the entity exists.
     */
    static void drawSprites(
        size_t index, ComponentArray<Position> position, std::optional<Drawable> &drawable, World &world);

    /**
     * @brief Draws text for entities that have a `Position` and `Drawable` component.
     *
     * This function is responsible for rendering text components at the appropriate position in the world.
     *
     * @param index The index of the entity being processed.
     * @param position The position component of the entity.
     * @param drawable The drawable component of the entity, which may include text.
     * @param world The world instance where the entity exists.
     */
    static void drawText(
        size_t index, ComponentArray<Position> position, std::optional<Drawable> &drawable, World &world);

    /**
     * @brief Draws buttons for entities that have a `Position` and `Drawable` component.
     *
     * This function is responsible for rendering button components at the appropriate position in the world.
     *
     * @param index The index of the entity being processed.
     * @param position The position component of the entity.
     * @param drawable The drawable component of the entity, which may include a button.
     * @param world The world instance where the entity exists.
     */
    static void drawButton(size_t index, ComponentArray<Position> position, std::optional<Drawable> &drawable,
        ComponentArray<Clickable> clickable, World &world);

    static void changeText(sf::Keyboard::Key, std::optional<Drawable> &drawable);
    static void changeKey(sf::Keyboard::Key key, World &world, std::size_t index);
    static void checkKeyUsed(sf::Keyboard::Key key, World &world);
    static void localAnimations(size_t index, std::optional<Drawable> &drawable, World &world);
};

#endif /* !SYSTEMS_HPP_ */
