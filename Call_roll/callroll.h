#pragma once
#include<iostream>
#include"student.h"
#include<vector>
#include<algorithm>
#include<fstream>
using namespace std;
//����ϵͳ��
class Roll {
public:
	Roll();
	//��ʼ���༶��������������ݷ������Ӧ�İ༶
	void Init();
	//�������Ұѵ㵽������������ļ�
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
