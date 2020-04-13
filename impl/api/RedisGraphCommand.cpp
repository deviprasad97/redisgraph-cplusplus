//
// Created by devi on 1/5/20.
//

#include "RedisGraphCommand.h"

const char *RedisGraphCommand::queryCommand() {
    return QUERY.c_str();
}

const char *RedisGraphCommand::deleteCommand() {
    return DELETE.c_str();
}

void RedisGraphCommand::flushCommand() {

}