// Leach.cpp: implementation of the CLeach class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cardio.h"
#include "Leach.h"
#include "math.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLeach::CLeach()
{
	Init_AllFilters_Parameter();   //��ʼ�������˲����Ĳ���
}
CLeach::~CLeach()
{

}

/*-*-*-*-*-*-*-*-*��һ�������������������*-*-*-*-*-*-*-*-*-*/
/*-*-*--*-*-*-*-*-x��Ϊkaiser����beta����*-*-*-*-*-*-*-*-*-*-*/
double CLeach::besse10(double x)
{
	int i;
	double d,y,d2,sum;
	y=x/2.0;
	d=1.0;
	sum=1.0;
	for(i=1;i<25;i++)
	{
		d=d*y/i;
		d2=d*d;
		sum=sum+d2;
		if(d2<sum*(1.0e-8)) break;
	}
	return(sum);
}

/*-*-*-*-*-*-*-*-*-*����kaiser��ֵ*-*-*-*-*-*-*-*-*-*-*/
/*---------------iΪkaiser���ĵڼ���ֵ----------------*/
/*-----------------nΪkaiser���Ľ���------------------*/
/*-*-*-*-*-*-*-*-*-*betaΪkaiser���Ĳ���*-*-*-*-*-*-*-*/
double CLeach::kaiser(int i, int n, double beta)
{
	double a,w,a2,b1,b2,beta1;
	b1=besse10(beta);
	a=2.0*i/(double)(n-1)-1.0;
	a2=a*a;
	beta1=beta*sqrt(1.0-a2);
	b2=besse10(beta1);
	w=b2/b1;
	return(w);
}

/*-*-*-*-*-*-*-*-*-*-*-*��ͨ���*-*-*-*-*-*-*-*-*--*-*-*/
//   ����˵��
//   n�����ͨ��ֹƵ�ʵ����
//   x----- �ɼ�������
//   k----- �ڼ���ͨ��
double CLeach::lowpass(int n,double x,int k)
{
//	return 0;

	double sum=0;
	static double yl[64][Num_filter+1];
	double tmp[Num_filter];
	CopyMemory(tmp,&yl[k][1],sizeof(tmp));
	CopyMemory(yl[k],tmp,sizeof(tmp));

    yl[k][Num_filter]=x;
	for(int j=0;j<=Num_filter;j++)
	{
		sum=sum+m_coefficient[n][j]*yl[k][Num_filter-j];
	}
	return sum;
}

/*-*-*-*-*-*-*-*-*-*��ͨ�˲�*-*-*-*-*-*-*-*-*-*-*/
//   ����˵��
//   n----- ��ͨ��ֹƵ�ʵ����
//   x----- �ɼ�������
//   k----- �ڼ���ͨ��
double CLeach::highpass(int n,double x,int k)
{
//	return 0;

	double sum1,sum;
	sum1=sum=1;
	static double in_h[64][2],out_h[64];
    in_h[k][0]=in_h[k][1];
	in_h[k][1]=x;
	sum1=in_h[k][1]-in_h[k][0]+(1-wp[n])*out_h[k];
	sum=sum1/(1+wp[n]);
	out_h[k]=sum;

	double tmp;
	tmp=out_h[k];
	if(tmp<0)
		tmp*=-1.0;
	if(tmp<1e-6)
		out_h[k]=0;

	return sum;
}


/*-*-*-*-*-*-*-*-*ECG ����Ӧ50Hz�˲�*-*-*-*-*-*-*-*-*/
double CLeach::notch_ECG(double x,int k)
{
	
	static double in_n[64][3],out_n[64][2];
	double sum,sum1,sum2;
	for(int i=0;i<2;i++)
	{
		in_n[k][i]=in_n[k][i+1];
	}
	in_n[k][2]=x;
	sum1=b_ecg[0]*in_n[k][2]+b_ecg[1]*in_n[k][1]+b_ecg[2]*in_n[k][0];
	sum2=a_ecg[1]*out_n[k][1]+a_ecg[2]*out_n[k][0];
	sum=(sum1-sum2)/a_ecg[0];
	out_n[k][0]=out_n[k][1];
	out_n[k][1]=sum;   

	double tmp;
	tmp=out_n[k][1];
	if(tmp<0)
		tmp*=-1.0;
	if(tmp<1e-6)
		out_n[k][1]=0;

	return sum; 
}

/*-*-*-*-*-*-*-*-*BIO ����Ӧ50Hz�˲�*-*-*-*-*-*-*-*-*/
double CLeach::notch_BIO(double x,int k)
{
	static double in_n[64][3],out_n[64][2];
	double sum,sum1,sum2;
	for(int i=0;i<2;i++)
	{
		in_n[k][i]=in_n[k][i+1];
	}
	in_n[k][2]=x;
	sum1=b_bio[0]*in_n[k][2]+b_bio[1]*in_n[k][1]+b_bio[2]*in_n[k][0];
	sum2=a_bio[1]*out_n[k][1]+a_bio[2]*out_n[k][0];
	sum=(sum1-sum2)/a_bio[0];
	out_n[k][0]=out_n[k][1];
	out_n[k][1]=sum; 
	double tmp;
	tmp=abs(out_n[k][1]*1e+10);
	if(tmp<1e-10)
		out_n[k][1]=0;
	return sum; 
}

/********************ѹ�����(FIR)*******************/
//   ����˵��
//   n----- ѹ����ͨ��ֹƵ��ֵ�����
//   x----- �ɼ�������
//   k----- �ڼ���ͨ��
double CLeach::Bp(int n,double x,int k)
{
//	return 0;

	double sum=0;
	static double yb[64][Num_bp+1];

	double tmp[Num_bp];
	CopyMemory(tmp,&yb[k][1],sizeof(tmp));
	CopyMemory(yb[k],tmp,sizeof(tmp));
    yb[k][Num_bp]=x;
	for(int j=0;j<=Num_bp;j++)
	{
		sum=sum+bp_coefficient[n][j]*yb[k][Num_bp-j];
	}
	return sum;
}

/*-*-*-*-*-*-*-*-*-*-*-*���ʴ�ͨ���*-*-*-*-*-*-*-*-*--*-*-*/
//   ����˵��
//   x----- �ɼ�������
//   k----- �ڼ���ͨ��
double CLeach::heart_out(double x,int k)
{
	double sum=0;
	static double y[2][Num_heart+1];
	double tmp[Num_heart];
	CopyMemory(tmp,&y[k][1],sizeof(tmp));
	CopyMemory(y[k],tmp,sizeof(tmp));
    y[k][Num_heart]=x;
	for(int j=0;j<=Num_heart;j++)
	{
		sum=sum+heart_coefficient[j]*y[k][Num_heart-j];
	}
	return sum;
	
}
/*-*-*-*-*-*-*-*-*-*-*-*ȥ���������37Hz��ͨ�˲����*-*-*-*-*-*-*-*-*--*-*-*/
double CLeach::skin_lp(double x,int k)
{
	double sum1,sum;
	static double in[64][2],out[64];
    in[k][0]=in[k][1];
	in[k][1]=x;
	sum1=b_skin[0]*in[k][1]+b_skin[1]*in[k][0]-a_skin[1]*out[k];
	sum=sum1/a_skin[0];
	out[k]=sum;
	return sum;
}


void CLeach::Init_Lowpass_Parameter()
{
	int  Frq_lp[7]={100,150,200,400,600,800,1200};        //��ͨ��ֹƵ��
	/*-*-*-*-*-*-*��ͨ�˲�*-*-*-*-*-*-*/
	double  beta[7]={2.5,3.4,4.3,6,6,6,6};                                      //��ͨ����������
	for(int j=0;j<7;j++)
	{
		double wc=2*PI*(Frq_lp[j]+95)/Frq_Sam;                 //wcΪ��Խ�Ƶ��
		double hd[Num_filter+1]={0};                                  //���治�Ӵ��������˲���ϵ��
		double wd[Num_filter+1]={0};                                  //����kaiser������ϵ��
		for(int i=0;i<=Num_filter;i++)
		{
			if(i==Num_filter/2) 
			{
				hd[i]=wc/PI;
			}
			else
			{	
				hd[i]=sin((i-Num_filter/2)*wc)/(PI*(i-Num_filter/2));
			} 
			wd[i]=kaiser(i,Num_filter+1,beta[j]);
			m_coefficient[j][i]=hd[i]*wd[i];          //��ͨ�˲���ϵ��
		}
	}

}

void CLeach::Init_Highpass_Parameter()
{
	double Frq_hp[13]={0.05,0.5,1,10,20,30,40,50,60,70,80,90,100};     //��ͨ��ֹƵ��
/*-*-*-*-*-*-*-*��ͨ�˲�*-*-*-*-*-*-*-*-*/
	for(int k=0;k<13;k++)
	{
		wp[k]=tan(PI*Frq_hp[k]/Frq_Sam);        //��ͨ�˲�����ϵ��
	}
}

void CLeach::Init_Bp_Lowpass_parameter()
{
	double Frq_bp[3]={20,30,40};                        //ѹ����ͨ��ֹƵ��
/*-*-*-*-*-*-*BP��ͨ(FIR)*-*-*-*-*-*-*-*-*/
//	double beta_bp=5;                                         //ѹ����ͨ����������
	double beta_bp[3]={2.05,3,4};                                         //ѹ����ͨ����������
	for (int j=0;j<3;j++)
	{
 		double wc1=2*PI*(Frq_bp[j]+15)/Frq_Sam;                  //wc1Ϊ��Խ�Ƶ��
		double hd1[Num_bp+1]={0};                                  //���治�Ӵ��������˲���ϵ��
		double wd1[Num_bp+1]={0};                                  //����kaiser������ϵ��
		for(int i=0;i<=Num_bp;i++)
		{
			if(i==Num_bp/2) 
			{
				hd1[i]=wc1/PI;
			}
			else
			{	
				hd1[i]=sin((i-Num_bp/2)*wc1)/(PI*(i-Num_bp/2));
			}
			wd1[i]=kaiser(i,Num_bp+1,beta_bp[j]);
			bp_coefficient[j][i]=hd1[i]*wd1[i];          //��ͨ�˲���ϵ��
		}
	}
}

void CLeach::Init_ECG_50Hz_Parameter()
{
	/*-*-*-*-*-*-*ECG 50Hz�˲��˲���ϵ��*-*-*-*-*-*-*-*/
	double BW_ECG=2;                                       //�ݲ�������λΪHz
	double U_ECG=BW_ECG*PI/Frq_Sam;
	double w_ECG=2*PI*50/Frq_Sam; 
	double rez_ECG=cos(w_ECG); 
	b_ecg[0]=1;                                     //b_ecg[] �˲�������ϵ��
	b_ecg[1]=-2*rez_ECG;
	b_ecg[2]=1;
	a_ecg[0]=1;                                      //a_ecg[]�˲�����ĸϵ��
	a_ecg[1]=-2*rez_ECG*(1-U_ECG);
	a_ecg[2]=1-U_ECG*2;

}

void CLeach::Init_BIO_50Hz_Parameter()
{
	/*-*-*-*-*-*-*BIO 50Hz�˲��˲���ϵ��*-*-*-*-*-*-*-*/
	double BW_BIO=1;                                       //�ݲ�������λΪHz
	double U_BIO=BW_BIO*PI/Frq_Sam;
	double w_BIO=2*PI*50/Frq_Sam; 
	double rez_BIO=cos(w_BIO); 
	b_bio[0]=1;                                     //b_bio[] �˲�������ϵ��
	b_bio[1]=-2*rez_BIO;
	b_bio[2]=1;
	a_bio[0]=1;                                      //a_bio[]�˲�����ĸϵ��
	a_bio[1]=-2*rez_BIO*(1-U_BIO);
	a_bio[2]=1-U_BIO*2;
}

void CLeach::Init_SkinNoise_Parameter()
{
/*-*-*-*-*-*-*-*ȥ���������37Hz��ͨ�˲�ϵ��*-*-*-*-*-*-*-*/
	double Frq_skin=36;
	double w_skin=tan(PI*Frq_skin/Frq_Sam);
	b_skin[0]=b_skin[1]=w_skin;
	a_skin[0]=1+w_skin;
	a_skin[1]=w_skin-1;
}

void CLeach::Init_AllFilters_Parameter()  //��ʼ�������˲����Ĳ���
{
	Init_Lowpass_Parameter();  //��ʼ����ͨ�˲����Ĳ���
	Init_Highpass_Parameter(); //��ʼ����ͨ�˲����Ĳ���
	Init_Bp_Lowpass_parameter();//��ʼ��ѹ����ͨ�˲����Ĳ���
	Init_ECG_50Hz_Parameter(); //��ʼ��ECG 50Hz�˲����Ĳ���
	Init_BIO_50Hz_Parameter(); //��ʼ��BIO 50Hz�˲����Ĳ���
	Init_SkinNoise_Parameter();//��ʼ��ȥ����������˲����Ĳ���
	Init_R_CheckUp_Parameter(); //��ʼ��R������˲����Ĳ���
	Init_50Hz_BandPass();
}

void CLeach::Init_R_CheckUp_Parameter()
{
/*-*-*-*-*-*-*���������˲���ϵ��*-*-*-*-*-*-*-*/
	double beta_heart=6;                                         //���ʴ�ͨ����������
 	double wl=2*PI*5/Frq_Heart;                              //whΪ��Խ�Ƶ��
 	double wh=2*PI*33/Frq_Heart;                              //wlΪ��Խ�Ƶ��
	double hd_heart[Num_heart+1]={0};                                  //���治�Ӵ��������˲���ϵ��
	double wd_heart[Num_heart+1]={0};                                  //����kaiser������ϵ��
	for(int i=0;i<=Num_heart;i++)
	{
		if(i==Num_heart/2) 
		{
			hd_heart[i]=(wh-wl)/PI;
		}
		else
		{	
			hd_heart[i]=sin((i-Num_heart/2)*wh)/(PI*(i-Num_heart/2))
				        -sin((i-Num_heart/2)*wl)/(PI*(i-Num_heart/2));
		}
		wd_heart[i]=kaiser(i,Num_heart+1,beta_heart);
		heart_coefficient[i]=hd_heart[i]*wd_heart[i];          //���ʴ�ͨ�˲���ϵ��
	}
}

double CLeach::Operate_heart_out(double x, int k)
{
	double sum=0;
	static double yy[2][Num_heart+1];
	double tmp[Num_heart];
	CopyMemory(tmp,&yy[k][1],sizeof(tmp));
	CopyMemory(yy[k],tmp,sizeof(tmp));
    yy[k][Num_heart]=x;
	for(int j=0;j<=Num_heart;j++)
	{
		sum=sum+heart_coefficient[j]*yy[k][Num_heart-j];
	}
	return sum;
}

void CLeach::Init_50Hz_BandPass()
{
/*-*-*-*-*-*-*50Hz��ͨ�˲���ϵ��*-*-*-*-*-*-*-*/
	double BW1=10;                                       //��ͨ������λΪHz
	double U1=BW1*PI/Frq_Sam;
	double w1=2*PI*50/Frq_Sam; 
	double rez1=cos(w1); 
	a_50_bp[0]=1;                                      //a1[]�˲�����ĸϵ��
	a_50_bp[1]=-2*rez1*(1-U1);
	a_50_bp[2]=1-U1*2;
	b_50_bp[0]=0;                                     //b1[] �˲�������ϵ��
	b_50_bp[1]=2*rez1*U1;
	b_50_bp[2]=-2*U1;
}

double CLeach::V_BandPass(double x, int k)
{
	static double in_n[64][3],out_n[64][2];
	double sum,sum1,sum2;
	for(int i=0;i<2;i++)
	{
		in_n[k][i]=in_n[k][i+1];
	}
	in_n[k][2]=x;
	sum1=b_50_bp[0]*in_n[k][2]+b_50_bp[1]*in_n[k][1]+b_50_bp[2]*in_n[k][0];
	sum2=a_50_bp[1]*out_n[k][1]+a_50_bp[2]*out_n[k][0];
	sum=(sum1-sum2)/a_50_bp[0];
	out_n[k][0]=out_n[k][1];
	out_n[k][1]=sum;        
	return sum; 
}
