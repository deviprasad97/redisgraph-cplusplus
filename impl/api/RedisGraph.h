//
// Created by devi on 1/5/20.
//

#ifndef REDISGRAPHCLINET_REDISGRAPH_H
#define REDISGRAPHCLINET_REDISGRAPH_H


#include <string>
#include <hiredis/hiredis.h>
#include "../../RedisGraphContext.h"
#include "../resultset/ResultSet.h"
#include "../utils.h"
#include <deque>

class RedisGraph {
    public:
        RedisGraph(std::string host, int port);
        RedisGraph() : RedisGraph("localhost", 6379) { };
        ~RedisGraph();

        void set_graph(std::string _name);

        static std::string get_args_formated(char **argv);

        ResultSet** query(std::string query);
        ResultSet** query(std::string graphID, std::string query);
        ResultSet* query(std::string graphID, std::string query, char **argv=nullptr);
        ResultSet* query(std::string graphID, std::string query, std::map<std::string, std::string> property);

        /**
         * Following the guidelines of radisgraph Procedure calls are implemented
         * to map index to actual value
         * @param procedure
         * @return
         */
        void call_procedure(const std::string& procedure, redisReply**);
//        ResultSet** labels();
//        ResultSet** relationship_type();
//        ResultSet** property_keys();

//        std::string get_label(int index);
//        std::string get_relation(int index);
//        std::string get_property(int index);

        std::string get_name();
        ResultSet getResultSet();
        std::vector<std::string> get_raw_data();

        RedisGraphContext getContext(); // TODO:: IMPLEMENT THIS AFTER REDISGRAPHCONTEXT is done

        void close();
        void flush();
        void commit();
        void load_graph();
        void save_graph();
        void deleteGraph(std::string graphID);
    private:
        // Only to be use internally to make the actual quey given the graph name and
        // properly formatted query string
        ResultSet** sendQuery(std::string graphID, std::string query);

        struct timeval timeout = { 1, 500000 }; // 1.5 seconds
        redisContext *c;                                // Redis graph object
        redisReply *reply;                              // struct that contains reply received from redis graph
        redisReply *reply_compact;                              // struct that contains reply received from redis graph

        ResultSet *resultSet;                           // Class contains formatted results
        std::map<int, Node> nodes;                      // map containing all node with id as their keys
        std::vector<Edge> edges;                        // map containing all edges with id as their keys
        std::vector<std::string> _labels;               // contains all labels of the graph
        std::vector<std::string> _properties;           // contains all properties keys of the graph
        std::vector<std::string> _relationshipTypes;    // contains all the realationsip types of the graph
        std::string name;                               // graph name
        std::deque<std::string> history;



};


#endif //REDISGRAPHCLINET_REDISGRAPH_H
