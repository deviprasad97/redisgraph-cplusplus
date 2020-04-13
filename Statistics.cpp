//
// Created by devi on 1/5/20.
//

#include "Statistics.h"
Statistics::Labels Statistics::getLabel(std::string text)
{
    if(text == "Labels Added")
        return LABELS_ADDED;
    if(text == "Indices deleted")
        return LABELS_ADDED;
    if(text == "Nodes created")
        return LABELS_ADDED;
    if(text == "Indices deleted")
        return INDICES_DELETED;
    if(text == "Nodes deleted")
        return NODES_DELETED;
    if(text == "Relationships deleted")
        return RELATIONSHIPS_DELETED;
    if(text == "Properties set")
        return PROPERTIES_SET;
    if(text == "Relationships created")
        return RELATIONSHIPS_CREATED;
    if(text == "Query internal execution time")
        return QUERY_INTERNAL_EXECUTION_TIME;

}