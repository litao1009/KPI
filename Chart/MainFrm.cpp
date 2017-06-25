
// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "Chart.h"

#include "MainFrm.h"

#include "Frame/OgreEnv.h"
#include "Frame/OgreWndWrapper.h"
#include "Controller/ChartController.h"

#include "DlgEditData.h"
#include "FrameEvent/ChartEvt.h"

//#ifdef _DEBUG
//#define new DEBUG_NEW
//#endif

// CMainFrame

class	CMainFrame::Imp
{
public:

	OgreWndWrapperUPtr	OgreWnd_;
	int					Day_{ 1 };
};

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND( ID_EDIT_DATA, &CMainFrame::OnLoad )
END_MESSAGE_MAP()

// CMainFrame ����/����

CMainFrame::CMainFrame():ImpUPtr_( std::make_unique<Imp>() )
{
	// TODO:  �ڴ���ӳ�Ա��ʼ������
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
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return TRUE;
}

// CMainFrame ���

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


// CMainFrame ��Ϣ�������



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


void CMainFrame::OnLoad()
{
	// TODO:  �ڴ���������������
	DlgEditData dlg;
	dlg.SetDay( ImpUPtr_->Day_ );

	if ( dlg.DoModal() )
	{
		ChartEvt evt;
		if ( dlg.Clear() )
		{
			evt.Clear_ = true;
			ImpUPtr_->Day_ = 1;
		}
		else
		{
			evt.Melanin = dlg.GetHSS();
			evt.Fat = dlg.GetYF();
			evt.Moisture = dlg.GetSF();
			evt.Day_ = ImpUPtr_->Day_;
			if ( evt.Day_ == 1 )
			{
				evt.Clear_ = true;
			}

			auto curDay = ++ImpUPtr_->Day_;
			if ( curDay > 8 )
			{
				curDay = 1;
			}
			ImpUPtr_->Day_ = curDay;
		}

		OgreEnv::GetInstance().PostFrameEventTo3D( evt.ConvertToFrameEvent() );
	}
}
