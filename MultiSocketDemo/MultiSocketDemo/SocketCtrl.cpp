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
	//��ʼ��Winsock
	WSADATA wsaData;
	::WSAStartup(MAKEWORD(2, 2), &wsaData);

	//����socket
	m_sockServer = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	//��socket
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));						//ÿ���ֽڶ���0���
	sockAddr.sin_family = PF_INET;												//ʹ��IPv4��ַ
	//sockAddr.sin_addr.s_addr = inet_pton((LPSTR)(LPCTSTR)m_strServerIp);		//�����IP��ַ
	InetPton(PF_INET,m_strServerIp,&sockAddr.sin_addr);
	sockAddr.sin_port = htons(m_nServerPort);							//�˿�
	::bind(m_sockServer, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));


	//�����ͻ���socket
	listen(m_sockServer, 20);

	//���ܿͻ�����������
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
			AfxMessageBox(_T("���ݷ���ʧ��"));
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
		AfxMessageBox(_T("Ƕ���ִ�ʧ��"));
		return;
	}
	m_sockClient = socket(AF_INET, SOCK_STREAM, 0);
	if (m_sockClient < 0)
	{
		AfxMessageBox(_T("�׽��ִ���ʧ��"));
		return;
	}

	SOCKADDR_IN client_in;
	//client_in.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//�������ַ�ַ���ת���ɶ�������ʽ
	InetPton(AF_INET, strServerIp, &client_in.sin_addr);
	client_in.sin_family = AF_INET;
	client_in.sin_port = htons(_ttoi(strPort));

	if (connect(m_sockClient, (SOCKADDR*)&client_in, sizeof(SOCKADDR)) == SOCKET_ERROR)
	{
		AfxMessageBox(_T("�׽�������ʧ��"));
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
		int nRet = 0;	//��¼���ͻ��߽��ܵ��ֽ���
		TIMEVAL tv;		//���ó�ʱ�ȴ�ʱ��
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
					strTimeStamp.Format(_T("ʱ���(����):%lld"), pDlg->m_sysTimeStamp.GetNowTime());
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
				strTimeStamp.Format(_T("ʱ���(����):%lld"), pDlg->m_sysTimeStamp.GetNowTime());
				//AfxMessageBox(strTimeStamp);
				//std::cout << (*iter) << "������Ϣ:" << m_szRecvBuff << std::endl;
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
