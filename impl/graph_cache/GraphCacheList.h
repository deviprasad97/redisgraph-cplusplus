//
// Created by devi on 1/5/20.
//

#ifndef REDISGRAPHCLINET_GRAPHCACHELIST_H
#define REDISGRAPHCLINET_GRAPHCACHELIST_H


#include <string>
#include <vector>
#include "../api/RedisGraph.h"

class GraphCacheList {
    public:
        GraphCacheList(std::string graphID, std::string procedure);
        GraphCacheList();

        std::string getCachedData(int index, RedisGraph* redisGraph);
        void getProcedureInfo(RedisGraph* redisGraph);
        void parse_helper(redisReply *reply);

    private:
        std::string _graphID;
        std::string _procedure;
        std::vector<std::string> _data;
};


#endif //REDISGRAPHCLINET_GRAPHCACHELIST_H
