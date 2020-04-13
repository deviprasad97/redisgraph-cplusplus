//
// Created by devi on 1/5/20.
//

#ifndef REDISGRAPHCLINET_EDGE_H
#define REDISGRAPHCLINET_EDGE_H


#include <string>
#include <map>
#include "Property.h"
#include "GraphEntity.h"

class Edge : public GraphEntity{
    public:
        Edge() = default;;
        // Getters & Setters
       /**
        *  @return the edge relationship type
        */
        std::string getRelationshipType();

       /**
        * @param relationshipType -  the relationship type to be set
        */
        void setRealtionshipType(std::string relationshipType);

       /**
        * @return the id of the source node
        */
        int getSource();

       /**
        * @param source - the id of the source node to be set
        */
        void setSource(int source);

       /**
        * @return the id of the destination node
        */
        int getDestination();

       /**
        * @param destination - the id of the destination node to be set
        */
        void setDestination(int destination);

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
        friend std::ostream& operator<<(std::ostream& os, const Edge& dt);

        /**
         * Equals operator overloading
         * @param e1
         * @param e2
         * @return
         */
        friend bool operator== (const Edge &e1, const Edge &e2);
    private:
        std::string _realationshipType;
        int _source{};
        int _destination{};
};


#endif //REDISGRAPHCLINET_EDGE_H
