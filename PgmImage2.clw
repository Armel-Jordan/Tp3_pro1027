; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMainFrame
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "PgmImage2.h"
LastPage=0

ClassCount=6
Class1=CPgmImage2App
Class2=CPgmImage2Doc
Class3=CPgmImage2View
Class4=CMainFrame

ResourceCount=5
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class5=CAboutDlg
Resource3=IDD_ABOUTBOX (French (France))
Resource4=IDR_MAINFRAME (French (France))
Class6=CDialogImage
Resource5=IDD_DIALOG_IMAGE

[CLS:CPgmImage2App]
Type=0
HeaderFile=PgmImage2.h
ImplementationFile=PgmImage2.cpp
Filter=N

[CLS:CPgmImage2Doc]
Type=0
HeaderFile=PgmImage2Doc.h
ImplementationFile=PgmImage2Doc.cpp
Filter=N

[CLS:CPgmImage2View]
Type=0
HeaderFile=PgmImage2View.h
ImplementationFile=PgmImage2View.cpp
Filter=C


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=ID_IMAGE_OUVRIR_AFFICHER




[CLS:CAboutDlg]
Type=0
HeaderFile=PgmImage2.cpp
ImplementationFile=PgmImage2.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_MRU_FILE1
Command6=ID_APP_EXIT
Command10=ID_EDIT_PASTE
Command11=ID_APP_ABOUT
CommandCount=11
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_CUT
Command9=ID_EDIT_COPY

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
CommandCount=13
Command4=ID_EDIT_UNDO
Command13=ID_PREV_PANE


[MNU:IDR_MAINFRAME (French (France))]
Type=1
Class=CMainFrame
Command1=ID_IMAGE_OUVRIR_AFFICHER
CommandCount=1

[ACL:IDR_MAINFRAME (French (France))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

[DLG:IDD_ABOUTBOX (French (France))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_DIALOG_IMAGE]
Type=1
Class=CDialogImage
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816

[CLS:CDialogImage]
Type=0
HeaderFile=DialogImage.h
ImplementationFile=DialogImage.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDialogImage

