#ifndef __From_atlTypes_H__
#define __From_atlTypes_H__

#	pragma once

#include "_From_MFC_windef.h"
#include "_From_MFC_minWinDef.h"

//#ifndef(_ATL_USE_WINAPI_FAMILY_DESKTOP_APP)
//#error This file is not compatible with the current WINAPI_FAMILY
//#endif // 

#ifndef _MSC_VER
#define _In_
#define _Out_
#endif // 

/////////////////////////////////////////////////////////////////////////////
// Classes declared in this file

class CSizeInt;
class CPointInt;
class CRectInt;

/////////////////////////////////////////////////////////////////////////////
// CSizeInt - An extent, similar to Windows SIZE_SPN structure.


class SPN_CMN_MATH_EXPORT CSizeInt : public tagSIZE_SPN
{
public:

// Constructors
	// construct an uninitialized size
	CSizeInt() throw();
	// create from two integers
	CSizeInt(
		_In_ int initCX,
		_In_ int initCY) throw();
	// create from another size
	CSizeInt(_In_ SIZE_SPN initSize) throw();
	// create from a point
	CSizeInt(_In_ POINT_SPN initPt) throw();
	// create from a DWORD: cx = LOWORD(dw) cy = HIWORD(dw)
	CSizeInt(_In_ DWORD dwSize) throw();

// Operations
	BOOL operator==(_In_ SIZE_SPN size) const throw();
	BOOL operator!=(_In_ SIZE_SPN size) const throw();
	void operator+=(_In_ SIZE_SPN size) throw();
	void operator-=(_In_ SIZE_SPN size) throw();
	void SetSize(_In_ int CX, _In_ int CY) throw();

// Operators returning CSizeInt values
	CSizeInt operator+(_In_ SIZE_SPN size) const throw();
	CSizeInt operator-(_In_ SIZE_SPN size) const throw();
	CSizeInt operator-() const throw();

// Operators returning CPointInt values
	CPointInt operator+(_In_ POINT_SPN point) const throw();
	CPointInt operator-(_In_ POINT_SPN point) const throw();

// Operators returning CRectInt values
	CRectInt operator+(_In_ const RECT_SPN* lpRect) const throw();
	CRectInt operator-(_In_ const RECT_SPN* lpRect) const throw();
};

/////////////////////////////////////////////////////////////////////////////
// CPointInt - A 2-D point, similar to Windows POINT_SPN structure.

class SPN_CMN_MATH_EXPORT CPointInt :
	public tagPOINT_SPN
{
public:
// Constructors

	// create an uninitialized point
	CPointInt() throw();
	// create from two integers
	CPointInt(
		_In_ int initX,
		_In_ int initY) throw();
	// create from another point
	CPointInt(_In_ POINT_SPN initPt) throw();
	// create from a size
	CPointInt(_In_ SIZE_SPN initSize) throw();
	// create from an LPARAM: x = LOWORD(dw) y = HIWORD(dw)
	CPointInt(_In_ LPARAM dwPoint) throw();


// Operations

// translate the point
	void Offset(
		_In_ int xOffset,
		_In_ int yOffset) throw();
	void Offset(_In_ POINT_SPN point) throw();
	void Offset(_In_ SIZE_SPN size) throw();
	void SetPoint(
		_In_ int X,
		_In_ int Y) throw();

	BOOL operator==(_In_ POINT_SPN point) const throw();
	BOOL operator!=(_In_ POINT_SPN point) const throw();
	void operator+=(_In_ SIZE_SPN size) throw();
	void operator-=(_In_ SIZE_SPN size) throw();
	void operator+=(_In_ POINT_SPN point) throw();
	void operator-=(_In_ POINT_SPN point) throw();

// Operators returning CPointInt values
	CPointInt operator+(_In_ SIZE_SPN size) const throw();
	CPointInt operator-(_In_ SIZE_SPN size) const throw();
	CPointInt operator-() const throw();
	CPointInt operator+(_In_ POINT_SPN point) const throw();

// Operators returning CSizeInt values
	CSizeInt operator-(_In_ POINT_SPN point) const throw();

// Operators returning CRectInt values
	CRectInt operator+(_In_ const RECT_SPN* lpRect) const throw();
	CRectInt operator-(_In_ const RECT_SPN* lpRect) const throw();
};

/////////////////////////////////////////////////////////////////////////////
// CRectInt - A 2-D rectangle, similar to Windows RECT_SPN structure.

//[8_21 17:34:27 ]: #ifndef _WINUSER_
inline void OffsetRect(LPRECT_SPN pRct, int x, int y)
{
	pRct->left += x;
	pRct->right += x;

	pRct->top += y;
	pRct->bottom += y;
}

inline bool CopyRect(
	_Out_ LPRECT_SPN lprcDst,
	_In_ CONST RECT_SPN *lprcSrc)
{
	if (lprcSrc && lprcDst)
	{
		lprcDst->left = lprcSrc->left;
		lprcDst->top = lprcSrc->top;
		lprcDst->right = lprcSrc->right;
		lprcDst->bottom = lprcSrc->bottom;
		return true;
	}
	else
	{
		return false;
	}
}
//[8_21 17:34:33 ]: #endif //  // _WINUSER_

class SPN_CMN_MATH_EXPORT CRectInt :
	public tagRECT_SPN
{
// Constructors
public:
	// uninitialized rectangle
	CRectInt() throw();
	// from left, top, right, and bottom
	CRectInt(
		_In_ int l,
		_In_ int t,
		_In_ int r,
		_In_ int b) throw();
	// copy constructor
	CRectInt(_In_ const RECT_SPN& srcRect) throw();

	// from a pointer to another rect
	CRectInt(_In_ LPCRECT_SPN lpSrcRect) throw();
	// from a point and size
	CRectInt(
		_In_ POINT_SPN point,
		_In_ SIZE_SPN size) throw();
	// from two points
	CRectInt(
		_In_ POINT_SPN topLeft,
		_In_ POINT_SPN bottomRight) throw();

// Attributes (in addition to RECT_SPN members)

	// retrieves the width
	int Width() const throw();
	// returns the height
	int Height() const throw();
	// returns the size
	CSizeInt Size() const throw();
	// reference to the top-left point
	CPointInt& TopLeft() throw();
	// reference to the bottom-right point
	CPointInt& BottomRight() throw();
	// const reference to the top-left point
	const CPointInt& TopLeft() const throw();
	// const reference to the bottom-right point
	const CPointInt& BottomRight() const throw();
	// the geometric center point of the rectangle
	CPointInt CenterPoint() const throw();
	// swap the left and right
	void SwapLeftRight() throw();
	static void WINAPI SwapLeftRight(_Inout_ LPRECT_SPN lpRect) throw();

	// convert between CRectInt and LPRECT_SPN/LPCRECT_SPN (no need for &)
	operator LPRECT_SPN() throw();
	operator LPCRECT_SPN() const throw();

	// returns TRUE if rectangle has no area
	BOOL IsRectEmpty() const throw();
	// returns TRUE if rectangle is at (0,0) and has no area
	BOOL IsRectNull() const throw();
	// returns TRUE if point is within rectangle
	BOOL PtInRect(_In_ POINT_SPN point) const throw();

// Operations

	// set rectangle from left, top, right, and bottom
	void SetRect(
		_In_ int x1,
		_In_ int y1,
		_In_ int x2,
		_In_ int y2) throw();
	void SetRect(
		_In_ POINT_SPN topLeft,
		_In_ POINT_SPN bottomRight) throw();
	// empty the rectangle
	void SetRectEmpty() throw();
	// copy from another rectangle
	void CopyRect(_In_ LPCRECT_SPN lpSrcRect) throw();
	// TRUE if exactly the same as another rectangle
	BOOL EqualRect(_In_ LPCRECT_SPN lpRect) const throw();

	// Inflate rectangle's width and height by
	// x units to the left and right ends of the rectangle
	// and y units to the top and bottom.
	void InflateRect(
		_In_ int x,
		_In_ int y) throw();
	// Inflate rectangle's width and height by
	// size.cx units to the left and right ends of the rectangle
	// and size.cy units to the top and bottom.
	void InflateRect(_In_ SIZE_SPN size) throw();
	// Inflate rectangle's width and height by moving individual sides.
	// Left side is moved to the left, right side is moved to the right,
	// top is moved up and bottom is moved down.
	void InflateRect(_In_ LPCRECT_SPN lpRect) throw();
	void InflateRect(
		_In_ int l,
		_In_ int t,
		_In_ int r,
		_In_ int b) throw();

	// deflate the rectangle's width and height without
	// moving its top or left
	void DeflateRect(
		_In_ int x,
		_In_ int y) throw();
	void DeflateRect(_In_ SIZE_SPN size) throw();
	void DeflateRect(_In_ LPCRECT_SPN lpRect) throw();
	void DeflateRect(
		_In_ int l,
		_In_ int t,
		_In_ int r,
		_In_ int b) throw();

	// translate the rectangle by moving its top and left
	void OffsetRect(
		_In_ int x,
		_In_ int y) throw();
	void OffsetRect(_In_ SIZE_SPN size) throw();
	void OffsetRect(_In_ POINT_SPN point) throw();
	void NormalizeRect() throw();

	// absolute position of rectangle
	void MoveToY(_In_ int y) throw();
	void MoveToX(_In_ int x) throw();
	void MoveToXY(
		_In_ int x,
		_In_ int y) throw();
	void MoveToXY(_In_ POINT_SPN point) throw();

	// set this rectangle to intersection of two others
	BOOL IntersectRect(
		_In_ LPCRECT_SPN lpRect1,
		_In_ LPCRECT_SPN lpRect2) throw();

	// set this rectangle to bounding union of two others
	BOOL UnionRect(
		_In_ LPCRECT_SPN lpRect1,
		_In_ LPCRECT_SPN lpRect2) throw();

	// set this rectangle to minimum of two others
	BOOL SubtractRect(
		_In_ LPCRECT_SPN lpRectSrc1,
		_In_ LPCRECT_SPN lpRectSrc2) throw();

// Additional Operations
	void operator=(_In_ const RECT_SPN& srcRect) throw();
	BOOL operator==(_In_ const RECT_SPN& rect) const throw();
	BOOL operator!=(_In_ const RECT_SPN& rect) const throw();
	void operator+=(_In_ POINT_SPN point) throw();
	void operator+=(_In_ SIZE_SPN size) throw();
	void operator+=(_In_ LPCRECT_SPN lpRect) throw();
	void operator-=(_In_ POINT_SPN point) throw();
	void operator-=(_In_ SIZE_SPN size) throw();
	void operator-=(_In_ LPCRECT_SPN lpRect) throw();
	void operator&=(_In_ const RECT_SPN& rect) throw();
	void operator|=(_In_ const RECT_SPN& rect) throw();

// Operators returning CRectInt values
	CRectInt operator+(_In_ POINT_SPN point) const throw();
	CRectInt operator-(_In_ POINT_SPN point) const throw();
	CRectInt operator+(_In_ LPCRECT_SPN lpRect) const throw();
	CRectInt operator+(_In_ SIZE_SPN size) const throw();
	CRectInt operator-(_In_ SIZE_SPN size) const throw();
	CRectInt operator-(_In_ LPCRECT_SPN lpRect) const throw();
	CRectInt operator&(_In_ const RECT_SPN& rect2) const throw();
	CRectInt operator|(_In_ const RECT_SPN& rect2) const throw();
	//CRectInt MulDiv(
	//	_In_ int nMultiplier,
	//	_In_ int nDivisor) const throw();
};


#ifndef _ATL_STATIC_LIB_IMPL

// CSizeInt
inline CSizeInt::CSizeInt() throw()
{
	cx = 0;
	cy = 0;
}

inline CSizeInt::CSizeInt(
	_In_ int initCX,
	_In_ int initCY) throw()
{
	cx = initCX;
	cy = initCY;
}

inline CSizeInt::CSizeInt(_In_ SIZE_SPN initSize) throw()
{
	*(SIZE_SPN*)this = initSize;
}

inline CSizeInt::CSizeInt(_In_ POINT_SPN initPt) throw()
{
	*(POINT_SPN*)this = initPt;
}

inline CSizeInt::CSizeInt(_In_ DWORD dwSize) throw()
{
		cx = (short)LOWORD(dwSize);
		cy = (short)HIWORD(dwSize);
}

inline BOOL CSizeInt::operator==(_In_ SIZE_SPN size) const throw()
{
	return (cx == size.cx && cy == size.cy);
}

inline BOOL CSizeInt::operator!=(_In_ SIZE_SPN size) const throw()
{
	return (cx != size.cx || cy != size.cy);
}

inline void CSizeInt::operator+=(_In_ SIZE_SPN size) throw()
{
	cx += size.cx;
	cy += size.cy;
}

inline void CSizeInt::operator-=(_In_ SIZE_SPN size) throw()
{
	cx -= size.cx;
	cy -= size.cy;
}

inline void CSizeInt::SetSize(
	_In_ int CX,
	_In_ int CY) throw()
{
	cx = CX;
	cy = CY;
}

inline CSizeInt CSizeInt::operator+(_In_ SIZE_SPN size) const throw()
{
	return CSizeInt(cx + size.cx, cy + size.cy);
}

inline CSizeInt CSizeInt::operator-(_In_ SIZE_SPN size) const throw()
{
	return CSizeInt(cx - size.cx, cy - size.cy);
}

inline CSizeInt CSizeInt::operator-() const throw()
{
	return CSizeInt(-cx, -cy);
}

inline CPointInt CSizeInt::operator+(_In_ POINT_SPN point) const throw()
{
	return CPointInt(cx + point.x, cy + point.y);
}

inline CPointInt CSizeInt::operator-(_In_ POINT_SPN point) const throw()
{
	return CPointInt(cx - point.x, cy - point.y);
}

inline CRectInt CSizeInt::operator+(_In_ const RECT_SPN* lpRect) const throw()
{
	return CRectInt(lpRect) + *this;
}

inline CRectInt CSizeInt::operator-(_In_ const RECT_SPN* lpRect) const throw()
{
	return CRectInt(lpRect) - *this;
}

// CPointInt
inline CPointInt::CPointInt() throw()
{
	x = 0;
	y = 0;
}

inline CPointInt::CPointInt(
	_In_ int initX,
	_In_ int initY) throw()
{
	x = initX;
	y = initY;
}

inline CPointInt::CPointInt(_In_ POINT_SPN initPt) throw()
{
	*(POINT_SPN*)this = initPt;
}

inline CPointInt::CPointInt(_In_ SIZE_SPN initSize) throw()
{
	*(SIZE_SPN*)this = initSize;
}

inline CPointInt::CPointInt(_In_ LPARAM dwPoint) throw()
{
	x = (short)LOWORD(dwPoint);
	y = (short)HIWORD(dwPoint);
}

inline void CPointInt::Offset(
	_In_ int xOffset,
	_In_ int yOffset) throw()
{
	x += xOffset;
	y += yOffset;
}

inline void CPointInt::Offset(_In_ POINT_SPN point) throw()
{
	x += point.x;
	y += point.y;
}

inline void CPointInt::Offset(_In_ SIZE_SPN size) throw()
{
	x += size.cx;
	y += size.cy;
}

inline void CPointInt::SetPoint(
	_In_ int X,
	_In_ int Y) throw()
{
	x = X;
	y = Y;
}

inline BOOL CPointInt::operator==(_In_ POINT_SPN point) const throw()
{
	return (x == point.x && y == point.y);
}

inline BOOL CPointInt::operator!=(_In_ POINT_SPN point) const throw()
{
	return (x != point.x || y != point.y);
}

inline void CPointInt::operator+=(_In_ SIZE_SPN size) throw()
{
	x += size.cx;
	y += size.cy;
}

inline void CPointInt::operator-=(_In_ SIZE_SPN size) throw()
{
	x -= size.cx;
	y -= size.cy;
}

inline void CPointInt::operator+=(_In_ POINT_SPN point) throw()
{
	x += point.x;
	y += point.y;
}

inline void CPointInt::operator-=(_In_ POINT_SPN point) throw()
{
	x -= point.x;
	y -= point.y;
}

inline CPointInt CPointInt::operator+(_In_ SIZE_SPN size) const throw()
{
	return CPointInt(x + size.cx, y + size.cy);
}

inline CPointInt CPointInt::operator-(_In_ SIZE_SPN size) const throw()
{
	return CPointInt(x - size.cx, y - size.cy);
}

inline CPointInt CPointInt::operator-() const throw()
{
	return CPointInt(-x, -y);
}

inline CPointInt CPointInt::operator+(_In_ POINT_SPN point) const throw()
{
	return CPointInt(x + point.x, y + point.y);
}

inline CSizeInt CPointInt::operator-(_In_ POINT_SPN point) const throw()
{
	return CSizeInt(x - point.x, y - point.y);
}

inline CRectInt CPointInt::operator+(_In_ const RECT_SPN* lpRect) const throw()
{
	return CRectInt(lpRect) + *this;
}

inline CRectInt CPointInt::operator-(_In_ const RECT_SPN* lpRect) const throw()
{
	return CRectInt(lpRect) - *this;
}

// CRectInt
inline CRectInt::CRectInt() throw()
{
	left = 0;
	top = 0;
	right = 0;
	bottom = 0;
}

inline CRectInt::CRectInt(
	_In_ int l,
	_In_ int t,
	_In_ int r,
	_In_ int b) throw()
{
	left = l;
	top = t;
	right = r;
	bottom = b;
}

inline CRectInt::CRectInt(_In_ const RECT_SPN& srcRect) throw()
{
	::CopyRect(this, &srcRect);
}

inline CRectInt::CRectInt(_In_ LPCRECT_SPN lpSrcRect) throw()
{
	::CopyRect(this, lpSrcRect);
}

inline CRectInt::CRectInt(
	_In_ POINT_SPN point,
	_In_ SIZE_SPN size) throw()
{
	right = (left = point.x) + size.cx;
	bottom = (top = point.y) + size.cy;
}

inline CRectInt::CRectInt(
	_In_ POINT_SPN topLeft,
	_In_ POINT_SPN bottomRight) throw()
{
	left = topLeft.x;
	top = topLeft.y;
	right = bottomRight.x;
	bottom = bottomRight.y;
}

inline int CRectInt::Width() const throw()
{
	return right - left;
}

inline int CRectInt::Height() const throw()
{
	return bottom - top;
}

inline CSizeInt CRectInt::Size() const throw()
{
	return CSizeInt(right - left, bottom - top);
}

inline CPointInt& CRectInt::TopLeft() throw()
{
	return *((CPointInt*)this);
}

inline CPointInt& CRectInt::BottomRight() throw()
{
	return *((CPointInt*)this+1);
}

inline const CPointInt& CRectInt::TopLeft() const throw()
{
	return *((CPointInt*)this);
}

inline const CPointInt& CRectInt::BottomRight() const throw()
{
	return *((CPointInt*)this+1);
}

inline CPointInt CRectInt::CenterPoint() const throw()
{
	return CPointInt((left+right)/2, (top+bottom)/2);
}

inline void CRectInt::SwapLeftRight() throw()
{
	SwapLeftRight(LPRECT_SPN(this));
}

inline void WINAPI CRectInt::SwapLeftRight(_Inout_ LPRECT_SPN lpRect) throw()
{
	LONG temp = lpRect->left;
	lpRect->left = lpRect->right;
	lpRect->right = temp;
}

inline CRectInt::operator LPRECT_SPN() throw()
{
	return this;
}

inline CRectInt::operator LPCRECT_SPN() const throw()
{
	return this;
}

inline BOOL CRectInt::IsRectEmpty() const throw()
{
	//return ::IsRectEmpty(this);
	if (this->left == this->right &&
		this->top == this->bottom)
	{
		return true;
	}
	else
	{
		return false;
	}
}

inline BOOL CRectInt::IsRectNull() const throw()
{
	return (left == 0 && right == 0 && top == 0 && bottom == 0);
}

inline BOOL CRectInt::PtInRect(_In_ POINT_SPN point) const throw()
{
	//return ::PtInRect(this, point);
	CRectInt Rct = *this;

	Rct.NormalizeRect();
	if (point.x < Rct.left ||
		point.x > Rct.right ||
		point.y < Rct.bottom ||
		point.y > Rct.top)
	{
		return false;
	}
	else
	{
		return true;
	}
}

inline void CRectInt::SetRect(
	_In_ int x1,
	_In_ int y1,
	_In_ int x2,
	_In_ int y2) throw()
{
	//::SetRect(this, x1, y1, x2, y2);
	this->left = x1;
	this->right = x2;
	this->top = y1;
	this->bottom = y2;
}

inline void CRectInt::SetRect(
	_In_ POINT_SPN topLeft,
	_In_ POINT_SPN bottomRight) throw()
{
	//::SetRect(this, topLeft.x, topLeft.y, bottomRight.x, bottomRight.y);
	SetRect(topLeft.x, topLeft.y, bottomRight.x, bottomRight.y);
}

inline void CRectInt::SetRectEmpty() throw()
{
	//::SetRectEmpty(this);
	this->left = 0;
	this->right = 0;
	this->top = 0;
	this->bottom = 0;
}

inline void CRectInt::CopyRect(_In_ LPCRECT_SPN lpSrcRect) throw()
{
	::CopyRect(this, lpSrcRect);
};


inline BOOL EqualRect(const RECT_SPN* lpRctA, const RECT_SPN* lpRctB)
{
	return
		lpRctA->left == lpRctB->left &&
		lpRctA->top == lpRctB->top &&
		lpRctA->right == lpRctB->right &&
		lpRctA->bottom == lpRctB->bottom;
}

inline BOOL CRectInt::EqualRect(_In_ LPCRECT_SPN lpRect) const throw()
{
	return ::EqualRect(this, lpRect);
}

inline void CRectInt::InflateRect(
	_In_ int x,
	_In_ int y) throw()
{
	//::InflateRect(this, x, y);
	this->left -= x;
	this->right += x;
	this->top -= y;
	this->bottom += y;
}

inline void CRectInt::InflateRect(_In_ SIZE_SPN size) throw()
{
	//::InflateRect(this, size.cx, size.cy);
	InflateRect(size.cx, size.cy);
}

inline void CRectInt::DeflateRect(
	_In_ int x,
	_In_ int y) throw()
{
	//::InflateRect(this, -x, -y);
	InflateRect(-x, -y);
}

inline void CRectInt::DeflateRect(_In_ SIZE_SPN size) throw()
{
	//::InflateRect(this, -size.cx, -size.cy);
	InflateRect(-size.cx, -size.cy);
}

inline void CRectInt::OffsetRect(
	_In_ int x,
	_In_ int y) throw()
{
	::OffsetRect(this, x, y);
}

inline void CRectInt::OffsetRect(_In_ POINT_SPN point) throw()
{
	::OffsetRect(this, point.x, point.y);
}

inline void CRectInt::OffsetRect(_In_ SIZE_SPN size) throw()
{
	::OffsetRect(this, size.cx, size.cy);
}

inline void CRectInt::MoveToY(_In_ int y) throw()
{
	bottom = Height() + y;
	top = y;
}

inline void CRectInt::MoveToX(_In_ int x) throw()
{
	right = Width() + x;
	left = x;
}

inline void CRectInt::MoveToXY(
	_In_ int x,
	_In_ int y) throw()
{
	MoveToX(x);
	MoveToY(y);
}

inline void CRectInt::MoveToXY(_In_ POINT_SPN pt) throw()
{
	MoveToX(pt.x);
	MoveToY(pt.y);
}


inline bool IntersectRng(int& iBgnR, int& iEndR, int iBgnA, int iEndA, int iBgnB, int iEndB)
{
	if (iBgnA > iEndA)
	{
		int iTmp = iBgnA;
		iBgnA = iEndA;
		iEndA = iTmp;
	}
	if (iBgnB > iEndB)
	{
		int iTmp = iBgnB;
		iBgnB = iEndB;
		iEndB = iTmp;
	}

	// off
	if (iBgnA > iEndB ||
		iBgnB > iEndA)
	{
		return false;
	}

	// Contain
	else if (iBgnA >= iBgnB ||
			 iEndA <= iEndB)
	{
		iBgnR = iBgnA;
		iEndR = iEndA;
		return true;
	}

	// Contain
	else if (iBgnB >= iBgnA || iEndB <= iEndA)
	{
		iBgnR = iBgnB;
		iEndR = iEndB;
		return true;
	}

	// part overlap
	else
	{
		iBgnR = std::max<int>(iBgnA, iBgnB);
		iEndR = std::min<int>(iEndA, iEndB);
		return true;
	}
}

inline BOOL CRectInt::IntersectRect(
	_In_ LPCRECT_SPN lpRect1,
	_In_ LPCRECT_SPN lpRect2) throw()
{
	//return ::IntersectRect(this, lpRect1, lpRect2);
	CRectInt RctA = *lpRect1;
	CRectInt RctB = *lpRect2;

	int iXBgn, iXEnd;
	bool Mtx_ovlp = IntersectRng(iXBgn, iXEnd,
								lpRect1->left, lpRect1->right,
								lpRect2->left, lpRect2->right);

	int iYBgn, iYEnd;
	bool bY_ovlp = IntersectRng(iYBgn, iYEnd,
								lpRect1->top, lpRect1->bottom,
								lpRect2->top, lpRect2->bottom);

	if (Mtx_ovlp && bY_ovlp)
	{
		this->left		= iXBgn;
		this->right		= iXEnd;
		this->top		= iYBgn;
		this->bottom	= iYEnd;
		return true;
	}
	else
	{
		return false;
	}
}

inline BOOL CRectInt::UnionRect(
	_In_ LPCRECT_SPN lpRect1,
	_In_ LPCRECT_SPN lpRect2) throw()
{
	//return ::UnionRect(this, lpRect1, lpRect2);

	CRectInt Rct1 = *lpRect1;
	CRectInt Rct2 = *lpRect2;

	Rct1.NormalizeRect();
	Rct2.NormalizeRect();

	this->left		= std::min<int>(Rct1.left, Rct2.left);
	this->right		= std::max<int>(Rct1.right, Rct2.right);
	this->top		= std::min<int>(Rct1.top, Rct2.top);
	this->bottom	= std::max<int>(Rct1.bottom, Rct2.bottom);

	return true;
}

inline void CRectInt::operator=(_In_ const RECT_SPN& srcRect) throw()
{
	::CopyRect(this, &srcRect);
}

inline BOOL CRectInt::operator==(_In_ const RECT_SPN& rect) const throw()
{
	return ::EqualRect(this, &rect);
}

inline BOOL CRectInt::operator!=(_In_ const RECT_SPN& rect) const throw()
{
	return !::EqualRect(this, &rect);
}

inline void CRectInt::operator+=(_In_ POINT_SPN point) throw()
{
	::OffsetRect(this, point.x, point.y);
}

inline void CRectInt::operator+=(_In_ SIZE_SPN size) throw()
{
	::OffsetRect(this, size.cx, size.cy);
}

inline void CRectInt::operator+=(_In_ LPCRECT_SPN lpRect) throw()
{
	InflateRect(lpRect);
}

inline void CRectInt::operator-=(_In_ POINT_SPN point) throw()
{
	::OffsetRect(this, -point.x, -point.y);
}

inline void CRectInt::operator-=(_In_ SIZE_SPN size) throw()
{
	::OffsetRect(this, -size.cx, -size.cy);
}

inline void CRectInt::operator-=(_In_ LPCRECT_SPN lpRect) throw()
{
	DeflateRect(lpRect);
}

inline void CRectInt::operator&=(_In_ const RECT_SPN& rect) throw()
{
	//::IntersectRect(this, this, &rect);
	IntersectRect(this, &rect);
}

inline void CRectInt::operator|=(_In_ const RECT_SPN& rect) throw()
{
	UnionRect(this, &rect);
}

inline CRectInt CRectInt::operator+(_In_ POINT_SPN pt) const throw()
{
	CRectInt rect(*this);
	::OffsetRect(&rect, pt.x, pt.y);
	return rect;
}

inline CRectInt CRectInt::operator-(_In_ POINT_SPN pt) const throw()
{
	CRectInt rect(*this);
	::OffsetRect(&rect, -pt.x, -pt.y);
	return rect;
}

inline CRectInt CRectInt::operator+(_In_ SIZE_SPN size) const throw()
{
	CRectInt rect(*this);
	::OffsetRect(&rect, size.cx, size.cy);
	return rect;
}

inline CRectInt CRectInt::operator-(_In_ SIZE_SPN size) const throw()
{
	CRectInt rect(*this);
	::OffsetRect(&rect, -size.cx, -size.cy);
	return rect;
}

inline CRectInt CRectInt::operator+(_In_ LPCRECT_SPN lpRect) const throw()
{
	CRectInt rect(this);
	rect.InflateRect(lpRect);
	return rect;
}

inline CRectInt CRectInt::operator-(_In_ LPCRECT_SPN lpRect) const throw()
{
	CRectInt rect(this);
	rect.DeflateRect(lpRect);
	return rect;
}

inline CRectInt CRectInt::operator&(_In_ const RECT_SPN& rect2) const throw()
{
	CRectInt rect;
	rect.IntersectRect(this, &rect2);
	return rect;
}

inline CRectInt CRectInt::operator|(_In_ const RECT_SPN& rect2) const throw()
{
	CRectInt rect;
	rect.UnionRect(this, &rect2);
	return rect;
}

inline BOOL CRectInt::SubtractRect(
	_In_ LPCRECT_SPN lpRectSrc1,
	_In_ LPCRECT_SPN lpRectSrc2) throw()
{
	//return ::SubtractRect(this, lpRectSrc1, lpRectSrc2);

	CRectInt Rct1 = *lpRectSrc1;
	CRectInt Rct2 = *lpRectSrc2;

	Rct1.NormalizeRect();
	Rct2.NormalizeRect();

	if (Rct1.Width() < Rct2.Width())
	{
		this->left = Rct1.left;
		this->right = Rct1.right;
	}
	else
	{
		this->left = Rct2.left;
		this->right = Rct2.right;
	}

	if (Rct1.Height() < Rct2.Height())
	{
		this->top = Rct1.top;
		this->bottom = Rct1.bottom;
	}
	else
	{
		this->top = Rct2.top;
		this->bottom = Rct2.bottom;
	}

	return true;
}

inline void CRectInt::NormalizeRect() throw()
{
	int nTemp;
	if (left > right)
	{
		nTemp = left;
		left = right;
		right = nTemp;
	}
	if (top > bottom)
	{
		nTemp = top;
		top = bottom;
		bottom = nTemp;
	}
}

inline void CRectInt::InflateRect(_In_ LPCRECT_SPN lpRect) throw()
{
	left -= lpRect->left;
	top -= lpRect->top;
	right += lpRect->right;
	bottom += lpRect->bottom;
}

inline void CRectInt::InflateRect(
	_In_ int l,
	_In_ int t,
	_In_ int r,
	_In_ int b) throw()
{
	left -= l;
	top -= t;
	right += r;
	bottom += b;
}

inline void CRectInt::DeflateRect(_In_ LPCRECT_SPN lpRect) throw()
{
	left += lpRect->left;
	top += lpRect->top;
	right -= lpRect->right;
	bottom -= lpRect->bottom;
}

inline void CRectInt::DeflateRect(
	_In_ int l,
	_In_ int t,
	_In_ int r,
	_In_ int b) throw()
{
	left += l;
	top += t;
	right -= r;
	bottom -= b;
}

//inline CRectInt CRectInt::MulDiv(
//	_In_ int nMultiplier,
//	_In_ int nDivisor) const throw()
//{
//	return CRectInt(
//		::MulDiv(left, nMultiplier, nDivisor),
//		::MulDiv(top, nMultiplier, nDivisor),
//		::MulDiv(right, nMultiplier, nDivisor),
//		::MulDiv(bottom, nMultiplier, nDivisor));
//}

#endif //  // _ATL_STATIC_LIB_IMPL

#endif //  // __From_atlTypes_H__
