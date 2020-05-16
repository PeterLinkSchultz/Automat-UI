#include "pch.h"
#include "Store.h"

void Store::initStore(StateList &stateList)
{
    Nodes* nodes = stateList.getNodes();

    for (auto& it : *nodes) {
        saved->push_back(it.lambda->index);
    }
}

int Store::getGroupNumber(int index)
{
    return saved->at(index - 1);
}

void Store::updateStore(int value)
{
    current->push_back(value);
}

void Store::swapStore()
{
    saved = current;
    current = nullptr;
    current = new vector<int>;
}