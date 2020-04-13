//
// Created by devi on 1/5/20.
//

#ifndef REDISGRAPHCLINET_PATH_H
#define REDISGRAPHCLINET_PATH_H


#include "Node.h"
#include "Edge.h"

class Path : public GraphEntity {
    public:
        Path(std::vector<Node> nodes, std::vector<Edge> edges);
        std::vector<Node> getNodes();
        std::vector<Edge> getEdges();
        int lenght();
        int nodeCount();
        Node firstNode();
        Node lastNode();
        Node getNode(int index);
        Edge getEdge(int index);

        /**
         *
         * @return string representation of the object
         */
        std::string to_string();

        /**
         * Out stream operator overloading
         * @param os
         * @param dt
         * @return
         */
        friend std::ostream& operator<<(std::ostream& os, const Path& dt);

        /**
         * Equals operator overloading
         * @param e1
         * @param e2
         * @return
         */
        friend bool operator== (const Path &p1, const Path &p2);

    private:
        std::vector<Node> _nodes;
        std::vector<Edge> _edges;


};


#endif //REDISGRAPHCLINET_PATH_H
