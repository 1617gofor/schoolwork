#include<iostream>
#include"callroll.h"
using namespace std;
int main() {
	//�������������
	srand((unsigned int)time(NULL));
	//����
	double sum11 = 0.0;
	//��ѭ��������ѧ����
	for (int i = 0; i < 2; i++) {
		Roll rol;
		rol.Init();//��������������зְ�
		ofstream ofs;
		ofs.open("../../schooldata/scheme.txt", ios::out | ios::trunc);
		if (!ofs.is_open()) {
			cout << "main���ļ���ʧ��" << endl;
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

			cout << "��" << clCnt << "�ε� E= " << rol.Calcu(clCnt) << endl;
			clCnt++;
		}
		sum11 += rol.Calcu1();
		//cout << "���� E = " << rol.Calcu1() << endl;
		ofs.close();
		cout << "----------------------------------" << endl;
	}
	//cout << sum11 / 1.0 << endl;
	cout << "�����ѱ�����schooldata�ļ��е�scheme�ļ���" << endl;
	system("pause");
	return 0;
}