
// Chart.h : Chart Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CChartApp:
// �йش����ʵ�֣������ Chart.cpp
//

class CChartApp : public CWinApp
{
public:
	CChartApp();


	virtual int ExitInstance() override;

	virtual BOOL OnIdle( LONG lCount ) override;

	virtual BOOL IsIdleMessage( MSG* pMsg ) override;

	virtual BOOL PumpMessage() override;

	// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CChartApp theApp;
