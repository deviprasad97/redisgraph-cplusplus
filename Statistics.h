//
// Created by devi on 1/5/20.
//

#ifndef REDISGRAPHCLINET_STATISTICS_H
#define REDISGRAPHCLINET_STATISTICS_H


#include <string>
#include <utility>


class Statistics {

    public:
    enum Labels{
        LABELS_ADDED,
        INDICES_ADDED,
        INDICES_DELETED,
        NODES_CREATED,
        NODES_DELETED,
        RELATIONSHIPS_DELETED,
        PROPERTIES_SET,
        RELATIONSHIPS_CREATED,
        QUERY_INTERNAL_EXECUTION_TIME,
    };
        virtual std::string getStringValue(Labels label) = 0;
        Labels getLabel(std::string text);
        virtual int nodesCreated() = 0;

        virtual int nodesDeleted() = 0;;

        virtual int indicesAdded() = 0;;

        virtual int indicesDeleted() = 0;;

        virtual int labelsAdded() = 0;;

        virtual int relationshipsDeleted() = 0;;

        virtual int relationshipsCreated() = 0;;

        virtual int propertiesSet() = 0;;

};


#endif //REDISGRAPHCLINET_STATISTICS_H
