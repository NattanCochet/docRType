/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** MainNetwork
*/

#ifndef MAINNETWORK_HPP_
#define MAINNETWORK_HPP_
#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>
#include <csignal>
#include "NetworkServer.hpp"
#include "../Logic/include/WorldsIndex.hpp"
#include "../Logic/include/MyClock.hpp"
#include "Message.hpp"
#include "NetworkFunctions.hpp"

class MainNetwork
{
    public:
        MainNetwork(const int &port);
        ~MainNetwork();

        void run(void);

    private:
        int _portServer;
        NetworkServer _networkServer;
        WorldsIndex _wi;
        MyClock _clock;

    private:
        static void signalHandler(int signal);
        static std::atomic<bool> _stopRequested;
};

#endif /* !MAINNETWORK_HPP_ */
