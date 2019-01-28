// IPCatchDlg.h : header file
//

#if !defined(AFX_IPCATCHDLG_H__51B9C436_8F59_4D27_8A96_04073CE67D3C__INCLUDED_)
#define AFX_IPCATCHDLG_H__51B9C436_8F59_4D27_8A96_04073CE67D3C__INCLUDED_

#if _MSC_VER > 1000
#include <winsock2.h>
#include <WS2tcpip.h>
#include"mstcpip.h"
#pragma comment(lib,"ws2_32.lib")
#include "mhead.h"
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CIPCatchDlg dialog

class CIPCatchDlg : public CDialog
{
// Construction
public:
	CIPCatchDlg(CWnd* pParent = NULL);	// standard constructor
	friend UINT mThreadRecv(LPVOID pParam);
	 void DealMes() ;
	 int FindMember(Sip s_ip[], DWORD sip, DWORD dip, CString kind, CString sport, CString dport);
	 void ChangeStyle(BOOL temp);

// Dialog Data
	//{{AFX_DATA(CIPCatchDlg)
	enum { IDD = IDD_IPCATCH_DIALOG };
	CListCtrl	m_list;
	CString	m_ip;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIPCatchDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	SOCKET sock;
	SOCKADDR_IN MyAddr;
	char * recvBuf;
	// Generated message map functions
	//{{AFX_MSG(CIPCatchDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnStart();
	afx_msg void OnStop();
	CString* DecodeTCPPacket(char  * pData);
	CString* DecodeUDPPacket(char * pData);
	CString DecodeICMPPacket(char * pData);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IPCATCHDLG_H__51B9C436_8F59_4D27_8A96_04073CE67D3C__INCLUDED_)
