//
// Created by devi on 1/5/20.
//

#include "RedisGraphCaches.h"

#include <utility>

GraphCache RedisGraphCaches::getGraphCache() {
    return graphCaches;
}

std::string RedisGraphCaches::getLabel(std::string graphID, int index, RedisGraph* redisGraph) {
    return getGraphCache().getLabel(index, redisGraph);
}

std::string RedisGraphCaches::getRelationshipType(std::string graphID, int index, RedisGraph* redisGraph) {
    return getGraphCache().getRelationshipType(index, redisGraph);
}

std::string RedisGraphCaches::getPropertyName(std::string graphID, int index, RedisGraph* redisGraph) {
    return getGraphCache().getPropertyName(index, redisGraph);
}

//void RedisGraphCaches::removeGraphCache(const std::string& graphID) {
//    graphCaches.erase(graphID);
//}
