#include "client.hpp"
#include "CommandHandler.hpp"
#include <asio.hpp>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <boost/system/system_error.hpp>

using asio::ip::udp;

UDPClient::UDPClient(const std::string& server_ip, uint16_t port) : client_socket(io_context), server_endpoint(asio::ip::address::from_string(server_ip), port) {
    client_socket.open(udp::v4());
    std::cout << "Client initialized. Sending data to " << server_ip << ":" << port << "\n";
}

void UDPClient::sendBinaryData(const std::vector<uint8_t>& binary_data) {
    try {
        client_socket.send_to(asio::buffer(binary_data), server_endpoint);
        std::cout << "Sent binary data: ";
        printHex(binary_data);
    } catch (const boost::system::system_error& e) {
        throw ClientError(ClientError::BINARY, e.what());
    } catch (const std::exception& e) {
        throw ClientError(ClientError::UNKNOWN, e.what());
    }
}

void UDPClient::printHex(const std::vector<uint8_t>& data) {
    for (const auto& byte : data) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte) << " ";
    }
    std::cout << std::dec << std::endl;
}

/*std::vector<uint8_t> data = {
    0x01,                                // Action type: "move"
    0x00, 0x00, 0x80, 0x3F,              // posX = 1.0 (float)
    0x00, 0x00, 0x00, 0x40,              // posY = 2.0 (float)
    0xCD, 0xCC, 0x8C, 0x3F,              // speedX = 1.1 (float)
    0xCD, 0xCC, 0x4C, 0x3E               // speedY = 0.2 (float)
};*/
int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "USAGE: " << argv[0] << " HOST PORT\n";
        return 84;
    }

    try {
        UDPClient client(argv[1], std::atoi(argv[2]));
        std::vector<uint8_t> data;

        CommandHandler commandHandler;

        while (true) {
            std::cout << "Enter command: ";
            std::string input;
            if (!std::getline(std::cin, input)) {
                std::cerr << "\nEOF detected\n";
                std::cin.clear();
                break;
            }

            if (input == "exit") break;

            commandHandler.executeCommand(input, data);

            if (!data.empty()) {
                client.sendBinaryData(data);
                data.clear();
            }
        }

    } catch (const std::exception& e) {
        std::cerr << "Critical Error: " << e.what() << "\n";
    }

    return 0;
}
