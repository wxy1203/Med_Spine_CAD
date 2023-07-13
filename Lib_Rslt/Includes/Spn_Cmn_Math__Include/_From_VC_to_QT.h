#ifndef __include__SPN_Cmn_VC_to_QT_H__
#define __include__SPN_Cmn_VC_to_QT_H__

#	pragma once

#include "_From_MFC_windef.h"
#include "_From_MFC_minWinDef.h"
#include "_From_MFC_afxtempl.h"
#include "_From_atlTypes.h"
#include <vector>

#ifndef _MSC_VER //[9_18 15:15:52 ]:
#define memcpy_s memcpy
#endif // 

typedef std::vector<std::string> StringArray;

#ifndef _WINGDI_
#define RGB(r,g,b)          ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))

//[8_2 10:19:17 ]: 
//#define PALETTERGB(r,g,b)   (0x02000000 | RGB(r,g,b))
//#define PALETTEINDEX(i)     ((COLORREF)(0x01000000 | (DWORD)(WORD)(i)))
//
///* palette entry flags */
//
//#define PC_RESERVED     0x01    /* palette index used for animation */
//#define PC_EXPLICIT     0x02    /* palette index is explicit to device */
//#define PC_NOCOLLAPSE   0x04    /* do not match color to system palette */

#define GetRValue(Clr)      (LOBYTE        (Clr))
#define GetGValue(Clr)      (LOBYTE(((WORD)(Clr)) >> 8))
#define GetBValue(Clr)      (LOBYTE(       (Clr)  >>16))
#endif // 

#endif //  // __include__SPN_Cmn_VC_to_QT_H__
