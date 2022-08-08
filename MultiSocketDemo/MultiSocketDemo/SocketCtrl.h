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
	int		m_nType;			//TCP类型
	char	m_szRecvBuff[256];	//接收缓存
	void ClearRecvBuff();

	SysTimeStamp m_sysTimeStamp;//时间戳
	
	/*
		Server 变量、函数
	*/ 
	SOCKET	m_sockServer;	//accept 调用
	CString m_strServerIp;	//
	int		m_nServerPort;	//
	typedef std::function<void()> EventCallback;
	std::list<SOCKET> m_sockList;
	/*
		Client 变量、函数
	*/
	SOCKET	m_sockClient;	//客户端
	BOOL	m_bConnectServ;	//是否成功连接服务器

};

