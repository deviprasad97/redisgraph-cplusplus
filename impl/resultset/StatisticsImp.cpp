//
// Created by devi on 1/5/20.
//

#include <sstream>
#include <vector>
#include "StatisticsImp.h"

StatisticsImp::StatisticsImp(redisReply *_reply) {
    reply = _reply;
    get_statistics();
}

int StatisticsImp::nodesCreated() {
    return getIntValue(NODES_CREATED);
}

int StatisticsImp::nodesDeleted() {
    return getIntValue(NODES_DELETED);
}

int StatisticsImp::indicesAdded() {
    return getIntValue(INDICES_ADDED);
}

int StatisticsImp::indicesDeleted() {
    return getIntValue(INDICES_DELETED);
}

int StatisticsImp::labelsAdded() {
    return getIntValue(LABELS_ADDED);
}

int StatisticsImp::relationshipsDeleted() {
    return getIntValue(RELATIONSHIPS_DELETED);
}

int StatisticsImp::relationshipsCreated() {
    return getIntValue(RELATIONSHIPS_CREATED);
}

int StatisticsImp::propertiesSet() {
    return getIntValue(PROPERTIES_SET);
}
int StatisticsImp::getIntValue(Labels label){
    std::string value = getStringValue(label);
    std::stringstream parse(value);
    int temp_value = 90843064;
    parse >> temp_value;
    if (temp_value == 90843064)
    {
        return -1;
    } else{
        return temp_value;
    }
}

std::string StatisticsImp::getStringValue(Labels label) {
    return statistics.at(label);
}

std::map<Statistics::Labels, std::string> StatisticsImp::get_statistics() {

    for(int i=0; i<reply->elements; i++)
    {   std::vector<std::string> chunks;
        std::stringstream ss(reply->element[i]->str);
        std::string token;
        while(std::getline(ss, token, ':'))
        {
            chunks.push_back(token);
        }
        std::string temp = chunks[1];
        statistics.insert(std::pair<Labels, std::string>(getLabel(chunks[0]), chunks[1]));
    }
    return statistics;
}
