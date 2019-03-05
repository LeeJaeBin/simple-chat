// CAlias.cpp: 구현 파일
//

#include "stdafx.h"
#include "SocketClient.h"
#include "SocketClientDlg.h"
#include "CAlias.h"
#include "afxdialogex.h"


// CAlias 대화 상자

IMPLEMENT_DYNAMIC(CAlias, CDialogEx)

CAlias::CAlias(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

CAlias::~CAlias()
{
}

void CAlias::DoDataExchange(CDataExchange* pDX)
{

	CButton *button1 = (CButton*)GetDlgItem(IDOK);
	CButton *button2 = (CButton*)GetDlgItem(IDCANCEL);
	button1->DestroyWindow();
	button2->DestroyWindow();

	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAlias, CDialogEx)
	ON_BN_CLICKED(IDC_ALIAS, &CAlias::OnBnClickedAlias)
END_MESSAGE_MAP()


// CAlias 메시지 처리기


void CAlias::OnBnClickedAlias()
{
	CString str;
	CString alias = L"alias:";

	GetDlgItemText(IDC_EDIT1, str);
	((CSocketClientDlg *)GetParent())->name = str;

	str = alias + str;
	((CSocketClientDlg *)GetParent())->m_Socket.Send((LPVOID)(LPCTSTR)str, str.GetLength() * 2);
	
	::SendMessage(this->m_hWnd, WM_CLOSE, NULL, NULL);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


BOOL CAlias::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		{   // 위 VK_RETURN은 Enter, VK_ESCAPE는 ESC을 의미함. 필요시 하나만 사용.
			OnBnClickedAlias();
			return true;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
