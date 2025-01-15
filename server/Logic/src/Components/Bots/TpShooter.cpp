/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** TpShooter
*/

#include "../../../include/Components/Bots/TpShooter.hpp"

TpShooter::TpShooter(float delay, std::size_t nbrShoot)
    : _clockShoot(),
      _clockWaitShoot(),
      _isShooting(false),
      _nbrShootTotal(nbrShoot),
      _nbrShoot(0)
{
    _delay = delay;
}

TpShooter::~TpShooter()
{
}

void TpShooter::moveBot(World &world, std::size_t myIndexEntity)
{
    if (!this->_isShooting) {
        const auto &[widthWindow, heightWindow] = world.getSizeWindow();
        std::optional<Position> &pos = world.getRegistry().get_components<Position>()[myIndexEntity];
        std::optional<Drawable::Drawable> &draw = world.getRegistry().get_components<Drawable::Drawable>()[myIndexEntity];

        if (!pos || !pos.has_value() || !draw || !draw.has_value()) {
            return;
        }

        const Drawable::FrameRect &rect = draw->getCurrentRect();
        const sf::Vector2f &scale = draw->getScale();

        static std::random_device rd;
        static std::mt19937 rng(rd());
        std::uniform_int_distribution<int> x_dist(0, widthWindow - (rect._rectWidth * scale.x));
        std::uniform_int_distribution<int> y_dist(0, heightWindow - (rect._rectHeight * scale.y));

        const int new_x = x_dist(rng);
        const int new_y = y_dist(rng);

        pos->setPosition(new_x, new_y);
        this->_isShooting = true;
        this->_clockWaitShoot.start();
        this->_clockShoot.start();
    }
}

void TpShooter::shootProjectile(World &world, std::size_t myIndexEntity)
{
    std::optional<Position> &pos = world.getRegistry().get_components<Position>()[myIndexEntity];

    if (!pos || !pos.has_value()) {
        return;
    }

    if (this->_isShooting) {
        if (this->_clockWaitShoot.getElapsedTime().asSeconds() >= 2.0f) {
            if (this->_nbrShoot < this->_nbrShootTotal) {
                if (this->_clockShoot.getElapsedTime().asSeconds() >= 0.2f) {
                    this->_nbrShoot += 1;
                    world.getClassCreateEntity().createLaser(pos->getPosition(), world.getRegistry(), myIndexEntity, false, false);
                    this->_clockShoot.restart();
                }
            } else {
                this->_isShooting = false;
                this->_nbrShoot = 0;
                this->_clockWaitShoot.restartAndPause();
                this->_clockShoot.restartAndPause();
            }
        }
    }
}
