/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Registry
*/

#pragma once
#ifndef REGISTRY_HPP_
#define REGISTRY_HPP_
#include <vector>
#include <iostream>
#include <functional>
#include <unordered_map>
#include <typeindex>
#include <any>
#include "ComponentArray.hpp"
#include "Entity.hpp"
#include "../../../Network/NetworkServer.hpp"

class World;

/**
 * @class Registry
 * @brief A class that manages entities and their components, as well as systems that operate on them.
 *
 * This class handles the registration, retrieval, and management of entities, components, and systems in the game world.
 * It provides functionality to register and store components for entities, spawn and kill entities, and register systems for game logic.
 */
class Registry
{
    public:
        /**
         * @brief Registers a system function to be executed in the world.
         *
         * @param system_func A function that takes a reference to a World object and returns an int.
         */
        void register_systems(std::function<int(World &, NetworkServer &)> system_func)
        {
            this->_system_array.push_back(system_func);
        }

        /**
         * @brief Retrieves the list of system functions registered in the registry.
         *
         * @return A vector containing system functions.
         */
        std::vector<std::function<int(World &, NetworkServer &)>> get_systems()
        {
            return (this->_system_array);
        }

        /**
         * @brief Registers a component type and returns a reference to the component array for that type.
         *
         * If the component type is not already registered, it is added to the registry.
         *
         * @tparam Component The component type to be registered.
         * @return A reference to the ComponentArray for the given component type.
         */
        template <class Component>
        ComponentArray<Component> &register_components()
        {
            if (_components_arrays.contains(std::type_index(typeid(Component))) == false) {
                _components_arrays[std::type_index(typeid(Component))] = ComponentArray<Component>();

                std::function<void(Registry &, Entity const &)> erase = [](Registry &r, Entity const &e) {
                    ComponentArray<Component> &arr = r.get_components<Component>();
                    arr.erase(e);
                };
                _erase_functions_array.push_back(erase);
            }

            return std::any_cast<ComponentArray<Component> &>(_components_arrays[std::type_index(typeid(Component))]);
        }

        /**
         * @brief Retrieves the component array for a specific component type.
         *
         * @tparam Component The component type to retrieve the array for.
         * @return A reference to the ComponentArray for the specified component type.
         */
        template <class Component>
        ComponentArray<Component> &get_components()
        {
            return std::any_cast<ComponentArray<Component> &>(_components_arrays[std::type_index(typeid(Component))]);
        }

        /**
         * @brief Retrieves the component array for a specific component type (const version).
         *
         * @tparam Component The component type to retrieve the array for.
         * @return A const reference to the ComponentArray for the specified component type.
         */
        template <class Component>
        ComponentArray<Component> const &get_components() const
        {
            return std::any_cast<ComponentArray<Component> &>(_components_arrays.at(std::type_index(typeid(Component))));
        }

        /**
         * @brief Spawns a new entity and returns it.
         *
         * If there are any dead entities in the registry, a dead entity will be reused.
         * Otherwise, a new entity is created with a new unique ID.
         *
         * @return The newly spawned entity.
         */
        Entity spawn_entity()
        {
            std::size_t idx;

            if (_dead_entities_array.empty()) {
                auto max_id = _entity_array.size();
                _entity_array.insert_at(max_id, Entity(max_id));
                return Entity(max_id);
            }
            idx = _dead_entities_array.back();
            _dead_entities_array.pop_back();
            return this->entity_from_index(idx);
        }

        /**
         * @brief Converts an entity index to an entity object.
         *
         * @param idx The index of the entity.
         * @return The entity corresponding to the given index.
         */
        Entity entity_from_index(std::size_t idx)
        {
            return Entity(idx);
        }

        /**
         * @brief Marks an entity as "dead" and removes its components.
         *
         * This method will invoke all the erase functions associated with the components of the entity
         * before adding it to the list of dead entities.
         *
         * @param e The entity to be killed.
         */
        void kill_entity(Entity const &e)
        {
            for (auto fct : _erase_functions_array) {
                fct(*this, e);
            }
            _dead_entities_array.push_back(e);
        }

        /**
         * @brief Adds a component to an entity.
         *
         * @tparam Component The type of component to add.
         * @param to The entity to which the component will be added.
         * @param c The component to add.
         * @return A reference to the added component.
         */
        template <typename Component>
        typename ComponentArray<Component>::reference_type add_component(Entity const &to, Component &&c)
        {
            auto &arr = this->get_components<Component>();

            arr.insert_at(to, c);
            return arr[to];
        }

        /**
         * @brief Constructs and adds a component to an entity with the specified parameters.
         *
         * @tparam Component The type of component to add.
         * @tparam Params The types of the parameters required to construct the component.
         * @param to The entity to which the component will be added.
         * @param p The parameters to construct the component.
         * @return A reference to the added component.
         */
        template <typename Component, typename... Params>
        typename ComponentArray<Component>::reference_type emplace_component(Entity const& to, Params&&... p)
        {
            Component c(std::forward<Params>(p)...);

            return this->add_component(to, std::move(c));
        }

        /**
         * @brief Removes a component from an entity.
         *
         * @tparam Component The type of component to remove.
         * @param from The entity from which the component will be removed.
         */
        template <typename Component> void remove_component(Entity const &from)
        {
            auto &arr = this->get_components<Component>();

            arr.erase(from);
        }

    private:
        std::unordered_map<std::type_index, std::any> _components_arrays; ///< A map of component arrays, indexed by component type.
        std::vector<std::function<void(Registry &, Entity const &)>> _erase_functions_array; ///< A list of erase functions for components.

        std::vector<std::function<int(World &, NetworkServer &)>> _system_array; ///< A list of system functions.

        ComponentArray<Entity> _entity_array; ///< The array of entities in the registry.
        std::vector<Entity> _dead_entities_array; ///< A list of dead entities.
};

#endif /* !REGISTRY_HPP_ */
