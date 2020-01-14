
// TimerDlg.h: 头文件
//
#include <map>
#include<vector>
using namespace std;
#pragma once


// CTimerDlg 对话框
class CTimerDlg : public CDialogEx
{
// 构造
public:
	CTimerDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TIMER_DIALOG };
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
public:
	afx_msg void OnBnClickedDuqu();
	afx_msg void OnBnClickedPeizhi();

	void SearchFiles(CString strMusicFolder);

public:
	
	void GetPeopleList(CString addr); //获取人事清单函数申明

	void PaintText(CString in, CStringA Data1, CStringA Data2, CStringA Data3,CStringA is_first);


	CArray<CString, CString> ary_filePath;//存放所有的文件路径，用于遍历
	
	CArray<CString, CString> ary_fileName;//存放所有文件的名称不含后缀，用于遍历

	CString AllPathName;//临时存放文件的全路径
	CString fileName;//临时存放文件的全称
	CString fileTitle; //临时存放文件的标题(不含后缀)

	CStringA Tick; //假单全称
	CStringA TickName;//假单名字
	CStringA TickTime; //离岗时间
	CStringA TickCause; //离岗事由

	CStringA panduan = ""; //判断如果有内容，就证明是同一个人的，如果不是就是新人


	//void GetFileFromDirectory(CString csDirPath, vector<CString>& vctPath);
	//寻找文件函数的申明
	 map<CString, CString> ary_People;//用存放人名和对应的单位名称
	 CStringA Pname, Department;//人名、对应的部门
	


	 CComboBox m_cb;
};
