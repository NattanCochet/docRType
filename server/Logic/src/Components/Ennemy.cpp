/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Ennemy
*/

#include "../../include/Components/Ennemy.hpp"

Ennemy::Ennemy(int id, std::shared_ptr<ABot> bot) : _id(id), _bot(bot) {}

Ennemy::~Ennemy()
{
}

void Ennemy::setId(int newId)
{
    _id = newId;
}

int Ennemy::getId()
{
    return _id;
}

void Ennemy::setBot(std::shared_ptr<ABot> newBot)
{
    _bot = newBot;
}

std::shared_ptr<ABot> Ennemy::getBot()
{
    return _bot;
}
