#include "pch.h"
#include "_SPN_Cmn_Math__inLib.h"


void Test_Compile_SPN_Cmn_3DMtx(CSPN_Cmn_3DMtx<int>& rMtx_iB)
{

	CSPN_Cmn_3DMtx<short> MtxSrc;
	CSPN_Cmn_3DMtx<short> MtxDst_1;

	MtxSrc.GetDRR_Ax(MtxDst_1);
	MtxSrc.GetDRR_Co(MtxDst_1);
	MtxSrc.GetDRR_Sa(MtxDst_1);

	MtxSrc.GetMaxIP_Ax(MtxDst_1);



	MtxSrc.GetSliceRandomParallelY(MtxDst_1, CSPN_Cmn_3DPoint<float>(0, 0, 0), CSPN_Cmn_3DPoint<float>(9, 9, 9));
	MtxSrc.GetSliceRandomParallelZ(MtxDst_1, CSPN_Cmn_3DPoint<float>(0, 0, 0), CSPN_Cmn_3DPoint<float>(9, 9, 9));

	MtxSrc.GetSlice_Y_XpZp_3D(MtxDst_1, 0, 8);
	MtxSrc.GetSlice_X_YpZp_3D(MtxDst_1, 0, 8);

	MtxDst_1.SetVox(1, 2, 3, 0);

	CSPN_Cmn_3DMtx<BYTE> MtxDst;
	MtxDst.GetSlice_Z_XpYp_3D(MtxDst, 1, 0);


	MtxDst += 5;
	MtxDst += MtxDst;

	CSPN_Cmn_3DMtx_Base<>* pMtxSrcBs = nullptr;
	MtxDst.CopyMtx(*pMtxSrcBs);

	MtxSrc.MapMtx_byWL_Slc(MtxDst, 0, 0, 100, 1000);
	MtxSrc.MapMtx_byWnd_Slc(MtxDst, 0, 0, 950, 1050);

	MtxSrc.MapMtx_byWndGamma_Slc(MtxDst, 0, 0, 950, 1050);
	MtxDst.MapMtx_byWndGamma_Slc(MtxDst, 0, 0, 950, 1050);

	short vMin, vMax;
	MtxSrc.GetVoxMinMax(vMin, vMax);

	CSPN_Cmn_3DMtx <int> MtxImg;
	QImage ImgGrey;
	MtxImg.GetQImage_Grey888(ImgGrey, 0);

	CSPN_Cmn_3DMtx<int> Mtx_iA;
	{
		Mtx_iA.Set_nXYZ(0, 0, 5);
		Mtx_iA.SetP3D_Bgn(0, 0, 0);
		Mtx_iA.SetP3D_Spc(.5f, .5f, 0.f);

		//D  
		for (int iVox = 0; iVox < Mtx_iA.GetSize_Mtx(); iVox++)
		{
			Mtx_iA.SetVox(iVox, rand()%3);
		}

		//3D
		int iVox = 0;
		for (int k = 0; k<Mtx_iA.GetSize_Z(); k++)
		{
			for (int j = 0; j < Mtx_iA.GetSize_Y(); j++)
			{
				for (int i = 0; i < Mtx_iA.GetSize_X(); i++, iVox++)
				{
					Mtx_iA.SetVox(i, j, k, rand() % 3);
				}
			}
		}

		Mtx_iA.Set_nXYZ(0, 0, 5);
		Mtx_iA.Set_nXYZ(0, 0, 5);
	}

	rMtx_iB;
	{
		//rMtx_iB.CopyMtx(Mtx_iA);

		assert(Mtx_iA.GetSize_Mtx() > 0);
		assert(rMtx_iB.GetSize_Mtx() == 0);

		rMtx_iB.Swap(Mtx_iA);

		assert(rMtx_iB.GetSize_Mtx() > 0);
		assert(Mtx_iA.GetSize_Mtx() == 0);
	}
}
//
//CSPN_Cmn_3DMtx<int>&& Test_Swap_3DMtx()
//{
//	CSPN_Cmn_3DMtx<int> Mtx_iA;
//	{
//		Mtx_iA.Set_nXYZ(, , 5);
//		Mtx_iA.SetP3D_Bgn(, , );
//		Mtx_iA.SetP3D_Spc(.5f, .5f, .f);
//
//		//D
//		for (int iVox = ; iVox < Mtx_iA.GetSize_Mtx(); iVox++)
//		{
//			Mtx_iA.SetVox(iVox, rand()%);
//		}
//
//		//3D
//		int iVox = ;
//		for (int k = ; k<Mtx_iA.GetSize_Z(); k++)
//		{
//			for (int j = ; j < Mtx_iA.GetSize_Y(); j++)
//			{
//				for (int i = ; i < Mtx_iA.GetSize_X(); i++, iVox++)
//				{
//					/iVox = Mtx_iA.GetVoxID(CSPN_Cmn_3DPoint<int>(i,j,k));/
//
//					Mtx_iA.SetVox(i, j, k, rand() % );
//				}
//			}
//		}
//
//		Mtx_iA.Set_nXYZ(, , 5);
//		Mtx_iA.Set_nXYZ(, , 5);
//	}
//
//	return Mtx_iA;
//
//	///CSPN_Cmn_3DMtx<int> /rMtx_iB;
//	//{
//	//	//rMtx_iB.CopyMtx(Mtx_iA);
//
//	//	assert(Mtx_iA.GetSize_Mtx() > );
//	//	assert(rMtx_iB.GetSize_Mtx() == );
//
//	//	rMtx_iB.Swap(Mtx_iA);
//
//	//	assert(rMtx_iB.GetSize_Mtx() > );
//	//	assert(Mtx_iA.GetSize_Mtx() == );
//	//}
//}
//
//void FunMain()
//{
//	CSPN_Cmn_3DMtx<int> MtxR;
//	MtxR.Swap(Test_Swap_3DMtx());
//
//	//std::map<int, int>::swap()
//}