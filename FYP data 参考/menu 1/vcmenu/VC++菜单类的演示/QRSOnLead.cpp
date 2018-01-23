// QRSOnLead.cpp: implementation of the CQRSOnLead class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "QRSOnLead.h"
#include <math.h>
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CQRSOnLead::CQRSOnLead()
{

}

CQRSOnLead::~CQRSOnLead()
{

}
int CQRSOnLead::Border(int x, int length)
{
		if(x<0)x=-x;
	if(x>length)x=length*2-x-2;
	return(x);
}

void CQRSOnLead::Wavelet_Trans(double *wavelet_cof,double *clean_data)
{
		int i,j,k;	
 	double h[4]={0.125,0.375,0.375,0.125};//С���任�õ���ϵ�� 
	double g[2]={-2.0,2.0};				//С���任�õ���ϵ��
	double c1[5]={1.5,1.12,1.03,1.01,1.00};//С���任�õ���ϵ��
	double c2;							//С���任�õ���ϵ���м����	
	int m;                              //���Ʋ���	
	double low[SCALE][SAMPLE_RATE*LENGTH];					//�ź�С���任��0-5���Ƶϵ��
	double temp1,temp2;					//�����Ƶ��Ƶϵ��ʱ�õ�����ʱ����	
	double high[SCALE][SAMPLE_RATE*LENGTH];					//�ź�С���任���0-6���Ƶϵ��

	for(i=0;i<SAMPLE_RATE*LENGTH;i++)
		high[0][i]=low[0][i]=clean_data[i];  //�Ե�һ�㸳ֵ

	m=1;
	for(k=1;k<SCALE;k++)                              //k Ϊ����
	{
		c2=1/c1[k-1];
 		     for(i=0;i<SAMPLE_RATE*LENGTH;i++)                         //iΪ�ڵ���
			 {
			      temp1=0;
			      temp2=0;         
     		      for(j=-1;j<=2;j++)                        //jΪ�˲���ϵ��  
			           temp1=temp1+h[j+1]*(*(low[k-1]+Border(i-m*j,SAMPLE_RATE*LENGTH)));
			      low[k][i]=temp1;
			}	
 		     for(i=0;i<SAMPLE_RATE*LENGTH;i++)                         //iΪ�ڵ���
			 {
			      temp1=0;
			      temp2=0;         
     		      for(j=-1;j<=2;j++)                        //jΪ�˲���ϵ��  
			           temp1=temp1+h[j+1]*(*(low[k-1]+Border(i-m*j,SAMPLE_RATE*LENGTH)));
			      for(j=0;j<=1;j++)
			           temp2=temp2+g[j]*(*(low[k-1]+Border(i-m*j,SAMPLE_RATE*LENGTH)));
			      high[k][i]=(c2*temp2);
			      low[k][i]=temp1;
			}
		
		m=2*m;
	}
    //���ӳ�ʱ����в���: 2��N����-1
	for(j=1;j<SCALE;j++)
	{
		for(i=0;i<SAMPLE_RATE*LENGTH-pow(2,j-1)+1;i++)
			high[j][i]=high[j][i+(int)(pow(2,j-1)-1)];
	}
	for(i=0;i<SAMPLE_RATE*LENGTH;i++)
		wavelet_cof[i]=high[2][i];
}

	void CQRSOnLead::Move_Window(double* Square_Data,double* Move_Data)
	{
		int i,j;
	for(i=WINDOW_WIDTH-1;i<SAMPLE_RATE*LENGTH;i++)
	{
		Move_Data[i]=0;
		for(j=0;j<WINDOW_WIDTH;j++)
			Move_Data[i]+=Square_Data[i-j];
		Move_Data[i]/=WINDOW_WIDTH;
	}
	for(i=0;i<WINDOW_WIDTH-1;i++)
		Move_Data[i]=0;
	}
	double CQRSOnLead::low_pass(double x)
	{
			static double in[3],out[2];
	double sum,sum1,sum2;
	double a[3]={1.0000,-1.2796,0.4776};
	double b[3]={0.0495,0.0990,0.0495};
	in[0]=in[1];
	in[1]=in[2];
	in[2]=x;
	sum1=b[0]*in[2]+b[1]*in[1]+b[2]*in[0];
	sum2=a[1]*out[1]+a[2]*out[0];
	sum=(sum1-sum2)/a[0];
	out[0]=out[1];
	out[1]=sum;
	return sum;
}

double CQRSOnLead::high_pass(double x)
{
	double sum1,sum;
	static double in[2],out;
   	 in[0]=in[1];
	in[1]=x;
	sum1=in[1]-in[0]+0.9895*out;
	sum=sum1/1.0105;
	out=sum;
	return sum;
}

int CQRSOnLead::Heart_Rate(int* R_Peak_Pos)
{
	int i,j;
	int temp_RR_Interval[10];
	int heart_rate=0;

	if(R_Peak_Pos[0]<900)
	{
		for(j=0,i=0;i<20;i++)
		{	
			if((temp_RR_Interval[j]=R_Peak_Pos[i]-R_Peak_Pos[i+1])>0 && R_Peak_Pos[i]!=900)
			{
				heart_rate+=temp_RR_Interval[j];
				Single_RR_InterVal[j]=temp_RR_Interval[j];
			     j++;
			}
			if(j==6)
				break;
		}
	}
	else
	{
		for(j=0,i=0;i<20;i++)
		{	
			if((temp_RR_Interval[j]=R_Peak_Pos[i]-R_Peak_Pos[i+1])>=0)
			{heart_rate+=temp_RR_Interval[j];j++;}
			if(j==6)
				break;
		}
	}
// download by http:www.codefans.net
	if(heart_rate==0)
		return(0);
	else
	{
			return((SAMPLE_RATE*60)/(heart_rate/j));
	}
}

//88888888888888888
double CQRSOnLead::Heart_Rate8(int* R_Peak_Pos,int pos)
{
	int i,j;
	int temp_RR_Interval[10];
	int heart_rate=0;
	
	if(R_Peak_Pos[0]<900)
	{
		for(j=0,i=pos;i<20;i++)
		{	
			if((temp_RR_Interval[j]=R_Peak_Pos[i]-R_Peak_Pos[i+1])>0 && R_Peak_Pos[i]!=900)
			{
				heart_rate+=temp_RR_Interval[j];
				Single_RR_InterVal[j]=temp_RR_Interval[j];
			     j++;
			}
			if(j==8)
				break;
		}
	}
	else
	{
		for(j=0,i=pos;i<20;i++)
		{	
			if((temp_RR_Interval[j]=R_Peak_Pos[i]-R_Peak_Pos[i+1])>=0)
			{heart_rate+=temp_RR_Interval[j];j++;}
			if(j==8)
				break;
		}
	}

	if(heart_rate==0)
		return(0);
	else
		return(((double)heart_rate/SAMPLE_RATE)/8);
}

int CQRSOnLead::Accurate_R_Move(double* Move_Data, int R_Peak)
{
	int i,a;
	for(a=0,i=0;i<SAMPLE_RATE*0.1;i++)
		if(Move_Data[R_Peak+a]<Move_Data[R_Peak+i])
			a=i;
	return(R_Peak+a);
}

int CQRSOnLead::R_Peak_detection(int* R_Peak_Pos2,double* MOV_DATA,int segment_flag,double* Clean_Data)
{
	int i,k,m ;
	double MOV_DATA_COPY[SAMPLE_RATE*LENGTH];//����3�볤��һ��MOV_DATA_COPY����
	int R_Peak_Pos[Max_Beat_Num];
	int Detected_Flag[Max_Beat_Num];//�˱�־����ĳһRR�����Ƿ񳬹�1.5����ƽ��RR���ڣ����Ƿ��ѱ�
	                      //��⣨���ڲ�Ѱ��QRS��1:�Ѿ�Ѱ�ң�0��û��Ѱ�� 
	int beat_num,beat_num2;
	double Ave_Ampl2;
    double Threshhold1=0.1;

	for(i=0;i<SAMPLE_RATE*LENGTH;i++)
		MOV_DATA_COPY[i]=MOV_DATA[i];

	for(i=0;i<Max_Beat_Num;i++)
		Detected_Flag[i]=0;
	//���ݳ�ʼ��
	if(segment_flag==0)
	{
	 for(i=0;i<Max_Beat_Num;i++)
	 {R_Peak_Pos[i]=0;}
	 for(i=0;i<Max_Beat_Num;i++)
	 {
		 R_Peak_Ampl[i]=Threshhold1;
		 RR_Interval[i]=(int)(SAMPLE_RATE*0.9);
	 }
	 Ave_Ampl=R_Peak_Ampl[0];
	 Ave_RR_Interval=RR_Interval[0];
	}	 
	//������ֵ0.08ȥ��ѡ���(��һ�Σ�
	beat_num=0;
	R_Peak_Pos[0]=0;
//	Ave_Ampl2=0.2*Ave_Ampl;
	while(beat_num==0)
	{
		for(i=SAMPLE_RATE*0.3;i<SAMPLE_RATE*(LENGTH-0.1);i++)
		{
			if(MOV_DATA_COPY[i]>=0.5*Ave_Ampl)
			{
				if(MOV_DATA_COPY[i]>MOV_DATA_COPY[i-4])//ȷ���õ��������������
				{
				R_Peak_Position_Num[beat_num]=R_Peak_Pos[beat_num+1]=i=Accurate_R_Peak_Clean(Clean_Data,i);
			
				R_Peak_Pos_Data=Clean_Data[R_Peak_Pos[beat_num+1]]*2000;
 					i=i+0.3*SAMPLE_RATE;//����300ms������ͬһ��QRS�������ΪR�����
					beat_num++;	
				}
			}
		}
		if(beat_num==0)
		{
			Ave_Ampl*=0.9;
			if(Ave_Ampl<Threshhold2)//�����ƽ������Ave_AmplС��Threshhold2ʱ����˵��û��
				                   //QRS�����Ƴ�ѭ����������һ���Ƴ�����
				break;
		}
	}
	//�жϵ�һ�δ�ѡ�Ƿ��з��
	if(beat_num>19)//��ֹ�������
	{
		for(i=0;i<Max_Beat_Num;i++)
			R_Peak_Pos2[i]=R_Peak_Pos[19-i];
		return(-1);
	}
	//û�е���� 
	if(beat_num==0)
	{
		for(i=0;i<7;i++)
			R_Peak_Pos2[i]=900;
		return(-2);
	}
	//�е����
	//����RR_Interval��Ave_RR_Interval
	for(i=Max_Beat_Num-(beat_num+1);i>=0;i--)
		RR_Interval[i+beat_num]=RR_Interval[i];
	for(i=0;i<beat_num;i++)
		RR_Interval[i]=R_Peak_Pos[i+1]-R_Peak_Pos[i];
	Ave_RR_Interval=0;
	for(i=0;i<Max_Beat_Num/2;i++)
		Ave_RR_Interval+=RR_Interval[i];
	Ave_RR_Interval/=Max_Beat_Num/2;
	//����R_Peak_Ampl��Ave_Ampl
	for(i=Max_Beat_Num-beat_num-1;i>=0;i--)
		R_Peak_Ampl[i+beat_num]=R_Peak_Ampl[i];
	for(i=0;i<beat_num;i++)
		R_Peak_Ampl[i]=MOV_DATA_COPY[Accurate_R_Move(MOV_DATA_COPY,R_Peak_Pos[i+1])];//��Ϊ��һ��QRS��λ��Ϊ0
	                                                      
	Ave_Ampl=0;
	for(i=0;i<Max_Beat_Num/2;i++)
		Ave_Ampl+=R_Peak_Ampl[i];
	Ave_Ampl/=Max_Beat_Num/2;


	//suppose Ave_RR_Interval=50
	Ave_Ampl2=Ave_Ampl;
	for(i=0;i<beat_num;i++)
	{
		beat_num2=beat_num;
		if(R_Peak_Pos[i+1]-R_Peak_Pos[i]>1.5*Ave_RR_Interval && Detected_Flag[i]==0 
			&& beat_num<Max_Beat_Num-1)//����©��, �������һ��������Ϊ�˷�ֹ���ʹ���
		{
			for(k=0;k<R_Peak_Pos[i+1]-R_Peak_Pos[i]-0.5*SAMPLE_RATE;k++)
			{
				if(MOV_DATA_COPY[R_Peak_Pos[i]+(int)(SAMPLE_RATE*0.3)+k]>=Ave_Ampl &&
					MOV_DATA_COPY[R_Peak_Pos[i]+(int)(SAMPLE_RATE*0.3)+k]>MOV_DATA_COPY[R_Peak_Pos[i]+(int)(SAMPLE_RATE*0.3)+k-80] &&//�޳�P��
					MOV_DATA_COPY[R_Peak_Pos[i]+(int)(SAMPLE_RATE*0.3)+k]>MOV_DATA_COPY[R_Peak_Pos[i]+(int)(SAMPLE_RATE*0.3)+k-3])//ȷ���������̼�⵽һ��QRS��
				{
					//����һ��R���
					for(m=Max_Beat_Num-2;m>=i+1;m--)
						R_Peak_Pos[m+1]=R_Peak_Pos[m];
					R_Peak_Pos[i+1]=Accurate_R_Peak_Clean(Clean_Data,R_Peak_Pos[i]+0.3*SAMPLE_RATE+k);

					//����һ��RR_Interval,and refresh the Ave_RR_Interval	
					for(m=Max_Beat_Num-2;m>=i+1;m--)
						RR_Interval[m+1]=RR_Interval[m];//leave one rooms
					RR_Interval[i]=R_Peak_Pos[i+1]-R_Peak_Pos[i];
					RR_Interval[i+1]=R_Peak_Pos[i+2]-R_Peak_Pos[i+1];
					Ave_RR_Interval=0;
					for(m=0;m<Max_Beat_Num/2;m++)
						Ave_RR_Interval+=RR_Interval[m];
					Ave_RR_Interval/=Max_Beat_Num/2;

					//����һ��Detected_Flag	
					for(m=Max_Beat_Num-2;m>i+1;m--)
						Detected_Flag[m+1]=Detected_Flag[m];//leave two rooms
					Detected_Flag[i]=0;
					Detected_Flag[i+1]=0;
					//����һ��R_Peak_Ampl���ı�Ave_R_Peak_Ampl 
					for(m=Max_Beat_Num-2;m>=0;m--)
						R_Peak_Ampl[m+1]=R_Peak_Ampl[m];
					R_Peak_Ampl[0]=MOV_DATA_COPY[Accurate_R_Move(MOV_DATA_COPY,R_Peak_Pos[i+1])];
					for(m=0;m<Max_Beat_Num/2;m++)
						Ave_Ampl+=R_Peak_Ampl[m];
					Ave_Ampl/=Max_Beat_Num/2;
					Ave_Ampl2=Ave_Ampl;

					//�ı�i��j��values
					beat_num+=1;
					break;
				}
			}	
			if(beat_num!=beat_num2+1)//û���ҵ�QRS
			{
				Ave_Ampl*=0.85;//�������������Ըı�ִ���ٶ�
				if(Ave_Ampl<2*Threshhold2)
				{Detected_Flag[i]=1;Ave_Ampl=Ave_Ampl2;continue;}//�ָ�Ave_Ampl��������ѭ��
				else//�Ծ�ͣ����ͬһRR�����ϣ� 
				{i-=1;}

			}
			else
				i=-1;//��ͷ��ʼ
		}
	}
	for(i=Max_Beat_Num-(beat_num+2);i>=0;i--)//�ƶ����飬�����ռ�	
		R_Peak_Pos2[i+beat_num+1]=R_Peak_Pos2[i];
	for(i=0;i<beat_num+1;i++)
	{
		R_Peak_Pos2[beat_num-i]=R_Peak_Pos[i];
	//	printf("the R peaks are:     R_Peak_Pos[%d]=%d\n",i,R_Peak_Pos[i]);
	}
	return(beat_num);
}

int CQRSOnLead::Accurate_R_Peak_Clean(double* Clean_Data, int R_Peak)
{
	int i,j;
	int a;
	int Max_Peak,Min_Peak,Max_Slope_Peak;
	double tempdata[int(0.15*SAMPLE_RATE)];
	int temppeak[10];
	double peakslope[10],Max_Slope,Slope_Max,Slope_Min;

	Max_Peak=Min_Peak=R_Peak;
	for(i=0;i<10;i++)
		temppeak[i]=R_Peak;
	//ȡR_Peak�������ݶ�
	for(i=0;i<0.15*SAMPLE_RATE;i++)
		tempdata[i]=Clean_Data[R_Peak+i-int(0.075*SAMPLE_RATE)];
	//�ҳ������ݶ��е����з��
	for(j=0,i=0;i<0.15*SAMPLE_RATE-10;i++)
		if((tempdata[i+5]-tempdata[i])*(tempdata[i+5]-tempdata[i+10])>=0)
		{
			temppeak[j]=R_Peak+i+5-0.075*SAMPLE_RATE;
			peakslope[j]=(tempdata[i+5]-tempdata[i])*(tempdata[i+5]-tempdata[i+10]);
			j++;
			i+=5;
			if(j==10)
				break;
		}

	//�ҳ����з���ж�Ӧԭʼ�źŵķ��ȵ�������Сֵ
	for(a=0,i=0;i<j;i++)
		if(Clean_Data[temppeak[a]]<Clean_Data[temppeak[i]])
			a=i;
	Max_Peak=temppeak[a];
	Slope_Max=peakslope[a];

	for(a=0,i=0;i<j;i++)
		if(Clean_Data[temppeak[a]]>Clean_Data[temppeak[i]])
			a=i;
	Min_Peak=temppeak[a];
	Slope_Min=peakslope[a];
	//�ҳ����з���У�б�����ֵ
	for(a=0,i=0;i<j;i++)
		if(peakslope[a]<peakslope[i])
			a=i;
	Max_Slope=peakslope[a];
	Max_Slope_Peak=temppeak[a];
	//����ȷ�����,�����������ȴ������������2��������Ϊ������ΪR���
	if(Clean_Data[Min_Peak]<0 && Slope_Min>0.5*Max_Slope)
		return(Min_Peak);
	if(Clean_Data[Min_Peak]<0 && fabs(Clean_Data[Min_Peak])<=fabs(Clean_Data[Max_Peak])
													&& Slope_Max>0.5*Max_Slope)
		return(Max_Peak);
	return(Max_Slope_Peak);
}

//����QS����

 int CQRSOnLead::Accurate_Q_S_Interval(double * Clean_Data, int R_Peak_Pos_Num)
{

   int Clean_Data_Temp_Max_Pos=0;
   double Clean_Data_Temp[75],Clean_Data_Temp_Max=0.0;
   memset(Clean_Data_Temp,0,75*8);
   for (int i=0;i<0.25*SAMPLE_RATE;i++)
   {
	   if ((R_Peak_Pos_Num-int(0.125*SAMPLE_RATE)+i)<0||(R_Peak_Pos_Num-int(0.125*SAMPLE_RATE)+i)>900)
	   {
		   return 100;
	   }
	   
	   Clean_Data_Temp[i]=Clean_Data[R_Peak_Pos_Num-int(0.125*SAMPLE_RATE)+i];
   }

   for (i=0;i<0.25*SAMPLE_RATE;i++)
   { 
	   if (Clean_Data_Temp[i]>Clean_Data_Temp_Max) 
	   {
		   Clean_Data_Temp_Max=Clean_Data_Temp[i];
		   Clean_Data_Temp_Max_Pos=i;
		   
	   }
   }

	for (i=Clean_Data_Temp_Max_Pos;i>0;i--)
	{
		Clean_Data_Temp[i]=Clean_Data_Temp[i]-Clean_Data_Temp[i-1];
		if (Clean_Data_Temp[i]<0) 
		{
			Q_Pos=i;

			break;
		}
	}

	for (i=Clean_Data_Temp_Max_Pos+1;i<73;i++)
	{
        Clean_Data_Temp[i]=Clean_Data_Temp[i+2]-Clean_Data_Temp[i+1];
		if (Clean_Data_Temp[i]>0)
		{
			S_Pos=i+1;
			break;
		}
	}
       QS_Interval=(S_Pos-Q_Pos)*1000/300;
     return (QS_Interval);
}
////////////////

int CQRSOnLead::HeartRate_Output(double* ECG_Data,int Segment_Flag)
{
	int i,beat_num;
	double Wavelet_Cof[SAMPLE_RATE*LENGTH],Square_Data[SAMPLE_RATE*LENGTH];
	double Move_Data[SAMPLE_RATE*LENGTH],Clean_Data[SAMPLE_RATE*LENGTH];
	for(i=0;i<SAMPLE_RATE*LENGTH;i++)
		Clean_Data[i]=low_pass(ECG_Data[i]);
	
		Wavelet_Trans(Wavelet_Cof,Clean_Data);
		
		for(i=0;i<SAMPLE_RATE*LENGTH;i++)
			Square_Data[i]=pow(Wavelet_Cof[i],2);
		
		Move_Window(Square_Data,Move_Data);

		beat_num=R_Peak_detection(R_Peak,Move_Data,Segment_Flag,Clean_Data);
		HeartRate=Heart_Rate(R_Peak);
        //QS_Interval=Accurate_Q_S_Interval(Clean_Data,R_Peak);
        Alarm=HeartRateAbnormalAlarm(Clean_Data);
		return(HeartRate);
}

//int CQRSOnLead::HeartRateAbnormalAlarm(double *Clean_Data)
//{
//
//	for (int i=0;R_Peak[i]!=0;i++)
//	{   
//		if(R_Peak[i+1]!=0)
//		{
//			m_HAlarm[i].RRt0=(double)(R_Peak[i+1]-R_Peak[i+2])/SAMPLE_RATE;
//		}
//		else
//		{
//			m_HAlarm[i].RRt0=(double)(R_Peak[i+2]-R_Peak[i+3])/SAMPLE_RATE;
//		}
//		m_HAlarm[i].RRt=(double)(R_Peak[i]-R_Peak[i+1])/SAMPLE_RATE;
//		if(i>0) m_HAlarm[i].RRt1=(double)(R_Peak[i-1]-R_Peak[i])/SAMPLE_RATE;
//		else m_HAlarm[i].RRt1=m_HAlarm[i].RRt;
//		m_HAlarm[i].ARt=Heart_Rate8(R_Peak,i);
//		m_HAlarm[i].ARt0=Heart_Rate8(R_Peak,i+1);
//		m_HAlarm[i].ARt00=Heart_Rate8(R_Peak,i+2);		
//		m_HAlarm[i].ThreeSeconds_No_RPeack=FALSE;
////		m_HAlarm[i].WW=Accurate_Q_S_Interval(Clean_Data,R_Peak[i]);//ms
//	//////////////////////////////////////////////////////////////////////////
//		if (m_HAlarm[i].RRt>1.5&&m_HAlarm[i].ARt>1.2)
//	    {
//			return TRUE;			
//	    }	
//		if(m_HAlarm[i].ARt!=0)
//		{	if ((m_HAlarm[i].ARt)<0.5)
//			{
//				return TRUE;				
//			}
//		
//			if ((m_HAlarm[i].RRt)>1.9*(m_HAlarm[i].ARt0))
//			{
//				return TRUE;			
//			}			
//			if ((m_HAlarm[i].RRt)<0.75*(m_HAlarm[i].ARt)&&
//			//	m_HAlarm[i].WW>120&&
//				((m_HAlarm[i].RRt)+(m_HAlarm[i].RRt1))>=2*(m_HAlarm[i].ARt))
//			{
//				return TRUE;				
//			}
//			if ((m_HAlarm[i].RRt)<0.75*(m_HAlarm[i].ARt)&&
//			//	m_HAlarm[i].WW<120&&
//				((m_HAlarm[i].RRt)+(m_HAlarm[i].RRt1))<2*(m_HAlarm[i].ARt))
//			{
//				return TRUE;				
//			}
//			if ((m_HAlarm[i].RRt)<0.7*(m_HAlarm[i].ARt)&&
//			//	m_HAlarm[i].WW>120&&
//				((m_HAlarm[i].RRt)+(m_HAlarm[i].RRt1))<=1.1*(m_HAlarm[i].ARt)
//				&&((m_HAlarm[i].RRt)+(m_HAlarm[i].RRt1))>=0.7*(m_HAlarm[i].ARt))
//			{
//				return TRUE;				
//			}
//			if (m_HAlarm[i].RRt<0.33*m_HAlarm[i].ARt&&
//				((m_HAlarm[i].RRt)+(m_HAlarm[i].RRt1))<=1.1*(m_HAlarm[i].ARt)
//				&&((m_HAlarm[i].RRt)+(m_HAlarm[i].RRt1))>=0.9*(m_HAlarm[i].ARt))
//			{
//				return TRUE;
//			}
//
//		}
////		if (m_HAlarm[i].WW>120)
////		{
////			return TRUE;
////			
////		}
//		
//	}	 
//  return FALSE;	
//}
int CQRSOnLead::HeartRateAbnormalAlarm(double *Clean_Data)
{

	for (int i=0;i<6;i++)
	{   
		if(i<5)
		{
			m_HAlarm[i].RRt0=(double)(Single_RR_InterVal[i+1])/SAMPLE_RATE;
		}
		else
		{
			m_HAlarm[i].RRt0=(double)(Single_RR_InterVal[i])/SAMPLE_RATE;
		}
		m_HAlarm[i].RRt=(double)(Single_RR_InterVal[i])/SAMPLE_RATE;
		if(i>0) m_HAlarm[i].RRt1=(double)(Single_RR_InterVal[i-1])/SAMPLE_RATE;
		else m_HAlarm[i].RRt1=m_HAlarm[i].RRt;
		m_HAlarm[i].ARt=Heart_Rate8(R_Peak,i);
		m_HAlarm[i].ARt0=Heart_Rate8(R_Peak,i+1);
		m_HAlarm[i].ARt00=Heart_Rate8(R_Peak,i+2);		
		m_HAlarm[i].ThreeSeconds_No_RPeack=FALSE;
//		m_HAlarm[i].WW=Accurate_Q_S_Interval(Clean_Data,R_Peak[i]);//ms
	//////////////////////////////////////////////////////////////////////////
		if (m_HAlarm[i].RRt>1.5&&m_HAlarm[i].ARt>1.2)
	    {
			return TRUE;			
	    }	
		if(m_HAlarm[i].ARt!=0)
		{	if ((m_HAlarm[i].ARt)<0.5)
			{
				return TRUE;				
			}
		
			if ((m_HAlarm[i].RRt)>1.9*(m_HAlarm[i].ARt0))
			{
				return TRUE;			
			}	
			//0.89 ���� �ɵ� ��׼ ����Ϊ0.75
			if ((m_HAlarm[i].RRt)<0.89*(m_HAlarm[i].ARt)&&
			//	m_HAlarm[i].WW>120&&
				((m_HAlarm[i].RRt)+(m_HAlarm[i].RRt1))>=2*(m_HAlarm[i].ARt))
			{
				return TRUE;				
			}
			if ((m_HAlarm[i].RRt)<0.89*(m_HAlarm[i].ARt)&&
			//	m_HAlarm[i].WW<120&&
				((m_HAlarm[i].RRt)+(m_HAlarm[i].RRt1))<2*(m_HAlarm[i].ARt))
			{
				return TRUE;				
			}
			if ((m_HAlarm[i].RRt)<0.7*(m_HAlarm[i].ARt)&&
			//	m_HAlarm[i].WW>120&&
				((m_HAlarm[i].RRt)+(m_HAlarm[i].RRt1))<=1.1*(m_HAlarm[i].ARt)
				&&((m_HAlarm[i].RRt)+(m_HAlarm[i].RRt1))>=0.7*(m_HAlarm[i].ARt))
			{
				return TRUE;				
			}
			if (m_HAlarm[i].RRt<0.33*m_HAlarm[i].ARt&&
				((m_HAlarm[i].RRt)+(m_HAlarm[i].RRt1))<=1.1*(m_HAlarm[i].ARt)
				&&((m_HAlarm[i].RRt)+(m_HAlarm[i].RRt1))>=0.9*(m_HAlarm[i].ARt))
			{
				return TRUE;
			}

		}
//		if (m_HAlarm[i].WW>120)
//		{
//			return TRUE;
//			
//		}
		
	}	 
  return FALSE;	
}
