#include<iostream>
#include"callroll.h"
using namespace std;
int main() {
	//�������������
	srand((unsigned int)time(NULL));
	Roll rol;
	rol.Init();//��������������зְ�
	//����
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
	cout << "����ɹ�" << endl;
	ofs.close();
	system("pause");
	return 0;
}