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
	map<string, int> table;// 对照表
	ifstream file;// 待分析文件
	char currChar;// 当前字符
private:
	// 分析函数：分析成功时返回响应的字符串，分析失败时返回空串
	string idAlys();// 标志符分析器
	string numberAlys();// 常量分析器
	string separatorAlys();// 分隔符分析器
	string singleDoubleAlys(string seconds,bool flag);
};
#endif