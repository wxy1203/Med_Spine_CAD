
#ifndef SPN_Cmn_Math_Base__h__included__
#define SPN_Cmn_Math_Base__h__included__



#include "math.h"
#include "limits.h"
#include "assert.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "windows.h"

//typedef unsigned short ushort;
using BYTE = unsigned char;
using ushort = unsigned short;
using uint = unsigned int;

//using BOOL = bool;
#define BYTE_MIN      ()                  // min binary exponent
#define BYTE_MAX      (55)                  // min binary exponent

enum E_CMN_MATH__InnerType
{
	E_CMN_MATH__InnerType_NULL = INT_MAX,

	E_CMN_MATH__InnerType_BYTE = 0,
	E_CMN_MATH__InnerType_Char,
	E_CMN_MATH__InnerType_Short,	//==
	E_CMN_MATH__InnerType_UShort,	//...
	E_CMN_MATH__InnerType_Int,
	E_CMN_MATH__InnerType_UInt,
	E_CMN_MATH__InnerType_Float,
	E_CMN_MATH__InnerType_Double,
};

template<typename TP>
E_CMN_MATH__InnerType GetID_InnerDataType()
{
	return E_CMN_MATH__InnerType_NULL;
}


 template<>inline E_CMN_MATH__InnerType GetID_InnerDataType<BYTE>()		{ return E_CMN_MATH__InnerType_BYTE; };
 template<>inline E_CMN_MATH__InnerType GetID_InnerDataType<char>()		{ return E_CMN_MATH__InnerType_Char; };
//template<> E_CMN_MATH__InnerType GetID_InnerDataType<short>()	{ return E_CMN_MATH__InnerType_NULL; };
//template<> E_CMN_MATH__InnerType GetID_InnerDataType<ushort>() { return E_CMN_MATH__InnerType_NULL; };
 template<>inline E_CMN_MATH__InnerType GetID_InnerDataType<int>()		{ return E_CMN_MATH__InnerType_Int; };
//template<> E_CMN_MATH__InnerType GetID_InnerDataType<int>() { return E_CMN_MATH__InnerType_NULL; };
//template<> E_CMN_MATH__InnerType GetID_InnerDataType<int>() { return E_CMN_MATH__InnerType_NULL; };
//template<> E_CMN_MATH__InnerType GetID_InnerDataType<int>() { return E_CMN_MATH__InnerType_NULL; };
//template<> E_CMN_MATH__InnerType GetID_InnerDataType<int>() { return E_CMN_MATH__InnerType_NULL; };
//template<> E_CMN_MATH__InnerType GetID_InnerDataType<int>() { return E_CMN_MATH__InnerType_NULL; };
//template<> E_CMN_MATH__InnerType GetID_InnerDataType<int>() { return E_CMN_MATH__InnerType_NULL; };
//template<> E_CMN_MATH__InnerType GetID_InnerDataType<int>() { return E_CMN_MATH__InnerType_NULL; };
//template<> E_CMN_MATH__InnerType GetID_InnerDataType<int>() { return E_CMN_MATH__InnerType_NULL; };
//template<> E_CMN_MATH__InnerType GetID_InnerDataType<int>() { return E_CMN_MATH__InnerType_NULL; };

template<typename TP>
inline void Exchange(TP& v1, TP& v2)
{
	TP vTmp = v1;
	v1 = v2;
	v2 = vTmp;
};

#define _EXCHANGE(TP, v1, v2) \
{ \
	TP vTmp = v1; \
	v1 = v2; \
	v2 = vTmp; \
}

inline void Test()
{
	int iA = 1;
	int iB = 2;
	_EXCHANGE(int,iA, iB); 
	Exchange(iA,iB);
}
//
//template<typename TP>
//inline void Exchange(TP pV, TP pV)
//{
//	TP vTmp = pV;
//	pV = pV;
//	pV = vTmp;
//};
//
//void TestPtr( int ppV)
//{
//	ppV = new int[];
//
//	int a = 5;
//
//	int& ra = a;
//	assert(&a == &ra);
//
//	ra = 8;
//    assert(8 == a);
//	//--------------------------------
//	int pa = &a;
//
//	pa = 9;
//	assert(9 == a);
//
//	//-----------------------------------
//	int& rA = a;
//}
//
//void TestPtr( int& rpV)
//{
//	rpV = new int[];
//}

#endif // !SPN_Cmn_Math_Base__h__included__
