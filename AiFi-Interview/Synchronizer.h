// Robin Kalia
// robinkalia@berkeley.edu
//
// Full Stack Software Engineer Interview
// AiFi
//
// Synchronizer.h: Declaration of members and methods of Synchronizer Class for getting SyncMessage from messages depending upon the timestamp and time-window size

#ifndef _AIFI_FULLSTACK_INT_SYNCHRONIZER_H
#define _AIFI_FULLSTACK_INT_SYNCHRONIZER_H

#include <stdexcept>

#include "Logger.h"
#include "MessageMap.h"
#include "SyncMessage.h"

class Synchronizer {
private:
    Logger log_;

    SyncMessage getSyncMessageFromMessages(const std::vector<Message>& messages) const;

public:
    Synchronizer() {
    }

    ~Synchronizer() {
    }

    SyncMessage getSyncMessage(MessageMap& messageMap, int64_t timestamp, int64_t window) const;
};

#endif      //  _AIFI_FULLSTACK_INT_SYNCHRONIZER_H