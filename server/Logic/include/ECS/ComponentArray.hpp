/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** ComponentArray
*/

#pragma once
#ifndef COMPONENTARRAY_HPP_
#define COMPONENTARRAY_HPP_
#include <optional>
#include <iostream>
#include <vector>
#include <algorithm>

/**
 * @brief A dynamic array that manages components, with optional values for each slot.
 *
 * This template class is designed to manage an array of components, supporting dynamic
 * resizing, insertion, and erasure while utilizing `std::optional` to handle empty slots.
 *
 * @tparam Component The type of components managed by the array.
 */
template <typename Component>
class ComponentArray {
    public:
        using value_type = std::optional<Component>; /**< The type of each slot, wrapped in std::optional. */
        using reference_type = value_type &; /**< The type of reference to a slot. */
        using const_reference_type = const value_type &; /**< The type of constant reference to a slot. */
        using container_t = std::vector<value_type>; /**< The underlying container type. */
        using size_type = typename container_t::size_type; /**< The type used for size and indexing. */
        using iterator = typename container_t::iterator; /**< Iterator type for the container. */
        using const_iterator = typename container_t::const_iterator; /**< Constant iterator type for the container. */

        // Allocator type
        using allocator_type = typename container_t::allocator_type; /**< Allocator type used by the container. */
        using allocator_traits = std::allocator_traits<allocator_type>; /**< Traits for the allocator type. */

    public:
        /**
         * @brief Default constructor.
         */
        ComponentArray() = default;

        /**
         * @brief Copy constructor.
         *
         * @param other Another ComponentArray to copy.
         */
        ComponentArray(ComponentArray const &other) : _data(other._data) {}

        /**
         * @brief Move constructor.
         *
         * @param other Another ComponentArray to move.
         */
        ComponentArray(ComponentArray &&other) noexcept : _data(std::move(other._data)) {}

        /**
         * @brief Destructor.
         */
        ~ComponentArray() = default;

        /**
         * @brief Copy assignment operator.
         *
         * @param other Another ComponentArray to copy.
         * @return Reference to this object.
         */
        ComponentArray &operator=(ComponentArray const &other) {
            if (this != &other) {
                _data = other._data;
            }
            return *this;
        }

        /**
         * @brief Move assignment operator.
         *
         * @param other Another ComponentArray to move.
         * @return Reference to this object.
         */
        ComponentArray &operator=(ComponentArray &&other) noexcept {
            if (this != &other) {
                _data = std::move(other._data);
            }
            return *this;
        }

        /**
         * @brief Access an element at the given index.
         *
         * @param idx Index of the element to access.
         * @return Reference to the optional component at the given index.
         */
        reference_type operator[](size_t idx) {
            return _data[idx];
        }

        /**
         * @brief Access an element at the given index (const version).
         *
         * @param idx Index of the element to access.
         * @return Constant reference to the optional component at the given index.
         */
        const_reference_type operator[](size_t idx) const {
            return _data[idx];
        }

        /**
         * @brief Get an iterator to the beginning of the array.
         *
         * @return Iterator to the beginning of the array.
         */
        iterator begin() {
            return _data.begin();
        }

        /**
         * @brief Get a constant iterator to the beginning of the array.
         *
         * @return Constant iterator to the beginning of the array.
         */
        const_iterator begin() const {
            return _data.begin();
        }

        /**
         * @brief Get a constant iterator to the beginning of the array.
         *
         * @return Constant iterator to the beginning of the array.
         */
        const_iterator cbegin() const {
            return _data.cbegin();
        }

        /**
         * @brief Get an iterator to the end of the array.
         *
         * @return Iterator to the end of the array.
         */
        iterator end() {
            return _data.end();
        }

        /**
         * @brief Get a constant iterator to the end of the array.
         *
         * @return Constant iterator to the end of the array.
         */
        const_iterator end() const {
            return _data.end();
        }

        /**
         * @brief Get a constant iterator to the end of the array.
         *
         * @return Constant iterator to the end of the array.
         */
        const_iterator cend() const {
            return _data.cend();
        }

        /**
         * @brief Get the size of the array.
         *
         * @return Number of elements in the array.
         */
        size_type size() const {
            return _data.size();
        }

        /**
         * @brief Insert a component at a specific index.
         *
         * @param pos Index to insert the component.
         * @param value The component to insert.
         * @return Reference to the inserted component.
         */
        reference_type insert_at(size_type pos, const Component &value) {
            if (pos >= _data.size()) {
                _data.resize(pos + 1);
            }
            _data[pos] = value;
            return _data[pos];
        }

        /**
         * @brief Insert a component at a specific index using move semantics.
         *
         * @param pos Index to insert the component.
         * @param value The component to insert.
         * @return Reference to the inserted component.
         */
        reference_type insert_at(size_type pos, Component &&value) {
            if (pos >= _data.size()) {
                _data.resize(pos + 1);
            }
            _data[pos] = std::move(value);
            return _data[pos];
        }

        /**
         * @brief Emplace a component at a specific index with in-place construction.
         *
         * @param pos Index to emplace the component.
         * @param params Parameters for constructing the component.
         * @return Reference to the emplaced component.
         */
        template <class... Params>
        reference_type emplace_at(size_type pos, Params &&...params) {
            if (pos > _data.size()) {
                throw std::out_of_range("Index out of range");
            }

            allocator_type alloc = _data.get_allocator();

            if (pos == _data.size()) {
                _data.emplace_back(std::forward<Params>(params)...);
            } else {
                allocator_traits::destroy(alloc, std::addressof(_data[pos]));
                allocator_traits::construct(alloc, std::addressof(_data[pos]), std::forward<Params>(params)...);
            }

            return _data[pos];
        }

        /**
         * @brief Erase a component at a specific index.
         *
         * @param pos Index of the component to erase.
         */
        void erase(size_type pos) {
            if (this->size() > pos) {
                allocator_type alloc = _data.get_allocator();

                allocator_traits::destroy(alloc, std::addressof(_data[pos]));
                _data[pos] = std::nullopt;
            }
        }

        /**
         * @brief Get the index of a specific value in the array.
         *
         * @param value The value to search for.
         * @return Index of the value if found.
         * @throw std::out_of_range If the value is not found.
         */
        size_t get_index(const value_type &value) const {
            auto it = std::find_if(_data.begin(), _data.end(), [&value](const value_type &item) {
                return compare_optional(item, value);
            });

            if (it != _data.end()) {
                return std::distance(_data.begin(), it);
            }
            throw std::out_of_range("Element not found");
        }

        /**
         * @brief Grow the array to ensure it can contain the specified index.
         *
         * @param pos Index up to which the array should grow.
         */
        void grow_to(size_type pos) {
            while (this->size() < pos + 1) {
                _data.push_back(value_type());
            }
        }

        /**
         * @brief Remove empty slots from the array.
         */
        void compaction() {
            container_t compacted_data;
            compacted_data.reserve(_data.size());

            for (auto &element : _data) {
                if (element.has_value()) {
                    compacted_data.push_back(std::move(element));
                }
            }

            _data = std::move(compacted_data);
        }

    private:
        container_t _data; /**< The underlying container storing components. */
};

/**
 * @brief Compare two optional components for equality.
 *
 * @tparam Component The type of the component.
 * @param lhs Left-hand side optional component.
 * @param rhs Right-hand side optional component.
 * @return True if both are equal or both are empty, false otherwise.
 */
template <typename Component>
typename std::enable_if<std::is_copy_constructible<Component>::value, bool>::type
compare_optional(const std::optional<Component>& lhs, const std::optional<Component>& rhs) {
    if (!lhs.has_value() && !rhs.has_value()) {
        return true;
    }
    if (lhs.has_value() && rhs.has_value()) {
        return lhs.value() == rhs.value();
    }
    return false;
}
#endif /* COMPONENTARRAY_HPP_ */
