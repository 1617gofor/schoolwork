#include<iostream>
#include"callroll.h"
using namespace std;
int main() {
	//�������������
	srand((unsigned int)time(NULL));
	//����
	double sum11 = 0.0;
	for (int i = 0; i < 100; i++) {
		Roll rol;
		rol.Init();//��������������зְ�
		ofstream ofs;
		ofs.open("../../schooldata/scheme.txt", ios::out | ios::trunc);
		int clCnt = 1;
		
		while (clCnt <= 20) {
			rol.Callcl(clCnt, ofs, 1);
			rol.Callcl(clCnt, ofs, 2);
			rol.Callcl(clCnt, ofs, 3);
			rol.Callcl(clCnt, ofs, 4);
			rol.Callcl(clCnt, ofs, 5);

			//cout << "��" << clCnt << "�ε� E= " << rol.Calcu(clCnt) << endl;
			clCnt++;
		}
		sum11 += rol.Calcu1();
		cout << "���� E = " << rol.Calcu1() << endl;
		//cout << "����ɹ�" << endl;
		ofs.close();
	}
	cout << sum11 / 100.0 << endl;
	system("pause");
	return 0;
}