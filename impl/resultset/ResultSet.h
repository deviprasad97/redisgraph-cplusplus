//
// Created by devi on 1/5/20.
//

#ifndef REDISGRAPHCLINET_RESULTSETIMPL_H
#define REDISGRAPHCLINET_RESULTSETIMPL_H


#include <map>
#include "../../graph_entities/Node.h"
#include "../../graph_entities/Edge.h"
#include "Header.h"
#include "StatisticsImp.h"
#include <hiredis/hiredis.h>
#include "../../graph_entities/Property.h"
class GraphCache;
class RedisGraph;

class ResultSet{
    public:
        ResultSet() = default;
        explicit ResultSet(redisReply *reply);
        ResultSet(redisReply *reply, void *_redisGrpah);
        ~ResultSet();
        ResultSet(const ResultSet &p2) { raw_data = p2.raw_data;}
        int size();
        StatisticsImp* getStatistics();
        Header* getHeader();
        std::vector<std::string> get_raw_result();
        enum PropertyType{
            PROPERTY_UNKNOWN = 0,
            PROPERTY_NULL = 1,
            PROPERTY_STRING = 2,
            PROPERTY_INTEGER = 3,
            PROPERTY_BOOLEAN = 4,
            PROPERTY_DOUBLE = 5,
        } PropertyTypeUser;

    private:
        void parse_helper(redisReply* reply);
        void parse_header(redisReply *reply);
        void parse_result(redisReply *reply);
        StatisticsImp* parse_stats(redisReply *reply);
        Node* deserialize_node(redisReply *rawNodeData);
        Edge* deserialize_edge(redisReply *rawEdgeData);
        void* deserialize_scalar(redisReply *rawScalarData);
        static void deserialize_graph_entity_id(GraphEntity *graphEntity, redisReply* rawEntityID);
        void deserialize_graph_entity_properties(GraphEntity *graphEntity, redisReply* rawEntityID);
        std::vector<std::string> raw_data;
        void *graph;
        Header *header = nullptr;
        RedisGraph *redisGrpah;
        GraphCache *graphCache;
        StatisticsImp *statisticsImp;
//        std::vector<std::string> result;
//        std::map<std::string, std::string> resutlSet;


    /**
     * TODO:: RESULTSETIMPL
     */
        //const Header header;

};


#endif //REDISGRAPHCLINET_RESULTSETIMPL_H
