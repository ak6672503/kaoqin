
// TimerDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Timer.h"
#include "TimerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <string>
#include <fstream>
#include<tchar.h>
#include"resource.h"
#include<vector>
#include "start.h"
using namespace std;

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


// CTimerDlg 对话框



CTimerDlg::CTimerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TIMER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTimerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTimerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_DUQU, &CTimerDlg::OnBnClickedDuqu)
END_MESSAGE_MAP()


// CTimerDlg 消息处理程序

BOOL CTimerDlg::OnInitDialog()
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

	CStringA addr = ".\\people.txt";
	GetPeopleList(addr);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTimerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTimerDlg::OnPaint()
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
HCURSOR CTimerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTimerDlg::OnBnClickedDuqu()
{
	
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_ALLOWMULTISELECT);
		
	//最多可以打开500个文件
	fileDlg.m_ofn.nMaxFile = 500 * MAX_PATH;

	 char* ch = new CHAR[fileDlg.m_ofn.nMaxFile];
	fileDlg.m_ofn.lpstrFile = ch;

	//对内存块清零
	::ZeroMemory(fileDlg.m_ofn.lpstrFile, sizeof(TCHAR) * fileDlg.m_ofn.nMaxFile);

	//显示文件对话框，获得文件名集合
	if (fileDlg.DoModal() == IDOK) {
		TCHAR ch1[10];
		CStringA bb;
		GetDlgItem(IDC_EDIT1)->GetWindowTextA(ch1, 10);
		bb = ch1;
		CreateDirectory(".\\"+bb, 0);//不存在则创建

		//获取第一个文件的位置
		POSITION pos_file;
		pos_file = fileDlg.GetStartPosition();

		//循环读出每个路径并存放在数组中
		while (pos_file != NULL) {

			//将文件路径存放在数组中
			AllPathName = fileDlg.GetNextPathName(pos_file);
			ary_filePath.Add(AllPathName);

			//获取文件名
			//从字符串的后面往前遍历，如果遇到'\'则结束遍历，'\'右边的字符串则为文件名
			int length = AllPathName.GetLength();
			for (int i = length - 1; i > 0; i--)
			{
				if ('\\' == (AllPathName.GetAt(i)))
				{//判断当前字符是否是'\'
					fileName = AllPathName.Right(length - i - 1);
						break;//跳出循环
				}
			}

			//获取文件名(不包含后缀)
			//采用CString的Left(int count)截取CString中从左往右数的count个字符
			//fileName.GetLength()-4中的4表示".dat"四个字符
			fileTitle = fileName.Left(fileName.GetLength() - 4);
			ary_fileName.Add(fileTitle);//将文件名(不包含后缀)添加到数组中
		
		
				
				AfxExtractSubString(TickName, fileTitle, 0, '-'); //切割出名字
				AfxExtractSubString(TickTime, fileTitle, 1, '-');//切割出离岗时间
				AfxExtractSubString(TickCause, fileTitle, 2, '-');//切割出离岗事由

				CString csDirPath = ".\\" + bb+".\\";
				//通过部门名称+原路径 变成部门文件夹
				csDirPath += ary_People[TickName];
				
				CreateDirectory(csDirPath, 0);//不存在则创建

				CopyFile(AllPathName, csDirPath + "\\" + fileName, FALSE);


					
					CStringA shiyixia = csDirPath + "\\" + ary_People[TickName]+".txt";
					
					 PaintText(shiyixia,TickName, TickTime, TickCause, panduan);
					 panduan = TickName;
		}
	}
	delete[] ch;
}



//寻找目录下是否有某个文件
void CTimerDlg::SearchFiles(CString strMusicFolder)
{
	CFileFind ff;

	strMusicFolder += _T("\\");

	strMusicFolder += _T("*.*");

	BOOL res = ff.FindFile(strMusicFolder);

	while (res)
	{
		res = ff.FindNextFile();
		if (!ff.IsDirectory() && !ff.IsDots())
		{
			MessageBox(ff.GetFilePath());
		}
	}
	ff.Close();
}

//程序启动的时候默认读取人事清单函数
void CTimerDlg::GetPeopleList(CString addr)
{
	char ch[255]; // 定义字符数组用来接受读取一行的数据
	ifstream ifs(addr);
	if (ifs) // 有该文件
	{
		::memset(ch, 0, 255);

		while (!ifs.eof()) {//文件中只要还有内容
			ifs.getline(ch, 255);  // getline函数可以读取整行并保存在str数组里
			CStringA Data = ch;
			AfxExtractSubString(Pname, Data, 0, '-'); //切割出名字
			AfxExtractSubString(Department, Data, 1, '-');//切割出部门
			ary_People[Pname] = Department;	  //把部门和人名关联起来
		}
		ifs.close();
	}
	else {//如果没有，就强行结束本程序
		AfxMessageBox(("没有people文件，请检查目录下是否有该文件"));
		HANDLE hself = GetCurrentProcess();
		TerminateProcess(hself, 0);
	}
}



void  CTimerDlg::PaintText(CString in,CStringA Data1, CStringA Data2, CStringA Data3,CStringA is_first) {
	
	ofstream ofs(in, ios::app);

	if (Data1 != is_first){
	ofs.write("\n", strlen("\n"));
	ofs.write(Data1, Data1.GetLength());
	ofs.write("\t", strlen("\t"));
	ofs.write(Data2, Data2.GetLength());
	ofs.write("\t", strlen("\t"));
	ofs.write(Data3, Data3.GetLength());
	ofs.write("\n", strlen("\n"));
	}
	else {
		
		ofs.write("\t", strlen("\t"));
		ofs.write(Data2, Data2.GetLength());
		ofs.write("\t", strlen("\t"));
		ofs.write(Data3, Data3.GetLength());
		ofs.write("\n", strlen("\n"));
		
	}
	ofs.close();

}


