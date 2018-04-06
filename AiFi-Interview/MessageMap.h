// Robin Kalia
// robinkalia@berkeley.edu
//
// Full Stack Software Engineer Interview
// AiFi
//
// MessageMap.h: A thread safe Message Map that stores elements as per their timestamp

#ifndef _AIFI_FULLSTACK_INT_MESSAGEMAP_H
#define _AIFI_FULLSTACK_INT_MESSAGEMAP_H

#include "Message.h"
#include <map>

class MessageMap
{
private:
    std::mutex mutex_;
    std::map<int64_t, Message> timestampSortedMessageMap_;

public:
    MessageMap(){
    }

    ~MessageMap() {
        std::lock_guard<std::mutex> lock(mutex_);
        this->timestampSortedMessageMap_.clear();
    }

    void insertMessage(Message msg) {
        std::lock_guard<std::mutex> lock(mutex_);
        timestampSortedMessageMap_[msg.timestamp()] = msg;
    }

    std::vector<Message> getMessagesWithinTimeInterval(int64_t startingTimestamp, int64_t endingTimestamp)  {
        std::vector<Message> messages;
        {
            std::lock_guard<std::mutex> lock(mutex_);
            for (const auto& elem : this->timestampSortedMessageMap_) {
                if (elem.first < startingTimestamp)  continue;
                if (elem.first > endingTimestamp)    break;
                messages.push_back(elem.second);
            }
        }
        return messages;
    }
};

#endif      // _AIFI_FULLSTACK_INT_MESSAGEMAP_H