// CFuncSmoothDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MyVisionTool.h"
#include "CFuncSmoothDlg.h"
#include "afxdialogex.h"


// CFuncSmoothDlg 对话框

IMPLEMENT_DYNAMIC(CFuncSmoothDlg, CDialogEx)

CFuncSmoothDlg::CFuncSmoothDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SMOOTHBLUR, pParent)
{

}

CFuncSmoothDlg::~CFuncSmoothDlg()
{
}

void CFuncSmoothDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFuncSmoothDlg, CDialogEx)
END_MESSAGE_MAP()


// CFuncSmoothDlg 消息处理程序
