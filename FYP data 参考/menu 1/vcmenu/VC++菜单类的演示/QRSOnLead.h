/************************************************************************/
/* ��    ����CQRSOnlead
   ��������������һ�����ݵ����ʣ���������������ʧ�����б���(12,13,14,15,
             16,17,19,24,25,26,28,29,30,31,32,33,34,37,38,39,40,42,43)
             ���ϱ���Ϊģ���ĵ緢��������˵�����ڴ��š�
   ���������double ECGData[900](3S*300Hz)    �ĵ�����
             int Segment_Flag                 ��־(���ε���HeartRate_Output()ʱ
                                                   ��ֵ0�����ֵΪ1)
   ���������int  R_Peak[0]  ���һ��R���λ��(�˴μ����������õ����ݸ���)
             int  HeartRate_OutPut() ��������ֵ   
			 BOOL Alarm ����ʧ��������־����ֵΪ��ʱ��ʾʧ����         
   ԭ���ߣ�          �ĺ㳬
   ����ʧ���������ߣ����� ��ҫ                                          */
/************************************************************************/

// QRSOnLead.h: interface for the CQRSOnLead class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QRSONLEAD_H__52FB12D9_1D7F_49F5_B051_378A37912D54__INCLUDED_)
#define AFX_QRSONLEAD_H__52FB12D9_1D7F_49F5_B051_378A37912D54__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define LENGTH 3			//����ÿ�δ�������ݳ���Ϊ3��
#define SAMPLE_RATE 300		//�����źŵĲ�����Ϊ300Hz
#define DATA_NUM 3000
#define Threshhold2 0.005//0.005
#define SCALE 3
#define WINDOW_WIDTH SAMPLE_RATE/10
#define Max_Beat_Num 20

class CQRSOnLead  
{
public:
	CQRSOnLead();
	virtual ~CQRSOnLead();
private:
	int RR_Interval[Max_Beat_Num];//����������ڵ�RR����
	double R_Peak_Ampl[Max_Beat_Num];
	double Ave_Ampl;
	int Ave_RR_Interval;
	int HeartRate;
	double R_Peak_Pos_Data;
	int R_Peak_Position_Num[10];
	int QS_Interval;
	int Q_Pos,S_Pos;
	int Single_RR_InterVal[10];
	
	typedef struct HeartRateAlarm{
		double RRt0;  //t-1ʱ�̵�RR����
		double RRt;   //tʱ�̵�RR����
		double RRt1;  //t+1ʱ�̵�RR����
		double ARt00; //t-2ʱ�̵�8��RR����
		double ARt0;  //t-1ʱ�̵�8��RR����
		double ARt;   //tʱ�̵�8��RR����
		int WW;    //��ʱtʱ�̵�QRS����
		BOOL ThreeSeconds_No_RPeack; //����δ����R��
	};
	HeartRateAlarm m_HAlarm[20];
	int HeartRateAbnormalAlarm(double *);
	int Accurate_Q_S_Interval(double * , int  );
	int Border(int x, int length);
	void Wavelet_Trans(double *wavelet_cof,double *clean_data);
	void Move_Window(double* Square_Data,double* Move_Data);
	double low_pass(double x);
	double high_pass(double x);
	int Heart_Rate(int* R_Peak_Pos);
	double Heart_Rate8(int* R_Peak_Pos,int pos);//�����ã���8��ƽ������
	int Accurate_R_Move(double* Move_Data, int R_Peak);
	int R_Peak_detection(int* R_Peak_Pos2,double* MOV_DATA,int segment_flag,double* Clean_Data);
    int Accurate_R_Peak_Clean(double* Clean_Data, int R_Peak);
public:
	BOOL Alarm;   //����ʧ��������־
	int HeartRate_Output(double* ECG_Data,int Segment_Flag);
	int R_Peak[Max_Beat_Num];


};

#endif // !defined(AFX_QRSONLEAD_H__52FB12D9_1D7F_49F5_B051_378A37912D54__INCLUDED_)
