#include "pch.h"
#include "ScrollController.h"

#define MaxShow 8

ScrollController::ScrollController(CWnd* ctx, int _id, CRect& fieldRect, CWnd* infoCtx, CPoint&start)
{
	id = _id;
	rect = fieldRect;
	context = ctx;
	data = new Graphs(ctx, infoCtx, start, MaxShow);
}

void ScrollController::SetNodesPresenter(Presenter* presenter, CScrollBar &scrollBar)
{
	data->SetPresenter(presenter);

	int size = presenter->getSize() - MaxShow;
	scrollBar.SetScrollRange(0, size > 0 ? size : 0, true);
}

int ScrollController::GetScrollID()
{
	return id;
}

void ScrollController::CheckPoint(CPoint& point)
{
	data->CheckPoint(point);
}

CRect ScrollController::GetFieldRect()
{
	return rect;
}

void ScrollController::RedrawField()
{
	ClearField();
	data->DrawNodes();
}

void ScrollController::ClearField()
{
	context->InvalidateRect(rect, true);
}

void ScrollController::Update(int offset)
{
	data->offset = offset;
	RedrawField();
}