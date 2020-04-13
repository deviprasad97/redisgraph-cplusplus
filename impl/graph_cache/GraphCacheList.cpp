//
// Created by devi on 1/5/20.
//

#include "GraphCacheList.h"

#include <utility>
#include <iostream>

GraphCacheList::GraphCacheList(std::string graphID, std::string procedure) {
    _graphID = std::move(graphID);
    _procedure = std::move(procedure);

}

std::string GraphCacheList::getCachedData(int index, RedisGraph* redisGraph) {
    if (index >= _data.size())
    {
        getProcedureInfo(redisGraph);
    }
    return _data[index];
}

void GraphCacheList::parse_helper(redisReply *reply) {
    int num_elements = 0;
    if(reply->element == nullptr)
    {
        std::string data_string;
        if(reply->type == REDIS_REPLY_INTEGER){
            data_string = std::to_string(reply->integer);
        }
        else{
            data_string = reply->str;
        }

        _data.push_back(data_string);
    }
    num_elements = reply->elements;

    for(int i=0; i<num_elements; i++){
        parse_helper(reply->element[i]);
    }
}

void GraphCacheList::getProcedureInfo(RedisGraph* redisGraph) {
    redisReply *result;
    redisGraph->call_procedure(_procedure, &result);
    auto all_labels = result->element[1];
    parse_helper(all_labels);
//    freeReplyObject(all_labels);
//    freeReplyObject(result);
}

GraphCacheList::GraphCacheList() {}
