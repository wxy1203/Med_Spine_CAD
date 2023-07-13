
#include "pch.h"
#include "SPN_Cmn_WString.h"

#ifdef _MSC_VER
	#include "stringapiset.h"
#else
	//
#endif // 

#ifdef _MSC_VER
const char CODE_SET_HZ[] = "GB2312";
#else
const char CODE_SET_HZ[] = "UTF-8";
#endif


//{{---------boost用b2编译, 未按CXX11_ABI生产新的string/lst接口, 所以暂时关闭:
//#ifdef _GLIBCXX_USE_CXX11_ABI
//#	undef _GLIBCXX_USE_CXX11_ABI
//#endif // 

#define _GLIBCXX_USE_CXX11_ABI 1
#include <boost/locale/conversion.hpp>
#include <boost/locale/encoding.hpp>
//#define _GLIBCXX_USE_CXX11_ABI 1 // **********打开

//#	pragma message("_GLIBCXX_USE_CXX11_ABI == ?A*********************************************:")
//#if (_GLIBCXX_USE_CXX11_ABI == 0)
//#	pragma message("_GLIBCXX_USE_CXX11_ABI == 0")
//#else
//#	pragma message("_GLIBCXX_USE_CXX11_ABI == 1")
//#endif // 
//#	pragma message("_GLIBCXX_USE_CXX11_ABI == ?A*********************************************!")
//}}---------boost用b2编译, 未按CXX11_ABI生产新的string/lst接口, 所以暂时关闭!

#include <iostream> 

//**************************************************************
#ifdef _DEBUG
#	ifdef _USE_VC_DBG_NEW
#		define new DEBUG_NEW
#	else
#		ifdef _USE_HPG_DBG_NEW
#			define new _DEBUG_NEW
//#			define delete _DEBUG_DEL
#		endif
#	endif
#endif // 


#ifdef _MSC_VER
wchar_t* old_SPN_String_ToFr__MByteToWChar(const char* lpcszStr)
{
	// Get the required size of the buffer that receives the Unicode
	// string.
	if (lpcszStr == NULL)
		return NULL;

	UINT dwMinSize;
	dwMinSize = MultiByteToWideChar(CP_ACP, 0, lpcszStr, -1, NULL, 0);

	wchar_t* lpWStr = new wchar_t[dwMinSize];
	if (!lpWStr)
	{
		//delete[] lpWStr;
		return NULL;
	}

	// Convert headers from ASCII to Unicode.
	MultiByteToWideChar(CP_ACP, 0, lpcszStr, -1, lpWStr, dwMinSize);
	return lpWStr;
};
char* old_SPN_String_ToFr__WCharToMByte(const wchar_t* lpcwszStr)
{
	if (lpcwszStr == NULL)
		return NULL;

	DWORD dwMinSize;
	dwMinSize = WideCharToMultiByte(CP_OEMCP, NULL, lpcwszStr, -1, NULL, 0, NULL, FALSE);

	char* lpStr = new char[dwMinSize];
	if (!lpStr)
	{
		//[2019_12_10 22:04:22 HanJun]: delete[] lpStr;
		return NULL;
	}
	WideCharToMultiByte(CP_OEMCP, NULL, lpcwszStr, -1, lpStr, dwMinSize, NULL, FALSE);
	return lpStr;
};
#endif // 
//**************************************************************

//**************************************************************
//#include <boost/locale/conversion.hpp>
//#include <boost/locale/encoding.hpp>
//
//#include <iostream> 
//void test()
//{
//	std::string source = "BIG5字符串";
//	std::string s = boost::locale::conv::between(source, "UTF-8", "BIG5");
//}

const wchar_t* SPN_String_ToFr::MByteToWChar(const char* lpcszStr)
{
	if (lpcszStr == NULL)
		return NULL;

	std::string StrSrc(lpcszStr);
	//std::wstring WStrDst = boost::locale::conv::to_utf<wchar_t>(StrSrc.c_str(), StrSrc.c_str() + StrSrc.size(), CODE_SET_HZ, boost::locale::conv::default_method);
	//
	//if (m_lpWStr)
	//{
	//	delete[]m_lpWStr;
	//}
	//
	//int nCW_W = WStrDst.size();
	//int nC_W = WStrDst._Memcpy_move_size
	//m_lpWStr = new wchar_t[nC_W];
	//::memcpy(m_lpWStr, WStrDst.c_str(), WStrDst.size());
	//
	//return m_lpWStr;
	//[2020_10_9 14:43:59 HanJun]:-->
#pragma message("_GLIBCXX_USE_CXX11_ABI == ?B*********************************************:")

#if (_GLIBCXX_USE_CXX11_ABI == 0)
#	pragma message("_GLIBCXX_USE_CXX11_ABI == 0")
#else
#	pragma message("_GLIBCXX_USE_CXX11_ABI == 1")
//#	define _GLIBCXX_USE_CXX11_ABI 0
//#	if (_GLIBCXX_USE_CXX11_ABI == 0)
//#		pragma message("afterChgDefine: _GLIBCXX_USE_CXX11_ABI == 0")
//#	else
//#		pragma message("afterChgDefine: _GLIBCXX_USE_CXX11_ABI == 1")
//#	endif
#endif // 

#pragma message("_GLIBCXX_USE_CXX11_ABI == ?B*********************************************!")

	m_WStr = boost::locale::conv::to_utf<wchar_t>(StrSrc.c_str(), StrSrc.c_str() + StrSrc.size(),
												  CODE_SET_HZ, boost::locale::conv::default_method);
	return m_WStr.c_str();

#pragma message("_GLIBCXX_USE_CXX11_ABI == ?C*********************************************:")
#if (_GLIBCXX_USE_CXX11_ABI == 0)
#	pragma message("_GLIBCXX_USE_CXX11_ABI == 0")
#else
#	pragma message("_GLIBCXX_USE_CXX11_ABI == 1")
#endif // 
#pragma message("_GLIBCXX_USE_CXX11_ABI == ?C*********************************************!")

};


const char* SPN_String_ToFr::WCharToMByte(const wchar_t* lpcwszStr)
{
	if (lpcwszStr == NULL)
		return NULL;

	std::wstring WStrSrc(lpcwszStr);
	//BOOST_LOCALE_DECL std::basic_string<wchar_t> to_utf(char const *begin, char const *end, std::string const &charset, method_type how);

	//std::string StrDst = boost::locale::conv::from_utf<wchar_t>(WStrSrc.c_str(), WStrSrc.c_str() + WStrSrc.size(), CODE_SET_HZ, boost::locale::conv::default_method);
	//
	//if (m_lpStr)
	//{
	//	delete []m_lpStr;
	//}
	//m_lpStr = new char[StrDst.size()];
	//::memcpy(m_lpStr, StrDst.c_str(), StrDst.size());
	//
	//return m_lpStr;
	//[2020_10_9 14:42:50 HanJun]:-->
	m_Str = boost::locale::conv::from_utf<wchar_t>(WStrSrc.c_str(), WStrSrc.c_str() + WStrSrc.size(), 
		CODE_SET_HZ, boost::locale::conv::default_method);

	return m_Str.c_str();
};

//**************************************************************
#ifdef _HPG_ENABLE_AUTO_UNIT_TEST_
class AutoTest_SPN_String_ToFr
{
public:
	AutoTest_SPN_String_ToFr()
	{
		TestUnit();
	}

	void TestUnit()
	{
		SPN_String_ToFr HWStrToFr;
		std::string StrSrc("I'm Chinese, 我是中国人\0");
		std::wstring StrDstW_new = HWStrToFr.MByteToWChar		(StrSrc.c_str());
		std::wstring StrDstW_old = old_SPN_String_ToFr__MByteToWChar	(StrSrc.c_str());
		assert(StrDstW_old == StrDstW_new);

		std::string StrDst_new = HWStrToFr.WCharToMByte		(StrDstW_new.c_str());
		std::string StrDst_old = old_SPN_String_ToFr__WCharToMByte	(StrDstW_new.c_str());
		assert(StrDst_old == StrDst_new);
	}
};

AutoTest_SPN_String_ToFr UT_SPN_String_ToFr;
#endif //  //_HPG_ENABLE_AUTO_UNIT_TEST_
//**************************************************************
