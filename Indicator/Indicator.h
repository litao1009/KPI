
// KPI.h : KPI Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CKPIApp:
// �йش����ʵ�֣������ KPI.cpp
//

class CIndicatorApp : public CWinApp
{
public:
	CIndicatorApp();


	virtual BOOL OnIdle(LONG lCount) override;

	virtual BOOL IsIdleMessage(MSG* pMsg) override;


	virtual int ExitInstance() override;

	// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CIndicatorApp theApp;
