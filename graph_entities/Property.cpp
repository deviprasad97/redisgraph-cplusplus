//
// Created by devi on 1/5/20.
//

#include <sstream>
#include <utility>
#include "Property.h"


Property::Property(const std::string& name, Any value) {
    _name = name;
    _value = std::move(value);
}


std::string Property::getName() {
    return _name;
}


void Property::setName(const std::string& name) {
    _name = name;
}


Any Property::getValue() {
    return _value;
}

void Property::setValue(Any value) {
    _value = std::move(value);
}


std::string Property::to_string() {
    std::stringstream ss;
    if(_value.type == 2)
    {
        ss<<"Property{"<<"name='"<<_name<<'\''<<", value"<<_value.string_data<<"}";
    }
    else if(_value.type == 3)
    {
        ss<<"Property{"<<"name='"<<_name<<'\''<<", value"<<_value.int_data<<"}";
    }
    else if(_value.type == 5)
    {
        ss<<"Property{"<<"name='"<<_name<<'\''<<", value"<<_value.double_data<<"}";
    }
    return ss.str();
}

std::ostream &operator<<(std::ostream &os, const Property &dt) {
    if(dt._value.type == 2)
    {
        os<<"Property{"<<"name='"<<dt._name<<'\''<<", value"<<dt._value.string_data<<"}";
    }
    else if(dt._value.type == 3)
    {
        os<<"Property{"<<"name='"<<dt._name<<'\''<<", value"<<dt._value.int_data<<"}";
    }
    else if(dt._value.type == 5)
    {
        os<<"Property{"<<"name='"<<dt._name<<'\''<<", value"<<dt._value.double_data<<"}";
    }
    return os;
}

bool operator==(const Property &p1, const Property &p2) {
    int value_type;
    if (p1._name != p2._name)
        return false;
    if(p1._value.type != p2._value.type)
    {
        return false;
    } else{
        value_type = p1._value.type;
    }
    if(value_type == 2)
    {
        return p1._value.string_data == p2._value.string_data;
    }
    else if(value_type == 3)
    {
        return p1._value.int_data == p2._value.int_data;
    }
    else if(value_type == 5)
    {
        return p1._value.double_data == p2._value.double_data;
    }
}