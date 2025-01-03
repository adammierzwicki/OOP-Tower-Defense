#include "../inc/logger.h"

#include <ctime>
#include <iostream>
#include <sstream>

//-----------------------------------
//     Constructor and destructor
//-----------------------------------

Logger::Logger(const std::string& filename) {
    logFile.open(filename, std::ios::trunc);
    if (!logFile.is_open()) {
        throw std::runtime_error("Cannot opening log file.");
    }
}

Logger::~Logger() { logFile.close(); }

//-----------------------------------
//          Private methods
//-----------------------------------

std::string Logger::levelToString(LogLevel level) {
    switch (level) {
    case DEBUG:
        return "DEBUG";
    case INFO:
        return "INFO";
    case WARNING:
        return "WARNING";
    case ERROR:
        return "ERROR";
    case CRITICAL:
        return "CRITICAL";
    default:
        return "UNKNOWN";
    }
}

//-----------------------------------
//             Accessors
//-----------------------------------

Logger* Logger::getInstance() {
    if (!instance) {
        instance = new Logger("logfile.txt");
    }
    return instance;
}

//-----------------------------------
//             Modifiers
//-----------------------------------

void Logger::setMode(Mode mode) {
    this->mode = mode; 
}

//-----------------------------------
//          Public methods
//-----------------------------------

void Logger::log(LogLevel level, const std::string& message, const std::string& source, int line) {
    time_t now = time(0);
    tm* timeinfo = localtime(&now);
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp),
        "%Y-%m-%d %H:%M:%S", timeinfo);

    std::ostringstream logEntry;
    logEntry << "[" << timestamp << "] " << levelToString(level) << ": " << message;

    if (source != "") {
        logEntry << " (" << source << ":" << line << ")";
    }

    logEntry << std::endl;
    
    if (mode == VERBOSE || level == INFO || level == CRITICAL) {
        std::cout << logEntry.str();
        std::flush(std::cout);
    }

    if (logFile.is_open()) {
        logFile << logEntry.str();
        logFile.flush(); // immediate write
    }
}

Logger* Logger::instance = nullptr;