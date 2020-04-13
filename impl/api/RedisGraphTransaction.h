//
// Created by devi on 1/5/20.
//

#ifndef REDISGRAPHCLINET_REDISGRAPHTRANSACTION_H
#define REDISGRAPHCLINET_REDISGRAPHTRANSACTION_H



#include "RedisGraphCacheHolder.h"
/**
 * TODO:: This to be implemented in version 2.
 * This will inherit from RedisGraphTransaction and implement it
 * Will also need to inherit form RedisGraph
 * This will become a the main driver
 */

class RedisGraphTransaction : public RedisGraphCacheHolder {
    public:
        //void setRedisGraphCaches(RedisGraphCaches caches) override ;
    private:
        RedisGraphCaches _caches;
        RedisGraph redisGraph;
};


#endif //REDISGRAPHCLINET_REDISGRAPHTRANSACTION_H
