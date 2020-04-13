//
// Created by devi on 1/9/20.
//

#ifndef BOOSTGRAPHEXAMPLE_NODE_H
#define BOOSTGRAPHEXAMPLE_NODE_H


#include <string>
#include <utility>

class Node {
    public:
        Node(int id, std::string name) : _id{id}, _name{std::move(name)} { }
        int get_id() {
            return _id;
        }
        friend std::ostream& operator<<(std::ostream& os, const Node& dt);
        bool operator==(const Node &rhs) const { return _name == rhs._name && _id == rhs._id; }
        bool operator!=(const Node &rhs) const { return !(rhs == *this); }

    std::string get_name() {
            return _name;
        }

    private:
        int _id;
        std::string _name;
};


#endif //BOOSTGRAPHEXAMPLE_NODE_H
