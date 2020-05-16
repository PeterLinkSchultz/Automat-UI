
#include <map>
#include "Model/Executor.h"
#include "ScrollController.h"
// mainDlg.h: файл заголовка
//

using namespace std;

#pragma once


// Диалоговое окно CmainDlg
class CmainDlg : public CDialogEx
{
// Создание
public:
	CmainDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAIN_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_picture;
private:
	void ClearView();
	void Run();
	Graphs* graphs;
	map<int, ScrollController*> scrollCollection;
	Executor* executor;
	bool isReady = false;
	bool isRunned = false;
	CString filePath;
	void RedrawButtons();
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CScrollBar m_scrollState;
	CScrollBar m_scrollState_1;
	CScrollBar m_scrollState_2;
	afx_msg void OnBnClickedButtonNext();
	CButton m_btnNext;
	CButton m_btnRun;
	CButton m_btnAgain;
	afx_msg void OnFileOpen();
	afx_msg void OnBnClickedButtonRun();
	afx_msg void OnBnClickedButtonAgain();
	afx_msg void OnBnClickedButtonReset();
};
