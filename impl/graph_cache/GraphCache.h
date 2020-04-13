    //
// Created by devi on 1/5/20.
//

#ifndef REDISGRAPHCLINET_GRAPHCACHE_H
#define REDISGRAPHCLINET_GRAPHCACHE_H

#include <string>
#include <utility>
#include "GraphCacheList.h"
#include "../api/RedisGraph.h"

class GraphCache {
    public:
        GraphCache() = default;
        GraphCache(const std::string& graphID);
        std::string getLabel(int index, RedisGraph* redisGraph);
        std::string getRelationshipType(int index, RedisGraph* redisGraph);
        std::string getPropertyName(int index, RedisGraph* redisGraph);
    private:
        GraphCacheList _labels;
        GraphCacheList _propertyNames;
        GraphCacheList _relationshipTypes;


};




#endif //REDISGRAPHCLINET_GRAPHCACHE_H
