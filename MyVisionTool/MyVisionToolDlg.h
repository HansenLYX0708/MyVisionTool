
// MyVisionToolDlg.h: 头文件
//

#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>
#include "highgui.hpp"
#include "xfeatures2d.hpp"
#include <string>
#include "ShapeFindDlg.h"
#include "SubpixelDlg.h"
#include "opencv2/imgproc.hpp"

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
	void CheckFlag();
	void StateInfo(string info, int type);
	void CheckWindowValue();

	void Stretch(Mat src, Mat dst, int min, int max);
	void MiddleSmooth(Mat src, Mat dst);
public:
	Mat src, dst;
	Mat pro, prePro;
	enum DisplayType
	{
		SHOW_SRC,
		SHOW_PREPRO,
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
	int m_size;
	double m_blurPram1;
	double m_blurPram2;
	CTabCtrl m_tabProcFunc;
	int m_curSelTab;
	ShapeFindDlg m_shapeFindDlg;
	SubpixelDlg m_subpixelDlg;
	CDialog* pDialog[2];
	CTabCtrl m_tab;
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
	
	afx_msg void OnBnClickedBtnThreshold();

	afx_msg void OnBnClickedBtnmorphologyEx();

	afx_msg void OnBnClickedBtnBitwise();
	afx_msg void OnBnClickedResize();
	afx_msg void OnBnClickedBtnSobel();
	afx_msg void OnBnClickedBtnLaplacian();
	afx_msg void OnBnClickedBtnShowprepro();
	afx_msg void OnBnClickedBtnCanny();
	afx_msg void OnBnClickedBtnHoughlines();
	afx_msg void OnBnClickedBtnHoughcircle();
	afx_msg void OnBnClickedBtnPlateextract();
	afx_msg void OnBnClickedPicturetransfertovideo();
	afx_msg void Image_To_Video(int p_num, string inputPath, string inputFormat, string outputPath, int fps, int width, int height, int isColor);
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonUndoall();
	afx_msg void OnBnClickedBtnSurf();
	afx_msg void OnBnClickedBtnHist();
	afx_msg void OnBnClickedBtnEqualizehist();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void ReleaseData();
	afx_msg void OnBnClickedBtnFindcontours();
	afx_msg void OnBnClickedBtnMinrect();
	afx_msg void OnBnClickedBtnThresholdAdapt();
	afx_msg void OnBnClickedBtnCorners();
	afx_msg void OnBnClickedBtnHull();
	
};
