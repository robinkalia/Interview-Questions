// Robin Kalia
// robinkalia@berkeley.edu
//
// Full Stack Software Engineer Interview
// AiFi
//
// AiFiMessager.h: Declaration of members and methods of AiFiMessager Class for starting threads for generating message stream and sync messages

#ifndef _AIFI_FULLSTACK_INT_AIFIMESSAGER_H
#define _AIFI_FULLSTACK_INT_AIFIMESSAGER_H

#include "Streamer.h"
#include "Synchronizer.h"
#include "MessageMap.h"

#include <thread>

class AiFiMessager {
private:
    Logger log_;
    const int64_t INTERVAL_BETWEEN_THREAD_INVOCATIONS = 10;     // 10 seconds
    int64_t window_;
    int64_t numSources_;
    int64_t messageGenerationInterval_;
    int64_t syncMessageOutputInterval_;

    Streamer streamer_;
    Synchronizer synchronizer_;
    MessageMap  msgMap_;

    std::thread messageStreamGenerator_;
    std::thread syncMessageGenerator_;

    std::mutex mutex_;
    bool streamMessageFlag_;
    bool generateSyncMessageFlag_;

public:
    AiFiMessager(int64_t windowInSecs, int64_t numSources, int64_t messageGenerationInterval, int64_t syncMessageOutputInterval) :
                 messageStreamGenerator_(), syncMessageGenerator_(), streamMessageFlag_(true), generateSyncMessageFlag_(true) {
        this->window_ = windowInSecs * 1000;    // Convert it to milliseconds to match the general timestamp unit
        this->numSources_ = numSources;
        this->messageGenerationInterval_ = messageGenerationInterval;
        this->syncMessageOutputInterval_ = syncMessageOutputInterval;
    }

    ~AiFiMessager() {
    }

    void generateMessageStream();
    void generateSyncMessage();

    void start();
    void end();
};

#endif      // _AIFI_FULLSTACK_INT_AIFIMESSAGER_H