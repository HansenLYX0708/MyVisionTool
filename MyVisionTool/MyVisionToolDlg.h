
// MyVisionToolDlg.h: 头文件
//

#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include "FuncMorphDlg.h"
#include "CFuncSmoothDlg.h"

using namespace cv;
using namespace std;

// CMyVisionToolDlg 对话框
class CMyVisionToolDlg : public CDialogEx
{
// 构造
public:
	CMyVisionToolDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYVISIONTOOL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	void Init();
	void ShowImage(int type);
	void CheckCloneFlag();
	void StateInfo(string info, int type);
	void CheckBlur();
public:
	Mat src, dst;
	Mat pro, prePro;
	enum DisplayType
	{
		SHOW_SRC,
		SHOW_PRO,
		SHOW_DST,
	};
	enum StateInfoType
	{
		STATE_INFO,
		STATE_ERROR,
		STATE_DEBUG,
	};
public:
	BOOL m_bIsContinPro;
	BOOL m_bIsDstSave;
	CStatic m_PicStatic;
	CString m_strStateInfo;
	int m_blurSize;
	double m_blurPram1;
	double m_blurPram2;
	CTabCtrl m_tabProcFunc;
	int m_curSelTab;
	CFuncMorphDlg m_tabFuncMorph;
	CFuncSmoothDlg m_tabFuncSmooth;
	CDialog* pDialog[2];

public:
	afx_msg void OnBnClickedBtnLoadSourceimage();
	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnBnClickedCheckConpro();
	afx_msg void OnBnClickedCheckDstSave();
	afx_msg void OnBnClickedBtnShowpro();
	afx_msg void OnBnClickedBtnShowdst();
	afx_msg void OnBnClickedBtnShowsrc();

	afx_msg void OnBnClickedBtnFilter2d();
	afx_msg void OnBnClickedBtnCvtcolor();
	afx_msg void OnBnClickedBtnBlur();
	afx_msg void OnBnClickedBtnGsblur();
	
	afx_msg void OnBnClickedBtnMedianblur();
	afx_msg void OnBnClickedBtnBilateralfilter();
	
	afx_msg void OnTcnSelchangeTabProcfunc(NMHDR *pNMHDR, LRESULT *pResult);
};
