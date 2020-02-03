
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
	DDX_Control(pDX, IDC_COMBO1, m_cb);
	DDX_Text(pDX, IDC_NAME, T_name);
	DDX_Text(pDX, IDC_TIME, T_time);
	DDX_Text(pDX, IDC_CAUSE, T_cause);
}

BEGIN_MESSAGE_MAP(CTimerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_DUQU, &CTimerDlg::OnBnClickedDuqu)
	ON_BN_CLICKED(IDC_GETLIST, &CTimerDlg::OnBnClickedGetlist)
	ON_BN_CLICKED(IDC_YUEBAO, &CTimerDlg::OnBnClickedYuebao)
	ON_BN_CLICKED(IDC_GETYB, &CTimerDlg::OnBnClickedGetyb)
	ON_BN_CLICKED(IDC_INPUT, &CTimerDlg::OnBnClickedInput)
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

	//读取人事清单
	PeopleListAddr = ".\\people.txt";  //目录下的人事清单文件
	GetPeopleList(PeopleListAddr);

	DepListAddr = ".\\dep.txt";//目录下的部门清单文件
	Getdepartment(DepListAddr);

	m_cb.SetCurSel(0);
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
		int nIndex = m_cb.GetCurSel();
		m_cb.GetLBText(nIndex, strCBText);
		bagaddr = ".\\" + strCBText + "考勤";
		CreateDirectory(bagaddr, 0);//不存在则创建

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

			
			CString csDirPath = bagaddr + "\\";
			//通过部门名称+原路径 变成部门文件夹
			csDirPath += ary_People[TickName];

			CreateDirectory(csDirPath, 0);//不存在则创建

			CopyFile(AllPathName, csDirPath + "\\" + fileName, FALSE);

			//某个部门文件下的txt文本
			CStringA ticklist = csDirPath + "\\" + ary_People[TickName] + ".txt";

			PaintText(ticklist, TickName, TickTime, TickCause, panduan);
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
	//	AfxMessageBox(("没有people文件，请检查目录下是否有该文件"));
		GetDlgItem(IDC_STA1)->SetWindowTextA("没有people文件，请检查目录下是否有该文件");
		//GetDlgItem(IDC_STA1)->
		
	}
}

//启动的时候读取部门名称
void CTimerDlg::Getdepartment(CString addr) {

	char ch[255]; // 定义字符数组用来接受读取一行的数据
	ifstream ifs(addr);
	if (ifs) // 有该文件
	{
		::memset(ch, 0, 255);

		while (!ifs.eof()) {//文件中只要还有内容
			ifs.getline(ch, 255);  // getline函数可以读取整行并保存在str数组里
			ary_DepName.Add(ch);
		}
		ifs.close();
	}
	else {//如果没有
		//AfxMessageBox(("没有找到部门文件，请检查目录下是否有该文件"));
		GetDlgItem(IDC_STA2)->SetWindowTextA("没有dep文件，请检查目录下是否有该文件");

	}
}

//打印函数
void  CTimerDlg::PaintText(CString in, CStringA Data1, CStringA Data2, CStringA Data3, CStringA is_first) {

	ofstream ofs(in, ios::app);

	if (Data1 != is_first) {
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


//生成人事清单，但是要按时更新
void CTimerDlg::OnBnClickedGetlist()
{
	ofstream ofs(PeopleListAddr, ios::app);
	if (ofs) {
		ofs.write("钟巧仪-中国电信\n", strlen("钟巧仪-中国电信\n"));
		ofs.write("凌大光-房管所\n", strlen("凌大光-房管所\n"));
		ofs.write("龚伍英-房管所\n", strlen("龚伍英-房管所\n"));
		ofs.write("钟美莲-房管所\n", strlen("钟美莲-房管所\n"));
		ofs.write("洪爱萍-房管所\n", strlen("洪爱萍-房管所\n"));
		ofs.write("夏志英-房管所\n", strlen("夏志英-房管所\n"));
		ofs.write("余德海-发改局\n", strlen("余德海-发改局\n"));
		ofs.write("郭文莉-供电局\n", strlen("郭文莉-供电局\n"));
		ofs.write("唐伍娣-供水管理处\n", strlen("唐伍娣-供水管理处\n"));
		ofs.write("黎海燕-交通运输局\n", strlen("黎海燕-交通运输局\n"));
		ofs.write("丘冬燕-交通运输局\n", strlen("丘冬燕-交通运输局\n"));
		ofs.write("张晓梦-交通运输局\n", strlen("张晓梦-交通运输局\n"));
		ofs.write("龚细年-农业农村局\n", strlen("龚细年-农业农村局\n"));
		ofs.write("潘晓东-农业农村局\n", strlen("潘晓东-农业农村局\n"));
		ofs.write("陈海媛-人力资源和社会保障局\n", strlen("陈海媛-人力资源和社会保障局\n"));
		ofs.write("何静-人力资源和社会保障局\n", strlen("何静-人力资源和社会保障局\n"));
		ofs.write("何春英-人力资源和社会保障局\n", strlen("何春英-人力资源和社会保障局\n"));
		ofs.write("莫美芸-市场监管局\n", strlen("莫美芸-市场监管局\n"));
		ofs.write("莫美芸-市场监管局\n", strlen("莫美芸-市场监管局\n"));
		ofs.write("刘丽榕-市场监管局\n", strlen("刘丽榕-市场监管局\n"));
		ofs.write("沈玉文-市场监管局\n", strlen("沈玉文-市场监管局\n"));
		ofs.write("谭盈-市场监管局\n", strlen("谭盈-市场监管局\n"));
		ofs.write("刘祝英-市场监管局\n", strlen("刘祝英-市场监管局\n"));
		ofs.write("赖秀娟-生态环境局\n", strlen("赖秀娟-生态环境局\n"));
		ofs.write("黄亿娣-水务局\n", strlen("黄亿娣-水务局\n"));
		ofs.write("林倚琪-水务局\n", strlen("林倚琪-水务局\n"));
		ofs.write("甘武胜-文广旅体局\n", strlen("甘武胜-文广旅体局\n"));
		ofs.write("钟洁敏-卫生监督局\n", strlen("钟洁敏-卫生监督局\n"));
		ofs.write("刘玉娟-综合窗口\n", strlen("刘玉娟-综合窗口\n"));
		ofs.write("黄萍-综合窗口\n", strlen("黄萍-综合窗口\n"));
		ofs.write("陈俐烨-综合窗口\n", strlen("陈俐烨-综合窗口\n"));
		ofs.write("温紫媚-综合窗口\n", strlen("温紫媚-综合窗口\n"));
		ofs.write("蒋健-综合窗口\n", strlen("蒋健-综合窗口\n"));
		ofs.write("谢年盛-综合窗口\n", strlen("谢年盛-综合窗口\n"));
		ofs.write("刘彦君-综合窗口\n", strlen("刘彦君-综合窗口\n"));
		ofs.write("何倩玲-综合窗口\n", strlen("何倩玲-综合窗口\n"));
		ofs.write("黄丽-综合窗口\n", strlen("黄丽-综合窗口\n"));
		ofs.write("莫玲雯-综合窗口\n", strlen("莫玲雯-综合窗口\n"));
		ofs.write("温心怡-综合窗口\n", strlen("温心怡-综合窗口\n"));
		ofs.write("邓伟云-综合窗口\n", strlen("邓伟云-综合窗口\n"));
		ofs.write("曾智鹏-综合窗口\n", strlen("曾智鹏-综合窗口\n"));
		ofs.write("李翠连-综合窗口\n", strlen("李翠连-综合窗口\n"));
		ofs.write("蒲颖-综合窗口\n", strlen("蒲颖-综合窗口\n"));
		ofs.write("欧倩倩-综合窗口\n", strlen("欧倩倩-综合窗口\n"));
		ofs.write("刘银霞-综合窗口\n", strlen("刘银霞-综合窗口\n"));
		ofs.write("黄玉珍-综合窗口\n", strlen("黄玉珍-综合窗口\n"));
		ofs.write("刘剑-综合窗口\n", strlen("刘剑-综合窗口\n"));
		ofs.write("罗仁英-住管局\n", strlen("罗仁英-住管局\n"));
		ofs.write("邱梅英-住管局\n", strlen("邱梅英-住管局\n"));
		ofs.write("易志彬-住管局\n", strlen("易志彬-住管局\n"));
		ofs.write("李冬顺-自然资源局\n", strlen("李冬顺-自然资源局\n"));
		ofs.write("刘秀红-自然资源局\n", strlen("刘秀红-自然资源局\n"));
		ofs.write("胡红英-自然资源局\n", strlen("胡红英-自然资源局\n"));
		ofs.write("张莹莹-自然资源局", strlen("张莹莹-自然资源局"));
		GetDlgItem(IDC_STA1)->SetWindowTextA("人事清单生成完毕，清单更新日期2020/01/18");

		ofs.close();
		//MessageBox("");

			
	}
	
}

//月报查询哪个单位没有交
void CTimerDlg::OnBnClickedYuebao()
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
		int nIndex = m_cb.GetCurSel();

		CString strCBText; //下拉框获取到的文本内容

		m_cb.GetLBText(nIndex, strCBText);
		CreateDirectory(".\\" + strCBText + "月报", 0);//不存在则创建

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
			CopyFile(AllPathName, ".\\" + strCBText + "月报" + "\\" + fileName, FALSE);
			
			//找到交了的单位名字，从列表中删除
			CStringA depname;
			AfxExtractSubString(depname, fileName, 0, '.'); //切割出名字
			
			for (int i = 0; i < ary_DepName.GetSize(); i++) {
				if (depname == ary_DepName.GetAt(i)) {
					ary_DepName.RemoveAt(i);
				}
			}
			

		}





		ofstream in(".\\" + strCBText + "月报" + "\\" + "没交的单位.txt", ios::app);

		//写下哪个单位没交
		for (int i = 0; i < ary_DepName.GetSize(); i++) {
			in.write(ary_DepName.GetAt(i) + "\t", strlen(ary_DepName.GetAt(i) + "\t"));
			
			CTime t = CTime::GetCurrentTime();
			int m = t.GetMonth(); //获取当前月份  
			int d = t.GetDay(); //获得几号  
			int h = t.GetHour(); //获取当前为几时   
			int mm = t.GetMinute(); //获取分钟  
			CStringA yue,ri,shi,fen;
			yue.Format(_T("%d"), m);
			ri.Format(_T("%d"), d);
			shi.Format(_T("%d"), h);
			fen.Format(_T("%d"), mm);


			
			in.write("\n"+yue+"月"+ri+"日"+shi+"时"+fen+"分", 
				strlen("\n" + yue + "月" + ri + "日" + shi + "时" + fen + "分"));

		}
		MessageBox("数据处理完毕");

	}
}

//生成部门清单，但是要按时更新
void CTimerDlg::OnBnClickedGetyb()
{
	ofstream ofs(DepListAddr, ios::app);
	if (ofs) {
		ofs.write("公安\n", strlen("公安\n"));
		ofs.write("市场监管\n", strlen("市场监管\n"));
		ofs.write("不动产登记中心\n", strlen("不动产登记中心\n"));
		ofs.write("房产交易中心\n", strlen("房产交易中心\n"));
		ofs.write("交通\n", strlen("交通\n"));
		ofs.write("社保\n", strlen("社保\n"));
		ofs.write("人社\n", strlen("人社\n"));
		ofs.write("自然资源\n", strlen("自然资源\n"));
		ofs.write("发改\n", strlen("发改\n"));
		ofs.write("住管\n", strlen("住管\n"));
		ofs.write("生态环境\n", strlen("生态环境\n"));
		ofs.write("供水\n", strlen("供水\n"));
		ofs.write("供电\n", strlen("供电\n"));
		ofs.write("燃气\n", strlen("燃气\n"));
		ofs.write("广播电视\n", strlen("广播电视\n"));
		ofs.write("税务\n", strlen("税务\n"));
		ofs.write("婚登\n", strlen("婚登\n"));
		ofs.write("电信\n", strlen("电信\n"));
		ofs.write("综窗\n", strlen("综窗\n"));
		GetDlgItem(IDC_STA2)->SetWindowTextA("清单生成完毕，清单更新日期2020/01/188");
		ofs.close();



	}
			
}


void CTimerDlg::OnBnClickedInput()
{
	
	//做记事本，先判断有没有生成该文件夹的考勤，如果没有 就新建
	UpdateData();
	int nIndex = m_cb.GetCurSel();
	m_cb.GetLBText(nIndex, strCBText);
	bagaddr = ".\\" + strCBText + "考勤";
	CreateDirectory(bagaddr, 0);//这里是创建几月份考勤包
	
	bagaddr+= "\\";
	bagaddr += ary_People[T_name];
	CreateDirectory(bagaddr, 0);//这里是创建部门的文件夹了

	bagaddr += "\\" + ary_People[T_name] + ".txt";

	PaintText(bagaddr, T_name, T_time, T_cause, panduan);
	panduan = T_name;

	GetDlgItem(IDC_STA2)->SetWindowTextA(T_name+"离岗数据生成完毕");
}
