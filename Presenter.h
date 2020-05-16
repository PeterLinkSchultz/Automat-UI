#pragma once
#include <string>
#include <vector>

class Presenter
{
public:
	virtual std::vector<std::string> toPrint(int i);
	virtual int getSize();
};

