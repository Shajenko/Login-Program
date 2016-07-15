// Signin_Records.h : Implementation of the CSignin_Records class



// CSignin_Records implementation

// code generated on Monday, March 07, 2016, 3:54 PM

#include "stdafx.h"
#include "Signin_Records.h"
IMPLEMENT_DYNAMIC(CSignin_Records, CRecordset)

CSignin_Records::CSignin_Records(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_EmployeeID = L"";
	m_Signin_Date;
	m_Purpose = L"";
	m_nFields = 3;
	m_nDefaultType = dynaset;
}
//#error Security Issue: The connection string may contain a password
// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString CSignin_Records::GetDefaultConnect()
{
	return _T("DBQ=C:\\Users\\tas3409\\Documents\\Visual Studio 2013\\Projects\\TLCSignIn\\TLCSignin.accdb;DefaultDir=C:\\Users\\tas3409\\Documents\\Visual Studio 2013\\Projects\\TLCSignIn;Driver={Microsoft Access Driver (*.mdb, *.accdb)};DriverId=25;FIL=MS Access;FILEDSN=C:\\Users\\tas3409\\Documents\\Visual Studio 2013\\Projects\\TLCSignIn\\TLC Sign In.dsn;MaxBufferSize=2048;MaxScanRows=8;PageTimeout=5;SafeTransactions=0;Threads=3;UID=admin;UserCommitSync=Yes;");
}

CString CSignin_Records::GetDefaultSQL()
{
	return _T("[Signin_Records]");
}

void CSignin_Records::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Text(pFX, _T("[EmployeeID]"), m_EmployeeID);
	RFX_Date(pFX, _T("[Sign-in_Date]"), m_Signin_Date);
	RFX_Text(pFX, _T("[Purpose]"), m_Purpose);

}
/////////////////////////////////////////////////////////////////////////////
// CSignin_Records diagnostics

#ifdef _DEBUG
void CSignin_Records::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSignin_Records::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


