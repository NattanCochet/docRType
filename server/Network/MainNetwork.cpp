/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** MainNetwork
*/

#include "MainNetwork.hpp"

std::atomic<bool> MainNetwork::_stopRequested(false);

MainNetwork::MainNetwork(const int &port) :
    _portServer(port), _wi(), _networkServer(static_cast<unsigned short>(port)), _clock()
{
    std::signal(SIGINT, this->signalHandler);
    _clock.start();
}

MainNetwork::~MainNetwork()
{
}

void MainNetwork::signalHandler(int signal)
{
    if (signal == SIGINT) {
        _stopRequested = true;
    }
}

void MainNetwork::run(void)
{
    NetworkFunctions nf;

    std::cout << "Serveur démarré sur le port " << std::to_string(this->_portServer) << std::endl;
    while (!this->_stopRequested) {
        while (this->_networkServer.HasMessages()) {
            ClientMessage msg = this->_networkServer.PopMessage();

            nf.executeProtocol(msg, this->_wi, this->_networkServer);
        }

        if (_clock.getElapsedTime().asMilliseconds() >= 80) {
            nf.sendPositions(this->_wi, this->_networkServer);
            _clock.restart();
        }

        this->_wi.applyFunctionsInWorlds(this->_networkServer);

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    std::cout << "\nServeur arrété.\n" << std::endl;
    return;
}
