
#include "pch.h"

#include "SPN_Cmn_DirFileOp.h"
#include "SPN_Cmn_WString.h"

#ifdef _MSC_VER
	#include "stringapiset.h"
#else
	
#endif // 

#include <QVariant>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>


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

//创建文件标记
void CSPN_Cmn_DirFileOp::Ensure_HasFile(SPN_String StrFilePath_OKFlag)
{
	if (QFile::exists(StrFilePath_OKFlag.Get_QString()))
	{
		return;
	}
	else
	{
		//CSPN_CmnQConfig CfgFileTmp;
		//CfgFileTmp.Construct(StrFilePath_OKFlag);
		//CfgFileTmp.SetVal_NodeKey("TmpNode", "TmpKey", 1);
	}
}

void CSPN_Cmn_DirFileOp::Ensure_DelFile(SPN_String StrFilePath_OKFlag)
{
	if (!QFile::exists(StrFilePath_OKFlag.Get_QString()))
	{
		return;
	}
	else
	{
		std::wstringstream WStrmCmd_DelFile;
		{
			WStrmCmd_DelFile << /*_T*/("del ");
			WStrmCmd_DelFile << StrFilePath_OKFlag;
		}

		std::wstring StrW_CmdLn_Lnk = WStrmCmd_DelFile.str();

		SPN_String_ToFr MBToFr;
		const char* lpCmd = MBToFr.WCharToMByte(StrW_CmdLn_Lnk.c_str());

		system(lpCmd);

#ifdef _DEBUG
		//bool bExist = QFile::exists(StrFilePath_OKFlag.Get_QString());
		//assert(!bExist);
#endif // 
	}
}

bool CSPN_Cmn_DirFileOp::GetSel_PathFile_by_BrowseUI_forLoad(SPN_String& StrRslt_FilePath, SPN_String StrPrompt, SPN_String StrDirPath_Def)
{
	QString qStrDirPath_Def = StrDirPath_Def.To_QString();
	StrRslt_FilePath = QFileDialog::getOpenFileName(nullptr, StrPrompt.Get_QString(), qStrDirPath_Def);

	bool bOK = StrRslt_FilePath.size() > 0;
	return bOK;
}

bool CSPN_Cmn_DirFileOp::GetSel_PathFile_by_BrowseUI_forSave(SPN_String& StrRslt_FilePath, SPN_String StrPrompt, SPN_String StrDirPath_Def)
{
	StrRslt_FilePath = QFileDialog::getSaveFileName(nullptr, StrPrompt.Get_QString(), StrDirPath_Def.Get_QString());

	bool bOK = StrRslt_FilePath.size() > 0;
	return bOK;
}

bool CSPN_Cmn_DirFileOp::GetSel_PathDir_by_BrowseUI(SPN_String& StrRslt_DirPath, SPN_String StrPrompt, SPN_String StrDirPath_Def)
{
	StrRslt_DirPath = QFileDialog::getExistingDirectory(nullptr, StrPrompt.Get_QString(), StrDirPath_Def.Get_QString());

	bool bOK = StrRslt_DirPath.size() > 0;
	return bOK;
}

