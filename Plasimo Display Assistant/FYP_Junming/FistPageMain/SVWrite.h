#pragma once

class CSVWrite
{
public:
	CSVWrite(CString WriteFilePath);
	~CSVWrite(void);
	CStdioFile wfile;
	// ��CSV�ļ�������һ������
	void WriteDataToFile(CStringArray* wArray);
	void  SeekPoint();
};
