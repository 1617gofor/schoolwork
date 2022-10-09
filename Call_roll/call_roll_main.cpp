#include<iostream>
#include"callroll.h"
using namespace std;
int main() {
	//加上随机数种子
	srand((unsigned int)time(NULL));
	Roll rol;
	rol.Init();//把输入的名单进行分班
	//测试
	int clCnt = 1;
	ofstream ofs;
	ofs.open("scheme.txt", ios::out | ios::trunc);
	while (clCnt<=20) {
		rol.Callcl1(clCnt,ofs,1);
		rol.Callcl2(clCnt, ofs, 2);
		rol.Callcl3(clCnt, ofs, 3);
		rol.Callcl4(clCnt, ofs, 4);
		rol.Callcl5(clCnt, ofs, 5);
		clCnt++;
	}
	cout << "保存成功" << endl;
	ofs.close();
	system("pause");
	return 0;
}