
// stdafx.cpp : 표준 포함 파일만 들어 있는 소스 파일입니다.
// YOADLLClient.pch는 미리 컴파일된 헤더가 됩니다.
// stdafx.obj에는 미리 컴파일된 형식 정보가 포함됩니다.

#include "stdafx.h"


IYOA			g_iYuantaAPI;
BOOL			g_bInitial		= FALSE;
BOOL			g_bLogin		= FALSE;
int				g_nStartMsgID	= WM_USER;