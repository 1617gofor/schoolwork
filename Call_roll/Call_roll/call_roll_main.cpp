#include<iostream>
#include"callroll.h"
using namespace std;
int main() {
	//�������������
	srand((unsigned int)time(NULL));
	//����
	double sum11 = 0.0;
	for (int i = 0; i < 1; i++) {
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
		//����--��һ�µ����ÿ����Ļ�ѧ���м���
		/*for (int j = 0; j < 5; j++) {
			for (int i = 0; i < rol.notComeStu[j].size(); i++) {
				cout << rol.notComeStu[j][i]->getName() << " ";
			}
			cout << endl;
		}*/
		sum11 += rol.Calcu1();
		//cout << "���� E = " << rol.Calcu1() << endl;
		//cout << "����ɹ�" << endl;
		ofs.close();
	}
	cout << sum11 / 1.0 << endl;
	system("pause");
	return 0;
}