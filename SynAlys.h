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
	vector<pair<int,string>> generate(vector<int> tokens);// 生成语法树
private:
	map<string, int> table1;// 终结符对照表
	map<string, int> table2;// 非终结符对照表
	map<int, string> table3;// 产生式对照表
	static const int tokensNum = 36;
	static const int symbolsNum = 27;
	int alysTable[tokensNum][symbolsNum];// 分析表
	vector<string> split(string source, char c);// 分割函数
};
#endif

