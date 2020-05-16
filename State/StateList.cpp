#include "pch.h"
#include "StateList.h"

StateList::StateList()
{
    states = new std::vector<StateNode>();
}

StateList::StateList(CString &fileName)
{
    fillStates(fileName);
}

StateList::StateList(StateList &copy)
{
    states = new std::vector<StateNode>();

    for (auto it: *copy.states) {
        states->push_back(it);
    }
}

StateList StateList::operator=(StateList &copy) {
    for (auto it: *copy.states) {
        states->push_back(it);
    }
    return *this;
}

StateList::~StateList()
{
    delete states;
    states = nullptr;
}

Nodes* StateList::getNodes()
{
    return states;
}

void StateList::printState()
{
    for (auto &it: *states) {
        //std::cout << it->name << std::endl;

        for (auto &jump : it.jumps) {
            jump->print();
        }
        std::cout << std::endl;
    }
}

void StateList::fillStates(CString& fileName)
{
    std::fstream fileStream;
    std::string line;
    int stateNumber, i = 0;

    fileStream.open(fileName, std::ios::in);
    if (fileStream.is_open()) {
        // get input alphabet
        getline(fileStream, line);
        auto alphabet = splitString(line, "\\s");
        // get output alphabet
        getline(fileStream, line);
        alphabet = splitString(line, "\\s");
        // number of states
        getline(fileStream, line);
        stateNumber = std::stoi(line);
        // states.resize(stateNumber);
        states = new std::vector<StateNode>(stateNumber, StateNode());
        // read state and jumps
        while (getline(fileStream, line)) {
            StateNode &node = (*states)[i];
            i++;
            for (auto & it : splitString(line, "\\s")) {
                node.jumps.push_back(new Jump(splitString(it, "\\\\")));
            }
            node.value = i;
        }
        fileStream.close();
    }
}

void StateList::pushNode(StateNode &node)
{
    states->push_back(node);
}

std::vector<std::string> splitString(const std::string& stringToSplit, const std::string& regexPattern)
{
    std::vector<std::string> result;

    const std::regex rgx(regexPattern);
    std::sregex_token_iterator iter(stringToSplit.begin(), stringToSplit.end(), rgx, -1);

    for (std::sregex_token_iterator end; iter != end; ++iter)
    {
        result.push_back(iter->str());
    }

    return result;
}

int StateList::getNodeLambdaId(int nodeId)
{
    StateNode node = (*states)[nodeId - 1];

    return node.lambda->index;
}

bool isEqualGroups(groupCondition &first, groupCondition &second)
{
    bool isEqual = true;
    if (first.size() != second.size())
    {
        return false;
    }
    auto it = first.begin();

    while (it != first.end() && isEqual)
    {
        isEqual = second.at(it->first) == it->second;
        it++;
    }
    return isEqual;
}

bool isEqualDeltaGroups(DeltaGroup &first, DeltaGroup &second)
{
    bool isEqual = true;
    if (first.condition->size() != second.condition->size() || first.lambda != second.lambda)
    {
        return false;
    }
    auto it = first.condition->begin();

    while (it != first.condition->end() && isEqual)
    {
        isEqual = second.condition->at(it->first) == it->second;
        it++;
    }
    return isEqual;
}