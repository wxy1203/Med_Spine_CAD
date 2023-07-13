
#ifndef __include__From_MFC_WinDef__H__
#define __include__From_MFC_WinDef__H__

//#ifdef _USE_SELP_Windef__SPN

//#ifndef _WINDEF_
//#define _WINDEF_

#	pragma once

#include "_From_MFC_minWinDef.h"

/****************************************************************************************
 本库脱离VC以支持跨平台移植, 但源码级重用了 CPointInt/CSizeInt/CRectInt几个类, 因此也需要以下几个基础结构;
 又, 3DSlicer 的Windows版本, 还是间接包含了Windef.h文件, 同时使用Slicer和本库的工程编译时, 出现
 重复定义错误, 因此只好将这几个结构重命名, 以避免此问题!
SIZE --> SIZE_SPN
POINT --> POINT_SPN
RECT --> RECT_SPN
****************************************************************************************/

//
//#include <winapifamily.h>
//
///****************************************************************************
//*                                                                           *
//* windef.h -- Basic Windows Type Definitions                                *
//*                                                                           *
//* Copyright (c) Microsoft Corporation. All rights reserved.                 *
//*                                                                           *
//****************************************************************************/
//
//
//#ifndef _WINDEF_
//#define _WINDEF_
//#	pragma once
//
//#ifdef __cplusplus
//extern "C" {
//#endif // 
//
//#ifdef _M_CEE_PURE
//#define WINAPI_INLINE  __clrcall
//#endif // 
//
//#include <minwindef.h>
//
//#ifndef WINVER
//#define WINVER 0x0500
//#endif //  /* WINVER */
//
//#ifndef NT_INCLUDED
//#include <winnt.h>
//#endif //  /* NT_INCLUDED */
//
//#ifndef WIN_INTERNAL
//
//#	pragma region Application Family
//#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
//
//DECLARE_HANDLE            (HWND);
//DECLARE_HANDLE            (HHOOK);
//
//#endif //  /* WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP) */
//#	pragma endregion
//
//#ifdef WINABLE
//
//#	pragma region Desktop Family
//#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
//
//DECLARE_HANDLE            (HEVENT);
//
//#endif //  /* WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) */
//#	pragma endregion
//
//#endif // 
//#endif // 
//
//#	pragma region Application Family
//#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
//
//#ifndef(_MAC) || !defined(GDI_INTERNAL)
//#ifdef STRICT
//typedef void NEAR* HGDIOBJ;
//#else
//DECLARE_HANDLE(HGDIOBJ);
//#endif // 
//#endif // 
//
//#ifndef(_MAC) || !defined(WIN_INTERNAL)
//DECLARE_HANDLE(HACCEL);
//#endif // 
//#ifndef(_MAC) || !defined(GDI_INTERNAL)
//DECLARE_HANDLE(HBITMAP);
//DECLARE_HANDLE(HBRUSH);
//#endif // 
//#if(WINVER >= 0x0400)
//DECLARE_HANDLE(HCOLORSPACE);
//#endif //  /* WINVER >= 0x0400 */
//#ifndef(_MAC) || !defined(GDI_INTERNAL)
//DECLARE_HANDLE(HDC);
//#endif // 
//DECLARE_HANDLE(HGLRC);          // OpenGL
//DECLARE_HANDLE(HDESK);
//DECLARE_HANDLE(HENHMETAFILE);
//#ifndef(_MAC) || !defined(GDI_INTERNAL)
//DECLARE_HANDLE(HFONT);
//#endif // 
//DECLARE_HANDLE(HICON);
//#ifndef(_MAC) || !defined(WIN_INTERNAL)
//DECLARE_HANDLE(HMENU);
//#endif // 
//#ifndef(_MAC) || !defined(GDI_INTERNAL)
//DECLARE_HANDLE(HPALETTE);
//DECLARE_HANDLE(HPEN);
//#endif // 
//
//#if(WINVER >= 0x0400)
//DECLARE_HANDLE(HWINEVENTHOOK);
//#endif //  /* WINVER >= 0x0400 */
//
//#endif //  /* WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP) */
//#	pragma endregion
//
//#if(WINVER >= 0x0500)
//#ifndef _MAC
//
//#	pragma region Application Family
//#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
//
//DECLARE_HANDLE(HMONITOR);
//
//#endif //  /* WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP) */
//#	pragma endregion
//
//#endif // 
//
//#	pragma region Desktop Family
//#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
//
//DECLARE_HANDLE(HUMPD);
//
//#endif //  /* WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) */
//#	pragma endregion
//
//#endif //  /* WINVER >= 0x0500 */
//
//#	pragma region Application Family
//#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
//
//#ifndef _MAC
//typedef HICON HCURSOR;      /* HICONs & HCURSORs are polymorphic */
//#else
//DECLARE_HANDLE(HCURSOR);    /* HICONs & HCURSORs are not polymorphic */
//#endif // 
//
#ifndef _MSC_VER//[9_18 14:16:15 ]:
typedef uint32_t COLORREF;
//
//#endif //  /* WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP) */
//#	pragma endregion
//
//#	pragma region Desktop Family
//#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
//
typedef uint32_t* LPCOLORREF;
#endif // 
//
//#define HFILE_ERROR ((HFILE)-1)
//
//#endif //  /* WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) */
//#	pragma endregion
//
//#	pragma region Application Family
//#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

typedef struct tagRECT_SPN
{
    LONG    left;
    LONG    top;
    LONG    right;
    LONG    bottom;
} RECT_SPN;
typedef RECT_SPN* PRECT_SPN;
typedef NEAR RECT_SPN* NPRECT_SPN;
typedef FAR  RECT_SPN* LPRECT_SPN;

typedef const RECT_SPN FAR* LPCRECT_SPN;

typedef struct _RECT_SPNL       /* rcl */
{
    LONG    left;
    LONG    top;
    LONG    right;
    LONG    bottom;
} RECT_SPNL;
typedef RECT_SPNL* PRECT_SPNL;
typedef RECT_SPNL* LPRECT_SPNL;

typedef const RECT_SPNL FAR* LPCRECT_SPNL;

typedef struct tagPOINT_SPN
{
    LONG  x;
    LONG  y;
} POINT_SPN;// , *PPOINT_SPN, NEAR *NPPOINT_SPN, FAR *LPPOINT_SPN;
typedef			POINT_SPN* PPOINT_SPN;
typedef NEAR	POINT_SPN* NPPOINT_SPN;
typedef FAR		POINT_SPN* LPPOINT_SPN;

typedef struct _POINT_SPNL      /* ptl  */
{
    LONG  x;
    LONG  y;
} POINT_SPNL;// , *PPOINT_SPNL;
typedef			POINT_SPNL* PPOINT_SPNL;

typedef struct tagSIZE_SPN
{
    LONG        cx;
    LONG        cy;
} SIZE_SPN;// , *PSIZE_SPN, *LPSIZE_SPN;
typedef SIZE_SPN* PSIZE_SPN;
typedef SIZE_SPN* LPSIZE_SPN;

typedef SIZE_SPN               SIZE_SPNL;
typedef SIZE_SPN               *PSIZE_SPNL, *LPSIZE_SPNL;

typedef struct tagPOINT_SPNS
{
#ifndef _MAC
    short   x;
    short   y;
#else
    short   y;
    short   x;
#endif // 
} POINT_SPNS;// , *PPOINT_SPNS, *LPPOINT_SPNS;
typedef POINT_SPNS* PPOINT_SPNS;
typedef POINT_SPNS* LPPOINT_SPNS;

//#endif //  /* WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP) */
//#	pragma endregion

///* mode selections for the device mode function */
//#define DM_UPDATE           1
//#define DM_COPY             2
//#define DM_PROMPT           4
//#define DM_MODIFY           8
//
//#define DM_IN_BUFFER        DM_MODIFY
//#define DM_IN_PROMPT        DM_PROMPT
//#define DM_OUT_BUFFER       DM_COPY
//#define DM_OUT_DEFAULT      DM_UPDATE
//
///* device capabilities indices */
//#define DC_FIELDS           1
//#define DC_PAPERS           2
//#define DC_PAPERSIZE_SPN        3
//#define DC_MINEXTENT        4
//#define DC_MAXEXTENT        5
//#define DC_BINS             6
//#define DC_DUPLEX           7
//#define DC_SIZE_SPN             8
//#define DC_EXTRA            9
//#define DC_VERSION          10
//#define DC_DRIVER           11
//#define DC_BINNAMES         12
//#define DC_ENUMRESOLUTIONS  13
//#define DC_FILEDEPENDENCIES 14
//#define DC_TRUETYPE         15
//#define DC_PAPERNAMES       16
//#define DC_ORIENTATION      17
//#define DC_COPIES           18
//
//#ifdef __cplusplus
//}
//#endif // 
//


//#endif //  //_WINDEF_

//#endif // // _USE_SELP_Windef__SPN

#endif //  //__include__From_MFC_WinDef__H__

