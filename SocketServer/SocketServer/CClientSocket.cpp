// ClientSocket.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "SocketServer.h"
#include "CClientSocket.h"
#include "CListenSocket.h"
#include "SocketServerDlg.h"


// CClientSocket
int index = 0;
CString alias[100][2];

CClientSocket::CClientSocket()
{
}

CClientSocket::~CClientSocket()
{
}


// CClientSocket 멤버 함수
void CClientSocket::SetListenSocket(CAsyncSocket* pSocket)
{
	m_pListenSocket = pSocket;
}
// CClientSocket 멤버 함수


void CClientSocket::OnClose(int nErrorCode)
{
	CSocket::OnClose(nErrorCode);

	CListenSocket* pServerSocket = (CListenSocket*)m_pListenSocket;
	pServerSocket->CloseClientSocket(this);
}

void CClientSocket::OnReceive(int nErrorCode)
{
	int i, check = 0;
	CString strTmp = _T(""), strIPAddress = _T("");
	UINT uPortNumber = 0;
	TCHAR strBuffer[1024];
	::ZeroMemory(strBuffer, sizeof(strBuffer));

	GetPeerName(strIPAddress, uPortNumber);
	if (Receive(strBuffer, sizeof(strBuffer)) > 0) {
		CSocketServerDlg* pMain = (CSocketServerDlg*)AfxGetMainWnd();
		
		CString portStr;
		portStr.Format(L"%d", uPortNumber);

		for (i = index - 1; i >= 0; i--) {
			if (portStr == alias[i][0]) {
				strTmp.Format(_T("[%s]: %s"), alias[i][1], strBuffer);
				break;
			}
		}

		if (i == -1) {
			strTmp.Format(_T("[%s:%d]: %s"), strIPAddress, uPortNumber, strBuffer);
		}

		if (strTmp.Find(L"alias:") != -1) {
			alias[index][0] = portStr;
			CString temp = strBuffer;
			temp.Delete(0, 6);
			alias[index][1] = temp;
			index++;
			check = 1;
		}

		if (check == 0) {
			int cnt = pMain->m_List.GetCount();
			pMain->m_List.InsertString(cnt, strTmp);

			CListenSocket* pServerSocket = (CListenSocket*)m_pListenSocket;

			TCHAR *tChr = (TCHAR*)(LPCTSTR)strTmp;
			pServerSocket->SendAllMessage(tChr);
		}
		else {
			check = 0;
		}
	}

	CSocket::OnReceive(nErrorCode);
}