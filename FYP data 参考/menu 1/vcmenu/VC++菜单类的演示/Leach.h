// Leach.h: interface for the CLeach class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LEACH_H__4FEBEDA1_F09A_11D6_89A6_00055D0EE50E__INCLUDED_)
#define AFX_LEACH_H__4FEBEDA1_F09A_11D6_89A6_00055D0EE50E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define  Frq_Sam   4000    //采样频率
#define  Frq_Heart   200     //R波识别的采样率
#define Num_heart  40                        //R波识别带通滤波阶数
#define PI 3.1415926
#define Num_filter 20                       //低通滤波阶数
#define Num_bp    100                       //压力低通滤波阶数
class CLeach 
{
public:
	double V_BandPass(double x,int k);
	void Init_50Hz_BandPass();
	double Operate_heart_out(double x, int k);
	void Init_R_CheckUp_Parameter();
	void Init_AllFilters_Parameter();
	void Init_SkinNoise_Parameter();
	void Init_BIO_50Hz_Parameter();
	void Init_ECG_50Hz_Parameter();
	void Init_Bp_Lowpass_parameter();
	void Init_Highpass_Parameter();
	void Init_Lowpass_Parameter();
	double heart_out(double x,int k);
	double besse10(double x);  
	double kaiser(int i, int n, double beta);
	double lowpass(int n,double x,int k);
	double highpass(int n,double x,int k);
	double Bp(int n,double x,int k);
	double notch_ECG(double x,int k);
	double notch_BIO(double x,int k);
	double skin_lp(double x,int k);
	double wp[13];                           //高通滤波所需参数              
	double m_coefficient[7][Num_filter+1];            //低通滤波系数
	double bp_coefficient[3][Num_bp+1];          //压力低通滤波系数
	double heart_coefficient[Num_heart+1];           //计算心率的带通滤波系数
	double a_skin[2],b_skin[2];               //去除肌电干扰37Hz低通滤波系数
	double a_ecg[3];                            //ECG 50Hz陷波器分母系数
	double b_ecg[3];                            //ECG 50Hz陷波器分子系数
	double a_bio[3];                            //BIO 50Hz陷波器分母系数
	double b_bio[3];                            //BIO 50Hz陷波器分子系数
	double a_50_bp[3];         //v 50Hz带通器分母系数
	double b_50_bp[3];         //v 50Hz带通器分子系数
	CLeach();
	virtual ~CLeach();


};

#endif // !defined(AFX_LEACH_H__4FEBEDA1_F09A_11D6_89A6_00055D0EE50E__INCLUDED_)