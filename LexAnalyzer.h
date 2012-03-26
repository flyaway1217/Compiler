#include<iostream>
#include<fstream>
#include<map>
#include<vector>
#include "Tables.h"
using namespace std;
class LexAnalyzer
{
	//私有变量 
	private:
	//关键字的键值对集合 
	map<string,string> m_KeyTable;
	//标识符的状态转换表 
	vector<vector<int> > m_id_transform_table;
	//操作符的状态转换表 
	vector<vector<int> > m_op_transform_table;
	//注释的状态转换表 
	vector<vector<int> > m_Comment_transform_table;
	//字符串的状态转换表 
	vector<vector<int> > m_String_transform_table;
	//数字的状态转换表 
	vector<vector<int> > m_Digital_transform_table;
	//标识当前的状态 
	int m_state;
	//内部读取时的游标 
	int m_i;
	//行号
	int m_row_count;
	//列号 
	int m_col_count;
	//当前读到的字符 
	char m_buffer;
	//string数组 
	string m_token;
	//整个源文件的缓冲变量 
	string m_strbuffer;
	//标识文件是否读出 
	bool m_isRead;
	//输入文件名 
	string m_infilename; 
	//输出文件名
	string m_outfilename; 
	//获取下一个字符 
	bool getsym();
	//将buffer中的字符连接到token中 
	void strcatc();
	//将结果写入到文件中 
	void WriteFile(int row,int colum,string strs,bool flag);
	//读入原始数据
	bool ReadFile(); 
	//初始化各张转换表(已经废弃)
	void InitTables();
	//将游标后退一个
	void retract(); 
	
	//各个分类的处理函数 
	//进入标示符的子分支中 
	void Identifier(int row,int col);
	void SingleOperator(int row,int col);
	void DoubleOperator(int row,int col);
	void Comment(int row,int col);
	void StringProcess(int row,int col);
	void Digital(int row,int col);
	//分类处理函数结束
	
	//各个分类的判断函数
	bool isIdent();
	bool isSingleOperator();
	bool isDoubleOperator();
	bool isComment();
	bool isString();
	bool isDigital();
	bool isEmpty();
	//判断函数结束 
	
	//检查函数，用来确定数字是否越界
	//flag=true表示检查的是整型数
	//flag=false表示检查的是浮点数 
	bool CheckIntRange();
	bool CheckFloatRange();
	//检查函数结束 
	
	//读取配置文件 
	bool ReadTables();
	public:
	LexAnalyzer(string infilename,string outfilename);
	~LexAnalyzer();
	void Scanner();
};



