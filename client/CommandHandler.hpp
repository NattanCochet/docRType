#include "client.hpp"
#include <string>
#include <sstream>
#include <functional>
#include <unordered_map>
#include <stdexcept>
#include <cstdint>

/**
 * @class CommandHandler
 * @brief A class that handles parsing and executing commands.
 *
 * This class manages a set of commands, processes input, and stores data associated with the commands.
 * It allows the registration of commands and the execution of the respective functions.
 */
class CommandHandler {
    public:
        /**
         * @brief Default constructor for CommandHandler.
         *
         * Registers the default commands like "move" and "shoot".
         */
        CommandHandler() {
            registerCommand("move", [this](const std::vector<std::string>& args, std::vector<uint8_t>& data) {
                handleMoveCommand(args, data);
            });

            registerCommand("shoot", [this](const std::vector<std::string>& args, std::vector<uint8_t>& data) {
                handleShootCommand(args, data);
            });
        }

        /**
         * @brief Executes a command based on input string.
         *
         * This method parses the input string, extracts the command and its arguments, and executes the corresponding command function.
         * @param input The command string to be executed.
         * @param data A reference to a vector that will store the data related to the command.
         */
        void executeCommand(const std::string& input, std::vector<uint8_t>& data) {
            std::istringstream stream(input);
            std::string commandName;
            std::vector<std::string> args;

            stream >> commandName;
            std::string arg;
            while (stream >> arg) {
                args.push_back(arg);
            }

            auto it = commands.find(commandName);
            if (it != commands.end()) {
                it->second(args, data);
            } else {
                std::cerr << "Unknown command: " << commandName << "\n";
            }
        }

    private:
        /**
         * @brief A map that stores command names and their associated functions.
         *
         * The map holds the relationship between a command name (string) and its corresponding handler function.
         */
        std::unordered_map<std::string, std::function<void(const std::vector<std::string>&, std::vector<uint8_t>&)>> commands;

        /**
         * @brief Registers a new command with its handler function.
         *
         * This function adds a new command and its associated callback to the list of available commands.
         * @param name The name of the command.
         * @param func The callback function to execute when the command is called.
         */
        void registerCommand(const std::string& name, std::function<void(const std::vector<std::string>&, std::vector<uint8_t>&)> func) {
            commands[name] = func;
        }

        /**
         * @brief Handles the "move" command.
         *
         * This function processes the "move" command and appends the relevant data to the provided data vector.
         * It requires 4 arguments: posX, posY, speedX, and speedY, which must be floating-point values.
         * @param args The arguments passed with the "move" command.
         * @param data The vector that will store the command data.
         */
        void handleMoveCommand(const std::vector<std::string>& args, std::vector<uint8_t>& data) {
            if (args.size() != 4) {
                std::cerr << "Error: 'move' command requires exactly 4 arguments (posX, posY, speedX, speedY).\n";
                return;
            }

            try {
                float posX = std::stof(args[0]);
                float posY = std::stof(args[1]);
                float speedX = std::stof(args[2]);
                float speedY = std::stof(args[3]);

                data.clear();
                data.push_back(0x01);
                appendToVector(data, posX);
                appendToVector(data, posY);
                appendToVector(data, speedX);
                appendToVector(data, speedY);

                std::cout << "Move command processed: posX=" << posX
                          << ", posY=" << posY
                          << ", speedX=" << speedX
                          << ", speedY=" << speedY << "\n";

            } catch (const std::exception& e) {
                std::cerr << "Error: Invalid argument for 'move'. All arguments must be floats.\n";
            }
        }

        /**
         * @brief Handles the "shoot" command.
         *
         * This function processes the "shoot" command and appends the relevant data to the provided data vector.
         * It requires 3 arguments: posX, posY (both floats), and type (an integer between 0 and 255).
         * @param args The arguments passed with the "shoot" command.
         * @param data The vector that will store the command data.
         */
        void handleShootCommand(const std::vector<std::string>& args, std::vector<uint8_t>& data) {
            if (args.size() != 3) {
                std::cerr << "Error: 'shoot' command requires exactly 3 arguments (posX, posY, type).\n";
                return;
            }

            try {
                float posX = std::stof(args[0]);
                float posY = std::stof(args[1]);
                int type = std::stoi(args[2]);

                if (type < 0 || type > 255) {
                    throw std::out_of_range("Type must be between 0 and 255.");
                }

                data.clear();
                data.push_back(0x02);
                appendToVector(data, posX);
                appendToVector(data, posY);
                data.push_back(static_cast<uint8_t>(type));

                std::cout << "Shoot command processed: posX=" << posX
                          << ", posY=" << posY
                          << ", type=" << type << "\n";

            } catch (const std::exception& e) {
                std::cerr << "Error: Invalid argument for 'shoot'. posX and posY must be floats, type must be an integer.\n";
            }
        }

        /**
         * @brief Appends a value to the data vector as a sequence of bytes.
         *
         * This template function converts the given value to its byte representation and appends it to the data vector.
         * @param data The vector to which the byte representation will be appended.
         * @param value The value to convert and append.
         */
        template <typename T>
        void appendToVector(std::vector<uint8_t>& data, const T& value) {
            uint8_t buffer[sizeof(T)];
            std::memcpy(buffer, &value, sizeof(T));
            data.insert(data.end(), buffer, buffer + sizeof(T));
        }
};
