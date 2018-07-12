
// ToolConfigDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "ToolConfig.h"
#include "ToolConfigDlg.h"
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


// CToolConfigDlg 对话框



CToolConfigDlg::CToolConfigDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TOOLCONFIG_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CToolConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_userlist);
	DDX_Text(pDX, IDC_EDIT1, m_listenroom);
}

BEGIN_MESSAGE_MAP(CToolConfigDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COMBO1, &CToolConfigDlg::OnUserSelchange)
	ON_BN_CLICKED(IDC_BUTTON1, &CToolConfigDlg::OnImportConfig)
	ON_BN_CLICKED(IDC_BUTTON2, &CToolConfigDlg::OnUpdateConfig)
	ON_EN_CHANGE(IDC_EDIT1, &CToolConfigDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CToolConfigDlg 消息处理程序

BOOL CToolConfigDlg::OnInitDialog()
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
	GetCurrentDirectoryA(sizeof(_cfgfile), _cfgfile);
	strcat_s(_cfgfile, DEF_CONFIGGILE_NAME);
	this->_ReadConfSummary();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CToolConfigDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CToolConfigDlg::OnPaint()
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
HCURSOR CToolConfigDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CToolConfigDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
}


void CToolConfigDlg::OnUserSelchange()
{
	// TODO: 在此添加控件通知处理程序代码
	int index = m_userlist.GetCurSel();
	this->_ReadConfUser(index);
}


void CToolConfigDlg::OnImportConfig()
{
	// TODO: 在此添加控件通知处理程序代码
	this->_ReadConfSummary();
}


void CToolConfigDlg::OnUpdateConfig()
{
	// TODO: 在此添加控件通知处理程序代码
	int index = m_userlist.GetCurSel();
	this->_WriteConfSummary();
	if (index) {
		this->_WriteConfUser(index);
		MessageBoxW(_T("修改成功"), _T("信息"));
	}
	else {
		MessageBoxW(_T("请先选择用户"), _T("信息"));
	}
}


int CToolConfigDlg::_ReadConfSummary()
{
	m_listenroom = ::GetPrivateProfileIntA("Global", "Room", 0, _cfgfile);
	int usernum = ::GetPrivateProfileIntA("Global", "Accountnum", 0, _cfgfile);
	this->SetDlgItemInt(IDC_TEXTSTATIC01, usernum, false);
	m_userlist.ResetContent();
	m_userlist.InsertString(0, _T(""));
	char usersn[30], username[30];
	for (int i = 1; i <= usernum; i++) {
		sprintf_s(usersn, "User%d", i);
		::GetPrivateProfileStringA(usersn, "Username", "", username, 30, _cfgfile);
		m_userlist.InsertString(i, CString(username));
	}
	m_userlist.SetCurSel(0);
	UpdateData(false);
	this->_ReadConfUser(0);

	return 0;
}

int CToolConfigDlg::_WriteConfSummary()
{
	if (m_listenroom) {
		char roomid[30];
		sprintf_s(roomid, "%d", m_listenroom);
		::WritePrivateProfileStringA("Global", "Room", roomid, _cfgfile);
	}

	return 0;
}

int CToolConfigDlg::_ReadConfUser(int index)
{
	char usersn[30];
	sprintf_s(usersn, "User%d", index);
	int userid, userconf;
	userid = ::GetPrivateProfileIntA(usersn, "UserID", 0, _cfgfile);
	userconf = ::GetPrivateProfileIntA(usersn, "Conf", 0, _cfgfile);
	this->SetDlgItemInt(IDC_TEXTSTATIC02, userid, false);
	// 设置各复选框 这里必须保证复选框ID连续并有序
	for (int i = 0; i < 7; i++) {
		((CButton*)GetDlgItem(IDC_CHECK1 + i))->SetCheck(userconf & (1 << i));
	}
	UpdateData(false);

	return 0;
}

int CToolConfigDlg::_WriteConfUser(int index)
{
	int conf = 0;
	// 读取各复选框 这里必须保证复选框ID连续并有序
	for (int i = 0; i < 7; i++) {
		conf |= ((CButton*)GetDlgItem(IDC_CHECK1 + i))->GetCheck() << i;
	}
	char usersn[30], strconf[30];
	sprintf_s(usersn, "User%d", index);
	sprintf_s(strconf, "%d", conf);
	::WritePrivateProfileStringA(usersn, "Conf", strconf, _cfgfile);

	return 0;
}
