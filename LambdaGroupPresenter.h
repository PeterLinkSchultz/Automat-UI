#pragma once
#include "Presenter.h"
#include "Model/Group.h"

class LambdaGroupPresenter : public Presenter
{
public:
	LambdaGroupPresenter(vector<LambdaGroup*>*);
	vector<string> toPrint(int);
	int getSize();
private:
	vector<LambdaGroup*>* data;
};

