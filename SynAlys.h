#ifndef SYNALYS_H
#define SYNALYS_H
#include<map>
#include<vector>
#include<stack>
#include<string>
#include<fstream>
#include<iostream>
using namespace std;
class SynAlys {
public:
	SynAlys(string fileName1, string fileName2, string fileName3, string fileName4);
	vector<pair<int,string>> generate(vector<int> tokens);// �����﷨��
private:
	map<string, int> table1;// �ս�����ձ�
	map<string, int> table2;// ���ս�����ձ�
	map<int, string> table3;// ����ʽ���ձ�
	static const int tokensNum = 36;
	static const int symbolsNum = 27;
	int alysTable[tokensNum][symbolsNum];// ������
	vector<string> split(string source, char c);// �ָ��
};
#endif

