#include "pch.h"
#include "DeltaBinder.h"

void DeltaBinder::bindNodes(StateList &state)
{
    Nodes* nodes = state.getNodes();
    counter = 1;
    lastNumbersGroup = data.size();
    data.clear();

    for (auto& it : *nodes) {
        bindGroup(it);
    }
}

void DeltaBinder::bindStore(Store *_store)
{
    store = _store;
}

vector<DeltaGroup *> DeltaBinder::getData()
{
    return data;
}

void DeltaBinder::bindGroup(StateNode &node)
{
    auto state = new deltaGroupCondition;

    for (auto& jump : node.jumps)
    {
        int groupIndex = store->getGroupNumber(atoi(jump->index.c_str()));
        state->insert({ jump->direction, groupIndex });
    }
    auto *tempDeltaGroup = new DeltaGroup{ counter, state, node.lambda->index };

    auto it = find_if(data.begin(), data.end(), [tempDeltaGroup](DeltaGroup *existed) {
        return isEqualDeltaGroups(*tempDeltaGroup, *existed);
    });

    if (it == data.end())
    {
        tempDeltaGroup->items.push_back(&node);
        data.push_back(tempDeltaGroup);
        store->updateStore(tempDeltaGroup->index);
        counter++;
    }
    else
    {
        (*it)->items.push_back(&node);
        store->updateStore((*it)->index);
        delete tempDeltaGroup;
        delete state;
    }
}

bool DeltaBinder::isGroupRepeatetly()
{
    return lastNumbersGroup == data.size();
}

