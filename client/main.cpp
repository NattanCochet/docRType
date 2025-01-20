/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** main
*/

#include "Game/Game.hpp"

int main(int argc, char **argv)
{
    if (argc != 1) {
        std::cerr << "USAGE: " << argv[0] << std::endl;
        return 84;
    }
    Game game;
    return (game.init());
}