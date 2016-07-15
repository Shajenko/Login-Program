
// TLCSignInDlg.h : header file
//

#pragma once
#include <afxdb.h>



// CTLCSignInDlg dialog
class CTLCSignInDlg : public CDialogEx
{
// Construction
public:
	CTLCSignInDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TLCSIGNIN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	CDatabase * db;
	CString sDsn;

	CString sEmpID;
	CString sPurpose;
	CTime tDate;

	CEdit * eIDEdit;
	CButton * signinButton;
	CComboBox * purposeCombo;

	CString idText, purposeText;

	bool validID, validReason;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSigninbutton();
	afx_msg void OnEnChangeIDEdit();
	afx_msg void OnCbnSelchangePurposeCombo();
};
