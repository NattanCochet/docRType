/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** GJKAlgorithm
*/

#ifndef GJKALGORITHM_HPP_
#define GJKALGORITHM_HPP_

#include <vector>
#include <cmath>
#include <optional>
#include "Vector.hpp"
#include "Components/Hitbox.hpp"

#ifdef _WIN32
#define M_PI 3.14159265358979323846
#endif

/**
 * @class GJKAlgorithm
 * @brief A class that implements the Gilbert-Johnson-Keerthi (GJK) algorithm for collision detection.
 *
 * The GJK algorithm is used to check if two convex shapes (such as rectangles or circles)
 * are colliding. This class provides methods to compute the collision using the GJK
 * algorithm with various types of shapes.
 */
class GJKAlgorithm {
    public:
        /**
         * @brief Default constructor for GJKAlgorithm.
         *
         * Initializes necessary data for the GJK collision detection algorithm.
         */
        GJKAlgorithm();

        /**
         * @brief Destructor for GJKAlgorithm.
         *
         * Cleans up any resources used by the GJK algorithm.
         */
        ~GJKAlgorithm();

        /**
         * @brief Checks if two hitboxes are colliding using the GJK algorithm.
         *
         * This function checks if two convex shapes (represented as hitboxes) are colliding
         * using the GJK algorithm. It returns an array of booleans indicating which collision
         * zones of the shapes are in collision.
         *
         * @param shapeA The first hitbox for collision detection.
         * @param shapeB The second hitbox for collision detection.
         * @return An array of booleans representing the collision zones.
         */
        const std::optional<std::array<bool, 8>> gjkCollision(const Hitbox& shapeA, const Hitbox& shapeB);

    private:
        /**
         * @brief Computes the triple product of three vectors.
         *
         * The triple product is a vector that results from the cross product of the first
         * vector with the result of the cross product of the second and third vectors.
         *
         * @param a The first vector.
         * @param b The second vector.
         * @param c The third vector.
         * @return The result of the triple product.
         */
        Vector<float, 2> tripleProduct(const Vector<float, 2>& a, const Vector<float, 2>& b, const Vector<float, 2>& c);

        /**
         * @brief Handles the collision detection for a line simplex.
         *
         * This function handles the case when the simplex (set of points) formed by the support
         * points is a line, and adjusts the direction vector accordingly.
         *
         * @param simplex The list of points representing the current simplex.
         * @param direction The direction vector for the GJK algorithm.
         * @return True if the line case was handled successfully, false otherwise.
         */
        bool handleLine(std::vector<Vector<float, 2>>& simplex, Vector<float, 2>& direction);

        /**
         * @brief Handles the collision detection for a triangle simplex.
         *
         * This function handles the case when the simplex formed by the support points
         * is a triangle, and adjusts the direction vector accordingly.
         *
         * @param simplex The list of points representing the current simplex.
         * @param direction The direction vector for the GJK algorithm.
         * @return True if the triangle case was handled successfully, false otherwise.
         */
        bool handleTriangle(std::vector<Vector<float, 2>>& simplex, Vector<float, 2>& direction);

        /**
         * @brief Computes the support point for the GJK algorithm.
         *
         * This function calculates the support point between two shapes in a given direction.
         * The support point is used to build the simplex for the collision detection.
         *
         * @param shapeA The first hitbox for collision detection.
         * @param shapeB The second hitbox for collision detection.
         * @param direction The direction in which to compute the support point.
         * @return The support point between the two shapes in the given direction.
         */
        Vector<float, 2> support(const Hitbox& shapeA, const Hitbox& shapeB, const Vector<float, 2>& direction);

        /**
         * @brief Handles the simplex and updates the direction vector.
         *
         * This function processes the simplex formed by the support points and updates
         * the direction vector accordingly. It is used as a general handler for the
         * GJK algorithm.
         *
         * @param simplex The list of points representing the current simplex.
         * @param direction The direction vector for the GJK algorithm.
         * @return True if the simplex was handled successfully, false otherwise.
         */
        bool handleSimplex(std::vector<Vector<float, 2>>& simplex, Vector<float, 2>& direction);

        /**
         * @brief Retrieves the farthest point from a rectangle in a given direction.
         *
         * This function calculates the farthest point of a rectangle in the specified
         * direction, which is used as the support point in the GJK algorithm.
         *
         * @param shape The hitbox representing the rectangle.
         * @param direction The direction in which to find the farthest point.
         * @return The farthest point of the rectangle in the given direction.
         */
        Vector<float, 2> getFarthestPointRectangle(const Hitbox& shape, const Vector<float, 2>& direction);

        /**
         * @brief Retrieves the farthest point from a circle in a given direction.
         *
         * This function calculates the farthest point of a circle in the specified direction,
         * which is used as the support point in the GJK algorithm.
         *
         * @param shape The hitbox representing the circle.
         * @param direction The direction in which to find the farthest point.
         * @return The farthest point of the circle in the given direction.
         */
        Vector<float, 2> getFarthestPointCircle(const Hitbox& shape, const Vector<float, 2>& direction);

        /**
         * @brief Transforms a vector of arbitrary dimension into a 2D vector.
         *
         * This template function transforms a vector of any size into a 2D vector by
         * extracting the first two elements and converting them to a `Vector<float, 2>`.
         *
         * @tparam T The type of the elements in the vector.
         * @tparam N The size of the vector.
         * @param toTransform The vector to transform into 2D.
         * @return The transformed 2D vector.
         */
        template<typename T, std::size_t N>
        Vector<float, 2> transformeVectorToVector2F(Vector<T, N> toTransform)
        {
            Vector<float, 2> result;

            result = {static_cast<float>(toTransform[0]), static_cast<float>(toTransform[1])};
            return (result);
        }

        /**
         * @brief Analyzes the collision zones between two hitboxes.
         *
         * This function analyzes the collision zones between two shapes and updates
         * the result array with the collision status for each zone.
         *
         * @param shapeA The first hitbox for collision detection.
         * @param shapeB The second hitbox for collision detection.
         * @param result The array that will hold the results of the collision analysis.
         */
        void analyzeCollisionZones(const Hitbox& shapeA, const Hitbox& shapeB, std::array<bool, 8> &result);
};

#endif /* !GJKALGORITHM_HPP_ */
