// Signin_Records.h : Declaration of the CSignin_Records

#pragma once

// code generated on Monday, March 07, 2016, 3:54 PM

class CSignin_Records : public CRecordset
{
public:
	CSignin_Records(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSignin_Records)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	CStringW	m_EmployeeID;
	CTime	m_Signin_Date;
	CStringW	m_Purpose;

// Overrides
	// Wizard generated virtual function overrides
	public:
	virtual CString GetDefaultConnect();	// Default connection string

	virtual CString GetDefaultSQL(); 	// default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


