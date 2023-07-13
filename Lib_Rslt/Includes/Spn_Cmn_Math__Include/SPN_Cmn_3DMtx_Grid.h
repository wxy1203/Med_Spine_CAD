// SPN_Cmn_3DMtx_Grid.h: interface for the CSPN_Cmn_3DMtx_Grid class.
//
//////////////////////////////////////////////////////////////////////

#ifndef SPN_Cmn_3DMtx_Grid__INCLUDED_
#define SPN_Cmn_3DMtx_Grid__INCLUDED_

#pragma once

using INT64 = signed __int64;      

template<typename TP_Crd = float>
class CSPN_Cmn_3DMtx_Grid
{	
	friend class CSPN_Cmn_3DMtx_FStreamer;
public:	
	CSPN_Cmn_3DMtx_Grid();
	CSPN_Cmn_3DMtx_Grid(const CSPN_Cmn_3DMtx_Grid<TP_Crd>& VoxMtx);
	virtual ~CSPN_Cmn_3DMtx_Grid();

	//Data member:
protected:
	INT64 m_nX = 0;						//体数据的三向体素个数长度
	INT64 m_nY = 0;
	INT64 m_nZ = 0;

	SSPN_Cmn_3DPoint<TP_Crd>		m_P3D_Bgn;
	SSPN_Cmn_3DPoint<TP_Crd>		m_P3D_Spc;	//体素三向间隔

	double							m_IJKToRASMatrix[4][4]; //[10_26 18:11:49 liuzhiwen]: IJKToRAS变换矩阵

	//下列成员用于快速存取之优化：
	//CSPN_Cmn_CArray<TP*, TP*&>	m_ArrPtrVoxHead_Z;			//缓存每切片首地址
	CSPN_Cmn_CArray<INT64, INT64&>	m_Arr_nVoxPreRowsInSlc_Y;	//每个体素所在行以前的全部行中所包含的体素个数(切片内因行引起的偏移, 因列引起的偏移为x)
	//
	INT64							m_nVoxTotal = 0;	//体素总数
	INT64							m_nVoxPerSlc = 0;	//每切片象素数
	//INT64 m_nBytePerSlc = 0;//每切片占用字节数

public:
	void Reset_All();
	void Reset_Geo();

protected:
	void VoxGeo_Construct_TmpAttr();

public:
	//......................................................................................................................................
	inline void LimitIdx_to_Valid(int& iX, int& jY, int& kZ) const
	{
		CutIntoRange<int>(iX, 0, m_nX - 1);
		CutIntoRange<int>(jY, 0, m_nY - 1);
		CutIntoRange<int>(kZ, 0, m_nZ - 1);
	};

	inline int Get_nDim()//[5_22 21:14:29 ]:
	{
		int nDim = 3;
		nDim -= ((m_nX < 2) ? (1) : (0));
		nDim -= ((m_nY < 2) ? (1) : (0));
		nDim -= ((m_nZ < 2) ? (1) : (0));
		return nDim;
	};

	//......................................................................................................................................

	void Construct_All(SPnt3D_Int P3D_nXYZ, SPnt3D_Dbl P3D_fBgn, SPnt3D_Dbl P3D_fSpcXYZ)//[11_13 21:29:24 ]: 
	{
		Set_nXYZ(P3D_nXYZ[0], P3D_nXYZ[1], P3D_nXYZ[2]);
		SetP3D_Bgn_Dbl(P3D_fBgn);
		SetP3D_Spc(P3D_fSpcXYZ.GetDataBuf());
	};

	void Construct_All(SPnt3D_Int P3D_nXYZ, SPnt3D_Flt P3D_fBgn, SPnt3D_Flt P3D_fSpcXYZ)//[11_13 21:29:24 ]: 
	{
		Set_nXYZ(P3D_nXYZ[0], P3D_nXYZ[1], P3D_nXYZ[2]);
		SetP3D_Bgn_Flt(P3D_fBgn);
		SetP3D_Spc(P3D_fSpcXYZ.GetDataBuf());
	};

	void TransposeGrid_XY_inSlc()//[1_22 11:00:28 ]:
	{
		ExchangeValue(m_nX, m_nY);
		ExchangeValue(m_P3D_Spc[0], m_P3D_Spc[1]);
		ExchangeValue(m_P3D_Bgn[0], m_P3D_Bgn[1]);

		VoxGeo_Construct_TmpAttr();//[3_5 15:31:53 ]:
	};

	void TransposeGrid_XY_n_FlipZ()//[1_22 11:00:23 ]:
	{
		TransposeGrid_XY_inSlc();
		m_P3D_Spc[2] = -m_P3D_Spc[2];
		m_P3D_Bgn[2] = GetVoxCoord_Z(GetUpperBound_Z());
	};

	virtual bool Set_nXYZ(INT64 nX, INT64 nY, INT64 nZ) //[6_8 10:28:05 ]:派生类决定是否同时分配内存
	{
		m_nX = nX;
		m_nY = nY;
		m_nZ = nZ;
		this->VoxGeo_Construct_TmpAttr();
		return true;
	};

	inline bool Set_nXYZ(Pnt3D_Int P3Sz) //[6_8 10:28:05 ]:派生类决定是否同时分配内存
	{
		return Set_nXYZ(P3Sz[0], P3Sz[1], P3Sz[2]);
	};

	bool Set_nXYZ_noAlloc(INT64 nX, INT64 nY, INT64 nZ)//[6_8 10:28:40 ]:不给派生类决定分配内存的机会!
	{
		m_nX = nX;
		m_nY = nY;
		m_nZ = nZ;
		this->VoxGeo_Construct_TmpAttr();

		return true;
	};

	inline float GetP3D_Spc_X() const { return m_P3D_Spc[0]; };
	inline float GetP3D_Spc_Y() const { return m_P3D_Spc[1]; };
	inline float GetP3D_Spc_Z() const { return m_P3D_Spc[2]; };
	inline float GetP3D_Spc_XYZ_MinLength() const
	{
		float fL_SpcMin = std::min<float>(qAbs<TP_Crd>(m_P3D_Spc[0]), qAbs<TP_Crd>(m_P3D_Spc[1]));
		fL_SpcMin = std::min<float>(qAbs<TP_Crd>(m_P3D_Spc[2]), fL_SpcMin);
		return fL_SpcMin;
	};
	inline float GetP3D_Spc_XYZ_MaxLength() const
	{
		float fL_SpcMax = std::max<float>(qAbs(m_P3D_Spc[0]), qAbs(m_P3D_Spc[1]));
		fL_SpcMax = std::max<float>(qAbs(m_P3D_Spc[2]), fL_SpcMax);
		return fL_SpcMax;
	};
	inline float GetP3D_Spc_XYZ_AvgLength() const
	{
		float fL_SpcAvg = (qAbs(m_P3D_Spc[0]) + qAbs(m_P3D_Spc[1]) + qAbs(m_P3D_Spc[2])) / 3.f;
		return fL_SpcAvg;
	};

	inline SSPN_Cmn_3DPoint<TP_Crd> GetP3D_Spc() const
	{
		return m_P3D_Spc;
	};
	inline SPnt3D_Flt GetP3D_Spc_Flt() const { return m_P3D_Spc.ToFloat(); };
	inline SPnt3D_Dbl GetP3D_Spc_Dbl() const { return m_P3D_Spc.ToDouble(); };

	inline void GetP3D_Spc(float fSpcXYZ[3]) const
	{
		fSpcXYZ[0] = m_P3D_Spc[0];
		fSpcXYZ[1] = m_P3D_Spc[1];
		fSpcXYZ[2] = m_P3D_Spc[2];
	};

	inline void GetP3D_Spc(double fSpcXYZ[3]) const
	{
		fSpcXYZ[0] = m_P3D_Spc[0];
		fSpcXYZ[1] = m_P3D_Spc[1];
		fSpcXYZ[2] = m_P3D_Spc[2];
	};

	void SetP3D_Spc(const float fSpacingX, const float fSpacingY, const float fSpacingZ);

	inline void SetP3D_Spc(const float fSpcXYZ[3])
	{
		m_P3D_Spc[0] = fSpcXYZ[0];
		m_P3D_Spc[1] = fSpcXYZ[1];
		m_P3D_Spc[2] = fSpcXYZ[2];
	};

	inline void SetP3D_Spc(SSPN_Cmn_3DPoint<TP_Crd> P3D_SpcXYZ)
	{
		m_P3D_Spc = P3D_SpcXYZ;
	};

	inline void SetP3D_Spc(const double fSpcXYZ[3])
	{
		m_P3D_Spc[0] = fSpcXYZ[0];
		m_P3D_Spc[1] = fSpcXYZ[1];
		m_P3D_Spc[2] = fSpcXYZ[2];
	};

	inline SSPN_Cmn_3DPoint<TP_Crd>	GetP3D_Bgn() const { return m_P3D_Bgn; };
	inline void						GetP3D_Bgn(SSPN_Cmn_3DPoint<TP_Crd>& P3D_Bgn) const
	{
		P3D_Bgn = m_P3D_Bgn;
	};
	inline void						GetP3D_Bgn_Flt(SPnt3D_Flt& P3D_Bgn) const
	{
		P3D_Bgn[0] = m_P3D_Bgn[0];
		P3D_Bgn[1] = m_P3D_Bgn[1];
		P3D_Bgn[2] = m_P3D_Bgn[2];
	};
	inline void						GetP3D_Bgn_Dbl(SPnt3D_Dbl& P3D_Bgn) const
	{
		P3D_Bgn[0] = m_P3D_Bgn[0];
		P3D_Bgn[1] = m_P3D_Bgn[1];
		P3D_Bgn[2] = m_P3D_Bgn[2];
	};
	inline SPnt3D_Flt GetP3D_Bgn_Flt() const { return m_P3D_Bgn.ToFloat(); };
	inline SPnt3D_Dbl GetP3D_Bgn_Dbl() const { return m_P3D_Bgn.ToDouble(); };

	inline void						GetP3D_Bgn(float& fx, float& fy, float& fz) const { fx = m_P3D_Bgn[0]; fy = m_P3D_Bgn[1]; fz = m_P3D_Bgn[2]; };
	inline void						GetP3D_Bgn(double& fx, double& fy, double& fz) const { fx = m_P3D_Bgn[0]; fy = m_P3D_Bgn[1]; fz = m_P3D_Bgn[2]; };
	inline void						GetP3D_Bgn(float fBgn[3]) const
	{
		fBgn[0] = m_P3D_Bgn[0];
		fBgn[1] = m_P3D_Bgn[1];
		fBgn[2] = m_P3D_Bgn[2];
	};
	inline void						GetP3D_Bgn(double fBgn[3]) const
	{
		fBgn[0] = m_P3D_Bgn[0];
		fBgn[1] = m_P3D_Bgn[1];
		fBgn[2] = m_P3D_Bgn[2];
	};

	inline void SetP3D_Bgn_Flt(const SPnt3D_Flt& P3D_Bgn) { SetP3D_Bgn(P3D_Bgn[0], P3D_Bgn[1], P3D_Bgn[2]); };
	inline void SetP3D_Bgn_Dbl(const SPnt3D_Dbl& P3D_Bgn) { SetP3D_Bgn(P3D_Bgn[0], P3D_Bgn[1], P3D_Bgn[2]); };
	inline void SetP3D_Bgn(const SSPN_Cmn_3DPoint<TP_Crd>& P3D_Bgn) { m_P3D_Bgn = P3D_Bgn; };

	inline void SetP3D_Bgn(TP_Crd fx, TP_Crd fy, TP_Crd fz) { m_P3D_Bgn[0] = fx; m_P3D_Bgn[1] = fy; m_P3D_Bgn[2] = fz; };

	inline void SetP3D_Bgn(float fBgn[3])
	{
		m_P3D_Bgn[0] = fBgn[0];
		m_P3D_Bgn[1] = fBgn[1];
		m_P3D_Bgn[2] = fBgn[2];
	};

	inline void SetP3D_Bgn(double fBgn[3])
	{
		m_P3D_Bgn[0] = fBgn[0];
		m_P3D_Bgn[1] = fBgn[1];
		m_P3D_Bgn[2] = fBgn[2];
	};

	inline const double* GetIJKTORASMatrix() const
	{
		return (const double*)(m_IJKToRASMatrix);
	};
	inline void GetIJKTORASMatrix(double matrix[4][4]) const
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				matrix[i][j] = m_IJKToRASMatrix[i][j];
	};
	inline void SetIJKTORASMatrix(const double matrix[4][4])
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				m_IJKToRASMatrix[i][j] = matrix[i][j];
	};

	inline void GetP3D_Center_VoxCoord(SPnt3D_Flt& P3D_Cntr) const;
	inline SPnt3D_Flt GetP3D_Center_VoxCoord() const
	{
		SPnt3D_Flt P3D_Cntr;
		GetP3D_Center_VoxCoord(P3D_Cntr);
		return P3D_Cntr;
	};

	inline void GetP3D_Center_VoxIndex(SPnt3D_Int& P3D_Cntr) const;
	inline SPnt3D_Int GetP3D_Center_VoxIndex() const
	{
		SPnt3D_Int P3D_Cntr;
		GetP3D_Center_VoxIndex(P3D_Cntr);
		return P3D_Cntr;
	};
	inline SPnt3D_Flt GetP3D_Center_VoxIndex_Flt() const
	{
		SPnt3D_Flt P3D_Cntr;
		P3D_Cntr.Construct(float(m_nX - 1)*0.5f,
						   float(m_nY - 1)*0.5f,
						   float(m_nZ - 1)*0.5f);
		return P3D_Cntr;
	};
	inline SPnt3D_Dbl GetP3D_Center_VoxIndex_Dbl() const
	{
		return GetP3D_Center_VoxIndex_Flt().ToDouble();
	};

	BOOL IsGridSameAs(const CSPN_Cmn_3DMtx_Grid<TP_Crd>& MtxGrid) const;//是否网格一致(体素值除外的相等比较)
	inline BOOL IsGridSame_Count_As(const CSPN_Cmn_3DMtx_Grid<TP_Crd>& MtxGrid) const//是否网格一致(体素值除外的相等比较)
	{
		return
			m_nX == MtxGrid.m_nX &&
			m_nY == MtxGrid.m_nY &&
			m_nZ == MtxGrid.m_nZ;
	};
	inline BOOL IsGridSame_CoordSpc_As(const CSPN_Cmn_3DMtx_Grid<TP_Crd>& MtxGrid) const//是否网格一致(体素值除外的相等比较)
	{
		return
			FLT_EQ(m_P3D_Spc[0], MtxGrid.m_P3D_Spc[0]) &&
			FLT_EQ(m_P3D_Spc[1], MtxGrid.m_P3D_Spc[1]) &&
			FLT_EQ(m_P3D_Spc[2], MtxGrid.m_P3D_Spc[2]);
	};
	inline BOOL IsGridSame_CoordBgn_As(const CSPN_Cmn_3DMtx_Grid<TP_Crd>& MtxGrid) const//是否网格一致(体素值除外的相等比较)
	{
		return
			FLT_EQ(m_P3D_Bgn[0], MtxGrid.m_P3D_Bgn[0]) &&
			FLT_EQ(m_P3D_Bgn[1], MtxGrid.m_P3D_Bgn[1]) &&
			FLT_EQ(m_P3D_Bgn[2], MtxGrid.m_P3D_Bgn[2]);
	};
	//......................................................................................................................................
	inline INT64 GetSize_X() const { return m_nX; };
	inline INT64 GetSize_Y() const { return m_nY; };
	inline INT64 GetSize_Z() const { return m_nZ; };
	inline void GetSize_XYZ(int nXYZ[3]) const
	{
		nXYZ[0] = m_nX;
		nXYZ[1] = m_nY;
		nXYZ[2] = m_nZ;
	};
	inline void GetSize_XYZ(UINT nXYZ[3]) const
	{
		nXYZ[0] = m_nX;
		nXYZ[1] = m_nY;
		nXYZ[2] = m_nZ;
	};
	inline void GetSize_XYZ(short nXYZ[3]) const
	{
		nXYZ[0] = m_nX;
		nXYZ[1] = m_nY;
		nXYZ[2] = m_nZ;
	};
	inline SPnt3D_Int GetSize_XYZ() const
	{
		SPnt3D_Int PSzXYZ;
		PSzXYZ.Construct(m_nX, m_nY, m_nZ);
		return PSzXYZ;
	};
	inline SPnt2D_Int GetSize_XY() const
	{
		SPnt2D_Int PSzXY;
		PSzXY.Construct(m_nX, m_nY);
		return PSzXY;
	};

	inline INT64 GetSize_XYZ_Min() const { return std::min<int>(std::min<int>(m_nX, m_nY), m_nZ); };
	inline INT64 GetSize_XYZ_Max() const { return std::max<int>(std::max<int>(m_nX, m_nY), m_nZ); };

	inline INT64 GetSize_Slc() const { return m_nVoxPerSlc; };
	inline INT64 GetSize_Mtx() const { return m_nVoxTotal; };

	//[11_30 20:20:23 ]: 
	inline int GetSz_nVoxAbs_byCoordLeng_X(float fL) const { return fRound(qAbs<float>(fL / GetP3D_Spc_X())); };
	inline int GetSz_nVoxAbs_byCoordLeng_Y(float fL) const { return fRound(qAbs<float>(fL / GetP3D_Spc_Y())); };
	inline int GetSz_nVoxAbs_byCoordLeng_Z(float fL) const { return fRound(qAbs<float>(fL / GetP3D_Spc_Z())); };

	inline INT64 GetCountOfVoxel() const { return m_nVoxTotal; };

	inline INT64 GetUpperBound_X() const { return m_nX - 1; };
	inline INT64 GetUpperBound_Y() const { return m_nY - 1; };
	inline INT64 GetUpperBound_Z() const { return m_nZ - 1; };
	inline Pnt3D_Int GetUpperBound_XYZ() const { return Pnt3D_Int(GetUpperBound_X(), GetUpperBound_Y(), GetUpperBound_Z()); };

	//......................................................................................................................................
	inline BOOL IsIdx3_Valid(const INT64  iX, const INT64  iY, const INT64  iZ) const
	{
		return (iX >= 0 && iX < m_nX && iY >= 0 && iY < m_nY && iZ >= 0 && iZ < m_nZ);
	};
	inline BOOL IsIdx3_Valid(const SPnt3D_Int&	P3DIdx) const { return IsIdx3_Valid(P3DIdx[0], P3DIdx[1], P3DIdx[2]); };
	inline BOOL IsIdx3_Valid(const SPnt3D_Sht& P3DIdx)	const { return IsIdx3_Valid(P3DIdx[0], P3DIdx[1], P3DIdx[2]); };
	inline BOOL IsIdx3_Valid(const SPnt3D_UInt& P3DIdx) const { return IsIdx3_Valid(P3DIdx[0], P3DIdx[1], P3DIdx[2]); };
	inline BOOL IsIdx3_Valid(const SPnt3D_Flt& P3DIdx)	const { return IsIdx3_Valid(fRound(P3DIdx[0]), fRound(P3DIdx[1]), fRound(P3DIdx[2])); };
	inline BOOL IsIdx3_Valid(const SPnt3D_Dbl& P3DIdx)	const { return IsIdx3_Valid(fRound(P3DIdx[0]), fRound(P3DIdx[1]), fRound(P3DIdx[2])); };

	inline BOOL IsIdx3_Invalid(const INT64  iX, const INT64  iY, const INT64  iZ) const
	{
		return (iX < 0 || iX >= m_nX || iY < 0 || iY >= m_nY || iZ < 0 || iZ >= m_nZ);
	};
	inline BOOL IsIdx3_Invalid(const SPnt3D_Int&	P3DIdx) const { return IsIdx3_Invalid(P3DIdx[0], P3DIdx[1], P3DIdx[2]); };
	inline BOOL IsIdx3_Invalid(const SPnt3D_Sht&	P3DIdx) const { return IsIdx3_Invalid(P3DIdx[0], P3DIdx[1], P3DIdx[2]); };
	inline BOOL IsIdx3_Invalid(const SPnt3D_UInt&	P3DIdx) const { return IsIdx3_Invalid(P3DIdx[0], P3DIdx[1], P3DIdx[2]); };

	//[4_20 21:06:54 ]:
	inline BOOL IsIdx3_Cub_Valid(const Cub3D_Int& Cub) const { return  IsIdx3_Valid(Cub.m_P3D_Min) && IsIdx3_Valid(Cub.m_P3D_Max); };
	inline BOOL IsIdx3_Cub_Invalid(const Cub3D_Int& Cub) const { return !IsIdx3_Valid(Cub.m_P3D_Min) || !IsIdx3_Valid(Cub.m_P3D_Max); };

	//[20210429_14:20:48 ]:
	inline Cub3D_Int GetCub3D_Full() const { Cub3D_Int C3; C3.m_P3D_Min.Construct(0, 0, 0); C3.m_P3D_Max.Construct(m_nX - 1, m_nY - 1, m_nZ - 1); return C3; };

	inline BOOL IsValidIndex(INT64 iX, INT64 iY, INT64 iZ) const;
	inline BOOL IsIdx_Valid_X(const INT64  iX) const { return (iX >= 0 && iX < m_nX); };
	inline BOOL IsIdx_Valid_Y(const INT64  jY) const { return (jY >= 0 && jY < m_nY); };
	inline BOOL IsIdx_Valid_Z(const INT64  kZ) const { return (kZ >= 0 && kZ < m_nZ); };

	//三维索 <==> 一维索引:
	inline INT64	GetVoxID(const SPnt3D_Int& P3D) const;
	inline INT64	GetVoxID(const SPnt3D_UInt& P3D) const { return GetVoxID(P3D[0], P3D[1], P3D[2]); };
	inline INT64	GetVoxID(const INT64 iX, const INT64 iY, const INT64 iZ) const;

	inline void GetVoxIdx3D(const INT64 iVox, int& iX, int& iY, int& iZ) const;
	inline void GetVoxIdx3D(const INT64 iVox, SPnt3D_Int& P3D) const;
	inline void GetVoxIdx3D(const UINT iVox, UINT& iX, UINT& iY, UINT& iZ) const;
	inline void GetVoxIdx3D(const UINT iVox, SPnt3D_UInt& P3D) const;

	//浮点坐标 => 浮点索引(结果未必有效):
	inline void			GetVoxIdxFlt(SPnt3D_Flt& P3DIndex, const SPnt3D_Flt& P3DCoord) const;
	inline SPnt3D_Flt	GetVoxIdxFlt(SPnt3D_Flt P3DCoord) const;
	inline void			GetVoxIdxFlt(float& fIX, float& fIY, float& fIZ, float fx, float fy, float fz) const;

	inline float GetVoxIdxFlt_X(float fx) const;
	inline float GetVoxIdxFlt_Y(float fy) const;
	inline float GetVoxIdxFlt_Z(float fz) const;

	//三维索引有效化:
	inline void ValidateIdx(SPnt3D_Flt& P3DIdxValid) const;
	inline void ValidateIdx(SPnt3D_Int& P3DIdxValid) const;
	inline void ValidateIdx(SPnt3D_Sht& P3DIdxValid) const;

	inline void ValidateIdx_XY(Pnt2D_Int& P2DIdxValid) const
	{
		ValidateIdx_X(P2DIdxValid[0]);
		ValidateIdx_Y(P2DIdxValid[1]);
	};
	inline void ValidateIdx_XY(Pnt2D_Flt& P2DIdxValid) const
	{
		ValidateIdx_X(P2DIdxValid[0]);
		ValidateIdx_Y(P2DIdxValid[1]);
	};

	inline void ValidateIdx(Cub3D_Int& Cub3DIdxValid) const
	{
		ValidateIdx(Cub3DIdxValid.GetP3D_Min());
		ValidateIdx(Cub3DIdxValid.GetP3D_Max());
	};

	inline void ValidateIdx(Cub3D_Flt& Cub3DIdxValid) const
	{
		ValidateIdx(Cub3DIdxValid.GetP3D_Min());
		ValidateIdx(Cub3DIdxValid.GetP3D_Max());
	};

	inline void ValidateIdx(Rct2D_Int& Rct2DIdxValid) const
	{
		ValidateIdx_X(Rct2DIdxValid.xMIN);
		ValidateIdx_X(Rct2DIdxValid.xMAX);
		ValidateIdx_Y(Rct2DIdxValid.yMIN);
		ValidateIdx_Y(Rct2DIdxValid.yMAX);
	};

	inline void ValidateIdx(Rct2D_Flt& Rct2DIdxValid) const
	{
		ValidateIdx_X(Rct2DIdxValid.xMIN);
		ValidateIdx_X(Rct2DIdxValid.xMAX);
		ValidateIdx_Y(Rct2DIdxValid.yMIN);
		ValidateIdx_Y(Rct2DIdxValid.yMAX);
	};

	inline void ValidateIdx(float& fixValid, float& fiyValid, float& fizValid) const;
	inline void ValidateIdx(int& ixValid, int& iyValid, int& izValid) const;
	inline void ValidateIdx(short& ixValid, short& iyValid, short& izValid) const;

	inline void ValidateIdx_X(float& fix) const;
	inline void ValidateIdx_Y(float& fiy) const;
	inline void ValidateIdx_Z(float& fiz) const;

	inline void ValidateIdx_X(int& ix) const;
	inline void ValidateIdx_Y(int& iy) const;
	inline void ValidateIdx_Z(int& iz) const;

	inline void ValidateIdx_X(short& ix) const;
	inline void ValidateIdx_Y(short& iy) const;
	inline void ValidateIdx_Z(short& iz) const;

	//浮点坐标 => 整数索引(结果未必有效):
	inline void			GetVoxIdxInt(SPnt3D_Int& P3DIndex, const SPnt3D_Flt& P3DCoord) const;
	inline void			GetVoxIdxInt(SPnt3D_Int& P3DIndex, const SPnt3D_Dbl& P3DCoord) const;
	inline SPnt3D_Int	GetVoxIdxInt(SPnt3D_Flt P3DCoord) const
	{
		SPnt3D_Int PIdx;
		GetVoxIdxInt(PIdx, P3DCoord);
		return PIdx;
	};
	inline SPnt3D_Int	GetVoxIdxInt(SPnt3D_Dbl P3DCoord) const
	{
		SPnt3D_Int PIdx;
		GetVoxIdxInt(PIdx, P3DCoord);
		return PIdx;
	};

	inline void			GetVoxIdxInt_Valid(SPnt3D_Int& P3DIndex, const SPnt3D_Flt& P3DCoord) const { GetVoxIdxInt(P3DIndex, P3DCoord); ValidateIdx(P3DIndex); };
	inline void			GetVoxIdxInt_Valid(SPnt3D_Int& P3DIndex, const SPnt3D_Dbl& P3DCoord) const { GetVoxIdxInt(P3DIndex, P3DCoord); ValidateIdx(P3DIndex); };
	inline SPnt3D_Int	GetVoxIdxInt_Valid(SPnt3D_Flt P3DCoord) const
	{
		SPnt3D_Int PIdx;
		GetVoxIdxInt_Valid(PIdx, P3DCoord);
		return PIdx;
	};
	inline SPnt3D_Int	GetVoxIdxInt_Valid(SPnt3D_Dbl P3DCoord) const
	{
		SPnt3D_Int PIdx;
		GetVoxIdxInt_Valid(PIdx, P3DCoord);
		return PIdx;
	};

	inline int			GetVoxIdxInt_X(float fX) const { return fRound((fX - m_P3D_Bgn[0]) / m_P3D_Spc[0]); };
	inline int			GetVoxIdxInt_Y(float fY) const { return fRound((fY - m_P3D_Bgn[1]) / m_P3D_Spc[1]); };
	inline int			GetVoxIdxInt_Z(float fZ) const { return fRound((fZ - m_P3D_Bgn[2]) / m_P3D_Spc[2]); };

	inline int			GetVoxIdxInt_Valid_X(float fX) const { int iX = fRound((fX - m_P3D_Bgn[0]) / m_P3D_Spc[0]); ValidateIdx_X(iX); return iX; };
	inline int			GetVoxIdxInt_Valid_Y(float fY) const { int jY = fRound((fY - m_P3D_Bgn[1]) / m_P3D_Spc[1]); ValidateIdx_Y(jY); return jY; };
	inline int			GetVoxIdxInt_Valid_Z(float fZ) const { int kZ = fRound((fZ - m_P3D_Bgn[2]) / m_P3D_Spc[2]); ValidateIdx_Z(kZ); return kZ; };

	inline void			GetVoxIdxInt(int& iX, int& iY, int& iZ, float fx, float fy, float fz) const;
	inline INT64		GetVoxIdxIntNearest(float fx, float fy, float fz) const;
	inline void			GetVoxIdxIntNearest(int& iX, int& iY, int& iZ, float fx, float fy, float fz) const;

	inline void			GetVoxCoord(const INT64 iVox, SPnt3D_Flt& P3DCoord) const;
	inline void			GetVoxCoord(const INT64 iVox, float& fX, float& fY, float& fZ) const;
	inline void			GetVoxCoord(const SPnt3D_Int& P3DIdx, SPnt3D_Flt& P3DCoord) const;
	inline void			GetVoxCoord(const SPnt3D_Flt& P3D_fIdx, SPnt3D_Flt& P3DCoord) const;
	inline void			GetVoxCoord(const SPnt3D_Dbl& P3D_fIdx, SPnt3D_Dbl& P3DCoord) const;
	inline void			GetVoxCoord(const SPnt3D_Int& P3DIdx, float& fX, float& fY, float& fZ) const;
	inline void			GetVoxCoord(INT64 i, INT64 j, INT64 k, SPnt3D_Flt& P3DCoord) const;
	inline void			GetVoxCoord(INT64 i, INT64 j, INT64 k, float& fX, float& fY, float& fZ) const;
	inline SPnt3D_Flt	GetVoxCoord(INT64 i, INT64 j, INT64 k) const;

	inline SPnt3D_Flt	GetVoxCoord(SPnt3D_Int Pijk) const;
	inline SPnt3D_Flt	GetVoxCoord_Flt(SPnt3D_Int Pijk) const;
	inline SPnt3D_Dbl	GetVoxCoord_Dbl(SPnt3D_Int Pijk) const;

	inline SPnt3D_Flt	GetVoxCoord(SPnt3D_Flt P3D_fIdx) const;
	inline SPnt3D_Flt	GetVoxCoord_Flt(SPnt3D_Flt P3D_fIdx) const;
	inline SPnt3D_Dbl	GetVoxCoord_Dbl(SPnt3D_Flt P3D_fIdx) const;

	inline SPnt3D_Dbl	GetVoxCoord(SPnt3D_Dbl P3D_fIdx) const;
	inline SPnt3D_Flt	GetVoxCoord_Flt(SPnt3D_Dbl P3D_fIdx) const;
	inline SPnt3D_Dbl	GetVoxCoord_Dbl(SPnt3D_Dbl P3D_fIdx) const;

	inline float GetVoxCoord_X(INT64 iX) const;
	inline float GetVoxCoord_Y(INT64 iY) const;
	inline float GetVoxCoord_Z(INT64 iZ) const;

	inline void GetSlcCoord_Z(std::vector<float>& Arr_fZPosImg_PatSys) const
	{
		Arr_fZPosImg_PatSys.resize(GetSize_Z());
		for (int k = 0; k < Arr_fZPosImg_PatSys.size(); k++)
		{
			Arr_fZPosImg_PatSys[k] = GetVoxCoord_Z(k);
		}
	};
	//......................................................................................................................................
	virtual void CopyGrid(const CSPN_Cmn_3DMtx_Grid<TP_Crd>& MtxGrid_Src)
	{
		if (&MtxGrid_Src == this)
			return;

		if (IsGridSameAs(MtxGrid_Src))
		{
			return; // 避免经由Set_nXYZ()的派生层实现引起不必要的重新内存分配, 进而导致挂接内存"失联"!
		}
		*this = MtxGrid_Src;
	};
	virtual void CopyGrid_noAlloc(const CSPN_Cmn_3DMtx_Grid<TP_Crd>& MtxGrid_Src)
	{
		if (&MtxGrid_Src == this)
			return;

		if (IsGridSameAs(MtxGrid_Src))
		{
			return; // 避免经由Set_nXYZ()的派生层实现引起不必要的重新内存分配, 进而导致挂接内存"失联"!
		}

		CopyGrid_Count_noAlloc(MtxGrid_Src);
		CopyGrid_CoordBgn(MtxGrid_Src);
		CopyGrid_CoordSpc(MtxGrid_Src);

		MtxGrid_Src.GetIJKTORASMatrix(m_IJKToRASMatrix);//[6_21 0:39:36 ]: 需要考虑移除外面处理, 不应放在此数据层!
	};
	virtual void CopyGrid_Count(const CSPN_Cmn_3DMtx_Grid<TP_Crd>& MtxGrid_Src)
	{
		if (&MtxGrid_Src == this)
			return;

		if (IsGridSame_Count_As(MtxGrid_Src))
		{
			return; // 避免经由Set_nXYZ()的派生层实现引起不必要的重新内存分配, 进而导致挂接内存"失联"!
		}

		Set_nXYZ(MtxGrid_Src.m_nX, MtxGrid_Src.m_nY, MtxGrid_Src.m_nZ); // 多态!
		VoxGeo_Construct_TmpAttr();
	};
	virtual void CopyGrid_Count_noAlloc(const CSPN_Cmn_3DMtx_Grid<TP_Crd>& MtxGrid_Src)
	{
		if (&MtxGrid_Src == this)
			return;

		if (IsGridSame_Count_As(MtxGrid_Src))
		{
			return; // 避免经由Set_nXYZ()的派生层实现引起不必要的重新内存分配, 进而导致挂接内存"失联"!
		}

		Set_nXYZ_noAlloc(MtxGrid_Src.m_nX, MtxGrid_Src.m_nY, MtxGrid_Src.m_nZ); // 多态!
		VoxGeo_Construct_TmpAttr();
	};
	virtual void CopyGrid_CoordBgn(const CSPN_Cmn_3DMtx_Grid<TP_Crd>& MtxGrid_Src)
	{
		if (&MtxGrid_Src == this)
			return;
		m_P3D_Bgn = MtxGrid_Src.m_P3D_Bgn;
	};
	virtual void CopyGrid_CoordSpc(const CSPN_Cmn_3DMtx_Grid<TP_Crd>& MtxGrid_Src)
	{
		if (&MtxGrid_Src == this)
			return;
		m_P3D_Spc = MtxGrid_Src.m_P3D_Spc;
	};

	virtual void CopyGrid_Coord(const CSPN_Cmn_3DMtx_Grid<TP_Crd>& MtxGrid_Src)//[9_6 14:34:21 ]:
	{
		CopyGrid_CoordBgn(MtxGrid_Src);
		CopyGrid_CoordSpc(MtxGrid_Src);
	};

	const CSPN_Cmn_3DMtx_Grid& operator=(const CSPN_Cmn_3DMtx_Grid<TP_Crd>& MtxGrid_Src)
	{
		if (&MtxGrid_Src != this)
		{
			CopyGrid_Count(MtxGrid_Src);
			CopyGrid_CoordBgn(MtxGrid_Src);
			CopyGrid_CoordSpc(MtxGrid_Src);
		}

		MtxGrid_Src.GetIJKTORASMatrix(m_IJKToRASMatrix);//[6_21 0:39:36 ]: 需要考虑移除外面处理, 不应放在此数据层!

		return *this;
	};

	//......................................................................................................................................
	//计算长度: 
	inline float GetLength_X() const { return m_nX * m_P3D_Spc[0]; };
	inline float GetLength_Y() const { return m_nY * m_P3D_Spc[1]; };
	inline float GetLength_Z() const { return m_nZ * m_P3D_Spc[2]; };

	//计算面积: 
	inline float GetArea_SlcXY() const;
	inline float GetArea_SlcYZ() const;
	inline float GetArea_SlcZX() const;

	//计算体积:
	inline float GetVolume() const;
	inline float GetVolume_aVox() const { return qAbs(m_P3D_Spc[0] * m_P3D_Spc[1] * m_P3D_Spc[2]); };//计算一个体素体积

	//......................................................................................................................................
	float GetVoxMaxDisToVertex(SSPN_Cmn_3DPoint<TP_Crd> P3D_Cntr);//已知点到VoxMtx个顶点的最大距离
	//......................................................................................................................................

	//virtual void Serialize(CSPN_Cmn_Archive& Ar);

	//#ifdef _DEBUG
	//	void DBG_TraceMtx() const;
	//#endif // 

		//Implementation:
protected:
};

//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
template<typename TP_Crd>
CSPN_Cmn_3DMtx_Grid<TP_Crd>::CSPN_Cmn_3DMtx_Grid()
{
	Reset_All();
};

//-----------------------------------------------------------------------------------
template<typename TP_Crd>
void CSPN_Cmn_3DMtx_Grid<TP_Crd>::Reset_All()
{
	//Reset_Mem();
	Reset_Geo();
}

//-----------------------------------------------------------------------------------
template<typename TP_Crd>
void CSPN_Cmn_3DMtx_Grid<TP_Crd>::Reset_Geo()
{
	m_P3D_Spc[0] = 0.f;//体素三向间隔
	m_P3D_Spc[1] = 0.f;
	m_P3D_Spc[2] = 0.f;

	m_P3D_Bgn.Construct(0, 0, 0);
	m_nVoxTotal = 0;//体素总数
	m_nVoxPerSlc = 0;//每切片象素数
	//m_nBytePerSlc = 0;//每切片占用字节数

	for (int i = 0; i < 4; i++)//[10_26 18:18:54 liuzhiwen]: IJK to RAS 方向矩阵
	{
		for (int j = 0; j < 4; j++)
		{
			if (i == j)
				m_IJKToRASMatrix[i][j] = 1;
			else
				m_IJKToRASMatrix[i][j] = 0;
		}
	}
};

//-----------------------------------------------------------------------------------
template<typename TP_Crd>
CSPN_Cmn_3DMtx_Grid<TP_Crd>::CSPN_Cmn_3DMtx_Grid(const CSPN_Cmn_3DMtx_Grid<TP_Crd>& MtxGrid)
{
	CopyGrid(MtxGrid);
};

//-----------------------------------------------------------------------------------
template<typename TP_Crd>
CSPN_Cmn_3DMtx_Grid<TP_Crd>::~CSPN_Cmn_3DMtx_Grid()
{
	Reset_All();
};

//-----------------------------------------------------------------------------------
//根据浮点坐标取得浮点索引(结果未必有效):
template<typename TP_Crd>
inline void CSPN_Cmn_3DMtx_Grid<TP_Crd>::GetVoxIdxFlt(SPnt3D_Flt& P3DIndex, const SPnt3D_Flt& P3DCoord) const
{
	assert(!FLT_EQ(0.0f, m_P3D_Spc[0]));
	assert(!FLT_EQ(0.0f, m_P3D_Spc[1]));
	assert(!FLT_EQ(0.0f, m_P3D_Spc[2]));

	P3DIndex[0] = (P3DCoord[0] - m_P3D_Bgn[0]) / m_P3D_Spc[0];
	P3DIndex[1] = (P3DCoord[1] - m_P3D_Bgn[1]) / m_P3D_Spc[1];
	P3DIndex[2] = (P3DCoord[2] - m_P3D_Bgn[2]) / m_P3D_Spc[2];
};
template<typename TP_Crd>
inline SPnt3D_Flt CSPN_Cmn_3DMtx_Grid<TP_Crd>::GetVoxIdxFlt(SPnt3D_Flt P3DCoord) const
{
	SPnt3D_Flt P3D_fIdx;
	GetVoxIdxFlt(P3D_fIdx, P3DCoord);
	return P3D_fIdx;
};

//-----------------------------------------------------------------------------------
//根据浮点坐标取得浮点索引(结果未必有效):
template<typename TP_Crd>
inline void CSPN_Cmn_3DMtx_Grid<TP_Crd>::GetVoxIdxFlt(float& fIX, float& fIY, float& fIZ, float fx, float fy, float fz) const
{
	assert(!FLT_EQ(0.0f, m_P3D_Spc[0]));
	assert(!FLT_EQ(0.0f, m_P3D_Spc[1]));
	assert(!FLT_EQ(0.0f, m_P3D_Spc[2]));

	fIX = (fx - m_P3D_Bgn[0]) / m_P3D_Spc[0];
	fIY = (fy - m_P3D_Bgn[1]) / m_P3D_Spc[1];
	fIZ = (fz - m_P3D_Bgn[2]) / m_P3D_Spc[2];
};
//-----------------------------------------------------------------------------------
//根据浮点坐标取得浮点索引(结果未必有效):
template<typename TP_Crd>
inline float CSPN_Cmn_3DMtx_Grid<TP_Crd>::GetVoxIdxFlt_X(float fx) const
{
	assert(!FLT_EQ(0.0f, m_P3D_Spc[0]));
	return (fx - m_P3D_Bgn[0]) / m_P3D_Spc[0];
};
template<typename TP_Crd>
inline float CSPN_Cmn_3DMtx_Grid<TP_Crd>::GetVoxIdxFlt_Y(float fy) const
{
	assert(!FLT_EQ(0.0f, m_P3D_Spc[1]));
	return (fy - m_P3D_Bgn[1]) / m_P3D_Spc[1];
};
template<typename TP_Crd>
inline float CSPN_Cmn_3DMtx_Grid<TP_Crd>::GetVoxIdxFlt_Z(float fz) const
{
	assert(!FLT_EQ(0.0f, m_P3D_Spc[2]));
	return (fz - m_P3D_Bgn[2]) / m_P3D_Spc[2];
};
//-----------------------------------------------------------------------------------
//根据浮点坐标取得整数索引(结果未必有效):
template<typename TP_Crd>
inline void CSPN_Cmn_3DMtx_Grid<TP_Crd>::GetVoxIdxInt(SPnt3D_Int& P3DIndex, const SPnt3D_Flt& P3DCoord) const
{
	assert(!FLT_EQ(0.0f, m_P3D_Spc[0]));
	assert(!FLT_EQ(0.0f, m_P3D_Spc[1]));
	assert(!FLT_EQ(0.0f, m_P3D_Spc[2]));

	P3DIndex[0] = fRound((P3DCoord[0] - m_P3D_Bgn[0]) / m_P3D_Spc[0]);
	P3DIndex[1] = fRound((P3DCoord[1] - m_P3D_Bgn[1]) / m_P3D_Spc[1]);
	P3DIndex[2] = fRound((P3DCoord[2] - m_P3D_Bgn[2]) / m_P3D_Spc[2]);
};
template<typename TP_Crd>
inline void CSPN_Cmn_3DMtx_Grid<TP_Crd>::GetVoxIdxInt(SPnt3D_Int& P3DIndex, const SPnt3D_Dbl& P3DCoord) const
{
	assert(!FLT_EQ(0.0f, m_P3D_Spc[0]));
	assert(!FLT_EQ(0.0f, m_P3D_Spc[1]));
	assert(!FLT_EQ(0.0f, m_P3D_Spc[2]));

	P3DIndex[0] = fRound((P3DCoord[0] - m_P3D_Bgn[0]) / m_P3D_Spc[0]);
	P3DIndex[1] = fRound((P3DCoord[1] - m_P3D_Bgn[1]) / m_P3D_Spc[1]);
	P3DIndex[2] = fRound((P3DCoord[2] - m_P3D_Bgn[2]) / m_P3D_Spc[2]);
};

//-----------------------------------------------------------------------------------
//根据浮点坐标取得整数索引(结果未必有效):
template<typename TP_Crd>
inline void CSPN_Cmn_3DMtx_Grid<TP_Crd>::GetVoxIdxInt(int& iX, int& iY, int& iZ, float fx, float fy, float fz) const
{
	assert(!FLT_EQ(0.0f, m_P3D_Spc[0]));
	assert(!FLT_EQ(0.0f, m_P3D_Spc[1]));
	assert(!FLT_EQ(0.0f, m_P3D_Spc[2]));

	iX = fRound((fx - m_P3D_Bgn[0]) / m_P3D_Spc[0]);
	iY = fRound((fy - m_P3D_Bgn[1]) / m_P3D_Spc[1]);
	iZ = fRound((fz - m_P3D_Bgn[2]) / m_P3D_Spc[2]);
};
//-----------------------------------------------------------------------------------
//根据浮点坐标取得整数索引(结果保证有效):
template<typename TP_Crd>
inline void CSPN_Cmn_3DMtx_Grid<TP_Crd>::GetVoxIdxIntNearest(int& iX, int& iY, int& iZ, float fx, float fy, float fz) const
{
	assert(!FLT_EQ(0.0f, m_P3D_Spc[0]));
	assert(!FLT_EQ(0.0f, m_P3D_Spc[1]));
	assert(!FLT_EQ(0.0f, m_P3D_Spc[2]));

	iX = fRound((fx - m_P3D_Bgn[0]) / m_P3D_Spc[0]);
	iY = fRound((fy - m_P3D_Bgn[1]) / m_P3D_Spc[1]);
	iZ = fRound((fz - m_P3D_Bgn[2]) / m_P3D_Spc[2]);

	CutIntoRange<int>(iX, 0, m_nX - 1);
	CutIntoRange<int>(iY, 0, m_nY - 1);
	CutIntoRange<int>(iZ, 0, m_nZ - 1);
};
//-----------------------------------------------------------------------------------
//根据浮点坐标取得整数索引(结果保证有效):
template<typename TP_Crd>
inline INT64 CSPN_Cmn_3DMtx_Grid<TP_Crd>::GetVoxIdxIntNearest(float fx, float fy, float fz) const
{
	//此处为加速, 不进行初始化(有违常理)
	int iX;
	int iY;
	int iZ;

	GetVoxIdxIntNearest(iX, iY, iZ, fx, fy, fz);

	return GetVoxID(iX, iY, iZ);
};

template<typename TP_Crd>
inline void CSPN_Cmn_3DMtx_Grid<TP_Crd>::VoxGeo_Construct_TmpAttr()
{
	//下列成员用于快速存取之优化：
	m_nVoxPerSlc = m_nX * m_nY;						//每切片象素数
	m_nVoxTotal = m_nZ * m_nVoxPerSlc;

	this->m_Arr_nVoxPreRowsInSlc_Y.SetSize(m_nY);	//每个体素所在行以前的全部行中所包含的体素个数(切片内因行引起的偏移, 因列引起的偏移为x)
	{
		int iYAccum = 0;
		for (int iY = 0; iY < m_nY; iY++, iYAccum += m_nX)
		{
			this->m_Arr_nVoxPreRowsInSlc_Y[iY] = iYAccum;
		}
	}
};

template<typename TP_Crd>
inline void CSPN_Cmn_3DMtx_Grid<TP_Crd>::SetP3D_Spc(const float fSpacingX, const float fSpacingY, const float fSpacingZ)
{
	m_P3D_Spc[0] = fSpacingX;
	m_P3D_Spc[1] = fSpacingY;
	m_P3D_Spc[2] = fSpacingZ;
};

template<typename TP_Crd>
inline INT64 CSPN_Cmn_3DMtx_Grid<TP_Crd>::GetVoxID(const SPnt3D_Int& P3D) const
{
	assert(IsIdx3_Valid(P3D));
	INT64 iVox = P3D[2] * m_nVoxPerSlc + P3D[1] * m_nX + P3D[0];
	return iVox;
};

template<typename TP_Crd>
inline INT64 CSPN_Cmn_3DMtx_Grid<TP_Crd>::GetVoxID(const INT64 iX, const INT64 iY, const INT64 iZ) const
{
	assert(IsIdx3_Valid(iX, iY, iZ));
	INT64 iVox = iZ * m_nVoxPerSlc + iY * m_nX + iX;
	return iVox;
};

//-----------------------------------------------------------------------------------
template<typename TP_Crd> inline float CSPN_Cmn_3DMtx_Grid<TP_Crd>::GetVoxCoord_X(INT64 iX) const { return m_P3D_Bgn[0] + m_P3D_Spc[0] * iX; };
template<typename TP_Crd> inline float CSPN_Cmn_3DMtx_Grid<TP_Crd>::GetVoxCoord_Y(INT64 iY) const { return m_P3D_Bgn[1] + m_P3D_Spc[1] * iY; };
template<typename TP_Crd> inline float CSPN_Cmn_3DMtx_Grid<TP_Crd>::GetVoxCoord_Z(INT64 iZ) const { return m_P3D_Bgn[2] + m_P3D_Spc[2] * iZ; };

template<typename TP_Crd>
inline void CSPN_Cmn_3DMtx_Grid<TP_Crd>::GetVoxCoord(INT64 i, INT64 j, INT64 k, SPnt3D_Flt& P3DCoord) const
{
	P3DCoord[0] = m_P3D_Bgn[0] + m_P3D_Spc[0] * i;
	P3DCoord[1] = m_P3D_Bgn[1] + m_P3D_Spc[1] * j;
	P3DCoord[2] = m_P3D_Bgn[2] + m_P3D_Spc[2] * k;
};

template<typename TP_Crd>
inline SPnt3D_Flt CSPN_Cmn_3DMtx_Grid<TP_Crd>::GetVoxCoord(INT64 i, INT64 j, INT64 k) const
{
	SPnt3D_Flt P3DCoord;
	P3DCoord[0] = m_P3D_Bgn[0] + m_P3D_Spc[0] * i;
	P3DCoord[1] = m_P3D_Bgn[1] + m_P3D_Spc[1] * j;
	P3DCoord[2] = m_P3D_Bgn[2] + m_P3D_Spc[2] * k;
	return P3DCoord;
};

template<typename TP_Crd>
inline SPnt3D_Flt CSPN_Cmn_3DMtx_Grid<TP_Crd>::GetVoxCoord(SPnt3D_Int Pijk) const
{
	SPnt3D_Flt P3DCoord;
	P3DCoord[0] = m_P3D_Bgn[0] + m_P3D_Spc[0] * Pijk[0];
	P3DCoord[1] = m_P3D_Bgn[1] + m_P3D_Spc[1] * Pijk[1];
	P3DCoord[2] = m_P3D_Bgn[2] + m_P3D_Spc[2] * Pijk[2];
	return P3DCoord;
};

template<typename TP_Crd>
inline SPnt3D_Flt CSPN_Cmn_3DMtx_Grid<TP_Crd>::GetVoxCoord_Flt(SPnt3D_Int Pijk) const
{
	return GetVoxCoord(Pijk).ToFloat();
};

template<typename TP_Crd>
inline SPnt3D_Dbl CSPN_Cmn_3DMtx_Grid<TP_Crd>::GetVoxCoord_Dbl(SPnt3D_Int Pijk) const
{
	return GetVoxCoord(Pijk).ToDouble();
};

template<typename TP_Crd>
inline SPnt3D_Flt CSPN_Cmn_3DMtx_Grid<TP_Crd>::GetVoxCoord(SPnt3D_Flt P3D_fIdx) const
{
	SPnt3D_Flt P3DCoord;
	P3DCoord[0] = m_P3D_Bgn[0] + m_P3D_Spc[0] * P3D_fIdx[0];
	P3DCoord[1] = m_P3D_Bgn[1] + m_P3D_Spc[1] * P3D_fIdx[1];
	P3DCoord[2] = m_P3D_Bgn[2] + m_P3D_Spc[2] * P3D_fIdx[2];
	return P3DCoord;
};

template<typename TP_Crd>
inline SPnt3D_Flt CSPN_Cmn_3DMtx_Grid<TP_Crd>::GetVoxCoord_Flt(SPnt3D_Flt P3D_fIdx) const
{
	return GetVoxCoord(P3D_fIdx).ToFloat();
};

template<typename TP_Crd>
inline SPnt3D_Dbl CSPN_Cmn_3DMtx_Grid<TP_Crd>::GetVoxCoord_Dbl(SPnt3D_Flt P3D_fIdx) const
{
	return GetVoxCoord(P3D_fIdx).ToDouble();
};

template<typename TP_Crd>
inline SPnt3D_Dbl CSPN_Cmn_3DMtx_Grid<TP_Crd>::GetVoxCoord(SPnt3D_Dbl P3D_fIdx) const
{
	SPnt3D_Dbl P3DCoord;
	P3DCoord[0] = m_P3D_Bgn[0] + m_P3D_Spc[0] * P3D_fIdx[0];
	P3DCoord[1] = m_P3D_Bgn[1] + m_P3D_Spc[1] * P3D_fIdx[1];
	P3DCoord[2] = m_P3D_Bgn[2] + m_P3D_Spc[2] * P3D_fIdx[2];
	return P3DCoord;
};
template<typename TP_Crd>
inline SPnt3D_Flt CSPN_Cmn_3DMtx_Grid<TP_Crd>::GetVoxCoord_Flt(SPnt3D_Dbl P3D_fIdx) const
{
	return GetVoxCoord(P3D_fIdx).ToFloat();
};

template<typename TP_Crd>
inline SPnt3D_Dbl CSPN_Cmn_3DMtx_Grid<TP_Crd>::GetVoxCoord_Dbl(SPnt3D_Dbl P3D_fIdx) const
{
	return GetVoxCoord(P3D_fIdx).ToDouble();
};

template<typename TP_Crd>
inline void CSPN_Cmn_3DMtx_Grid<TP_Crd>::GetVoxCoord(INT64 i, INT64 j, INT64 k, float& fX, float& fY, float& fZ) const
{
	fX = m_P3D_Bgn[0] + m_P3D_Spc[0] * i;
	fY = m_P3D_Bgn[1] + m_P3D_Spc[1] * j;
	fZ = m_P3D_Bgn[2] + m_P3D_Spc[2] * k;
};

template<typename TP_Crd>
inline void CSPN_Cmn_3DMtx_Grid<TP_Crd>::GetVoxCoord(const INT64 iVox, SPnt3D_Flt& P3DCoord) const
{
	//	assert(iVox < m_nVoxTotal);
	P3DCoord[0] = m_P3D_Bgn[0] + m_P3D_Spc[0] * (iVox % m_nX);
	P3DCoord[1] = m_P3D_Bgn[1] + m_P3D_Spc[1] * ((iVox % m_nVoxPerSlc) / m_nX);
	P3DCoord[2] = m_P3D_Bgn[2] + m_P3D_Spc[2] * ((iVox / m_nVoxPerSlc));
};

template<typename TP_Crd>
inline void CSPN_Cmn_3DMtx_Grid<TP_Crd>::GetVoxCoord(const INT64 iVox, float& fX, float& fY, float& fZ) const
{
	//	assert(iVox < m_nVoxTotal);
	fX = m_P3D_Bgn[0] + m_P3D_Spc[0] * (iVox % m_nX);
	fY = m_P3D_Bgn[1] + m_P3D_Spc[1] * ((iVox % m_nVoxPerSlc) / m_nX);
	fZ = m_P3D_Bgn[2] + m_P3D_Spc[2] * ((iVox / m_nVoxPerSlc));
};

template<typename TP_Crd>
inline void CSPN_Cmn_3DMtx_Grid<TP_Crd>::GetVoxCoord(const SPnt3D_Int& P3DIdx, SPnt3D_Flt& P3DCoord) const
{
	//	assert(IsIdx3_Valid(P3DIdx));
	P3DCoord[0] = m_P3D_Bgn[0] + m_P3D_Spc[0] * P3DIdx[0];
	P3DCoord[1] = m_P3D_Bgn[1] + m_P3D_Spc[1] * P3DIdx[1];
	P3DCoord[2] = m_P3D_Bgn[2] + m_P3D_Spc[2] * P3DIdx[2];
};

template<typename TP_Crd>
inline void CSPN_Cmn_3DMtx_Grid<TP_Crd>::GetVoxCoord(const SPnt3D_Flt& P3D_fIdx, SPnt3D_Flt& P3DCoord) const
{
	//	assert(IsIdx3_Valid(P3DIdx));
	P3DCoord[0] = m_P3D_Bgn[0] + m_P3D_Spc[0] * P3D_fIdx[0];
	P3DCoord[1] = m_P3D_Bgn[1] + m_P3D_Spc[1] * P3D_fIdx[1];
	P3DCoord[2] = m_P3D_Bgn[2] + m_P3D_Spc[2] * P3D_fIdx[2];
};


template<typename TP_Crd>
inline void CSPN_Cmn_3DMtx_Grid<TP_Crd>::GetVoxCoord(const SPnt3D_Dbl& P3D_fIdx, SPnt3D_Dbl& P3DCoord) const
{
	//	assert(IsIdx3_Valid(P3DIdx));
	P3DCoord[0] = m_P3D_Bgn[0] + m_P3D_Spc[0] * P3D_fIdx[0];
	P3DCoord[1] = m_P3D_Bgn[1] + m_P3D_Spc[1] * P3D_fIdx[1];
	P3DCoord[2] = m_P3D_Bgn[2] + m_P3D_Spc[2] * P3D_fIdx[2];
};

template<typename TP_Crd>
inline void CSPN_Cmn_3DMtx_Grid<TP_Crd>::GetVoxCoord(const SPnt3D_Int& P3DIdx, float& fX, float& fY, float& fZ) const
{
	//	assert(IsIdx3_Valid(P3DIdx));
	fX = m_P3D_Bgn[0] + m_P3D_Spc[0] * P3DIdx[0];
	fY = m_P3D_Bgn[1] + m_P3D_Spc[1] * P3DIdx[1];
	fZ = m_P3D_Bgn[2] + m_P3D_Spc[2] * P3DIdx[2];
};
//-----------------------------------------------------------------------------------
template<typename TP_Crd>
inline void CSPN_Cmn_3DMtx_Grid<TP_Crd>::GetP3D_Center_VoxCoord(SPnt3D_Flt& P3D_Cntr) const
{
	P3D_Cntr[0] = m_P3D_Bgn[0] + m_P3D_Spc[0] * (GetSize_X() - 1) / 2;
	P3D_Cntr[1] = m_P3D_Bgn[1] + m_P3D_Spc[1] * (GetSize_Y() - 1) / 2;
	P3D_Cntr[2] = m_P3D_Bgn[2] + m_P3D_Spc[2] * (GetSize_Z() - 1) / 2;
};
//-----------------------------------------------------------------------------------
template<typename TP_Crd>
inline void CSPN_Cmn_3DMtx_Grid<TP_Crd>::GetP3D_Center_VoxIndex(SPnt3D_Int& P3D_Cntr) const
{
	P3D_Cntr[0] = GetSize_X() / 2;
	P3D_Cntr[1] = GetSize_Y() / 2;
	P3D_Cntr[2] = GetSize_Z() / 2;
};
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------                                                                    
template<typename TP_Crd>
inline void CSPN_Cmn_3DMtx_Grid<TP_Crd>::GetVoxIdx3D(const INT64 iVox, SPnt3D_Int& P3D) const
{
	//	assert(iVox < m_nVoxTotal);
	P3D[0] = iVox % m_nX;
	P3D[1] = (iVox % m_nVoxPerSlc) / m_nX;
	P3D[2] = (iVox / m_nVoxPerSlc);
};

//-----------------------------------------------------------------------------------
template<typename TP_Crd>
inline void CSPN_Cmn_3DMtx_Grid<TP_Crd>::GetVoxIdx3D(const INT64 iVox, int& iX, int& iY, int& iZ) const
{
	//	assert(iVox < m_nVoxTotal);
	iX = iVox % m_nX;
	iY = (iVox % m_nVoxPerSlc) / m_nX;
	iZ = (iVox / m_nVoxPerSlc);
};
//-----------------------------------------------------------------------------------                                                                    
template<typename TP_Crd>
inline void CSPN_Cmn_3DMtx_Grid<TP_Crd>::GetVoxIdx3D(const UINT iVox, SPnt3D_UInt& P3D) const
{
	//	assert(iVox < m_nVoxTotal);
	INT64 intVox = INT64(iVox);
	P3D[0] = UINT(intVox % m_nX);
	P3D[1] = UINT((intVox % m_nVoxPerSlc) / m_nX);
	P3D[2] = UINT((intVox / m_nVoxPerSlc));
};

//-----------------------------------------------------------------------------------
template<typename TP_Crd>
inline void CSPN_Cmn_3DMtx_Grid<TP_Crd>::GetVoxIdx3D(const UINT iVox, UINT& iX, UINT& iY, UINT& iZ) const
{
	//	assert(iVox < m_nVoxTotal);
	INT64 intVox = INT64(iVox);
	iX = UINT(intVox % m_nX);
	iY = UINT((intVox % m_nVoxPerSlc) / m_nX);
	iZ = UINT((intVox / m_nVoxPerSlc));
};

//template<typename TP_Crd>
//void CSPN_Cmn_3DMtx_Grid<TP_Crd>::Serialize(CSPN_Cmn_Archive& Ar)
//{
//	if (Ar.IsStoring())
//	{
//		int iVer = 1;
//		Ar << iVer;
//
//		Ar << m_nX;		//体数据的三向体素个数长度
//		Ar << m_nY;
//		Ar << m_nZ;
//
//		Ar << m_P3D_Spc[0];//体素三向间隔
//		Ar << m_P3D_Spc[1];
//		Ar << m_P3D_Spc[2];
//
//		m_P3D_Bgn.Serialize(Ar);
//	}
//	else
//	{
//		int iVer = 0;
//		Ar >> iVer;
//		switch (iVer)
//		{
//		case 1:
//			Ar >> m_nX;		//体数据的三向体素个数长度
//			Ar >> m_nY;
//			Ar >> m_nZ;
//
//			Ar >> m_P3D_Spc[0];//体素三向间隔
//			Ar >> m_P3D_Spc[1];
//			Ar >> m_P3D_Spc[2];
//
//			m_P3D_Bgn.Serialize(Ar);
//			break;
//		default:
//			;//::ShowMsg (/*_T*/("遇到无法识别的CSPN_Cmn_3DMtx_Grid对象版本!!!"));
//		}
//	}
//}

template<typename TP_Crd>
BOOL CSPN_Cmn_3DMtx_Grid<TP_Crd>::IsValidIndex(INT64 iX, INT64 iY, INT64 iZ) const
{
	return
		iX >= 0 && iX < GetSize_X() &&
		iY >= 0 && iY < GetSize_Y() &&
		iZ >= 0 && iZ < GetSize_Z();
}

//-----------------------------------------------------------------------------------

//计算面积: 
template<typename TP_Crd>
float CSPN_Cmn_3DMtx_Grid<TP_Crd>::GetArea_SlcXY() const { return m_nX * m_nY * m_P3D_Spc[0] * m_P3D_Spc[1]; };

template<typename TP_Crd>
float CSPN_Cmn_3DMtx_Grid<TP_Crd>::GetArea_SlcYZ() const { return m_nY * m_nZ * m_P3D_Spc[1] * m_P3D_Spc[2]; };

template<typename TP_Crd>
float CSPN_Cmn_3DMtx_Grid<TP_Crd>::GetArea_SlcZX() const { return m_nZ * m_nX * m_P3D_Spc[2] * m_P3D_Spc[0]; };

//-----------------------------------------------------------------------------------

//计算体积:
template<typename TP_Crd>
float CSPN_Cmn_3DMtx_Grid<TP_Crd>::GetVolume() const
{
	return m_nVoxTotal * m_P3D_Spc[0] * m_P3D_Spc[1] * m_P3D_Spc[2];
};
//-----------------------------------------------------------------------------------

//已知点到VoxMtx个顶点的最大距离

template<typename TP_Crd>
float CSPN_Cmn_3DMtx_Grid<TP_Crd>::GetVoxMaxDisToVertex(SSPN_Cmn_3DPoint<TP_Crd> P3D_Cntr)
{
	CSPN_Cmn_CArray<SSPN_Cmn_3DPoint<TP_Crd>, SSPN_Cmn_3DPoint<TP_Crd> &> ARR_P3D;
	ARR_P3D.SetSize(8);

	CSPN_Cmn_3DPoint<TP_Crd> P3D_X1Y0Z0(m_P3D_Bgn[0] + m_P3D_Spc[0] * m_nX, m_P3D_Bgn[1], m_P3D_Bgn[2]);
	CSPN_Cmn_3DPoint<TP_Crd> P3D_X0Y1Z0(m_P3D_Bgn[0], m_P3D_Bgn[1] + m_P3D_Spc[1] * m_nY, m_P3D_Bgn[2]);
	CSPN_Cmn_3DPoint<TP_Crd> P3D_X1Y1Z0(m_P3D_Bgn[0] + m_P3D_Spc[0] * m_nX, m_P3D_Bgn[1] + m_P3D_Spc[1] * m_nY, m_P3D_Bgn[2]);
	CSPN_Cmn_3DPoint<TP_Crd> P3D_X0Y0Z1(m_P3D_Bgn[0], m_P3D_Bgn[1], m_P3D_Bgn[2] + m_P3D_Spc[2] * m_nZ);
	CSPN_Cmn_3DPoint<TP_Crd> P3D_X1Y0Z1(m_P3D_Bgn[0] + m_P3D_Spc[0] * m_nX, m_P3D_Bgn[1], m_P3D_Bgn[2] + m_P3D_Spc[2] * m_nZ);
	CSPN_Cmn_3DPoint<TP_Crd> P3D_X0Y1Z1(m_P3D_Bgn[0], m_P3D_Bgn[1] + m_P3D_Spc[1] * m_nY, m_P3D_Bgn[2] + m_P3D_Spc[2] * m_nZ);
	CSPN_Cmn_3DPoint<TP_Crd> P3D_X1Y1Z1(m_P3D_Bgn[0] + m_P3D_Spc[0] * m_nX, m_P3D_Bgn[1] + m_P3D_Spc[1] * m_nY, m_P3D_Bgn[2] + m_P3D_Spc[2] * m_nZ);

	ARR_P3D.Add(m_P3D_Bgn);
	ARR_P3D.Add(P3D_X1Y0Z0);
	ARR_P3D.Add(P3D_X0Y1Z0);
	ARR_P3D.Add(P3D_X1Y1Z0);
	ARR_P3D.Add(P3D_X0Y0Z1);
	ARR_P3D.Add(P3D_X1Y0Z1);
	ARR_P3D.Add(P3D_X0Y1Z1);
	ARR_P3D.Add(P3D_X1Y1Z1);

	float fMaxDis = P3D_Cntr.GetDistTo(m_P3D_Bgn);

	for (int iP3D = 1; iP3D < ARR_P3D.GetSize(); iP3D++)
	{
		float fDistoVertex = P3D_Cntr.GetDistTo(ARR_P3D[iP3D]);
		if (fDistoVertex > fMaxDis)
		{
			fMaxDis = fDistoVertex;
		}
	}

	return fMaxDis;
}


//-----------------------------------------------------------------------------------

//是否网格一致(体素值除外的相等比较)
template<typename TP_Crd>
BOOL CSPN_Cmn_3DMtx_Grid<TP_Crd>::IsGridSameAs(const CSPN_Cmn_3DMtx_Grid<TP_Crd>& MtxGrid) const
{
	if (!FLT_EQ(m_P3D_Spc[0], MtxGrid.GetP3D_Spc_X())) return FALSE;
	if (!FLT_EQ(m_P3D_Spc[1], MtxGrid.GetP3D_Spc_Y())) return FALSE;
	if (!FLT_EQ(m_P3D_Spc[2], MtxGrid.GetP3D_Spc_Z())) return FALSE;

	if (m_nX != MtxGrid.GetSize_X()) return FALSE;
	if (m_nY != MtxGrid.GetSize_Y()) return FALSE;
	if (m_nZ != MtxGrid.GetSize_Z()) return FALSE;

	SSPN_Cmn_3DPoint<TP_Crd> P3D000Extn;
	MtxGrid.GetP3D_Bgn(P3D000Extn);

	if (SSPN_Cmn_3DPoint__NotEq(P3D000Extn, m_P3D_Bgn))
	{
		return FALSE;
	}

	return TRUE;
};

//三维索引有效化:
template<typename TP_Crd>
inline void CSPN_Cmn_3DMtx_Grid<TP_Crd>::ValidateIdx(SPnt3D_Flt& P3DIdxValid) const
{
	CutIntoRange<float>(P3DIdxValid[0], 0, GetSize_X() - 1);
	CutIntoRange<float>(P3DIdxValid[1], 0, GetSize_Y() - 1);
	CutIntoRange<float>(P3DIdxValid[2], 0, GetSize_Z() - 1);
};

template<typename TP_Crd>
inline void CSPN_Cmn_3DMtx_Grid<TP_Crd>::ValidateIdx(SPnt3D_Sht& P3DIdxValid) const
{
	CutIntoRange<short>(P3DIdxValid[0], 0, GetSize_X() - 1);
	CutIntoRange<short>(P3DIdxValid[1], 0, GetSize_Y() - 1);
	CutIntoRange<short>(P3DIdxValid[2], 0, GetSize_Z() - 1);
};

template<typename TP_Crd>
inline void CSPN_Cmn_3DMtx_Grid<TP_Crd>::ValidateIdx(SPnt3D_Int& P3DIdxValid) const
{
	CutIntoRange<int>(P3DIdxValid[0], 0, GetSize_X() - 1);
	CutIntoRange<int>(P3DIdxValid[1], 0, GetSize_Y() - 1);
	CutIntoRange<int>(P3DIdxValid[2], 0, GetSize_Z() - 1);
};

template<typename TP_Crd>
inline void CSPN_Cmn_3DMtx_Grid<TP_Crd>::ValidateIdx(float& fixValid, float& fiyValid, float& fizValid) const
{
	CutIntoRange<float>(fixValid, 0, GetSize_X() - 1);
	CutIntoRange<float>(fiyValid, 0, GetSize_Y() - 1);
	CutIntoRange<float>(fizValid, 0, GetSize_Z() - 1);
};

template<typename TP_Crd>
inline void CSPN_Cmn_3DMtx_Grid<TP_Crd>::ValidateIdx(int& ixValid, int& iyValid, int& izValid) const
{
	CutIntoRange<int>(ixValid, 0, GetSize_X() - 1);
	CutIntoRange<int>(iyValid, 0, GetSize_Y() - 1);
	CutIntoRange<int>(izValid, 0, GetSize_Z() - 1);
};

template<typename TP_Crd>
inline void CSPN_Cmn_3DMtx_Grid<TP_Crd>::ValidateIdx(short& ixValid, short& iyValid, short& izValid) const
{
	CutIntoRange<short>(ixValid, 0, GetSize_X() - 1);
	CutIntoRange<short>(iyValid, 0, GetSize_Y() - 1);
	CutIntoRange<short>(izValid, 0, GetSize_Z() - 1);
};

template<typename TP_Crd> inline void CSPN_Cmn_3DMtx_Grid<TP_Crd>::ValidateIdx_X(float& fix) const { CutIntoRange<float>(fix, 0, GetSize_X() - 1); };
template<typename TP_Crd> inline void CSPN_Cmn_3DMtx_Grid<TP_Crd>::ValidateIdx_Y(float& fiy) const { CutIntoRange<float>(fiy, 0, GetSize_Y() - 1); };
template<typename TP_Crd> inline void CSPN_Cmn_3DMtx_Grid<TP_Crd>::ValidateIdx_Z(float& fiz) const { CutIntoRange<float>(fiz, 0, GetSize_Z() - 1); };

template<typename TP_Crd> inline void CSPN_Cmn_3DMtx_Grid<TP_Crd>::ValidateIdx_X(int& ix) const { CutIntoRange<int>(ix, 0, GetSize_X() - 1); };
template<typename TP_Crd> inline void CSPN_Cmn_3DMtx_Grid<TP_Crd>::ValidateIdx_Y(int& iy) const { CutIntoRange<int>(iy, 0, GetSize_Y() - 1); };
template<typename TP_Crd> inline void CSPN_Cmn_3DMtx_Grid<TP_Crd>::ValidateIdx_Z(int& iz) const { CutIntoRange<int>(iz, 0, GetSize_Z() - 1); };

template<typename TP_Crd> inline void CSPN_Cmn_3DMtx_Grid<TP_Crd>::ValidateIdx_X(short& ix) const { CutIntoRange<short>(ix, 0, GetSize_X() - 1); };
template<typename TP_Crd> inline void CSPN_Cmn_3DMtx_Grid<TP_Crd>::ValidateIdx_Y(short& iy) const { CutIntoRange<short>(iy, 0, GetSize_Y() - 1); };
template<typename TP_Crd> inline void CSPN_Cmn_3DMtx_Grid<TP_Crd>::ValidateIdx_Z(short& iz) const { CutIntoRange<short>(iz, 0, GetSize_Z() - 1); };

//-----------------------------------------------------------------------------------

#endif //  // !defined(SPN_Cmn_3DMtx_Grid__INCLUDED_
