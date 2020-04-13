//
// Created by devi on 1/5/20.
//

#ifndef REDISGRAPHCLINET_UTILS_H
#define REDISGRAPHCLINET_UTILS_H


#include <vector>
#include <string>
#include <map>
#include <hiredis/hiredis.h>
#include <algorithm>
#include <cctype>
#include <locale>


class utils {
    public:
        static std::vector<std::string> DUMMY_LIST;
        static std::map<std::string, std::vector<std::string>> DUMMY_MAP;
        static const std::string COMPACT_STRING;
        static std::vector<std::string> process_redis_reply(redisReply *reply);
        static std::string prepareQuery(std::string query, int argc, char **argv);
        static std::string prepareQuery(std::string query, std::map<std::string, std::string> params);

    private:
    static std::vector<std::string> data;
};

static inline void ltrim(std::string &s);

// trim from end (in place)
static inline void rtrim(std::string &s);

// trim from both ends (in place)
static inline void trim(std::string &s);

// trim from start (copying)
static inline std::string ltrim_copy(std::string s);

// trim from end (copying)
static inline std::string rtrim_copy(std::string s);

// trim from both ends (copying)
static inline std::string trim_copy(std::string s);

#endif //REDISGRAPHCLINET_UTILS_H
