#include "stdafx.h"
#include "CConnectSocket.h"
#include "SocketClientDlg.h"


CConnectSocket::CConnectSocket()
{
}


CConnectSocket::~CConnectSocket()
{
}

void CConnectSocket::OnClose(int nErrorCode)
{
	ShutDown();
	Close();

	CSocket::OnClose(nErrorCode);

	AfxMessageBox(_T("ERROR:Disconnected from server!"));
	::PostQuitMessage(0);
}

void CConnectSocket::OnReceive(int nErrorCode)
{
	TCHAR szBuffer[1024];
	::ZeroMemory(szBuffer, sizeof(szBuffer));

	if (Receive(szBuffer, sizeof(szBuffer)) > 0) {
		CSocketClientDlg* pMain = (CSocketClientDlg*)AfxGetMainWnd();
		int cnt = pMain->m_List.GetCount();
		pMain->m_List.InsertString(cnt, szBuffer);
	}
	CSocket::OnReceive(nErrorCode);
}