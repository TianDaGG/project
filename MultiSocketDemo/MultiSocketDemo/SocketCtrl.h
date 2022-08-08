#pragma once
/*
	socket ������
	������
		�ṩsocket�Ĳ������ӹ���
		û���ļ�������ȫ���������ڴ洦��
*/

#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#include "SysTimeStamp.h"
#include <functional>
#include <list>


#define WM_RECVSOCKDATA (WM_USER+100)  

#define WM_SOCKETACCEPT (WM_USER+200)  
#define WM_SOCKETRECV	(WM_USER+201)  
#define WM_SOCKETCLOSE	(WM_USER+202)  

class SocketCtrl
{
public:
	SocketCtrl();
	~SocketCtrl();
public:
	enum {
		TCP_CLIENT=0, 
		TCP_SERVER
	};
	void InitServer(HWND hParentWnd, CString strIp, int nPort);
	void SendMsg(CString strMsg);
	void InitClient(CString strServerIp, CString strPort);

	static UINT Accept(LPVOID pParam);
	static UINT Loop(LPVOID pParam);
public:
	int		m_nType;			//TCP����
	char	m_szRecvBuff[256];	//���ջ���
	void ClearRecvBuff();

	SysTimeStamp m_sysTimeStamp;//ʱ���
	
	/*
		Server ����������
	*/ 
	SOCKET	m_sockServer;	//accept ����
	CString m_strServerIp;	//
	int		m_nServerPort;	//
	typedef std::function<void()> EventCallback;
	std::list<SOCKET> m_sockList;
	/*
		Client ����������
	*/
	SOCKET	m_sockClient;	//�ͻ���
	BOOL	m_bConnectServ;	//�Ƿ�ɹ����ӷ�����

};

