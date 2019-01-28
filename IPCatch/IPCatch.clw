; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CIPCatchDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "IPCatch.h"

ClassCount=3
Class1=CIPCatchApp
Class2=CIPCatchDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_IPCATCH_DIALOG

[CLS:CIPCatchApp]
Type=0
HeaderFile=IPCatch.h
ImplementationFile=IPCatch.cpp
Filter=N

[CLS:CIPCatchDlg]
Type=0
HeaderFile=IPCatchDlg.h
ImplementationFile=IPCatchDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=IPCatchDlg.h
ImplementationFile=IPCatchDlg.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_IPCATCH_DIALOG]
Type=1
Class=CIPCatchDlg
ControlCount=7
Control1=IDC_STATIC,static,1342308352
Control2=IDC_IP,edit,1484849280
Control3=IDC_Start,button,1342242816
Control4=IDC_Stop,button,1342242816
Control5=IDC_LIST1,SysListView32,1350631425
Control6=IDC_STATIC,static,1342308352
Control7=IDC_Sum,edit,1476460672

