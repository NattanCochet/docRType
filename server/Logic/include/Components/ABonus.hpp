/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** ABonus
*/

#ifndef ABONUS_HPP_
#define ABONUS_HPP_
#include <iostream>

class World;

class ABonus
{
  public:
    ABonus() : _isEquipped(false) {};

    virtual ~ABonus() = default;

    virtual bool activate(World &world, std::size_t myIndexEntity) = 0;

    const bool getIsEquipped() const noexcept
    {
        return (_isEquipped);
    };

    const std::size_t &getIdBelong() const noexcept
    {
        return (_indexBelong);
    };

    void isEquipped(const std::size_t indexBelong) noexcept
    {
        _isEquipped = true;
        _indexBelong = indexBelong;
    };

  protected:
    bool _isEquipped;
    std::size_t _indexBelong;
};

#endif /* !ABONUS_HPP_ */
