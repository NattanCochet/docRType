/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Clickable
*/

/**
 * @file Clickable.hpp
 * @brief Header file for the Clickable class.
 */

#pragma once
#ifndef CLICKABLE_HPP_
    #define CLICKABLE_HPP_
    #include "IClickable.hpp"

    /**
     * @class Clickable
     * @brief Class that represents a clickable object with an associated action.
     */
    class Clickable : public IClickable {
        public:
            /**
             * @brief Default constructor for the Clickable class.
             */
            Clickable();

            enum BUTTONTYPE {
                BASICBUTTON,
                TEXTBUTTON,
                SPLITBUTTON,
                KEYBUTTON,
                NUMBUTTON,
                BACKBUTTON,
                ROOMBUTTON
            };
            /**
             * @brief Constructor that initializes the Clickable with an action and an ID.
             * @param action Function to be executed when the object is clicked.
             * @param id Unique identifier for the clickable object.
             */
            Clickable(std::function<void(std::size_t)> action, int id, void *infos, Clickable::BUTTONTYPE kindButton);

            /**
             * @brief Destructor for the Clickable class.
             */
            ~Clickable();

            /**
             * @brief Gets the action associated with this Clickable object.
             * @return The function that defines the action to be executed.
             */
            std::function<void(std::size_t)> getAction();

            /**
             * @brief Sets a new action for this Clickable object.
             * @param action Function to be executed when the object is clicked.
             */
            void setAction(std::function<void(std::size_t)> action);

            /**
             * @brief Gets the ID of this Clickable object.
             * @return The unique identifier of the clickable object.
             */
            int getId();
            void setInfos(void *newInfos);
            void *getInfos();
            Clickable::BUTTONTYPE getKindButton();
            void setKindButton(Clickable::BUTTONTYPE kindButton);

            /**
             * @brief Equality operator to compare two Clickable objects based on their ID.
             * @param other The other Clickable object to compare with.
             * @return True if the objects have the same ID, false otherwise.
             */
            bool operator==(const Clickable& other) const;

        protected:
        private:
            std::function<void(std::size_t)> _action; ///< The action to be executed when the object is clicked.
            int _id; ///< Unique identifier for the Clickable object.
            void *_infos;
            Clickable::BUTTONTYPE _kindButton;
    };

#endif /* !CLICKABLE_HPP_ */
