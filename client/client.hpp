#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <asio.hpp>
#include <vector>
#include <exception>
#include <iostream>
#include <iomanip>

using asio::ip::udp;

/**
 * @class UDPClient
 * @brief A client for sending UDP messages to a server.
 *
 * The `UDPClient` class provides functionality for sending binary data to a server
 * over UDP. It supports error handling through the `ClientError` exception class.
 */
class UDPClient {
    public:
        /**
         * @brief Constructs a UDP client to communicate with the specified server.
         *
         * @param server_ip The IP address of the server to send data to.
         * @param port The port number to use for the UDP connection.
         */
        UDPClient(const std::string& server_ip, uint16_t port);
        /**
         * @class ClientError
         * @brief Exception class used for error handling in the UDP client.
         *
         * This exception class is used to signal errors related to the client. It includes
         * the type of error (e.g., BINARY error) and optional details about the error.
         */
        class ClientError : public std::exception {
            public:
                /**
                 * @enum ErrorType
                 * @brief Enum for different types of errors.
                 */
                enum ErrorType {
                    UNKNOWN, ///< Unknown error.
                    BINARY,  ///< Binary data error.
                };

                /**
                 * @brief Constructs a ClientError with a specified error type and optional details.
                 *
                 * @param type The type of error.
                 * @param details Optional details about the error.
                 */
                ClientError(ErrorType type, const std::string& details = "")
                    : _type(type), _details(details) {}

                /**
                 * @brief Destructor for the ClientError class.
                 */
                ~ClientError() override = default;

                /**
                 * @brief Returns the error message.
                 *
                 * @return A C-string representing the error message.
                 */
                const char* what() const noexcept override {
                    if (_type == BINARY)
                        return "BINARY ERROR";
                    return "Unknown command";
                }

                /**
                 * @brief Returns additional details about the error.
                 *
                 * @return A string containing error details.
                 */
                const std::string& details() const {
                    return _details;
                }

            private:
                ErrorType _type; ///< The type of error.
                std::string _details; ///< Details about the error.
        };

        /**
         * @brief Sends binary data to the server.
         *
         * @param binary_data A vector of bytes to be sent to the server.
         */
        void sendBinaryData(const std::vector<uint8_t>& binary_data);

    private:
        /**
         * @brief Prints the binary data as hexadecimal for debugging purposes.
         *
         * @param data A vector of bytes to be printed in hexadecimal.
         */
        void printHex(const std::vector<uint8_t>& data);

        asio::io_context io_context; ///< The ASIO I/O context used for communication.
        udp::socket client_socket; ///< The UDP socket for communication.
        udp::endpoint server_endpoint; ///< The endpoint of the server to which data is sent.
};

#endif // CLIENT_HPP
