//
// Created by devi on 1/5/20.
//

#include <sstream>
#include "Path.h"

Path::Path(std::vector<Node> nodes, std::vector<Edge> edges) {
    _nodes = nodes;
    _edges = edges;
}

std::vector<Node> Path::getNodes() {
    return _nodes;
}

std::vector<Edge> Path::getEdges() {
    return _edges;
}

int Path::lenght() {
    return _edges.size();
}

int Path::nodeCount() {
    return _nodes.size();
}

Node Path::firstNode() {
    return _nodes[0];
}

Node Path::lastNode() {
    return _nodes[_nodes.size()-1];
}

Node Path::getNode(int index) {
    return _nodes[index];
}

Edge Path::getEdge(int index) {
    return _edges[0];
}

std::string Path::to_string() {
    std::stringstream ss;
    std::stringstream node_stream;
    std::stringstream edge_stream;

    for(Node node : _nodes)
    {
        node_stream<<node.to_string();
    }
    for(Edge edge: _edges)
    {
        edge_stream<<edge.to_string();
    }
    ss<<"Path{"<<"nodes="<<node_stream.str()<<", edges"<<edge_stream.str()<<"}";
    return ss.str();
}

std::ostream &operator<<(std::ostream &os, const Path &dt) {
    std::stringstream node_stream;
    std::stringstream edge_stream;

    for(Node node : dt._nodes)
    {
        node_stream<<node.to_string();
    }
    for(Edge edge: dt._edges)
    {
        edge_stream<<edge.to_string();
    }
    os<<"Path{"<<"nodes="<<node_stream.str()<<", edges"<<edge_stream.str()<<"}";

    return os;
}

bool operator==(const Path &p1, const Path &p2) {
    if (p1._edges != p2._edges)
        return false;

    if (p1._nodes != p2._nodes)
        return false;

    if(p1._id != p2._id)
        return false;

    if(p1._propertyMap.size() != p2._propertyMap.size())
        return false;
    //return map_compare(e1.properties, e2.properties) != 1;
    return true;
}