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
	void Callcl(int claAount, ofstream& ofs, int clnb);
	//计算到目前为止没有被抽到过的人数
	int getNeverNotCalledCnt(vector<Student>& veClass);
	//计算有过缺课1次或者2次的人数
	int getNotComeCntOne(vector<Student>& veClass);
	//计算每次点名的E值
	double Calcu(int claAount);
	//计算总的名的E值
	double Calcu1();
	
private:
	vector<Student> veClass[5];//班级
	vector<Student*> notComeStu[5];
	vector<pair<int, int>> scheme[5];
};
