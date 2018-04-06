// Robin Kalia
// robinkalia@berkeley.edu
//
// Full Stack Software Engineer Interview
// AiFi
//
// Synchronizer.cpp: Definition of members and methods of Synchronizer Class for getting SyncMessage from messages depending upon the timestamp and time-window size

#include "Synchronizer.h"
#include <set>

SyncMessage Synchronizer::getSyncMessage(MessageMap& messageMap, int64_t timestamp, int64_t window) const {
    int64_t startTimestamp = timestamp - window;
    startTimestamp = (startTimestamp < 0) ? 0 : startTimestamp;
    int64_t endingTimestamp = timestamp + window;

    std::vector<Message> messages = messageMap.getMessagesWithinTimeInterval(startTimestamp, endingTimestamp);
    SyncMessage syncMessage = getSyncMessageFromMessages(messages);

    return syncMessage;
}


SyncMessage Synchronizer::getSyncMessageFromMessages(const std::vector<Message>& messages) const {
    std::set<int64_t> parsedMessageSources;

    SyncMessage syncMessage;
    for (const auto& elem: messages) {
        if (parsedMessageSources.count(elem.source()))    continue;
        parsedMessageSources.insert(elem.source());
        syncMessage.addTimestampAndMessage(elem.timestamp(), elem);
    }

    return syncMessage;
}