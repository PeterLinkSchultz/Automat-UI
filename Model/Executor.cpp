#include "pch.h"
#include "../Model/Executor.h"

Executor::Executor(StateList &list)
{
    stateList = list;
}

void Executor::init()
{
    lambdaBinder.bindNodes(stateList);
    store.initStore(stateList);
    deltaBinder.bindStore(&store);
}

void Executor::start()
{
    do {
        deltaBinder.bindNodes(stateList);
        store.swapStore();
    } while(!deltaBinder.isGroupRepeatetly());

    makeShortedAuto();
    //printShortedAuto();
}

Nodes* Executor::getInitNodes()
{
    return stateList.getNodes();
}

vector<LambdaGroup*>* Executor::getLambdaGroups()
{
    return lambdaBinder.getData();
}

vector<DeltaGroup*>* Executor::getDeltaGroups()
{
    return new vector<DeltaGroup*>(deltaBinder.getData());
}

void Executor::makeShortedAuto()
{
    auto deltaGroups = deltaBinder.getData();
    for (auto &it: deltaGroups) {
        StateNode node;
        pGroupCondition lambdaCondition = lambdaBinder.getCondition(it->lambda);
        for (auto &lambdaIt: *lambdaCondition) {
           string index = intToChars(it->condition->find(lambdaIt.first)->second); // new group index
           string direction = lambdaIt.first; // direction
           string value = lambdaIt.second; // value

           node.jumps.push_back(new Jump(index, direction, value));
        }
        finishList.pushNode(node);
    }
}

void Executor::printShortedAuto()
{
    finishList.printState();
}

bool Executor::next()
{
    deltaBinder.bindNodes(stateList);
    store.swapStore();

    return deltaBinder.isGroupRepeatetly();
}