/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Clickable
*/

#include "Clickable.hpp"

Clickable::Clickable()
{
}

Clickable::Clickable(std::function<void(std::size_t)> action, int id, void *infos, Clickable::BUTTONTYPE kindButton)
{
    _action = action;
    _id = id;
    _infos = infos;
    _kindButton = kindButton;
}

Clickable::~Clickable()
{
}

int Clickable::getId()
{
    return (_id);
}

std::function<void(std::size_t)> Clickable::getAction()
{
    return (_action);
}

void Clickable::setAction(std::function<void(std::size_t)> action)
{
    _action = action;
}

void *Clickable::getInfos()
{
    return (_infos);
}

void Clickable::setInfos(void *newInfos)
{
    _infos = newInfos;
}

Clickable::BUTTONTYPE Clickable::getKindButton()
{
    return (_kindButton);
}

void Clickable::setKindButton(Clickable::BUTTONTYPE kindButton)
{
    _kindButton = kindButton;
}

bool Clickable::operator==(const Clickable& other) const
{
    return this->_id == other._id;
}
