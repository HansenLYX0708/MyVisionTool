#pragma once


// CFuncSmoothDlg 对话框

class CFuncSmoothDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFuncSmoothDlg)

public:
	CFuncSmoothDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CFuncSmoothDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SMOOTHBLUR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
