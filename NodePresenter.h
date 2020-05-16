#pragma once

#include "./Model/Group.h"
#include "Presenter.h"

class NodePresenter : public Presenter
{
public:
	NodePresenter(Nodes*);
	vector<string> toPrint(int);
	int getSize();
private:
	Nodes* data;
};

