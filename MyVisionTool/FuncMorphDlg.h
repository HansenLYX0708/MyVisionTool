#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>


using namespace cv;
using namespace std;

// FuncMorphDlg 对话框

class CFuncMorphDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFuncMorphDlg)

public:
	CFuncMorphDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CFuncMorphDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MORPHOLOGY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnDilate();
};
