//
// Created by devi on 1/5/20.
//

#include <sstream>
#include <utility>
#include "Edge.h"
/**
 * Returns back edge relationship type
 * @return
 */
std::string Edge::getRelationshipType() {
    return _realationshipType;
}

/**
 * Sets the relationship type for the edge
 * @param relationshipType , String value for relationship type
 */
void Edge::setRealtionshipType(std::string relationshipType) {
    _realationshipType = std::move(relationshipType);
}

/**
 * for directed graph sets the source obj
 * @return
 */
int Edge::getSource() {
    return _source;
}

/**
 * for directed graph sets the source obj
 * @param source
 */
void Edge::setSource(int source) {
    _source = source;
}

int Edge::getDestination() {
    return _destination;
}

void Edge::setDestination(int destination) {
    _destination = destination;
}


/**
 * creates a string representation of edge object
 * @return
 */
std::string Edge::to_string() {
    std::stringstream ss;

    std::string propertyMapString;
    std::string temp;

    for (const auto & it : _propertyMap) {
        //auto some = it.second;
        //temp = some.to_string();
        propertyMapString += (it.first) + ":" + ", ";
    }

    ss << "Edge{";
    ss << "relationshipType='"<<_realationshipType<<'\'' << ", source=" << _source << ", destination=" << _destination<<", id=" << _id << ", propertyMap=" << propertyMapString<<"}";
    return ss.str();
}

/**
 * out operator overloading to be used for creating output stream
 * @param os
 * @param dt
 * @return
 */
std::ostream &operator<<(std::ostream &os, const Edge &dt) {

    std::string propertyMapString;
    std::string temp;

    for (const auto & it : dt._propertyMap) {
        //auto some = it.second;
        //temp = some.to_string();
        propertyMapString += (it.first) + ":" + ", ";
    }
    os<<"relationshipType='"<<dt._realationshipType<<'\'' << ", source=" << dt._source <<", destination="<< dt._destination<<", id=" << dt._id << ", propertyMap=" << propertyMapString<<"}";
    return os;
}

/**
 * compare operator overloading to compare two edge object
 * @param e1
 * @param e2
 * @return
 */
bool operator==(const Edge &e1, const Edge &e2) {
    if (e1._id != e2._id)
        return false;
    if (e1._source != e2._source)
        return false;

    if (e1._destination != e2._destination)
        return false;

    if(e1._realationshipType != e2._realationshipType)
        return false;

    if (e1._propertyMap.size() != e2._propertyMap.size())
        return false;
    //return map_compare(e1.properties, e2.properties) != 1;
    return true;
}