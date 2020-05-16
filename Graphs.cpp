#include "pch.h"
#include "Graphs.h"

#define LinkRange 50
#define XYR 0.1

Graphs::Graphs(CWnd* context, CWnd* infoContext, CPoint& start, int maxShow)
{
	this->context = context;
	this->start = start;
	this->infoContext = infoContext;
	this->maxShow = maxShow;
}

void Graphs::DrawNodes()
{
	CPaintDC dc(context);

	int toShow = n < maxShow ? n : maxShow;
	int i;
	for (i = 0; i < toShow; i++)
	{
		int real = i + offset;

		NODE& node = nodes[real];
		node.home.x = start.x + i * (margin + size);
		node.home.y = start.y;
		node.rct = CRect(node.home.x, node.home.y, node.home.x + size, node.home.y + size);

		DrawNode(real, dc);
	}
}

void Graphs::DrawNode(int i, CPaintDC &dc)
{
	CString s;
	CPoint pt;

	CPen pBlack(PS_SOLID, 2, RGB(0, 0, 0));
	dc.SelectObject(pBlack);
	pt = nodes[i].home;
	dc.Rectangle(nodes[i].rct);
	s.Format(L"%d", i + 1);
	dc.TextOutW(pt.x + 7, pt.y + 4, s);
}

void Graphs::CheckPoint(CPoint& point)
{
	int i = 0;
	for (i = 0; i < n; i++)
	{
		if (nodes[i].rct.PtInRect(point))
		{
			WriteInfo(i);
		}
	}
}

void Graphs::WriteInfo(int n)
{
	CClientDC dc(infoContext);
	CString s;
	CPen pBlack(PS_SOLID, 2, RGB(0, 0, 0));
	RECT* rect = new RECT;
	infoContext->GetClientRect(rect);
	dc.SelectStockObject(NULL_PEN);
	dc.Rectangle(rect);
	dc.SelectObject(pBlack);

	auto toPrint = presenter->toPrint(n);
	int i = 0;
	for (auto it : toPrint) {
		s = it.c_str();
		dc.TextOutW(10, 10 + i * 20, s);
		i++;
	}
}

void Graphs::SetPresenter(Presenter* presenter)
{
	this->presenter = presenter;
	n = presenter->getSize();
	nodes.resize(n);
	DrawNodes();
}