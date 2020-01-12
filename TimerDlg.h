
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
	//用CString数组存放人名和对应的单位名称
	map<CString,CString> ary_People ;
	void GetFileFromDirectory(CString csDirPath, vector<CString>& vctPath);
	CStringA Pname, department;
};
