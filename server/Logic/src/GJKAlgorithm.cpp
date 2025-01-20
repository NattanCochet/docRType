/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** GJKAlgorithm
*/

#include "../include/GJKAlgorithm.hpp"

GJKAlgorithm::GJKAlgorithm()
{
}

GJKAlgorithm::~GJKAlgorithm()
{
}

const std::optional<std::array<bool, 8>> GJKAlgorithm::gjkCollision(
    const Hitbox::RectHitbox &shapeA, const Hitbox::RectHitbox &shapeB)
{
    Vector<float, 2> direction(1.0f, 0.0f);
    std::array<bool, 8> result = {};

    std::vector<Vector<float, 2>> simplex;
    simplex.push_back(this->support(shapeA, shapeB, direction));

    direction = Vector<float, 2>(0.0f, 0.0f) - simplex[0];

    while (true) {
        Vector<float, 2> newSupport = this->support(shapeA, shapeB, direction);

        if (newSupport.dot(direction) < 0) {
            return (std::nullopt);
        }

        simplex.push_back(newSupport);

        if (this->handleSimplex(simplex, direction)) {
            this->analyzeCollisionZones(shapeA, shapeB, result);
            return (result);
        }
    }
    return (std::nullopt);
}

bool GJKAlgorithm::handleSimplex(std::vector<Vector<float, 2>> &simplex, Vector<float, 2> &direction)
{
    if (simplex.size() == 2) {
        return handleLine(simplex, direction);
    }
    return handleTriangle(simplex, direction);
}

Vector<float, 2> GJKAlgorithm::support(
    const Hitbox::RectHitbox &shapeA, const Hitbox::RectHitbox &shapeB, const Vector<float, 2> &direction)
{
    Vector<float, 2> farthestPointShapeA;
    Vector<float, 2> farthestPointShapeB;

    switch (shapeA.type) {
    case Hitbox::TYPE::CIRCULAR:
        farthestPointShapeA = this->getFarthestPointCircle(shapeA, direction);
        break;
    case Hitbox::TYPE::RECTANGLE:
        farthestPointShapeA = this->getFarthestPointRectangle(shapeA, direction);
        break;
    default:
        break;
    }

    switch (shapeB.type) {
    case Hitbox::TYPE::CIRCULAR:
        farthestPointShapeB = this->getFarthestPointCircle(shapeB, direction * -1);
        break;
    case Hitbox::TYPE::RECTANGLE:
        farthestPointShapeB = this->getFarthestPointRectangle(shapeB, direction * -1);
        break;
    default:
        break;
    }

    return (farthestPointShapeA - farthestPointShapeB);
}

Vector<float, 2> GJKAlgorithm::getFarthestPointRectangle(
    const Hitbox::RectHitbox &shape, const Vector<float, 2> &direction)
{
    Vector<float, 2> sizeShape =
        Vector<float, 2>(static_cast<float>(shape.widthHitbox), static_cast<float>(shape.heightHitbox));
    Vector<float, 2> positionShape = Vector<float, 2>(shape.XHitbox, shape.YHitbox);
    float rotationRectangle = shape.rotation * M_PI / 180.0f;

    Vector<float, 2> halfSize = sizeShape * 0.5f;
    std::vector<Vector<float, 2>> corners = {Vector<float, 2>(-halfSize[0], -halfSize[1]),
        Vector<float, 2>(halfSize[0], -halfSize[1]), Vector<float, 2>(halfSize[0], halfSize[1]),
        Vector<float, 2>(-halfSize[0], halfSize[1])};

    float cos_rot = cos(rotationRectangle);
    float sin_rot = sin(rotationRectangle);

    float maxDistance = -INFINITY;
    Vector<float, 2> farthest;

    for (const Vector<float, 2> &corner : corners) {
        Vector<float, 2> rotated(corner[0] * cos_rot - corner[1] * sin_rot, corner[0] * sin_rot + corner[1] * cos_rot);

        Vector<float, 2> final = rotated + positionShape + halfSize;
        float distance = final.dot(direction);

        if (distance > maxDistance) {
            maxDistance = distance;
            farthest = final;
        }
    }

    return (farthest);
}

Vector<float, 2> GJKAlgorithm::getFarthestPointCircle(
    const Hitbox::RectHitbox &shape, const Vector<float, 2> &direction)
{
    float lenght = sqrt(direction[0] * direction[0] + direction[1] * direction[1]);
    Vector<float, 2> positionShape = Vector<float, 2>(shape.XHitbox, shape.YHitbox);
    Vector<float, 2> sizeShape = Vector<float, 2>(shape.widthHitbox, shape.heightHitbox);

    if (lenght == 0) {
        return (positionShape);
    }

    Vector<float, 2> normalized(direction[0] / lenght, direction[1] / lenght);

    return (positionShape + normalized * sizeShape[0]);
}

bool GJKAlgorithm::handleTriangle(std::vector<Vector<float, 2>> &simplex, Vector<float, 2> &direction)
{
    Vector<float, 2> C = simplex[0];
    Vector<float, 2> B = simplex[1];
    Vector<float, 2> A = simplex[2];

    Vector<float, 2> AB = B - A;
    Vector<float, 2> AC = C - A;
    Vector<float, 2> AO = Vector<float, 2>(0.0f, 0.0f) - A;

    Vector<float, 2> ABperp = tripleProduct(AC, AB, AB);
    Vector<float, 2> ACperp = tripleProduct(AB, AC, AC);

    if (ABperp.dot(AO) > 0) {
        simplex.erase(simplex.begin());
        direction = ABperp;
        return false;
    }

    if (ACperp.dot(AO) > 0) {
        simplex.erase(simplex.begin() + 1);
        direction = ACperp;
        return false;
    }

    return true;
}

bool GJKAlgorithm::handleLine(std::vector<Vector<float, 2>> &simplex, Vector<float, 2> &direction)
{
    Vector<float, 2> B = simplex[0];
    Vector<float, 2> A = simplex[1];

    Vector<float, 2> AB = B - A;
    Vector<float, 2> AO = Vector<float, 2>(0.0f, 0.0f) - A;

    Vector<float, 2> perp(AB[1], -AB[0]);
    if (perp.dot(AO) > 0) {
        direction = perp;
    }
    else {
        direction = perp * -1;
    }

    return false;
}

Vector<float, 2> GJKAlgorithm::tripleProduct(
    const Vector<float, 2> &a, const Vector<float, 2> &b, const Vector<float, 2> &c)
{
    float ac = a.dot(c);
    float bc = b.dot(c);
    return Vector<float, 2>(b[0] * ac - a[0] * bc, b[1] * ac - a[1] * bc);
}

void GJKAlgorithm::analyzeCollisionZones(
    const Hitbox::RectHitbox &shapeA, const Hitbox::RectHitbox &shapeB, std::array<bool, 8> &result)
{
    result = {false, false, false, false, false, false, false, false};
    Vector<float, 2> posA = Vector<float, 2>(shapeA.XHitbox, shapeA.YHitbox);
    Vector<float, 2> posB = Vector<float, 2>(shapeB.XHitbox, shapeB.YHitbox);
    Vector<float, 2> direction = posB - posA;

    Vector<float, 2> origin(0.0f, 0.0f);
    Vector<float, 2> referencePoint(1.0f, 0.0f);

    double angleRadians = std::atan2(direction[1], direction[0]);

    double angleDegrees = angleRadians * 180.0 / M_PI;
    if (angleDegrees < 0) {
        angleDegrees += 360.0;
    }

    if (angleDegrees >= 224 && angleDegrees <= 319) {
        result[0] = true;
    }
    if (angleDegrees >= 320 || angleDegrees <= 47) {
        result[2] = true;
    }
    if (angleDegrees >= 38 && angleDegrees <= 132) {
        result[4] = true;
    }
    if (angleDegrees >= 94 && angleDegrees <= 245) {
        result[6] = true;
    }
}
