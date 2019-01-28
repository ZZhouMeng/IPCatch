// IPCatchDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IPCatch.h"
#include "IPCatchDlg.h"
#include <io.h> 
#include <fcntl.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;

#define SIO_RCVALL _WSAIOW(IOC_VENDOR,1)//接收所有包
#define BUFFER_SIZE 65535
#endif


char *MyIP;
struct hostent* pHostent;
Sip ip[1000];
BOOL stop;

int ssum; //源IP总数
int sum;  //所有总数
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
void InitConsoleWindow()
{
	AllocConsole();
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	int hCrt = _open_osfhandle((long)handle, _O_TEXT);
	FILE * hf = _fdopen(hCrt, "w");
	*stdout = *hf;
}


class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	enum { IDD = IDD_ABOUTBOX };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

protected:

	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{

}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIPCatchDlg dialog

CIPCatchDlg::CIPCatchDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIPCatchDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIPCatchDlg)
	m_ip = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CIPCatchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIPCatchDlg)
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Text(pDX, IDC_IP, m_ip);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CIPCatchDlg, CDialog)
	//{{AFX_MSG_MAP(CIPCatchDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Start, OnStart)
	ON_BN_CLICKED(IDC_Stop, OnStop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIPCatchDlg message handlers

BOOL CIPCatchDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	WSADATA WSAData;
	WSAStartup(MAKEWORD(2, 2), &WSAData);
	m_list.InsertColumn(0, "源地址", LVCFMT_LEFT, 190, 0);
	m_list.InsertColumn(1, "目的地址", LVCFMT_LEFT, 190, 0);
	m_list.InsertColumn(2, "包类型", LVCFMT_LEFT, 90, 0);
	m_list.InsertColumn(3, "源端口", LVCFMT_LEFT, 90, 0);
	m_list.InsertColumn(4, "目的端口", LVCFMT_LEFT, 90, 0);
	m_list.InsertColumn(5, "ICMP消息", LVCFMT_LEFT, 190, 0);
	m_list.InsertColumn(6, "数量", LVCFMT_LEFT, 50, 0);
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT);


	char hostname[128];
	gethostname(hostname, 128);
	pHostent = gethostbyname(hostname);


	MyIP = inet_ntoa(*(in_addr*)pHostent->h_addr);
	m_ip = MyIP;
	UpdateData(FALSE);
	sum = 0;
	ssum = 0;

	MyAddr.sin_family = AF_INET;
	MyAddr.sin_addr.s_addr = inet_addr(MyIP); // MyIp为本主机IP
	MyAddr.sin_port = htons(INADDR_ANY);

	//InitConsoleWindow();
	ChangeStyle(true);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CIPCatchDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CIPCatchDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM)dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CIPCatchDlg::OnQueryDragIcon()
{
	return (HCURSOR)m_hIcon;
}

void CIPCatchDlg::OnStart()
{
	// TODO: Add your control notification handler code here
	stop = false;
	sock = socket(AF_INET, SOCK_RAW, IPPROTO_IP);
	int flag = 1;
	setsockopt(sock, IPPROTO_IP, IP_HDRINCL, (char*)&flag, sizeof(flag));
	//绑定网卡IP地址
	bind(sock, (struct sockaddr*)&MyAddr, sizeof(SOCKADDR_IN));
	printf("%s", inet_ntoa(MyAddr.sin_addr));
	DWORD dwValue = 1;
	//调用ioctlsocket将网卡设为混杂模式
	ioctlsocket(sock, SIO_RCVALL, &dwValue);

	recvBuf = (char*)malloc(BUFFER_SIZE);
	ZeroMemory(recvBuf, BUFFER_SIZE);
	ChangeStyle(false);
	CWinThread* cap1 = AfxBeginThread(mThreadRecv, (void*)this);
}

UINT mThreadRecv(LPVOID pParam)
{
	CIPCatchDlg *cd = (CIPCatchDlg *)pParam;
	cd->DealMes();
	return 0;
}

void CIPCatchDlg::DealMes()
{

	while (!stop) {
		int ret = recv(sock, recvBuf, 4096, 0);
		IP_HEADER * iphead = (IP_HEADER*)recvBuf;
		if (ret > 0) {
			in_addr source, dest;
			CString str, packet, kind;
			CString* port;
			CString response = _T("");
			CString sport = _T("NULL");
			CString	dport = _T("NULL");
			source.S_un.S_addr = iphead->sourceIP;
			dest.S_un.S_addr = iphead->destIP;
			char csip[32];
			char destip[32];
			strcpy(csip, inet_ntoa(source));
			strcpy(destip, inet_ntoa(dest));
			DWORD sip;
			DWORD dip;
			sip = ntohl(iphead->sourceIP);
			dip = ntohl(iphead->destIP);
			int nHeaderLen = (iphead->iphVerLen & 0xf) * sizeof(ULONG);
			switch (iphead->ipProtocol)
			{
				case IPPROTO_TCP://调用函数解析TCP包
					port = DecodeTCPPacket(recvBuf + nHeaderLen);
					kind = "TCP";
					sport = port[0];
					dport = port[1];
					break;
				case IPPROTO_UDP://调用函数解析UDP包
					port = DecodeUDPPacket(recvBuf + nHeaderLen);
					kind = "UDP";
					sport = port[0];
					dport = port[1];
					break;
				case IPPROTO_ICMP://调用函数解析ICMP包
					response = DecodeICMPPacket(recvBuf + nHeaderLen);
					kind = "ICMP";

					break;
				default:
					break;
			}
			if (ssum != 0) {
				int index = FindMember(ip, sip, dip,kind,sport,dport);
				if (index < 0)
				{
					ip[ssum].count = 1;
					ip[ssum].sip = sip;
					ip[ssum].dip = dip;
					ip[ssum].kind = kind;
					ip[ssum].sport = sport;
					ip[ssum].dport = dport;
					CString str;
					str.Format("%d", ip[ssum].count);
					m_list.InsertItem(ssum, csip);
					m_list.SetItemText(ssum, 1, destip);
					m_list.SetItemText(ssum, 2, kind);
					m_list.SetItemText(ssum, 3, sport);
					m_list.SetItemText(ssum, 4, dport);
					m_list.SetItemText(ssum, 5, response);
					m_list.SetItemText(ssum, 6, str);
					ssum++;
				}
				else
				{
					ip[index].count++;
					CString str;
					str.Format("%d", ip[index].count);
					m_list.SetItemText(index, 6, str);
				}
			}
			else {
				ip[ssum].count = 1;
				ip[ssum].sip = sip;
				ip[ssum].dip = dip;
				ip[ssum].kind = kind;
				ip[ssum].sport = sport;
				ip[ssum].dport = dport;
				CString str;
				str.Format("%d", ip[ssum].count);
				m_list.InsertItem(ssum, csip);
				m_list.SetItemText(ssum, 1, destip);
				m_list.SetItemText(ssum, 2, kind);
				m_list.SetItemText(ssum, 3, sport);
				m_list.SetItemText(ssum, 4, dport);
				m_list.SetItemText(ssum, 5, response);
				m_list.SetItemText(ssum, 6, str);
				ssum++;
			}
			sum++;
			CString str1;
			str1.Format("%d", sum);
			GetDlgItem(IDC_Sum)->SetWindowText(str1);
		}
	}


}
int CIPCatchDlg::FindMember(Sip s_ip[], DWORD sip, DWORD dip,CString kind,CString sport, CString dport)
{
	for (int i = 0; i < ssum; i++)
	{
		if (s_ip[i].sip == sip && s_ip[i].dip==dip && s_ip[i].kind == kind && s_ip[i].sport == sport && s_ip[i].dport == dport)
		{
			return i;
		}

	}
	return -1;
}

void CIPCatchDlg::OnStop()
{
	// TODO: Add your control notification handler code here
	stop = true;
	closesocket(sock);
	ChangeStyle(true);
}

void CIPCatchDlg::ChangeStyle(BOOL temp)
{
	GetDlgItem(IDC_Start)->EnableWindow(temp);
	GetDlgItem(IDC_Stop)->EnableWindow(!temp);
}

CString* CIPCatchDlg::DecodeTCPPacket(char  * pData)
{
	CString *port = new CString[2];
	CString str;
	TCPHeader *pTCPHdr = (TCPHeader *)pData;
	str.Format("%u", ntohs(pTCPHdr->tcpSourcePort));
	port[0] = str;
	str.Format("%u", ntohs(pTCPHdr->tcpDestinationPort));
	port[1] = str;
	return port;
}
CString* CIPCatchDlg::DecodeUDPPacket(char * pData)
{
	CString *port = new CString[2];
	CString str;;
	UDPHeader *pUDPHdr = (UDPHeader *)pData;
	str.Format("%u", ntohs(pUDPHdr->udpSourcePort));
	port[0] = str;
	str.Format("%u", ntohs(pUDPHdr->udpDestinationPort));
	port[1] = str;
	return port;
}

CString CIPCatchDlg::DecodeICMPPacket(char * pData)
{
	CString response;
	ICMPHeader *pICMHdr = (ICMPHeader*)pData;
	switch (pICMHdr->icmpType)
	{
	case 0:
		response = _T("Echo Response.\n"); break;
	case 8:
		response = _T("Echo Request.\n"); break;
	case 3:
		response = _T("Destination Unreachable.\n"); break;
	case 11:
		response = _T("Datagram Timeout(TTL=0).\n"); break;
	}
	return response;
}