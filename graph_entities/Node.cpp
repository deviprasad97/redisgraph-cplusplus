//
// Created by devi on 1/5/20.
//

#include <algorithm>
#include <sstream>
#include "Node.h"

/**
 * adds a named label to the object
 * @param label
 */
void Node::addLabel(std::string label) {
    labels.push_back(label);
}

/**
 * removes the labels
 * @param label
 */
void Node::removeLabel(std::string label) {
    std::vector<std::string>::iterator it;
    it = std::find(labels.begin(), labels.end(), label);
    if(it != labels.end())
    {
        label.erase(it - labels.begin());
    }
}

std::string Node::getLabel(int index) {
    return labels[index];
}

int Node::getNumberOfLabels() {
    return labels.size();
}

std::string Node::to_string() {
    std::stringstream ss;
    std::stringstream labels_stream;

    for(const std::string& s : labels)
    {
        labels_stream<<s;
    }

    std::string output;
    std::string convrt;

    for (const auto & it : _propertyMap) {
        auto some = it.second;
        convrt = some.to_string();
        output += (it.first) + ":" + (convrt) + ", ";
    }
    ss<<"Node{"<<"labels="<<labels_stream.str()<<", id="<<_id<<", propertyMap="<<output<<"}";
    return ss.str();
}

std::ostream &operator<<(std::ostream &os, const Node &dt) {
    std::stringstream labels_stream;

    for(const std::string& s : dt.labels)
    {
        labels_stream<<s;
    }
    std::string output;
    std::string convrt;

    for (const auto & it : dt._propertyMap) {
        auto some = it.second;
        convrt = some.to_string();
        output += (it.first) + ":" + (convrt) + ", ";
    }
    os<<"Node{"<<"labels="<<labels_stream.str()<<", id="<<dt._id<<", propertyMap="<<output<<"}";
    return os;
}

bool operator==(const Node &n1, const Node &n2) {
    if (n1._id != n2._id)
        return false;

    if (n1.labels != n2.labels)
        return false;

    if (n1._propertyMap.size() != n2._propertyMap.size())
        return false;

    //return map_compare(e1.properties, e2.properties) != 1;
    return true;
}