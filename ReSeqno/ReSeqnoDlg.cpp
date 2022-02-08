
// ReSeqnoDlg.cpp: Implementierungsdatei
//

#include "pch.h"
#include "resource.h"
#include "framework.h"
#include "ReSeqno.h"
#include "ReSeqnoDlg.h"
#include "afxdialogex.h"
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg-Dialogfeld für Anwendungsbefehl "Info"

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialogfelddaten
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

// Implementierung
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CReSeqnoDlg-Dialogfeld



CReSeqnoDlg::CReSeqnoDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RESEQNO_DIALOG, pParent)
	, m_RADIO_FILTER_INT(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CReSeqnoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_PATH, m_STATIC_PATH);
	DDX_Control(pDX, IDC_EDIT_FILE, m_EDIT_FILE);
	DDX_Control(pDX, IDC_LIST_MESSAGES, m_LIST_MESSAGES);
	DDX_Control(pDX, IDC_COMBO_START, m_COMBO_START);
	DDX_Control(pDX, IDC_EDIT_OUTPUT, m_EDIT_OUTPUT);
	DDX_Control(pDX, IDC_COMBO_STEP, m_COMBO_STEP);
	DDX_Radio(pDX, IDC_RADIO_NXXX, m_RADIO_FILTER_INT);
}

BEGIN_MESSAGE_MAP(CReSeqnoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(buttonOpen, &CReSeqnoDlg::OnBnClickedbuttonopen)
	ON_BN_CLICKED(IDOK, &CReSeqnoDlg::OnBnClickedOk)
	ON_WM_DROPFILES()
	
	ON_BN_CLICKED(IDCANCEL, &CReSeqnoDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_FILE, &CReSeqnoDlg::OnBnClickedButtonSaveFile)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_FILE, &CReSeqnoDlg::OnBnClickedButtonCloseFile)

	ON_BN_CLICKED(IDC_CLEARBUTTON, &CReSeqnoDlg::OnBnClickedClearbutton)
END_MESSAGE_MAP()


// CReSeqnoDlg-Meldungshandler

BOOL CReSeqnoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Hinzufügen des Menübefehls "Info..." zum Systemmenü.

	// IDM_ABOUTBOX muss sich im Bereich der Systembefehle befinden.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Symbol für dieses Dialogfeld festlegen.  Wird automatisch erledigt
	//  wenn das Hauptfenster der Anwendung kein Dialogfeld ist
	SetIcon(m_hIcon, TRUE);			// Großes Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden
	DragAcceptFiles();
	m_CCOMBOBOX_INDEX = 3;
	m_COMBO_STEP.AddString(("1"));
	m_COMBO_STEP.AddString("2");
	m_COMBO_STEP.AddString("5");
	m_COMBO_STEP.AddString("10");


	m_COMBO_START.AddString("1");
	m_COMBO_START.AddString("2");
	m_COMBO_START.AddString("5");
	m_COMBO_START.AddString("10");

	m_COMBO_STEP.SetCurSel(m_CCOMBOBOX_INDEX);
	m_COMBO_START.SetCurSel(m_CCOMBOBOX_INDEX);

	loadFileInfo();
	return TRUE;  // TRUE zurückgeben, wenn der Fokus nicht auf ein Steuerelement gesetzt wird
}


void CReSeqnoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// Wenn Sie dem Dialogfeld eine Schaltfläche "Minimieren" hinzufügen, benötigen Sie
//  den nachstehenden Code, um das Symbol zu zeichnen.  Für MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch ausgeführt.

void CReSeqnoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Gerätekontext zum Zeichnen

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Symbol in Clientrechteck zentrieren
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Symbol zeichnen
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Die System ruft diese Funktion auf, um den Cursor abzufragen, der angezeigt wird, während der Benutzer
//  das minimierte Fenster mit der Maus zieht.
HCURSOR CReSeqnoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CReSeqnoDlg::OnBnClickedbuttonopen()
{

	// TODO: Fügen Sie hier Ihren Handlercode für Benachrichtigungen des Steuerelements ein.
	
	CFileDialog cFileDialog(true ,NULL, NULL, NULL, _T("mpf-files (*.mpf)|*.mpf;|text-files(*.txt)|*.txt;|tape-files(*.tape)|*.tape;|nc-files(*.nc)|*.nc;|h-files(*.h)|*.h;|All-files(*.*)|*.*;|"));

	int iD;
	iD = (int)cFileDialog.DoModal();
	bool bOk = true;
	//CString m_sInputfile;
	CStdioFile file;
	vector<string>data;
	if (iD == IDOK)
	{
		
		m_sInputfile = cFileDialog.GetPathName();
		CString newName = m_sInputfile + "_backup";
		m_STATIC_PATH.SetWindowText(m_sInputfile);
		//rename(m_sInputfile, newName);
		CStdioFile file;
		file.Open(m_sInputfile, CStdioFile::modeRead);
		
		CString sLine;
		bool bRead;
		CString sFilecontent = _T("");
		int i = 0;

		m_sFilecontent.RemoveAll();
		m_FILE_NAME = m_sInputfile;
		
		while (true)
		{
			bRead = file.ReadString(sLine);
			if (bRead == false)
			{
				break;
			}

			m_sFilecontent.Add(sLine);
			data.push_back((LPCTSTR)sLine);
		}
		theApp.ArrToVal(m_sFilecontent, sFilecontent);
		m_EDIT_FILE.SetWindowText(sFilecontent);
		
		
	}
	if (m_sFilecontent.GetSize() <= 0) {
		m_LIST_MESSAGES.AddString("File is empty!");
	}
	
	




	//---------------------------------------------------------//
	suggestedValues();

}


void CReSeqnoDlg::OnBnClickedOk()
{

	//CString windowText;
	//m_EDIT_FILE.GetWindowTextA(windowText);
	// Array durchgehen, zeilenweise ergänzen mit Zeilen nummer
	string cppLine;
	CString sLineNew;
	CString sSeqno;
	CString sFilecontentNew; 
	CString sStart;
	CString sStep;
	int iStart;
	bool changed = false;
	m_COMBO_START.GetWindowTextA(sStart);
	m_COMBO_STEP.GetWindowTextA(sStep);
	
	iStart = atoi(sStart);
	
	int iStep = atoi(sStep);
	int firstSpaceIndex = 0;

	if (m_sFilecontent.GetSize() <= 0) 
	{
		m_LIST_MESSAGES.AddString("File is empty!");
	}



	/// </NEU NUMMERIEREN BEGIN>/////////////////////////////////////////////////////////
	for (int iLine = 0; iLine < m_sFilecontent.GetSize(); iLine++)
	{

		cppLine = m_sFilecontent[iLine];
					if (cppLine[0] == 'N') {

				for (int i = 0; i < cppLine.size(); i++)
				{
					if (cppLine[i] == ' ') {
						firstSpaceIndex = i;
						break;
					}
				}
				cppLine = cppLine.substr(firstSpaceIndex, cppLine.length());

				sSeqno.Format("N%d ", iStart);
				iStart += iStep;
				sLineNew = sSeqno + cppLine.c_str();
				m_sFilecontentNew.Add(sLineNew);

				/// </NEU NUMMERIEREN END>/////////////////////////////////////////////////////////
			}
			else
			{
				//Falls die Zeile keine Nummerierung hat wird Sie 1:1 übernommen//////////////////
				m_sFilecontentNew.Add(cppLine.c_str());
			}
		
		
		
	}
	
		theApp.ArrToVal(m_sFilecontentNew, sFilecontentNew);
		m_EDIT_OUTPUT.SetWindowText(sFilecontentNew);
		CString m_sMsg;
		m_sMsg = " Renumbered Start:" + sStart + " Step:" + sStep;
		m_LIST_MESSAGES.AddString("Start:" + sStart + " Step:" + sStep);
}




void CReSeqnoDlg::OnBnClickedButtonSave()
{
	

}


void CReSeqnoDlg::OnBnClickedCancel()
{
	// TODO: Fügen Sie hier Ihren Handlercode für Benachrichtigungen des Steuerelements ein.
	CDialogEx::OnCancel();
	
}




void CReSeqnoDlg::OnBnClickedButtonSaveFile()
{


	CString sFilecontentNew;
	string sfileName(m_FILE_NAME, m_FILE_NAME.GetLength());
	string snewFileName;
	
	int lastSlashIndex = 0;
	int lastDot = 0;
	
	// IGNORE:Der Name der Ursprünglichen Datei wird zerlegt und ein "_new" wird angehängt
	// UPDATE: der Name der neuen = Name der alten Datei
	//         alte Da
	for (int i = 0; i < sfileName.length(); i++) 
	{
		if (sfileName[i] == '\\') {
			lastSlashIndex = i + 1;
		}
		if (sfileName[i] == '.') {
			lastDot = i;
		}

	}

	snewFileName = sfileName.substr(lastSlashIndex);
	//lastDot = snewFileName.find_last_of('.');
	snewFileName = snewFileName.replace(snewFileName.end() - 4, snewFileName.end(), "");
	snewFileName = "BackupFiles\\" + snewFileName + "_backup.mpf";
	int ok = rename(m_FILE_NAME, snewFileName.c_str());

	// Neuer Dialog wird gestartet, die Datei kann auch überschrieben werden 
	// falls diese schon existiert der User wird aber nochmals gefragt:OFN_OVERWRITEPROMPT 

	CFileDialog cFileDialog(false, _T("mpf"), m_FILE_NAME, OFN_OVERWRITEPROMPT, _T("mpf-files (*.mpf)|*.mpf;|text-Files(*.txt)|*.txt;|"));
	int iD;
	iD = (int)cFileDialog.DoModal();
	bool bOk = true;
	CString m_sSavefile;
	
	if (iD == IDOK)
	{
		m_sSavefile = cFileDialog.GetPathName();
		CStdioFile file(cFileDialog.GetPathName(), CFile::modeCreate | CFile::modeWrite | CFile::typeBinary );
		

		for (int i = 0; i < m_sFilecontentNew.GetSize(); i++) {
			file.WriteString(m_sFilecontentNew.GetAt(i).GetString());
			file.WriteString("\r\n");
		}

		if (m_sFilecontent.GetSize() <= 0) {
			m_LIST_MESSAGES.AddString("File is empty!");
		}
		file.Flush();
		file.Close();
	}
	
}




void CReSeqnoDlg::OnBnClickedButtonCloseFile()
{
	// TODO: Add your control notification handler code here
	//Ruft die Methode saveFileInfo() auf bevor das Programm geschlossen wird

	saveFileInfo();
	PostQuitMessage(0);
}


void CReSeqnoDlg::OnBnClickedRadio2()
{
	// TODO: Add your control notification handler code here
}


void CReSeqnoDlg::OnDropFiles(HDROP dropInfo)
{
	ChangeWindowMessageFilter(WM_DROPFILES, MSGFLT_ADD);
	ChangeWindowMessageFilter(WM_COPYDATA, MSGFLT_ADD);
	ChangeWindowMessageFilter(0x0049, MSGFLT_ADD);
	CString    sFile;
	DWORD      nBuffer = 0;
	// Get the number of files dropped
	UINT nFilesDropped = DragQueryFile(dropInfo, 0xFFFFFFFF, NULL, 0);
	// If more than one, only use the first
	if (nFilesDropped > 0)
	{
		// Get the buffer size for the first filename
		nBuffer = DragQueryFile(dropInfo, 0, NULL, 0);
		// Get path and name of the first file
		DragQueryFile(dropInfo, 0, sFile.GetBuffer(nBuffer + 1), nBuffer + 1);
		sFile.ReleaseBuffer();
		// Do something with the path
	}
	// Free the memory block containing the dropped-file information
	DragFinish(dropInfo);
}



//Löscht alles was in Message Box enthalten ist


void CReSeqnoDlg::suggestedValues()
{
	string sLine;
	CString sLineNew;
	CString sSeqno;
	CString sFilecontentNew;
	CString sStart;
	CString sStep;
	int firstSpaceIndex = 0;
	int iStart;
	vector<int>numberVector;
	// TODO: Add your control notification handler code here
	int counter = 0;
	for (int iLine = 0; iLine < m_sFilecontent.GetSize(); iLine++)
	{
		sLine = m_sFilecontent[iLine];
		if (sLine[0] == 'N' ) {

			for (int i = 0; i < sLine.size(); i++)
			{
				if (sLine[i] == ' ') {
					firstSpaceIndex = i;
					break;
				}
			}
			sLine = sLine.substr( 1 ,firstSpaceIndex );

			numberVector.push_back( stoi(sLine));
			
		}
	
	}

	CString suggestedValue;
	//length.Format(" Length %d", numberVector.size());
	
	vector<int>diff;

	for (int i = 0; i <numberVector.size() - 1; i++) {
		//cout<<allNumbers[i]<<endl;
		if (numberVector.at(i + 1) - numberVector.at(i) > 0) {
			diff.push_back(numberVector.at(i + 1) - numberVector.at(i));
		}
	}

	sort(diff.begin(),diff.end());

	int count = 0;
	int highscore = 0;
	int index = 0;

	for (int i = 0; i < diff.size()-1; i++) {
		if (diff.at(i) == diff.at(i + 1)) {
			count++;
		}
		else {
			if (count > highscore) {
				highscore = counter;
				index = i;
				counter = 0;
			}
		}
	}

	suggestedValue.Format("Suggested Start Value:%d", numberVector.at(0));
	m_LIST_MESSAGES.AddString(suggestedValue);
	suggestedValue.Format("Suggested Step Value:%d", diff.at(index));
	m_LIST_MESSAGES.AddString(suggestedValue);

	suggestedValue.Format("%d", diff.at(index));
	m_COMBO_STEP.AddString(suggestedValue);
	suggestedValue.Format("%d", numberVector.at(0));
	m_COMBO_START.AddString(suggestedValue);

	m_CCOMBOBOX_INDEX++;
	m_COMBO_START.SetCurSel(m_CCOMBOBOX_INDEX);
	m_COMBO_STEP.SetCurSel(m_CCOMBOBOX_INDEX);
	

}

void CReSeqnoDlg::saveFileInfo() 
{
	//Erstellt/Überschreibt die Datei inifile.txt
	//Die Datei liegt im Reseqno Pfad
	//Die Werte für den Start und Step werden aus dem Fenster über GetWindowTextA den Variablen übergeben
	//GetWindowTextA  Übergabeparameter erhalten den gesuchten Wert, die Funktion selbst hat eine int return 
	//ANSI/UNICODE versionen 
	//Methode wir in OnBnClickedButtonCloseFile() aufgerufen

	ofstream inifile("inifile.txt");
	CString sStart;
	CString sStep;

	m_COMBO_START.GetWindowTextA(sStart);
	m_COMBO_STEP.GetWindowTextA(sStep);

	inifile << "Information from the last session:" << endl;
	inifile << "START VALUE:" << sStart<< endl;
	inifile << "STEP VALUE:" << sStep << endl;
	
	inifile.close();

}

void CReSeqnoDlg::loadFileInfo()
{
	// Die Datei inifile wird mit mit der Information der letzten Sitzung geladen
	// Die Werte werden in ein String abgespeichert und dann der CCombobox erst dazu addiert
	// m_CCOMBOBOX_INDEX wird um eins erhöht damit es auf das zuletzt hinzugefügte Wert zeigt
	// Die String zerlegung wurde mit C++ strings verarbeitet und ich ein CString am ende eingespeichert

	ifstream inifile("inifile.txt");
	string line;
	m_CCOMBOBOX_INDEX++;
	while (getline(inifile, line)) {
		if (line.find("START")!=string::npos) {
			for (int i = 0; i < line.size(); i++) {
				if (line[i] == ':') {
					string substring = line.replace(line.begin(),line.begin()+i+1,"");
					m_COMBO_START.AddString(substring.c_str());
					m_COMBO_START.SetCurSel(m_CCOMBOBOX_INDEX);
				}
			}
		}
		if (line.find("STEP") != string::npos) {
			for (int i = 0; i < line.size(); i++) {
				if (line[i] == ':') {
					string substring = line.replace(line.begin(), line.begin() + i + 1, "");
					m_COMBO_STEP.AddString(substring.c_str());
					m_COMBO_STEP.SetCurSel(m_CCOMBOBOX_INDEX);
				}
			}
		}
	}

	inifile.close();

}

void CReSeqnoDlg::OnBnClickedButton1()
{
	//Löscht Alle Elemente aus der Message Box
	//Name der Funktion sollte noch geändert werden
	m_LIST_MESSAGES.ResetContent();
}









void CReSeqnoDlg::OnBnClickedClearbutton()
{
	m_LIST_MESSAGES.ResetContent();
}