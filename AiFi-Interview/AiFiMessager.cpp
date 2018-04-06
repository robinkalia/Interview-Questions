// Robin Kalia
// robinkalia@berkeley.edu
//
// Full Stack Software Engineer Interview
// AiFi
//
// AiFiMessager.cpp: Definition of members and methods of AiFiMessager Class for starting threads for generating message stream and sync messages

#include "AiFiMessager.h"

void AiFiMessager::generateMessageStream() {
    bool generateMessageStreamFlag = true;
    try {
        while(generateMessageStreamFlag) {
            std::this_thread::sleep_for(std::chrono::seconds(this->messageGenerationInterval_));
            this->streamer_.constructAndAddMessageToMessageMap(this->msgMap_);
            {
                std::lock_guard<std::mutex> lock(this->mutex_);
                generateMessageStreamFlag = this->streamMessageFlag_;
            }
        }
    } catch (const std::exception& ex) {
        log_.error("Error thrown in AiFiMessager::generateMessageStream() method: " + std::string(ex.what()));
    }
}

void AiFiMessager::generateSyncMessage() {
    bool generateSyncMessageFlag = true;
    try {
        while(generateSyncMessageFlag) {
            std::this_thread::sleep_for(std::chrono::seconds(this->syncMessageOutputInterval_));
            int64_t timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            SyncMessage syncMessage = this->synchronizer_.getSyncMessage(this->msgMap_, timestamp, this->window_);
            log_.info("Sync Message: " + syncMessage.syncMessage());
            {
                std::lock_guard<std::mutex> lock(this->mutex_);
                generateSyncMessageFlag = this->generateSyncMessageFlag_;
            }
        }
    } catch (const std::exception& ex) {
        log_.error("Error thrown in AiFiMessager::generateSyncMessage() method: " + std::string(ex.what()));
    }
}

void AiFiMessager::start() {
    this->messageStreamGenerator_ = std::thread(&AiFiMessager::generateMessageStream, this);
    std::this_thread::sleep_for(std::chrono::seconds(this->INTERVAL_BETWEEN_THREAD_INVOCATIONS));
    this->syncMessageGenerator_ = std::thread(&AiFiMessager::generateSyncMessage, this);
}

void AiFiMessager::end() {
    std::lock_guard<std::mutex> lock(this->mutex_);
    this->streamMessageFlag_ = false;
    this->generateSyncMessageFlag_ = false;
}