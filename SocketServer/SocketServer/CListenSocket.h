#pragma once

class CListenSocket : public CAsyncSocket
{
public:
	CListenSocket();
	virtual ~CListenSocket();

	CPtrList m_ptrClientSocketList;
	void OnAccept(int nErrorCode);
	void CloseClientSocket(CSocket* pClient);
	void SendAllMessage(TCHAR* pszMessage);

};