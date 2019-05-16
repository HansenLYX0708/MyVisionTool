// ShapeFindDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyVisionTool.h"
#include "ShapeFindDlg.h"
#include "afxdialogex.h"


// ShapeFindDlg dialog

IMPLEMENT_DYNAMIC(ShapeFindDlg, CDialogEx)

ShapeFindDlg::ShapeFindDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SHAPE, pParent)
{

}

ShapeFindDlg::~ShapeFindDlg()
{
}

void ShapeFindDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ShapeFindDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_FINDCIRCLE, &ShapeFindDlg::OnBnClickedButtonFindcircle)
END_MESSAGE_MAP()


// ShapeFindDlg message handlers


void ShapeFindDlg::OnBnClickedButtonFindcircle()
{
	// TODO: Add your control notification handler code here

}
