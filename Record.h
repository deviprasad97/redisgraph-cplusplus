//
// Created by devi on 1/5/20.
//

#ifndef REDISGRAPHCLINET_RECORD_H
#define REDISGRAPHCLINET_RECORD_H


#include <string>
#include <vector>
#include <jmorecfg.h>

class Record {
    public:
        virtual std::string getString(std::string key) = 0;
        virtual std::string getString(int index) = 0;
        virtual std::vector<std::string> values() = 0;
        virtual bool containsKey(std::string key) = 0;
        virtual int size() = 0 ;
};


#endif //REDISGRAPHCLINET_RECORD_H
