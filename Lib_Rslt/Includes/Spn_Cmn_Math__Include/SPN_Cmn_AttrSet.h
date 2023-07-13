// SPN_Cmn_AttrSet.h: interface for the CSPN_Cmn_AttrSet class.
//
//////////////////////////////////////////////////////////////////////

#ifndef SPN_Cmn_AttrSet_H__INCLUDED_
#define SPN_Cmn_AttrSet_H__INCLUDED_
#pragma once

#include "SPN_Cmn_Math_Base.h"

#include <string>
#include <vector>
#include <list>
#include <map> //Key --> Value
#include <stdio.h> //Key --> Value
#include <iostream> //Key --> Value

//

const int C_nChar_MaxLeng_StrAttr = 56;
union SPN_CMN_MATH_EXPORT USPN_Cmn_AttrVal
{
	char    m_str[C_nChar_MaxLeng_StrAttr];
	BYTE	m_vByte;
	char	m_vChar;
	short	m_vShort;
	ushort  m_vUShort;
	int		m_vInt;
	uint    m_vUInt;
	float	m_vFloat;
	double  m_vDouble;
};
//
//void Test()
//{
//	::USPN_Cmn_AttrVal uAttr;
//	uAttr.m_vFloat = float();
//	uAttr.m_vFloat = 3.f;//();
//
//	float fTmp = uAttr.m_vFloat;
//	assert(FLT_EQ(3.f, uAttr.m_vFloat));
//
//	::USPN_Cmn_AttrVal uAttr;
//	uAttr.m_vChar = 'A';
//
//	::USPN_Cmn_AttrVal uAttr3;
//	char sTmp[C_nChar_MaxLeng_StrAttr] = "rrrrrrrrrrrrrtttttttttttttt";
//	memcpy(uAttr3.m_str, sTmp, sizeof(sTmp));//?????
//	//{
//	//	double pBuf[::C_nChar_MaxLeng_StrAttr];
//	//	::memset(pBuf, 'a', ::C_nChar_MaxLeng_StrAttrsizeof(pBuf[]));
//	//}
//
//	uAttr.m_vFloat = float();
//}

//-------------------------------------------------------------------------------------
struct SPN_CMN_MATH_EXPORT SSPN_Cmn_Attr
{
public:
	std::string		m_StrAttrName;
	USPN_Cmn_AttrVal	m_uAttrVal;

public:
	SSPN_Cmn_Attr();

	SSPN_Cmn_Attr(const SSPN_Cmn_Attr& sAttr);

	~SSPN_Cmn_Attr();
	
	const SSPN_Cmn_Attr& operator=(const SSPN_Cmn_Attr& sAttr);
};
//-------------------------------------------------------------------------------------
class SPN_CMN_MATH_EXPORT CSPN_Cmn_AttrSet
{
public:
	using MyMapTP = std::map<std::string, SSPN_Cmn_Attr>;

public:
	CSPN_Cmn_AttrSet();
	~CSPN_Cmn_AttrSet();

public:
	void Swap(CSPN_Cmn_AttrSet& rAttrSet)
	{
		m_Map_AttrSet_StrName_to_Val.swap(rAttrSet.m_Map_AttrSet_StrName_to_Val);

		//MyMapTP MapTmp;
		//MapTmp = m_Map_AttrSet_StrName_to_Val;
		//m_Map_AttrSet_StrName_to_Val = rAttrSet.m_Map_AttrSet_StrName_to_Val;

		//Exchange(m_Map_AttrSet_StrName_to_Val, m_Map_AttrSet_StrName_to_Val);
	};

public:
	bool Add_Attr(std::string StrAttrName, USPN_Cmn_AttrVal uAttrVal);
	bool Del_Attr(USPN_Cmn_AttrVal& ruAttrVal, std::string StrAttrName);

	bool Set_AttrVal(std::string StrAttrName, USPN_Cmn_AttrVal uAttrVal);
	bool Get_AttrVal(std::string StrAttrName, USPN_Cmn_AttrVal& ruAttrVal) const;

	USPN_Cmn_AttrVal* Get_AttrVal_Ref(std::string StrAttrName);

	bool IsHas_Attr(std::string StrAttrName) const;

public:
	bool WriteStream(std::fstream& FStream) const;
	bool ReadStream (std::fstream& FStream);

	//Implementations:
protected:
	MyMapTP m_Map_AttrSet_StrName_to_Val;
};

//void TestMap()
//{
//	using MpTp = CSPN_Cmn_AttrSet::MyMapTP;
//	MpTp MapTmp;
//	for (MpTp::iterator it = MapTmp.begin(); it != MapTmp.end(); it++)
//	{
//		std::cout 
//			<< "MapTmp[" 
//			<< it->first << "]="
//			<< it->second << "\n";
//	}
//}

//
#endif //  // !defined(SPN_Cmn_AttrSet_H__INCLUDED_
