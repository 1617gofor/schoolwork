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
	void Callcl(int claAount, ofstream& ofs, int clnb);
	//���㵽ĿǰΪֹû�б��鵽��������
	int getNeverNotCalledCnt(vector<Student>& veClass);
	//�����й�ȱ��1�λ���2�ε�����
	int getNotComeCntOne(vector<Student>& veClass);
	//����ÿ�ε�����Eֵ
	double Calcu(int claAount);
	//�����ܵ�����Eֵ
	double Calcu1();
	
private:
	vector<Student> veClass[5];//�༶
	vector<Student*> notComeStu[5];
	vector<pair<int, int>> scheme[5];
};
