// SPN_Cmn_2DSize.h: interface for the CSPN_Cmn_2DSize class.
//
//////////////////////////////////////////////////////////////////////

#ifndef SPN_Cmn_2DSIZE_H__INCLUDED_
#define SPN_Cmn_2DSIZE_H__INCLUDED_

#include <vector>
#include "stdio.h"
//#include "afx.h"
//#include "TCHAR.h"
//#include "CTYPE.H"
//#include <afxcoll.h>
//#include "_From_MFC_afxtempl.h"//#include "_From_MFC_afxtempl.h"//#include <From_MFC_afxtempl.h>
//#include <fstream.h>

//#include "SPN_Cmn_CArray.h"
#include "QSize.h"

#pragma once


template< class TP >
class CSPN_Cmn_2DSize
{
//Constructor/destructor:
public:
	CSPN_Cmn_2DSize();
	CSPN_Cmn_2DSize( const TP & fcx, const TP & fcy );
	CSPN_Cmn_2DSize( const CSizeInt  & size );

	TP* GetDataBuf()
	{
		return m_arrf2D;
	};
	const TP* GetDataBuf() const
	{
		return m_arrf2D;
	};
	//data member:
protected:
	static int m_iSortKey;
	TP m_arrf2D[2];

//Attritutes:
public:
	static inline int	GetCount_SubDim() { return 2; };

	TP&			operator[](int i);
	const TP&	operator[](int i) const;
	const TP&	cx()	const;
	const TP&	cy()	const;

	void cx( const TP& fcx );
	void cy( const TP& fcy );

	CSizeInt Get_CSize () const;

public:
	explicit CSPN_Cmn_2DSize(const QSize& Sz)					{ cx(Sz.width());	cy(Sz.height()); };
	explicit CSPN_Cmn_2DSize(const QSizeF& SzF)					{ cx(SzF.width());	cy(SzF.height()); };
	QSize	To_QSize()											{ return QSize((*this).x(), (*this).y()); };
	QSizeF	To_QSizeF()											{ return QSizeF((*this).x(), (*this).y());};
	const CSPN_Cmn_2DSize<TP>& operator  = (const QSize qSz)		{ m_arrf2D[0] = qSz.width(); m_arrf2D[1] = qSz.height(); return *this; };
	const CSPN_Cmn_2DSize<TP>& operator  = (const QSizeF qSz)	{ m_arrf2D[0] = qSz.width(); m_arrf2D[1] = qSz.height(); return *this; };

//Calculations:
public:
	const CSPN_Cmn_2DSize<TP>& operator  = (const CSizeInt& Sz)				{ (*this).m_arrf2D[0] = Sz.cx; (*this).m_arrf2D[1] = Sz.cy; return *this; };
	const CSPN_Cmn_2DSize<TP>& operator  = (const CSPN_Cmn_2DSize<TP> &Sz)	{ (*this).m_arrf2D[0] = Sz.cx(); (*this).m_arrf2D[1] = Sz.cy(); return *this; };

	void operator += ( const CSPN_Cmn_2DSize<TP> & size );
	void operator -= ( const CSPN_Cmn_2DSize<TP> & size );
	void operator *= (double fK);
	void operator /= (double fK);

	CSPN_Cmn_2DSize<TP> operator  = (const TP fV) { (*this).m_arrf2D[0] = fV; (*this).m_arrf2D[1] = fV; return *this; };
	void operator += (const TP fV) { (*this).m_arrf2D[0] += fV; (*this).m_arrf2D[1] += fV; };
	void operator -= (const TP fV) { (*this).m_arrf2D[0] -= fV; (*this).m_arrf2D[1] -= fV; };


	BOOL operator> ( const CSPN_Cmn_2DSize<TP> & size2 ) const;
	BOOL operator< ( const CSPN_Cmn_2DSize<TP> & size2 ) const;
	BOOL operator==( const CSPN_Cmn_2DSize<TP> & size2 ) const;
	BOOL operator!=( const CSPN_Cmn_2DSize<TP> & size2 ) const;
	BOOL operator>=( const CSPN_Cmn_2DSize<TP> & size2 ) const;
	BOOL operator<=( const CSPN_Cmn_2DSize<TP> & size2 ) const;

//member function:
public:
	int Compare	( const CSPN_Cmn_2DSize<TP> & size2 ) const;

	static void SetSortKey	( int iSortKey );
	static BOOL IsSortKey	( int iSortKey );
	static int  GetSortKey	();

	//friend ::ofstream& operator<<( ::ofstream &stream, const CSPN_Cmn_2DSize<TP> & size );
	//friend ::ifstream& operator>>( ::ifstream &stream, CSPN_Cmn_2DSize<TP> & size );
	//void Serialize(CSPN_Cmn_Archive & ar );


	#ifdef _DEBUG
		//void AssertValid( CSPN_Cmn_2DSize<TP> & size );
		//void TraceFmt( std::string& StrTrace ) const;
	#endif // 
};
//**************************************************************************************************
//--------------------------------------------------------------------------------------------------
template< class TP > 
inline CSizeInt CSPN_Cmn_2DSize<TP>::Get_CSize() const 
{
	return CSizeInt((*this).m_arrf2D[0], (*this).m_arrf2D[1]);
};
//--------------------------------------------------------------------------------------------------
template< class TP > 
inline void CSPN_Cmn_2DSize<TP>::SetSortKey( int iSortKey )
{
	CSPN_Cmn_2DSize<TP>::m_iSortKey = iSortKey % 2;
};
//--------------------------------------------------------------------------------------------------
template< class TP > 
inline int CSPN_Cmn_2DSize<TP>::GetSortKey()
{
	return CSPN_Cmn_2DSize<TP>::m_iSortKey;
};
//--------------------------------------------------------------------------------------------------
template< class TP > 
inline BOOL CSPN_Cmn_2DSize<TP>::IsSortKey( int iSortKey )
{
	if( iSortKey == CSPN_Cmn_2DSize<TP>::m_iSortKey )
		return TRUE;
	else
		return FALSE;
};
//--------------------------------------------------------------------------------------------------
template< class TP > 
inline int CSPN_Cmn_2DSize<TP>::Compare( const CSPN_Cmn_2DSize<TP> & size2 ) const
{
	if( ( *this ) == size2 )
		return 0;
	if( ( *this ) < size2 )
		return -1;
	else
		return 1;
};
//--------------------------------------------------------------------------------------------------
template< class TP > 
inline CSPN_Cmn_2DSize<TP> operator +( const CSPN_Cmn_2DSize<TP> & size1, const CSPN_Cmn_2DSize<TP> & size2 )
{
	return CSPN_Cmn_2DSize<TP>( size1.cx()+size2.cx(), size1.y()+size2.cy());
}
//--------------------------------------------------------------------------------------------------
template< class TP > 
inline CSPN_Cmn_2DSize<TP> operator -( const CSPN_Cmn_2DSize<TP> & size1, const CSPN_Cmn_2DSize<TP> & size2 )
{
	return CSPN_Cmn_2DSize<TP>( size1.cx()-size2.cx(), size1.cy()-size2.cy());
}
//--------------------------------------------------------------------------------------------------
template< class TP > inline
CSPN_Cmn_2DSize<TP> operator *( const CSPN_Cmn_2DSize<TP> & size, const TP fK )
{
	return CSPN_Cmn_2DSize<TP>( size.cx()*fK, size.cy()*fK );
}
//--------------------------------------------------------------------------------------------------
template< class TP > inline 
CSPN_Cmn_2DSize<TP> operator /( const CSPN_Cmn_2DSize<TP> & size, const TP fK )
{
	assert( !FLT_EQ( fK, 0.0f ) );
	return CSPN_Cmn_2DSize<TP>( size.cx()/fK, size.cy()/fK );
}
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
template< class TP > 
inline void CSPN_Cmn_2DSize<TP>::operator +=( const CSPN_Cmn_2DSize<TP> & size )
{
	m_arrf2D[0] += size.cx();
	m_arrf2D[1] += size.cy();
}
//--------------------------------------------------------------------------------------------------
template< class TP > 
inline void CSPN_Cmn_2DSize<TP>::operator -=( const CSPN_Cmn_2DSize<TP> & size )
{
	m_arrf2D[0] -= size.cx();
	m_arrf2D[1] -= size.cy();
}
//--------------------------------------------------------------------------------------------------
template< class TP > 
inline void CSPN_Cmn_2DSize<TP>::operator *=( double fK )
{
	m_arrf2D[0] *= fK;
	m_arrf2D[1] *= fK;
}
//--------------------------------------------------------------------------------------------------
template< class TP > 
inline void CSPN_Cmn_2DSize<TP>::operator /=( double fK )
{
	assert( !FLT_EQ( fK,0.0f ) );
	m_arrf2D[0] /= fK;
	m_arrf2D[1] /= fK;
}
//--------------------------------------------------------------------------------------------------
template< class TP > 
inline const TP & CSPN_Cmn_2DSize<TP>::cx() const 
{ 
	return m_arrf2D[0]; 
};
//--------------------------------------------------------------------------------------------------
template< class TP > 
inline const TP & CSPN_Cmn_2DSize<TP>::cy() const 
{ 
	return m_arrf2D[1];
};
//--------------------------------------------------------------------------------------------------
template< class TP > 
inline void CSPN_Cmn_2DSize<TP>::cx(const TP & fcx )
{ 
	m_arrf2D[0] = fcx; 
};
//--------------------------------------------------------------------------------------------------
template< class TP > 
inline void CSPN_Cmn_2DSize<TP>::cy( const TP & fcy )
{ 
	m_arrf2D[1] = fcy; 
};
//--------------------------------------------------------------------------------------------------
template< class TP > 
inline CSPN_Cmn_2DSize<TP>::CSPN_Cmn_2DSize( const TP & fcx, const TP & fcy )
{
	m_arrf2D[0] = fcx;
	m_arrf2D[1] = fcy;
};
//--------------------------------------------------------------------------------------------------
//Assume the the size as TP array that hold two member; It's easy for cycle:
template< class TP > 
inline TP & CSPN_Cmn_2DSize<TP>::operator[]( int i )
{
	assert( i >= 0 && i < 2 );
	return m_arrf2D[i];
};
//--------------------------------------------------------------------------------------------------
//Assume the the size as TP array that hold two member; It's easy for cycle:
template< class TP > 
inline const TP & CSPN_Cmn_2DSize<TP>::operator []( int i ) const
{
	assert( i >= 0 && i < 2 );
	return m_arrf2D[i];
};
//--------------------------------------------------------------------------------------------------
//template< class TP > 
//inline void CSPN_Cmn_2DSize<TP>::operator =( const CSizeInt & size )
//{
//	cx( size.cx );
//	cy( size.cy );
//};
//--------------------------------------------------------------------------------------------------
//template< class TP > 
//inline void CSPN_Cmn_2DSize<TP>::operator =( const CSPN_Cmn_2DSize<TP> & size )
//{
//	cx( size.cx() );
//	cy( size.cy() );
//};
//--------------------------------------------------------------------------------------------------
template< class TP > 
inline BOOL CSPN_Cmn_2DSize<TP>::operator >( const CSPN_Cmn_2DSize<TP> & size2 ) const
{
	if( IsSortKey( 0 ) )//cx first and cy second:
	{
		if( cx() - size2.cx() > FLT_EPSILON )
			return TRUE;
		else if( cx() - size2.cx() < -FLT_EPSILON )
			return FALSE;
		else if( cy() - size2.cy() > FLT_EPSILON )
			return TRUE;
		else 
			return FALSE;
	}
	else//cy first and cx second:
	{
		if( cy() - size2.cy() > FLT_EPSILON )
			return TRUE;
		else if( cy() - size2.cy() < -FLT_EPSILON )
			return FALSE;
		else if( cx() - size2.cx() > FLT_EPSILON )
			return TRUE;
		else 
			return FALSE;
		
	}
};
//--------------------------------------------------------------------------------------------------
template< class TP > 
inline BOOL CSPN_Cmn_2DSize<TP>::operator <( const CSPN_Cmn_2DSize<TP> & size2 ) const
{
	if( IsSortKey( 0 ) )//cx first and cy second:
	{
		if( cx() - size2.cx() < -FLT_EPSILON )
			return TRUE;
		else if( cx() - size2.cx() > FLT_EPSILON )
			return FALSE;
		else if( cy() - size2.cy() < -FLT_EPSILON )
			return TRUE;
		else 
			return FALSE;
	}
	else//cy first and cx second:
	{
		if( cy() - size2.cy() < -FLT_EPSILON )
			return TRUE;
		else if( cy() - size2.cy() > FLT_EPSILON )
			return FALSE;
		else if( cx() - size2.cx() < -FLT_EPSILON )
			return TRUE;
		else
			return FALSE;
	}
};
//--------------------------------------------------------------------------------------------------
template< class TP > 
inline BOOL CSPN_Cmn_2DSize<TP>::operator ==( const CSPN_Cmn_2DSize<TP> & size2 ) const
{
	if( FLT_EQ( cx(), size2.cx() ) && FLT_EQ( cy(), size2.cy() ) )
		return TRUE;
	else 
		return FALSE;
};
//--------------------------------------------------------------------------------------------------
template< class TP > 
inline BOOL CSPN_Cmn_2DSize<TP>::operator != (const CSPN_Cmn_2DSize<TP> & size2 ) const
{
	return !( *this == size2 );
};
//--------------------------------------------------------------------------------------------------
template< class TP >
inline BOOL CSPN_Cmn_2DSize<TP>::operator >=( const CSPN_Cmn_2DSize<TP> & size2 ) const
{
	return !( *this < size2 );
};
//--------------------------------------------------------------------------------------------------
template< class TP >
inline BOOL CSPN_Cmn_2DSize<TP>::operator <=( const CSPN_Cmn_2DSize<TP> & size2 ) const
{
	return !( *this > size2 );
};
//--------------------------------------------------------------------------------------------------
template< class TP >
int CSPN_Cmn_2DSize<TP>::m_iSortKey = 0;//for sorting points;

template< class TP >
CSPN_Cmn_2DSize<TP>::CSPN_Cmn_2DSize()
{
	m_iSortKey  = 0;
	m_arrf2D[0] = 0;
	m_arrf2D[1] = 0;
};
//--------------------------------------------------------------------------------------------------
template< class TP >
CSPN_Cmn_2DSize<TP>::CSPN_Cmn_2DSize( const CSizeInt & size )//copy constructor:
{
	cx( size.cx );
	cy( size.cy );
};
//--------------------------------------------------------------------------------------------------
//template< class TP >
//inline void CSPN_Cmn_2DSize<TP>::Serialize( CSPN_Cmn_Archive & ar )
//{
//	if( ar.IsStoring() )
//	{
//		ar << m_arrf2D[0];
//		ar << m_arrf2D[1];
//	}
//	else
//	{
//		ar >> m_arrf2D[0];
//		ar >> m_arrf2D[1];
//	}
//};
////------------------------------------------------------------------------------
//template< class TP >
//::ifstream & operator >>( ::ifstream & stream, CSPN_Cmn_2DSize<TP> & size )
//{
//	stream >> size.m_arrf2D[0] >> size.m_arrf2D[1];
//	return stream;
//}
////------------------------------------------------------------------------------
//template< class TP >
//::ofstream & operator <<( ::ofstream & stream, const CSPN_Cmn_2DSize<TP> & size )
//{
//	stream << size.m_arrf2D[0] << size.m_arrf2D[1];
//	return stream;
//}
////------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//#ifdef _DEBUG
//template< class TP >
//	void CSPN_Cmn_2DSize<TP>::AssertValid( CSPN_Cmn_2DSize & size )
//	{
//		std::string S;
//		for(int i=0; i<2; i++)
//		{
//			S.Format( "%f",size[i] );
//			std::string SzErr( "#IND" );
//			if( S.FindOneOf( SzErr ) >= 0 )
//			{
//				std::string Stmp;
//				size.TraceFmt( Stmp );
//				::ShowMsg( Stmp );
//				abort();
//			}
//		}
//	};
//
//template< class TP >
//	void CSPN_Cmn_2DSize<TP>::TraceFmt( std::string & StrTrace ) const
//	{
//		StrTrace.Format( "%sSize2D<%f,%f>", StrTrace, cx(), cy());
//	};
//#endif // 

//--------------------------------------------------------------------------------------------------
//**************************************************************************************************
;


template<typename TPNum, typename TPSize>
inline CSPN_Cmn_2DSize<TPSize> operator*(TPNum vNum, const CSPN_Cmn_2DSize<TPSize>& Size)
{
	CSPN_Cmn_2DSize<TPSize> SizeDst(Size);
	SizeDst *= vNum;
	return SizeDst;
};

template<typename TPNum, typename TPSize>
inline CSPN_Cmn_2DSize<TPSize> operator*(const CSPN_Cmn_2DSize<TPSize>& Size, TPNum vNum)
{
	CSPN_Cmn_2DSize<TPSize> SizeDst(Size);
	SizeDst *= vNum;
	return SizeDst;
};


template<typename TPNum, typename TPSize>
inline CSPN_Cmn_2DSize<TPSize> operator/(const CSPN_Cmn_2DSize<TPSize>& Size, TPNum vNum)
{
	CSPN_Cmn_2DSize<TPSize> SizeDst(Size);
	SizeDst /= vNum;
	return SizeDst;
};

template<typename TPNum, typename TPSize>
inline CSPN_Cmn_2DSize<TPSize> operator+(const CSPN_Cmn_2DSize<TPSize>& Size, TPNum vNum)
{
	CSPN_Cmn_2DSize<TPSize> SizeDst(Size);
	SizeDst += vNum;
	return SizeDst;
};

template<typename TPNum, typename TPSize>
inline CSPN_Cmn_2DSize<TPSize> operator+(TPNum vNum, const CSPN_Cmn_2DSize<TPSize>& Size)
{
	CSPN_Cmn_2DSize<TPSize> SizeDst(Size);
	SizeDst += vNum;
	return SizeDst;
};

template<typename TPNum, typename TPSize>
inline CSPN_Cmn_2DSize<TPSize> operator-(const CSPN_Cmn_2DSize<TPSize>& Size, TPNum vNum)
{
	CSPN_Cmn_2DSize<TPSize> SizeDst(Size);
	SizeDst -= vNum;
	return SizeDst;
};

template<typename TPNum, typename TPSize>
inline CSPN_Cmn_2DSize<TPSize> operator-(TPNum vNum, const CSPN_Cmn_2DSize<TPSize>& Size)
{
	CSPN_Cmn_2DSize<TPSize> SizeDst(Size);
	SizeDst *= -1;
	SizeDst -= vNum;
	return SizeDst;
};




typedef CSPN_Cmn_2DSize<int>				Sz2D_Int;
typedef CSPN_Cmn_2DSize<unsigned int>	Sz2D_UInt;

typedef CSPN_Cmn_2DSize<short>			Sz2D_Sht;
typedef CSPN_Cmn_2DSize<unsigned short>	Sz2D_USht;

typedef CSPN_Cmn_2DSize<char>			Sz2D_Char;
typedef CSPN_Cmn_2DSize<unsigned char>	Sz2D_UChar;

typedef CSPN_Cmn_2DSize<float>			Sz2D_Flt;
typedef CSPN_Cmn_2DSize<double>			Sz2D_Dbl;

typedef CSPN_Cmn_2DSize<int>				Sz2D_Idx;



#endif //  // !defined(SPN_Cmn_2DSIZE_H__INCLUDED_
