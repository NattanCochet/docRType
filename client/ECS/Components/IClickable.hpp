/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Clickable
*/

/**
 * @file IClickable.hpp
 * @brief Header file for the IClickable class.
 */

#pragma once
#ifndef ICLICKABLE_HPP_
    #define ICLICKABLE_HPP_
    #include "../World.hpp"


    /**
     * @class IClickable
     * @brief Interface class that represents a clickable object with an associated action.
     */
    class IClickable {
        public:
            /**
             * @brief Gets the action associated with this Clickable object.
             * @return The function that defines the action to be executed.
             */
            virtual std::function<void(std::size_t)> getAction() = 0;

            /**
             * @brief Sets a new action for this Clickable object.
             * @param action Function to be executed when the object is clicked.
             */
            virtual void setAction(std::function<void(std::size_t)> action) = 0;
    };

#endif /* !CLICKABLE_HPP_ */
