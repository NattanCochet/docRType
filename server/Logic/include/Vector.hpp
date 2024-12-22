/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Vector4i
*/

#pragma once
#ifndef VECTOR_HPP_
#define VECTOR_HPP_
#include <iostream>
#include <array>
#include <cmath>
#include <string>

/**
 * @class Vector
 * @brief A templated class representing a vector of arbitrary size and type.
 *
 * This class provides functionality for creating and manipulating vectors of any type T and size N. It supports
 * common operations like addition, subtraction, scalar multiplication, dot product, and cross product (for 2D vectors).
 *
 * @tparam T The type of the elements in the vector (e.g., int, float).
 * @tparam N The number of dimensions of the vector (size of the vector).
 */
template<typename T, std::size_t N>
class Vector {
    public:
        /**
         * @brief Default constructor that initializes the vector with default values.
         *
         * Each element of the vector is initialized to the default value of type T.
         */
        Vector()
        {
            for(size_t i = 0; i < N; i++) {
                _data[i] = T();
            }
            _size = N;
        }

        /**
         * @brief Constructor that initializes the vector with specified values.
         *
         * Initializes the vector with the provided arguments, which are cast to type T. The number of arguments
         * must match the size of the vector (N).
         *
         * @param args The values to initialize the vector with.
         *
         * @note This constructor uses a variadic template, so it can accept any number of arguments.
         */
        template<typename... Args>
        Vector(Args... args)
        {
            _data = {static_cast<T>(args)...};
            _size = N;
            static_assert(sizeof...(args) == N, "Incorrect number of arguments");
        }

        /**
         * @brief Destructor.
         *
         * The destructor does not perform any specific operations in this class as no dynamic memory is allocated.
         */
        ~Vector() {}

        /**
         * @brief Indexing operator for non-const access to vector elements.
         *
         * Allows for accessing and modifying vector elements using the bracket notation (e.g., vec[index]).
         *
         * @param index The index of the element to access.
         * @return A reference to the element at the specified index.
         */
        T& operator[](std::size_t index)
        {
            return _data[index];
        }

        /**
         * @brief Indexing operator for const access to vector elements.
         *
         * Allows for accessing vector elements in a read-only manner using the bracket notation.
         *
         * @param index The index of the element to access.
         * @return A constant reference to the element at the specified index.
         */
        const T& operator[](std::size_t index) const
        {
            return _data[index];
        }

        /**
         * @brief Retrieves the size of the vector.
         *
         * @return The size (number of elements) of the vector.
         */
        const std::size_t getSize() const
        {
            return (_size);
        }

        /**
         * @brief Adds two vectors element-wise.
         *
         * Adds corresponding elements of two vectors and returns the result.
         *
         * @param other The vector to add.
         * @return A new vector containing the result of the addition.
         */
        Vector<T, N> operator+(const Vector<T, N>& other) const
        {
            Vector<T, N> result;
            for(size_t i = 0; i < N; i++) {
                result[i] = _data[i] + other[i];
            }
            return result;
        }

        /**
         * @brief Subtracts one vector from another element-wise.
         *
         * Subtracts corresponding elements of two vectors and returns the result.
         *
         * @param other The vector to subtract.
         * @return A new vector containing the result of the subtraction.
         */
        Vector<T, N> operator-(const Vector<T, N>& other) const {
            Vector<T, N> result;
            for(size_t i = 0; i < N; i++) {
                result[i] = _data[i] - other[i];
            }
            return result;
        }

        /**
         * @brief Multiplies two vectors element-wise.
         *
         * Multiplies corresponding elements of two vectors and returns the result.
         *
         * @param other The vector to multiply.
         * @return A new vector containing the result of the multiplication.
         */
        Vector<T, N> operator*(const Vector<T, N>& other) const {
            Vector<T, N> result;
            for(size_t i = 0; i < N; i++) {
                result[i] = _data[i] * other[i];
            }
            return result;
        }

        /**
         * @brief Multiplies a vector by a scalar.
         *
         * Multiplies each element of the vector by a scalar value and returns the result.
         *
         * @param coeff The scalar value to multiply with.
         * @return A new vector containing the result of the multiplication.
         */
        Vector<T, N> operator*(const T coeff) const {
            Vector<T, N> result;
            for(size_t i = 0; i < N; i++) {
                result[i] = _data[i] * coeff;
            }
            return result;
        }

        /**
         * @brief Computes the dot product of two vectors.
         *
         * Computes the dot product of two vectors by multiplying corresponding elements and summing the results.
         *
         * @param other The vector to compute the dot product with.
         * @return The result of the dot product.
         */
        float dot(const Vector<T, N>& other) const {
            float result = 0.0f;
            for (std::size_t i = 0; i < N; i++) {
                result += _data[i] * other[i];
            }
            return result;
        }

        /**
         * @brief Computes the cross product of two 2D vectors.
         *
         * Computes the cross product of two 2D vectors (for N = 2) and returns the result.
         *
         * @param other The vector to compute the cross product with.
         * @return The result of the cross product (or -1.0f if the vectors are not 2D).
         */
        float cross(const Vector<T, N>& other) const {
            if (other.getSize() != 2 || _size != 2) {
                return (-1.0f);
            }
            return _data[0] * other[1] - _data[1] * other[0];
        }

        /**
         * @brief Stream insertion operator to output the vector.
         *
         * Allows printing the vector using the `<<` operator. The vector is output as a tuple of values.
         *
         * @param os The output stream to write to.
         * @param v The vector to output.
         * @return The output stream with the vector's values inserted.
         */
        friend std::ostream& operator<<(std::ostream& os, const Vector<T, N>& v) {
            os << "(";
            for(size_t i = 0; i < N; i++) {
                os << v[i];
                if (i < N - 1) {
                    os << ", ";
                }
            }
            os << ")";
            return os;
        }

    private:
        std::array<T, N> _data; ///< The data array holding the vector elements.
        std::size_t _size; ///< The size of the vector (number of dimensions).
};

#endif /* !VECTOR_HPP_ */
