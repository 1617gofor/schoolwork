#include"student.h"
Student::Student() {
	this->calledcnt = 0;
	this->notComeCnt = 0;
}
Student::Student(int cln, string nm, string nme, int* st) {
	this->classnumber = cln;
	this->num = nm;
	this->name = nme;
	this->calledcnt = 0;
	this->notComeCnt = 0;
	for (int i = 0; i < 20; i++) {
		this->state[i] = st[i];
	}
}

//��ȡ������Ϣ
string Student::getName() {
	return this->name;
}
string Student::getNum() {
	return this->num;
}
int Student::getState(int courseN) {
	return this->state[courseN - 1];
}
int Student::getClassNumber() {
	return this->classnumber;
}
int Student::getCalledCnt() {
	return this->calledcnt;
}
int Student::getNotComeCnt() {
	return this->notComeCnt;
}
//�޸�state״̬
//void Student::setState(int courseN, int sta) {
//	this->state[courseN-1] = sta;
//
//}
//�޸ı��㵽�Ĵ���(��һ)
void Student::setCalledCnt() {
	this->calledcnt+=1;
}
//���ѧ��
void Student::setNum(string num) {
	this->num = num;
}
//��Ӱ༶
void Student::setClassNumber(int clanumb) {
	this->classnumber=clanumb;
}
//�������
void Student::setName(string name) {
	this->name = name;
}
//���״̬
void Student::setState(int* st) {
	for (int i = 0; i < 20; i++) {
		this->state[i] = st[i];
	}
}
//�޸�û������
void Student::setNotComeCnt() {
	this->notComeCnt+=1;
}
