//
// Created by vladislav on 29.04.22.
//

#ifndef SERVER_V0_1_LOGGER_HPP
#define SERVER_V0_1_LOGGER_HPP

#include <mutex>
#include <ctime>

class Logger {
public:
    Logger() = default;
    ~Logger() = default;
    Logger(const Logger&&) = delete;
    Logger& operator= (const Logger&) = delete;
    Logger(const Logger&) = delete;

    template<typename... Args>
    static void Trace(unsigned int line_number, const char* source_file, const char* message, Args... args) {
        get_instance().log(MESSAGE_PRIORITY::TracePriority, line_number, source_file, message, args...);
    }

    template<typename... Args>
    static void Debug(unsigned int line_number, const char* source_file, const char* message, Args... args) {
        get_instance().log(MESSAGE_PRIORITY::DebugPriority, line_number, source_file, message, args...);
    }

    template<typename... Args>
    static void Info(unsigned int line_number, const char* source_file, const char* message, Args... args) {
        get_instance().log(MESSAGE_PRIORITY::InfoPriority, line_number, source_file, message, args...);
    }

    template<typename... Args>
    static void Warn(unsigned int line_number, const char* source_file, const char* message, Args... args) {
        get_instance().log(MESSAGE_PRIORITY::WarnPriority, line_number, source_file, message, args...);
    }

    template<typename... Args>
    static void Error(unsigned int line_number, const char* source_file, const char* message, Args... args) {
        get_instance().log(MESSAGE_PRIORITY::ErrorPriority, line_number, source_file, message, args...);
    }

    template<typename... Args>
    static void Critical(unsigned int line_number, const char* source_file, const char* message, Args... args) {
        get_instance().log(MESSAGE_PRIORITY::CriticalPriority, line_number, source_file, message, args...);
    }

protected:
    static Logger& get_instance() {
        static Logger logger;
        return logger;
    }

private:
    enum class MESSAGE_PRIORITY { TracePriority, DebugPriority, InfoPriority, WarnPriority, ErrorPriority, CriticalPriority };
    MESSAGE_PRIORITY priority = MESSAGE_PRIORITY::TracePriority;

    std::mutex mutex;
    unsigned short BUFFER_SIZE = 80;

    template<typename... Args>
    void log(MESSAGE_PRIORITY message_priority, const unsigned int line_number, const char* source_file, const char* message, Args... args) {
        const std::time_t time = std::time(0);

        if (message_priority >= priority) {
            const std::lock_guard<std::mutex> lock(mutex);

            switch (message_priority) {
                case (MESSAGE_PRIORITY::CriticalPriority):
                    std::cout << "[CRITICAL!!!]\t";
                    break;
                case (MESSAGE_PRIORITY::ErrorPriority):
                    std::cout << "[ERROR]\t";
                    break;
                case (MESSAGE_PRIORITY::WarnPriority):
                    std::cout << "[WARN]\t";
                    break;
                case (MESSAGE_PRIORITY::InfoPriority):
                    std::cout << "[INFO]\t";
                    break;
                case (MESSAGE_PRIORITY::DebugPriority):
                    std::cout << "[DEBUG]\t";
                    break;
                case (MESSAGE_PRIORITY::TracePriority):
                    std::cout << "[TRACE]\t";
                    break;
            }

            char buffer[BUFFER_SIZE];
            std::strftime(buffer, BUFFER_SIZE, "%c", std::localtime(&time));

            std::cout << "time: " << buffer << '\t';
            std::cout << "file: " << source_file << ':' << line_number << '\t';
            std::cout << message << ' ';
            ((std::cout << args << ' '), ...);
            std::cout << '\n';
        }
    }

};

#endif //SERVER_V0_1_LOGGER_HPP
