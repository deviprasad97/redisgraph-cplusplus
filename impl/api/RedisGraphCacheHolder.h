//
// Created by devi on 1/5/20.
//

#ifndef REDISGRAPHCLINET_REDISGRAPHCACHEHOLDER_H
#define REDISGRAPHCLINET_REDISGRAPHCACHEHOLDER_H

#include "../graph_cache/RedisGraphCaches.h"
class RedisGraphCacheHolder {
    public:
        //virtual void setRedisGraphCaches(RedisGraphCaches caches) = 0;
    private:
        ResultSet *resultSet;                           // Class contains formatted results
        static std::vector<std::string> _labels;               // contains all labels of the graph
        static std::vector<std::string> _properties;           // contains all properties keys of the graph
        static std::vector<std::string> _relationshipTypes;    // contains all the realationsip types of the graph
};


#endif //REDISGRAPHCLINET_REDISGRAPHCACHEHOLDER_H
