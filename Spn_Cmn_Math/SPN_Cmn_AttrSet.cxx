// SPN_Cmn_AttrSet.cpp: implementation of the CSPN_Cmn_AttrSet class.
//
//////////////////////////////////////////////////////////////////////


#include "pch.h"
#include "_SPN_Cmn_Math__inLib.h"
//#include "_SPN_Cmn_Math__inLib.h"

#include <fstream>

//
#ifdef _DEBUG
#	ifdef _USE_VC_DBG_NEW
#		define new DEBUG_NEW
#	else
#		ifdef _USE_SPN_DBG_NEW
#			define new _DEBUG_NEW
//#			define delete _DEBUG_DEL
#		endif
#	endif
#endif // 
//

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//typedef std::map<std::string, SSPN_Cmn_Attr> MyMapTP;

CSPN_Cmn_AttrSet::CSPN_Cmn_AttrSet()
{
}

CSPN_Cmn_AttrSet::~CSPN_Cmn_AttrSet()
{
}


SSPN_Cmn_Attr::SSPN_Cmn_Attr()
{
	//m_StrAttrName;
	m_uAttrVal.m_vDouble = 0;
}

SSPN_Cmn_Attr::SSPN_Cmn_Attr(const SSPN_Cmn_Attr& sAttr)
{
	*this = sAttr;
};

SSPN_Cmn_Attr::~SSPN_Cmn_Attr()
{
}

const SSPN_Cmn_Attr& SSPN_Cmn_Attr::operator=(const SSPN_Cmn_Attr& sAttr)
{
	m_StrAttrName = sAttr.m_StrAttrName;
	m_uAttrVal = sAttr.m_uAttrVal;
	return *this;
};



bool CSPN_Cmn_AttrSet::Add_Attr(std::string StrAttrName, USPN_Cmn_AttrVal uAttrVal)
{
	SSPN_Cmn_Attr& sAttr = m_Map_AttrSet_StrName_to_Val[StrAttrName];//
	sAttr.m_StrAttrName = StrAttrName;
	sAttr.m_uAttrVal = uAttrVal;
	return true;
}

bool CSPN_Cmn_AttrSet::Del_Attr(USPN_Cmn_AttrVal& ruAttrVal, std::string StrAttrName)
{
	if (m_Map_AttrSet_StrName_to_Val.find(StrAttrName) != m_Map_AttrSet_StrName_to_Val.end())
	{
		this->m_Map_AttrSet_StrName_to_Val.erase(StrAttrName);
		return true;
	}
	else
	{
		return false;
	}
}

bool CSPN_Cmn_AttrSet::Set_AttrVal(std::string StrAttrName, USPN_Cmn_AttrVal uAttrVal)
{
	MyMapTP::iterator it = m_Map_AttrSet_StrName_to_Val.find(StrAttrName);
	if (it != m_Map_AttrSet_StrName_to_Val.end())
	{
		it->second.m_uAttrVal = uAttrVal;
		return true;
	}
	else
	{
		return false;
	}
}

bool CSPN_Cmn_AttrSet::Get_AttrVal(std::string StrAttrName, USPN_Cmn_AttrVal& ruAttrVal) const
{
	MyMapTP::const_iterator it = m_Map_AttrSet_StrName_to_Val.find(StrAttrName);
	if (it != m_Map_AttrSet_StrName_to_Val.cend())
	{
		ruAttrVal = it->second.m_uAttrVal;
		return true;
	}
	else
	{
		return false;
	}
}

USPN_Cmn_AttrVal* CSPN_Cmn_AttrSet::Get_AttrVal_Ref(std::string StrAttrName)
{
	MyMapTP::iterator it = m_Map_AttrSet_StrName_to_Val.find(StrAttrName);
	if (it != m_Map_AttrSet_StrName_to_Val.end())
	{
		return &(it->second.m_uAttrVal);
	}
	else
	{
		return nullptr;
	}
}

bool CSPN_Cmn_AttrSet::IsHas_Attr(std::string StrAttrName) const
{
	bool bFind = (m_Map_AttrSet_StrName_to_Val.find(StrAttrName) != m_Map_AttrSet_StrName_to_Val.end());
	return bFind;
}

bool CSPN_Cmn_AttrSet::WriteStream(std::fstream& FStream) const
{
	int iVer = 0;
	FStream.write((char*)(&iVer), sizeof(iVer));

	int nAttr = m_Map_AttrSet_StrName_to_Val.size();
	FStream.write((char*)(&nAttr), sizeof(nAttr));

	for (MyMapTP::const_iterator it = m_Map_AttrSet_StrName_to_Val.begin();
		 it != m_Map_AttrSet_StrName_to_Val.cend();
		 it++)
	{
		const SSPN_Cmn_Attr& sAttr = it->second;

		int nSzName = sAttr.m_StrAttrName.size();
		FStream.write((char*)(&nSzName), sizeof(nSzName));
		FStream.write((char*)(sAttr.m_StrAttrName.c_str()), nSzName);

		FStream.write((char*)(&sAttr.m_uAttrVal), sizeof(sAttr.m_uAttrVal));
	}
	return true;
}

bool CSPN_Cmn_AttrSet::ReadStream(std::fstream& FStream)
{
	int iVer = 1;
	FStream.read((char*)(&iVer), sizeof(iVer));

	bool bOK = false;
	switch (iVer)
	{
	case 1:
	{
		int nAttr = 1;
		FStream.read((char*)(&nAttr), sizeof(nAttr));

		for (int i=0; i<nAttr; i++)
		{
			SSPN_Cmn_Attr sAttr;

			int nSzName = 0;
			FStream.read((char*)(&nSzName), sizeof(nSzName));
			sAttr.m_StrAttrName.resize(nSzName);
			FStream.read((char*)(sAttr.m_StrAttrName.c_str()), nSzName);

			FStream.read((char*)(&sAttr.m_uAttrVal), sizeof(sAttr.m_uAttrVal));
		}
		bOK = true;
	}
	break;
	default:
		bOK = false;
		assert(false);
		;//::ShowMsg (/_T/("遇到无法识别的CSPN_Cmn_3DMtx_Grid对象版本!!!"));
	}

	return bOK;
}
