// Robin Kalia
// robinkalia@berkeley.edu
//
// Full Stack Software Engineer Interview
// AiFi
//
// Message.h: Basic message data structure containing the identity of messages

#ifndef _AIFI_FULLSTACK_INT_MESSAGE_H
#define _AIFI_FULLSTACK_INT_MESSAGE_H

#include <iostream>
#include <stdint.h>

#include <vector>

class Message {
private:
    int64_t timestamp_;
    std::vector<uint8_t> body_;
    int64_t source_;

public:
    Message(int64_t timestamp = -1, const std::vector<uint8_t>& body = std::vector<uint8_t>(0), int64_t source = -1) {
        this->timestamp_ = timestamp;
        this->body_ = body;
        this->source_ = source;
    }

    ~Message() {
        this->body_.clear();
    }

    Message& operator=(const Message& msg) {
        this->timestamp_ = msg.timestamp();
        this->body_      = msg.body();
        this->source_    = msg.source();

        return *this;
    }

    // I only provide getters and no setters since I want the source creating the message
    // to provide those parameters in the constructors while instantiating a Message object

    // Getters
    int64_t timestamp()         const   {   return this->timestamp_;    }
    std::vector<uint8_t> body() const   {   return this->body_;         }
    int64_t source()            const   {   return this->source_;       }
    std::string message()       const   {   return std::string("\nTimestamp: " + std::to_string(this->timestamp_) + "\nSource: " + std::to_string(this->source_) + "\nBody(Len=" +
                                                   std::to_string(this->body_.size()) + "): \"" + std::string(this->body_.begin(), this->body_.end())) + "\"";
    }
};

#endif      // _AIFI_FULLSTACK_INT_MESSAGE_H