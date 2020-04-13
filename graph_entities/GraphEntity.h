//
// Created by devi on 1/5/20.
//

#ifndef REDISGRAPHCLINET_GRAPHENTITY_H
#define REDISGRAPHCLINET_GRAPHENTITY_H


#include <map>
#include <set>
#include "Property.h"
#include <vector>

template <class P>
struct select1st : public std::unary_function<P, typename P::first_type>
{
    const typename P::first_type& operator()(const P &arg) const { return arg.first; }
};

class GraphEntity {
    protected:
        int _id;
        std::map<std::string, Property> _propertyMap;

        // To contain Matrix
        std::vector<std::vector<float >> mat;

        // Row lables for matrix
        std::vector<std::string> type_labels;
        std::vector<std::string> relation_labels; // Col lables for matrix
        std::vector<int> types_id;  // Row id for matrix
        std::vector<int> relation_id; // Col id for matrix
    public:
        int getId();
        void setId(int id);
        void addProperty(const std::string& name, Any value);
        std::set<std::string> getEntityPropertyNames();
        void addProperty(Property property);
        int getNumberOfProperties();
        Property getProperty(std::string propertyName);
        void removeProperty(std::string name);
};


#endif //REDISGRAPHCLINET_GRAPHENTITY_H
