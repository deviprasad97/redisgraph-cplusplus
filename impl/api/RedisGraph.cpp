//
// Created by devi on 1/5/20.
//

#include <sstream>
#include <utility>
#include <iostream>
#include <deque>
#include "RedisGraph.h"
#include "../graph_cache/GraphCache.h"

RedisGraph::RedisGraph(std::string host, int port) {
    c = redisConnectWithTimeout(host.c_str(), port, timeout);
    if (c == nullptr || c->err) {
        if (c) {
            printf("Connection error: %s\n", c->errstr);
            redisFree(c);
        } else {
            printf("Connection error: can't allocate redis context\n");
        }
        exit(1);
    }
}

void RedisGraph::close() {
    redisFree(c);
}

void RedisGraph::deleteGraph(std::string graphID) {
        std::string deleteCommand = "GRAPH.DELETE %s";
        reply = (redisReply*) redisCommand(c, deleteCommand.c_str(), graphID.c_str());
        freeReplyObject(reply);
}

// Getters
ResultSet RedisGraph::getResultSet()
{
    return *resultSet;
}

std::vector<std::string> RedisGraph::get_raw_data()
{
    return resultSet->get_raw_result();
}

// Setters
void RedisGraph::set_graph(std::string _name) {
    name = _name;
    return;
}


// Query Functions implementation
std::string RedisGraph::get_args_formated(char **argv)
{
    std::string arguments;
    /**
     * TODO:: WILL HAVE TO FORMULATE HOW TO ARGUMENTS SHOULD LOOK LIKE
     *        AND HOW TO PARSE THEM
     */
    return arguments;
}

ResultSet** RedisGraph::sendQuery(std::string graphID, std::string query) {
    if(history.size() == 50)
        history.pop_back();
    history.push_back(query);
    reply = (redisReply*) redisCommand(c, "GRAPH.QUERY %s %s %s", name.c_str(), query.c_str(), "--compact");
    resultSet = new ResultSet(reply, this);
    return &resultSet;
}

ResultSet** RedisGraph::query(std::string graphID, std::string query) {
    return sendQuery(std::move(graphID), std::move(query));
}


ResultSet** RedisGraph::query(std::string query) {
    return sendQuery(name, query);
}

void RedisGraph::commit() {
    if(nodes.size() == 0 || edges.size() == 0)
    {
        return;
    }
    std::stringstream query_stream;
    query_stream<< "CREATE ";
    for(std::map<int, Node>::const_iterator it = nodes.begin(); it != nodes.end(); ++it){
        query_stream<<it->second <<",";
    }
    for(std::vector<Edge>::const_iterator it = edges.begin(); it != edges.end(); ++it){
        query_stream<<it.base()<<",";
    }
    query(query_stream.str());
}


RedisGraphContext RedisGraph::getContext() {
    return RedisGraphContext();
}

std::string RedisGraph::get_name() {
    return name;
}

// Procedure calls

void RedisGraph::call_procedure(const std::string& procedure, redisReply** reply1)
{
    // GRAPH.QUERY Test "CALL db.labels()"
    std::stringstream procedure_stream;
    procedure_stream<<"CALL "<<procedure;
    char temp[1000];
    sprintf(temp, "GRAPH.QUERY %s %s", name.c_str(), procedure_stream.str().c_str());
    std::string q = temp;
    *reply1 = (redisReply*) redisCommand(c, "GRAPH.QUERY %s %s", name.c_str(), procedure_stream.str().c_str());
    std::cout<<"debug\n";
}

void RedisGraph::flush() {

}

RedisGraph::~RedisGraph() {
    close();
    delete resultSet;
    freeReplyObject(reply);
    freeReplyObject(reply_compact);
}