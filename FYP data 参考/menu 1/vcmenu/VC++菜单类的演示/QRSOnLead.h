/************************************************************************/
/* 类    名：CQRSOnlead
   功能描述：计算一道数据的心率，并对以下心率是失常进行报警(12,13,14,15,
             16,17,19,24,25,26,28,29,30,31,32,33,34,37,38,39,40,42,43)
             以上编码为模拟心电发生器中文说明书内代号。
   输入参数：double ECGData[900](3S*300Hz)    心电数据
             int Segment_Flag                 标志(初次调用HeartRate_Output()时
                                                   赋值0，其后赋值为1)
   输出参数：int  R_Peak[0]  最后一个R峰的位置(此次计算心率所用的数据个数)
             int  HeartRate_OutPut() 返回心率值   
			 BOOL Alarm 心率失常报警标志。其值为真时表示失常。         
   原作者：          夏恒超
   心律失常报警作者：王翔 赵耀                                          */
/************************************************************************/

// QRSOnLead.h: interface for the CQRSOnLead class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QRSONLEAD_H__52FB12D9_1D7F_49F5_B051_378A37912D54__INCLUDED_)
#define AFX_QRSONLEAD_H__52FB12D9_1D7F_49F5_B051_378A37912D54__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define LENGTH 3			//定义每次处理的数据长度为3秒
#define SAMPLE_RATE 300		//定义信号的采样率为300Hz
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
	int RR_Interval[Max_Beat_Num];//存放六个周期的RR间期
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
		double RRt0;  //t-1时刻的RR间期
		double RRt;   //t时刻的RR间期
		double RRt1;  //t+1时刻的RR间期
		double ARt00; //t-2时刻的8个RR间期
		double ARt0;  //t-1时刻的8个RR间期
		double ARt;   //t时刻的8个RR间期
		int WW;    //此时t时刻的QRS波宽
		BOOL ThreeSeconds_No_RPeack; //三秒未出现R峰
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
	double Heart_Rate8(int* R_Peak_Pos,int pos);//报警用，求8个平均心率
	int Accurate_R_Move(double* Move_Data, int R_Peak);
	int R_Peak_detection(int* R_Peak_Pos2,double* MOV_DATA,int segment_flag,double* Clean_Data);
    int Accurate_R_Peak_Clean(double* Clean_Data, int R_Peak);
public:
	BOOL Alarm;   //心率失常报警标志
	int HeartRate_Output(double* ECG_Data,int Segment_Flag);
	int R_Peak[Max_Beat_Num];


};

#endif // !defined(AFX_QRSONLEAD_H__52FB12D9_1D7F_49F5_B051_378A37912D54__INCLUDED_)
