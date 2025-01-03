#pragma once

#include <string>
#include <fstream>

enum LogLevel { DEBUG, INFO, WARNING, ERROR, CRITICAL };
enum Mode { VERBOSE, QUIET };

class Logger {
private:
    //-----------------------------------
    //             Attributes
    //-----------------------------------

    std::ofstream logFile;
    static Logger* instance;
    Mode mode;


    //-----------------------------------
    //     Constructor and destructor
    //-----------------------------------

    /**
     * @brief Construct a new Logger object
     * @param filename Name of the log file
     *
     * Opens log file with given name and writes starting message
     */
    Logger(const std::string& filename);

    /**
     * @brief Logger Destructor
     *
     * Closes log file
     */
    ~Logger();

    //-----------------------------------
    //          Private methods
    //-----------------------------------

    /**
     * @brief Convert LogLevel to string
     * @param level LogLevel to convert
     * @return String representation of LogLevel
     *
     * Converts value from LogLevel enumeration to string representation
     */
    std::string levelToString(LogLevel level);

public:
    // copy and assignment not allowed
    Logger(Logger const&) = delete;
    Logger& operator=(Logger const&) = delete;

    //-----------------------------------
    //             Accessors
    //-----------------------------------

    /**
     * @brief Get instance of Logger
     * @return Pointer to Logger instance
     *
     * Get instance of Logger class
     */
    static Logger* getInstance();

    //-----------------------------------
    //             Modifiers
    //-----------------------------------

    /**
     * @brief Set logger mode
     * @param mode Mode of the logger
     *
     * Set logger mode to VERBOSE or QUIET
     */
    void setMode(Mode mode);

    //-----------------------------------
    //          Public methods
    //-----------------------------------

    /**
     * @brief Log message
     * @param level LogLevel of the message
     * @param message Message to log
     * @param source Calling function
     * @param line Line number
     *
     * Logs message with given LogLevel
     */
    void log(LogLevel level, const std::string& message, const std::string& source = "", int line = 0);
};