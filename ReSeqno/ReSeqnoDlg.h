
// ReSeqnoDlg.h: Headerdatei

#pragma once


// CReSeqnoDlg-Dialogfeld
class CReSeqnoDlg : public CDialogEx
{
// Konstruktion
public:
	CReSeqnoDlg(CWnd* pParent = nullptr);	// Standardkonstruktor

	CStringArray m_sFilecontent;
	CStringArray m_sFilecontentNew;

// Dialogfelddaten
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RESEQNO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung

private:
	HICON		m_hIcon	;
	CStatic		m_STATIC_PATH;
	CEdit		m_EDIT_FILE;
	CEdit		m_EDIT_OUTPUT;
	CListBox	m_LIST_MESSAGES;
	CComboBox	m_COMBO_START;
	CComboBox	m_COMBO_STEP;
	CComboBox m_COMBO_FILE_PATH;
	CString     m_FILE_NAME;
	CString     g_sFilePath;
	int			m_CCOMBOBOX_INDEX;
	CString		m_sInputfile;
	int			m_RADIO_FILTER_INT;
	CFont		m_CFont;
	int			iFilePathIndex;
	void Close();

//	CButton m_RADIO_NXXX;
// Generierte Funktionen für die Meldungstabellen
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedbuttonopen();
	afx_msg void OnBnClickedButtonSaveFile();
	void OnBnClickedOk();
	void OnBnClickedButtonSave();
	void OnBnClickedCancel();
	void suggestedValues();
	void saveFileInfo();
	void loadFileInfo();
	void updateText();
	void splitPathName();
	void UpdateCombo(CComboBox* pCombo);
	void delteDuplicatesCombobox();
public:
	afx_msg void OnBnClickedButtonCloseFile();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedClearbutton();
	afx_msg void OnBnClickedRadioNxxx();
	afx_msg void OnBnClickedRadioHeidenhein();
	afx_msg void OnBnClickedButtonAbout();
	
	
	
	afx_msg void OnClose();
	afx_msg void OnBnClickedButtonClearEdit();
	afx_msg void OnBnClickedButtonClearOutput();
	
	
	afx_msg void OnBnClickedButtonOpenPath();
	afx_msg void OnBnClickedButtonClearPathBox();
};
