//ʹ��˵��:
//1.���������������ʹ����CFileDialogʱ��Flags����ΪOFN_NOCHANGEDIR
//2.�������д�������ƣ��д��Ľ�
//---------------------------------------------------------�����:ţ��ƽ
extern int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData);
extern CString strTmpPath;
class CFileOperate
{
public:
	//���캯��
	CFileOperate();
	//ȡ�õ�ǰ�������е�·��
	CString GetAppPath();
	//�ж��Ƿ����strFn�ļ���
	BOOL IsFileExist(CString strFn, BOOL bDir);
	//����strFloderName�ļ��з����ļ�����
	CString MakeDirectory(CString strFloderName);
	//�Զ������ļ���
	CString MakeDirectory();
	//�õ��ļ�����ΪstrFloderName��·��
	CString GetDirectoryPath(CString strFloderName);
	//ɾ��strFloderdName�ļ���
	void delDirectory(CString strFloderdName);
	//ɾ�����ļ���(data)
	void delMainDirectory();
	//�������ļ���
	void MakeMainDirectory();
	//�ж�strIntDigit�Ƿ�Ϊ�������Ƿ�С��intBig
	BOOL CheckIntDigit(CString strIntDigit,int intBig);
	//�ж�strFileName�Ƿ�������ļ��л��ļ�������
	BOOL CheckFileName(CString strFileName);
	//�ж�strText�Ƿ�Ϊ��
	BOOL CheckEmpty(CString strText);
	//ɾ��strFloderName�ļ�������ΪstrFileName���ļ�
	void delFile(CString strFloderName,CString strFileName);
	//�õ�strFloderName�ļ�������ΪstrFileName���ļ�·��
	CString GetFileName(CString strFolderName,CString strFileName);
	//����strFloderName�ļ�������ΪstrFileName���ļ�
	CString MakeFile(CString strFloderName,BOOL blnMake);
	//��ʾ�ļ��жԻ���
	BOOL GetFolder(CString* strSelectedFolder,const char* lpszTitle,const HWND hwndOwner,const char* strRootFolder,const char* strStartFolder);

};