#include"student.h"
Student::Student() {
	this->calledcnt = 0;

}
Student::Student(string num, string name, int state, int clnumber) {
	this->num=num;
	this->name = name;
	this->classnumber = clnumber;
	for (int i = 0; i < 20; i++) {
		this->state[i] = state;
	}
	this->calledcnt = 0;
}
//��ȡ������Ϣ
string Student::getName() {
	return this->name;
}
string Student::getNum() {
	return this->num;
}
int Student::getState(int courseN) {
	return this->state[courseN-1];
}
int Student::getClassNumber() {
	return this->classnumber;
}
int Student::getCalledCnt() {
	return this->calledcnt;
}
//�޸�state״̬
void Student::setState(int courseN, int sta) {
	this->state[courseN-1] = sta;

}
//�޸ı��㵽�Ĵ���(��һ)
void Student::setCalledCnt() {
	this->calledcnt++;
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