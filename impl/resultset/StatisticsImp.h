//
// Created by devi on 1/5/20.
//

#ifndef REDISGRAPHCLINET_STATISTICSIMP_H
#define REDISGRAPHCLINET_STATISTICSIMP_H

#include <hiredis/hiredis.h>
#include <map>
#include "../../Statistics.h"
#include "../utils.h"

class StatisticsImp: public Statistics {
public:
    StatisticsImp() = default;
    StatisticsImp(redisReply *_reply);
    std::string getStringValue(Labels label) override ;
    int nodesCreated() override ;

    int nodesDeleted() override ;

    int indicesAdded() override ;

    int indicesDeleted() override;

    int labelsAdded() override ;

    int relationshipsDeleted() override;

    int relationshipsCreated()  override ;

    int propertiesSet()  override;
    int getIntValue(Labels label);
    std::map<Labels, std::string> get_statistics();

private:
    std::map<Labels, std::string> statistics;
    redisReply *reply;
};


#endif //REDISGRAPHCLINET_STATISTICSIMP_H
