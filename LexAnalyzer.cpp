#include"LexAnalyzer.h"
//构造函数 
//参数是源文件名和目的文件名 
LexAnalyzer::LexAnalyzer(string infilename,string outfilename)
{
	//初始化内部变量 
	m_col_count = 0;
	m_row_count = 1;
	m_i = 0;
	m_state = 0;
	m_infilename = infilename;
	m_outfilename = outfilename;
}

void LexAnalyzer::InitTables()
{
	int i,j;
	//初始化标示符状态转化表 
	m_id_transform_table[0][0]=0;
	m_id_transform_table[0][1]=0;
	m_id_transform_table[0][2]=-1;
	m_id_transform_table[1][0]=0;
	m_id_transform_table[1][1]=1;
	m_id_transform_table[1][2]=-2;
	
	//初始化操作符状态转化表
	for(i = 0;i < 8;++i)
	{
		for(j = 0;j < 9;++j)
		{
			if(i == 0)
			{
				m_op_transform_table[i][j]=-3;
			}
			else
			{
				m_op_transform_table[i][j]=-1;
			}
			
		}
	}
	m_op_transform_table[0][0]=-2;
	m_op_transform_table[1][3]=-2;
	m_op_transform_table[2][3]=-2;
	m_op_transform_table[3][3]=-2;
	m_op_transform_table[4][3]=-2;
	m_op_transform_table[5][5]=-2;
	m_op_transform_table[6][6]=-2;
	m_op_transform_table[7][7]=-2;
	
	
	//初始化注释状态转换表
	m_Comment_transform_table[0][0]=3; 
	m_Comment_transform_table[0][1]=1;
	m_Comment_transform_table[0][2]=-3;
	m_Comment_transform_table[0][3]=-3;
	m_Comment_transform_table[1][0]=1;
	m_Comment_transform_table[1][1]=2;
	m_Comment_transform_table[1][2]=1;
	m_Comment_transform_table[1][3]=1;
	m_Comment_transform_table[2][0]=-1;
	m_Comment_transform_table[2][1]=2;
	m_Comment_transform_table[2][2]=1;
	m_Comment_transform_table[2][3]=1;
	m_Comment_transform_table[3][0]=3;
	m_Comment_transform_table[3][1]=3;
	m_Comment_transform_table[3][2]=-2;
	m_Comment_transform_table[3][3]=3;
	
	//初始化字符串状态转换表
	for(i = 0;i < 6;++i)
	{
		for(j = 0;j < 6;++j)
		{
			if(j == 0)
			{
				m_String_transform_table[i][j]=-1;
			}
			else if(j == 1)
			{
				m_String_transform_table[i][j]=1;
			}
			else if(j == 4)
			{
				m_String_transform_table[i][j]=-2;
			}
			else
			{
				m_String_transform_table[i][j]=0;
			}
			
		}
	}
	m_String_transform_table[1][0]=5;
	m_String_transform_table[1][1]=4;
	m_String_transform_table[1][2]=2;
	m_String_transform_table[1][3]=3;
	m_String_transform_table[1][4]=-2;
	m_String_transform_table[1][5]=-3;	
	
	
	
	
	//初始化数字状态转换表
	for(int i = 0;i < 8;++i)
	{
		for(j = 0;j < 7;++j)
		{
			if(j == 5)
			{
				m_Digital_transform_table[i][j]=7;
			}
			else
			{
				m_Digital_transform_table[i][j]=-1;
			}
		}
	}
	m_Digital_transform_table[0][0]=0;
	m_Digital_transform_table[1][0]=2;
	m_Digital_transform_table[2][0]=2;
	m_Digital_transform_table[3][0]=5;
	m_Digital_transform_table[4][0]=5;
	m_Digital_transform_table[5][0]=5;
	m_Digital_transform_table[6][0]=-3;
	m_Digital_transform_table[7][0]=-2;
	
	m_Digital_transform_table[0][1]=3;
	m_Digital_transform_table[1][1]=3;
	m_Digital_transform_table[2][1]=3;
	m_Digital_transform_table[3][1]=-1;
	m_Digital_transform_table[4][1]=-1;
	m_Digital_transform_table[5][1]=-1;
	m_Digital_transform_table[6][1]=-2;\
	m_Digital_transform_table[7][1]=-2;
	
	m_Digital_transform_table[0][2]=1;
	m_Digital_transform_table[6][2]=1;
	m_Digital_transform_table[7][2]=-2;
	
	m_Digital_transform_table[3][3]=4;
	m_Digital_transform_table[0][3]=-4;
	m_Digital_transform_table[7][3]=-2;
	
	m_Digital_transform_table[0][4]=-4;
	m_Digital_transform_table[7][4]=-2;
	
	m_Digital_transform_table[0][6]=0;
	m_Digital_transform_table[1][6]=2;
	m_Digital_transform_table[2][6]=2;
	m_Digital_transform_table[3][6]=5;
	m_Digital_transform_table[4][6]=5;
	m_Digital_transform_table[5][6]=5;
	m_Digital_transform_table[6][6]=6;	
	m_Digital_transform_table[7][6]=-2;
	
	
	//初始化关键字表
	m_KeyTable.insert(pair<string,string>("bool","BOOL"));
	m_KeyTable.insert(pair<string,string>("double","DOUBLE"));
	m_KeyTable.insert(pair<string,string>("else","ELSE"));
	m_KeyTable.insert(pair<string,string>("false","FALSE"));
	m_KeyTable.insert(pair<string,string>("if","IF"));
	m_KeyTable.insert(pair<string,string>("int","INT"));
	m_KeyTable.insert(pair<string,string>("null","NULL"));
	m_KeyTable.insert(pair<string,string>("read","READ"));
	m_KeyTable.insert(pair<string,string>("string","STRING"));
	m_KeyTable.insert(pair<string,string>("true","TRUE"));
	m_KeyTable.insert(pair<string,string>("void","VOID"));
	m_KeyTable.insert(pair<string,string>("while","WHILE"));
	m_KeyTable.insert(pair<string,string>("write","WRITE"));
	

}


LexAnalyzer::~LexAnalyzer()
{
	
}

//获取下一个字符 
//游标自动加1,行坐标和列坐标自动跟随变化 
//如果达到文件尾，则返回false 
bool LexAnalyzer::getsym()
{
	if(m_i < m_strbuffer.length())
	{
		m_buffer = m_strbuffer[m_i++];
		m_col_count++;
		if(m_buffer == '\n')
		{
			m_row_count++;
			m_col_count=0;
		}
		if(m_buffer == '\t')
		{
			m_col_count+=3;
		}
		return true;
	}
	else
	{
		return false;
	}
}
//将m_buffer添加到m_token中 
void LexAnalyzer::strcatc()
{
	m_token+=m_buffer;
}
//将游标后退一个 
void LexAnalyzer::retract()
{
	m_buffer = m_strbuffer[--m_i];
	m_col_count--;
	if(m_buffer == '\n')
	{
		m_row_count--;
		m_col_count=1;
	}
	if(m_buffer == '\t')
	{
		m_col_count-=3;
	}
}





//主要函数，扫描整个文件 
void LexAnalyzer::Scanner()
{
	if(!ReadTables())
	{
		cerr<<"Configuration file wrong!"<<endl;
		exit(-1);
	}
	if(ReadFile())
	{
		for(;getsym();)
		{
			//如果是标识符 
			if(isIdent())
			{
				Identifier(m_row_count,m_col_count);
				continue;
			}
			//如果是单运算符
			else if(isSingleOperator())
			{
				continue;
			}
			//如果是双运算符 
			else if(isDoubleOperator())
			{
				DoubleOperator(m_row_count,m_col_count);
			}
			//如果是注释 
			else if(isComment())
			{
				Comment(m_row_count,m_col_count);
			}
			//如果是字符串 
			else if(isString())
			{
				StringProcess(m_row_count,m_col_count);
			}
			//如果是数字
			else if(isDigital())
			{
				Digital(m_row_count,m_col_count);
			}
			//忽略空白符 
			else if(isEmpty())
			{
				continue;
			}
			//出现其他符号，报错 
			else
			{
				strcatc();
				WriteFile(m_row_count,m_col_count,InvalidID,true);
				cerr<<Wrong;
				exit(-1);
			}
		}
		cout<<"Successed!";
	}
}

//将数据写入到文件中
//row、colum表示当前token首字符的行号和列号
//strs表示需要输出的类型名，如IDENT
//flag表示是否要输出token中的值,true表示要输出，false表示不输出 
void LexAnalyzer::WriteFile(int row,int colum,string strs,bool flag)
{
	ofstream outFile(m_outfilename.c_str(),ios::app);
	if(outFile.is_open())
	{
		outFile<<row<<" "<<colum<<" ";
		outFile<<strs;
		if(flag)
		{
			outFile<<":";
			for(int i = 0;i < m_token.length();++i)
			{
				outFile<<m_token[i];	
			}
		}
		outFile<<endl;
		outFile.close();
		m_token="";
	}
}

bool LexAnalyzer::ReadFile()
{
	//打开原文件 
	ifstream infile(m_infilename.c_str());
	if(infile.is_open())
	{
		for(;!infile.eof();)
		{
			//读取源文件中的字符放入到缓存vecotr中 
			infile.get(m_buffer);
			m_strbuffer+=m_buffer;
		}
		infile.close();
		//InitTables();
		return true;
	}
	else
	{
		//如果文件打开失败,返回假 
		return false;
	}
	
}




/******************用于处理标识符的两个函数*********************************/
//判断是否是标识符，若是则返回true，否则返回false 
bool LexAnalyzer::isIdent()
{
	if(isalpha(m_buffer) != 0 || m_buffer=='_' || m_buffer=='$')
	{
		return true;
	}
	else
	{
		return false;
	}
}
//标示符的子分支的处理函数 
void LexAnalyzer::Identifier(int row,int col)
{
	//如果是字符，则状态为0 
	if(isalpha(m_buffer)!=0)
	{
		m_state = 0;
	}
	//如果是$或_，则状态为1 
	else
	{
		m_state = 1;
	}
	//不停地循环直到处于结束状态 
	for(;m_state!=-1 && m_state!=-2;)
	{
		strcatc();
		getsym();
		//如果是字母或数字 
		if(isalnum(m_buffer)!=0)
		{
			m_state = m_id_transform_table[m_state][0];
		}
		//如果是$或_ 
		else if(m_buffer=='$' || m_buffer=='_')
		{
			
			m_state = m_id_transform_table[m_state][1];
		}
		//其他情况 
		else
		{
			m_state = m_id_transform_table[m_state][2];
		}
	}
	//将游标后退一个 
	retract();
	if(m_state==-1)
	{
		if(!m_KeyTable[m_token].empty())
		{
			m_token = m_KeyTable[m_token];
			WriteFile(row,col,Keywords,true);
		}
		else
		{
			WriteFile(row,col,IDENT,true);
		}
		return;
	}
	else
	{
		WriteFile(row,col,InvalidID,true);
		cerr<<Wrong; 
		exit(-1);
	}
}
/**************************标识符函数结束*****************************/
 
/******************用于处理操作符的三个个函数*********************************/
//判断是否单运算符 ，若是返回true，否则返回false
//同时还需要处理相关的输出 
bool LexAnalyzer::isSingleOperator()
{
	switch(m_buffer)
	{
		case '*':WriteFile(m_row_count,m_col_count,STAR,false);return true;
		case '(':WriteFile(m_row_count,m_col_count,LPAREN,false);return true;
		case ')':WriteFile(m_row_count,m_col_count,RPAREN,false);return true;
		case '{':WriteFile(m_row_count,m_col_count,LBRACE,false);return true;
		case '}':WriteFile(m_row_count,m_col_count,RBRACE,false);return true;
		case '[':WriteFile(m_row_count,m_col_count,LBRACKET,false);return true;
		case ']':WriteFile(m_row_count,m_col_count,RBRACKET,false);return true;
		case ';':WriteFile(m_row_count,m_col_count,SEMI,false);return true;
		case ',':WriteFile(m_row_count,m_col_count,COMMA,false);return true;
		case '%':WriteFile(m_row_count,m_col_count,MOD,false);return true;
		default:return false;
	}
}
//判断是否双运算符 ，若是返回true，否则返回false
bool LexAnalyzer::isDoubleOperator()
{
	switch(m_buffer)
	{
		case '|':
		case '<':
		case '>':
		case '=':
		case '!':
		case '+':
		case '-':
		case '&':return true;
		default:return false;
	}
}
//对双操作符进行处理 
void LexAnalyzer::DoubleOperator(int row,int col)
{
	//确定初始状态 
	switch(m_buffer)
	{
		case '|':m_state = 0;break;
		case '<':m_state = 1;break;
		case '>':m_state = 2;break;
		case '=':m_state = 3;break;
		case '!':m_state = 4;break;
		case '+':m_state = 5;break;
		case '-':m_state = 6;break;
		case '&':m_state = 7;break;
	}
	//接到token后面 
	strcatc();
	//获取一个字符 
	getsym();
	//状态转换 
	switch(m_buffer)
	{
		case '|':m_state = m_op_transform_table[m_state][0];break;
		case '<':m_state = m_op_transform_table[m_state][1];break;
		case '>':m_state = m_op_transform_table[m_state][2];break;
		case '=':m_state = m_op_transform_table[m_state][3];break;
		case '!':m_state = m_op_transform_table[m_state][4];break;
		case '+':m_state = m_op_transform_table[m_state][5];break;
		case '-':m_state = m_op_transform_table[m_state][6];break;
		case '&':m_state = m_op_transform_table[m_state][7];break;
		default :m_state = m_op_transform_table[m_state][8];break;
	}
	//单操作符 
	if(m_state==-1)
	{
		//回退一个字符 
		retract();
		switch(m_token[0])
		{
			case '<':WriteFile(row,col,LT,false);break;
			case '>':WriteFile(row,col,GT,false);break;
			case '=':WriteFile(row,col,ASSIGN,false);break;
			case '!':WriteFile(row,col,LNOT,false);break;
			case '+':WriteFile(row,col,PLUS,false);break;
			case '-':WriteFile(row,col,MINUS,false);break;
			case '&':WriteFile(row,col,ADDROF,false);break;
		}
	}
	//双操作符 
	else if(m_state==-2)
	{
		strcatc();
		if(m_token[0]=='|' && m_token[1]=='|'){WriteFile(row,col,LOR,false);}
		if(m_token[0]=='<' && m_token[1]=='='){WriteFile(row,col,LTE,false);}
		if(m_token[0]=='>' && m_token[1]=='='){WriteFile(row,col,GTE,false);}
		if(m_token[0]=='=' && m_token[1]=='='){WriteFile(row,col,EQUAL,false);}
		if(m_token[0]=='!' && m_token[1]=='='){WriteFile(row,col,NEQUAL,false);}
		if(m_token[0]=='+' && m_token[1]=='+'){WriteFile(row,col,INCR,false);}
		if(m_token[0]=='-' && m_token[1]=='-'){WriteFile(row,col,DECR,false);}
		if(m_token[0]=='&' && m_token[1]=='&'){WriteFile(row,col,LAND,false);}
	}
	//错误 
	else if(m_state==-3)
	{
		WriteFile(row,col,InvalidOP,false);
		cerr<<Wrong;
		exit(-1);
	}
}
/*********************处理操作符函数结束***********************************/


/*********************两个处理注释的函数***********************************/
//判断是否是'\',若是则返回true，否则返回false 
bool LexAnalyzer::isComment()
{
	if(m_buffer=='/')
	{
		return true;
	}
	else
	{
		return false;
	}
}

//注释的处理函数 
void LexAnalyzer::Comment(int row,int col)
{
	
	m_state=0;
	for(;m_state!=-1 && m_state!=-2 && m_state!=-3;)
	{
		strcatc();
		if(getsym())
		{
			switch(m_buffer)
			{
				case '/':m_state=m_Comment_transform_table[m_state][0];break;
				case '*':m_state=m_Comment_transform_table[m_state][1];break;
				case '\n':m_state=m_Comment_transform_table[m_state][2];break;
				default:m_state=m_Comment_transform_table[m_state][3];break;
			}
		}
		else
		{
			WriteFile(row,col,InvalidComment,false);
			cerr<<Wrong;
			exit(-1);
		}
	}
	//块注释 
	if (m_state==-1)
	{
		strcatc();
	//	WriteFile(row,col,Blockcomments,true);
		m_token.clear();
	}
	//行注释 
	else if(m_state == -2)
	{
		//WriteFile(row,col,Linecomments,true);
		m_token.clear();
	}
	//除号 
	else if(m_state==-3)
	{
		retract();
		WriteFile(row,col,DIV,false);
	}
}
/*********************两个注释函数结束***********************************/


/************************两个字符串处理函数*****************************/
//判断是否是字符串
bool LexAnalyzer::isString()
{
	if(m_buffer=='\"')
	{
		return true;
	}
	else
	{
		return false;
	}
} 
//字符串处理函数
void LexAnalyzer::StringProcess(int row,int col)
{
	m_state = 0;
	for(;m_state >= 0;)
	{
		strcatc();
		if(getsym())
		{
			switch(m_buffer)
			{
				case '\"':m_state = m_String_transform_table[m_state][0];break;
				case '\\':m_state = m_String_transform_table[m_state][1];break;
				case 'n':m_state = m_String_transform_table[m_state][2];break;
				case 't':m_state = m_String_transform_table[m_state][3];break;
				case '\t':m_state = m_String_transform_table[m_state][4];break;
				default:m_state = m_String_transform_table[m_state][5];break;
			}
		}
		else
		{
			WriteFile(row,col,USL,false);
			cerr<<Wrong;
			exit(-1);
		}
	}
	//状态为-1，表示正常退出 
	if(m_state==-1)
	{
		strcatc();
		WriteFile(row,col,STRING,true);
	}
	//状态为-2，表示llegal string character 
	else if(m_state == -2)
	{
		WriteFile(row,col,ISC,false);
		cerr<<Wrong;
		exit(-1);
	}
	//状态为-3，表示Illegal escape sequence 
	else if(m_state==-3)
	{
		m_token="";
		m_token='\\';
		strcatc();
		WriteFile(row,col,IES,true);
		cerr<<Wrong;
		exit(-1);
	}
} 
/************************字符串处理函数结束*****************************/


/************************两个数字处理的函数*****************************/
bool LexAnalyzer::isDigital()
{
	if(isdigit(m_buffer)!=0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void LexAnalyzer::Digital(int row,int col)
{
	if(m_buffer=='0')
	{
		m_state = 6;
	}
	else
	{
		m_state = 0;
	}
	for(;m_state >= 0;)
	{
		//追加到m_token中 
		strcatc();
		getsym();
		//如果是0 
		if(m_buffer=='0')
		{
			m_state = m_Digital_transform_table[m_state][6];
		}
		//如果是1-9的数字 
		else if(isdigit(m_buffer)!=0)
		{
			m_state = m_Digital_transform_table[m_state][0];
		}
		//如果是E或e 
		else if(m_buffer == 'E' || m_buffer == 'e')
		{
			m_state = m_Digital_transform_table[m_state][1];
		}
		//如果是小数点 
		else if(m_buffer=='.')
		{
			m_state = m_Digital_transform_table[m_state][2];
		}
		//如果是+- 
		else if(m_buffer=='+' || m_buffer=='-')
		{
			m_state = m_Digital_transform_table[m_state][3];
		}
		//如果是字母或$或_ 
		else if(isalpha(m_buffer)!=0 || m_buffer=='$' ||m_buffer=='_' )
		{
			m_state = m_Digital_transform_table[m_state][5];
		}
		//其他情况 
		else
		{
			m_state = m_Digital_transform_table[m_state][4];
		}		
	}
	//正常退出,浮点数 
	if(m_state == -1)
	{
		//回退
		retract();
		WriteFile(row,col,FLOAT_LIT,true);
	}
	//非法标识符 
	else if(m_state == -2)
	{
		retract();
		WriteFile(row,col,InvalidID,true);
		cerr<<Wrong;
		exit(-1);
	}
	//以0开头的数字 
	else if(m_state==-3)
	{
		strcatc();
		WriteFile(row,col,IntegerLead0,true);
		cerr<<Wrong;
		exit(-1);
	}
	//正常退出，整型数字
	else if(m_state==-4)
	{
		retract();
		//判断是否越界 
		if(CheckIntRange())
		{
			WriteFile(row,col,INT_LIT,true);
		}
		else
		{
			//如果越界	
			WriteFile(row,col,IntegerOutofRange,true);
			cerr<<Wrong;
			exit(-1);
		}
	} 
}
/************************数字处理的函数结束*****************************/

//判断是否是空字符 
bool LexAnalyzer::isEmpty()
{
	if(m_buffer =='\t' || m_buffer=='\n' || m_buffer==' ' ||m_buffer=='\r')
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool LexAnalyzer::CheckIntRange()
{
	//整型数的上界 
	string UpBound("2147483647");
	//整型数的下届 
	string LowBound("-2147483648");
	//判断正负 
	if(m_token[0]== '-')
	{
		//比较长度 
		if(m_token.length() > LowBound.length())
		{
			return false;
		}
		else if(m_token.length() == LowBound.length())
		{
			for(int i = 1;i < m_token.length();++i)
			{
				if(m_token[i] > LowBound[i])
				{
					return false;
				}
			}
		}
	}
	else
	{
		if(m_token.length() > UpBound.length())
		{
			return false;
		}
		else if(m_token.length() == UpBound.length())
		{
			for(int i = 0;i < m_token.length();++i)
			{
				if(m_token[i] > UpBound[i])
				{
					return false;
				}
			}
		}
	}
	return true;
}



bool LexAnalyzer::ReadTables()
{
	ifstream infile("Table.txt");
	int n,m,i,j;
	string str;
	string Lower,Upper;
	if(infile.is_open())
	{
		for(;;)
		{
			infile>>str;
			//读取标示符状态转换图 
			if(str == "IdentTable")
			{
				infile>>m>>n;
				m_id_transform_table.resize(m);
				for(i = 0;i < m;++i)
				{
					m_id_transform_table[i].resize(n);
					for(j = 0;j < n;++j)
					{
						infile>>m_id_transform_table[i][j];
					}
				}
			}
			//读取操作符状态转换表 
			else if(str == "OPTable" )
			{
				infile>>m>>n;
				m_op_transform_table.resize(m);
				for(i = 0;i < m;++i)
				{
					m_op_transform_table[i].resize(n);
					for(j = 0;j < n;++j)
					{
						infile>>m_op_transform_table[i][j];
					}
				}
			}
			//读取注释状态转换表
			else if(str == "CommentTable" )
			{
				infile>>m>>n;
				m_Comment_transform_table.resize(m);
				for(i = 0;i < m;++i)
				{
					m_Comment_transform_table[i].resize(n);
					for(j = 0;j < n;++j)
					{
						infile>>m_Comment_transform_table[i][j];
					}
				}
			}
			//读取字符串状态转换表
			else if(str == "StringTable" )
			{
				infile>>m>>n;
				m_String_transform_table.resize(m);
				for(i = 0;i < m;++i)
				{
					m_String_transform_table[i].resize(n);
					for(j = 0;j < n;++j)
					{
						infile>>m_String_transform_table[i][j];
					}
				}
			}
			//读取数字状态转换表
			else if(str == "DigitalTable" )
			{
				infile>>m>>n;
				m_Digital_transform_table.resize(m);
				for(i = 0;i < m;++i)
				{
					m_Digital_transform_table[i].resize(n);
					for(j = 0;j < n;++j)
					{
						infile>>m_Digital_transform_table[i][j];
					}
				}
			}
			else if(str == "KeyTables")
			{
				infile>>m;
				for(i = 0;i < m;++i)
				{
					infile>>Lower>>Upper;
					m_KeyTable.insert(pair<string,string>(Lower,Upper));
				}
			}
			else if(str == "end")
			{
				break;
			}
		}	
		infile.close();
		return true;
	}
	else
	{
		return false;
	}
	
	/*测试代码 
	for(i = 0;i < m_Digital_transform_table.size();++i)
	{
		for(j = 0;j < m_Digital_transform_table[i].size();++j)
		{
			cout<<m_Digital_transform_table[i][j]<<" ";
		}
		cout<<endl;
	}
	*/
}
