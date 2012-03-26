#include"LexAnalyzer.h"
//���캯�� 
//������Դ�ļ�����Ŀ���ļ��� 
LexAnalyzer::LexAnalyzer(string infilename,string outfilename)
{
	//��ʼ���ڲ����� 
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
	//��ʼ����ʾ��״̬ת���� 
	m_id_transform_table[0][0]=0;
	m_id_transform_table[0][1]=0;
	m_id_transform_table[0][2]=-1;
	m_id_transform_table[1][0]=0;
	m_id_transform_table[1][1]=1;
	m_id_transform_table[1][2]=-2;
	
	//��ʼ��������״̬ת����
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
	
	
	//��ʼ��ע��״̬ת����
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
	
	//��ʼ���ַ���״̬ת����
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
	
	
	
	
	//��ʼ������״̬ת����
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
	
	
	//��ʼ���ؼ��ֱ�
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

//��ȡ��һ���ַ� 
//�α��Զ���1,��������������Զ�����仯 
//����ﵽ�ļ�β���򷵻�false 
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
//��m_buffer��ӵ�m_token�� 
void LexAnalyzer::strcatc()
{
	m_token+=m_buffer;
}
//���α����һ�� 
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





//��Ҫ������ɨ�������ļ� 
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
			//����Ǳ�ʶ�� 
			if(isIdent())
			{
				Identifier(m_row_count,m_col_count);
				continue;
			}
			//����ǵ������
			else if(isSingleOperator())
			{
				continue;
			}
			//�����˫����� 
			else if(isDoubleOperator())
			{
				DoubleOperator(m_row_count,m_col_count);
			}
			//�����ע�� 
			else if(isComment())
			{
				Comment(m_row_count,m_col_count);
			}
			//������ַ��� 
			else if(isString())
			{
				StringProcess(m_row_count,m_col_count);
			}
			//���������
			else if(isDigital())
			{
				Digital(m_row_count,m_col_count);
			}
			//���Կհ׷� 
			else if(isEmpty())
			{
				continue;
			}
			//�����������ţ����� 
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

//������д�뵽�ļ���
//row��colum��ʾ��ǰtoken���ַ����кź��к�
//strs��ʾ��Ҫ���������������IDENT
//flag��ʾ�Ƿ�Ҫ���token�е�ֵ,true��ʾҪ�����false��ʾ����� 
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
	//��ԭ�ļ� 
	ifstream infile(m_infilename.c_str());
	if(infile.is_open())
	{
		for(;!infile.eof();)
		{
			//��ȡԴ�ļ��е��ַ����뵽����vecotr�� 
			infile.get(m_buffer);
			m_strbuffer+=m_buffer;
		}
		infile.close();
		//InitTables();
		return true;
	}
	else
	{
		//����ļ���ʧ��,���ؼ� 
		return false;
	}
	
}




/******************���ڴ����ʶ������������*********************************/
//�ж��Ƿ��Ǳ�ʶ���������򷵻�true�����򷵻�false 
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
//��ʾ�����ӷ�֧�Ĵ����� 
void LexAnalyzer::Identifier(int row,int col)
{
	//������ַ�����״̬Ϊ0 
	if(isalpha(m_buffer)!=0)
	{
		m_state = 0;
	}
	//�����$��_����״̬Ϊ1 
	else
	{
		m_state = 1;
	}
	//��ͣ��ѭ��ֱ�����ڽ���״̬ 
	for(;m_state!=-1 && m_state!=-2;)
	{
		strcatc();
		getsym();
		//�������ĸ������ 
		if(isalnum(m_buffer)!=0)
		{
			m_state = m_id_transform_table[m_state][0];
		}
		//�����$��_ 
		else if(m_buffer=='$' || m_buffer=='_')
		{
			
			m_state = m_id_transform_table[m_state][1];
		}
		//������� 
		else
		{
			m_state = m_id_transform_table[m_state][2];
		}
	}
	//���α����һ�� 
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
/**************************��ʶ����������*****************************/
 
/******************���ڴ��������������������*********************************/
//�ж��Ƿ������ �����Ƿ���true�����򷵻�false
//ͬʱ����Ҫ������ص���� 
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
//�ж��Ƿ�˫����� �����Ƿ���true�����򷵻�false
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
//��˫���������д��� 
void LexAnalyzer::DoubleOperator(int row,int col)
{
	//ȷ����ʼ״̬ 
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
	//�ӵ�token���� 
	strcatc();
	//��ȡһ���ַ� 
	getsym();
	//״̬ת�� 
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
	//�������� 
	if(m_state==-1)
	{
		//����һ���ַ� 
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
	//˫������ 
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
	//���� 
	else if(m_state==-3)
	{
		WriteFile(row,col,InvalidOP,false);
		cerr<<Wrong;
		exit(-1);
	}
}
/*********************�����������������***********************************/


/*********************��������ע�͵ĺ���***********************************/
//�ж��Ƿ���'\',�����򷵻�true�����򷵻�false 
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

//ע�͵Ĵ����� 
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
	//��ע�� 
	if (m_state==-1)
	{
		strcatc();
	//	WriteFile(row,col,Blockcomments,true);
		m_token.clear();
	}
	//��ע�� 
	else if(m_state == -2)
	{
		//WriteFile(row,col,Linecomments,true);
		m_token.clear();
	}
	//���� 
	else if(m_state==-3)
	{
		retract();
		WriteFile(row,col,DIV,false);
	}
}
/*********************����ע�ͺ�������***********************************/


/************************�����ַ���������*****************************/
//�ж��Ƿ����ַ���
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
//�ַ���������
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
	//״̬Ϊ-1����ʾ�����˳� 
	if(m_state==-1)
	{
		strcatc();
		WriteFile(row,col,STRING,true);
	}
	//״̬Ϊ-2����ʾllegal string character 
	else if(m_state == -2)
	{
		WriteFile(row,col,ISC,false);
		cerr<<Wrong;
		exit(-1);
	}
	//״̬Ϊ-3����ʾIllegal escape sequence 
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
/************************�ַ�������������*****************************/


/************************�������ִ���ĺ���*****************************/
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
		//׷�ӵ�m_token�� 
		strcatc();
		getsym();
		//�����0 
		if(m_buffer=='0')
		{
			m_state = m_Digital_transform_table[m_state][6];
		}
		//�����1-9������ 
		else if(isdigit(m_buffer)!=0)
		{
			m_state = m_Digital_transform_table[m_state][0];
		}
		//�����E��e 
		else if(m_buffer == 'E' || m_buffer == 'e')
		{
			m_state = m_Digital_transform_table[m_state][1];
		}
		//�����С���� 
		else if(m_buffer=='.')
		{
			m_state = m_Digital_transform_table[m_state][2];
		}
		//�����+- 
		else if(m_buffer=='+' || m_buffer=='-')
		{
			m_state = m_Digital_transform_table[m_state][3];
		}
		//�������ĸ��$��_ 
		else if(isalpha(m_buffer)!=0 || m_buffer=='$' ||m_buffer=='_' )
		{
			m_state = m_Digital_transform_table[m_state][5];
		}
		//������� 
		else
		{
			m_state = m_Digital_transform_table[m_state][4];
		}		
	}
	//�����˳�,������ 
	if(m_state == -1)
	{
		//����
		retract();
		WriteFile(row,col,FLOAT_LIT,true);
	}
	//�Ƿ���ʶ�� 
	else if(m_state == -2)
	{
		retract();
		WriteFile(row,col,InvalidID,true);
		cerr<<Wrong;
		exit(-1);
	}
	//��0��ͷ������ 
	else if(m_state==-3)
	{
		strcatc();
		WriteFile(row,col,IntegerLead0,true);
		cerr<<Wrong;
		exit(-1);
	}
	//�����˳�����������
	else if(m_state==-4)
	{
		retract();
		//�ж��Ƿ�Խ�� 
		if(CheckIntRange())
		{
			WriteFile(row,col,INT_LIT,true);
		}
		else
		{
			//���Խ��	
			WriteFile(row,col,IntegerOutofRange,true);
			cerr<<Wrong;
			exit(-1);
		}
	} 
}
/************************���ִ���ĺ�������*****************************/

//�ж��Ƿ��ǿ��ַ� 
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
	//���������Ͻ� 
	string UpBound("2147483647");
	//���������½� 
	string LowBound("-2147483648");
	//�ж����� 
	if(m_token[0]== '-')
	{
		//�Ƚϳ��� 
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
			//��ȡ��ʾ��״̬ת��ͼ 
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
			//��ȡ������״̬ת���� 
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
			//��ȡע��״̬ת����
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
			//��ȡ�ַ���״̬ת����
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
			//��ȡ����״̬ת����
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
	
	/*���Դ��� 
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
