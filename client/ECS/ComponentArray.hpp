/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** ComponentArray
*/

#pragma once
#ifndef COMPONENTARRAY_HPP_
#define COMPONENTARRAY_HPP_
#include <algorithm>
#include <iostream>
#include <optional>
#include <vector>

/**
 * @brief Template class for managing an array of optional components
 * @tparam Component The type of component to store in the array
 */
template <typename Component> class ComponentArray
{
  public:
    /// @brief Type alias for optional component values
    using value_type = std::optional<Component>;
    /// @brief Type alias for references to optional component values
    using reference_type = value_type &;
    /// @brief Type alias for const references to optional component values
    using const_reference_type = const value_type &;
    /// @brief Type alias for the underlying container type
    using container_t = std::vector<value_type>;
    /// @brief Type alias for size operations
    using size_type = typename container_t::size_type;
    /// @brief Type alias for iterators
    using iterator = typename container_t::iterator;
    /// @brief Type alias for const iterators
    using const_iterator = typename container_t::const_iterator;

    /// @brief Type alias for allocator
    using allocator_type = typename container_t::allocator_type;
    /// @brief Type alias for allocator traits
    using allocator_traits = std::allocator_traits<allocator_type>;

  private:
    container_t _data; ///< Internal container for storing components

  public:
    /// @brief Default constructor
    ComponentArray() = default;

    /**
     * @brief Copy constructor
     * @param other The ComponentArray to copy from
     */
    ComponentArray(ComponentArray const &other) : _data(other._data)
    {
    }

    /**
     * @brief Move constructor
     * @param other The ComponentArray to move from
     */
    ComponentArray(ComponentArray &&other) noexcept : _data(std::move(other._data))
    {
    }

    /// @brief Default destructor
    ~ComponentArray() = default;

    /**
     * @brief Copy assignment operator
     * @param other The ComponentArray to copy from
     * @return Reference to this ComponentArray
     */
    ComponentArray &operator=(ComponentArray const &other)
    {
        if (this != &other) {
            _data = other._data;
        }
        return *this;
    }

    /**
     * @brief Move assignment operator
     * @param other The ComponentArray to move from
     * @return Reference to this ComponentArray
     */
    ComponentArray &operator=(ComponentArray &&other) noexcept
    {
        if (this != &other) {
            _data = std::move(other._data);
        }
        return *this;
    }

    /**
     * @brief Array subscript operator
     * @param idx Index to access
     * @return Reference to the component at the specified index
     */
    reference_type operator[](size_t idx)
    {
        return _data[idx];
    }

    /**
     * @brief Const array subscript operator
     * @param idx Index to access
     * @return Const reference to the component at the specified index
     */
    const_reference_type operator[](size_t idx) const
    {
        return _data[idx];
    }

    /**
     * @brief Get iterator to beginning
     * @return Iterator to the beginning
     */
    iterator begin()
    {
        return _data.begin();
    }

    /**
     * @brief Get const iterator to beginning
     * @return Const iterator to the beginning
     */
    const_iterator begin() const
    {
        return _data.begin();
    }

    /**
     * @brief Get const iterator to beginning
     * @return Const iterator to the beginning
     */
    const_iterator cbegin() const
    {
        return _data.cbegin();
    }

    /**
     * @brief Get iterator to end
     * @return Iterator to the end
     */
    iterator end()
    {
        return _data.end();
    }

    /**
     * @brief Get const iterator to end
     * @return Const iterator to the end
     */
    const_iterator end() const
    {
        return _data.end();
    }

    /**
     * @brief Get const iterator to end
     * @return Const iterator to the end
     */
    const_iterator cend() const
    {
        return _data.cend();
    }

    /**
     * @brief Get size of array
     * @return Number of elements in array
     */
    size_type size() const
    {
        return _data.size();
    }

    /**
     * @brief Insert component at specified position
     * @param pos Position to insert at
     * @param value Component to insert
     * @return Reference to inserted component
     */
    reference_type insert_at(size_type pos, const Component &value)
    {
        if (pos >= _data.size()) {
            _data.resize(pos + 1);
        }
        _data[pos] = value;
        return _data[pos];
    }

    /**
     * @brief Insert component at specified position using move semantics
     * @param pos Position to insert at
     * @param value Component to insert
     * @return Reference to inserted component
     */
    reference_type insert_at(size_type pos, Component &&value)
    {
        if (pos >= _data.size()) {
            _data.resize(pos + 1);
        }
        _data[pos] = std::move(value);
        return _data[pos];
    }

    /**
     * @brief Grow container to accommodate specified position
     * @param pos Position to grow to
     */
    void grow_to(size_type pos)
    {
        while (this->size() < pos + 1) {
            _data.push_back(value_type());
        }
    }

    /**
     * @brief Compact array by removing null elements
     */
    void compaction()
    {
        container_t compacted_data;
        compacted_data.reserve(_data.size());

        for (auto &element : _data) {
            if (element.has_value()) {
                compacted_data.push_back(std::move(element));
            }
        }

        _data = std::move(compacted_data);
    }

    /**
     * @brief Construct component in-place at specified position
     * @param pos Position to construct at
     * @param params Constructor parameters
     * @return Reference to constructed component
     * @throw std::out_of_range if position is out of range
     */
    template <class... Params> reference_type emplace_at(size_type pos, Params &&...params)
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
     * @brief Erase component at specified position
     * @param pos Position to erase
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
     * @brief Get index of specified component
     * @param value Component to find
     * @return Index of component
     * @throw std::out_of_range if component not found
     */
    size_t get_index(const value_type &value) const
    {
        auto it = std::find_if(
            _data.begin(), _data.end(), [&value](const value_type &item) { return compare_optional(item, value); });

        if (it != _data.end()) {
            return std::distance(_data.begin(), it);
        }
        throw std::out_of_range("Element not found");
    }
};

/**
 * @brief Compare two optional components for equality
 * @param lhs First component
 * @param rhs Second component
 * @return True if components are equal
 */
template <typename Component>
typename std::enable_if<std::is_copy_constructible<Component>::value, bool>::type compare_optional(
    const std::optional<Component> &lhs, const std::optional<Component> &rhs)
{
    if (!lhs.has_value() && !rhs.has_value()) {
        return true;
    }

    if (!lhs.has_value() || !rhs.has_value()) {
        return false;
    }

    return lhs.value() == rhs.value();
}

/**
 * @brief Stream insertion operator for ComponentArray
 * @param os Output stream
 * @param arr ComponentArray to output
 * @return Modified output stream
 */
template <typename Component> std::ostream &operator<<(std::ostream &os, const ComponentArray<Component> &arr)
{
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
 * @brief Stream insertion operator for optional values
 * @param os Output stream
 * @param opt Optional value to output
 * @return Modified output stream
 */
template <typename T> std::ostream &operator<<(std::ostream &os, const std::optional<T> &opt)
{
    if (opt.has_value()) {
        os << opt.value();
    } else {
        os << "nullopt";
    }
    return os;
}

#endif /* !COMPONENTARRAY_HPP_ */