// Robin Kalia
// robinkalia@berkeley.edu
//
// Full Stack Software Engineer Interview
// AiFi
//
// Streamer.h: Declaration of members and methods of Streamer Class for constructing messages and adding them to a message map

#ifndef _AIFI_FULLSTACK_INT_STREAMER_H
#define _AIFI_FULLSTACK_INT_STREAMER_H

#include <stdexcept>

#include "Logger.h"
#include "MessageMap.h"

class Streamer {
private:
    int64_t numSources_;
    Logger log_;

    Message constructMessage();

public:
    Streamer(int64_t numSources = 10) {
        if (numSources < 1)     {
            std::string errMsg = "The number of sources must be between 1 and 2^64: Value provided = " + std::to_string(numSources);
            log_.debug(errMsg);
            throw std::runtime_error(errMsg);
        }

        this->numSources_ = numSources;
    }

    ~Streamer() {
    }

    void setNumSources(int64_t numSources)  {   this->numSources_ = numSources;     }  
    
    void constructAndAddMessageToMessageMap(MessageMap& messageMap);
};

#endif      //  _AIFI_FULLSTACK_INT_STREAMER_H