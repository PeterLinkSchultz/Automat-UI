
// mainDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "main.h"
#include "mainDlg.h"
#include "afxdialogex.h"
#include "NodePresenter.h"
#include "DeltaGroupPresenter.h"
#include "LambdaGroupPresenter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define StateStart CPoint(35, 52)
#define StateCont CRect(StateStart.x - 10, StateStart.y - 2, StateStart.x + 270, StateStart.y + 26)

#define Temp1Start CPoint(35, 143)
#define Temp1Cont CRect(Temp1Start.x - 10, Temp1Start.y - 2, Temp1Start.x + 270, Temp1Start.y + 26)

#define Temp2Start CPoint(35, 215)
#define Temp2Cont CRect(Temp2Start.x - 10, Temp2Start.y - 2, Temp2Start.x + 270, Temp2Start.y + 26)

// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Диалоговое окно CmainDlg
CmainDlg::CmainDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MAIN_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SCROLL_STATE, m_scrollState);
	DDX_Control(pDX, IDC_SCROLL_STATE_1, m_scrollState_1);
	DDX_Control(pDX, IDC_SCROLL_STATE_2, m_scrollState_2);
	DDX_Control(pDX, IDC_BUTTON_NEXT, m_btnNext);
	DDX_Control(pDX, IDC_BUTTON_RUN, m_btnRun);
	DDX_Control(pDX, IDC_BUTTON_AGAIN, m_btnAgain);
}

BEGIN_MESSAGE_MAP(CmainDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON_NEXT, &CmainDlg::OnBnClickedButtonNext)
	ON_COMMAND(ID_FILE_OPEN, &CmainDlg::OnFileOpen)
	ON_BN_CLICKED(IDC_BUTTON_RUN, &CmainDlg::OnBnClickedButtonRun)
	ON_BN_CLICKED(IDC_BUTTON_AGAIN, &CmainDlg::OnBnClickedButtonAgain)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CmainDlg::OnBnClickedButtonReset)
END_MESSAGE_MAP()


// Обработчики сообщений CmainDlg

BOOL CmainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	CWnd* stateInfo = GetDlgItem(IDC_STATE_INFO);

	int id = m_scrollState.GetDlgCtrlID();
	ScrollController *controller = new ScrollController(this, id, StateCont, stateInfo, StateStart);
	scrollCollection.insert(std::pair<int, ScrollController*>(id, controller));

	id = m_scrollState_1.GetDlgCtrlID();
	controller = new ScrollController(this, id, Temp1Cont, stateInfo, Temp1Start);
	scrollCollection.insert(std::pair<int, ScrollController*>(id, controller));

	id = m_scrollState_2.GetDlgCtrlID();
	controller = new ScrollController(this, id, Temp2Cont, stateInfo, Temp2Start);
	scrollCollection.insert(std::pair<int, ScrollController*>(id, controller));

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CmainDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CmainDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CmainDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CmainDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	
}


void CmainDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	for (auto& it : scrollCollection) {
		it.second->CheckPoint(point);
	}
}


void CmainDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int CurPos = pScrollBar->GetScrollPos();
	LPINT min = new int, max = new int;
	pScrollBar->GetScrollRange(min, max);

	switch (nSBCode)
	{
	case SB_LEFT:      // Scroll to far left.
		CurPos = *min;
		break;
	case SB_RIGHT:      // Scroll to far right.
		CurPos = *max;
		break;
	case SB_ENDSCROLL:   // End scroll.
		break;
	case SB_LINELEFT:      // Scroll left.
		if (CurPos > *min)
			CurPos--;
		break;
	case SB_LINERIGHT:   // Scroll right.
		if (CurPos < *max)
			CurPos++;
		break;
		/*
	case SB_PAGELEFT:    // Scroll one page left.
	{
		// Get the page size. 
		SCROLLINFO   info;
		pScrollBar->GetScrollInfo(&info, SIF_ALL);

		if (CurPos > 0)
			CurPos = max(0, CurPos - (int)info.nPage);
	}
	break;

	case SB_PAGERIGHT:      // Scroll one page right
	{
		// Get the page size. 
		SCROLLINFO info;
		pScrollBar->GetScrollInfo(&info, SIF_ALL);

		if (CurPos < 122)
			CurPos = min(122, CurPos + (int)info.nPage);
	}
	break;*/

	case SB_THUMBPOSITION: // Scroll to absolute position. nPos is the position
		CurPos = nPos;      // of the scroll box at the end of the drag operation.
		break;

	case SB_THUMBTRACK:   // Drag scroll box to specified position. nPos is the
		CurPos = nPos;     // position that the scroll box has been dragged to.
		break;
	}

	pScrollBar->SetScrollPos(CurPos);
	int id = pScrollBar->GetDlgCtrlID();

	ScrollController* controller = scrollCollection.at(id);

	if (controller != nullptr)
	{
		controller->Update(CurPos);
	}

	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}


void CmainDlg::OnBnClickedButtonNext()
{
	auto current = executor->getDeltaGroups();
	if (current->size() != 0) {
		scrollCollection.at(m_scrollState_1.GetDlgCtrlID())->SetNodesPresenter(new DeltaGroupPresenter(current), m_scrollState_1);
		scrollCollection.at(m_scrollState_1.GetDlgCtrlID())->RedrawField();
	}
	bool ended = executor->next();
	auto groups = executor->getDeltaGroups();

	scrollCollection.at(m_scrollState_2.GetDlgCtrlID())->SetNodesPresenter(new DeltaGroupPresenter(groups), m_scrollState_2);
	scrollCollection.at(m_scrollState_2.GetDlgCtrlID())->RedrawField();

	if (ended) {
		isReady = false;
		RedrawButtons();
	}
}

void CmainDlg::OnFileOpen()
{
	CFileDialog fileDialog(TRUE);

	int result = fileDialog.DoModal();	
	if (result == IDOK)	
	{
		isReady = true;
		isRunned = false;
		filePath = fileDialog.GetPathName();

		RedrawButtons();
		ClearView();
	}
}

void CmainDlg::Run()
{
	delete executor;
	StateList stateList(filePath);
	executor = new Executor(stateList);
	executor->init();

	auto nodes = executor->getInitNodes();
	scrollCollection.at(m_scrollState.GetDlgCtrlID())->SetNodesPresenter(new NodePresenter(nodes), m_scrollState);
	scrollCollection.at(m_scrollState.GetDlgCtrlID())->RedrawField();

	auto lambdaGroups = executor->getLambdaGroups();
	scrollCollection.at(m_scrollState_1.GetDlgCtrlID())->SetNodesPresenter(new LambdaGroupPresenter(lambdaGroups), m_scrollState_1);
	scrollCollection.at(m_scrollState_1.GetDlgCtrlID())->RedrawField();
}

void CmainDlg::ClearView()
{
	for (auto it : scrollCollection) {
		it.second->ClearField();
	}
	auto ctx = GetDlgItem(IDC_STATE_INFO);
	CClientDC dc(ctx);
	RECT* rect = new RECT;
	ctx->GetClientRect(rect);
	dc.SelectStockObject(NULL_PEN);
	dc.Rectangle(rect);
}

void CmainDlg::OnBnClickedButtonRun()
{
	isRunned = true;
	RedrawButtons();
	Run();
}


void CmainDlg::OnBnClickedButtonAgain()
{
	isReady = true;
	RedrawButtons();
	ClearView();
	Run();
}


void CmainDlg::OnBnClickedButtonReset()
{
	isReady = true;
	isRunned = false;
	RedrawButtons();
	ClearView();
}

void CmainDlg::RedrawButtons()
{
	m_btnRun.EnableWindow(isReady && !isRunned);
	m_btnNext.EnableWindow(isReady && isRunned);
	m_btnAgain.EnableWindow(isRunned);
}