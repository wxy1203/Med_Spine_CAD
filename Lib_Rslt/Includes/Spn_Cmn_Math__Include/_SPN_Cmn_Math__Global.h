
#ifndef _SPN_Cmn_MATH__Global__Included
#define _SPN_Cmn_MATH__Global__Included

#pragma once

//
//  ����ڴ�й© //[_8 :5:56 ]: 
#ifdef _DEBUG
#ifdef _DEBUG_MEM_LEAK
//[__4 :46:7 ]:����exe"Ӧ�ó����޷�����"��"SideBySide"�쳣!!! #include "vld.h"
#endif // 
#endif // 
//

#include "assert.h"//[_8 3:6: ]:
#define SPN_ASSERT assert

#include "_include_QT.h"

#ifndef _MSC_VER // ��Windows ==> Linux!
#define SPN_CMN_MATH__MAKE_STC_LIB 
#endif //  //_MSC_VER

#define _SHOW_define_SPN_CMN_MATH_EXPORT_

#ifndef SPN_CMN_MATH__MAKE_STC_LIB
#	if defined(SPN_Cmn_MATH_LIB)
#		define SPN_CMN_MATH_EXPORT Q_DECL_EXPORT
#		ifdef _SHOW_define_SPN_CMN_MATH_EXPORT_
#			pragma message( "define SPN_CMN_MATH_EXPORT --> Q_DECL_EXPORT in Compiling " __FILE__ ) 
#		endif
#	else
#		define SPN_CMN_MATH_EXPORT Q_DECL_IMPORT
#		ifdef _SHOW_define_SPN_CMN_MATH_EXPORT_
#			pragma message( "define SPN_CMN_MATH_EXPORT --> Q_DECL_IMPORT in Compiling " __FILE__ ) 
#		endif
#	endif
#else
#	define SPN_CMN_MATH_EXPORT
#		ifdef _SHOW_define_SPN_CMN_MATH_EXPORT_
#			pragma message( "define SPN_CMN_MATH_EXPORT --> (void) in Compiling " __FILE__ ) 
#		endif
#endif // 

//�����º�: ����WINDOWS�ϱ���LINUXר�÷�֧����, ����������ٹرմ˺�, �Իָ�������֧�ж�
//#define _SIM_LINUX_COMPILE_BRANCH_ON_WINDOWS

#if defined(_MSC_VER)
#	ifdef _SIM_LINUX_COMPILE_BRANCH_ON_WINDOWS
#		undef _NOT_LINUX_CXX
#	else
#		define _NOT_LINUX_CXX _MSC_VER
#	endif
#endif // 

#endif // //_SPN_Cmn_MATH__Global__Included
