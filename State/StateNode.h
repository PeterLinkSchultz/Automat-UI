#include <string>

using namespace std;
#ifndef AUTOMAT_STATENODE_H
#define AUTOMAT_STATENODE_H

struct Jump {
    Jump(string _index, string _direction, string _value) {
        index = _index;
        direction = _direction;
        value = _value;
    }
    Jump(const std::vector<std::string> &input) {
        index = input[0];
        direction = input[1];
        value = input[2];
    }
    void print() {
        // std::cout << index << "/" << direction << "/" << value << " ";
    }
    string toPrint() {
        return index + ": " + direction + "/" + value;
    }
    std::string index;
    std::string direction;
    std::string value;
};


#endif //AUTOMAT_STATENODE_H
