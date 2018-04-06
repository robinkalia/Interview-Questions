// Robin Kalia
// robinkalia@berkeley.edu
//
// Full Stack Software Engineer Interview
// AiFi
//
// Streamer.cpp: Definition of members and methods of Streamer Class for constructing messages and adding them to message map

#include "Streamer.h"
#include <chrono>

Message Streamer::constructMessage() {
    int64_t timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    srand(time(nullptr));
    int64_t source = (rand() + timestamp) % this->numSources_;
    int64_t messageLen = ((rand() + timestamp)%(1<<8)) + 1;
    std::vector<uint8_t> body;
    for (int64_t i=0; i<messageLen; ++i) {
        uint8_t singleChar = rand()%(1<<7);
        singleChar = (singleChar < 33) ? (singleChar+33) : 0;
        singleChar = (singleChar == 0) ? 1 : singleChar;
        body.push_back(singleChar);
    }

    Message msg(timestamp, body, source);
    return msg;
}


void Streamer::constructAndAddMessageToMessageMap(MessageMap& messageMap) {
    Message msg = constructMessage();
    log_.debug("Generated Message" + msg.message() + "\n");
    messageMap.insertMessage(msg);
}