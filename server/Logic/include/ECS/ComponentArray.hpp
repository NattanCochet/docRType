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
class ComponentArray
{
    public:
        using value_type = std::optional<Component>; ///< Type of the values stored.
        using reference_type = value_type &; ///< Reference to a value type.
        using const_reference_type = const value_type &; ///< Const reference to a value type.
        using container_t = std::vector<value_type>; ///< Underlying container type.
        using size_type = typename container_t::size_type; ///< Size type for the container.
        using iterator = typename container_t::iterator; ///< Iterator type for the container.
        using const_iterator = typename container_t::const_iterator; ///< Const iterator type.

        // Allocator type
        using allocator_type = typename container_t::allocator_type; ///< Allocator type.
        using allocator_traits = std::allocator_traits<allocator_type>; ///< Allocator traits.

    private:
        container_t _data; ///< Internal storage for the component array.

public:
    /**
     * @brief Default constructor for ComponentArray.
     */
    ComponentArray() = default;

    /**
     * @brief Copy constructor for ComponentArray.
     * @param other The other ComponentArray to copy from.
     */
    ComponentArray(ComponentArray const &other) : _data(other._data) {}

    /**
     * @brief Move constructor for ComponentArray.
     * @param other The other ComponentArray to move from.
     */
    ComponentArray(ComponentArray &&other) noexcept : _data(std::move(other._data)) {}

    /**
     * @brief Destructor for ComponentArray.
     */
    ~ComponentArray() = default;

    /**
     * @brief Copy assignment operator for ComponentArray.
     * @param other The other ComponentArray to assign from.
     * @return A reference to this ComponentArray.
     */
    ComponentArray &operator=(ComponentArray const &other)
    {
        if (this != &other) {
            _data = other._data;
        }
        return *this;
    }

    /**
     * @brief Move assignment operator for ComponentArray.
     * @param other The other ComponentArray to move from.
     * @return A reference to this ComponentArray.
     */
    ComponentArray &operator=(ComponentArray &&other) noexcept
    {
        if (this != &other) {
            _data = std::move(other._data);
        }
        return *this;
    }

    /**
     * @brief Accessor for the element at the given index.
     * @param idx The index of the element to access.
     * @return A reference to the element at the given index.
     */
    reference_type operator[](size_t idx)
    {
        return _data[idx];
    }

    /**
     * @brief Const accessor for the element at the given index.
     * @param idx The index of the element to access.
     * @return A const reference to the element at the given index.
     */
    const_reference_type operator[](size_t idx) const
    {
        return _data[idx];
    }

    /**
     * @brief Returns an iterator to the beginning of the array.
     * @return An iterator to the first element.
     */
    iterator begin()
    {
        return _data.begin();
    }

    /**
     * @brief Returns a const iterator to the beginning of the array.
     * @return A const iterator to the first element.
     */
    const_iterator begin() const
    {
        return _data.begin();
    }

    /**
     * @brief Returns a const iterator to the beginning of the array.
     * @return A const iterator to the first element.
     */
    const_iterator cbegin() const
    {
        return _data.cbegin();
    }

    /**
     * @brief Returns an iterator to the end of the array.
     * @return An iterator to the element after the last element.
     */
    iterator end()
    {
        return _data.end();
    }

    /**
     * @brief Returns a const iterator to the end of the array.
     * @return A const iterator to the element after the last element.
     */
    const_iterator end() const
    {
        return _data.end();
    }

    /**
     * @brief Returns a const iterator to the end of the array.
     * @return A const iterator to the element after the last element.
     */
    const_iterator cend() const
    {
        return _data.cend();
    }

    /**
     * @brief Returns the number of elements in the array.
     * @return The size of the array.
     */
    size_type size() const
    {
        return _data.size();
    }

    /**
     * @brief Inserts a value at the specified position.
     * @param pos The position to insert the value at.
     * @param value The value to insert.
     * @return A reference to the inserted element.
     */
    reference_type insert_at(size_type pos, const Component &value) {
        if (pos >= _data.size())
        {
            _data.resize(pos + 1);
        }
        _data[pos] = value;
        return _data[pos];
    }

    /**
     * @brief Inserts a value at the specified position.
     * @param pos The position to insert the value at.
     * @param value The value to insert.
     * @return A reference to the inserted element.
     */
    reference_type insert_at(size_type pos, Component &&value) {
        if (pos >= _data.size())
        {
            _data.resize(pos + 1);
        }
        _data[pos] = std::move(value);
        return _data[pos];
    }

    /**
     * @brief Grows the array to ensure that it can accommodate an element at the specified position.
     * @param pos The position to grow to.
     */
    void grow_to(size_type pos) {
        while (this->size() < pos + 1) {
            _data.push_back(value_type());
        }
    }

    /**
     * @brief Emplaces a value at the specified position, constructing it in place.
     * @param pos The position to emplace the value at.
     * @param params The parameters to forward to the constructor of the value.
     * @return A reference to the emplaced element.
     * @throws std::out_of_range If the position is out of bounds.
     */
    template <class... Params>
    reference_type emplace_at(size_type pos, Params &&...params)
    {
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
     * @brief Erases the element at the specified position.
     * @param pos The position of the element to erase.
     */
    void erase(size_type pos)
    {
        if (this->size() > pos) {
            allocator_type alloc = _data.get_allocator();

            allocator_traits::destroy(alloc, std::addressof(_data[pos]));
            _data[pos] = std::nullopt;
        }
    }

    /**
     * @brief Gets the index of a specific value in the array.
     * @param value The value to search for.
     * @return The index of the value in the array.
     * @throws std::out_of_range If the value is not found.
     */
    size_t get_index(const value_type &value) const
    {
        auto it = std::find_if(_data.begin(), _data.end(), [&value](const value_type &item) {
            return item == value;
        });

        if (it != _data.end()) {
            return std::distance(_data.begin(), it);
        }
        throw std::out_of_range("Element not found");
    }
};

/**
 * @brief Outputs a ComponentArray to an output stream.
 * @param os The output stream.
 * @param arr The ComponentArray to output.
 * @return The output stream with the ComponentArray outputted.
 */
template <typename Component>
std::ostream& operator<<(std::ostream& os, const ComponentArray<Component>& arr) {
    os << "[";
    for (auto it = arr.begin(); it != arr.end(); ++it) {
        if (it->has_value()) {
            os << it->value();
        } else {
            os << "nullopt";
        }
        if (std::next(it) != arr.end()) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

/**
 * @brief Outputs an optional value to an output stream.
 * @param os The output stream.
 * @param opt The optional value to output.
 * @return The output stream with the optional value outputted.
 */
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::optional<T>& opt) {
    if (opt.has_value()) {
        os << opt.value();
    } else {
        os << "nullopt";
    }
    return os;
}
#endif /* !COMPONENTARRAY_HPP_ */