
// tp_lpu237.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// Ctplpu237App:
// See tp_lpu237.cpp for the implementation of this class
//

class Ctplpu237App : public CWinApp
{
public:
	Ctplpu237App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern Ctplpu237App theApp;
