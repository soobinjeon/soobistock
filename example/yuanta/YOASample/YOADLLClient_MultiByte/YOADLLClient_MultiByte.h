
// YOADLLClient_MultiByte.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CYOADLLClient_MultiByteApp:
// �� Ŭ������ ������ ���ؼ��� YOADLLClient_MultiByte.cpp�� �����Ͻʽÿ�.
//

class CYOADLLClient_MultiByteApp : public CWinApp
{
public:
	CYOADLLClient_MultiByteApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CYOADLLClient_MultiByteApp theApp;