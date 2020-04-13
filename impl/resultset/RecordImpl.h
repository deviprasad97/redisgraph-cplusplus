//
// Created by devi on 1/5/20.
//

#ifndef REDISGRAPHCLINET_RECORDIMPL_H
#define REDISGRAPHCLINET_RECORDIMPL_H


#include <string>
#include <utility>
#include "../../Record.h"

class RecordImpl : public Record{
    public:
        RecordImpl(std::vector<std::string> header, std::vector<std::string> values) : _header{std::move(header)}, _values{std::move(values)} { };
        std::string getString(std::string key) override;
        std::string getString(int index) override;
        std::vector<std::string> values() override;
        bool containsKey(std::string key) override;
        int size() override;
        std::vector<std::string> keys();

    private:
        std::vector<std::string> _header;
        std::vector<std::string> _values;

        /**
         * TODO:: Implement:
         *        to_string
         *        operator overloading of ==
         *        operator overloading of <<
         */
};


#endif //REDISGRAPHCLINET_RECORDIMPL_H
