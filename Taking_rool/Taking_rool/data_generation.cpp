#include"student.h"
#include<vector>
#include<fstream>
#include<algorithm>
using namespace std;
//���ɲ������ݲ����浽�ļ�
void DataG() {
	vector<string> veName;
	vector<Student>veStu;
	ifstream ifs;
	//д��Ӧ�������ļ�·��
	ifs.open("Name.txt", ios::in);
	if (ifs.is_open()) {
		char buf[1024] = { 0 };
		while (ifs>>buf) {
			veName.push_back((string)buf);
		}
	}
	ifs.close();
	int sum[5] = {0,0,0,0,0};
	int len = veName.size();
	int num0 = 101;
	int cnt1 = rand() % 7 + 5;
	int cnt2 = rand() % 7 + 5;
	int cnt3 = rand() % 7 + 5;
	int cnt4 = rand() % 7 + 5;
	int cnt5 = rand() % 7 + 5;
	int cnt[5] = { cnt1,cnt2,cnt3,cnt4,cnt5 };
	//cout << "δ������" << cnt << "��" << endl;
	//�����ַ�װ��ѧ�����󣬲��ҷ���ѧ������veStu��
	int clnumber = 1;
	for (int i = 0; i < 450; i++) {
		string num = "032006";
		int index = rand() % len;
		string name = veName[index];//���ȡһ������
		vector<string>::iterator it = veName.begin();
		int num1 = num0 + i;
		num += to_string(num1);//����ѧ��
		int state = 1;
		////cnt��ʾȱ�ε�����
		//if (cnt[clnumber-1])
		//{
		//	state = 0;
		//	cnt[clnumber-1]--;
		//}
		//����ÿ����ֻ��90��
		if (sum[clnumber-1] == 90) {
			clnumber++;
		}
		sum[clnumber-1]++;
		Student s(num, name, state, clnumber);
		veStu.push_back(s);
		it += index;
		veName.erase(it);
		len--;
	}
	//����state״̬
	int index = 0;
	for (int i = 1; i <= 5; i++){
		auto begin = veStu.begin() + 90 * (i - 1);
		auto end = veStu.begin() + 90 * i;
		random_shuffle(begin, end);//��ѧ����������ϴ�Ʋ���
		int badmenCount = rand() % 4 + 5;//��ѧ������
		int badmenCount2 = badmenCount;
		//��ÿ���༶״̬����
		for (; index < veStu.size(); index++) {
			//�ȷ��仵ѧ��
			if (badmenCount > 0) {
				for (int j = 1; j <= 20; j++) {
					veStu[index].setState(j, 0);
				}
				for (int badmanCnt = 0; badmanCnt < 4;) {
					int badmanIndex = rand() % 20 + 1;
					if (veStu[index].getState(badmanIndex) == 0) {
						veStu[index].setState(badmanIndex, 1);
						badmanCnt++;
					}
				}
				badmenCount--;
			}
			//ÿ�ογ�
			else {
				break;
			}
		}
		//ѡ��ÿ�ολ�����0-3��δ��ͬѧ
		for (int j = 1; j <= 20; j++) {
			int index2;
			int notComeN = rand() % 4;
			while (notComeN) {
				//ѡ��ÿ�ο�������ԭ��δ����ͬѧ
				int stuIndex = rand() % (90 - badmenCount2);
				index2 = index+stuIndex;
				if (veStu[index2].getState(j) == 1) {
					veStu[index2].setState(j, 0);
					notComeN--;
				}

			}
		}
		index = index-badmenCount2+90;

	}
	


	//����ѧ�������ļ�
	ofstream ofs;
	//д�༶�����ļ���ŵ�·��
	ofs.open("Name1.txt", ios::out | ios::trunc);
	vector<Student>::iterator it;
	for (it = veStu.begin(); it != veStu.end(); it++) {
		ofs << it->getClassNumber() << " " << it->getNum() << " "
			<< it->getName() << " ";
		for (int i = 0; i < 20; i++) {
			ofs << it->getState(i+1)<<" ";
		}
		ofs << endl;
	}
	ofs.close();
	cout << "�������ɳɹ�" << endl;
}

int main() {
	srand((unsigned int)time(NULL));
	DataG();
	system("pause");
	return 0;
}