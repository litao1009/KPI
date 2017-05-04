
// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "KPI.h"

#include "MainFrm.h"

#include "Frame/OgreEnv.h"
#include "Frame/OgreWndWrapper.h"
#include "Controller/DummyController.h"

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

	auto ctrller = std::make_shared<DummyController>(ImpUPtr_->OgreWnd_->GetRenderWindow());
	OgreEnv::GetInstance().AddController(ctrller);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
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
