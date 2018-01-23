// Leach.h: interface for the CLeach class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LEACH_H__4FEBEDA1_F09A_11D6_89A6_00055D0EE50E__INCLUDED_)
#define AFX_LEACH_H__4FEBEDA1_F09A_11D6_89A6_00055D0EE50E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define  Frq_Sam   4000    //����Ƶ��
#define  Frq_Heart   200     //R��ʶ��Ĳ�����
#define Num_heart  40                        //R��ʶ���ͨ�˲�����
#define PI 3.1415926
#define Num_filter 20                       //��ͨ�˲�����
#define Num_bp    100                       //ѹ����ͨ�˲�����
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
	double wp[13];                           //��ͨ�˲��������              
	double m_coefficient[7][Num_filter+1];            //��ͨ�˲�ϵ��
	double bp_coefficient[3][Num_bp+1];          //ѹ����ͨ�˲�ϵ��
	double heart_coefficient[Num_heart+1];           //�������ʵĴ�ͨ�˲�ϵ��
	double a_skin[2],b_skin[2];               //ȥ���������37Hz��ͨ�˲�ϵ��
	double a_ecg[3];                            //ECG 50Hz�ݲ�����ĸϵ��
	double b_ecg[3];                            //ECG 50Hz�ݲ�������ϵ��
	double a_bio[3];                            //BIO 50Hz�ݲ�����ĸϵ��
	double b_bio[3];                            //BIO 50Hz�ݲ�������ϵ��
	double a_50_bp[3];         //v 50Hz��ͨ����ĸϵ��
	double b_50_bp[3];         //v 50Hz��ͨ������ϵ��
	CLeach();
	virtual ~CLeach();


};

#endif // !defined(AFX_LEACH_H__4FEBEDA1_F09A_11D6_89A6_00055D0EE50E__INCLUDED_)