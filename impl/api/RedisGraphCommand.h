//
// Created by devi on 1/5/20.
//

#ifndef REDISGRAPHCLINET_REDISGRAPHCOMMAND_H
#define REDISGRAPHCLINET_REDISGRAPHCOMMAND_H


#include <string>
class RedisGraphCommand {
    std::string QUERY = "GRAPH.QUERY";
    std::string DELETE = "GRAPH.DELETE";
    const char* queryCommand();
    const char* deleteCommand();
    void flushCommand();
};


#endif //REDISGRAPHCLINET_REDISGRAPHCOMMAND_H
