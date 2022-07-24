#include "pch.h"
#include "SocketCtrl.h"
#include <afxwin.h>

HWND m_hParentWnd;

SocketCtrl::SocketCtrl()
{
}

SocketCtrl::~SocketCtrl()
{
	WSACleanup();
}

void SocketCtrl::InitServer(HWND hParentWnd,CString strIp,int nPort)
{
	m_hParentWnd = hParentWnd;
	m_strServerIp = strIp;
	m_nServerPort = nPort;
	//初始化Winsock
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	//创建socket
	m_sockServer = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	//绑定socket
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));						//每个字节都用0填充
	sockAddr.sin_family = PF_INET;												//使用IPv4地址
	//sockAddr.sin_addr.s_addr = inet_pton((LPSTR)(LPCTSTR)m_strServerIp);		//具体的IP地址
	InetPton(PF_INET,m_strServerIp,&sockAddr.sin_addr);
	sockAddr.sin_port = htons(m_nServerPort);							//端口
	bind(m_sockServer, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

	//监听客户端socket
	listen(m_sockServer, 20);

	//接受客户端连接请求
	AfxBeginThread(LoopReadBuff, this);
	
}

void SocketCtrl::ReceiveAccept()
{
	SOCKADDR clntAddr;
	int nSize = sizeof(SOCKADDR);
	m_sockListen = accept(m_sockServer, (SOCKADDR*)&clntAddr, &nSize);

	char recvBuffer[256] = {0};
	CString strDefaultMsg = _T("server:Welcome to connect !");
	int resSend = send(m_sockListen, (LPSTR)(LPCTSTR)strDefaultMsg, strDefaultMsg.GetLength(), 0);

	while (true)
	{
		if (resSend != strDefaultMsg.GetLength())	//发送的长度与需要发送的长度不等
		{
			break;
		}

		int recvLen = recv(m_sockListen, recvBuffer, sizeof(recvBuffer), 0);
		if (0 == recvLen)
		{
			break;
		}
		else if (recvLen < 0)
		{
			break;
		}
		//发送消息
		PostMessage(m_hParentWnd, WM_RECVSOCKDATA, TRUE, (LPARAM)&recvBuffer);
	}
}

void SocketCtrl::InitClient()
{
	//初始化Winsock
	//创建socket
	//连接服务端
	//发送和接收数据
	//断开连接
}

UINT SocketCtrl::LoopReadBuff(LPVOID pParam)
{
	SocketCtrl* pDlg = (SocketCtrl*)pParam;
	pDlg->ReceiveAccept();
	return 1;
}
