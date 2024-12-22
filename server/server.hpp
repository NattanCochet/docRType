#include <iostream>
#include <string>
#include <asio.hpp>
#include <vector>
#include <iostream>
#include <iomanip>
#include <memory>
#include "error.hpp"

using asio::ip::udp;

/**
 * @class UDPServer
 * @brief A class for handling a UDP server that receives and processes packets.
 *
 * The `UDPServer` class uses the ASIO library to manage a UDP socket and provides functionality
 * for receiving packets, processing them, and handling various types of data like movement or shooting.
 * It also includes error handling for binary data and unknown commands.
 */
class UDPServer {
    private:
        asio::io_context io_context; ///< The ASIO I/O context for asynchronous operations
        udp::socket server_socket; ///< The UDP socket used to listen for incoming packets
        std::vector<uint8_t> receive_buffer; ///< Buffer for storing received data

    public:
        /**
         * @brief Constructor for the UDPServer class.
         *
         * Initializes the server socket to listen on the specified port.
         *
         * @param port The port number on which the server listens for incoming packets.
         */
        UDPServer(uint16_t port);

        /**
         * @class Error
         * @brief A custom exception class used to report errors in the UDP server.
         *
         * This class is used to handle errors related to binary data and unknown commands.
         */
        class Error : public std::exception {
            public:
                /**
                 * @enum ErrorType
                 * @brief Enum representing different error types in the UDP server.
                 */
                enum ErrorType {
                    UNKNOWN, ///< Unknown error type
                    BINARY,  ///< Error related to binary data
                };

                /**
                 * @brief Constructor for the Error class.
                 *
                 * Initializes an error with the specified type.
                 *
                 * @param type The type of error (e.g., BINARY, UNKNOWN).
                 */
                Error(ErrorType type) : _type(type) {};

                /**
                 * @brief Destructor for the Error class.
                 *
                 * Cleans up any resources used by the error object.
                 */
                ~Error() {};

                /**
                 * @brief Retrieves the error message as a C-string.
                 *
                 * Returns a description of the error based on its type.
                 *
                 * @return A C-string describing the error.
                 */
                const char *what() const noexcept override {
                    if (_type == BINARY)
                        return "Binary problem";
                    return "Unknown command";
                }

                ErrorType _type; ///< The type of error encountered
        };

        /**
         * @brief Starts the server to listen for incoming UDP packets.
         *
         * This method sets up the server to receive packets asynchronously and process them once received.
         */
        void start();

    private:
        /**
         * @brief Prints the binary data as a hexadecimal string.
         *
         * This utility function formats and prints the received binary data as hexadecimal for debugging or inspection purposes.
         *
         * @param data The binary data to be printed in hexadecimal format.
         * @param length The number of bytes to print from the data buffer.
         */
        void printHex(const std::vector<uint8_t>& data, size_t length);

        /**
         * @brief Processes the received packet and determines the type of action.
         *
         * This method examines the packet data and determines which handler to invoke (e.g., movement, shooting).
         *
         * @param packet A vector containing the binary data received from the client.
         */
        void processPacket(const std::vector<uint8_t>& packet);

        /**
         * @brief Handles movement actions based on the received packet data.
         *
         * This method processes a packet containing movement data and performs the appropriate action in the game.
         *
         * @param packet A vector containing the movement data in binary format.
         */
        void handleMovement(const std::vector<uint8_t>& packet);

        /**
         * @brief Handles shooting actions based on the received packet data.
         *
         * This method processes a packet containing shooting data and performs the appropriate action in the game.
         *
         * @param packet A vector containing the shooting data in binary format.
         */
        void handleShoot(const std::vector<uint8_t>& packet);
};

//#endif // CLIENT_HPP