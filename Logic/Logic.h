
// Logic.h : Logic ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.

#include <gdiplus.h>
using namespace Gdiplus;


// CLogicApp:
// �� Ŭ������ ������ ���ؼ��� Logic.cpp�� �����Ͻʽÿ�.
//

class CLogicApp : public CWinApp
{
public:
	CLogicApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CLogicApp theApp;
