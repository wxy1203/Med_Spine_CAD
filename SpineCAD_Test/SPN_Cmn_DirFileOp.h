#ifndef SPN_Cmn_DirFileOp_H__INCLUDED_
#define	SPN_Cmn_DirFileOp_H__INCLUDED_

#	pragma once

#include "SPN_Cmn_WString.h"

class  CSPN_Cmn_DirFileOp
{
public:
	static void Ensure_HasFile(SPN_String StrFilePath);
	static void Ensure_DelFile(SPN_String StrFilePath);

	static bool GetSel_PathFile_by_BrowseUI_forLoad	(SPN_String& StrRslt_FilePath, SPN_String StrPrompt, SPN_String StrDirPath_Def);
	static bool GetSel_PathFile_by_BrowseUI_forSave	(SPN_String& StrRslt_FilePath, SPN_String StrPrompt, SPN_String StrDirPath_Def);
	static bool GetSel_PathDir_by_BrowseUI			(SPN_String& StrRslt_DirPath , SPN_String StrPrompt, SPN_String StrDirPath_Def);

protected:
	CSPN_Cmn_DirFileOp(){};
	virtual ~CSPN_Cmn_DirFileOp(){};
};

#endif //  // !defined(SPN_Cmn_DirFileOp_H__INCLUDED_)
