#include<iostream>
#include"LexAlys.h"
#include"SynAlys.h"
using namespace std;

int main() {
	string fileName1;
	cout << "�����ļ�·����";
	cin >> fileName1;
	string fileName2;
	cout << "�﷨���ļ�·����";
	cin >> fileName2;
	LexAlys lex("config/tokens.cfg");
	vector<int> tokens = lex.generate(fileName1);
	if (tokens.size() == 0)cout << "�����ļ�������" << endl;
	else if (tokens[0] < 0) {
		switch (tokens[0])
		{
		case -1:
			cout << "�޷�ʶ��number" << endl;
			break;
		case -2:
			cout << "�޷�ʶ��&��|" << endl;
			break;
		case -3:
			cout << "�����޷�ʶ��ķ���" << endl;
			break;
		default:
			break;
		}
	}
	else {
		SynAlys syn("config/tokens.cfg", "config/symbols.cfg", "config/productions.cfg", "config/table.cfg");
		vector<pair<int,string>> productions = syn.generate(tokens);
		if (productions.size() == 0)cout << "�﷨��������" << endl;
		else {
			ofstream file;
			file.open(fileName2, ios::out);
			for (int i = 0; i < productions.size(); i++)
				file << productions[i].first << " " << productions[i].second << endl;
			file.close();
		}
	}
	return 0;
}