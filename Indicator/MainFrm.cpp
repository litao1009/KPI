
// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "Indicator.h"

#include "MainFrm.h"

#include "DlgParam.h"

#include "Frame/OgreEnv.h"
#include "Frame/OgreWndWrapper.h"
#include "Controller/IndicatorController.h"
#include "FrameEvent/IndicatorEvt.h"

#include <fstream>
#include <regex>

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
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_COMMAND( ID_IMPORT, &CMainFrame::OnImport )
	ON_COMMAND( ID_MODIFY_PARAM, &CMainFrame::OnModifyParam )
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/����

CMainFrame::CMainFrame() :ImpUPtr_(std::make_unique<Imp>())
{
	// TODO:  �ڴ���ӳ�Ա��ʼ������
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	auto cf = GetActiveView();
	

	auto curHwnd = reinterpret_cast<int>( cf->GetSafeHwnd() );
	RECT rect;
	cf->GetClientRect(&rect);
	ImpUPtr_->OgreWnd_ = OgreEnv::GetInstance().CreateRenderWindow(curHwnd, rect.right - rect.left, rect.bottom - rect.top);

	auto ctrller = std::make_shared<IndicatorController>(ImpUPtr_->OgreWnd_->GetRenderWindow());
	OgreEnv::GetInstance().AddController(ctrller);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	auto height = 800;
	cs.cx = height * 2 + 20;
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



void CMainFrame::OnDestroy()
{
	OgreEnv::GetInstance().RemoveAllController();
	ImpUPtr_->OgreWnd_->Destory();

	CFrameWnd::OnDestroy();

	// TODO:  �ڴ˴������Ϣ����������
}


void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CFrameWnd::OnSize(nType, cx, cy);
	if ( ImpUPtr_->OgreWnd_ )
	{
		ImpUPtr_->OgreWnd_->Resize(0, 0);
	}
	// TODO:  �ڴ˴������Ϣ����������
}


void CMainFrame::OnImport()
{
	// TODO:  �ڴ���������������	
	CFileDialog dlg(TRUE, 0, 0, 6UL, _T("�ļ� (*.txt)|*.txt||"));
	
	auto ret = dlg.DoModal();
	if ( ret == 1 )
	{
		auto fp = dlg.GetPathName();
		std::wstring wstr = fp.GetBuffer();
		fp.ReleaseBuffer();

		std::ifstream ifs( wstr );
		std::string line;

		std::regex rg( R"((\d+))" );
		std::smatch what;

		auto evt = std::make_shared<IndicatorEvt>();

		std::getline( ifs, line );
		if ( !std::regex_match( line, what, rg ) )
		{
			MessageBox( _T( "��ʽ����" ) );
		}
		evt->Moisture = std::stoi( what[1].str() );

		std::getline( ifs, line );
		if ( !std::regex_match( line, what, rg ) )
		{
			MessageBox( _T( "��ʽ����" ) );
		}
		evt->Fat = std::stoi( what[1].str() );

		std::getline( ifs, line );
		if ( !std::regex_match( line, what, rg ) )
		{
			MessageBox( _T( "��ʽ����" ) );
		}
		evt->Melanin = std::stoi( what[1].str() );

		OgreEnv::GetInstance().PostFrameEventTo3D( evt->ConvertToFrameEvent() );
	}
}


void CMainFrame::OnModifyParam()
{
	// TODO:  �ڴ���������������
	{
		auto evt = std::make_shared<ClearEvt>();
		OgreEnv::GetInstance().PostFrameEventTo3D( evt->ConvertToFrameEvent() );
	}

	CDlgParam dlg;
	auto ret = dlg.DoModal();
	if ( ret == 1 )
	{
		auto evt = std::make_shared<IndicatorEvt>();
		evt->Fat = dlg.GetYF();
		evt->Moisture = dlg.GetSF();
		evt->Melanin = dlg.GetHSS();
		evt->Male = dlg.IsMale();
		evt->Age_ = dlg.GetAge();

		OgreEnv::GetInstance().PostFrameEventTo3D( evt->ConvertToFrameEvent() );
	}
}
