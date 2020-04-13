//
// Created by devi on 1/5/20.
//

#ifndef REDISGRAPHCLINET_REDISGRAPHCACHES_H
#define REDISGRAPHCLINET_REDISGRAPHCACHES_H


#include <map>
#include "GraphCache.h"

class RedisGraphCaches {
    public:
        GraphCache getGraphCache();
        std::string getLabel(std::string graphID, int index, RedisGraph* redisGraph);
        std::string getRelationshipType(std::string graphID, int index, RedisGraph* redisGraph);
        std::string getPropertyName(std::string graphID, int index, RedisGraph* redisGraph);
        void removeGraphCache(const std::string& graphID);
    private:
        GraphCache graphCaches;
};


#endif //REDISGRAPHCLINET_REDISGRAPHCACHES_H
