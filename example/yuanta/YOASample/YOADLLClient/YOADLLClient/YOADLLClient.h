
// YOADLLClient.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CYOADLLClientApp:
// �� Ŭ������ ������ ���ؼ��� YOADLLClient.cpp�� �����Ͻʽÿ�.
//

class CYOADLLClientApp : public CWinApp
{
public:
	CYOADLLClientApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CYOADLLClientApp theApp;