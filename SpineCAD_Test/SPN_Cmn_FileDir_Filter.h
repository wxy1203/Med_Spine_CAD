
#ifndef __Include__SPN_Cmn_FileDir_Filter__H__
#define __Include__SPN_Cmn_FileDir_Filter__H__

#include "SPN_Cmn_WString.h"

#include <string>

class QStringList;

class  CSPN_Cmn_FileDir_Filter
{
public:
	CSPN_Cmn_FileDir_Filter();
	virtual ~CSPN_Cmn_FileDir_Filter();

public:
	static void GetVctString_fr_StringList(std::vector<SPN_String>& ArrStrFPath_Dst, const QStringList& LstStrFPath);

public:
	static bool GetAllPath_Folders_inDir(QStringList& FolderList, QString DirPath, bool bRecursive, bool bIncludeTopDir = false);
	static bool GetAllPath_Folders_inDir(std::vector<std::string>& ArrFolder, QString DirPath, bool bRecursive, bool bIncludeTopDir = false);

	static bool GetAllPath_Files_inDir(std::vector<SPN_String>&	ArrStrFPath_Dst, const QString &FoldPath, bool bRecursive);
	static bool GetAllPath_Files_inDir(QStringList&				LstStrFPath_Dst, const QString &FoldPath, bool bRecursive);

	//把源全路径StrDirPath_FullSrc（P4）中的指定顶源顶级目录StrDirPath_TopSrc（P3），替换成目标顶级目录StrDirPath_TopDst（P2），合成新的目标全路径StrDirPath_FullDst（P1）
	static bool CopyMake_SubPath(SPN_String& StrDirPath_FullDst, 
								 SPN_String  StrDirPath_TopDst, SPN_String StrDirPath_TopSrc, SPN_String StrDirPath_FullSrc);
	static bool CopyCalc_SubPath(SPN_String& StrDirPath_FullDst, 
								 SPN_String  StrDirPath_TopDst, SPN_String StrDirPath_TopSrc, SPN_String StrDirPath_FullSrc);

	static bool _CreateFile_Txt(QString StrFilePath);
	static bool _DeleteFile(QString StrFilePath);

	static void _Validate_FileName(SPN_String& StrFileName, char cNew = '_');
	static void _Validate_FileName(QString& StrFileName, char cNew = '_');

public:
	/***********************************************************************************/
	inline static bool _Is_Slash_Head(const QString& StrPath)
	{
		return StrPath.at(0) == '/' || StrPath.at(0) == '\\';
	};
	inline static bool _Is_Slash_Head(const SPN_String& StrPath)
	{
		QString qStrTmp = StrPath.To_QString();
		return _Is_Slash_Head(qStrTmp);
	}

	//-----------------------------------------------------------------------------------
	inline static bool _Is_Slash_Tail(const QString& StrPath)
	{
		int iCTail = StrPath.size() - 1;
		return StrPath.at(iCTail) == '/' || StrPath.at(iCTail) == '\\';
	};
	inline static bool _Is_Slash_Tail(const SPN_String& StrPath)
	{
		QString qStrTmp = StrPath.To_QString();
		return _Is_Slash_Tail(qStrTmp);
	}

	//-----------------------------------------------------------------------------------
	inline static bool _Ensure_HasSlash_Tail(QString& StrPath)
	{
		if (!_Is_Slash_Tail(StrPath))
		{
			StrPath += '/';
		}
		return true;
	};
	inline static bool _Ensure_HasSlash_Tail(SPN_String& StrPath)
	{
		QString qStrTmp = StrPath.To_QString();
		bool bOK = _Ensure_HasSlash_Tail(qStrTmp);
		if (bOK)
		{
			StrPath = qStrTmp;
		}
		return bOK;
	}

	//-----------------------------------------------------------------------------------
	inline static bool _Ensure_HasSlash_Head(QString& StrPath)
	{
		if (!_Is_Slash_Head(StrPath))
		{
			StrPath.insert(0, '/');
		}
		return true;
	};
	inline static bool _Ensure_HasSlash_Head(SPN_String& StrPath)
	{
		QString qStrTmp = StrPath.To_QString();
		bool bOK = _Ensure_HasSlash_Head(qStrTmp);
		if (bOK)
		{
			StrPath = qStrTmp;
		}
		return bOK;
	}

	//-----------------------------------------------------------------------------------
	inline static bool _Ensure_NoSlash_Tail(QString& StrPath)
	{
		if (_Is_Slash_Tail(StrPath))
		{
			int iCTail = StrPath.size() - 1;
			StrPath.remove(iCTail, 1);
		}
		return true;
	};
	inline static bool _Ensure_NoSlash_Tail(SPN_String& StrPath)
	{
		QString qStrTmp = StrPath.To_QString();
		bool bOK = _Ensure_NoSlash_Tail(qStrTmp);
		if (bOK)
		{
			StrPath = qStrTmp;
		}
		return bOK;
	}
	//-----------------------------------------------------------------------------------
	inline static bool _Ensure_NoSlash_Head(QString& StrPath)
	{
		if (_Is_Slash_Head(StrPath))
		{
			StrPath.remove(0, 1);
		}
		return true;
	};
	inline static bool _Ensure_NoSlash_Head(SPN_String& StrPath)
	{
		QString qStrTmp = StrPath.To_QString();
		bool bOK = _Ensure_NoSlash_Head(qStrTmp);
		if (bOK)
		{
			StrPath = qStrTmp;
		}
		return bOK;
	}
	//-----------------------------------------------------------------------------------
	inline static bool _NormalizePath(QString& StrPath)
	{
		StrPath.replace('\\', '/');
		StrPath = StrPath.toUpper();
		return true;
	};
	inline static bool _NormalizePath(SPN_String& StrPath)
	{
		QString qStrTmp = StrPath.To_QString();
		bool bOK = _NormalizePath(qStrTmp);
		StrPath = qStrTmp;
		return bOK;
	}
	//-----------------------------------------------------------------------------------
	inline static bool _IsEq_Path(const QString& StrPathA, const QString& StrPathB)
	{
		QString qStrTmpA = StrPathA;
		QString qStrTmpB = StrPathB;
		_NormalizePath(qStrTmpA);
		_NormalizePath(qStrTmpB);
		return qStrTmpA == qStrTmpB;
	};
	inline static bool _IsEq_Path(const SPN_String& StrPathA, const SPN_String& StrPathB)
	{
		QString qStrTmpA = StrPathA.To_QString();
		QString qStrTmpB = StrPathB.To_QString();
		_NormalizePath(qStrTmpA);
		_NormalizePath(qStrTmpB);
		return qStrTmpA == qStrTmpB;
	}

	static bool _IsHas_SubDir(const SPN_String& StrDirPath);
	static bool _IsHas_File(const SPN_String& StrDirPath);

	static bool _ComposeFilePath(SPN_String& StrFPath_Dst, const SPN_String& StrFolderPath_Dst, const SPN_String& StrFileName);
	static bool _ComposeFilePath(QString& StrFPath_Dst, const QString& StrFolderPath_Dst, const QString& StrFileName);
	/***********************************************************************************/

};
//-----------------------------------------------------------------------------
#endif //  // __Include__SPN_Cmn_FileDir_Filter__H__
