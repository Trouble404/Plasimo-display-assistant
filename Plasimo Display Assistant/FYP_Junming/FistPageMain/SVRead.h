#pragma once

class CSVRead
{
public:
	CSVRead(CString ReadFilePath);
	~CSVRead(void);
	CStdioFile file;
protected:
	//Obtain data from CSV file
	CStringArray* DevideStr(CString ItemFieldStr , char divider);
public:
	// Read and save the data in CSV
	CStringArray * CSVInf(char divided);
	// obtain the rows of CSV
	int FileRowCount(void);

	CString DeleteBlank(CString str);//把连续的空格转成一个空格
	static CString ** ReadCsvFile(CString filepath, char divided, int *row, int *col);//OUTPUT AN ARRARY
};


