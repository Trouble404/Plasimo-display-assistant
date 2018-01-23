#include "StdAfx.h"
#include "SVWrite.h"

CSVWrite::CSVWrite(CString WriteFilePath)
{
	wfile.Open(WriteFilePath,CFile::typeText|CFile::modeReadWrite);
}

CSVWrite::~CSVWrite(void)
{
	wfile.Close();
}

// 向CSV文件中输入一行数据
void CSVWrite::WriteDataToFile(CStringArray* wArray)
{
	int dataCount;
	dataCount=wArray->GetCount();
	CString wstr;
	wstr=wArray->GetAt(0);
	int i;
	for(i=1;i<dataCount;i++)
	{
		
		wstr+=+_T(",")+wArray->GetAt(i);
	}
	wstr+="\n";
	wfile.WriteString(wstr);	
}

void  CSVWrite::SeekPoint()
{
	wfile.Seek(0,CFile::end);
}