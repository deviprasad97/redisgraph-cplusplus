//
// Created by devi on 1/5/20.
//

#include "GraphCache.h"
GraphCache::GraphCache(const std::string& graphID) {
    _labels = GraphCacheList(graphID, "db.labels");
    _propertyNames = GraphCacheList(graphID, "db.propertyKeys");
    _relationshipTypes = GraphCacheList(graphID, "db.relationshipTypes");
}

std::string GraphCache::getLabel(int index, RedisGraph* redisGraph) {
    return _labels.getCachedData(index, redisGraph);
}

std::string GraphCache::getRelationshipType(int index, RedisGraph* redisGraph) {
    return _relationshipTypes.getCachedData(index, redisGraph);
}

std::string GraphCache::getPropertyName(int index, RedisGraph* redisGraph) {
    return _propertyNames.getCachedData(index, redisGraph);
}