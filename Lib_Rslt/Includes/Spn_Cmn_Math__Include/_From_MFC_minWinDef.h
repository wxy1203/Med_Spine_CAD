/****************************************************************************
*                                                                           *
* minwindef.h -- Basic Windows Type Definitions for minwin partition        *
*                                                                           *
* Copyright (c) Microsoft Corporation. All rights reserved.                 *
*                                                                           *
****************************************************************************/


#ifndef __Include__From_MFC_minWinDef__H__
#define __Include__From_MFC_minWinDef__H__

#	pragma once

//{{****************************************************************************************
//[9_18 10:54:23 ]: Linux compile needed:

#include "_From_MFC_intsafe.h"

#ifndef _MSC_VER //[9_18 14:04:56 ]:
#define near
#define far
#endif // 

#undef FAR
#undef  NEAR
#define FAR                 far
#define NEAR                near
#ifndef CONST
#define CONST               const
#endif // 

//}}****************************************************************************************

#define _ENABLE_FROM_MFC_MINWINDEF_H
#ifdef _ENABLE_FROM_MFC_MINWINDEF_H

//#include <spestd::strings.h>
//
//#include <winapifamily.h>
//
//#	pragma region Application Family
//#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
//
//#ifndef NO_STRICT
//#ifndef STRICT
//#define STRICT 1
//#endif // 
//#endif //  /* NO_STRICT */
//
//// Win32 defines _WIN32 automatically,
//// but Macintosh doesn't, so if we are using
//// Win32 Functions, we must do it here
//
//#ifdef _MAC
//#ifndef _WIN32
//#define _WIN32
//#endif // 
//#endif //  //_MAC
//
//#ifndef _WIN32
//#define _WIN32
//#endif // 
//
//#ifdef __cplusplus
//extern "C" {
//#endif // 

/*
 * BASETYPES is defined in ntdef.h if these types are already defined
 */

#ifndef _MSC_VER //[9_18 15:15:52 ]:
#define _Null_terminated_
#define memcpy_s memcpy
#define memmove_s memmove
#define __stdcall
#define __cdecl
#define WINAPI
#define _Inout_
#endif // 

//#ifndef BASETYPES
//#define BASETYPES
typedef unsigned long ULONG;
typedef ULONG *PULONG;
typedef unsigned short USHORT;
typedef USHORT *PUSHORT;
typedef unsigned char UCHAR;
typedef UCHAR *PUCHAR;
typedef _Null_terminated_ char *PSZ;
//#endif //   /* !BASETYPES */

//#define MAX_PATH          260
//
//#ifndef NULL
//#ifdef __cplusplus
//#define NULL    0
//#else
//#define NULL    ((void *)0)
//#endif // 
//#endif // 
//
#ifndef FALSE
#define FALSE               0
#endif // 

#ifndef TRUE
#define TRUE                1
#endif // 
//
//#ifndef IN
//#define IN
//#endif // 
//
//#ifndef OUT
//#define OUT
//#endif // 
//
//#ifndef OPTIONAL
//#define OPTIONAL
//#endif // 
//
//#undef far
//#undef near
//#undef pascal
//
#define far
#define near
//
//#if (!defined(_MAC)) && ((_MSC_VER >= 800) || defined(_STDCALL_SUPPORTED))
//#define pascal __stdcall
//#else
//#define pascal
//#endif // 
//
//#if defined(DOSWIN32) || defined(_MAC)
//#define cdecl _cdecl
//#ifndef CDECL
//#define CDECL _cdecl
//#endif // 
//#else
//#define cdecl
//#ifndef CDECL
//#define CDECL
//#endif // 
//#endif // 
//
//#ifdef _MAC
//#define CALLBACK    PASCAL
//#define WINAPI      CDECL
//#define WINAPIV     CDECL
//#define APIENTRY    WINAPI
//#define APIPRIVATE  CDECL
//#ifdef _68K_
//#define PASCAL      __pascal
//#else
//#define PASCAL
//#endif // 
//#elif (_MSC_VER >= 800) || defined(_STDCALL_SUPPORTED)
#define CALLBACK    __stdcall
#define WINAPI      __stdcall
#define WINAPIV     __cdecl
#define APIENTRY    WINAPI
#define APIPRIVATE  __stdcall
#define PASCAL      __stdcall
//#else
//#define CALLBACK
//#define WINAPI
//#define WINAPIV
//#define APIENTRY    WINAPI
//#define APIPRIVATE
//#define PASCAL      pascal
//#endif // 
//
//#ifndef _M_CEE_PURE
//#ifndef WINAPI_INLINE
//#define WINAPI_INLINE  WINAPI
//#endif // 
//#endif // 

typedef char CHAR;
typedef short SHORT;
typedef long LONG;
typedef int INT;


#undef FAR
#undef  NEAR
#define FAR                 far
#define NEAR                near
#ifndef CONST
#define CONST               const
#endif // 

#ifdef _MSC_VER//[9_18 14:51:20 ]:
	//__int64 OK!
#else
	#undef __int64
	#define __int64 long long
	#define _W64 
	#define __w64
#endif // 


typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef float               FLOAT;
typedef FLOAT               *PFLOAT;
typedef BOOL near           *PBOOL;
typedef BOOL far            *LPBOOL;
typedef BYTE near           *PBYTE;
typedef BYTE far            *LPBYTE;
typedef int near            *PINT;
typedef int far             *LPINT;
typedef WORD near           *PWORD;
typedef WORD far            *LPWORD;
typedef long far            *LPLONG;
typedef DWORD near          *PDWORD;
typedef DWORD far           *LPDWORD;
typedef void far            *LPVOID;
typedef CONST void far      *LPCVOID;

typedef int                 INT;
typedef unsigned int        UINT;
typedef unsigned int        *PUINT;


//
//#ifndef NT_INCLUDED
//#include <winnt.h>
//#endif //  /* NT_INCLUDED */



// from BaseTsd.h
#if defined(_WIN64)
typedef __int64 INT_PTR, *PINT_PTR;
typedef unsigned __int64 UINT_PTR, *PUINT_PTR;

typedef __int64 LONG_PTR, *PLONG_PTR;
typedef unsigned __int64 ULONG_PTR, *PULONG_PTR;

#define __int3264   __int64

#else
typedef _W64 int INT_PTR, *PINT_PTR;
typedef _W64 unsigned int UINT_PTR, *PUINT_PTR;

typedef _W64 long LONG_PTR, *PLONG_PTR;
typedef _W64 unsigned long ULONG_PTR, *PULONG_PTR;

#define __int3264   __int32
#endif // 


typedef ULONG_PTR DWORD_PTR, *PDWORD_PTR;


/* Types use for passing & returning polymorphic values */
typedef UINT_PTR            WPARAM;
typedef LONG_PTR            LPARAM;
typedef LONG_PTR            LRESULT;

#ifndef NOMINMAX

#ifndef max
#define __max(a,b)            (((a) > (b)) ? (a) : (b))
#endif // 

#ifndef min
#define __min(a,b)            (((a) < (b)) ? (a) : (b))
#endif // 

#endif //   /* NOMINMAX */

#define MAKEWORD(a, b)      ((WORD)(((BYTE)(((DWORD_PTR)(a)) & 0xff)) | ((WORD)((BYTE)(((DWORD_PTR)(b)) & 0xff))) << 8))
#define MAKELONG(a, b)      ((LONG)(((WORD)(((DWORD_PTR)(a)) & 0xffff)) | ((DWORD)((WORD)(((DWORD_PTR)(b)) & 0xffff))) << 16))
#define LOWORD(l)           ((WORD)(((DWORD_PTR)(l)) & 0xffff))
#define HIWORD(l)           ((WORD)((((DWORD_PTR)(l)) >> 16) & 0xffff))
#define LOBYTE(w)           ((BYTE)(((DWORD_PTR)(w)) & 0xff))
#define HIBYTE(w)           ((BYTE)((((DWORD_PTR)(w)) >> 8) & 0xff))


// from wTypes.h
//typedef void * HANDLE;
//typedef void *HMODULE;
//typedef void *HINSTANCE;
//typedef void *HTASK;
//typedef void *HKEY;
//typedef void *HDESK;
//typedef void *HMF;
//typedef void *HEMF;
//typedef void *HPEN;
//typedef void *HRSRC;
//typedef void *HSTR;
//typedef void *HWINSTA;
//typedef void *HKL;
//typedef void *HGDIOBJ;
//typedef HANDLE HDWP;


//typedef HANDLE NEAR         *SPHANDLE;
//typedef HANDLE FAR          *LPHANDLE;
//typedef HANDLE              HGLOBAL;
//typedef HANDLE              HLOCAL;
//typedef HANDLE              GLOBALHANDLE;
//typedef HANDLE              LOCALHANDLE;
//#ifndef _MANAGED
//#ifndef _MAC
//#ifdef _WIN64
//typedef INT_PTR (FAR WINAPI *FARPROC)();
//typedef INT_PTR (NEAR WINAPI *NEARPROC)();
//typedef INT_PTR (WINAPI *PROC)();
//#else
//typedef int (FAR WINAPI *FARPROC)();
//typedef int (NEAR WINAPI *NEARPROC)();
//typedef int (WINAPI *PROC)();
//#endif //   // _WIN64
//#else
//typedef int (CALLBACK *FARPROC)();
//typedef int (CALLBACK *NEARPROC)();
//typedef int (CALLBACK *PROC)();
//#endif // 
//#else
//typedef INT_PTR (WINAPI *FARPROC)(void);
//typedef INT_PTR (WINAPI *NEARPROC)(void);
//typedef INT_PTR (WINAPI *PROC)(void);
//#endif // 
//
//typedef WORD                ATOM;   //BUGBUG - might want to remove this from minwin
//
//DECLARE_HANDLE(HKEY);
//typedef HKEY *PHKEY;
//DECLARE_HANDLE(HMETAFILE);
//DECLARE_HANDLE(HINSTANCE);
//typedef HINSTANCE HMODULE;      /* HMODULEs can be used in place of HINSTANCEs */
//DECLARE_HANDLE(HRGN);
//DECLARE_HANDLE(HRSRC);
//DECLARE_HANDLE(HSPRITE);
//DECLARE_HANDLE(HLSURF);
//DECLARE_HANDLE(HSTR);
//DECLARE_HANDLE(HTASK);
//DECLARE_HANDLE(HWINSTA);
//DECLARE_HANDLE(HKL);
//
//#ifndef _MAC
//typedef int HFILE;
//#else
//typedef short HFILE;
//#endif // 
//
////
////  File System time stamps are represented with the following structure:
////
//
//typedef struct _FILETIME {
//    DWORD dwLowDateTime;
//    DWORD dwHighDateTime;
//} FILETIME, *PFILETIME, *LPFILETIME;
//#define _FILETIME_

//#ifdef __cplusplus
//}
//#endif // 
//
//#endif //  /* WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP) */
//#	pragma endregion

#endif //  //_ENABLE_FROM_MFC_MINWINDEF_H

#endif //  // __Include__From_MFC_minWinDef__H__

