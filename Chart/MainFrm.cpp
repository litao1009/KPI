
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "Chart.h"

#include "MainFrm.h"

#include "Frame/OgreEnv.h"
#include "Frame/OgreWndWrapper.h"
#include "Controller/ChartController.h"
//#include "FrameEvent/IndicatorEvt.h"

//#ifdef _DEBUG
//#define new DEBUG_NEW
//#endif

// CMainFrame

class	CMainFrame::Imp
{
public:

	OgreWndWrapperUPtr	OgreWnd_;
};

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CMainFrame 构造/析构

CMainFrame::CMainFrame():ImpUPtr_( std::make_unique<Imp>() )
{
	// TODO:  在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	auto height = 500;
	cs.cx = height * 3 + 20;
	cs.cy = height + 62;
	cs.style &= ~WS_MAXIMIZEBOX;
	cs.style &= ~WS_THICKFRAME;

	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序



int CMainFrame::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
	if ( CFrameWnd::OnCreate( lpCreateStruct ) == -1 )
		return -1;

	auto cf = GetActiveView();


	auto curHwnd = reinterpret_cast<int>( cf->GetSafeHwnd() );
	RECT rect;
	cf->GetClientRect( &rect );
	ImpUPtr_->OgreWnd_ = OgreEnv::GetInstance().CreateRenderWindow( curHwnd, rect.right - rect.left, rect.bottom - rect.top );

	auto ctrller = std::make_shared<ChartController>( ImpUPtr_->OgreWnd_->GetRenderWindow() );
	OgreEnv::GetInstance().AddController( ctrller );

	return 0;
}
