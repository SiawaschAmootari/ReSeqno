
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

CReSeqnoDlg::CReSeqnoDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RESEQNO_DIALOG, pParent)
	, m_RADIO_FILTER_INT(-1)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CReSeqnoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_FILE, m_EDIT_FILE);
	DDX_Control(pDX, IDC_LIST_MESSAGES, m_LIST_MESSAGES);
	DDX_Control(pDX, IDC_COMBO_START, m_COMBO_START);
	DDX_Control(pDX, IDC_EDIT_OUTPUT, m_EDIT_OUTPUT);
	DDX_Control(pDX, IDC_COMBO_STEP, m_COMBO_STEP);
	DDX_Radio(pDX, IDC_RADIO_NXXX, m_RADIO_FILTER_INT);
	DDX_Control(pDX, IDC_COMBO_FILE_PATH, m_COMBO_FILE_PATH);
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
	ON_BN_CLICKED(IDC_RADIO_NXXX, &CReSeqnoDlg::OnBnClickedRadioNxxx)
	ON_BN_CLICKED(IDC_RADIO_HEIDENHEIN, &CReSeqnoDlg::OnBnClickedRadioHeidenhein)
	ON_BN_CLICKED(IDC_BUTTON_ABOUT, &CReSeqnoDlg::OnBnClickedButtonAbout)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_EDIT, &CReSeqnoDlg::OnBnClickedButtonClearEdit)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_OUTPUT, &CReSeqnoDlg::OnBnClickedButtonClearOutput)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_PATH, &CReSeqnoDlg::OnBnClickedButtonOpenPath)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_PATH_BOX, &CReSeqnoDlg::OnBnClickedButtonClearPathBox)
END_MESSAGE_MAP()


// CReSeqnoDlg-Meldungshandler

BOOL CReSeqnoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
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
	m_CFont.CreateFont(16,                                            // Height, ausprobieren
		0,                                              // Width
		0,                                              // Escapement
		0,                                              // Orientation
		FW_MEDIUM,                                // Weight
		FALSE,                                           // Italic
		FALSE,                                           // Underline
		0,                                              // StrikeOut
		ANSI_CHARSET,                             // CharSet
		OUT_DEFAULT_PRECIS,                // OutPrecision
		CLIP_DEFAULT_PRECIS,               // ClipPrecision
		DEFAULT_QUALITY,                   // Quality
		DEFAULT_PITCH | FF_SWISS,   // PitchAndFamily
		_T("Courier New"));                       // Facename
	m_EDIT_FILE.SetFont(&m_CFont, TRUE);
	m_EDIT_OUTPUT.SetFont(&m_CFont, TRUE);
	m_LIST_MESSAGES.SetFont(&m_CFont, TRUE);

	SetIcon(m_hIcon, TRUE);			// Großes Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden
	DragAcceptFiles();
	
	m_CCOMBOBOX_INDEX = 3;

	m_COMBO_STEP.AddString("1");
	m_COMBO_STEP.AddString("2");
	m_COMBO_STEP.AddString("5");
	m_COMBO_STEP.AddString("10");
	
	m_COMBO_START.AddString("1");
	m_COMBO_START.AddString("2");
	m_COMBO_START.AddString("5");
	m_COMBO_START.AddString("10");

	m_COMBO_STEP.SetCurSel(m_CCOMBOBOX_INDEX);
	m_COMBO_START.SetCurSel(m_CCOMBOBOX_INDEX);

	//loadFileInfo();
	m_RADIO_FILTER_INT = -1;
	
	delteDuplicatesCombobox();
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
void CReSeqnoDlg::OnBnClickedButtonOpenPath()
{	
	//CString g_sFilePath;
	CStdioFile csfFile;
	m_COMBO_FILE_PATH.GetWindowTextA(g_sFilePath);
	if (std::ifstream(g_sFilePath).good()) 
	{
		m_RADIO_FILTER_INT = -1;
		UpdateData(false);
		try 
		{
			csfFile.Open(g_sFilePath, CStdioFile::modeRead);

			CString sLine="";
			bool bRead;
			CString sFilecontent = _T("");
			
			m_sFilecontent.RemoveAll();
			splitPathName();
			m_FILE_NAME = m_sInputfile;

			while (true)
			{
				bRead = csfFile.ReadString(sLine);
				if (bRead == false)
				{
					break;
				}
				m_sFilecontent.Add(sLine);
			}
			theApp.ArrToVal(m_sFilecontent, sFilecontent);
			m_EDIT_FILE.SetWindowText(sFilecontent);
			csfFile.Close();
			suggestedValues();
			UpdateData(false);
		}
		catch (const std::out_of_range& e) 
		{
			m_LIST_MESSAGES.InsertString(0, "No file selected");
		}
		catch (const std::invalid_argument& e) 
		{
			m_LIST_MESSAGES.InsertString(0, "Invalid file");
		}
	}
	else 
	{
		m_LIST_MESSAGES.InsertString(0, "Error: filepath is wrong");
	}
}

void CReSeqnoDlg::OnBnClickedbuttonopen()
{
	m_RADIO_FILTER_INT = -1;
	UpdateData(false);
	try 
	{
		CFileDialog cFileDialog(true, NULL, NULL, NULL, _T("mpf-files (*.mpf)|*.mpf;|text-files(*.txt)|*.txt;|tape-files(*.tape)|*.tape;|nc-files(*.nc)|*.nc;|h-files(*.h)|*.h;|All-files(*.*)|*.*;|"));

		int iId;
		iId = (int)cFileDialog.DoModal();
		bool bOk = true;
		//CString m_sInputfile;
		CStdioFile file;
		if (iId == IDOK)
		{
			g_sFilePath = cFileDialog.GetPathName();
			if (std::ifstream(g_sFilePath).good())
			{
				CString sNewName = g_sFilePath + "_backup";
				m_COMBO_FILE_PATH.InsertString(0, g_sFilePath);
				//rename(m_sInputfile, newName);
				CStdioFile file;
				file.Open(g_sFilePath, CStdioFile::modeRead);

				CString sLine = "";
				bool bRead;
				CString sFilecontent = _T("");
				int i = 0;

				m_sFilecontent.RemoveAll();
				m_FILE_NAME = g_sFilePath;

				while (true)
				{
					bRead = file.ReadString(sLine);
					if (bRead == false)
					{
						break;
					}
					m_sFilecontent.Add(sLine);
				}
				theApp.ArrToVal(m_sFilecontent, sFilecontent);
				m_EDIT_FILE.SetWindowText(sFilecontent);
				file.Close();
			}
			if (m_FILE_NAME.GetLength() <= 0) 
			{
				m_LIST_MESSAGES.InsertString(0, "No file selected");
			}
			else 
			{
				suggestedValues();
				UpdateData(false);
			}
		}
	}
	catch (const std::out_of_range& e) 
	{
		m_LIST_MESSAGES.InsertString(0,"No file selected");
	}
	catch(const std::invalid_argument& e)
	{
		m_LIST_MESSAGES.InsertString(0,"Invalid file");
	}
	
}


void CReSeqnoDlg::OnBnClickedOk()
{
	updateText();
	m_EDIT_OUTPUT.Clear();
	m_sFilecontentNew.RemoveAll();
	//updateText();
	// Array durchgehen, zeilenweise ergänzen mit Zeilen nummer
	string sLine;
	CString sLineNew;
	CString sSeqno;
	CString sFilecontentNew; 
	CString sStart;
	CString sStep;
	int iStart;
	bool bChanged = false;
	
	m_COMBO_START.GetWindowTextA(sStart);
	m_COMBO_STEP.GetWindowTextA(sStep);
	
	iStart = atoi(sStart);
	int iStep = atoi(sStep);
	int iLeftBorder = 0;

	if (m_sFilecontent.GetSize() <= 0) 
	{
		m_LIST_MESSAGES.InsertString(0,"File is empty!");
	}

	UpdateData(false);
	/// </NEU NUMMERIEREN BEGIN>/////////////////////////////////////////////////////////
	if (m_RADIO_FILTER_INT == 0) 
	{
		for (int iLine = 0; iLine < m_sFilecontent.GetSize(); iLine++)
		{
			sLine = m_sFilecontent[iLine];
			if (sLine[0] == 'N') {
				for (int iIndexCppsLine = 1; iIndexCppsLine < sLine.size(); iIndexCppsLine++)
				{
					if (isdigit(sLine[iIndexCppsLine])==false)
					{
						iLeftBorder = iIndexCppsLine;
						break;
					}
				}
				sLine = sLine.substr(iLeftBorder, sLine.length());

				sSeqno.Format("N%d", iStart);
				iStart += iStep;
				sLineNew = sSeqno + sLine.c_str();
				m_sFilecontentNew.Add(sLineNew);
				/// </NEU NUMMERIEREN END>/////////////////////////////////////////////////////////
			}
			else
			{
				///Falls die Zeile keine Nummerierung hat wird Sie 1:1 übernommen//////////////////
				m_sFilecontentNew.Add(sLine.c_str());
			}
		}
	}
	else if (m_RADIO_FILTER_INT == 1) 
	{
		for (int iLine = 0; iLine < m_sFilecontent.GetSize(); iLine++)
		{
			sLine = m_sFilecontent[iLine];
			char compare = sLine[0];
			if (isdigit(compare)) 
			{
				for (int iIndexCppsLine = 0; iIndexCppsLine < sLine.size(); iIndexCppsLine++)
				{
					if (isdigit(sLine[iIndexCppsLine])==false)
					{
						iLeftBorder = iIndexCppsLine;
						break;
					}
				}
				sLine = sLine.substr(iLeftBorder, sLine.length());
				sSeqno.Format("%d", iStart);
				iStart += iStep;
				sLineNew = sSeqno + sLine.c_str();
				m_sFilecontentNew.Add(sLineNew);
				/// </NEU NUMMERIEREN END>/////////////////////////////////////////////////////////
			}
			else
			{
				//Falls die Zeile keine Nummerierung hat wird Sie 1:1 übernommen//////////////////
				m_sFilecontentNew.Add(sLine.c_str());
			}

		}	
	}
		theApp.ArrToVal(m_sFilecontentNew, sFilecontentNew);
		m_EDIT_OUTPUT.SetWindowText(sFilecontentNew);
		CString m_sMsg;
		m_sMsg = " Renumbered Start:" + sStart + " Step:" + sStep;
		m_LIST_MESSAGES.InsertString(0,"Start:" + sStart + " Step:" + sStep);
}
/*
void CReSeqnoDlg::UpdateCombo(CComboBox* pCombo){
	CString csCombo;
	int iRet;
	pCombo->GetWindowText(csCombo);                   // aktuellen Text holen
	csCombo.TrimRight();
	csCombo.TrimLeft();
	if (csCombo.IsEmpty()) return;
	iRet = pCombo->FindStringExact(-1, csCombo);   // Wenn noch nicht vorhanden -> neu hinzu. FindStringExact ist nicht case-sensitiv
	if (iRet == -1)
	{

		pCombo->AddString(csCombo);

	}
}*/
/*
Aufruf:
UpdateCombo(&m_COMBOBOX…)
Beispiel aus einem anderen Projekt :
m_COMBO_SEARCH.SetWindowText(sSearch);                             // Suchtext in Combofeld eintragen
UpdateCombo(&m_COMBO_SEARCH);
*/



void CReSeqnoDlg::OnBnClickedButtonSave()
{
	

}


void CReSeqnoDlg::OnBnClickedCancel() // auf escape drücken
{
	Close();
}

void CReSeqnoDlg::OnClose()
{
	Close();
}
void CReSeqnoDlg::Close()
{
	saveFileInfo();
	EndDialog(IDOK);
	CDialog::OnCancel();
}



void CReSeqnoDlg::OnBnClickedButtonSaveFile()
{
	updateText();
	if (g_sFilePath.GetLength() > 0) 
	{
		CString sFilecontentNew;
		string sfileName((LPCTSTR)g_sFilePath);
		string sNewFileName;

		int lastSlashIndex = 0;
		int lastDot = 0;
		// IGNORE:Der Name der Ursprünglichen Datei wird zerlegt und ein "_new" wird angehängt
		// UPDATE: der Name der neuen = Name der alten Datei
		for (int iIndexFileName = 0; iIndexFileName < sfileName.length(); iIndexFileName++)
		{
			if (sfileName[iIndexFileName] == '\\')
			{
				lastSlashIndex = iIndexFileName + 1;
			}
			if (sfileName[iIndexFileName] == '.')
			{
				lastDot = iIndexFileName;
			}
		}

		sNewFileName = sfileName.substr(lastSlashIndex);
		sNewFileName = sNewFileName.replace(sNewFileName.end() - 4, sNewFileName.end(), "");
		sNewFileName = "BackupFiles\\" + sNewFileName + "_backup.mpf";
		int ok = rename(m_FILE_NAME, sNewFileName.c_str());

		// Neuer Dialog wird gestartet, die Datei kann auch überschrieben werden 
		// falls diese schon existiert der User wird aber nochmals gefragt:OFN_OVERWRITEPROMPT 

		CFileDialog cFileDialog(false, _T("mpf"), m_FILE_NAME, OFN_OVERWRITEPROMPT, _T("mpf-files (*.mpf)|*.mpf;|text-Files(*.txt)|*.txt;|"));
		int iId;
		iId = (int)cFileDialog.DoModal();
		bool bOk = true;
		CString m_sSavefile;

		if (iId == IDOK)
		{
			m_sSavefile = cFileDialog.GetPathName();
			CStdioFile file(cFileDialog.GetPathName(), CFile::modeCreate | CFile::modeWrite | CFile::typeText);
			for (int iIndexM_sFilecontentNew = 0; iIndexM_sFilecontentNew < m_sFilecontentNew.GetSize(); iIndexM_sFilecontentNew++)
			{
				file.WriteString(m_sFilecontentNew.GetAt(iIndexM_sFilecontentNew).GetString());
				//file.WriteString("\n");
			}
			if (m_sFilecontent.GetSize() <= 0) 
			{
				m_LIST_MESSAGES.InsertString( 0,"File is empty!");
			}
			file.Flush();
			file.Close();
		}
	}
	else 
	{
		m_LIST_MESSAGES.InsertString(0, m_FILE_NAME);
		m_LIST_MESSAGES.InsertString(0,"File is empty!");
	}
}




void CReSeqnoDlg::OnBnClickedButtonCloseFile()
{
	Close();
}





void CReSeqnoDlg::OnDropFiles(HDROP dropInfo)
{
	//https://helgeklein.com/blog/how-to-enable-drag-and-drop-for-an-elevated-mfc-application-on-vistawindows-7/
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

void CReSeqnoDlg::suggestedValues()
{
	//updateText();
	try 
	{
	string sLine="";
	CString sLineNew;
	CString sSeqno;
	CString sFilecontentNew;
	CString sStart;
	CString sStep;
	int iRightBorder = 0;
	int iStart;
	vector<int>vNumbers;
	
	
	if (m_RADIO_FILTER_INT == -1) 
	{
		for (int iLine = 0; iLine < m_sFilecontent.GetSize(); iLine++)
		{
			sLine = m_sFilecontent[iLine];
			if (sLine[0] == 'N') 
			{
				m_sFilecontentNew.Add("Suggested Filter NXXX");
				m_RADIO_FILTER_INT = 0;
				break;
			}
		}
		if (m_RADIO_FILTER_INT == -1)
		{
			m_sFilecontentNew.Add("Suggested Filter Heidenhain");
			m_RADIO_FILTER_INT = 1;
		}
		UpdateData(false);
	}
	if (m_RADIO_FILTER_INT == 0) 
	{
			for (int iLine = 0; iLine < m_sFilecontent.GetSize(); iLine++)
			{
				sLine = m_sFilecontent[iLine];
				if (sLine[0] == 'N')
				{
					for (int iIndex_sLine = 1; iIndex_sLine < sLine.size(); iIndex_sLine++)
					{
						if (!(isdigit(sLine[iIndex_sLine])))
						{
							iRightBorder = iIndex_sLine;
							break;
						}
					}
					sLine = sLine.substr(1, iRightBorder);
					vNumbers.push_back(stoi(sLine));
				}
			}
		}
		else if (m_RADIO_FILTER_INT == 1) 
		{
			for (int iLine = 0; iLine < m_sFilecontent.GetSize(); iLine++)
			{
				sLine = m_sFilecontent[iLine];
				if (isdigit(sLine[0]))
				{
					for (int iIndex_sLine = 0; iIndex_sLine < sLine.size(); iIndex_sLine++)
					{
						if (!(isdigit(sLine[iIndex_sLine])))
						{
							iRightBorder = iIndex_sLine;
							break;
						}
					}
					sLine = sLine.substr(0, iRightBorder);
					vNumbers.push_back(stoi(sLine));
				}
			}
		}

		CString sSuggestedValue;
		vector<int>vDifference;

		for (int iIndex_vNumbers = 0; iIndex_vNumbers < vNumbers.size() - 1; iIndex_vNumbers++)
		{
			if (vNumbers.at(iIndex_vNumbers +1) - vNumbers.at(iIndex_vNumbers) > 0)
			{
				vDifference.push_back(vNumbers.at(iIndex_vNumbers +1) - vNumbers.at(iIndex_vNumbers));
			}
		}

		sort(vDifference.begin(), vDifference.end());
		int iCount = 0;
		int iHighscore = 0;
		int iStepValue = 0;
		
		for (int iIndex_vDifference_comparableValue = 0; iIndex_vDifference_comparableValue < vDifference.size(); iIndex_vDifference_comparableValue++)
		{
			for (int iIndex_vDifference = 0; iIndex_vDifference < vDifference.size(); iIndex_vDifference++)
			{
				if (vDifference.at(iIndex_vDifference_comparableValue) == vDifference.at(iIndex_vDifference))
				{
					iCount++;
				}
			}
			if (iCount > iHighscore) 
			{
				iHighscore = iCount;
				iStepValue = vDifference.at(iIndex_vDifference_comparableValue);
			}
			iCount = 0;
		}
	
	sSuggestedValue.Format("Suggested Start Value:%d", vNumbers.at(0));
	m_LIST_MESSAGES.InsertString(0,sSuggestedValue);
	sSuggestedValue.Format("Suggested Step Value:%d", iStepValue);
	m_LIST_MESSAGES.InsertString(0,sSuggestedValue);

	sSuggestedValue.Format("%d", iStepValue);
	m_COMBO_STEP.SetWindowText(sSuggestedValue);
	m_COMBO_STEP.AddString(sSuggestedValue);

	sSuggestedValue.Format("%d", vNumbers.at(0));
	m_COMBO_START.SetWindowText(sSuggestedValue);
	m_COMBO_START.AddString(sSuggestedValue);

	m_CCOMBOBOX_INDEX++;

	m_COMBO_FILE_PATH.SetCurSel(0);
	delteDuplicatesCombobox();
	
	//m_COMBO_STEP.SetCurSel(m_CCOMBOBOX_INDEX);
	}
	catch (const std::out_of_range& exception) 
	{
		
		if (m_FILE_NAME.GetLength()<0) 
		{
			m_LIST_MESSAGES.AddString("No file selected");
			m_hWnd = NULL;
			m_pCtrlSite = NULL;
		}
		else if (m_RADIO_FILTER_INT == 0) 
		{
			m_LIST_MESSAGES.AddString("Wrong numbering property please change ");
			m_LIST_MESSAGES.AddString("Current property: NXXX");
			m_LIST_MESSAGES.AddString("Change to: Heidenhein");
		}
		else if (m_RADIO_FILTER_INT == 1) 
		{
			m_LIST_MESSAGES.AddString("Wrong numbering property please change ");
			m_LIST_MESSAGES.AddString("Current property: Heidenhein");
			m_LIST_MESSAGES.AddString("Change to: NXXX");
		}
	}
}

void CReSeqnoDlg::saveFileInfo() 
{
	//Erstellt/Überschreibt die Datei inifile.txt
	//Die Datei liegt im Reseqno Pfad
	//Die Werte für den Start und Step werden aus dem Fenster über GetWindowTextA den Variablen übergeben
	//GetWindowTextA  Übergabeparameter erhalten den gesuchten Wert, die Funktion selbst hat eine int return 
	//ANSI/UNICODE versionen 
	//Methode wir in OnBnClickedButtonCloseFile() aufgerufen

	ofstream osInitialFile("inifile.txt");
	CString sStart;
	CString sStep;
	CString sPath;
	m_COMBO_START.GetWindowTextA(sStart);
	m_COMBO_STEP.GetWindowTextA(sStep);

	osInitialFile << "Information from the last session:" << endl;
	osInitialFile << "START VALUE:" << sStart<< endl;
	osInitialFile << "STEP VALUE:" << sStep << endl;
	osInitialFile << "Paths:" << endl;
	
	for (int iIndex_m_COMBO_FILE_PATH = 0; iIndex_m_COMBO_FILE_PATH < m_COMBO_FILE_PATH.GetCount(); iIndex_m_COMBO_FILE_PATH++)
	{
		m_COMBO_FILE_PATH.GetLBText(iIndex_m_COMBO_FILE_PATH, sPath);
		osInitialFile << iIndex_m_COMBO_FILE_PATH << "Path=" << sPath << endl;
	}
	osInitialFile.close();
}

void CReSeqnoDlg::loadFileInfo()
{	
	// Die Datei inifile wird mit mit der Information der letzten Sitzung geladen
	// Die Werte werden in ein String abgespeichert und dann der CCombobox erst dazu addiert
	// m_CCOMBOBOX_INDEX wird um eins erhöht damit es auf das zuletzt hinzugefügte Wert zeigt
	// Die String zerlegung wurde mit C++ strings verarbeitet und ich ein CString am ende eingespeichert
	ifstream isInitialFile("inifile.txt");
	string sLine;
	m_CCOMBOBOX_INDEX++;
	iFilePathIndex = -1;
	while (getline(isInitialFile, sLine))
	{
		if (sLine.find("START")!=string::npos) 
		{
			for (int iLine = 0; iLine < sLine.size(); iLine++) 
			{
				if (sLine[iLine] == ':') 
				{
					string substring = sLine.replace(sLine.begin(),sLine.begin()+ iLine +1,"");
					//m_COMBO_START.AddString(substring.c_str());
					//m_COMBO_START.SetCurSel(m_CCOMBOBOX_INDEX);
					m_COMBO_START.SetWindowText(substring.c_str());
				}
			}
		}
		if (sLine.find("STEP") != string::npos) 
		{
			for (int iLine = 0; iLine < sLine.size(); iLine++) 
			{
				if (sLine[iLine] == ':') 
				{
					string substring = sLine.replace(sLine.begin(), sLine.begin() + iLine + 1, "");
					//m_COMBO_STEP.AddString(substring.c_str());
					//m_COMBO_STEP.SetCurSel(m_CCOMBOBOX_INDEX);
					m_COMBO_STEP.SetWindowText(substring.c_str());
				}
			}
		}
		if (sLine.find("Path") != string::npos) 
		{
			for (int iLine = 0; iLine < sLine.size(); iLine++) 
			{
				if (sLine[iLine] == '=') 
				{
					string substring = sLine.replace(sLine.begin(), sLine.begin() + iLine + 1, "");
					m_COMBO_FILE_PATH.AddString(substring.c_str());
					iFilePathIndex++;
				}
			}
		}
	}
	m_COMBO_FILE_PATH.SetCurSel(iFilePathIndex);
	isInitialFile.close();
}

void CReSeqnoDlg::OnBnClickedButton1()
{
	m_LIST_MESSAGES.ResetContent();
}

void CReSeqnoDlg::updateText() {
	//theApp.ArrToVal(m_sFilecontent, sFilecontent);
	//m_EDIT_FILE.SetWindowText(sFilecontent);
	CString sUpdateText;
	m_EDIT_FILE.GetWindowTextA(sUpdateText);
	m_sFilecontent.RemoveAll();
	CString sLine;
	for (int iUpdateText = 0; iUpdateText < sUpdateText.GetLength(); iUpdateText++)
	{
		if (sUpdateText[iUpdateText] =='\n')
		{
			sLine = sLine + sUpdateText[iUpdateText];
			m_sFilecontent.Add(sLine);
			sLine = "";
		}
		else if(sUpdateText[iUpdateText] != '\r')
		{
			sLine = sLine + sUpdateText[iUpdateText];
		}
	}
	
	for (int iUpdateText = 0; iUpdateText < sUpdateText.GetLength(); iUpdateText++)
	{
		if (sUpdateText[iUpdateText] == '\n')
		{
			sLine = sLine + sUpdateText[iUpdateText];
			m_sFilecontent.Add(sLine);
			sLine = "";
		}
		else if (sUpdateText[iUpdateText] != '\r')
		{
			sLine = sLine + sUpdateText[iUpdateText];
		}
	}

}

void CReSeqnoDlg::OnBnClickedClearbutton()
{
	m_LIST_MESSAGES.ResetContent();
}

void CReSeqnoDlg::OnBnClickedRadioNxxx()
{
	m_RADIO_FILTER_INT = 0;
}

void CReSeqnoDlg::OnBnClickedRadioHeidenhein()
{
	m_RADIO_FILTER_INT = 1;
}

void CReSeqnoDlg::OnBnClickedButtonAbout()
{
	CAboutDlg cAboutDlg;
	cAboutDlg.DoModal();
}

void CReSeqnoDlg::OnBnClickedButtonClearEdit()
{
	m_sFilecontent.RemoveAll();
	m_EDIT_FILE.SetSel(0, -1);
	m_EDIT_FILE.Clear();
}

void CReSeqnoDlg::OnBnClickedButtonClearOutput()
{
	m_EDIT_OUTPUT.SetSel(0, -1);
	m_EDIT_OUTPUT.Clear();
}

void CReSeqnoDlg::OnBnClickedButtonClearPathBox()
{
	m_COMBO_FILE_PATH.ResetContent();
}

void CReSeqnoDlg::splitPathName() {
	CString sReplaceNameReverse=_T("");
	CString sReplaceName = _T("");
	int iSlashIndex = 0;
	for (int iIndex_g_sFilePath = g_sFilePath.GetLength()-1; iIndex_g_sFilePath >= 0; iIndex_g_sFilePath--) 
	{
		sReplaceNameReverse.AppendChar(g_sFilePath.GetAt(iIndex_g_sFilePath));
	}

	for (int iIndex_sReplaceNameReverse = sReplaceNameReverse.GetLength()-1; iIndex_sReplaceNameReverse >= 0; iIndex_sReplaceNameReverse--) 
	{
		sReplaceName.AppendChar(sReplaceNameReverse.GetAt(iIndex_sReplaceNameReverse));
	}
	m_LIST_MESSAGES.AddString(g_sFilePath);
	m_LIST_MESSAGES.AddString(sReplaceName);
	m_FILE_NAME.Append(sReplaceName);
	m_LIST_MESSAGES.AddString(m_FILE_NAME);
}


void CReSeqnoDlg::delteDuplicatesCombobox() {
	int iCount = m_COMBO_START.GetCount();
	if (iCount <= 0) return;
	CString sCompareOne;
	CString sCompareTwo;

	for (int iIndex_COMBO_START_sCompareOne = 0; iIndex_COMBO_START_sCompareOne < iCount; iIndex_COMBO_START_sCompareOne++)
	{
		m_COMBO_START.GetLBText(iIndex_COMBO_START_sCompareOne, sCompareOne);
		for (int iIndex_COMBO_START_sCompareTwo = 0; iIndex_COMBO_START_sCompareTwo < iCount; iIndex_COMBO_START_sCompareTwo++)
		{
			m_COMBO_START.GetLBText(iIndex_COMBO_START_sCompareTwo, sCompareTwo);
			if (sCompareOne == sCompareTwo && iIndex_COMBO_START_sCompareOne != iIndex_COMBO_START_sCompareTwo)
			{
				m_COMBO_START.DeleteString(iIndex_COMBO_START_sCompareTwo);
				iCount--;
			}
		}
	}

	iCount = m_COMBO_STEP.GetCount();
	if (iCount <= 0) return;

	for (int iIndex_COMBO_START_sCompareOne = 0; iIndex_COMBO_START_sCompareOne < iCount; iIndex_COMBO_START_sCompareOne++)
	{
		m_COMBO_STEP.GetLBText(iIndex_COMBO_START_sCompareOne, sCompareOne);
		for (int iIndex_COMBO_START_sCompareTwo = 0; iIndex_COMBO_START_sCompareTwo < iCount; iIndex_COMBO_START_sCompareTwo++)
		{
			m_COMBO_STEP.GetLBText(iIndex_COMBO_START_sCompareTwo, sCompareTwo);
			if (sCompareOne == sCompareTwo && iIndex_COMBO_START_sCompareOne != iIndex_COMBO_START_sCompareTwo)
			{
				m_COMBO_STEP.DeleteString(iIndex_COMBO_START_sCompareTwo);
				iCount--;
			}
		}
	}
}


