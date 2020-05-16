#include "pch.h"
#include "NodePresenter.h"
#include "Model/Group.h"

NodePresenter::NodePresenter(Nodes *nodes)
{
	data = nodes;
}

vector<string> NodePresenter::toPrint(int i)
{
	StateNode node = data->at(i);

	vector<string> info;

	for (auto it : node.jumps) {
		info.push_back(it->toPrint());
	}
	
	return info;
}

int NodePresenter::getSize()
{
	return data->size();
}