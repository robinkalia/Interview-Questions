// Robin Kalia
// robinkalia@berkeley.edu
//
// Full Stack Software Engineer Interview
// AiFi
//
// SynchedMessage.h: Message data structure that is returned by Synchronizer

#ifndef _AIFI_FULLSTACK_INT_SYNCMESSAGE_H
#define _AIFI_FULLSTACK_INT_SYNCMESSAGE_H

#include <iostream>
#include "Message.h"

class SyncMessage {
private:
    std::vector<int64_t> timestamps_;
    std::vector<Message> messages_;

public:
    SyncMessage(const std::vector<int64_t>& timeStamps = std::vector<int64_t>(0), const std::vector<Message>& messages = std::vector<Message>(0)) {
        this->timestamps_ = timeStamps;
        this->messages_ = messages;
    }

    ~SyncMessage() {
        this->timestamps_.clear();
        this->messages_.clear();
    }

    SyncMessage& operator=(const SyncMessage& syncMsg) {
        this->timestamps_ = syncMsg.timestamps();
        this->messages_ = syncMsg.messages();

        return *this;
    }

    // Setters
    void addTimestamp(int64_t timestamp)    {   this->timestamps_.push_back(timestamp);     }
    void addMessage(const Message& message) {   this->messages_.push_back(message);         }
    void addTimestampAndMessage(int64_t timestamp, const Message& message) {
        this->timestamps_.push_back(timestamp);
        this->messages_.push_back(message);
    }

    // Getters
    std::vector<int64_t> timestamps()   const   {   return this->timestamps_;         }
    std::vector<Message> messages()     const   {   return this->messages_;           }
    int64_t timestamp(int32_t index)    const   {   return this->timestamps_[index];  }
    Message message(int32_t index)      const   {   return this->messages_[index];    }
    std::string syncMessage()           const   {
        std::string syncMsg;
        syncMsg = "\nTimestamps = [  ";
        for (const auto &elem : this->timestamps_) {
            syncMsg += std::to_string(elem) + "  ";
        }
        syncMsg += "]\nSources = [  ";
        for (const auto &elem : this->messages_) {
            syncMsg += std::to_string(elem.source()) + "  ";
        }
        syncMsg += "]\n";
        return syncMsg;
    }
};

#endif      // _AIFI_FULLSTACK_INT_SYNCMESSAGE_H