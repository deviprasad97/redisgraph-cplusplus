//
// Created by devi on 1/5/20.
//

#include <algorithm>
#include "RecordImpl.h"

std::string RecordImpl::getString(std::string key) {
    std::vector<std::string>::iterator it;
    it =  std::find(_header.begin(), _header.end(), key);

    return getString(it-_header.begin());
}

std::string RecordImpl::getString(int index) {
    return _values[index];
}

std::vector<std::string> RecordImpl::values() {
    return _values;
}

bool RecordImpl::containsKey(std::string key) {
    return std::count(_header.begin(), _header.end(), key) != 0;
}

int RecordImpl::size() {
    return _header.size();
}

std::vector<std::string> RecordImpl::keys() {
    return _header;
}
