#pragma once

class CSVWrite
{
public:
	CSVWrite(CString WriteFilePath);
	~CSVWrite(void);
	CStdioFile wfile;
	// 向CSV文件中输入一行数据
	void WriteDataToFile(CStringArray* wArray);
	void  SeekPoint();
};
