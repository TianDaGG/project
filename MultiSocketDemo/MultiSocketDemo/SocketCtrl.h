#pragma once
/*
	socket 管理类
	描述：
		提供socket的并发连接管理
		没有文件操作，全部数据在内存处理
*/
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")


#define WM_RECVSOCKDATA (WM_USER+100)  

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
	void ReceiveAccept();
	void InitClient();

	static UINT LoopReadBuff(LPVOID pParam);

	//void SendData();
public:
	int m_nType;	//TCP类型
	
	SOCKET m_sockServer;
	SOCKET m_sockListen;	//连接的客户端
	CString m_strServerIp;
	int		m_nServerPort;

};

