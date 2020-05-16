#pragma once
#include "Presenter.h"
#include "Model/Group.h"

class DeltaGroupPresenter : public Presenter
{
public:
	DeltaGroupPresenter(vector<DeltaGroup*>*);
	vector<string> toPrint(int);
	int getSize();
private:
	vector<DeltaGroup*>* data;
};

