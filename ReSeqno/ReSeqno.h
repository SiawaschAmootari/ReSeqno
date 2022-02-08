
// ReSeqno.h: Hauptheaderdatei für die PROJECT_NAME-Anwendung
//

#pragma once

#ifndef __AFXWIN_H__
#error "'pch.h' vor dieser Datei für PCH einschließen"
#endif

#include "resource.h"		// Hauptsymbole

// #sia
typedef CStringArray CStrArr;


// CReSeqnoApp:
// Siehe ReSeqno.cpp für die Implementierung dieser Klasse
//

class CReSeqnoApp : public CWinApp
{
public:
	CReSeqnoApp();
	// #sia
	void	ArrToVal(const CStrArr& sValArr, CString& sVal);
	void	ArrToVal(const CString sDel, const CStrArr& sValArr, CString& sVal);

	// Überschreibungen
public:
	virtual BOOL InitInstance();

	// Implementierung

	DECLARE_MESSAGE_MAP()
};

extern CReSeqnoApp theApp;
