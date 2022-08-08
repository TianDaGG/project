#include "pch.h"
#include "SocketCtrl.h"
#include <afxwin.h>
#include "SysTimeStamp.h"
#include <vcruntime_string.h>




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
	m_nType = TCP_SERVER;
	ClearRecvBuff();

	m_hParentWnd = hParentWnd;
	m_strServerIp = strIp;
	m_nServerPort = nPort;
	//初始化Winsock
	WSADATA wsaData;
	::WSAStartup(MAKEWORD(2, 2), &wsaData);

	//创建socket
	m_sockServer = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	//绑定socket
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));						//每个字节都用0填充
	sockAddr.sin_family = PF_INET;												//使用IPv4地址
	//sockAddr.sin_addr.s_addr = inet_pton((LPSTR)(LPCTSTR)m_strServerIp);		//具体的IP地址
	InetPton(PF_INET,m_strServerIp,&sockAddr.sin_addr);
	sockAddr.sin_port = htons(m_nServerPort);							//端口
	::bind(m_sockServer, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));


	//监听客户端socket
	listen(m_sockServer, 20);

	//接受客户端连接请求
	AfxBeginThread(Accept, this);
	AfxBeginThread(Loop, this);

}

void SocketCtrl::SendMsg(CString strMsg)
{
	if (m_nType == TCP_CLIENT)
	{
		USES_CONVERSION;
		char* pFileName = T2A(strMsg);
		int nRet = send(m_sockClient, pFileName, (int)strlen(pFileName), 0);
		if (nRet == SOCKET_ERROR) {
			AfxMessageBox(_T("数据发送失败"));
			return;
		}
	}
}

void SocketCtrl::InitClient(CString strServerIp,CString strPort)
{
	m_nType = TCP_CLIENT;
	m_bConnectServ = FALSE;
	WSADATA wsadata;
	if (0 != WSAStartup(MAKEWORD(2, 2), &wsadata))
	{
		AfxMessageBox(_T("嵌套字打开失败"));
		return;
	}
	m_sockClient = socket(AF_INET, SOCK_STREAM, 0);
	if (m_sockClient < 0)
	{
		AfxMessageBox(_T("套接字创建失败"));
		return;
	}

	SOCKADDR_IN client_in;
	//client_in.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//将网络地址字符串转换成二进制形式
	InetPton(AF_INET, strServerIp, &client_in.sin_addr);
	client_in.sin_family = AF_INET;
	client_in.sin_port = htons(_ttoi(strPort));

	if (connect(m_sockClient, (SOCKADDR*)&client_in, sizeof(SOCKADDR)) == SOCKET_ERROR)
	{
		AfxMessageBox(_T("套接字连接失败"));
		return;
	}
	m_bConnectServ = TRUE;
}

UINT SocketCtrl::Accept(LPVOID pParam)
{
	SocketCtrl* pDlg = (SocketCtrl*)pParam;
	while (TRUE)
	{
		SOCKADDR clientAddr;
		int nSize = sizeof(SOCKADDR);
		SOCKET sockListen = accept(pDlg->m_sockServer, (SOCKADDR*)&clientAddr, &nSize);
		//INVALID_SOCKET
		//FD_SET
		if (INVALID_SOCKET != sockListen)
		{
			bool bFound = (std::find(pDlg->m_sockList.begin(), pDlg->m_sockList.end(), sockListen) != pDlg->m_sockList.end());
			if (!bFound)
			{
				char szAccept[5] = {0};
				sprintf_s(szAccept,5, "%d", (size_t)sockListen);
				PostMessage(m_hParentWnd, WM_RECVSOCKDATA, (WPARAM)WM_SOCKETACCEPT, (LPARAM)szAccept);
				pDlg->m_sockList.push_back(sockListen);
				const char* szDefault = "server:Welcome!";
				int resSend = send(sockListen, szDefault, strlen(szDefault), 0);
			}
		}
	}
	
	return 1;
}

UINT SocketCtrl::Loop(LPVOID pParam)
{
	SocketCtrl* pDlg = (SocketCtrl*)pParam;
	if (pDlg->m_nType == TCP_SERVER)
	{
		fd_set fdRead;
		int nRet = 0;	//记录发送或者接受的字节数
		TIMEVAL tv;		//设置超时等待时间
		tv.tv_sec = 1;
		tv.tv_usec = 0;
		while (true)
		{
			if (pDlg->m_sockList.size() == 0)
				continue;
			FD_ZERO(&fdRead);
			for (std::list<SOCKET>::iterator iter = pDlg->m_sockList.begin(); iter != pDlg->m_sockList.end(); ++iter)
			{
				FD_SET((*iter), &fdRead);
			}
			nRet = select(0, &fdRead, NULL, NULL, &tv);

			if (nRet == 0)
			{
				continue;
			}

			for (std::list<SOCKET>::iterator iter = pDlg->m_sockList.begin(); iter != pDlg->m_sockList.end(); ++iter)
			{
				if (FD_ISSET((*iter), &fdRead))
				{
					char szRecvBuff[256] = { 0 };
					nRet = recv((*iter), szRecvBuff, 256, 0);
					if (nRet == 0 || (nRet == SOCKET_ERROR && WSAGetLastError() == WSAECONNRESET))
					{
						char szClose[5] = { 0 };
						sprintf_s(szClose, 5, "%d", (size_t)*iter);
						PostMessage(m_hParentWnd, WM_RECVSOCKDATA, (WPARAM)WM_SOCKETCLOSE, (LPARAM)szClose);
						::closesocket((*iter));
						pDlg->m_sockList.erase(iter);
						break;
					}
					CString strTimeStamp;
					strTimeStamp.Format(_T("时间戳(纳秒):%lld"), pDlg->m_sysTimeStamp.GetNowTime());
					//AfxMessageBox(strTimeStamp);

					char szRecv[5] = {0};
					sprintf_s(szRecv, 5, "%d", (size_t)(*iter));
					strcat_s(szRecv,262, szRecvBuff);
					PostMessage(m_hParentWnd, WM_RECVSOCKDATA, (WPARAM)WM_SOCKETRECV, (LPARAM)&szRecv);//m_szRecvBuff

				}
			}
		}
	}
	else if (pDlg->m_nType == TCP_CLIENT)
	{
		while (TRUE)
		{
			char szRecvBuff[256] = { 0 };
			int nRet = recv(pDlg->m_sockClient, szRecvBuff, 256, 0);
			if (nRet == 0 || (nRet == SOCKET_ERROR && WSAGetLastError() == WSAECONNRESET))
			{
				closesocket(pDlg->m_sockClient);
			}
			else
			{
				CString strTimeStamp;
				strTimeStamp.Format(_T("时间戳(纳秒):%lld"), pDlg->m_sysTimeStamp.GetNowTime());
				//AfxMessageBox(strTimeStamp);
				//std::cout << (*iter) << "发来消息:" << m_szRecvBuff << std::endl;
				PostMessage(m_hParentWnd, WM_RECVSOCKDATA, TRUE, (LPARAM)&szRecvBuff);//m_szRecvBuff
			}
		}
	}
	
	return TRUE;
}

void SocketCtrl::ClearRecvBuff()
{
	memset(m_szRecvBuff, 0, 256);
}
