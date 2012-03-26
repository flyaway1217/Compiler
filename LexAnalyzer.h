#include<iostream>
#include<fstream>
#include<map>
#include<vector>
#include "Tables.h"
using namespace std;
class LexAnalyzer
{
	//˽�б��� 
	private:
	//�ؼ��ֵļ�ֵ�Լ��� 
	map<string,string> m_KeyTable;
	//��ʶ����״̬ת���� 
	vector<vector<int> > m_id_transform_table;
	//��������״̬ת���� 
	vector<vector<int> > m_op_transform_table;
	//ע�͵�״̬ת���� 
	vector<vector<int> > m_Comment_transform_table;
	//�ַ�����״̬ת���� 
	vector<vector<int> > m_String_transform_table;
	//���ֵ�״̬ת���� 
	vector<vector<int> > m_Digital_transform_table;
	//��ʶ��ǰ��״̬ 
	int m_state;
	//�ڲ���ȡʱ���α� 
	int m_i;
	//�к�
	int m_row_count;
	//�к� 
	int m_col_count;
	//��ǰ�������ַ� 
	char m_buffer;
	//string���� 
	string m_token;
	//����Դ�ļ��Ļ������ 
	string m_strbuffer;
	//��ʶ�ļ��Ƿ���� 
	bool m_isRead;
	//�����ļ��� 
	string m_infilename; 
	//����ļ���
	string m_outfilename; 
	//��ȡ��һ���ַ� 
	bool getsym();
	//��buffer�е��ַ����ӵ�token�� 
	void strcatc();
	//�����д�뵽�ļ��� 
	void WriteFile(int row,int colum,string strs,bool flag);
	//����ԭʼ����
	bool ReadFile(); 
	//��ʼ������ת����(�Ѿ�����)
	void InitTables();
	//���α����һ��
	void retract(); 
	
	//��������Ĵ����� 
	//�����ʾ�����ӷ�֧�� 
	void Identifier(int row,int col);
	void SingleOperator(int row,int col);
	void DoubleOperator(int row,int col);
	void Comment(int row,int col);
	void StringProcess(int row,int col);
	void Digital(int row,int col);
	//���ദ��������
	
	//����������жϺ���
	bool isIdent();
	bool isSingleOperator();
	bool isDoubleOperator();
	bool isComment();
	bool isString();
	bool isDigital();
	bool isEmpty();
	//�жϺ������� 
	
	//��麯��������ȷ�������Ƿ�Խ��
	//flag=true��ʾ������������
	//flag=false��ʾ�����Ǹ����� 
	bool CheckIntRange();
	bool CheckFloatRange();
	//��麯������ 
	
	//��ȡ�����ļ� 
	bool ReadTables();
	public:
	LexAnalyzer(string infilename,string outfilename);
	~LexAnalyzer();
	void Scanner();
};



