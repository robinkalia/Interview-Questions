// Robin Kalia
// robinkalia@berkeley.edu
//
// Full Stack Software Engineer Interview
// AiFi
//
// Logger.h: A very simple and basic logger for displaying logs for just 4 levels: INFO, DEBUG, WARN, ERROR
// Again, a very simple and basic logger that does not take thread safety into consideration

#ifndef _AIFI_FULLSTACK_INT_LOGGER_H
#define _AIFI_FULLSTACK_INT_LOGGER_H

#include <iostream>
#include <stdint.h>

#include <time.h>

class Logger {
private:
    time_t rawtime;
    struct tm *timeinfo;

    std::string getLocalTime() {
        timeinfo = nullptr;
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        return std::string(asctime(timeinfo));
    }

    void logMessage(const std::string& message, bool errFlag = false) {
        std::string localTime = this->getLocalTime();
        localTime.erase(std::remove(localTime.begin(), localTime.end(), '\n'), localTime.end());
        if (!errFlag)
            std::cout << localTime << ":: " << message << std::endl;
        else
            std::cerr << localTime << ":: " << message << std::endl;
    }

public:
    static bool DEBUG_FLAG_;
    static bool WARN_FLAG_;

    Logger() {
    }

    ~Logger() {
    }

    void info(const std::string& message) {
        this->logMessage(message);
    }

    void error(const std::string& message) {
        this->logMessage(message, true);
    }

    void warn(const std::string& message) {
        if (WARN_FLAG_)      this->logMessage(message);
    }

    void debug(const std::string& message) {
        if (DEBUG_FLAG_)     this->logMessage(message);
    }
};

#endif      // _AIFI_FULLSTACK_INT_LOGGER_H