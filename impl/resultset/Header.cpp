//
// Created by devi on 1/5/20.
//

#include "Header.h"

std::vector<std::string> Header::getSchemaNames()
{
    if(schemaNames.empty())
        buildSchema();
    return schemaNames;
}

std::vector<Header::ResultSetColumnTypes> Header::getSchemaTypes() {
    if(schemaTypes.empty())
        buildSchema();
    return schemaTypes;
}

void Header::buildSchema() {
    for(int i=0; i<raw->elements; i++){
        auto temp = raw->element[i];
        schemaTypes.push_back((Header::ResultSetColumnTypes)raw->element[i]->element[0]->integer);
        schemaNames.emplace_back(raw->element[i]->element[1]->str);
    }
}

Header::Header(redisReply *_raw) {
    raw = _raw;
    schemaTypes = std::vector<ResultSetColumnTypes>();
    schemaNames = std::vector<std::string>();
    buildSchema();
}

std::ostream &operator<<(std::ostream &out, const Header::ResultSetColumnTypes value) {
    static std::map<Header::ResultSetColumnTypes, std::string> strings;
    if (strings.size() == 0){
#define INSERT_ELEMENT(p) strings[p] = #p
        INSERT_ELEMENT(Header::COLUMN_UNKNOWN);
        INSERT_ELEMENT(Header::COLUMN_SCALAR);
        INSERT_ELEMENT(Header::COLUMN_NODE);
        INSERT_ELEMENT(Header::COLUMN_RELATION);
#undef INSERT_ELEMENT
    }

    return out << strings[value];
}

