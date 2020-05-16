#include "Graphs.h"
#include "Presenter.h"

#pragma once
class ScrollController
{
public:
	ScrollController(CWnd*, int, CRect&, CWnd*, CPoint&);
	int GetScrollID();
	CRect GetFieldRect();
	void RedrawField();
	void Update(int);
	void SetNodesPresenter(Presenter*, CScrollBar&);
	void CheckPoint(CPoint&);
	void ClearField();
private:
	CWnd* context;
	Graphs* data = nullptr;
	Presenter* presenter;
	CRect rect;
	int id;
};

