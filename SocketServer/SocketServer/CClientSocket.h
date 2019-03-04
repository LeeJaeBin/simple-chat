#pragma once

class CClientSocket : public CSocket
{
public:
	CClientSocket();
	virtual ~CClientSocket();

	CAsyncSocket *m_pListenSocket;
	void SetListenSocket(CAsyncSocket* pSocket);
	void OnClose(int nErrorCode);
	void OnReceive(int nErrorCode);

};
