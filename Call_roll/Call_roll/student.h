#pragma once
#include<iostream>
#include<string>
using namespace std;
class Student {
public:
	Student();
	Student(int cln,string nm,string nme,int* st);
	//��ȡ������Ϣ
	string getName();
	string getNum();
	int getState(int courseN);
	int getClassNumber();
	int getCalledCnt();
	int getNotComeCnt();
	//�޸ı��㵽�Ĵ���(��һ)
	void setCalledCnt();
	//���ѧ��
	void setNum(string num);
	//��Ӱ༶
	void setClassNumber(int clanumb);
	//�������
	void setName(string name);
	//���״̬
	void setState(int* st);
	//�޸�û������
	void setNotComeCnt();
	//�޸�state״̬
	//void setState(int courseN, int sta);
private:
	string num;
	string name;
	int state[20];
	int classnumber;
	int calledcnt;//���㵽�Ĵ���
	int notComeCnt;//û������
};
