//
// Created by devi on 1/5/20.
//

#include <iostream>
#include "../api/RedisGraph.h"
#include "../graph_cache/GraphCache.h"
#include "ResultSet.h"


ResultSet::ResultSet(redisReply *reply){
    raw_data = std::vector<std::string>();
    graphCache = new GraphCache(redisGrpah->get_name());
    if(reply->type == REDIS_REPLY_ARRAY){
        if(reply->elements != 3)
        {
            header = nullptr;
        } else{
            parse_header(reply->element[0]);
            parse_result(reply->element[1]);
        }
    }
}

ResultSet::ResultSet(redisReply *reply, void *_redisGrpah){
    redisGrpah = reinterpret_cast<RedisGraph *>(_redisGrpah);
    raw_data = std::vector<std::string>();
    graphCache = new GraphCache(redisGrpah->get_name());
    if(reply->type == REDIS_REPLY_ARRAY){
        if(reply->elements != 3)
        {
            header = nullptr;
            statisticsImp = parse_stats(reply->element[0]);
        } else{
            parse_header(reply->element[0]);
            parse_result(reply->element[1]);
            statisticsImp = parse_stats(reply->element[2]);
        }
    }
}

int ResultSet::size() {
    raw_data.size();
    return 0;
}

StatisticsImp* ResultSet::getStatistics() {
    return statisticsImp;
}

Header* ResultSet::getHeader() {
    return header;
}
void ResultSet::parse_helper(redisReply *reply) {
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

        raw_data.push_back(data_string);
    }
    num_elements = reply->elements;

    for(int i=0; i<num_elements; i++){
        parse_result(reply->element[i]);
    }
}

void ResultSet::parse_result(redisReply *reply) {
    // reply contains all the node and edge data in it: num element == 1
    for(int i=0; i<reply->element[0]->elements; i++)
    {
        if(header->getSchemaTypes().at(i) == Header::COLUMN_NODE){
            deserialize_node(reply->element[0]->element[i]);
        }
        else if(header->getSchemaTypes().at(i) == Header::COLUMN_RELATION){
            deserialize_edge(reply->element[0]->element[i]);
        }
        else if(header->getSchemaTypes().at(i) == Header::COLUMN_SCALAR){
            deserialize_scalar(reply->element[0]->element[i]);
        }
    }
}

std::vector<std::string> ResultSet::get_raw_result() {
    return raw_data;
}

void ResultSet::parse_header(redisReply *reply) {
    header = new Header(reply);
}

ResultSet::~ResultSet() {
    delete header;
    delete redisGrpah;
    delete graphCache;
    delete statisticsImp;
}

Node* ResultSet::deserialize_node(redisReply *rawNodeData) {
    /**
        # Node ID (integer),
        # [label string offset (integer)],
        # [[name, value type, value] X N]
    **/
    Node *node = new Node();
    deserialize_graph_entity_id(node, rawNodeData->element[0]);
    int label_index = (int) rawNodeData->element[1]->element[0]->integer;
    node->addLabel(graphCache->getLabel(label_index, redisGrpah));
    deserialize_graph_entity_properties(node, rawNodeData->element[2]);

    return node;
}

Edge* ResultSet::deserialize_edge(redisReply *rawEdgeData) {
    /**
     *
     * [
            Relation ID (integer),
            type ID (integer),
            source node ID (integer),
            destination node ID (integer),
            [[property key ID (integer), PropertyType (enum), value (scalar)] X property count]
        ]
     */
     Edge *edge = new Edge();
     deserialize_graph_entity_id(edge, rawEdgeData->element[0]);
     graphCache->getRelationshipType(rawEdgeData->element[1]->integer, redisGrpah);
     edge->setSource(rawEdgeData->element[2]->integer);
     edge->setDestination(rawEdgeData->element[3]->integer);
     deserialize_graph_entity_properties(edge, rawEdgeData->element[4]);

     return edge;
}

void *ResultSet::deserialize_scalar(redisReply *rawScalarData) {
    return nullptr;
}

void ResultSet::deserialize_graph_entity_id(GraphEntity *graphEntity, redisReply *rawEntityID) {
    graphEntity->setId((int)rawEntityID->integer);
}
void ResultSet::deserialize_graph_entity_properties(GraphEntity *graphEntity, redisReply *rawEntityID) {
    /**
     * # [[property key, value type, value] X N]
     */
     std::map<std::string, Any> properties;
     for(int i=0; i<rawEntityID->elements; i++) {
         Any any;
         auto property = rawEntityID->element[i]; // This contains [property key, value type, value]
         int property_name_int = property->element[0]->integer;
         int property_value_type = property->element[1]->integer;
         std::string property_key = graphCache->getPropertyName(i, redisGrpah);
         switch (property_value_type)
         {
             case ResultSet::PROPERTY_INTEGER:
                any.type = ResultSet::PROPERTY_INTEGER;
                any.int_data = property->element[2]->integer;
                break;
             case ResultSet::PROPERTY_STRING:
                 any.type = ResultSet::PROPERTY_STRING;
                 any.string_data = property->element[2]->str;
                 break;
             case ResultSet::PROPERTY_DOUBLE:
                 any.type = ResultSet::PROPERTY_DOUBLE;
                 any.double_data =  property->element[2]->dval;
                 break;
         }
         properties.insert(std::pair<std::string, Any>(property_key, any));
         graphEntity->addProperty(property_key, any);
     }
}

StatisticsImp* ResultSet::parse_stats(redisReply *reply) {
    return new StatisticsImp(reply);
}






