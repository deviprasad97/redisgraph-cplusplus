//
// Created by devi on 1/9/20.
//

#include "Node.h"
std::ostream &operator<<(std::ostream &os, Node dt) {


    os<<std::to_string(dt.get_id());
    return os;
}