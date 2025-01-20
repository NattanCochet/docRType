/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** HandlingParameters
*/

#include "HandlingParameters.hpp"

HandlingParameters::HandlingParameters(const int &ac, char **av)
    : _ac(ac), _goodParameters(true), _isFlagHelp(false), _isFlagTests(false), _portServer(this->defaultPort)
{
    for (std::size_t i = 1; i < this->_ac; i++) {
        if (av[i]) {
            this->_av.emplace_back(av[i]);
        }
    }
    for (std::size_t index = 0; index < this->_av.size(); index++) {
        if (this->_av[index] == "-h" || this->_av[index] == "--help" || this->_av[index] == "-help") {
            this->_isFlagHelp = true;
            this->_portServer = -1;
            this->_isFlagTests = false;
            return;
        }
        if (this->_av[index] == "-t" || this->_av[index] == "--tests" || this->_av[index] == "-tests") {
            this->_isFlagTests = true;
            continue;
        }
        if (this->_av[index] == "-p" || this->_av[index] == "--port" || this->_av[index] == "-port") {
            if (index + 1 >= this->_av.size() || !this->stringToInt(this->_av[index + 1], this->_portServer)) {
                this->_goodParameters = false;
                this->_isFlagHelp = false;
                this->_portServer = -1;
                this->_isFlagTests = false;
                return;
            }
            index++;
            continue;
        }
        this->_goodParameters = false;
        this->_isFlagHelp = false;
        this->_portServer = -1;
        this->_isFlagTests = false;
        return;
    }
}

HandlingParameters::~HandlingParameters()
{
}

const bool &HandlingParameters::isGoodParameters() const noexcept
{
    return (this->_goodParameters);
}

const bool &HandlingParameters::isFlagHelp() const noexcept
{
    return (this->_isFlagHelp);
}

const bool &HandlingParameters::isFlagTests() const noexcept
{
    return (this->_isFlagTests);
}

const bool HandlingParameters::doIRunServer() const noexcept
{
    return (this->_goodParameters && this->_portServer != -1);
}

const int &HandlingParameters::getPortServer() const noexcept
{
    return (this->_portServer);
}

bool HandlingParameters::stringToInt(const std::string &str, int &result)
{
    try {
        std::size_t pos = 0;
        result = std::stoi(str, &pos);
        if (pos != str.size()) {
            return (false);
        }
        return (true);
    } catch (const std::invalid_argument&) {
        return (false);
    } catch (const std::out_of_range&) {
        return (false);
    }
}
