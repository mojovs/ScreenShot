#pragma once
#include "Shape.h"
#include <utility>
#include <memory>


// MScreenShotDlg 对话框

class MScreenShotDlg : public CDialogEx
{
	DECLARE_DYNAMIC(MScreenShotDlg)
private:
	CList<Shape*> shape_list;
	Shape *cur_shape=nullptr;
	std::shared_ptr<CImage> m_screenImage=nullptr; //整个屏幕的截图
	std::shared_ptr<CImage> m_rectImage=nullptr;	//拉框选择的截图
	bool is_imageCreated=false;
public:
	MScreenShotDlg(CWnd* pParent = nullptr);   // 标准构造函数
		CPoint m_startPoint;	//鼠标按下的坐标
	virtual ~MScreenShotDlg();


// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = DLG_SCREENSHOT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
//	afx_msg void OnPaint();
	afx_msg void OnPaint();
};
