// FuncMorphDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MyVisionTool.h"
#include "MyVisionToolDlg.h"
#include "FuncMorphDlg.h"
#include "afxdialogex.h"


// FuncMorphDlg 对话框

IMPLEMENT_DYNAMIC(CFuncMorphDlg, CDialogEx)

CFuncMorphDlg::CFuncMorphDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_MORPHOLOGY, pParent)
{

}

CFuncMorphDlg::~CFuncMorphDlg()
{
}

void CFuncMorphDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFuncMorphDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_DILATE, &CFuncMorphDlg::OnBnClickedBtnDilate)
END_MESSAGE_MAP()


// FuncMorphDlg 消息处理程序
int element_size = 3;

void CFuncMorphDlg::OnBnClickedBtnDilate()
{
	int s = element_size * 2 + 1;
	Mat structureElement = getStructuringElement(MORPH_RECT, Size(s, s), Point(-1, -1));
	//erode(prePro, pro, structureElement);
}
