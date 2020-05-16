#include <afxwin.h>
#include <vector>

#include "Presenter.h"

#pragma once

typedef struct
{
	CPoint home;
	CRect rct;
} NODE;

class Graphs
{
public:
	Graphs(CWnd*, CWnd*, CPoint&, int);
	void DrawNodes();
	void DrawNode(int i, CPaintDC&);
	void CheckPoint(CPoint&);
	void WriteInfo(int);
	void SetPresenter(Presenter*);
	CPoint start;
	int offset = 0;
private:
	CWnd* context;
	CWnd* infoContext;
	int n = 0;
	int size = 25;
	int margin = 10;
	int maxShow = 1;
	std::vector<NODE> nodes;
	CPoint end;
	Presenter* presenter;
};

