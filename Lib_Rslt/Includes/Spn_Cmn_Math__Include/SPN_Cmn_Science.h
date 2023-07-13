

#ifndef SPN_Cmn_ABC_Science__INCLUDE
#define SPN_Cmn_ABC_Science__INCLUDE

//*****************************************************************************

#include "_From_VC_to_QT.h"

//typedef unsigned long       DWORD;
//typedef int                 BOOL;
//typedef unsigned char       BYTE;
//typedef unsigned short      WORD;
//typedef float               FLOAT;
//typedef FLOAT               *PFLOAT;
//typedef BOOL near           *PBOOL;
//typedef BOOL far            *LPBOOL;
//typedef BYTE near           *PBYTE;
//typedef BYTE far            *LPBYTE;
//typedef int near            *PINT;
//typedef int far             *LPINT;
//typedef WORD near           *PWORD;
//typedef WORD far            *LPWORD;
//typedef long far            *LPLONG;
//typedef DWORD near          *PDWORD;
//typedef DWORD far           *LPDWORD;
//typedef void far            *LPVOID;
//typedef CONST void far      *LPCVOID;

//typedef int                 INT;
//typedef unsigned int        UINT;
//typedef unsigned int        *PUINT;




//#include "_From_MFC_afxtempl.h"
//#include "_From_MFC_afxtempl.h"
#include "SPN_Cmn_Math_Const.h"

//*****************************************************************************
inline void IntersectLineAndPlane
(DBLFLT  xN, DBLFLT  yN, DBLFLT  zN,//normline of the plane
 DBLFLT  xP, DBLFLT  yP, DBLFLT  zP,//point on the plane
 DBLFLT  xA, DBLFLT  yA, DBLFLT  zA,//point A to define the line
 DBLFLT  xB, DBLFLT  yMin, DBLFLT  zB,//point B to defint the line 
 DBLFLT& xI, DBLFLT& yI, DBLFLT& zI)
{
	//the line's tangent vector for the coefficient of line equation
	//	(x-xA)/m = (y-yA)/n = (z-ZA)/p:
	DBLFLT m = xB - xA;
	DBLFLT n = yMin - yA;
	DBLFLT p = zB - zA;
	DBLFLT t = ((xN*xP + yN * yP + zN * zP) - (xN*xA + yN * yA + zN * zA)) / (xN*m + yN * n + zN * p);

	xI = xA + m * t;
	yI = yA + n * t;
	zI = zA + p * t;

	/*
	std::string Str[100];
	Str.Format("xI=%f, yI=%f, zI=%f", xI, yI, zI);
	::ShowMsg(Str);
	*/
};

//------------------------------------------------------------------------------
//#ifdef _DEBUG
//void Assert_Valid_DBLFLT(const DBLFLT& v);
//#endif // 
//------------------------------------------------------------------------------

template<class TP>
inline void CutIntoRange(TP& v, const TP vMin, const TP vMax)
{
	if (v < vMin)
		v = vMin;
	else if (v > vMax)
		v = vMax;
}

template<class TP>
inline TP ClcIntoRange(const TP& v, const TP vMin, const TP vMax)
{
	if (v < vMin)
		return vMin;
	else if (v > vMax)
		return vMax;
	else
		return v;
}

//------------------------------------------------------------------------------

inline int fRound(float fV)
{
	if (fV >= 0.0f)
		return (int)(fV + 0.5f);
	else
		return (int)(fV - 0.5f);
};

inline int dRound(double fV)
{
	if (fV >= 0.0f)
		return (int)(fV + 0.5f);
	else
		return (int)(fV - 0.5f);
};

//修改给定数值以使之处在均布的"节点"上(按"四舍五入"处理):
template<class TPNum, class TPStep>
inline int RoundNum(TPNum& vCalc, TPStep vBgn, TPStep vSpacing)
{
	int iPosRslt = (vCalc - vBgn) / vSpacing + 0.5f;
	vCalc = vBgn + iPosRslt * vSpacing;

	return iPosRslt;
};

inline BOOL FLT_EQ(float x, float v)
{
#ifdef _DEBUG
	BOOL B0 = ((v - FLT_EPSILON) <= x);
	BOOL B1 = (x <= (v + FLT_EPSILON));
	return B0 && B1;
#else
	return (((v - FLT_EPSILON) <= x) && (x <= (v + FLT_EPSILON)));
#endif // 
};

inline BOOL DBL_EQ(double x, double v)
{
#ifdef _DEBUG
	BOOL B0 = ((v - DBL_EPSILON) <= x);
	BOOL B1 = (x <= (v + DBL_EPSILON));
	return B0 && B1;
#else
	return (((v - DBL_EPSILON) <= x) && (x <= (v + DBL_EPSILON)));
#endif // 
};

template<class TPFlt>
inline BOOL FLT_EQ_TOL(TPFlt x, TPFlt v, TPFlt fTol)
{
	assert(fTol >= 0.0f);	//	fTol不小于0
	return (((v - fTol) <= x) && (x <= (v + fTol)));
};

template<class T>
inline void ExchangeValue(T& v1, T& v2)
{
	T vTmp = v1;
	v1 = v2;
	v2 = vTmp;
};


/**********************************************************************************
 *
 *  三个数中返回中间大小的值
 *
 **********************************************************************************/
template<class T>
inline T GetMedian3(T v1, T v2, T v3)
{
	T v;
	if (v1 > v2)
	{
		if (v2 > v3)		v = v2;
		else
		{
			if (v1 > v3)	v = v3;
			else		v = v1;
		}
	}
	else
	{
		if (v1 > v3)		v = v1;
		else
		{
			if (v2 > v3)	v = v3;
			else		v = v2;
		}
	}
	return v;
};

inline int Compare(int m, int n)
{
	if (m > n)		return 1;
	else if (m == n)	return 0;
	else			return -1;
};


/***********************************************************
	从已知点(X1,Y1) 和 (X2,Y2) 求未X对应的Y值: 点(X, Y?)
***********************************************************/
template<class TPX, class TPY>
inline void Interpolate_Linear(const TPX X1, //已知点第1点的X
							   const TPY Y1, //已知点第1点的Y
							   const TPX X2, //已知点第2点的X
							   const TPY Y2, //已知点第2点的Y
							   const TPX X,  //待求点的已知X
							   TPY& Y)		 //待求点的未知Y
{
	assert(!FLT_EQ(X1, X2));

	Y = ((X2 - X)*Y1 + (X - X1)*Y2) / (X2 - X1);
};

template<typename TP>
inline TP MIN_VAL_of_TYPE()
{
	assert(false); // 如果运行到此, 则需补充实现对应的特化函数!
	return 0;
};

template<typename TP>
inline TP MAX_VAL_of_TYPE()
{
	assert(false); // 如果运行到此, 则需补充实现对应的特化函数!
	return 0;
};

template<typename TP1, typename TP2>
inline bool IS_SAME_TYPE()
{
	return
		MAX_VAL_of_TYPE<TP1>() == MAX_VAL_of_TYPE<TP2>() &&
		MIN_VAL_of_TYPE<TP1>() == MIN_VAL_of_TYPE<TP2>() &&
		sizeof(TP1) == sizeof(TP2);
};

//以下为支持模板算法类中, 浮点数向整体转换时确保调用到四舍五入, 而其他则顺其自然(包括数值范围的可能越界, 就由算法逻辑自己保障)
// (函数不允许偏特化, 因为借用类偏特化)
template<typename TPDst, typename TPSrc>
class CSPN_TypeValue
{
public:
	static inline TPDst TransformValue(TPSrc vSrc) { return vSrc; };
};
template<>class CSPN_TypeValue<double, float> { public: static inline double TransformValue(float  vSrc) { return vSrc; }; };
template<>class CSPN_TypeValue<float, double> { public: static inline float  TransformValue(double vSrc) { return vSrc; }; };
template<>class CSPN_TypeValue<float, float> { public: static inline float  TransformValue(float  vSrc) { return vSrc; }; };
template<>class CSPN_TypeValue<double, double> { public: static inline double TransformValue(double vSrc) { return vSrc; }; };
template<typename TPDst>class CSPN_TypeValue<TPDst, double> { public: static inline TPDst TransformValue(double vSrc) { return fRound(vSrc); }; };
template<typename TPDst>class CSPN_TypeValue<TPDst, float> { public: static inline TPDst TransformValue(float  vSrc) { return fRound(vSrc); }; };


template<> inline long MIN_VAL_of_TYPE<long>() { return LONG_MIN; };
template<> inline long MAX_VAL_of_TYPE<long>() { return LONG_MAX; };
template<> inline ULONG MIN_VAL_of_TYPE<ULONG>() { return 0; };
template<> inline ULONG MAX_VAL_of_TYPE<ULONG>() { return ULONG_MAX; };

template<> inline int MIN_VAL_of_TYPE<int>() { return INT_MIN; };
template<> inline int MAX_VAL_of_TYPE<int>() { return INT_MAX; };
template<> inline UINT MIN_VAL_of_TYPE<UINT>() { return 0; };
template<> inline UINT MAX_VAL_of_TYPE<UINT>() { return UINT_MAX; };

template<> inline short MIN_VAL_of_TYPE<short>() { return SHORT_MIN; };
template<> inline short MAX_VAL_of_TYPE<short>() { return SHORT_MAX; };
template<> inline USHORT MIN_VAL_of_TYPE<USHORT>() { return 0; };
template<> inline USHORT MAX_VAL_of_TYPE<USHORT>() { return USHORT_MAX; };

template<> inline char MIN_VAL_of_TYPE<char>() { return CHAR_MIN; };
template<> inline char MAX_VAL_of_TYPE<char>() { return CHAR_MAX; };
template<> inline BYTE MIN_VAL_of_TYPE<BYTE>() { return 0; };
template<> inline BYTE MAX_VAL_of_TYPE<BYTE>() { return BYTE_MAX; };

template<> inline float MIN_VAL_of_TYPE<float>() { return FLT_MIN; };
template<> inline float MAX_VAL_of_TYPE<float>() { return FLT_MAX; };

template<> inline double MIN_VAL_of_TYPE<double>() { return DBL_MIN; };
template<> inline double MAX_VAL_of_TYPE<double>() { return DBL_MAX; };

inline double Agl_RAD_to_DEG(double fA_RAD)
{
	return fA_RAD * CNST_dbl_DEGpRAD;
};
inline double Agl_DEG_to_RAD(double fA_DEG)
{
	return fA_DEG * CNST_dbl_RADpDEG;
};

inline double Sin_Deg(double fADeg)
{
	return sin(Agl_DEG_to_RAD(fADeg));
};

inline double Cos_Deg(double fADeg)
{
	return cos(Agl_DEG_to_RAD(fADeg));
};

inline double Tan_Deg(double fADeg)
{
	return tan(Agl_DEG_to_RAD(fADeg));
};

inline double Ctan_Deg(double fADeg)
{
	return 1.0 / Tan_Deg(Agl_DEG_to_RAD(fADeg));
};

#endif // //SPN_Cmn_ABC_Science__INCLUDE
