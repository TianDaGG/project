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
	//��ʼ��Winsock
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	//����socket
	m_sockServer = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	//��socket
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));						//ÿ���ֽڶ���0���
	sockAddr.sin_family = PF_INET;												//ʹ��IPv4��ַ
	//sockAddr.sin_addr.s_addr = inet_pton((LPSTR)(LPCTSTR)m_strServerIp);		//�����IP��ַ
	InetPton(PF_INET,m_strServerIp,&sockAddr.sin_addr);
	sockAddr.sin_port = htons(m_nServerPort);							//�˿�
	bind(m_sockServer, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

	//�����ͻ���socket
	listen(m_sockServer, 20);

	//���ܿͻ�����������
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
		if (resSend != strDefaultMsg.GetLength())	//���͵ĳ�������Ҫ���͵ĳ��Ȳ���
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
		//������Ϣ
		PostMessage(m_hParentWnd, WM_RECVSOCKDATA, TRUE, (LPARAM)&recvBuffer);
	}
}

void SocketCtrl::InitClient()
{
	//��ʼ��Winsock
	//����socket
	//���ӷ����
	//���ͺͽ�������
	//�Ͽ�����
}

UINT SocketCtrl::LoopReadBuff(LPVOID pParam)
{
	SocketCtrl* pDlg = (SocketCtrl*)pParam;
	pDlg->ReceiveAccept();
	return 1;
}
