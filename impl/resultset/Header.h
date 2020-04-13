//
// Created by devi on 1/5/20.
//

#ifndef REDISGRAPHCLINET_HEADERIMPL_H
#define REDISGRAPHCLINET_HEADERIMPL_H


#include <vector>
#include <string>
#include <hiredis/hiredis.h>
#include <cstring>
#include <map>

class Header {
    public:
        enum ResultSetColumnTypes {
            COLUMN_UNKNOWN,
            COLUMN_SCALAR,
            COLUMN_NODE,
            COLUMN_RELATION

        };
        friend std::ostream& operator<<(std::ostream& out, const ResultSetColumnTypes value);

        Header() = default;
        explicit Header(redisReply *_raw);
        virtual std::vector<std::string> getSchemaNames();
        virtual std::vector<ResultSetColumnTypes> getSchemaTypes();

    private:
        redisReply *raw;
        std::vector<ResultSetColumnTypes> schemaTypes;
        std::vector<std::string> schemaNames;
        void buildSchema();
    /**
     * TODO:: Implement:
     *        to_string
     *        operator overloading of ==
     *        operator overloading of <<
     */
};


#endif //REDISGRAPHCLINET_HEADERIMPL_H
