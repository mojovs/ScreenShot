﻿// ScreenShotDlg.h: 头文件
//

#pragma once

#include "MScreenShotDlg.h"
#include <memory>

// CScreenShotDlg 对话框
class CScreenShotDlg : public CDialogEx
{
	// 构造
public:
	CScreenShotDlg(CWnd* pParent = nullptr); // 标准构造函数
	std::shared_ptr<MScreenShotDlg> m_dlg; //拉框截图的窗口


	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SCREENSHOT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV 支持


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
	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);
};
