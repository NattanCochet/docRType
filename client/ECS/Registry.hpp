/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Registry
*/

#pragma once
#ifndef REGISTRY_HPP_
#define REGISTRY_HPP_
#include "../Network/Network.hpp"
#include "ComponentArray.hpp"
#include "Entity.hpp"
#include <any>
#include <functional>
#include <iostream>
#include <typeindex>
#include <unordered_map>
#include <vector>

class World;
class Network;

/**
 * @brief Registry class for managing entities, components, and systems
 *
 * This class serves as the main container and manager for the ECS (Entity Component System).
 * It handles entity creation/deletion, component management, and system registration.
 */
class Registry
{
  public:
    /**
     * @brief Register a system function to be executed by the World
     * @param system_func Function that takes a World reference and returns an int
     */
    void register_systems(std::function<int(World &, Network *)> system_func)
    {
        this->_system_array.push_back(system_func);
    }

    /**
     * @brief Get all registered system functions
     * @return Vector of system functions
     */
    std::vector<std::function<int(World &, Network *)>> get_systems()
    {
        return (this->_system_array);
    }

    /**
     * @brief Register a new component type and its associated array
     * @tparam Component Type of component to register
     * @return Reference to the component array
     */
    template <class Component> ComponentArray<Component> &register_components()
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
     * @brief Get the component array for a specific component type
     * @tparam Component Type of component to retrieve
     * @return Reference to the component array
     */
    template <class Component> ComponentArray<Component> &get_components()
    {
        return std::any_cast<ComponentArray<Component> &>(_components_arrays[std::type_index(typeid(Component))]);
    }

    /**
     * @brief Get the const component array for a specific component type
     * @tparam Component Type of component to retrieve
     * @return Const reference to the component array
     */
    template <class Component> ComponentArray<Component> const &get_components() const
    {
        return std::any_cast<ComponentArray<Component> &>(_components_arrays.at(std::type_index(typeid(Component))));
    }

    /**
     * @brief Create a new entity
     * @return Newly created entity
     *
     * If there are dead entities available, reuses one of them.
     * Otherwise, creates a new entity with the next available ID.
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
     * @brief Create an entity with a specific index
     * @param idx Index to use for the entity
     * @return Entity with the specified index
     */
    Entity entity_from_index(std::size_t idx)
    {
        return Entity(idx);
    }

    /**
     * @brief Remove an entity and all its components
     * @param e Entity to remove
     */
    void kill_entity(Entity const &e)
    {
        for (auto fct : _erase_functions_array) {
            fct(*this, e);
        }
        _dead_entities_array.push_back(e);
    }

    /**
     * @brief Add a component to an entity
     * @tparam Component Type of component to add
     * @param to Entity to add the component to
     * @param c Component to add
     * @return Reference to the added component
     */
    template <typename Component>
    typename ComponentArray<Component>::reference_type add_component(Entity const &to, Component &&c)
    {
        auto &arr = this->get_components<Component>();

        arr.insert_at(to, c);
        return arr[to];
    }

    /**
     * @brief Construct and add a component to an entity
     * @tparam Component Type of component to add
     * @tparam Params Parameter types for component construction
     * @param to Entity to add the component to
     * @param p Parameters for component construction
     * @return Reference to the added component
     */
    template <typename Component, typename... Params>
    typename ComponentArray<Component>::reference_type emplace_component(Entity const &to, Params &&...p)
    {
        Component c(std::forward<Params>(p)...);

        return this->add_component(to, std::move(c));
    }

    /**
     * @brief Remove a component from an entity
     * @tparam Component Type of component to remove
     * @param from Entity to remove the component from
     */
    template <typename Component> void remove_component(Entity const &from)
    {
        auto &arr = this->get_components<Component>();

        arr.erase(from);
    }

  private:
    /// @brief Map of component arrays indexed by component type
    std::unordered_map<std::type_index, std::any> _components_arrays;

    /// @brief Array of functions to erase components when an entity is killed
    std::vector<std::function<void(Registry &, Entity const &)>> _erase_functions_array;

    /// @brief Array of system functions to be executed by the World
    std::vector<std::function<int(World &, Network *)>> _system_array;

    /// @brief Array of active entities
    ComponentArray<Entity> _entity_array;

    /// @brief Array of indices of dead entities that can be reused
    std::vector<Entity> _dead_entities_array;
};

#endif /* !REGISTRY_HPP_ */