/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** HandlingParameters
*/

#ifndef HANDLINGPARAMETERS_HPP_
#define HANDLINGPARAMETERS_HPP_
#include <vector>
#include <iostream>
#include <string>

class HandlingParameters {
    public:
        HandlingParameters(const int &ac, char **av);
        ~HandlingParameters();

    public:
        const bool &isGoodParameters() const noexcept;
        const bool &isFlagHelp() const noexcept;
        const bool &isFlagTests() const noexcept;
        const bool doIRunServer() const noexcept;
        const int &getPortServer() const noexcept;

        bool stringToInt(const std::string &str, int &result);

    private:
        static const int defaultPort = 4242;
        int _ac;
        std::vector<std::string> _av;
        bool _goodParameters;
        bool _isFlagHelp;
        bool _isFlagTests;
        int _portServer;
};

#endif /* !HANDLINGPARAMETERS_HPP_ */
