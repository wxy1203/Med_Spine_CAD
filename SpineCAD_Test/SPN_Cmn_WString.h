#ifndef SPN_Cmn_WString_H__INCLUDED_
#define	SPN_Cmn_WString_H__INCLUDED_

#	pragma once


////-------------------------------------------------------------------------------------
////Description:
//// This function maps a character string to a wide-character (Unicode) string
////
////Parameters:
//// lpcszStr: [in] Pointer to the character string to be converted
//// lpwszStr: [out] Pointer to a buffer that receives the translated string.
//// dwSize: [in] Size of the buffer
////
////Return Values:
//// TRUE: Succeed
//// FALSE: Failed
////
////Example:
//// MByteToWChar(szA,szW,sizeof(szW)/sizeof(szW[0]));
////---------------------------------------------------------------------------------------
//BOOL MByteToWChar(char* lpcszStr, wchar_t* lpwszStr, DWORD dwSize)
//{
//	// Get the required size of the buffer that receives the Unicode
//	// string.
//	DWORD dwMinSize;
//	dwMinSize = MultiByteToWideChar(CP_ACP, 0, lpcszStr, -1, NULL, 0);
//
//	if (dwSize < dwMinSize)
//	{
//		return FALSE;
//	}
//	// Convert headers from ASCII to Unicode.
//	MultiByteToWideChar(CP_ACP, 0, lpcszStr, -1, lpwszStr, dwMinSize);
//	return TRUE;
//}
//
////-------------------------------------------------------------------------------------
////Description:
//// This function maps a wide-character string to a new character string
////
////Parameters:
//// lpcwszStr: [in] Pointer to the character string to be converted
//// lpszStr: [out] Pointer to a buffer that receives the translated string.
//// dwSize: [in] Size of the buffer
////
////Return Values:
//// TRUE: Succeed
//// FALSE: Failed
////
////Example:
//// MByteToWChar(szW,szA,sizeof(szA)/sizeof(szA[0]));
////---------------------------------------------------------------------------------------
//BOOL WCharToMByte(wchar_t* lpcwszStr, char* lpszStr, DWORD dwSize)
//{
//	DWORD dwMinSize;
//	dwMinSize = WideCharToMultiByte(CP_OEMCP, NULL, lpcwszStr, -1, NULL, 0, NULL, FALSE);
//	if (dwSize < dwMinSize)
//	{
//		return FALSE;
//	}
//	WideCharToMultiByte(CP_OEMCP, NULL, lpcwszStr, -1, lpszStr, dwSize, NULL, FALSE);
//	return TRUE;
//}
////使用方法也很简单, 示例如下:
////wchar_t wText[10] = { L"函数示例" };
////char sText[20] = { 0 };
////WCharToMByte(wText, sText, sizeof(sText) / sizeof(sText[0]));
////MByteToWChar(sText, wText, sizeof(wText) / sizeof(wText[0]));
//
//
//这两个函数的缺点在于无法动态分配内存，在转换很长的字符串时可能会浪费较多内存空间；
// 优点是在不考虑浪费空间的情况下转换较短字符串非常方便。
//为了解决不能动态分配内存的问题，重新定义如下：
class  SPN_String_ToFr
{
public:
	SPN_String_ToFr(){};
	virtual ~SPN_String_ToFr()
	{
		ReleaseMem();
	}

public:
	const wchar_t*	MByteToWChar(const char* lpcszStr);
	const char*		WCharToMByte(const wchar_t* lpcwszStr);

	inline void ReleaseMem()
	{
		//[2020_10_9 14:41:10 HanJun]:
		//if (m_lpStr)
		//{
		//	delete[] m_lpStr;
		//	m_lpStr = nullptr;
		//}
		//if (m_lpWStr)
		//{
		//	delete[] m_lpWStr;
		//	m_lpWStr = nullptr;
		//}
	};

protected:
	//char*		m_lpStr = nullptr;
	//wchar_t*	m_lpWStr = nullptr;
	//[2020_10_9 14:41:19 HanJun]: -->
	std::string m_Str;
	std::wstring m_WStr;
};

//*************************************************************************
inline std::string WStr_stdWStr_to_StdStr(std::wstring wStr)
{
	std::string Str;
	{
		SPN_String_ToFr WStrToFr;
		const char* lpStr = WStrToFr.WCharToMByte(wStr.c_str());
		Str = std::string(lpStr);
	}
	return Str;
};
inline void WStr_stdWStr_to_StdStr(std::string& Str, const std::wstring& wStr) // 性能版本
{
	SPN_String_ToFr WStrToFr;
	const char* lpStr = WStrToFr.WCharToMByte(wStr.c_str());
	Str = std::string(lpStr);
};
//-----------------------------------------------------------------

inline std::wstring WStr_StdStr_to_stdWStr(std::string stdStr)
{
	std::wstring wStr;
	{
		SPN_String_ToFr WStrToFr;
		const wchar_t* lpwStr = WStrToFr.MByteToWChar(stdStr.c_str());
		wStr = std::wstring(lpwStr);
	}
	return wStr;
};

inline void WStr_StdStr_to_stdWStr(std::wstring& wStr, const std::string& stdStr)//性能版本
{
	SPN_String_ToFr WStrToFr;
	const wchar_t* lpwStr = WStrToFr.MByteToWChar(stdStr.c_str());
	wStr = std::wstring(lpwStr);
};

//-----------------------------------------------------------------

inline std::wstring WStr_QString_to_StdWStr(QString qStr)
{
	std::wstring WStr;
	{
#ifdef _MSC_VER
		WStr = std::wstring((const wchar_t *)qStr.utf16());
#else
		WStr = qStr.toStdWString();
#endif // 
	}
	return WStr;
};
inline void WStr_QString_to_StdWStr(std::wstring& WStr, const QString& qStr) // 性能版本
{
	WStr;
	{
#ifdef _MSC_VER
		WStr = std::wstring((const wchar_t *)qStr.utf16());
#else
		WStr = qStr.toStdWString();
#endif // 
	}
};

//-----------------------------------------------------------------

inline QString WStr_stdWStr_to_QString(std::wstring stdWStr)
{
	QString qStr;
	{
#ifdef _MSC_VER
		qStr = QString::fromUtf16((const ushort *)(stdWStr.c_str()));
#else
		qStr = QString::fromStdWString(stdWStr);
#endif // 
	}
	return qStr;
};
inline void WStr_stdWStr_to_QString(QString& qStr, const std::wstring& stdWStr)//性能版本
{
	qStr;
	{
#ifdef _MSC_VER
		qStr = QString::fromUtf16((const ushort *)(stdWStr.c_str()));
#else
		qStr = QString::fromStdWString(stdWStr);
#endif // 
	}
};

//-----------------------------------------------------------------
inline std::string WStr_QString_to_StdStr(QString qStr)
{
	std::wstring WStr;
	{
		WStr_QString_to_StdWStr(qStr);
	}

	SPN_String_ToFr WStrToFr;
	const char* lpStr = WStrToFr.WCharToMByte(WStr.c_str());
	std::string Str(lpStr);
	return Str;
};
inline void WStr_QString_to_StdStr(std::string& Str, const QString& qStr)//性能版本
{
	std::wstring WStr;
	{
		WStr_QString_to_StdWStr(WStr, qStr);
	}

	SPN_String_ToFr WStrToFr;
	const char* lpStr = WStrToFr.WCharToMByte(WStr.c_str());
	Str = std::string(lpStr);
};
//-----------------------------------------------------------------

inline QString WStr_StdStr_to_QString(std::string stdStr)
{
	std::wstring WStr;
	WStr_StdStr_to_stdWStr(WStr, stdStr);
	QString qStr = WStr_stdWStr_to_QString(WStr);
	return qStr;
};
inline void WStr_StdStr_to_QString(QString& qStr, const std::string& stdStr) //性能版本
{
	std::wstring WStr;
	WStr_StdStr_to_stdWStr(WStr, stdStr);
	WStr_stdWStr_to_QString(qStr, WStr);
};
//-----------------------------------------------------------------

//*************************************************************************

template<int TMP_TP = 0>
class SPN_String_T : public std::wstring
{
public:
	SPN_String_T()	{};
	virtual ~SPN_String_T()	{};

	SPN_String_T(const std::wstring& Str)
	{
		(*(std::wstring*)this) = Str;
	};
	SPN_String_T(const std::string& Str)
	{
		SPN_String_ToFr StrToFr;
		*this = StrToFr.MByteToWChar(Str.c_str());
		//[2020_5_29 11:22:52 HanJun]:*this = QString(Str.c_str());
	};
	SPN_String_T(const QString& qStr)
	{
		Set_QString(qStr);
	};
	SPN_String_T(const char* pChBuf)
	{
		Set_QString(QString(pChBuf));
	};
	SPN_String_T(const wchar_t* pWChBuf)
		: std::wstring(pWChBuf)
	{
		//SPN_String_ToFr WStrToFr;
		//char* lpStr = WStrToFr.WCharToMByte(pWChBuf);
		//Set_QString(QString(lpStr));
	};
	//--------------------------------------------------------

	inline void Set_QString(const QString& qStr)
	{
#ifdef _MSC_VER
		*this = std::wstring((const wchar_t *)qStr.utf16());
#else
		*this = qStr.toStdWString();
#endif // 
	};

	//--------------------------------------------------------
	inline QString Get_QString() const
	{
#ifdef _MSC_VER
		return QString::fromUtf16((const ushort *)(this->c_str()));
#else
		return QString::fromStdWString(*this);
#endif // 
	};
	inline void Get_QString(QString& qStr) const
	{
#ifdef _MSC_VER
		qStr = QString::fromUtf16((const ushort *)(this->c_str()));
#else
		qStr = QString::fromStdWString(*this);
#endif // 
	};
	//--------------------------------------------------------
	inline QString To_QString() const
	{
		return Get_QString();
	};

	inline void To_QString(QString& qStr) const
	{
		 Get_QString(qStr);
	};
	//--------------------------------------------------------
	inline std::string To_StdString() const
	{
		SPN_String_ToFr WStrToFr;
		const char* lpStr = WStrToFr.WCharToMByte(this->c_str());
		std::string Str(lpStr);
		return Str;
	};
	inline void To_StdString(std::string& Str) const
	{
		SPN_String_ToFr WStrToFr;
		const char* lpStr = WStrToFr.WCharToMByte(this->c_str());
		Str = std::string(lpStr);
	};
	//--------------------------------------------------------

	inline const SPN_String_T& operator=(const SPN_String_T& wStr)
	{
		*(std::wstring*)(this) = wStr;
		return *this;
	};

	inline const SPN_String_T& operator+=(const SPN_String_T& wStr)
	{
		*(std::wstring*)(this) += wStr;
		return *this;
	};
	//inline const SPN_String& operator=(QString qStr)
	//{
	//	Set_QString(qStr);
	//};
	
	inline SPN_String_T<> Left(int nCh) const
	{
		SPN_String_T<> HStr = this->substr(0, nCh);
		return HStr;
	}
	inline SPN_String_T<> Right(int nCh) const
	{
		int nSz = this->size();

		int iBgn = std::max<int>(0, nSz - nCh);
		SPN_String_T<> HStr = this->substr(iBgn, nCh);
		return HStr;
	}
};

typedef SPN_String_T<> SPN_String;

template<int N>
SPN_String_T<N> operator+(SPN_String_T<N> wStrA, SPN_String_T<N> wStrB)
{
	SPN_String_T<N> wStr = wStrA;
	wStr += wStrB;
	return wStr;
};

#endif //  // !defined(SPN_Cmn_WString_H__INCLUDED_
