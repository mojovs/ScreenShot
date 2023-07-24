// MScreenShotDlg.cpp: 实现文件
//

#include "pch.h"
#include "ScreenShot.h"
#include "MScreenShotDlg.h"
#include "afxdialogex.h"
#include  "afxwin.h"


// MScreenShotDlg 对话框

IMPLEMENT_DYNAMIC(MScreenShotDlg, CDialogEx)

MScreenShotDlg::MScreenShotDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(DLG_SCREENSHOT, pParent)
{
	cur_shape = new ShapeRect; //创建一个矩形
}

MScreenShotDlg::~MScreenShotDlg()
{
}

void MScreenShotDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MScreenShotDlg, CDialogEx)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//	ON_WM_PAINT()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// MScreenShotDlg 消息处理程序


BOOL MScreenShotDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//设置窗口透明度
	if (!::SetLayeredWindowAttributes(GetSafeHwnd(),RGB(125, 125, 125), 200,LWA_ALPHA))
	{
		AfxMessageBox("SetLayeredWindowAttributesSetLay	failed!");
		return false;
	}
	//保存屏幕截图
	HDC hdc = ::GetDC(NULL);
	//获取屏幕的长宽
	int screen_x = GetSystemMetrics(SM_CXSCREEN);
	int screen_y = GetSystemMetrics(SM_CYSCREEN);
	//创建image
	m_screenImage = std::make_shared<CImage>();

	m_screenImage->Create(screen_x, screen_y, ::GetDeviceCaps(hdc,BITSPIXEL));
	//进行拷贝
	HDC image_dc = m_screenImage->GetDC();
	::BitBlt(image_dc, 0, 0, screen_x, screen_y, hdc, 0, 0,SRCCOPY);
	m_screenImage->Save("screen.png");
	m_screenImage->ReleaseDC();

	return TRUE; // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void MScreenShotDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_startPoint = point; //按下的初始化值

	CDialogEx::OnLButtonDown(nFlags, point);
}


void MScreenShotDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值


	m_rectImage->Save("2.png");
		m_rectImage.reset();
		m_rectImage = nullptr;
	CloseWindow();
	DestroyWindow();
	CDialogEx::OnLButtonUp(nFlags, point);
}


void MScreenShotDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nFlags == VK_LBUTTON) //如果左键按下
	{
		//添加绘制图形
		cur_shape->SetPoints(m_startPoint, point);

		CPen pen;
		pen.CreatePen(PS_SOLID, 4,RGB(255, 0, 0));
		//获取dc
		CDC* cdc = GetDC();
		cdc->SelectObject(&pen);
		cdc->SelectStockObject(NULL_BRUSH);

		//将矩形加入到队列
		shape_list.AddTail(cur_shape);

		//拷贝screenImage的部分区域 到屏幕和新的IMage里方便保存

		CRect rect(m_startPoint, point);
		HDC screen_hdc = m_screenImage->GetDC();

		//拉框选取的CImage
		m_rectImage = std::make_shared<CImage>();
		is_imageCreated = m_rectImage->Create(rect.Width(), rect.Height(), m_screenImage->GetBPP());
		if (is_imageCreated == true)
		{
			HDC rect_hdc = m_rectImage->GetDC();
			BitBlt(rect_hdc, 0, 0, rect.Width(), rect.Height(), screen_hdc, m_startPoint.x, m_startPoint.y,SRCCOPY);
			m_rectImage->ReleaseDC();
		}
		//根据拉框选择大小
		m_screenImage->ReleaseDC();


		//开始更新界面
		//开始刷新界面，闪屏变少
		InvalidateRect(NULL, 0);
		UpdateWindow(); //绘制边框
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


void MScreenShotDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	//创建设备兼容内存
	CDC mem_cdc;
	mem_cdc.CreateCompatibleDC(&dc);
	//获取dialog的位图
	CRect rect;
	//GetWindowRect(&rect);
	GetClientRect(&rect);
	//创建位图兼容内存
	CBitmap mem_bitmap;
	mem_bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	//将位图兼容内存选入设备兼容内存
	mem_cdc.SelectObject(&mem_bitmap);
	//给内存选择画壁画刷 
	CPen n_pen;
	n_pen.CreatePen(PS_SOLID, 6,RGB(255, 0, 0));
	mem_cdc.SelectObject(&n_pen);
	//CBrush  n_brush;
	//n_brush.CreateHatchBrush(HS_CROSS,RGB(0,255,0));
	//mem_cdc.SelectObject(&n_brush);
	mem_cdc.SelectStockObject(NULL_BRUSH);
	//内存中清屏
	mem_cdc.FillSolidRect(&rect,RGB(255, 255, 255));
	/**开始绘画**/
	//	auto a=shape_list.GetHeadPosition();
	//	while(a)
	//	{
	//		Shape *n_shape = shape_list.GetNext(a);
	//		n_shape->OnDraw(&dc);
	//		
	//	}
	if (cur_shape != nullptr && is_imageCreated != false)
	{
		//CString str;
		//str.Format("[Width]:%d,[Height]:%d\n", m_rectImage->GetWidth(), m_rectImage->GetHeight());
		//OutputDebugString(str);
		m_rectImage->Draw(mem_cdc, cur_shape->get_m_start_pnt());
		cur_shape->OnDraw(&mem_cdc);
	}

	//将兼容内存中的内容拷贝到设备上
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &mem_cdc, 0, 0,SRCCOPY);
}
