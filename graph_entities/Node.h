//
// Created by devi on 1/5/20.
//

#ifndef REDISGRAPHCLINET_NODE_H
#define REDISGRAPHCLINET_NODE_H


#include <vector>
#include "GraphEntity.h"

class Node : public GraphEntity{
    public:
        void addLabel(std::string label);
        void removeLabel(std::string label);
        std::string getLabel(int index);
        int getNumberOfLabels();

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
        friend std::ostream& operator<<(std::ostream& os, const Node& dt);

        /**
         * Equals operator overloading
         * @param e1
         * @param e2
         * @return
         */
        friend bool operator== (const Node &n1, const Node &n2);

    private:
        std::vector<std::string> labels;
};


#endif //REDISGRAPHCLINET_NODE_H
