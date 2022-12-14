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
//获取个人信息
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
//修改state状态
void Student::setState(int courseN, int sta) {
	this->state[courseN-1] = sta;

}
//修改被点到的次数(加一)
void Student::setCalledCnt() {
	this->calledcnt++;
}
//添加学号
void Student::setNum(string num) {
	this->num = num;
}
//添加班级
void Student::setClassNumber(int clanumb) {
	this->classnumber=clanumb;
}
//添加姓名
void Student::setName(string name) {
	this->name = name;
}
//添加状态
void Student::setState(int* st) {
	for (int i = 0; i < 20; i++) {
		this->state[i] = st[i];
	}
}