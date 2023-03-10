#include"LexAlys.h"
LexAlys::LexAlys(string fileName) {
	ifstream file;
	file.open(fileName, ios::in);
	if (!file.is_open())return;
	string token = "";
	int counter = 0;
	while (getline(file, token))
	{
		table[token] = counter;
		counter++;
	}
	file.close();
}
vector<int> LexAlys::generate(string fileName) {
	vector<int> tokens;
	bool isError = false;// 分析是否结束。这里的结束属于异常结束，即分析出错
	string temp = "";
	map<string, int>::iterator iter;
	file.open(fileName, ios::in);
	if (!file.is_open())return tokens;
	currChar = file.get();// 获取当前字符
	while (!isError)
	{
		if (currChar == '_' || (currChar >= 'a' && currChar <= 'z') || (currChar >= 'A' && currChar <= 'Z')) {
			temp = idAlys();
			iter = table.find(temp);
			if (iter != table.end() && iter->first != "id")tokens.push_back(iter->second);
			else tokens.push_back(table["id"]);
		}
		else if (currChar >= '0' && currChar <= '9') {
			temp = numberAlys();
			if (temp == "") {
				isError = true;
				tokens.clear(); tokens.push_back(-1);
			}
			else tokens.push_back(table["number"]);
		}
		else if (currChar == ' ' || currChar == '\t' || currChar == '\n') {
			temp = separatorAlys();
		}
		else if (currChar == '+' || currChar == '-' || currChar == '*' || currChar == '/' || currChar == '%' || currChar == '>' || currChar == '<' || currChar == '=' || currChar == '!') {
			temp = singleDoubleAlys("=", true);
			tokens.push_back(table[temp]);
		}
		else if (currChar == ',' || currChar == ';' || currChar == '(' || currChar == ')' || currChar == '{' || currChar == '}') {
			string tempChar = "";
			tempChar += currChar;
			currChar = file.get();
			tokens.push_back(table[tempChar]);
		}
		else if (currChar == '&' || currChar == '|') {
			string tempChar = "";
			tempChar += currChar;
			temp = singleDoubleAlys(tempChar,false);
			if (temp == "") {
				isError = true;
				tokens.clear(); tokens.push_back(-2);
			}
			else tokens.push_back(table[temp]);
		}
		else if (currChar == EOF)break;
		else {
			isError = true;
			tokens.clear(); tokens.push_back(-3);
		}
	}
	file.close();
	return tokens;
}
string LexAlys::idAlys() {
	string token = "";
	token += currChar;
	while (true)
	{
		currChar = file.get();
		if (currChar == '_' || (currChar >= 'a' && currChar <= 'z') || (currChar >= 'A' && currChar <= 'Z') || (currChar >= '0' && currChar <= '9')) token += currChar;
		else return token;
	}
}
string LexAlys::numberAlys() {
	string token = "";
	token += currChar;
	int state = 1;
	while (true)
	{
		currChar = file.get();
		switch (state)
		{
		case 1:
			if (currChar >= '0' && currChar <= '9')token += currChar;
			else if (currChar == '.') {
				token += currChar;
				state = 2;
			}
			else return token;
			break;
		case 2:
			if (currChar >= '0' && currChar <= '9') {
				token += currChar;
				state = 3;
			}
			else return "";
			break;
		case 3:
			if (currChar >= '0' && currChar <= '9') token += currChar;
			else return token;
			break;
		default:
			break;
		}
	}
}
string LexAlys::separatorAlys() {
	while (true)
	{
		currChar = file.get();
		if (currChar == ' ' || currChar == '\t' || currChar == '\n')continue;
		else return "";
	}
}
string LexAlys::singleDoubleAlys(string seconds,bool flag) {
	string token = "";
	token += currChar;
	int state = 1;
	bool isIn = false;
	while (true)
	{
		currChar = file.get();
		switch (state)
		{
		case 1:
			for (int i = 0; i < seconds.size(); i++)
				if (currChar == seconds[i])isIn = true;
			if (isIn) {
				token += currChar;
				state = 2;
			}
			else if (flag) return token;
			else return "";
			break;
		case 2:
			return token;
			break;
		default:
			break;
		}

	}
}