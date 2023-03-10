#include"SynAlys.h"
SynAlys::SynAlys(string fileName1, string fileName2, string fileName3, string fileName4) {
	ifstream file;
	int counter;
	// 读入终结符
	file.open(fileName1, ios::in);
	if (!file.is_open())return;
	string token = "";
	counter = 0;
	while (getline(file, token))
	{
		table1[token] = counter;
		counter++;
	}
	file.close();
	// 读入非终结符
	file.open(fileName2, ios::in);
	if (!file.is_open())return;
	string  symbol= "";
	counter = 0;
	while (getline(file, symbol))
	{
		table2[symbol] = counter;
		counter++;
	}
	file.close();
	// 读入产生式
	file.open(fileName3, ios::in);
	if (!file.is_open())return;
	string production = "";
	counter = 1;
	while (getline(file, production))
	{
		table3[counter] = production;
		counter++;
	}
	file.close();
	// 初始化分析表
	file.open(fileName4, ios::in);
	if (!file.is_open())return;
	string  text = "";
	counter = 0;
	while (getline(file, text))
	{
		vector<string> ss = split(text, '\t');
		for (int i = 0; i < ss.size(); i++) {
			if (ss[i].size() <= 2)alysTable[i][counter] = atoi(ss[i].c_str());
			else alysTable[i][counter] = -1;// 冲突项
		}
		counter++;
	}
	file.close();
}
vector<pair<int,string>> SynAlys::generate(vector<int> tokens) {
	vector<pair<int, string>> productions;
	stack<pair<bool, int>> push_stack;// 下推栈：flag==true 终结符 flag=false 非终极符
	push_stack.push(pair<bool, int>(true, 0));// 压入#
	push_stack.push(pair<bool, int>(false, 0));// 压入文法开始符号
	tokens.push_back(0);// 加入终止符
	int index = 0;// 读头位置
	while (true)
	{
		pair<bool, int> top = push_stack.top();
		if (top.first) {// 终结符
			if (top.second == 0)return productions;
			else if (top.second == tokens[index]) {
				index++;
				push_stack.pop();
			}
			else {// 出错
				productions.clear();
				return productions;
			}
		}
		else {// 非终结符
			int result = alysTable[tokens[index]][top.second];
			if (result == 0) {// 出错
				productions.clear();
				return productions;
			}
			else if (result > 0);
			else if (result == -1) {// 冲突项手动处理
				if (tokens[index+1] == table1["="] || tokens[index+1] == table1["+="] || tokens[index+1] == table1["-="] || tokens[index+1] == table1["*="] || tokens[index+1] == table1["/="] || tokens[index+1] == table1["%="]) result = 27;
				else result = 28;
			}
			productions.push_back(pair<int, string>(result, table3[result]));
			string production = table3[result];// 获取产生式
			vector<string> temp = split(production, ' ');
			push_stack.pop();
			for (int i = temp.size() - 1; i > 1; i--) {
				map<string, int>::iterator iter1 = table1.find(temp[i]);
				map<string, int>::iterator iter2 = table2.find(temp[i]);
				if (iter1 != table1.end())push_stack.push(pair<bool, int>(true, iter1->second));
				if (iter2 != table2.end())push_stack.push(pair<bool, int>(false, iter2->second));
			}
		}
	}
}
vector<string> SynAlys::split(string source, char c) {
	vector<string> ss;
	string temp = "";
	for (int i = 0; i < source.size(); i++) {
		if (source[i] == c) {
			if (temp != "")ss.push_back(temp);
			temp = "";
		}
		else temp += source[i];
	}
	if(temp!="")ss.push_back(temp);
	return ss;
}