#include "pch.h"
#include "LambdaGroupPresenter.h"

LambdaGroupPresenter::LambdaGroupPresenter(vector<LambdaGroup *>* groups)
{
	data = groups;
}

vector<string> LambdaGroupPresenter::toPrint(int n)
{
	auto group = data->at(n);

	return group->toPrint();
}

int LambdaGroupPresenter::getSize()
{

	return data->size();
}