
// TLCSignInDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TLCSignIn.h"
#include "TLCSignInDlg.h"
#include "afxdialogex.h"
#include "Signin_Records.h"
#include <string>
#include <ctype.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTLCSignInDlg dialog



CTLCSignInDlg::CTLCSignInDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTLCSignInDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTLCSignInDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTLCSignInDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SIGNINBUTTON, &CTLCSignInDlg::OnBnClickedSigninbutton)
	ON_EN_CHANGE(IDC_EDIT1, &CTLCSignInDlg::OnEnChangeIDEdit)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CTLCSignInDlg::OnCbnSelchangePurposeCombo)
END_MESSAGE_MAP()


// CTLCSignInDlg message handlers

BOOL CTLCSignInDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	ShowWindow(SW_SHOW);

	// TODO: Add extra initialization here
	db = new CDatabase();

	eIDEdit = (CEdit *)GetDlgItem(IDC_EID);
	purposeCombo = (CComboBox *)GetDlgItem(IDC_REASONCOMBO);
	signinButton = (CButton *)GetDlgItem(IDC_SIGNINBUTTON);

	eIDEdit->LimitText(8);

	signinButton->EnableWindow(FALSE);//Disables the Sign In Button
	validID = false;
	validReason = false;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTLCSignInDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTLCSignInDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTLCSignInDlg::OnBnClickedSigninbutton()
{

	CSignin_Records * rec;

	std::string text;
	LPTSTR editText;

	editText = _T("");

	// TODO: Add your control notification handler code here

	if (!db->Open(_T("TLC Sign in")))
	{
		MessageBox(_T("Error: database TLCSignin.accdb does not exist."));
		return;
	}

	if(!db->CanUpdate())
	{
		MessageBox(_T("Error: cannot update database."));
		return;
	}

	if (!db->CanTransact())
	{
		MessageBox(_T("Error: cannot transact with database."));
		return;
	}

	rec = new CSignin_Records(db);
	rec->Open(CSignin_Records::dynaset, _T("SELECT * from Signin_Records"));  // fail here - why?

	if (!rec->IsOpen())
	{
		MessageBox(_T("Error: failed to open the recordset."));
		return;
	}

	if (!rec->CanAppend())
	{
		MessageBox(_T("Error: cannot append the recordset."));
		return;
	}

	if (!rec->CanUpdate())
	{
		MessageBox(_T("Error: cannot update the recordset."));
		return;
	}

	tDate = CTime::GetCurrentTime();



	//purposeCombo->get

	rec->AddNew();
	rec->m_EmployeeID = idText;
	rec->m_Signin_Date = CTime(tDate.GetYear(), tDate.GetMonth(), tDate.GetDay(), tDate.GetHour(), tDate.GetMinute(), tDate.GetSecond());
	rec->m_Purpose = purposeText;


	if (!rec->Update())
	{
		MessageBox(_T("Error: update failed."));
		db->Close();
		MessageBox(_T("Database closed"));
		return;
	}


	db->Close();
	MessageBox(_T("Thank you for signing in!"));

	// Reset everything
	idText = "";

	purposeCombo->SetCurSel(0);
	int index = purposeCombo->GetCurSel();
	purposeCombo->GetLBText(index, purposeText);

	eIDEdit->SetDlgItemTextW(0, _T(""));
	eIDEdit->SetSel(0, 7);
	eIDEdit->Clear();

}


void CTLCSignInDlg::OnEnChangeIDEdit()
{
	using namespace std;
	LPTSTR editText;
	string text;

	short i;

	int nLineCount = eIDEdit->GetLineCount();
	CString strText, strLine;

	editText = _T("");

	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	int len = eIDEdit->LineLength(eIDEdit->LineIndex(0));
	eIDEdit->GetLine(0, strText.GetBuffer(len), len);
	strText.ReleaseBuffer(len);

	text = "e1234567";

	for (i = 0; i < 8; i++) // string copying isn't working for some reason
	{
		if (strText[i] == '\0')
		{
			text[i] = '\0';
			break;
		}
		text[i] = (char)strText[i];
	}

	if (text.length() > 8)
		text = text.substr(0, 8);

	idText = text.c_str();

	validID = true;


	if (idText.GetLength() < 7) // Not a valid ID
	{
		validID = false;
		signinButton->EnableWindow(FALSE);
		return;
	}

	// Check to see if this is a valid user ID: TODO
	if (!isalpha(idText[0])) // Definitely not a valid ID
	{
		validID = false;
		signinButton->EnableWindow(FALSE);
		return;
	}
		
	else
	{
		if (!isalpha(idText[1])) // check for employee ID
		{
			if (idText[0] == 'e') // possibly using employee ID
			{
				for (i = 1; i < 8; i++) // check that the rest of the characters are numbers
					if (!isdigit(idText[i]))
					{
						validID = false;
						signinButton->EnableWindow(FALSE);
						return;
					}
					else
						validID = true;
			}
		}

		else  // Check for 3x4 id
		{
			if (!isalpha(idText[0]) || !isalpha(idText[1]) || !isalpha(idText[2]))
			{
				validID = false;
				signinButton->EnableWindow(FALSE);
				return;
			}
			else if (!isdigit(idText[3]) || !isdigit(idText[4]) || !isdigit(idText[5]) || !isdigit(idText[6]))
			{
				validID = false;
				signinButton->EnableWindow(FALSE);
				return;
			}
			else if (idText[7] != ' ' && idText[7] != '\0')
			{
				validID = false;
				signinButton->EnableWindow(FALSE);
				return;
			}
			else
				validID = true;
		}
	}
		
	if (validID == true && validReason == true) // Both a valid ID and a valid reason are entered, enable the button
		signinButton->EnableWindow(TRUE);
	return;
}


void CTLCSignInDlg::OnCbnSelchangePurposeCombo()
{
	// TODO: Add your control notification handler code here
	purposeText = "";

	int index = purposeCombo->GetCurSel();

	purposeCombo->GetLBText(index, purposeText);

	if (purposeText != "")
		validReason = true;
	else
	{
		validReason = false;
		signinButton->EnableWindow(FALSE);
		return;
	}

	if (validID == true && validReason == true) // Both a valid ID and a valid reason are entered, enable the button
		signinButton->EnableWindow(TRUE);

	return;

}
