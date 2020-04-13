//
// Created by devi on 1/5/20.
//

#include <sstream>
#include "utils.h"
const std::string utils::COMPACT_STRING = "--COMPACT";

std::string utils::prepareQuery(std::string query, int argc, char **argv) {
    std::stringstream ss;
    ss<<"CYPHER ";
    if (argv == nullptr){
        return "";
    }
    for (int i=0; i<argc; i++){

    }
    return std::__cxx11::string();
}

std::string utils::prepareQuery(std::string query, std::map<std::string, std::string> params) {
    return std::__cxx11::string();
}

// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

// trim from start (copying)
static inline std::string ltrim_copy(std::string s) {
    ltrim(s);
    return s;
}

// trim from end (copying)
static inline std::string rtrim_copy(std::string s) {
    rtrim(s);
    return s;
}

// trim from both ends (copying)
static inline std::string trim_copy(std::string s) {
    trim(s);
    return s;
}