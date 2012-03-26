#include"LexAnalyzer.cpp"
int main()
{
	
	string infilename;
	string outfilename;
	cout<<"Input infilename:"<<endl;
	cin>>infilename;
	cout<<"Input outfilename:"<<endl;
	cin>>outfilename;
	LexAnalyzer t(infilename,outfilename);
	t.Scanner();
}

