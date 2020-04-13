//
// Created by devi on 1/5/20.
//

#ifndef REDISGRAPHCLINET_PROPERTY_H
#define REDISGRAPHCLINET_PROPERTY_H


#include <string>

typedef struct any
{
    std::string string_data;
    int int_data;
    bool bool_data;
    double double_data;
    int type;
} Any;

class Property {
    public:
        Property() = default;
        Property(const std::string& name, Any value);

        std::string getName();
        void setName(const std::string& name);
        Any getValue();
        void setValue(Any value);

        std::string to_string();
        /**
         * Out stream operator overloading
         * @param os
         * @param dt
         * @return
         */
        friend std::ostream& operator<<(std::ostream& os, const Property& dt);

        /**
         * Equals operator overloadings
         * @param e1
         * @param e2
         * @return
         */
        friend bool operator== (const Property &p1, const Property &p2);

    private:
        std::string _name;
        Any _value;

};




#endif //REDISGRAPHCLINET_PROPERTY_H
