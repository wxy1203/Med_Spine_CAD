
#include "pch.h"

#include "SPN_Cmn_FileDir_Filter.h"
#include "SPN_Cmn_WString.h"

#include "qdir.h"
#include <QFile>
#include <QDir>
#include <QString>
#include <QStringList>
#include <QDebug>
#include <QByteArray>
#include <QMap>
#include <QVector>

#include <fstream>
#include <iostream>
#include <string>

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
//**************************************************************

//*************************************************************************************************************
//*************************************************************************************************************


using namespace std;

//*************************************************************************************************************
CSPN_Cmn_FileDir_Filter::CSPN_Cmn_FileDir_Filter()
{
}

CSPN_Cmn_FileDir_Filter::~CSPN_Cmn_FileDir_Filter()
{
}

void CSPN_Cmn_FileDir_Filter::GetVctString_fr_StringList(std::vector<SPN_String>& ArrStrFPath_Dst, const QStringList& LstStrFPath)
{
	int nSlcFile = LstStrFPath.size();
	ArrStrFPath_Dst.resize(nSlcFile);

#pragma omp parallel for
	for (int i = 0; i < nSlcFile; i++)
	{
		std::wstring StrFNameW = WStr_QString_to_StdWStr(LstStrFPath[i]);
		ArrStrFPath_Dst[i] = StrFNameW;
	}
}

bool _Do_GetAllPath_Folders_inDir_Recursive(QStringList& FolderList, QString StrDirPath_TopSrc)
{
	if (StrDirPath_TopSrc.size() == 0)
	{
		return false;
	}

	QDir DirPa(StrDirPath_TopSrc);
	if (!DirPa.exists())
	{
		return false;
	}

	QString StrDirTop_Path = DirPa.absolutePath();
	FolderList.push_back(StrDirTop_Path);

	QStringList StrLst_Filters;
	StrLst_Filters << QString("*");

	QDirIterator DirItrt(StrDirTop_Path,
						 StrLst_Filters,
						 QDir::AllDirs | QDir::NoDotAndDotDot,
						 QDirIterator::Subdirectories);

	while (DirItrt.hasNext())
	{
		DirItrt.next();
		QFileInfo qFI = DirItrt.fileInfo();
		QString StrPath_SubDir = qFI.absoluteFilePath();

		FolderList.push_back(StrPath_SubDir);
	}
	return true;
}

bool _Do_GetAllPath_Folders_inDir_No_Recursive(QStringList& FolderList, QString StrDirPath_TopSrc)
{
	if (StrDirPath_TopSrc.size() == 0)
	{
		return false;
	}

	QDir DirPa(StrDirPath_TopSrc);
	if (!DirPa.exists())
	{
		return false;
	}

	//1.记入当前上目录：
	QString StrDirTop_Path = DirPa.absolutePath();
	FolderList.push_back(StrDirTop_Path);

	//2.收集子目录：
	QStringList StrLst_Filters;
	StrLst_Filters << QString("*");
	QFileInfoList Lst_FileInfo;
	Lst_FileInfo = DirPa.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot);

	int nSubDir = Lst_FileInfo.size();
	for (int i = 0; i < nSubDir; i++)
	{
		QFileInfo& FInf = Lst_FileInfo[i];
		if (!FInf.isDir() || !FInf.exists())
		{
			continue;
		}
		//QString StrPath_SubDir1 = FInf.absolutePath();
		QString StrPath_SubDir2 = FInf.absoluteFilePath();

		FolderList.push_back(StrPath_SubDir2);
	}

	return true;
}

bool CSPN_Cmn_FileDir_Filter::GetAllPath_Folders_inDir(QStringList& FolderList, 
														   QString StrDirPath_TopSrc,
														   bool bRecursive, 
														   bool bIncludeTopDir/* = false*/)
{
	//1.确保顶目录添加:
	if (bIncludeTopDir)
	{
		FolderList.push_back(StrDirPath_TopSrc);
	}

	//2.子目录搜索:
	bool bOK = false;
	if (bRecursive)
	{
		bOK = _Do_GetAllPath_Folders_inDir_Recursive(FolderList, StrDirPath_TopSrc);
	}
	else
	{
		bOK = _Do_GetAllPath_Folders_inDir_No_Recursive(FolderList, StrDirPath_TopSrc);
	}

	//3.避免顶目录重复:
	QDir QDir0(FolderList[0]);
	QDir QDir1(FolderList[1]);
	{
		QString qStrPathTop0 = QDir0.absolutePath();
		QString qStrPathTop1 = QDir1.absolutePath();

		qStrPathTop0 = qStrPathTop0.toUpper();
		qStrPathTop1 = qStrPathTop1.toUpper();

		if (qStrPathTop0 == qStrPathTop1)
		{
			FolderList.erase(FolderList.begin());
		}
	}

	return bOK;
}

bool CSPN_Cmn_FileDir_Filter::GetAllPath_Folders_inDir(std::vector<std::string>& ArrFolder,
														   QString DirPath, 
														   bool bRecursive, 
														   bool bIncludeTopDir/* = false*/)
{
	QStringList QStrLst_SubDir;
	{
		bool bOK = CSPN_Cmn_FileDir_Filter::GetAllPath_Folders_inDir(QStrLst_SubDir, DirPath, bRecursive, bIncludeTopDir);
		if (!bOK)
		{
			return bOK;
		}
	}

	//格式转换:
	ArrFolder.resize(QStrLst_SubDir.size());
	for (int i = 0; i < QStrLst_SubDir.size(); i++)
	{
		std::string& rStrSubDir = ArrFolder[i];
		rStrSubDir = SPN_String(QStrLst_SubDir[i]).To_StdString();
	}

	return true;
};

bool CSPN_Cmn_FileDir_Filter::GetAllPath_Files_inDir(std::vector<SPN_String>& ArrStrFPath_Dst, const QString& QStrDirPath_TopSrc, bool bRecursive)
{
	QStringList QLstStrFPath_Dst;
	bool bOK = GetAllPath_Files_inDir(QLstStrFPath_Dst, QStrDirPath_TopSrc, bRecursive);
	CSPN_Cmn_FileDir_Filter::GetVctString_fr_StringList(ArrStrFPath_Dst, QLstStrFPath_Dst);

	return bOK;
}

bool CSPN_Cmn_FileDir_Filter::GetAllPath_Files_inDir(QStringList& QLstStrFPath_Dst, const QString& QStrDirPath_TopSrc, bool bRecursive)
{
	QDir qDir(QStrDirPath_TopSrc);
	QStringList nameFilters;
	nameFilters << "*";

	assert(1);//搜索顶级目录下的文件
	{
		QStringList FileList;
		FileList = qDir.entryList(nameFilters, QDir::Files | QDir::Readable, QDir::Name);
	
		int nF = FileList.size();

//不宜并行#pragma omp parallel for
		for (int i = 0; i < nF; i++)
		{
			QString QStrFPath;
			{
				QStrFPath = QStrDirPath_TopSrc;
				QStrFPath += "/";
				QStrFPath += FileList[i];
			}
			QLstStrFPath_Dst.push_back(QStrFPath);
		}
	}

	assert(1);//搜索子目录下的文件
	if(bRecursive)
	{
		QFileInfoList Lst_FileInfo;
		Lst_FileInfo = qDir.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot);

		QDir qDirPa;
		{
			qDirPa = qDir;
			qDirPa.cdUp();
		}
		QString qStrPath_DirPa = qDirPa.absolutePath();
		QString qStrPath_DirCur = qDir.absolutePath();

		int nSubDir = Lst_FileInfo.size();
		for (int i = 0; i < nSubDir; i++)
		{
			QFileInfo& FInf = Lst_FileInfo[i];
			if (FInf.isDir())
			{
				QString QStrPath_SubDir = FInf.filePath();
				if(QStrPath_SubDir == qStrPath_DirCur ||
				   QStrPath_SubDir == qStrPath_DirPa)
				{
					continue;
				}

				bool bOK = GetAllPath_Files_inDir(QLstStrFPath_Dst, QStrPath_SubDir, bRecursive);
			}
		}
	}

	return true;
}

bool CSPN_Cmn_FileDir_Filter::CopyMake_SubPath(SPN_String& StrDirPath_FullDst,
												  SPN_String StrDirPath_TopDst,
												  SPN_String StrDirPath_TopSrc,
												  SPN_String StrDirPath_FullSrc)
{
	CopyCalc_SubPath(StrDirPath_FullDst,
					 StrDirPath_TopDst,
					 StrDirPath_TopSrc,
					 StrDirPath_FullSrc);

	QDir DirDst;
	bool bOK = DirDst.mkpath(StrDirPath_FullDst.To_QString());
	return bOK;
}

bool CSPN_Cmn_FileDir_Filter::CopyCalc_SubPath(SPN_String& StrDirPath_FullDst, 
												  SPN_String StrDirPath_TopDst,
												  SPN_String StrDirPath_TopSrc, 
												  SPN_String StrDirPath_FullSrc)
{
	//1. 参数准备
	QString qStrDirPath_TopDst = StrDirPath_TopDst.To_QString();
	QString qStrDirPath_TopSrc = StrDirPath_TopSrc.To_QString();
	QString qStrDirPath_FullSrc = StrDirPath_FullSrc.To_QString();

	qStrDirPath_TopDst  = QDir(qStrDirPath_TopDst).absolutePath();
	qStrDirPath_TopSrc  = QDir(qStrDirPath_TopSrc).absolutePath();
	qStrDirPath_FullSrc = QDir(qStrDirPath_FullSrc).absolutePath();

	_NormalizePath(qStrDirPath_TopDst);
	_NormalizePath(qStrDirPath_TopSrc);
	_NormalizePath(qStrDirPath_FullSrc);

	//2. 入口规则
	QString qStrTmp_TopSrc = qStrDirPath_FullSrc.mid(0, qStrDirPath_TopSrc.size());
	if (qStrDirPath_TopSrc != qStrTmp_TopSrc)
	{
		return false; //输入顶级源目录路径, 未包含在长路径中!
	}

	QString qStrFolderSrc_IncFrTop;
	{
		qStrFolderSrc_IncFrTop = qStrDirPath_FullSrc.mid(StrDirPath_TopSrc.size());
	}

	if (qStrFolderSrc_IncFrTop.size() == 0)
	{
		StrDirPath_FullDst = qStrDirPath_TopDst;
		return true;
	}

	if (!_Is_Slash_Tail(StrDirPath_TopSrc.To_QString()) && !_Is_Slash_Head(qStrFolderSrc_IncFrTop))
	{
		return false; //输入顶级源目录路径不是一个完整的目录路径!
	}

	//3. Dst路径计算
	QString qStrDirPath_FullDst;
	{
		qStrDirPath_FullDst = qStrDirPath_TopDst;

		_Ensure_HasSlash_Tail(qStrDirPath_FullDst);
		_Ensure_NoSlash_Head(qStrFolderSrc_IncFrTop);

		qStrDirPath_FullDst += qStrFolderSrc_IncFrTop;
	}

	StrDirPath_FullDst = qStrDirPath_FullDst;

	return true;
}

bool CSPN_Cmn_FileDir_Filter::_CreateFile_Txt(QString StrFPath_FullDst)
{
	//1 如果存在不再创建:
#ifdef _DEBUG
	static int iDbg_Run = 0;
	{
		if (0 == iDbg_Run)
		{
			//assert(false);
			int iBrk = 0;
		}
		iDbg_Run++;
	}
#endif // 
	QFileInfo qFI(StrFPath_FullDst);
	if (qFI.exists())
	{
		return true;
	}

	//2 确保目录存在:
	QDir Dir = qFI.dir();		
	if (!Dir.exists())
	{
		Dir.mkpath(Dir.absolutePath());
		if (!Dir.exists())
		{
			return false;
		}
	}

	//3 创建文件:
	std::fstream FStrm;
	SPN_String HwStrFPath_FullDst = StrFPath_FullDst;
	std::string StdStr_FPath_FullDst = HwStrFPath_FullDst.To_StdString(); //用QString直接转换出现乱码!
	FStrm.open(StdStr_FPath_FullDst, std::fstream::out | std::fstream::app);
	FStrm.close();

	//4 检测结果:
	bool bOK = qFI.exists();
	return bOK;
}

bool CSPN_Cmn_FileDir_Filter::_DeleteFile(QString StrFPath_FullDst)
{
	QFileInfo qFI(StrFPath_FullDst);
	if (!qFI.exists())
	{
		return true;
	}

	bool bOK = qFI.dir().remove(qFI.fileName());
	return bOK;
}

bool CSPN_Cmn_FileDir_Filter::_IsHas_SubDir(const SPN_String& StrDirPath)
{
	if (StrDirPath.size() == 0)
	{
		return false;
	}

	if (!QFileInfo(StrDirPath.To_QString()).isDir())
	{
		return false;
	}

	QDir Dir(StrDirPath.To_QString());
	if (!Dir.exists())
	{
		return false;
	}

	QFileInfoList qLstFI = Dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
	if (qLstFI.size() > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CSPN_Cmn_FileDir_Filter::_IsHas_File(const SPN_String& StrDirPath)
{
	if (StrDirPath.size() == 0)
	{
		return false;
	}

	if (!QFileInfo(StrDirPath.To_QString()).isDir())
	{
		return false;
	}

	QDir Dir(StrDirPath.To_QString());
	if (!Dir.exists())
	{
		return false;
	}

	QFileInfoList qLstFI = Dir.entryInfoList(QDir::Files);
	if (qLstFI.size() > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void CSPN_Cmn_FileDir_Filter::_Validate_FileName(SPN_String& StrFileName, char cNew/* = '_*/)
{
	for (int iC = StrFileName.size() - 1; iC >= 0; iC--)
	{
		if ('\\' == StrFileName[iC] ||
			'/' == StrFileName[iC] ||
			':' == StrFileName[iC] ||
			'*' == StrFileName[iC] ||
			'?' == StrFileName[iC] ||
			'\"' == StrFileName[iC] ||
			'\'' == StrFileName[iC] ||
			'<' == StrFileName[iC] ||
			'>' == StrFileName[iC] ||
			'|' == StrFileName[iC]
			)
		{
			StrFileName[iC] = cNew;
		}
	}
}

void CSPN_Cmn_FileDir_Filter::_Validate_FileName(QString& StrFileName, char cNew/* = '_'*/)
{
	for (int iC = StrFileName.size() - 1; iC >= 0; iC--)
	{
		if ('\\' == StrFileName[iC] ||
			'/' == StrFileName[iC] ||
			':' == StrFileName[iC] ||
			'*' == StrFileName[iC] ||
			'?' == StrFileName[iC] ||
			'\"' == StrFileName[iC] ||
			'\'' == StrFileName[iC] ||
			'<' == StrFileName[iC] ||
			'>' == StrFileName[iC] ||
			'|' == StrFileName[iC]
			)
		{
			StrFileName[iC] = cNew;
		}
	}
}

bool CSPN_Cmn_FileDir_Filter::_ComposeFilePath(SPN_String& StrFPath_Dst, const SPN_String& StrFolderPath_Dst, const SPN_String& StrFileName)
{
	SPN_String StrFolderPath_DstTmp = StrFolderPath_Dst;
	{
		_Ensure_HasSlash_Tail(StrFolderPath_DstTmp);
	}
	
	SPN_String StrFileName_Tmp = StrFileName;
	{
		QFileInfo qFI(StrFileName_Tmp.To_QString());
		StrFileName_Tmp = qFI.fileName();
	}

	StrFPath_Dst;
	{
		StrFPath_Dst =  StrFolderPath_DstTmp;
		StrFPath_Dst += StrFileName_Tmp;
	}

	return true;
}

bool CSPN_Cmn_FileDir_Filter::_ComposeFilePath(QString& StrFPath_Dst, const QString& StrFolderPath_Dst, const QString& StrFileName)
{
	QString StrFolderPath_DstTmp = StrFolderPath_Dst;
	{
		_Ensure_HasSlash_Tail(StrFolderPath_DstTmp);
	}
	
	QString StrFileName_Tmp = StrFileName;
	{
		QFileInfo qFI(StrFileName_Tmp);
		StrFileName_Tmp = qFI.fileName();
	}

	StrFPath_Dst;
	{
		StrFPath_Dst = StrFolderPath_DstTmp;
		StrFPath_Dst += StrFileName_Tmp;
	}

	return true;
}
