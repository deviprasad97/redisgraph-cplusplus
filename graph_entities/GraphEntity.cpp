//
// Created by devi on 1/5/20.
//

#include <algorithm>
#include <sstream>
#include <utility>
#include "GraphEntity.h"

/**
 * get the id of the object
 * @return
 */
int GraphEntity::getId() {
    return _id;
}

/**
 * set the id of the object
 * @param id, int
 */
void GraphEntity::setId(int id) {
    _id = id;
}

/**
 * Given a key and value it creates a property
 * @param name, string:key
 * @param value string:value
 */
void GraphEntity::addProperty(const std::string& name, Any value) {
    addProperty(Property(name, std::move(value)));
}

/**
 * Gets all the unique keys from the property map
 * @return
 */
std::set<std::string> GraphEntity::getEntityPropertyNames() {
    std::set<std::string> s;
    std::transform(_propertyMap.begin(), _propertyMap.end(), inserter(s, s.begin()), select1st<std::pair<std::string, Property >>());

    return std::set<std::string>();
}

/**
 * To add porperty with Property object
 * @param property
 */
void GraphEntity::addProperty(Property property) {
    _propertyMap.insert(std::pair<std::string, Property >(property.getName(), property));
}

/**
 * returns number of properties
 * @return int (property size)
 */
int GraphEntity::getNumberOfProperties() {
    return _propertyMap.size();
}

/**
 * Provided key it returns the value for that key
 * @param propertyName (key, string)
 * @return value for the key: string
 */
Property GraphEntity::getProperty(std::string propertyName) {
    return _propertyMap.find(propertyName)->second;
}

/**
 * Given the key it removes that key and its corresponding value from property map
 * @param name, string:key
 */
void GraphEntity::removeProperty(std::string name) {
    std::map<std::string,Property>::iterator it;

    it = _propertyMap.find(name);
    _propertyMap.erase(it);

}

//std::string GraphEntity::to_string() {
//    std::stringstream ss;
//
//}
//
//std::ostream &operator<<(std::ostream &os, const GraphEntity &dt) {
//    os<<"Property{"<<"name='"<<dt._name<<'\''<<", value"<<dt._value<<"}";
//    return os;
//}
//
//bool operator==(const GraphEntity &g1, const GraphEntity &g2) {
//    if (p1._name != p2._name)
//        return false;
//
//    return !(p1._value != p2._value);
//}