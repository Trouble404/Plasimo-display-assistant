#include "StdAfx.h"
#include "SVRead.h"

CSVRead::CSVRead(CString ReadFilePath)
{
	file.Open(ReadFilePath,CFile::typeText|CFile::modeRead);
	file.SeekToBegin();
}

CSVRead::~CSVRead(void)
{
	file.Close();
}



CStringArray* CSVRead::DevideStr(CString ItemFieldStr , char divider) //Obtain data from CSV file
{
	CStringArray *SingleItemArray=new CStringArray;
	CStringArray *tempArray=new CStringArray;
	CString SingleItem;
	int dividerPos,dividerSum=0;
	dividerPos=ItemFieldStr.Find(divider,0);
	//counting the number of dividers
	while(dividerPos>=0)
	{
		dividerSum++;
		dividerPos=ItemFieldStr.Find(divider,dividerPos+1);
	}
	for(int i=0;i<=dividerSum;i++)
	{
		AfxExtractSubString(SingleItem,ItemFieldStr,i,divider);
		SingleItemArray->Add(SingleItem);

	}
	SingleItemArray->Add('\0');
	return SingleItemArray;
}

//if not get the right data, delete this data
CStringArray* CSVRead::CSVInf(char divided)
{
	CStringArray* tempString;
	CString str;
	file.ReadString(str);

	if(divided == ' ')
	str = DeleteBlank(str);
	tempString=DevideStr(str, divided);
	return tempString;
}

// counting the number of rows of csv
int CSVRead::FileRowCount(void)
{
	int countline=0;
	CString sss;
	while(file.ReadString(sss))
		countline++;
	file.SeekToBegin();
	return countline;
}
//transf continuous blank to one
CString CSVRead::DeleteBlank(CString str)
{
	CString reStr = "";
	for (int i = 0; i < str.GetLength()-1; i++)
	{	
			if (str[i] == ' '&& str[i + 1] == ' ')
			{

			}
			else
				reStr += str[i];
			
		if(i == str.GetLength() - 1)
		reStr += str[i];
   }

	return reStr;
}
 CString ** CSVRead::ReadCsvFile(CString filepath, char divided,int *row,int *col)//Read csv file, get related data and save into an arrary
{
	CStringArray * Array = NULL;
	
	if (!PathFileExists(filepath))
		return NULL;
	CSVRead read(filepath);
	
	int Rowcount = read.FileRowCount();
	Array = read.CSVInf(divided);
	int Columcount = Array->GetSize();
	
	CString **p = new CString *[Rowcount];
	for (int i = 0; i < Rowcount; i++)
		p[i] = new CString[Columcount];
	for (int i = 0; i < Columcount; i++)
		p[0][i] = Array->GetAt(i);
	
	*row = Rowcount;
	*col = Columcount;
	for (int i = 1; i<Rowcount ; i++)
	{
		Array = read.CSVInf(divided);
		for (int j = 0; j < Columcount; j++)
		{
			CString a = Array->GetAt(j);
			p[i][j] = Array->GetAt(j);
		}
	}

	return p;

}


