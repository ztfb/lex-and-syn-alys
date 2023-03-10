#ifndef LEXALYS_H
#define LEXALYS_H
#include<map>
#include<vector>
#include<string>
#include<fstream>
#include<iostream>
using namespace std;
class LexAlys {
public:
	LexAlys(string fileName);
	vector<int> generate(string fileName);
private:
	map<string, int> table;// ���ձ�
	ifstream file;// �������ļ�
	char currChar;// ��ǰ�ַ�
private:
	// ���������������ɹ�ʱ������Ӧ���ַ���������ʧ��ʱ���ؿմ�
	string idAlys();// ��־��������
	string numberAlys();// ����������
	string separatorAlys();// �ָ���������
	string singleDoubleAlys(string seconds,bool flag);
};
#endif