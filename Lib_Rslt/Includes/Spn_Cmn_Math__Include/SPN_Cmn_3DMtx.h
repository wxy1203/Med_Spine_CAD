// SPN_Cmn_3DMtx.h: interface for the CSPN_Cmn_3DMtx class.
//
//////////////////////////////////////////////////////////////////////

#ifndef SPN_Cmn_3DMtx_H__INCLUDED_
#define SPN_Cmn_3DMtx_H__INCLUDED_

#pragma once

//#include "SPN_Cmn_LUT_Arr.h"
#include "SPN_Cmn_3DMtx_Grid.h"
#include "SPN_Cmn_AttrSet.h"
#include "SPN_Cmn_3DPoint.h"
#include "SPN_Cmn_LUT_Arr.h"

#include <iostream>
#include <sstream>

//---------------------------------------------------------------------------------------

template<typename TP_Crd=float>
class CSPN_Cmn_3DMtx_Base : public CSPN_Cmn_3DMtx_Grid<TP_Crd>
{
	friend class CSPN_Cmn_3DMtx_FStreamer;
public:
	CSPN_Cmn_3DMtx_Base(){}
	virtual ~CSPN_Cmn_3DMtx_Base(){}
	//-----------------------------------------------------------------------------------

public:
	virtual void*	GetMemBgn_Slice		(const INT64 iZ) = 0;
	virtual void*	GetMemBgn_SliceRow	(const INT64 iZ, INT64 iY) = 0;

	virtual int		GetMemSize_Vox() const =  0;
	inline int		GetMemSize_Row() const { return GetMemSize_Vox() * (this->GetSize_X()); }
	inline int		GetMemSize_Slc() const { return GetMemSize_Row() * (this->GetSize_Y()); }
	inline int		GetMemSize_Mtx() const { return GetMemSize_Slc() * (this->GetSize_Z()); }
	//-----------------------------------------------------------------------------------

	virtual int		GetVoxTypeID__InnerDataType() const =  0;
	int				GetVoxTypeID_User() const			{ return this->m_iVoxTP_User; }
	void			SetVoxTypeID_User(int iVoxTP_Usr)	{ this->m_iVoxTP_User = iVoxTP_Usr; }

	int				GetVoxTypeID() const				{ return GetVoxTypeID_User(); }
	void			SetVoxTypeID(int iVoxTP_Usr)		{  SetVoxTypeID_User(iVoxTP_Usr); }
	//-----------------------------------------------------------------------------------

	int				Get_nChannel() const	 { return this->m_nChannel; }
	void			Set_nChannel(int nChann) { this->m_nChannel = nChann; }
	//-----------------------------------------------------------------------------------

	virtual void	CopyMtx(const CSPN_Cmn_3DMtx_Base<>& MtxSrcI) = 0;

	virtual void	VoxMem_Attatch(void* pVoxBuf, const INT64 nX, const INT64 nY, const INT64 nZ) =  0;
	virtual void	VoxMem_Attatch(void* pVoxBuf, const SSPN_Cmn_3DPoint<int> nXYZ) =  0;
	virtual void	VoxMem_Attatch(void* pVoxBuf, const SSPN_Cmn_3DPoint<UINT> nXYZ) =  0;
	virtual void	VoxMem_Detatch() =  0;

	//virtual void	Swap(CSPN_Cmn_3DMtx_Base<>& Mtx) =  0;
	//-----------------------------------------------------------------------------------

	virtual void	ZeroMem		() =  0;
	virtual void	Reset_All	() =  0;
	virtual void	Reset_Mem	() =  0;
	//-----------------------------------------------------------------------------------

	//virtual void	CopyMtxTo(SSPN_Cmn_3DPoint<int> P3IdxBgnSrc,				
	//						  SSPN_Cmn_3DPoint<int> P3IdxBgnDst,	
	//						  SSPN_Cmn_3DPoint<int> P3_Count,
	//						  CSPN_Cmn_3DMtx_Base<TP_Crd>& MtxDst) const =  0;

	//virtual CSPN_Cmn_3DMtx_Base<>* CloneMtx() =  0;

	virtual const void*	GetVoxMem_Bs() const = 0;
public:
	//-----------------------------------------------------------------------------------

protected:
	int						m_iVoxTP_User = -1;	
	static int				m_nChannel;

public:
	CSPN_Cmn_AttrSet			m_AttrSet;
};

template<typename TP_Crd>
int CSPN_Cmn_3DMtx_Base<TP_Crd>::m_nChannel = -1;

//

template<typename TP_Vox, typename TP_Crd = float>
class CSPN_Cmn_3DMtx : public CSPN_Cmn_3DMtx_Base<TP_Crd>
{
	friend class CSPN_Cmn_3DMtx_FStreamer;
public:
	CSPN_Cmn_3DMtx()
	{
		Reset_All();
	};
	~CSPN_Cmn_3DMtx()
	{
		Reset_All();
	};

protected:
	CSPN_Cmn_3DMtx(const CSPN_Cmn_3DMtx& rMtx) {};
	const CSPN_Cmn_3DMtx<TP_Vox, TP_Crd>& operator=(const CSPN_Cmn_3DMtx& rMtx) { return this; };

public:
	virtual int GetVoxTypeID__InnerDataType() const
	{
		return GetID_InnerDataType<TP_Vox>();
	}

	//---------------------------------------------------------------------------

	virtual bool Set_nXYZ(INT64 nX, INT64 nY, INT64 nZ)
	{
		Reset_All();
		assert(0 == this->m_nVoxTotal);

		CSPN_Cmn_3DMtx_Grid<TP_Crd>::Set_nXYZ(nX, nY, nZ);
		assert(nX*nY*nZ == this->m_nVoxTotal);

		this->m_pVoxMem = new TP_Vox[this->m_nVoxTotal];
		this->m_bVoxBuf_Hooked = false;
		//try
		//{
		//	this->m_pVoxMem = new TP_Vox[this->m_nVoxTotal];
		//
		//	adkfj;asdkf;ladfaj
		//		();a'
		//		dfa
		//		f
		//}
		//catch( exception )
		//{
		//}
		VoxMem_Construct_TmpAttr();

		return true;
	};

	virtual bool Set_nXYZ3(int nX, int nY, int nZ) { return Set_nXYZ(nX, nY, nZ); }
	//virtual bool Set_nXYZ(const int nXYZ[3]);
	//virtual bool Set_nXYZ(const SPnt3D_Int& P3Int);
	//virtual bool Set_nXYZ(INT64 nXYZ[3]);

	bool VoxMem_New(const INT64 nX, const INT64 nY, const INT64 nZ)
	{
		Set_nXYZ(nX, nY, nZ);
	};
	bool VoxMem_New(const SSPN_Cmn_3DPoint<int> nXYZ) { return VoxMem_New(nXYZ[0], nXYZ[1], nXYZ[2]); }
	bool VoxMem_New(const SSPN_Cmn_3DPoint<UINT> nXYZ) { return VoxMem_New(nXYZ[0], nXYZ[1], nXYZ[2]); }
	//---------------------------------------------------------------------------

	virtual void VoxMem_Attatch(void* pVoxBuf, const INT64 nX, const INT64 nY, const INT64 nZ)
	{
		Reset_All();
		assert(0 == this->m_nVoxTotal);

		CSPN_Cmn_3DMtx_Grid<TP_Crd>::Set_nXYZ(nX, nY, nZ);
		assert(nX*nY*nZ == this->m_nVoxTotal);
		assert(nullptr == m_pVoxMem);

		//this->m_pVoxMem = new TP_Vox[this->m_nVoxTotal];
		m_pVoxMem = (TP_Vox*)pVoxBuf;
		m_bVoxBuf_Hooked = true;

		VoxMem_Construct_TmpAttr();
	};
	virtual void VoxMem_Attatch(void* pVoxBuf, const SSPN_Cmn_3DPoint<int> nXYZ) { VoxMem_Attatch(pVoxBuf, nXYZ[0], nXYZ[1], nXYZ[2]); }
	virtual void VoxMem_Attatch(void* pVoxBuf, const SSPN_Cmn_3DPoint<UINT> nXYZ) { VoxMem_Attatch(pVoxBuf, nXYZ[0], nXYZ[1], nXYZ[2]); }
	virtual void VoxMem_Detatch()
	{
		Reset_All();
	};
	//---------------------------------------------------------------------------
	void Swap(CSPN_Cmn_3DMtx<TP_Vox>& Mtx)
	{
		//CSPN_Cmn_3DMtx<TP_Vox>& rMtxTP = (dynamic_cast<CSPN_Cmn_3DMtx<TP_Vox>>(&MtxBs));
		//CSPN_Cmn_3DMtx<TP_Vox>& rMtxTP = (dynamic_cast<CSPN_Cmn_3DMtx<TP_Vox>&>(MtxBs));
		//assert(nullptr != (&rMtxTP)); 
		CSPN_Cmn_3DMtx<TP_Vox>& rMtxTP = Mtx;

		::Exchange(m_pVoxMem, rMtxTP.m_pVoxMem);
		this->VoxMem_Construct_TmpAttr();
		rMtxTP.VoxMem_Construct_TmpAttr();

		::Exchange(this->m_nX, rMtxTP.m_nX);
		::Exchange(this->m_nY, rMtxTP.m_nY);
		::Exchange(this->m_nZ, rMtxTP.m_nZ);
		this->VoxGeo_Construct_TmpAttr();
		rMtxTP.VoxGeo_Construct_TmpAttr();

		::Exchange(this->m_iVoxTP_User, rMtxTP.m_iVoxTP_User);

		assert(&(this->m_nChannel) == &(rMtxTP.m_nChannel));
		this->m_AttrSet.Swap(rMtxTP.m_AttrSet);
	};

	//---------------------------------------------------------------------------

	virtual inline void VoxMem_Set(const TP_Vox v)
	{
		int nVox = this->GetSize_Mtx();
		for (int i = 0; i < nVox; i++)
		{
			m_pVoxMem[i] = v;
		}
	}
	virtual void ZeroMem() { memset(this->m_pVoxMem, 0, this->m_nVoxTotal * sizeof(TP_Vox)); }
	virtual void Reset_Mem()
	{
		if (m_pVoxMem)
		{
			if (m_bVoxBuf_Hooked)
			{
				m_pVoxMem = nullptr;
				m_bVoxBuf_Hooked = false;
			}
			else
			{
				delete[]m_pVoxMem;
				m_pVoxMem = nullptr;
			}
		}

		m_nBytePerSlc = 0;
		m_ArrPtrVoxHead_Z.resize(0);
	};

	virtual void Reset_All()
	{
		CSPN_Cmn_3DMtx_Grid<TP_Crd>::Reset_All();
		Reset_Mem();
	};

protected:
	void VoxMem_Construct_TmpAttr()
	{
		m_nBytePerSlc = sizeof(TP_Vox)*(this->GetSize_Slc());

		m_ArrPtrVoxHead_Z.resize(this->GetSize_Z());
		for (int k = 0; k < this->GetSize_Z(); k++)
		{

			TP_Vox* pSlc = m_pVoxMem + k * (this->GetSize_Slc());
			m_ArrPtrVoxHead_Z[k] = pSlc;
		}
	};

public:
	//---------------------------------------------------------------------------
	//virtual CSPN_Cmn_3DMtx_Base<>*	CloneMtx();

	inline		 TP_Vox*&	GetVoxMem_Ref() { return m_pVoxMem; }
	virtual	const void*		GetVoxMem_Bs()	const { return m_pVoxMem; }
	virtual		 TP_Vox*	GetVoxMem()		const { return m_pVoxMem; }
	inline const TP_Vox*	GetVoxMem(const INT64 iX, const INT64 iY, const INT64 iZ) const { assert((*this).IsIdx3_Valid(iX, iY, iZ));	return this->GetSliceRowBuf(iZ, iY) + iX; }
	inline		 TP_Vox*	GetVoxMem(const INT64 iX, const INT64 iY, const INT64 iZ) { assert((*this).IsIdx3_Valid(iX, iY, iZ));	return this->GetSliceRowBuf(iZ, iY) + iX; }

	//---------------------------------------------------------------------------
	inline const TP_Vox&	GetVox(const INT64 iVox) const { assert(iVox < this->m_nVoxTotal && iVox >= 0); 	return this->m_pVoxMem[iVox]; }
	inline const TP_Vox&	GetVox(const INT64 iX, const INT64 iY, const INT64 iZ)	const { assert((*this).IsIdx3_Valid(iX, iY, iZ));		return (*this).GetVox((*this).GetVoxID(iX, iY, iZ)); }
	inline const TP_Vox&	GetVox(const SPnt3D_Int& P3DIdx) const { return (*this).GetVox(P3DIdx[0], P3DIdx[1], P3DIdx[2]); }
	inline const TP_Vox&	GetVox(const SPnt3D_Sht& P3DIdx) const { return (*this).GetVox(P3DIdx[0], P3DIdx[1], P3DIdx[2]); }

	inline		 TP_Vox&	GetVox(const INT64 iVox) { assert(iVox < this->m_nVoxTotal && iVox >= 0); 	return this->m_pVoxMem[iVox]; }
	inline		 TP_Vox&	GetVox(const INT64 iX, const INT64 iY, const INT64 iZ) { assert((*this).IsIdx3_Valid(iX, iY, iZ));		return (*this).GetVox((*this).GetVoxID(iX, iY, iZ)); }
	inline		 TP_Vox&	GetVox(const SPnt3D_Int& P3DIdx) { return (*this).GetVox(P3DIdx[0], P3DIdx[1], P3DIdx[2]); }
	inline		 TP_Vox&	GetVox(const SPnt3D_Sht& P3DIdx) { return (*this).GetVox(P3DIdx[0], P3DIdx[1], P3DIdx[2]); }

	inline const TP_Vox&	GetVox_NearIdx(Pnt3D_Flt P3D_fIdx) const;
	inline		 TP_Vox&	GetVox_NearIdx(Pnt3D_Flt P3D_fIdx);

	inline const TP_Vox&	GetVoxAtCoord_IntrpNearIdx(const float fX, const float fY, const float fZ) const;
	inline const TP_Vox&	GetVoxAtCoord_IntrpNearIdx(Pnt3D_Flt P3D_fIdx) const { return (*this).GetVoxAtCoord_IntrpNearIdx(P3D_fIdx[0], P3D_fIdx[1], P3D_fIdx[2]); }

	inline		 TP_Vox		GetVoxAtCoord_IntrpXYNearZLn(const float fX, const float fY, const float fZ) const;
	inline		 TP_Vox		GetVoxAtCoord_IntrpTriLn(const float fX, const float fY, const float fZ) const;
	inline		 TP_Vox		GetVoxAtCoord_IntrpTriLn(Pnt3D_Flt P3D_fIdx) const { return (*this).GetVoxAtCoord_IntrpTriLn(P3D_fIdx[0], P3D_fIdx[1], P3D_fIdx[2]); }
	//---------------------------------------------------------------------------

	inline void LimitIdx_to_Valid(int& iX, int& jY, int& kZ) const;
	inline void LimitIdx_to_Valid(SPnt3D_Int& P3D_Idx) const;

	inline void LimitIdx_to_Valid_X(int& iX) const { CutIntoRange<int>(iX, 0, this->m_nX - 1); }
	inline void LimitIdx_to_Valid_Y(int& jY) const { CutIntoRange<int>(jY, 0, this->m_nY - 1); }
	inline void LimitIdx_to_Valid_Z(int& kZ) const { CutIntoRange<int>(kZ, 0, this->m_nZ - 1); }
	//---------------------------------------------------------------------------

	//TP_Vox GetVoxAtCoord_IntrpSparceWeight_SqDist	(const float fX, const float fY, const float fZ,
	//												 CSPN_Cmn_BitMtx& MtxFlg,
	//												 INT64 nVoxSrcMin,
	//												 TP_Vox vDefault) const;
	//---------------------------------------------------------------------------

	inline void SetVox(const INT64 iVox, const TP_Vox& v);
	inline void SetVox(const INT64 iX, const INT64 iY, const INT64 iZ, const TP_Vox& v)
	{
		TP_Vox* pVox = this->m_ArrPtrVoxHead_Z[iZ] + iY * this->GetSize_X() + iX;
		*pVox = v;
	}
	inline void SetVox(SPnt3D_Int&  P3DIdx, const TP_Vox& v) { SetVox(P3DIdx[0], P3DIdx[1], P3DIdx[2], v); };
	inline void SetVox(SPnt3D_Sht&  P3DIdx, const TP_Vox& v) { SetVox(P3DIdx[0], P3DIdx[1], P3DIdx[2], v); };
	inline void SetVox(SPnt3D_Char& P3DIdx, const TP_Vox& v) { SetVox(P3DIdx[0], P3DIdx[1], P3DIdx[2], v); };
	inline void SetVox(SPnt3D_Flt&  P3DIdx, const TP_Vox& v) { SetVox(fRound(P3DIdx[0]), fRound(P3DIdx[1]), fRound(P3DIdx[2]), v); };
	inline void SetVox(SPnt3D_Dbl&  P3DIdx, const TP_Vox& v) { SetVox(fRound(P3DIdx[0]), fRound(P3DIdx[1]), fRound(P3DIdx[2]), v); };
	inline void SetVox_All(TP_Vox vVox)
	{
		int nVox = this->GetSize_Mtx();
#pragma omp parallel for
		for (int i = 0; i < nVox; i++)
		{
			m_pVoxMem[i] = vVox;
		}
	}

	inline void SetVox_All_CubInOut(TP_Vox vVoxIn, TP_Vox vVoxOut, Cub3D_Int Cub);
	inline void SetVox_All_CubIn(TP_Vox vVox, Cub3D_Int Cub);
	inline void SetVox_All_CubOut(TP_Vox vVox, Cub3D_Int Cub);

	inline void SetVox_byReplaceVal_inRange(TP_Vox vDst, TP_Vox vSrcMin, TP_Vox vSrcMax);
	inline void SetVox_byReplaceVal(TP_Vox vDst, TP_Vox vSrc, double pfTol_Src = nullptr);
	//---------------------------------------------------------------------------

	virtual int				GetMemSize_Vox() const { return sizeof(TP_Vox); }
	virtual void*			GetMemBgn_Slice(const INT64 iZ) { assert(iZ < this->m_nZ); return this->m_ArrPtrVoxHead_Z[iZ]; }
	virtual void*			GetMemBgn_SliceRow(const INT64 iZ, INT64 iY)
	{
		assert(iZ < this->m_nZ);
		return this->m_ArrPtrVoxHead_Z[iZ] + this->m_Arr_nVoxPreRowsInSlc_Y[iY];
	}

	inline TP_Vox*			GetSliceBuf(const INT64 iZ) { assert(iZ < this->m_nZ); return this->m_ArrPtrVoxHead_Z[iZ]; }
	inline TP_Vox*			GetSliceRowBuf(const INT64 iZ, INT64 iY) { assert(iZ < this->m_nZ); return this->m_ArrPtrVoxHead_Z[iZ] + this->m_Arr_nVoxPreRowsInSlc_Y[iY]; }

	inline const TP_Vox*	GetSliceBuf(const INT64 iZ) 			const { assert(iZ < this->m_nZ); return this->m_ArrPtrVoxHead_Z[iZ]; }
	inline const TP_Vox*	GetSliceRowBuf(const INT64 iZ, INT64 iY) 	const { assert(iZ < this->m_nZ); return this->m_ArrPtrVoxHead_Z[iZ] + this->m_Arr_nVoxPreRowsInSlc_Y[iY]; }
	//---------------------------------------------------------------------------

	inline bool GetSlice_Z_XpYp_3D(CSPN_Cmn_3DMtx<TP_Vox>& MtxDst, INT64 kSlcDst, INT64 kSlcSrc) const

	{
		//-----------------1----------------数据准备
		if (kSlcSrc < 0 || kSlcSrc >= this->GetSize_Z())
		{
			return false;
		}
		//inline void MapTo_GreyImg_LoUp(QImage& rImg, float vLow_to_0, float vUp_to_255) const



		if (this->GetSize_X() != MtxDst.GetSize_X() ||
			this->GetSize_Y() != MtxDst.GetSize_Y())
		{
			MtxDst.Set_nXYZ(this->GetSize_X(), this->GetSize_Y(), kSlcDst + 1);
			MtxDst.SetVox_All(0);
		}
		else
		{
			if (kSlcDst < 0 || kSlcDst >= MtxDst.GetSize_Z())
			{
				MtxDst.Set_nXYZ(this->GetSize_X(), this->GetSize_Y(), kSlcDst + 1);
				MtxDst.SetVox_All(0);
			}
		}

		int nXY = MtxDst.GetSize_Slc();
		TP_Vox* pSlcDst = MtxDst.GetSliceBuf(kSlcDst);
		const TP_Vox* pSlcSrc = this->GetSliceBuf(kSlcSrc);



		::memcpy(pSlcDst, pSlcSrc, nXY * sizeof(TP_Vox));
		return true;
	};


	void GetSlice_Y_XpZn_3D(CSPN_Cmn_3DMtx<TP_Vox>& MtxDst, INT64 kZDst, INT64 jYSrc) const;
	void GetSlice_Y_XpZp_3D(CSPN_Cmn_3DMtx<TP_Vox>& MtxDst, INT64 kZDst, INT64 jYSrc) const
	{
		assert(kZDst >= 0 && kZDst < MtxDst.GetSize_Z());
		::CutIntoRange<INT64>(kZDst, 0, MtxDst.GetSize_Z() - 1);
		assert(jYSrc >= 0 && jYSrc < this->GetSize_Y());
		::CutIntoRange<INT64>(jYSrc, 0, this->GetSize_Y() - 1);

#pragma omp parallel for
		for (int jD = 0; jD < MtxDst.GetSize_Y(); jD++)
		{
			//int jS = kZDst;
			int kS = jD;

			TP_Vox* pDst = MtxDst.GetSliceRowBuf(kZDst, jD);
			const TP_Vox* pSrc = this->GetSliceRowBuf(kS, jYSrc);
			::memcpy(pDst, pSrc, this->GetMemSize_Row());

			//for (iD = 0; iD < MtxDst.GetSize_Y(); iD++)
			//{
			//	int iS = iD;
			//	MtxDst.SetVox(iD, jD, kZDst, this->GetVox(iS, jS, kS));
			//}

		}
	}
	void GetSlice_Y_ZpXp_3D(CSPN_Cmn_3DMtx<TP_Vox>& MtxDst, INT64 kZDst, INT64 jYSrc) const;

	void GetSlice_X_YpZp_3D(CSPN_Cmn_3DMtx<TP_Vox>& MtxDst, INT64 kZDst, INT64 iXSrc) const
	{
		assert(kZDst >= 0 && kZDst < MtxDst.GetSize_Z());
		assert(iXSrc >= 0 && iXSrc < this->GetSize_X());

#pragma omp parallel for
		for (int jD = 0; jD < MtxDst.GetSize_Y(); jD++)
		{
			TP_Vox* pDst = MtxDst.GetSliceRowBuf(kZDst, jD);

			int jYSrcBgn = 0;
			int kZSrc = jD;
			const TP_Vox* pSrc = (*this).GetSliceRowBuf(kZSrc, jYSrcBgn) + iXSrc;
			for (int iD = 0; iD < MtxDst.GetSize_X(); iD++)
			{
				//int iS = iXSrc;
				//int jS = iD;
				//int kS = jD;
				//TP_Vox vVox = this->GetVox(iS, jS, kS);
				//MtxDst.SetVox(iD, jD, kZDst, vVox);
				pDst[iD] = *pSrc;
				pSrc += (this->GetSize_X());
			}
		}
	};


	void GetSlice_X_YnZn_3D(CSPN_Cmn_3DMtx<TP_Vox>& MtxDst, INT64 kZDst, INT64 iXSrc) const;
	void GetSlice_X_YnZp_3D(CSPN_Cmn_3DMtx<TP_Vox>& MtxDst, INT64 kZDst, INT64 iXSrc) const;

	void GetMtx_RotVox_XZPos_ZYPos_YXPos(CSPN_Cmn_3DMtx<TP_Vox>& MtxDst) const;

	void GetDRR_Ax(CSPN_Cmn_3DMtx<TP_Vox>& MtxDst)const
	{
		if (this->GetSize_X() != MtxDst.GetSize_X() ||
			this->GetSize_Y() != MtxDst.GetSize_Y())
		{
			MtxDst.Set_nXYZ(this->GetSize_X(), this->GetSize_Y(), 1);
		}

		CSPN_Cmn_3DMtx<double> MtxDstTmp;
		{
			MtxDstTmp.Set_nXYZ(this->GetSize_X(), this->GetSize_Y(), 1);
		}
		MtxDstTmp.SetVox_All(0);


		for (int k = 0; k < this->GetSize_Z(); k++)
		{
			for (int j = 0; j < this->GetSize_Y(); j++)
			{
				/****/double* pDst = MtxDstTmp.GetSliceRowBuf(0, j);
				const TP_Vox* pSrc = this->GetSliceRowBuf(k, j);
				for (int i = 0; i < this->GetSize_X(); i++)
				{
					//MtxDst.GetVox(i, j, 0) += this->GetVox(i, j, k);
					(*pDst++) += (*pSrc++);
				}
			}
		}
		double fK = 1.0 / this->GetSize_Z();
		for (int iVox = 0; iVox < MtxDstTmp.GetSize_Mtx(); iVox++)
		{
			MtxDst.GetVox(iVox) = MtxDstTmp.GetVox(iVox)*fK;
		}
	};

	void GetDRR_Co(CSPN_Cmn_3DMtx<TP_Vox>& MtxDst) const
	{
		CSPN_Cmn_3DMtx<double> MtxDstTmp;
		{
			MtxDst.Set_nXYZ(this->GetSize_X(), this->GetSize_Z(), 1);
			MtxDstTmp.Set_nXYZ(this->GetSize_X(), this->GetSize_Z(), 1);
			MtxDstTmp.SetVox_All(0);
		}

		for (int jS = 0; jS < this->GetSize_Y(); jS++)
		{
#pragma omp parallel for
			for (int jD = 0; jD < MtxDstTmp.GetSize_Y(); jD++)
			{
				//int jS = kZDst;
				int kS = jD;

				double* pDst = MtxDstTmp.GetSliceRowBuf(0, jD);
				const TP_Vox* pSrc = this->GetSliceRowBuf(kS, jS);

				for (int iD = 0; iD < MtxDstTmp.GetSize_X(); iD++)
				{
					int iS = iD;
					//MtxDstTmp.GetVox(iD, jD, kZDst)= this->GetVox(iS, jS, kS));
					(*pDst++) += (*pSrc++);
				}
			}
		}

		double fK = 1.0 / this->GetSize_Y();
		for (int iVox = 0; iVox < MtxDstTmp.GetSize_Mtx(); iVox++)
		{
			MtxDst.GetVox(iVox) = MtxDstTmp.GetVox(iVox)*fK;
		}
	}

	void GetDRR_Sa(CSPN_Cmn_3DMtx<TP_Vox>& MtxDst) const
	{
		CSPN_Cmn_3DMtx<double> MtxDstTmp;
		{
			MtxDst		.Set_nXYZ(this->GetSize_Y(), this->GetSize_Z(), 1);
			MtxDstTmp	.Set_nXYZ(this->GetSize_Y(), this->GetSize_Z(), 1);
			MtxDstTmp	.SetVox_All(0);
		}
		for (int iS = 0; iS < this->GetSize_X(); iS++)
		{
#pragma omp parallel for
			for (int jD = 0; jD < MtxDstTmp.GetSize_Y(); jD++)
			{
				double* pDst = MtxDstTmp.GetSliceRowBuf(0, jD);

				int jYSrcBgn = 0;
				int kZSrc = jD;
				const TP_Vox* pSrc = (*this).GetSliceRowBuf(kZSrc, jYSrcBgn) + iS;
				for (int iD = 0; iD < MtxDstTmp.GetSize_X(); iD++)
				{
					//int iS = iXSrc;
					//int jS = iD;
					//int kS = jD;
					//TP_Vox vVox = this->GetVox(iS, jS, kS);
					//MtxDst.SetVox(iD, jD, kZDst, vVox);
					(*pDst++) += *pSrc;
					pSrc += (this->GetSize_X());
				}
			}
		}
		double fK = 1.0 / this->GetSize_X();
		for (int iVox = 0; iVox < MtxDstTmp.GetSize_Mtx(); iVox++)
		{
			MtxDst.GetVox(iVox) = MtxDstTmp.GetVox(iVox)*fK;
		}
	};

	void GetMaxIP_Ax(CSPN_Cmn_3DMtx<TP_Vox>& MtxDst)const
	{
		MtxDst;
		{
			MtxDst.Set_nXYZ(this->GetSize_X(), this->GetSize_Y(), 1);
			MtxDst.SetVox_All(SHORT_MIN);
		}

		for (int k = 0; k < this->GetSize_Z(); k++)
		{
			for (int j = 0; j < this->GetSize_Y(); j++)
			{
				/****/TP_Vox* pDst = MtxDst.GetSliceRowBuf(0, j);
				const TP_Vox* pSrc = this->GetSliceRowBuf(k, j);
				for (int i = 0; i < this->GetSize_X(); i++)
				{
					//MtxDst.GetVox(i, j, 0) += this->GetVox(i, j, k);
					if (pDst[i] < pSrc[i])
					{
						pDst[i] = pSrc[i];
					}
				}
			}
		}
	};

	void GetMaxIP_Co(CSPN_Cmn_3DMtx<TP_Vox>& MtxDst) const
	{
		MtxDst;
		{
			MtxDst.Set_nXYZ(this->GetSize_X(), this->GetSize_Z(), 1);
			MtxDst.SetVox_All(SHORT_MIN);
		}

		for (int jS = 0; jS < this->GetSize_Y(); jS++)
		{
#pragma omp parallel for
			for (int jD = 0; jD < MtxDst.GetSize_Y(); jD++)
			{
				//int jS = kZDst;
				int kS = jD;

				TP_Vox* pDst = MtxDst.GetSliceRowBuf(0, jD);
				const TP_Vox* pSrc = this->GetSliceRowBuf(kS, jS);

				for (int iD = 0; iD < MtxDst.GetSize_X(); iD++)
				{
					int iS = iD;
					//MtxDstTmp.GetVox(iD, jD, kZDst)= this->GetVox(iS, jS, kS));
					if (pDst[iD] < pSrc[iS])
					{
						pDst[iD] = pSrc[iS];
					}
				}
			}
		}
	}

	void GetMaxIP_Sa(CSPN_Cmn_3DMtx<TP_Vox>& MtxDst) const
	{
		MtxDst;
		{
			MtxDst.Set_nXYZ(this->GetSize_Y(), this->GetSize_Z(), 1);
			MtxDst.SetVox_All(SHORT_MIN);
		}
		for (int iS = 0; iS < this->GetSize_X(); iS++)
		{
#pragma omp parallel for
			for (int jD = 0; jD < MtxDst.GetSize_Y(); jD++)
			{
				TP_Vox* pDst = MtxDst.GetSliceRowBuf(0, jD);

				int jS = 0;
				int kS = jD;
				const TP_Vox* pSrc = (*this).GetSliceRowBuf(kS, jS) + iS;
				for (int iD = 0; iD < MtxDst.GetSize_X(); iD++)
				{
					//int iS = iXSrc;
					//int jS = iD;
					//int kS = jD;
					//TP_Vox vVox = this->GetVox(iS, jS, kS);
					//MtxDst.SetVox(iD, jD, kZDst, vVox);
					if (pDst[iD] < *pSrc)
					{
						pDst[iD] = *pSrc;
					}
					pSrc += (this->GetSize_X());
				}
			}
		}
	};

	//---------------------------------------------------------------------------

	void GetSliceRandomParallelX(CSPN_Cmn_3DMtx<TP_Vox>& MtxSection,
		const SSPN_Cmn_3DPoint<float>P3Idx1,
		const SSPN_Cmn_3DPoint<float> P3Idx2
		/*CSizeInt& SzBmpRandom_PixUnit*/) const
	{
		int nW = this->GetSize_X();
		float fH = P3Idx1.GetDistTo(P3Idx2);
		int nH = fRound(fH);
		MtxSection.Set_nXYZ(nW, nH, 1);
		if (MtxSection.GetMemSize_Mtx() == 0)
		{
			return;
		}
			
		float fDjS = P3Idx2.y() - P3Idx1.y();
		float fDkS = P3Idx2.z() - P3Idx1.z();

#pragma omp parallel for
		for (int jD = 0; jD < nH; jD++)
		{
			float fKjk = float(jD) / float(nH);

			float fjS = P3Idx1.y() + fKjk * fDjS;
			float fkS = P3Idx1.z() + fKjk * fDkS;

			::CutIntoRange<float>(fjS,0,  this->GetSize_Y() - 1);
			::CutIntoRange<float>(fkS,0,  this->GetSize_Z() - 1);

			TP_Vox* pVx_Dst = MtxSection.GetSliceRowBuf(0, jD);
			for (int iD = 0; iD < nW; iD++)
			{
				int iS = iD;
				pVx_Dst[iD] = GetVox(iS, fjS, fkS);
			}
		}
	}

	void GetSliceRandomParallelY(CSPN_Cmn_3DMtx<TP_Vox>& MtxSection,
								const SSPN_Cmn_3DPoint<float>& P3Idx1,
								const SSPN_Cmn_3DPoint<float>& P3Idx2
								/* CSizeInt& SzBmpRandom_PixUnit*/) const
	{
		int nW = this->GetSize_X();
		float fH = P3Idx1.GetDistTo(P3Idx2);
		int nH = fRound(fH);
		MtxSection.Set_nXYZ(nW, nH, 1);
		if (MtxSection.GetMemSize_Mtx() == 0)
		{
			return;
		}

		float fDiS = P3Idx2.x() - P3Idx1.x();
		float fDkS = P3Idx2.z() - P3Idx1.z();

#pragma omp parallel for
		for (int jD = 0; jD < nH; jD++)
		{
			float fKik = float(jD) / float(nH);

			float fiS = P3Idx1.x() + fKik * fDiS;
			float fkS = P3Idx1.z() + fKik * fDkS;

			::CutIntoRange<float>(fiS, 0, this->GetSize_X() - 1);
			::CutIntoRange<float>(fkS, 0, this->GetSize_Z() - 1);

			TP_Vox* pVx_Dst = MtxSection.GetSliceRowBuf(0, jD);
			for (int iD = 0; iD < nW; iD++)
			{
				int jS = iD;
				pVx_Dst[iD] = GetVox(fiS, jS, fkS);
			}
		}
	}

	void GetSliceRandomParallelZ(CSPN_Cmn_3DMtx<TP_Vox>& MtxSection, 
								const SSPN_Cmn_3DPoint<float>& P3Idx1,
								const SSPN_Cmn_3DPoint<float>& P3Idx2
								/* CSizeInt& SzBmpRandom_PixUnit*/) const

	{
		int nW = this->GetSize_Z();
		float fH = P3Idx1.GetDistTo(P3Idx2);
		int nH = fRound(fH);
		MtxSection.Set_nXYZ(nW, nH, 1);
		if (MtxSection.GetMemSize_Mtx() == 0)
		{
			return;
		}

		float fDiS = P3Idx2.x() - P3Idx1.x();
		float fDjS = P3Idx2.y() - P3Idx1.y();

#pragma omp parallel for
		for (int jD = 0; jD < nH; jD++)
		{
			float fKij = float(jD) / float(nH);

			float fiS = P3Idx1.x() + fKij * fDiS;
			float fjS = P3Idx1.y() + fKij * fDjS;

			::CutIntoRange<float>(fiS, 0, this->GetSize_X() - 1);
			::CutIntoRange<float>(fjS, 0, this->GetSize_Y() - 1);

			TP_Vox* pVx_Dst = MtxSection.GetSliceRowBuf(0, jD);
			for (int iD = 0; iD < nW; iD++)
			{
				int kS = iD;
				pVx_Dst[iD] = GetVox(fiS, fjS, kS);
			}
		}
	};
	//---------------------------------------------------------------------------
	inline void SetSlice_Z(const INT64 iZ, const CSPN_Cmn_3DMtx<TP_Vox, TP_Crd>& VoxSlc);
	//inline void SetSlice_Z(const INT64 iZ, const SPN_Cmn_Matrix<TP_Vox>& Mtx);

	CSPN_Cmn_3DMtx_Grid<TP_Crd>&	GetGrid();
	void							GetGrid(CSPN_Cmn_3DMtx_Grid<TP_Crd>& MtxGridDst);
	//---------------------------------------------------------------------------
	void VoxMem_Copy(TP_Vox const* pVoxMem, const int nX, const int nY, const int nZ);
	//void VoxMem_Copy(const SPN_Cmn_Matrix<TP_Vox>& Mtx, const int iZ);
	void VoxMem_CopyAt(TP_Vox const* pVoxMem, const int iZBgn, const int nZCount);

	void CopyMtx(const CSPN_Cmn_3DMtx_Base<>& MtxSrcI) override
	{
		const CSPN_Cmn_3DMtx<TP_Vox>* pMtxSrc = dynamic_cast<const CSPN_Cmn_3DMtx<TP_Vox>*>(&MtxSrcI);
		if (nullptr == pMtxSrc)
		{
			assert(false);
			return;
		}
		this->CopyGrid(*pMtxSrc);
		::memcpy(this->m_pVoxMem, pMtxSrc->m_pVoxMem, sizeof(TP_Vox)*(this->GetMemSize_Mtx()));
	};

	void PlusEQ(SSPN_Cmn_3DPoint<int> P3IdxBgnSrc,
				SSPN_Cmn_3DPoint<int> P3IdxBgnDst,
				SSPN_Cmn_3DPoint<int> P3_Count,
				const CSPN_Cmn_3DMtx<TP_Vox, TP_Crd>& MtxSrc);
	//---------------------------------------------------------------------------

	void Append(const CSPN_Cmn_3DMtx<TP_Vox, TP_Crd>& MtxTail);

	//virtual void CopyMtxTo(SSPN_Cmn_3DPoint<int> P3IdxBgnSrc,
	//					   SSPN_Cmn_3DPoint<int> P3IdxBgnDst,
	//					   SSPN_Cmn_3DPoint<int> P3_Count,
	//					   CSPN_Cmn_3DMtx_Base<TP_Crd>& MtxDst) const;
	void WrapCopy_Z(const CSPN_Cmn_3DMtx<TP_Vox, TP_Crd>& MtxSrc,
					const INT64 nLayer_perSide,
					const TP_Vox* ptpFill_OutWrapped = nullptr);

	void PeelCopy_Z(const CSPN_Cmn_3DMtx<TP_Vox, TP_Crd>& VoxMtx, const INT64 nLayer);

	void WrapCopy(const CSPN_Cmn_3DMtx<TP_Vox, TP_Crd>& VoxMtx, const SSPN_Cmn_3DPoint<int> P3_Count, const TP_Vox tpFill_OutWrapped);
	void PeelCopy(const CSPN_Cmn_3DMtx<TP_Vox, TP_Crd>& VoxMtx, const SSPN_Cmn_3DPoint<int> P3_Count);

	void WrapCopy(const CSPN_Cmn_3DMtx<TP_Vox, TP_Crd>& VoxMtx, const SSPN_Cmn_3DPoint<int> P3_CountBgn, const SSPN_Cmn_3DPoint<int> P3_CountEnd, const TP_Vox tpFill_OutWrapped);
	void PeelCopy(const CSPN_Cmn_3DMtx<TP_Vox, TP_Crd>& VoxMtx, const SSPN_Cmn_3DPoint<int> P3_CountBgn, const SSPN_Cmn_3DPoint<int> P3_CountEnd);
	//---------------------------------------------------------------------------

	void StretchTo_ZInsert(CSPN_Cmn_3DMtx<TP_Vox, TP_Crd>& MtxDst, int nSlcInsertPerSpan) const;
	void StretchTo_TriLinear(CSPN_Cmn_3DMtx<TP_Vox, TP_Crd>& MtxDst) const;
	void StretchTo_TriLinear_Round(CSPN_Cmn_3DMtx<TP_Vox, TP_Crd>& MtxDst, float fRoundCtrl) const;
	void StretchTo_NearPoint(CSPN_Cmn_3DMtx<TP_Vox, TP_Crd>& MtxDst) const;
	//---------------------------------------------------------------------------

	void MapMtxByLUT(CSPN_Cmn_3DMtx<TP_Vox, TP_Crd>& Mtx, const CSPN_Cmn_LUT_Arr<TP_Vox, TP_Vox>& LutArr) const;

	void MapMtx_byWnd_Slc(CSPN_Cmn_3DMtx<COLORREF>& MtxDst,
						int kSlcDst,
						int kSlcSrc,
						TP_Vox vSrcMin,
						TP_Vox vSrcMax,
						CSPN_Cmn_3DMtx<BYTE>* pMtxA) const;

	inline void MapMtx_byWL_Slc(CSPN_Cmn_3DMtx<BYTE>& MtxDst,
								int kSlcDst,
								int kSlcSrc,
								TP_Vox vW,
								TP_Vox vL) const
	{
		TP_Vox vLo_to_0 = vL - 0.5f*vW;
		TP_Vox vUp_to_255 = vL + 0.5f*vW;

		MapMtx_byWnd_Slc(MtxDst, kSlcDst, kSlcSrc, vLo_to_0, vUp_to_255);
	}

	inline bool MapMtx_byWnd_Slc(CSPN_Cmn_3DMtx<BYTE>& MtxDst,
		int kSlcDst,
		int kSlcSrc,
		TP_Vox vLow_to_0,
		TP_Vox vUp_to_255) const

	{
		//-----------------1----------------数据准备
		if (kSlcSrc < 0 || kSlcSrc >= this->GetSize_Z())
		{
			return false;
		}
		//inline void MapTo_GreyImg_LoUp(QImage& rImg, float vLow_to_0, float vUp_to_255) const



		if (this->GetSize_X() != MtxDst.GetSize_X() ||
			this->GetSize_Y() != MtxDst.GetSize_Y())
		{
			MtxDst.Set_nXYZ(this->GetSize_X(), this->GetSize_Y(), kSlcDst + 1);
			MtxDst.SetVox_All(0);
		}
		else
		{
			if (kSlcDst < 0 || kSlcDst >= MtxDst.GetSize_Z())
			{
				MtxDst.Set_nXYZ(this->GetSize_X(), this->GetSize_Y(), kSlcDst + 1);
				MtxDst.SetVox_All(0);
			}
		}

		int nXY = MtxDst.GetSize_Slc();
	          	BYTE* pSlcDst = MtxDst.GetSliceBuf(kSlcDst);
		const TP_Vox* pSlcSrc = this->GetSliceBuf(kSlcDst);


		if (fabs(vUp_to_255 - vLow_to_0) < 2 * FLT_EPSILON)
		{
			uchar C_vGrey = 128;
			::memset(pSlcDst, C_vGrey, nXY * sizeof(BYTE));
		}
		else
		{
			float fK = 255.f / (vUp_to_255 - vLow_to_0);

			//int nBytesPerLine = rImg.bytesPerLine();
			//int nBytePerPx = nBytesPerLine / m_nW;

			//以下可做LUT优化（当TP_Vox为16位以下的整型）

#pragma omp parallel for
			for (int ij = 0; ij < this->GetSize_Slc(); ij++)
			{
				const TP_Vox& rvSrc = pSlcSrc[ij];
				BYTE& rvGrey = pSlcDst[ij];
				{
					if (rvSrc < vLow_to_0)
					{
						rvGrey = 0;
					}
					else if (rvSrc > vUp_to_255)
					{
						rvGrey = 255;
					}
					else
					{
						rvGrey = (rvSrc - vLow_to_0) * fK;
					}

				}
			}
		}

	};


	bool MapMtx_byWndGamma_Slc(CSPN_Cmn_3DMtx<BYTE>& MtxDst,
									  int kSlcDst,
									  int kSlcSrc,
									  TP_Vox vLow_to_0,
									  TP_Vox vUp_to_255,
									  float fGamma = 1.3f)const;
//
//	{
//		//-----------------1----------------数据准备
//		if (kSlcSrc < 0 || kSlcSrc >= this->GetSize_Z())
//		{
//			return false;
//		}
//		//inline void MapTo_GreyImg_LoUp(QImage& rImg, float vLow_to_0, float vUp_to_255) const
//
//
//
//		if (this->GetSize_X() != MtxDst.GetSize_X() ||
//			this->GetSize_Y() != MtxDst.GetSize_Y())
//		{
//			MtxDst.Set_nXYZ(this->GetSize_X(), this->GetSize_Y(), kSlcDst + 1);
//			MtxDst.SetVox_All(0);
//		}
//		else
//		{
//			if (kSlcDst < 0 || kSlcDst >= MtxDst.GetSize_Z())
//			{
//				MtxDst.Set_nXYZ(this->GetSize_X(), this->GetSize_Y(), kSlcDst + 1);
//				MtxDst.SetVox_All(0);
//			}
//		}
//
//		int nXY = MtxDst.GetSize_Slc();
//		BYTE* pSlcDst = MtxDst.GetSliceBuf(kSlcDst);
//		const TP_Vox* pSlcSrc = this->GetSliceBuf(kSlcDst);
//
//
//		if (fabs(vUp_to_255 - vLow_to_0) < 2 * FLT_EPSILON)
//		{
//			uchar C_vGrey = 128;
//			::memset(pSlcDst, C_vGrey, nXY * sizeof(BYTE));
//		}
//		else
//		{
//			float fK = 255.f / (vUp_to_255 - vLow_to_0);
//
//			//int nBytesPerLine = rImg.bytesPerLine();
//			//int nBytePerPx = nBytesPerLine / m_nW;
//
//			//以下可做LUT优化（当TP_Vox为16位以下的整型）
//
//			const int C_LutIdxOfst = 32768;
//			std::vector<BYTE> Arr_LUT_Gamma;
//			{
//				const int C_nSize = 65536;
//				Arr_LUT_Gamma.resize(C_nSize);
//				
//				const float fKGm = pow(255, 1 - fGamma);
//
//				for (int i = 0; i < C_nSize; i++)
//				{
//					short sSrc = i - C_LutIdxOfst;
//					if (sSrc < vLow_to_0)
//					{
//						Arr_LUT_Gamma[i] = 0;
//					}
//					else if (sSrc > vUp_to_255)
//					{
//						Arr_LUT_Gamma[i] = 255;
//					}
//					else
//					{
//						float fGrey = (sSrc - vLow_to_0) * fK;
//						Arr_LUT_Gamma[i] = pow(fGrey, fGamma) * fKGm;
//					}
//				}
//			}
//			
//#pragma omp parallel for
//			for (int ij = 0; ij < this->GetSize_Slc(); ij++)
//			{
//				const TP_Vox& rvSrc = pSlcSrc[ij];
//				BYTE&        rvGrey = pSlcDst[ij];
//				{
//					rvGrey = Arr_LUT_Gamma[rvSrc+ C_LutIdxOfst];
//					//if (rvSrc < vLow_to_0)
//					//{
//					//	rvGrey = 0;
//					//}
//					//else if (rvSrc > vUp_to_255)
//					//{
//					//	rvGrey = 255;
//					//}
//					//else
//					//{
//					//	float fGrey = (rvSrc - vLow_to_0) * fK;
//					//	//rvGrey = pow(fGrey, fGamma) * fKGm;
//					//	rvGrey = arr_LUT_Gamma256[(BYTE)fGrey];
//					//}
//				}
//			}
//
//		}
//	};

	void MapMtxByWnd_Box(CSPN_Cmn_3DMtx<BYTE>& MtxDst,
						 TP_Vox vSrcMin,
						 TP_Vox vSrcMax) const;
	void MapMtxByWnd_Box(CSPN_Cmn_3DMtx<COLORREF>& MtxDst,
						 TP_Vox vSrcMin,
						 TP_Vox vSrcMax,
						 CSPN_Cmn_3DMtx<BYTE>* pMtxA) const;

	void MapMtx(TP_Vox vSrcA, TP_Vox vSrcB, TP_Vox vDstA, TP_Vox vDstB);
	void MapMtx_MinMaxTo(TP_Vox vDstMin, TP_Vox vDstMax);
	void MapTowVal_toNew(TP_Vox vA_Old, TP_Vox vB_Old, TP_Vox vA_New, TP_Vox vB_New);

	bool IsAllVox_between_MinMax(TP_Vox vMin, TP_Vox vMax);

	bool GetQImage_Grey888(QImage& qImg888,int kSlc)
	{

		if (0 == this->GetMemSize_Mtx())
		{
			return false;
		}
		qImg888 = QImage(this->GetSize_X(), this->GetSize_Y(), QImage::Format::Format_RGB888);


		int nBytesPerLine = qImg888.bytesPerLine();
		int nBytePerPx = nBytesPerLine / this->GetSize_X();

		//#pragma omp parallel for
		for (int j = 0; j < this->GetSize_Y(); j++)
		{
			uchar* pRowBuf_Dst = qImg888.scanLine(j);
			TP_Vox* pRowVox_Src = this->GetSliceRowBuf(kSlc, j);
			for (int i = 0; i < this->GetSize_X(); i++)
			{
				int iPx = j * this->GetSize_X() + i;

				uchar vGrey = *pRowVox_Src++;
				//{
				//	if (m_pfImgBuf[iPx] < vLow_to_0)
				//	{
				//		vGrey = 0;
				//	}
				//	else if (m_pfImgBuf[iPx] > vUp_to_255)
				//	{
				//		vGrey = 255;
				//	}
				//	else
				//	{
				//		vGrey = (m_pfImgBuf[iPx] - vLow_to_0) * fK;
				//	}
				//}

				//qImg888.setPixel(i, j, qRgb(vGrey, vGrey, vGrey/*, 0*/));
				int iBytePxBgn_inRow = i * nBytePerPx;
				int iByte_inPx = nBytePerPx;
				while (iByte_inPx--)
				{
					pRowBuf_Dst[iBytePxBgn_inRow + iByte_inPx] = vGrey;
				}
			}
		}
		return true;
	}


	////---------------------------------------------------------------------------
	inline float GetArea_SlcXY_Range(const INT64 iZ, const TP_Vox vMin, const TP_Vox vMax) const;

	inline float GetVolume_Range(const TP_Vox vMin, const TP_Vox vMax) const;
	inline float GetVolume_Range_inCub(const TP_Vox vMin, const TP_Vox vMax, Cub3D_Idx Cub) const;

	//---------------------------------------------------------------------------
	//inline int GetSegmentInf_inRange_X(std::vector<S_SPN_MtxVoxSegment>& Arr_sVoxSgmnt,
	//								   TP_Vox vMin, const TP_Vox vMax,
	//								   int iXMin, int iXMax, int jY, int kZ) const;

	//inline int GetSegmentInf_inRange_Y(std::vector<S_SPN_MtxVoxSegment>& Arr_sVoxSgmnt,
	//								   TP_Vox vMin, const TP_Vox vMax,
	//								   int iX, int jYMin, int jYMax, int kZ) const;
	//inline int GetSegmentInf_inRange_Z(std::vector<S_SPN_MtxVoxSegment>& Arr_sVoxSgmnt,
	//								   TP_Vox vMin, const TP_Vox vMax,
	//								   int iX, int jY, int kZMin, int kZMax) const;

	//---------------------------------------------------------------------------
	inline int	 GetVoxCount_Range(const TP_Vox vMin, const TP_Vox vMax) const;
	inline float GetVoxCount_Range_inCub(const TP_Vox vMin, const TP_Vox vMax, Cub3D_Idx Cub) const;

	inline bool IsAnyVox_inRange(const TP_Vox vMin, const TP_Vox vMax) const;
	inline bool IsAnyVox_inRange_inCub(const TP_Vox vMin, const TP_Vox vMax, Cub3D_Idx Cub) const;

	//---------------------------------------------------------------------------
	inline Pnt3D_Flt GetP3D_WeightCenter_IdxFlt() const;
	inline Pnt3D_Flt GetP3D_WeightCenter_Range_IdxFlt(const TP_Vox vMin, const TP_Vox vMax) const;
	inline Pnt3D_Flt GetP3D_WeightCenter_Range_inCub_IdxFlt(const TP_Vox vMin, const TP_Vox vMax, int arri3Min[3], int arri3Max[3]) const;

	//---------------------------------------------------------------------------
	SRct2D_Int	FindBoundCubD_InRange(const INT64 kSlc,
									  const TP_Vox vMin,
									  const TP_Vox vMax,
									  const int nInflate = 0) const;
	bool		FindBoundCub3D_InRange(const TP_Vox vMin,
									   const TP_Vox vMax,
									   SSPN_Cmn_3DPoint<int>& Pmin,
									   SSPN_Cmn_3DPoint<int>& Pmax,
									   const int* pijkBgn = nullptr,
									   const int* pijkEnd = nullptr,
									   const int nInflate = 0) const;

	bool		FindBoundCub3D_InRange_Rgn_inMask(SSPN_Cmn_3DPoint<int>& Pmin,
												  SSPN_Cmn_3DPoint<int>& Pmax) const;
	bool		FindBoundCub3D_InRange_Rgn_inMask_inPreBound(SSPN_Cmn_3DPoint<int>& Pmin,
															 SSPN_Cmn_3DPoint<int>& Pmax) const;
	bool		FindBoundCub3D_InRange_Rgn_inMask(Cub3D_Idx& Cub) const
	{
		bool bOK = FindBoundCub3D_InRange_Rgn_inMask(Cub.GetP3D_Min(), Cub.GetP3D_Max());
		return bOK;
	}
	bool		FindBoundCub3D_InRange_MaskVal_in_nValMtx(SSPN_Cmn_3DPoint<int>& Pmin,
														  SSPN_Cmn_3DPoint<int>& Pmax,
														  TP_Vox iMask) const;
	bool		FindBoundCub3D_InRange_ValRng_in_nValMtx(SSPN_Cmn_3DPoint<int>& Pmin,
														 SSPN_Cmn_3DPoint<int>& Pmax,
														 TP_Vox vMin, TP_Vox vMax) const;
	bool		FindBoundCub3D_InRange_MaskVal_in_nValMtx(Cub3D_Idx& Cub, TP_Vox iMask) const;

	//---------------------------------------------------------------------------

	TP_Vox GetVoxAvg() const;
	TP_Vox GetVoxSum() const;

	template<typename TPSUM> TPSUM GetVoxSum_TP(TPSUM* pSum = nullptr) const;
	//---------------------------------------------------------------------------

	TP_Vox	GetVoxMin() const;
	TP_Vox	GetVoxMax() const;

	TP_Vox	GetVoxMin(int& iVoxMin) const;
	TP_Vox	GetVoxMax(int& iVoxMax) const;

	TP_Vox	GetVoxMin_Abs(int& iVoxMin) const;
	TP_Vox	GetVoxMax_Abs(int& iVoxMax) const;

	inline void GetVoxMinMax(TP_Vox& vMin, TP_Vox& vMax)const
	{
		int nXY = this->GetSize_Slc();

		vMin = this->m_pVoxMem[0];
		vMax = this->m_pVoxMem[0];

		for (int i = 0; i < nXY; i++)
		{
			if (this->m_pVoxMem[i] < vMin)
			{
				vMin = this->m_pVoxMem[i];
			}
			if (this->m_pVoxMem[i] > vMax)
			{
				vMax = this->m_pVoxMem[i];
			}
		}
	}
	void	GetVoxMinMax(TP_Vox& vMin, TP_Vox& vMax, int& iVoxMin, int& iVoxMax) const;


	TP_Vox	GetVoxMin_NearP3Cntr(SPnt3D_Int sP3Cntr, SPnt3D_Int sP3Dxyz, SPnt3D_Int* psP3Min = nullptr) const;
	TP_Vox	GetVoxMax_NearP3Cntr(SPnt3D_Int sP3Cntr, SPnt3D_Int sP3Dxyz, SPnt3D_Int* psP3Max = nullptr) const;
	void	GetVoxMinMax_NearP3Cntr(TP_Vox& vMin, TP_Vox& vMax, SPnt3D_Int sP3Cntr, SPnt3D_Int sP3Dxyz,
									SPnt3D_Int* psP3Min = nullptr, SPnt3D_Int* psP3Max = nullptr) const;
	TP_Vox	GetVoxMin_NearP3Cntr_byMask(SPnt3D_Int sP3Cntr, SPnt3D_Int sP3Dxyz, const CSPN_Cmn_3DMtx<BYTE>& MtxMsk_Find, SPnt3D_Int* psP3Min = nullptr) const;
	TP_Vox	GetVoxMax_NearP3Cntr_byMask(SPnt3D_Int sP3Cntr, SPnt3D_Int sP3Dxyz, const CSPN_Cmn_3DMtx<BYTE>& MtxMsk_Find, SPnt3D_Int* psP3Max = nullptr) const;

	void	GetVoxMinMax_NearP3Cntr_byMask(TP_Vox& vMin, TP_Vox& vMax, SPnt3D_Int sP3Cntr, SPnt3D_Int sP3Dxyz, const CSPN_Cmn_3DMtx<BYTE>& MtxMsk_Find,
										   SPnt3D_Int* psP3Min = nullptr, SPnt3D_Int* psP3Max = nullptr) const;

	TP_Vox	GetVoxMin_inBox(SPnt3D_Int sP3IdxMin, SPnt3D_Int sP3IdxMax, SPnt3D_Int* psP3Min = nullptr) const;
	TP_Vox	GetVoxMax_inBox(SPnt3D_Int sP3IdxMin, SPnt3D_Int sP3IdxMax, SPnt3D_Int* psP3Max = nullptr) const;
	void	GetVoxMinMax_inBox(TP_Vox& vMin, TP_Vox& vMax, SPnt3D_Int sP3IdxMin, SPnt3D_Int sP3IdxMax,
							   SPnt3D_Int* psP3Min = nullptr, SPnt3D_Int* psP3Max = nullptr) const;

	TP_Vox GetVoxMax_inBox_byMask(SPnt3D_Int sP3RngMin,
								  SPnt3D_Int sP3RngMax,
								  const CSPN_Cmn_3DMtx<BYTE>& MtxMsk_Find,
								  SPnt3D_Int* psP3Max/* = nullptr*/) const;

	TP_Vox GetVoxMin_inBox_byMask(SPnt3D_Int sP3RngMin,
								  SPnt3D_Int sP3RngMax,
								  const  CSPN_Cmn_3DMtx<BYTE>& MtxMsk_Find,
								  SPnt3D_Int* psP3Max/* = nullptr*/) const;

	void   GetVoxMinMax_inBox_byMask(TP_Vox& vMin,
									 TP_Vox& vMax,
									 SPnt3D_Int sP3RngMin,
									 SPnt3D_Int sP3RngMax,
									 const CSPN_Cmn_3DMtx<BYTE>& MtxMsk_Find,
									 SPnt3D_Int* psP3Min/* = nullptr*/,
									 SPnt3D_Int* psP3Max/* = nullptr*/) const;
	void	GetVoxMinMax_perSlc(TP_Vox* pvMin, TP_Vox* pvMax, std::string* pStr_Inf = nullptr) const;

	//---------------------------------------------------------------------------

	void LimitVoxVal_Min(const TP_Vox vMin);
	void LimitVoxVal_Max(const TP_Vox vMax);
	void LimitVoxVal_MinMax(const TP_Vox vMin, const TP_Vox vMax);
	//---------------------------------------------------------------------------

	template<typename TPOther> 	void operator+=	(const TPOther& V)
	{
		int nVox = this->GetSize_Mtx();
#pragma omp parallel for
		for (int i = 0; i < nVox; i++)
		{
			this->m_pVoxMem[i] += V;
		}
	}

	template<typename TPOther> 	void operator+=	(const CSPN_Cmn_3DMtx<TPOther, TP_Crd>& Mtx)
	{
		if (!this->IsGridSame_Count_As(Mtx))
		{
			assert(false);
			return;
		}
		int nVox = this->GetSize_Mtx();
#pragma omp parallel for
		for (int i = 0; i < nVox; i++)
		{
			this->m_pVoxMem[i] += Mtx.m_pVoxMem[i];
		}
	}


	template<typename TPOther> 	void operator-=	(const TPOther& V);
	template<typename TPOther> 	void operator-=	(const CSPN_Cmn_3DMtx<TPOther, TP_Crd>& Mtx);

	template<typename TPOther> 	void operator=	(const TPOther& V);
	template<typename TPOther> 	void operator=	(const CSPN_Cmn_3DMtx<TPOther, TP_Crd>& Mtx);

	template<typename TPOther> 	void operator/=	(const TPOther& V);
	template<typename TPOther> 	void operator/=	(const CSPN_Cmn_3DMtx<TPOther, TP_Crd>& Mtx);

	//---------------------------------------------------------------------------
	void FlipX_Vox_PerSlc();
	void FlipY_Vox_PerSlc();
	void FlipZ_Vox_PerSlc();

public:
	void Transpose_XY_n_FlipZ(bool bFlip_CoordZ);
	void Transpose_XY_inSlc();
protected:
	void _Transpose_XY_inSlc_Calc(bool bTransposeCoordXY);
	//---------------------------------------------------------------------------

//Data member:
protected:
	TP_Vox*					m_pVoxMem = NULL;
	BOOL					m_bVoxBuf_Hooked = FALSE;

	INT64					m_nBytePerSlc = 0;
	std::vector<TP_Vox*>	m_ArrPtrVoxHead_Z;
	//---------------------------------------------------------------------------
};

//
typedef CSPN_Cmn_3DMtx<BYTE>		MtxByteTP;
typedef CSPN_Cmn_3DMtx<COLORREF>	MtxRGBA_TP;
//_UNUSE_FSTREAM_SERIALIZE(MtxRGBA_TP)

inline void GetMap_ColorMtx_Slc(MtxRGBA_TP& MtxRGBA,
								int kSlcDst,
								int kSlcSrc,
								const MtxByteTP& MtxR,
								const MtxByteTP& MtxG,
								const MtxByteTP& MtxB,
								const MtxByteTP* pMtxA);

inline void GetMap_ColorMtx_Box(MtxRGBA_TP& MtxRGBA,
								const MtxByteTP& MtxR,
								const MtxByteTP& MtxG,
								const MtxByteTP& MtxB,
								const MtxByteTP* pMtxA);

//

//-----------------------------------------------------------------------------------

template<typename TPVoxSrc, typename TPVoxDst>
void CSPN_Cmn_3DMtx__To_MtxType(const CSPN_Cmn_3DMtx<TPVoxSrc>& MtxSrc, CSPN_Cmn_3DMtx<TPVoxDst>& MtxDst);

//-----------------------------------------------------------------------------------
//todo:改成通用版本
//{
template < typename TP_Vox,typename TP_Crd>
inline bool CSPN_Cmn_3DMtx<TP_Vox, TP_Crd>::MapMtx_byWndGamma_Slc(CSPN_Cmn_3DMtx<BYTE>& MtxDst,
																  int kSlcDst,
																  int kSlcSrc,
																  TP_Vox vLow_to_0,
																  TP_Vox vUp_to_255,
																  float fGamma/* = 1.3f*/)const

{
	assert(false);
	//????????????????????????????????????????????????



	//-----------------1----------------数据准备
	if (kSlcSrc < 0 || kSlcSrc >= this->GetSize_Z())
	{
		return false;
	}
	//inline void MapTo_GreyImg_LoUp(QImage& rImg, float vLow_to_0, float vUp_to_255) const



	if (this->GetSize_X() != MtxDst.GetSize_X() ||
		this->GetSize_Y() != MtxDst.GetSize_Y())
	{
		MtxDst.Set_nXYZ(this->GetSize_X(), this->GetSize_Y(), kSlcDst + 1);
		MtxDst.SetVox_All(0);
	}
	else
	{
		if (kSlcDst < 0 || kSlcDst >= MtxDst.GetSize_Z())
		{
			MtxDst.Set_nXYZ(this->GetSize_X(), this->GetSize_Y(), kSlcDst + 1);
			MtxDst.SetVox_All(0);
		}
	}

	int nXY = MtxDst.GetSize_Slc();
	BYTE* pSlcDst = MtxDst.GetSliceBuf(kSlcDst);
	const TP_Vox* pSlcSrc = this->GetSliceBuf(kSlcDst);


	if (fabs(vUp_to_255 - vLow_to_0) < 2 * FLT_EPSILON)
	{
		uchar C_vGrey = 128;
		::memset(pSlcDst, C_vGrey, nXY * sizeof(BYTE));
	}
	else
	{
		float fK = 255.f / (vUp_to_255 - vLow_to_0);

		//int nBytesPerLine = rImg.bytesPerLine();
		//int nBytePerPx = nBytesPerLine / m_nW;

		//以下可做LUT优化（当TP_Vox为16位以下的整型）

		const int C_LutIdxOfst = 32768;
		std::vector<BYTE> Arr_LUT_Gamma;
		{
			const int C_nSize = 65536;
			Arr_LUT_Gamma.resize(C_nSize);

			const float fKGm = pow(255, 1 - fGamma);

			for (int i = 0; i < C_nSize; i++)
			{
				short sSrc = i - C_LutIdxOfst;
				if (sSrc < vLow_to_0)
				{
					Arr_LUT_Gamma[i] = 0;
				}
				else if (sSrc > vUp_to_255)
				{
					Arr_LUT_Gamma[i] = 255;
				}
				else
				{
					float fGrey = (sSrc - vLow_to_0) * fK;
					Arr_LUT_Gamma[i] = pow(fGrey, fGamma) * fKGm;
				}
			}
		}

#pragma omp parallel for
		for (int ij = 0; ij < this->GetSize_Slc(); ij++)
		{
			const TP_Vox& rvSrc = pSlcSrc[ij];
			BYTE&        rvGrey = pSlcDst[ij];
			{
				rvGrey = Arr_LUT_Gamma[rvSrc + C_LutIdxOfst];
				//if (rvSrc < vLow_to_0)
				//{
				//	rvGrey = 0;
				//}
				//else if (rvSrc > vUp_to_255)
				//{
				//	rvGrey = 255;
				//}
				//else
				//{
				//	float fGrey = (rvSrc - vLow_to_0) * fK;
				//	//rvGrey = pow(fGrey, fGamma) * fKGm;
				//	rvGrey = arr_LUT_Gamma256[(BYTE)fGrey];
				//}
			}
		}

	}
};
//}

template </* typename short*/>
inline bool CSPN_Cmn_3DMtx<short, float>::MapMtx_byWndGamma_Slc(CSPN_Cmn_3DMtx<BYTE>& MtxDst,
																int kSlcDst,
																int kSlcSrc,
																short vLow_to_0,
																short vUp_to_255,
																float fGamma/* = 1.3f*/)const
{
	//-----------------1----------------数据准备
	if (kSlcSrc < 0 || kSlcSrc >= this->GetSize_Z())
	{
		return false;
	}
	//inline void MapTo_GreyImg_LoUp(QImage& rImg, float vLow_to_0, float vUp_to_255) const



	if (this->GetSize_X() != MtxDst.GetSize_X() ||
		this->GetSize_Y() != MtxDst.GetSize_Y())
	{
		MtxDst.Set_nXYZ(this->GetSize_X(), this->GetSize_Y(), kSlcDst + 1);
		MtxDst.SetVox_All(0);
	}
	else
	{
		if (kSlcDst < 0 || kSlcDst >= MtxDst.GetSize_Z())
		{
			MtxDst.Set_nXYZ(this->GetSize_X(), this->GetSize_Y(), kSlcDst + 1);
			MtxDst.SetVox_All(0);
		}
	}

	int nXY = MtxDst.GetSize_Slc();
	BYTE* pSlcDst = MtxDst.GetSliceBuf(kSlcDst);
	const short* pSlcSrc = this->GetSliceBuf(kSlcDst);


	if (fabs(vUp_to_255 - vLow_to_0) < 2 * FLT_EPSILON)
	{
		uchar C_vGrey = 128;
		::memset(pSlcDst, C_vGrey, nXY * sizeof(BYTE));
	}
	else
	{
		float fK = 255.f / (vUp_to_255 - vLow_to_0);

		//int nBytesPerLine = rImg.bytesPerLine();
		//int nBytePerPx = nBytesPerLine / m_nW;

		//以下可做LUT优化（当TP_Vox为16位以下的整型）

		const int C_LutIdxOfst = 32768;
		std::vector<BYTE> Arr_LUT_Gamma;
		{
			const int C_nSize = 65536;
			Arr_LUT_Gamma.resize(C_nSize);

			const float fKGm = pow(255, 1 - fGamma);

			for (int i = 0; i < C_nSize; i++)
			{
				short sSrc = i - C_LutIdxOfst;
				if (sSrc < vLow_to_0)
				{
					Arr_LUT_Gamma[i] = 0;
				}
				else if (sSrc > vUp_to_255)
				{
					Arr_LUT_Gamma[i] = 255;
				}
				else
				{
					float fGrey = (sSrc - vLow_to_0) * fK;
					Arr_LUT_Gamma[i] = pow(fGrey, fGamma) * fKGm;
				}
			}
		}

#pragma omp parallel for
		for (int ij = 0; ij < this->GetSize_Slc(); ij++)
		{
			const short& rvSrc = pSlcSrc[ij];
			BYTE&        rvGrey = pSlcDst[ij];
			{
				rvGrey = Arr_LUT_Gamma[rvSrc + C_LutIdxOfst];
				//if (rvSrc < vLow_to_0)
				//{
				//	rvGrey = 0;
				//}
				//else if (rvSrc > vUp_to_255)
				//{
				//	rvGrey = 255;
				//}
				//else
				//{
				//	float fGrey = (rvSrc - vLow_to_0) * fK;
				//	//rvGrey = pow(fGrey, fGamma) * fKGm;
				//	rvGrey = arr_LUT_Gamma256[(BYTE)fGrey];
				//}
			}
		}

	}
};

#endif //!defined(SPN_Cmn_3DMtx_H__INCLUDED_
