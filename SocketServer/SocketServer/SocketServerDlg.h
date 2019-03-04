#pragma once
#include "CListenSocket.h"
#include "afxwin.h"

// CSocketServerDlg 대화 상자
class CSocketServerDlg : public CDialogEx
{
	// 생성입니다.
public:
	CSocketServerDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.
	CListenSocket m_ListenSocket;
	CListBox* clientList;
	// 대화 상자 데이터입니다.
	enum { IDD = IDD_SOCKETSERVER_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.
	void OnDestroy();


	// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListBox m_List;
};
