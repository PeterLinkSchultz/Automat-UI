#include "pch.h"
#include "DeltaGroupPresenter.h"

DeltaGroupPresenter::DeltaGroupPresenter(vector<DeltaGroup*>*groups)
{
	data = groups;
}


vector<string> DeltaGroupPresenter::toPrint(int n)
{
	auto group = data->at(n);

	return group->toPrint();
}

int DeltaGroupPresenter::getSize()
{
	return data->size();
}