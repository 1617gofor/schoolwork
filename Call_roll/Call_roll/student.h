#pragma once
#include<iostream>
#include<string>
using namespace std;
class Student {
public:
	Student();
	Student(int cln,string nm,string nme,int* st);
	//获取个人信息
	string getName();
	string getNum();
	int getState(int courseN);
	int getClassNumber();
	int getCalledCnt();
	int getNotComeCnt();
	//修改被点到的次数(加一)
	void setCalledCnt();
	//添加学号
	void setNum(string num);
	//添加班级
	void setClassNumber(int clanumb);
	//添加姓名
	void setName(string name);
	//添加状态
	void setState(int* st);
	//修改没来次数
	void setNotComeCnt();
	//修改state状态
	//void setState(int courseN, int sta);
private:
	string num;
	string name;
	int state[20];
	int classnumber;
	int calledcnt;//被点到的次数
	int notComeCnt;//没来次数
};
