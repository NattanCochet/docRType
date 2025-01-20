#include <iostream>
#include <thread>
#include "HandlingParameters.hpp"
#include "Test/Test.hpp"
#include "Network/MainNetwork.hpp"

void printHelp(void)
{
    std::cout << "R-Type Server - Game Server Implementation\n"
              << "Usage: ./r-type_server [OPTIONS]\n"
              << "\n"
              << "Options:\n"
              << "  -h, --help, -help     Display this help message and exit\n"
              << "  -t, --tests, tests    Run server with unit tests function and exit\n"
              << "  -p, --port, -port     Set server port (default: 4242)\n"
              << "\n"
              << "Examples:\n"
              << "  ./r-type_server             Start server on default port (4242)\n"
              << "  ./r-type_server -p 8080     Start server on port 8080\n"
              << "  ./r-type_server --tests     Run unit tests\n"
              << "  ./r-type_server -h          Display this help message\n"
              << "\n"
              << "Note:\n"
              << "  The server must be launched before any client connection attempts.\n"
              << "  Make sure the chosen port is not already in use by another service.\n"
              << "  Go check this link for more informations about us: https://nattancochet.github.io/docRType/\n";
}

int main(int ac, char **av)
{
    HandlingParameters hp(ac, av);

    if (!hp.isGoodParameters()) {
        std::cerr << "Error: Wrong Parameters. Retry with -h or -help or --help.\n";
        return (84);
    }
    if (hp.isFlagHelp()) {
        printHelp();
        return (0);
    }
    if (!hp.doIRunServer()) {
        std::cerr << "Error: Cannot run server.\n";
        return (84);
    }
    if (hp.isFlagTests()) {
        flagTest();
        return (0);
    }

    try {
        MainNetwork mn(hp.getPortServer());
        mn.run();
    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    return (0);
}
