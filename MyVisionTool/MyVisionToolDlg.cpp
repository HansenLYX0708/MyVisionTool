
// MyVisionToolDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MyVisionTool.h"
#include "MyVisionToolDlg.h"
#include "afxdialogex.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMyVisionToolDlg 对话框



CMyVisionToolDlg::CMyVisionToolDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MYVISIONTOOL_DIALOG, pParent)
	, m_bIsContinPro(FALSE)
	, m_bIsDstSave(FALSE)
	, m_strStateInfo(_T(""))
	, m_blurSize(0)
	, m_blurPram1(0)
	, m_blurPram2(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyVisionToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PIC_STATIC, m_PicStatic);
	DDX_Check(pDX, IDC_CHECK_CONPRO, m_bIsContinPro);
	DDX_Check(pDX, IDC_CHECK_DST_SAVE, m_bIsDstSave);
	DDX_Text(pDX, IDC_EDIT_STATEINFO, m_strStateInfo);
	DDV_MaxChars(pDX, m_strStateInfo, 200);
	DDX_Text(pDX, IDC_EDIT_SIZE, m_blurSize);
	DDV_MinMaxInt(pDX, m_blurSize, 1, 51);
	DDX_Text(pDX, IDC_EDIT_PRAM1, m_blurPram1);
	DDX_Text(pDX, IDC_EDIT_PRAM2, m_blurPram2);
	DDX_Control(pDX, IDC_TAB_PROCFUNC, m_tabProcFunc);
}

BEGIN_MESSAGE_MAP(CMyVisionToolDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_LOADIMAGE, &CMyVisionToolDlg::OnBnClickedBtnLoadSourceimage)
	ON_BN_CLICKED(IDC_BTN_SHOWSRC, &CMyVisionToolDlg::OnBnClickedBtnShowsrc)
	ON_BN_CLICKED(IDC_BTN_SHOWPRO, &CMyVisionToolDlg::OnBnClickedBtnShowpro)
	ON_BN_CLICKED(IDC_BTN_SHOWDST, &CMyVisionToolDlg::OnBnClickedBtnShowdst)
	ON_BN_CLICKED(IDC_BTN_FILTER2D, &CMyVisionToolDlg::OnBnClickedBtnFilter2d)
	ON_BN_CLICKED(IDC_CHECK_CONPRO, &CMyVisionToolDlg::OnBnClickedCheckConpro)
	ON_BN_CLICKED(IDC_CHECK_DST_SAVE, &CMyVisionToolDlg::OnBnClickedCheckDstSave)
	ON_BN_CLICKED(IDC_BTN_CVTCOLOR, &CMyVisionToolDlg::OnBnClickedBtnCvtcolor)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CMyVisionToolDlg::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_BLUR, &CMyVisionToolDlg::OnBnClickedBtnBlur)
	ON_BN_CLICKED(IDC_BTN_GSBLUR, &CMyVisionToolDlg::OnBnClickedBtnGsblur)
	ON_BN_CLICKED(IDC_BTN_MEDIANBLUR, &CMyVisionToolDlg::OnBnClickedBtnMedianblur)
	ON_BN_CLICKED(IDC_BTN_BILATERALFILTER, &CMyVisionToolDlg::OnBnClickedBtnBilateralfilter)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_PROCFUNC, &CMyVisionToolDlg::OnTcnSelchangeTabProcfunc)
END_MESSAGE_MAP()


// CMyVisionToolDlg 消息处理程序

BOOL CMyVisionToolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	namedWindow("view", WINDOW_AUTOSIZE);
	HWND hWnd = (HWND)cvGetWindowHandle("view");
	HWND hParent = ::GetParent(hWnd);
	::SetParent(hWnd, GetDlgItem(IDC_PIC_STATIC)->m_hWnd);
	::ShowWindow(hParent, SW_HIDE);
	
	m_tabProcFunc.InsertItem(0, "Smooth");
	m_tabProcFunc.InsertItem(1, "Morphology");
	m_tabFuncSmooth.Create(IDD_DIALOG_SMOOTHBLUR, &m_tabProcFunc);
	m_tabFuncMorph.Create(IDD_DIALOG_MORPHOLOGY, &m_tabProcFunc);
	//设定在Tab内显示的范围
	CRect rc;
	m_tabProcFunc.GetClientRect(rc);
	rc.top += 20;
	rc.bottom -= 0;
	rc.left += 0;
	rc.right -= 0;
	m_tabFuncSmooth.MoveWindow(&rc);
	m_tabFuncMorph.MoveWindow(&rc);

	//把对话框对象指针保存起来
	pDialog[0] = &m_tabFuncSmooth;
	pDialog[1] = &m_tabFuncMorph;
	//显示初始页面
	pDialog[0]->ShowWindow(SW_SHOW);
	pDialog[1]->ShowWindow(SW_HIDE);
	//保存当前选择
	m_curSelTab = 0;

	Init();

	UpdateData(false);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMyVisionToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMyVisionToolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMyVisionToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

#pragma region Process
void CMyVisionToolDlg::Init()
{
	m_bIsContinPro = true;
	m_bIsDstSave = true;

	// blur 
	m_blurSize = 5;
	m_blurPram1 = 5.0;
	m_blurPram2 = 5.0;
}

void CMyVisionToolDlg::ShowImage(int type)
{
	Mat image;
	string strInfo = "";
	if (type == SHOW_SRC)
	{
		image = src;
		strInfo = "src";
	}
	else if (type == SHOW_PRO)
	{
		image = pro;
		strInfo = "pro";
	}
	else if (type == SHOW_DST)
	{
		image = dst;
		strInfo = "dst";
	}
	else
	{
		return;
	}
	if (!image.data)
	{
		string info = "could not load " + strInfo + " image...\n";
		StateInfo(info, STATE_ERROR);
		return;
	}

	//以下操作获取图形控件尺寸并以此改变图片尺寸，按比例缩放
	CRect rect;
	GetDlgItem(IDC_PIC_STATIC)->GetClientRect(&rect);
	Rect dst(rect.left, rect.top, rect.right, rect.bottom);
	double fx = (double)rect.Width() / image.cols;
	double fy = (double)rect.Height() / image.rows;
	if (fx > fy)
	{
		fx = fy;
	}
	Mat imagedst;
	resize(image, imagedst, Size(0, 0), fx, fx);
	// 清除图片后再显示
	CStatic* pStatic = (CStatic*)GetDlgItem(IDC_PIC_STATIC);
	pStatic->SetBitmap(NULL);
	imshow("view", imagedst);
}

void CMyVisionToolDlg::CheckCloneFlag()
{
	if (m_bIsContinPro)
	{
		prePro = pro.clone();
	}
	if (m_bIsDstSave)
	{
		dst = pro.clone();
	}
}

void CMyVisionToolDlg::StateInfo(string info, int type)
{
	if (info.empty())
	{
		return;
	}
	// string to CString
	m_strStateInfo.Format("%s", info.c_str());
	UpdateData(FALSE);
}
void CMyVisionToolDlg::CheckBlur()
{
	UpdateData(TRUE);
}
#pragma endregion

void CMyVisionToolDlg::OnBnClickedBtnLoadSourceimage()
{
	CString picPath;
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_ALLOWMULTISELECT, NULL, this);
	if (dlg.DoModal() == IDOK)
	{
		picPath = dlg.GetPathName();
	}
	// CString to string
	string imageSrcPath1 = picPath.GetBuffer(0);
	src = imread(imageSrcPath1);
	prePro = src.clone();
	ShowImage(SHOW_SRC);
}

void CMyVisionToolDlg::OnBnClickedBtnSave()
{
	if (!dst.data)
	{
		string info = "Error: The dst picture cannot be empty\n";
		StateInfo(info, STATE_ERROR);
		return;
	}
	imwrite("dst.png", dst);
}

void CMyVisionToolDlg::OnBnClickedBtnShowsrc()
{
	ShowImage(SHOW_SRC);
}

void CMyVisionToolDlg::OnBnClickedBtnShowpro()
{
	ShowImage(SHOW_PRO);
}

void CMyVisionToolDlg::OnBnClickedBtnShowdst()
{
	ShowImage(SHOW_DST);
}

void CMyVisionToolDlg::OnBnClickedCheckConpro()
{
	UpdateData(TRUE);
}

void CMyVisionToolDlg::OnBnClickedCheckDstSave()
{
	UpdateData(TRUE);
}

void CMyVisionToolDlg::OnBnClickedBtnFilter2d()
{
	if (!prePro.data)
	{
		string info = "Error: The picture cannot be empty";
		StateInfo(info, STATE_ERROR);
		return;
	}
	Mat kernel = (Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	filter2D(prePro, pro, prePro.depth(), kernel);
	CheckCloneFlag();
	ShowImage(SHOW_PRO);
	StateInfo("Success", STATE_INFO);
}

void CMyVisionToolDlg::OnBnClickedBtnCvtcolor()
{
	if (!prePro.data)
	{
		string info = "Error::The picture cannot be empty";
		StateInfo(info, STATE_ERROR);
		return;
	}
	else if (prePro.channels() <= 1)
	{
		string info = "Error::The picture channels cannot be less than 1";
		StateInfo(info, STATE_ERROR);
		return;
	}
	cvtColor(prePro, pro, CV_BGR2GRAY);
	CheckCloneFlag();
	ShowImage(SHOW_PRO);
	StateInfo("Success", STATE_INFO);
}

void CMyVisionToolDlg::OnBnClickedBtnBlur()
{
	CheckBlur();
	if (!prePro.data)
	{
		string info = "Error::The picture cannot be empty";
		StateInfo(info, STATE_ERROR);
		return;
	}
	blur(prePro, pro, Size(m_blurSize, m_blurSize), Point(-1, -1));
	CheckCloneFlag();
	ShowImage(SHOW_PRO);
	StateInfo("Success", STATE_INFO);
}

void CMyVisionToolDlg::OnBnClickedBtnGsblur()
{
	CheckBlur();
	if (!prePro.data)
	{
		string info = "Error::The picture cannot be empty";
		StateInfo(info, STATE_ERROR);
		return;
	}
	GaussianBlur(prePro, pro, Size(m_blurSize, m_blurSize), m_blurPram1, m_blurPram2);
	CheckCloneFlag();
	ShowImage(SHOW_PRO);
	StateInfo("Success", STATE_INFO);
}


void CMyVisionToolDlg::OnBnClickedBtnMedianblur()
{
	CheckBlur();
	if (!prePro.data)
	{
		string info = "Error::The picture cannot be empty";
		StateInfo(info, STATE_ERROR);
		return;
	}
	medianBlur(prePro, pro, m_blurSize);
	CheckCloneFlag();
	ShowImage(SHOW_PRO);
	StateInfo("Success", STATE_INFO);
}


void CMyVisionToolDlg::OnBnClickedBtnBilateralfilter()
{
	CheckBlur();
	if (!prePro.data)
	{
		string info = "Error::The picture cannot be empty";
		StateInfo(info, STATE_ERROR);
		return;
	}
	bilateralFilter(prePro, pro, 15, 100, 5);
	CheckCloneFlag();
	ShowImage(SHOW_PRO);
	StateInfo("Success", STATE_INFO);
}

void CMyVisionToolDlg::OnTcnSelchangeTabProcfunc(NMHDR *pNMHDR, LRESULT *pResult)
{
	pDialog[m_curSelTab]->ShowWindow(SW_HIDE);
	m_curSelTab = m_tabProcFunc.GetCurSel();
	pDialog[m_curSelTab]->ShowWindow(SW_SHOW);
	*pResult = 0;
}