#include<iostream>
#include"callroll.h"
using namespace std;
int main() {
	//加上随机数种子
	srand((unsigned int)time(NULL));
	//测试
	double sum11 = 0.0;
	//次循环可设置学期数
	for (int i = 0; i < 2; i++) {
		Roll rol;
		rol.Init();//把输入的名单进行分班
		ofstream ofs;
		ofs.open("../../schooldata/scheme.txt", ios::out | ios::trunc);
		if (!ofs.is_open()) {
			cout << "main中文件打开失败" << endl;
			return 0;
		}
		int clCnt = 1;
		
		while (clCnt <= 20) {
			rol.Callcl(clCnt, ofs, 1);
			rol.Callcl(clCnt, ofs, 2);
			rol.Callcl(clCnt, ofs, 3);
			rol.Callcl(clCnt, ofs, 4);
			rol.Callcl(clCnt, ofs, 5);
			ofs << "-----------------------------------" << endl;

			cout << "第" << clCnt << "次的 E= " << rol.Calcu(clCnt) << endl;
			clCnt++;
		}
		sum11 += rol.Calcu1();
		//cout << "总体 E = " << rol.Calcu1() << endl;
		ofs.close();
		cout << "----------------------------------" << endl;
	}
	//cout << sum11 / 1.0 << endl;
	cout << "方案已保存至schooldata文件夹的scheme文件中" << endl;
	system("pause");
	return 0;
}