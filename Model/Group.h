#include <vector>
#include <string>
#include <sstream>
#include <map>
#include "../State/StateNode.h"

using namespace std;

#ifndef AUTOMAT_GROUP_H
#define AUTOMAT_GROUP_H

typedef std::map<string, string> groupCondition;
typedef groupCondition* pGroupCondition;
typedef std::map<string, int> deltaGroupCondition;
typedef deltaGroupCondition* pDeltaGroupCondition;

struct StateNode;

template <typename T>
struct Group {
    int index;
    T condition;
    std::vector<StateNode *> items;
    Group(int _i, T _cond, std::vector<StateNode *> _items) {
        index = _i;
        condition = _cond;
        items = _items;
    }
    vector<string> toPrint() {
        vector<string> result;
        string states = "States: ";

        for (auto it : items) {
            states += intToChars(it->value) + " ";
        }
        result.push_back(states);
        for (auto it : *condition) {
            result.push_back(it.first + " : " + it.second);
        }

        return result;
    }
    std::string intToChars(int n)
    {
        std::ostringstream os;
        os << n;

        return os.str();
    }

};

struct StateNode {
    std::vector<Jump*> jumps{};
    Group<pGroupCondition>* lambda;
    int value;
};
typedef std::vector<StateNode> Nodes;
typedef Group<pGroupCondition> LambdaGroup;

struct DeltaGroup: Group<pDeltaGroupCondition> {
    int lambda;
    DeltaGroup(int index, pDeltaGroupCondition condition, int lambdaGroupId): Group(index, condition, {}) {
        lambda = lambdaGroupId;
    }
    vector<string> toPrint() {
        vector<string> result;
        string states = "States: ";
        string base = "Base lambda group: " + intToChars(lambda);

        for (auto it : items) {
            states += intToChars(it->value) + " ";
        }
        result.push_back(states);
        for (auto it : *condition) {
            result.push_back(it.first + " : " + intToChars(it.second));
        }
        result.push_back(base);

        return result;
    }
};

#endif //AUTOMAT_GROUP_H