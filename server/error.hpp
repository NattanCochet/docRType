class ErrorManager {
    public:
        static void handleError(const std::string& context, const std::exception& e) {
            std::cerr << "[Error][" << context << "] " << e.what() << std::endl;
        }

        static void handleCustomError(const std::string& context, const std::string& message) {
            std::cerr << "[Error][" << context << "] " << message << std::endl;
        }
};


