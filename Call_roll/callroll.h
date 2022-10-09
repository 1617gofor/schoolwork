#pragma once
#include<iostream>
#include"student.h"
#include<vector>
#include<algorithm>
#include<fstream>
using namespace std;
//点名系统类
class Roll {
public:
	Roll();
	//初始化班级，即把输入的数据分配给对应的班级
	void Init();
	//点名并且把点到的名单输出到文件
	void Callcl1(int claAount, ofstream& ofs, int clnb);
	void Callcl2(int claAount, ofstream& ofs, int clnb);
	void Callcl3(int claAount, ofstream& ofs, int clnb);
	void Callcl4(int claAount, ofstream& ofs, int clnb);
	void Callcl5(int claAount, ofstream& ofs, int clnb);


private:
	vector<Student> veClass1;
	vector<Student> veClass2;
	vector<Student> veClass3;
	vector<Student> veClass4;
	vector<Student> veClass5;
	vector<Student*> notComeStu[5];
};
