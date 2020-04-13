cmake_minimum_required(VERSION 3.15)
project(phClinet)

set(CMAKE_CXX_STANDARD 11)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(redisGraphClinet main.cpp graph_entities/Edge.cpp graph_entities/Edge.h graph_entities/GraphEntity.cpp graph_entities/GraphEntity.h graph_entities/Node.cpp graph_entities/Node.h graph_entities/Path.cpp graph_entities/Path.h graph_entities/Property.cpp graph_entities/Property.h Record.cpp Record.h RedisGraphContext.cpp RedisGraphContext.h RedisGraphContextGenerator.cpp RedisGraphContextGenerator.h RedisGraphTransaction.cpp RedisGraphTransaction.h Statistics.cpp Statistics.h impl/utils.cpp impl/utils.h impl/api/AbstractRedisGraph.cpp impl/api/AbstractRedisGraph.h impl/api/ContextedRedisGraph.cpp impl/api/ContextedRedisGraph.h impl/api/RedisGraph.cpp impl/api/RedisGraph.h impl/api/RedisGraphCacheHolder.cpp impl/api/RedisGraphCacheHolder.h impl/api/RedisGraphCommand.cpp impl/api/RedisGraphCommand.h impl/api/RedisGraphTransaction.cpp impl/api/RedisGraphTransaction.h impl/graph_cache/GraphCache.cpp impl/graph_cache/GraphCache.h impl/graph_cache/GraphCacheList.cpp impl/graph_cache/GraphCacheList.h impl/graph_cache/RedisGraphCaches.cpp impl/graph_cache/RedisGraphCaches.h impl/resultset/Header.cpp impl/resultset/Header.h impl/resultset/RecordImpl.cpp impl/resultset/RecordImpl.h impl/resultset/ResultSet.cpp impl/resultset/ResultSet.h impl/resultset/ResultSetScalarTypes.cpp impl/resultset/ResultSetScalarTypes.h impl/resultset/StatisticsImp.cpp impl/resultset/StatisticsImp.h)
TARGET_LINK_LIBRARIES(redisGraphClinet hiredis ${Boost_LIBRARIES})