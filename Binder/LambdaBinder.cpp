#include "pch.h"
#include "LambdaBinder.h"

void LambdaBinder::bindNodes(StateList &state)
{
    Nodes* nodes = state.getNodes();

    for (auto& it : *nodes) {
        bindGroup(it);
    }
}

pGroupCondition LambdaBinder::getCondition(int index)
{
    return data[index-1]->condition;
}

void LambdaBinder::bindGroup(StateNode &node)
{
    pGroupCondition state = new groupCondition;

	for (auto& jump : node.jumps) 
	{
		state->insert({ jump->direction, jump->value });
	}

	auto it = find_if(data.begin(), data.end(), [state](Group<pGroupCondition> *existed) {
		return isEqualGroups(*state, *existed->condition);
		});

	auto templateLambdaGroup = new Group<pGroupCondition>{ counter, state, {} };
	if (it == data.end())
	{
		templateLambdaGroup->items.push_back(&node);
        data.push_back(templateLambdaGroup);
        node.lambda = data.back();
        counter++;
	}
	else 
	{
		(*it)->items.push_back(&node);
	    node.lambda = *it;
		delete state;
	}
}

vector<LambdaGroup*>* LambdaBinder::getData()
{
	return &data;
}