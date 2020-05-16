#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <fstream>
#include <regex>
#include <iostream>
#include "../Model/Group.h"
#include "StateNode.h"

#ifndef AUTOMAT_STATELIST_H
#define AUTOMAT_STATELIST_H

class StateList {
public:
    StateList();
    StateList(StateList&);
    StateList(CString &);
    ~StateList();
    void printState();
    void fillStates(CString &);
    Nodes* getNodes();
    void pushNode(StateNode &);
    int getNodeLambdaId(int);
    StateList operator =(StateList &);
private:
    std::vector<StateNode> *states{};
};

bool isEqualGroups(groupCondition &first, groupCondition &second);
bool isEqualDeltaGroups(DeltaGroup &first, DeltaGroup &second);

std::vector<std::string> splitString(const std::string&, const std::string&);
#endif //AUTOMAT_STATELIST_H
