#include<iostream>
#include<fstream>
#include"callroll.h"
using namespace std;
class Greater {
public:
	bool operator()( Student &s1,  Student &s2) {
		return s1.getNum() < s2.getNum();
	}
};
Roll::Roll() {

}
//��ʼ���༶��������������ݷ������Ӧ�İ༶
void Roll::Init() {
	ifstream ifs;
	ifs.open("Name1.txt", ios::in);
	if (!ifs.is_open()) {
		//�ļ���ʧ�ܸ�����ʾ
		cout << "�ļ���ʧ��" << endl;
		return;
	}
	int sum = 450;
	while (sum) {
		char classNumber[1024] = { 0 };
		char Num[1024] = { 0 };
		char Name[1024] = { 0 };
		ifs >> classNumber >> Num >> Name;

		string clN;
		clN = classNumber;
		int clN1 = atoi(clN.c_str());
		string Nm = (string)Num;
		string Nme = (string)Name;
		//��ȡ״̬
		int state1[20] = { 0 };
		for (int i = 0; i < 20; i++) {
			char st[1024] = { 0 };
			ifs >> st;
			string sta = (string)st;
			int sta1 = atoi(sta.c_str());
			state1[i] = sta1;
		}
		Student sd(clN1, Nm, Nme, state1);
		if (clN1 == 1) {
			this->veClass1.push_back(sd);
		}
		else if (clN1 == 2) {
			this->veClass2.push_back(sd);
		}
		else if (clN1 == 3) {
			this->veClass3.push_back(sd);
		}
		else if (clN1 == 4) {
			this->veClass4.push_back(sd);
		}
		else if (clN1 == 5) {
			this->veClass5.push_back(sd);
		}
		sum--;

	}
	ifs.close();
	//��ÿ������а���ѧ����������
	sort(veClass1.begin(), veClass1.end(), Greater());
	sort(veClass2.begin(), veClass2.end(), Greater());
	sort(veClass3.begin(), veClass3.end(), Greater());
	sort(veClass4.begin(), veClass4.end(), Greater());
	sort(veClass5.begin(), veClass5.end(), Greater());
	//*********************����
	/*for (Student s : this->veClass1) {
		cout << s.getClassNumber() << " " << s.getNum() << " "
			<< s.getName()<<" ";
		for (int i = 1; i <= 20; i++) {
			cout << s.getState(i) << " ";
		}
		cout << endl;
	}
	for (Student s : this->veClass2) {
		cout << s.getClassNumber() << " " << s.getNum() << " "
			<< s.getName() << " ";
		for (int i = 1; i <= 20; i++) {
			cout << s.getState(i) << " ";
		}
		cout << endl;
	}
	for (Student s : this->veClass3) {
		cout << s.getClassNumber() << " " << s.getNum() << " "
			<< s.getName() << " ";
		for (int i = 1; i <= 20; i++) {
			cout << s.getState(i) << " ";
		}
		cout << endl;
	}
	for (Student s : this->veClass4) {
		cout << s.getClassNumber() << " " << s.getNum() << " "
			<< s.getName() << " ";
		for (int i = 1; i <= 20; i++) {
			cout << s.getState(i) << " ";
		}
		cout << endl;
	}
	for (Student s : this->veClass5) {
		cout << s.getClassNumber() << " " << s.getNum() << " "
			<< s.getName() << " ";
		for (int i = 1; i <= 20; i++) {
			cout << s.getState(i) << " ";
		}
		cout << endl;
	}*/
}
//���ε������Ұѵ㵽������������ļ�
void Roll::Callcl1(int claAount, ofstream& ofs, int clnb) {
	int sum = 0;//��¼��Ч��������
	int callingCnt = 0;
	if (claAount <= 5) {
		//ǰ��ογ��45����	
		callingCnt = 45;
	}
	else {
		//��γ��30����	
		callingCnt = 25;
	}
	if (this->notComeStu[clnb-1].empty()) {
		//������Ϊ�գ��ʹ�ȫ���
		int rolled[90] = { 0 };//��������Ѿ�����һ�γ���е㵽����
		for (int i = 0; i < callingCnt;) {
			int index = rand() % 90;
			if (rolled[index] == 0) {
				//�޸ı��㵽����
				this->veClass1[index].setCalledCnt();
				int state = this->veClass1[index].getState(claAount);
				//���㵽������û����ͬѧ���м����������ͬʱ�޸�û������
				if (state == 0) {
					this->veClass1[index].setNotComeCnt();
					this->notComeStu[clnb-1].push_back(&(this->veClass1[index]));
					
					sum++;
				}
				rolled[index] = 1;
				i++;
			}
		}
	}
	else {
		//��������Ϊ�գ�һ���ִӺ������飬һ���ִӺ�����֮����˳�
		//��������
		for (int i = 0; i < this->notComeStu[clnb-1].size();i++) {
			//�޸ı������
			(this->notComeStu[clnb-1][i])->setCalledCnt();
			int state = (this->notComeStu[clnb-1][i])->getState(claAount);
			//���û�����޸�û������
			if (state == 0) {
				(this->notComeStu[clnb-1][i])->setNotComeCnt();
				sum++;
			}
		}
		for (int i = 0; i < callingCnt - (this->notComeStu[clnb-1].size());) {
			int index = rand() % 90;
			int flag = 0;//��Ǹ����Ƿ��ں�������
			for (Student* s : this->notComeStu[clnb-1]) {
				if (s->getNum().compare( this->veClass1[index].getNum())==0) {
					flag = 1;//˵��index������ں�������
					break;
				}
			}
			if (flag == 0) {
				//���ں�������
				//�޸ı������
				this->veClass1[index].setCalledCnt();
				int state = this->veClass1[index].getState(claAount);
				//���û���޸�û������,���Ҽ��������
				if (state == 0) {
					this->veClass1[index].setNotComeCnt();
					this->notComeStu[clnb-1].push_back(&(this->veClass1[index]));
					sum++;
				}
				i++;
			}
		}
	}
	if (claAount%5 ==0&&claAount<20 ) {
		if (!(this->notComeStu[clnb-1].empty())) {
			for (auto it = this->notComeStu[clnb-1].begin(); it != this->notComeStu[clnb-1].end();it++) {
				if ((*it)->getNotComeCnt()<3) {
					//û������С�����ε����Ƴ�������
					this->notComeStu[clnb-1].erase(it);
					it = this->notComeStu[clnb-1].begin();
				}
			}
		}	
	}
	//д���ļ�������
	ofs <<clnb<< "���" << claAount << "�γ�� ���" << callingCnt << "�� δ��" << sum << "��" << endl;

}
void Roll::Callcl2(int claAount, ofstream& ofs, int clnb) {
	int sum = 0;//��¼��Ч��������
	int callingCnt = 0;
	if (claAount <= 5) {
		//ǰ��ογ��45����	
		callingCnt = 45;
	}
	else {
		//��γ��30����	
		callingCnt = 25;
	}
	if (this->notComeStu[clnb-1].empty()) {
		//������Ϊ�գ��ʹ�ȫ���
		int rolled[90] = { 0 };//��������Ѿ�����һ�γ���е㵽����
		for (int i = 0; i < callingCnt;) {
			int index = rand() % 90;
			if (rolled[index] == 0) {
				//�޸ı��㵽����
				this->veClass2[index].setCalledCnt();
				int state = this->veClass2[index].getState(claAount);
				//���㵽������û����ͬѧ���м����������ͬʱ�޸�û������
				if (state == 0) {
					this->veClass2[index].setNotComeCnt();
					this->notComeStu[clnb-1].push_back(&(this->veClass2[index]));

					sum++;
				}
				rolled[index] = 1;
				i++;
			}
		}
	}
	else {
		//��������Ϊ�գ�һ���ִӺ������飬һ���ִӺ�����֮����˳�
		//��������
		for (int i = 0; i < this->notComeStu[clnb-1].size(); i++) {
			//�޸ı������
			(this->notComeStu[clnb-1][i])->setCalledCnt();
			int state = (this->notComeStu[clnb-1][i])->getState(claAount);
			//���û�����޸�û������
			if (state == 0) {
				(this->notComeStu[clnb-1][i])->setNotComeCnt();
				sum++;
			}
		}
		for (int i = 0; i < callingCnt - (this->notComeStu[clnb-1].size());) {
			int index = rand() % 90;
			int flag = 0;//��Ǹ����Ƿ��ں�������
			for (Student* s : this->notComeStu[clnb-1]) {
				if (s->getNum().compare(this->veClass2[index].getNum()) == 0) {
					flag = 1;//˵��index������ں�������
					break;
				}
			}
			if (flag == 0) {
				//���ں�������
				//�޸ı������
				this->veClass2[index].setCalledCnt();
				int state = this->veClass2[index].getState(claAount);
				//���û���޸�û������,���Ҽ��������
				if (state == 0) {
					this->veClass2[index].setNotComeCnt();
					this->notComeStu[clnb-1].push_back(&(this->veClass2[index]));
					sum++;
				}
				i++;
			}
		}
	}
	if (claAount % 5 == 0 && claAount < 20) {
		if (!(this->notComeStu[clnb-1].empty())) {
			for (auto it = this->notComeStu[clnb-1].begin(); it != this->notComeStu[clnb-1].end(); it++) {
				if ((*it)->getNotComeCnt() < 3) {
					//û������С�����ε����Ƴ�������
					this->notComeStu[clnb-1].erase(it);
					it = this->notComeStu[clnb-1].begin();
				}
			}
		}
	}
	//д���ļ�������
	ofs << clnb << "���" << claAount << "�γ�� ���" << callingCnt << "�� δ��" << sum << "��" << endl;
}
void Roll::Callcl3(int claAount, ofstream& ofs, int clnb) {
	int sum = 0;//��¼��Ч��������
	int callingCnt = 0;
	if (claAount <= 5) {
		//ǰ��ογ��45����	
		callingCnt = 45;
	}
	else {
		//��γ��30����	
		callingCnt = 25;
	}
	if (this->notComeStu[clnb-1].empty()) {
		//������Ϊ�գ��ʹ�ȫ���
		int rolled[90] = { 0 };//��������Ѿ�����һ�γ���е㵽����
		for (int i = 0; i < callingCnt;) {
			int index = rand() % 90;
			if (rolled[index] == 0) {
				//�޸ı��㵽����
				this->veClass3[index].setCalledCnt();
				int state = this->veClass3[index].getState(claAount);
				//���㵽������û����ͬѧ���м����������ͬʱ�޸�û������
				if (state == 0) {
					this->veClass3[index].setNotComeCnt();
					this->notComeStu[clnb-1].push_back(&(this->veClass3[index]));

					sum++;
				}
				rolled[index] = 1;
				i++;
			}
		}
	}
	else {
		//��������Ϊ�գ�һ���ִӺ������飬һ���ִӺ�����֮����˳�
		//��������
		for (int i = 0; i < this->notComeStu[clnb-1].size(); i++) {
			//�޸ı������
			(this->notComeStu[clnb-1][i])->setCalledCnt();
			int state = (this->notComeStu[clnb-1][i])->getState(claAount);
			//���û�����޸�û������
			if (state == 0) {
				(this->notComeStu[clnb-1][i])->setNotComeCnt();
				sum++;
			}
		}
		for (int i = 0; i < callingCnt - (this->notComeStu[clnb-1].size());) {
			int index = rand() % 90;
			int flag = 0;//��Ǹ����Ƿ��ں�������
			for (Student* s : this->notComeStu[clnb-1]) {
				if (s->getNum().compare(this->veClass3[index].getNum()) == 0) {
					flag = 1;//˵��index������ں�������
					break;
				}
			}
			if (flag == 0) {
				//���ں�������
				//�޸ı������
				this->veClass3[index].setCalledCnt();
				int state = this->veClass3[index].getState(claAount);
				//���û���޸�û������,���Ҽ��������
				if (state == 0) {
					this->veClass3[index].setNotComeCnt();
					this->notComeStu[clnb-1].push_back(&(this->veClass3[index]));
					sum++;
				}
				i++;
			}
		}
	}
	if (claAount % 5 == 0 && claAount < 20) {
		if (!(this->notComeStu[clnb-1].empty())) {
			for (auto it = this->notComeStu[clnb-1].begin(); it != this->notComeStu[clnb-1].end(); it++) {
				if ((*it)->getNotComeCnt() < 3) {
					//û������С�����ε����Ƴ�������
					this->notComeStu[clnb-1].erase(it);
					it = this->notComeStu[clnb-1].begin();
				}
			}
		}
	}
	//д���ļ�������
	ofs << clnb << "���" << claAount << "�γ�� ���" << callingCnt << "�� δ��" << sum << "��" << endl;
}
void Roll::Callcl4(int claAount, ofstream& ofs, int clnb) {
	int sum = 0;//��¼��Ч��������
	int callingCnt = 0;
	if (claAount <= 5) {
		//ǰ��ογ��45����	
		callingCnt = 45;
	}
	else {
		//��γ��30����	
		callingCnt = 25;
	}
	if (this->notComeStu[clnb-1].empty()) {
		//������Ϊ�գ��ʹ�ȫ���
		int rolled[90] = { 0 };//��������Ѿ�����һ�γ���е㵽����
		for (int i = 0; i < callingCnt;) {
			int index = rand() % 90;
			if (rolled[index] == 0) {
				//�޸ı��㵽����
				this->veClass4[index].setCalledCnt();
				int state = this->veClass4[index].getState(claAount);
				//���㵽������û����ͬѧ���м����������ͬʱ�޸�û������
				if (state == 0) {
					this->veClass4[index].setNotComeCnt();
					this->notComeStu[clnb-1].push_back(&(this->veClass4[index]));

					sum++;
				}
				rolled[index] = 1;
				i++;
			}
		}
	}
	else {
		//��������Ϊ�գ�һ���ִӺ������飬һ���ִӺ�����֮����˳�
		//��������
		for (int i = 0; i < this->notComeStu[clnb-1].size(); i++) {
			//�޸ı������
			(this->notComeStu[clnb-1][i])->setCalledCnt();
			int state = (this->notComeStu[clnb-1][i])->getState(claAount);
			//���û�����޸�û������
			if (state == 0) {
				(this->notComeStu[clnb-1][i])->setNotComeCnt();
				sum++;
			}
		}
		for (int i = 0; i < callingCnt - (this->notComeStu[clnb-1].size());) {
			int index = rand() % 90;
			int flag = 0;//��Ǹ����Ƿ��ں�������
			for (Student* s : this->notComeStu[clnb-1]) {
				if (s->getNum().compare(this->veClass4[index].getNum()) == 0) {
					flag = 1;//˵��index������ں�������
					break;
				}
			}
			if (flag == 0) {
				//���ں�������
				//�޸ı������
				this->veClass4[index].setCalledCnt();
				int state = this->veClass4[index].getState(claAount);
				//���û���޸�û������,���Ҽ��������
				if (state == 0) {
					this->veClass4[index].setNotComeCnt();
					this->notComeStu[clnb-1].push_back(&(this->veClass4[index]));
					sum++;
				}
				i++;
			}
		}
	}
	if (claAount % 5 == 0 && claAount < 20) {
		if (!(this->notComeStu[clnb-1].empty())) {
			for (auto it = this->notComeStu[clnb-1].begin(); it != this->notComeStu[clnb-1].end(); it++) {
				if ((*it)->getNotComeCnt() < 3) {
					//û������С�����ε����Ƴ�������
					this->notComeStu[clnb-1].erase(it);
					it = this->notComeStu[clnb-1].begin();
				}
			}
		}
	}
	//д���ļ�������
	ofs << clnb << "���" << claAount << "�γ�� ���" << callingCnt << "�� δ��" << sum << "��" << endl;
}
void Roll::Callcl5(int claAount, ofstream& ofs, int clnb) {
	int sum = 0;//��¼��Ч��������
	int callingCnt = 0;
	if (claAount <= 5) {
		//ǰ��ογ��45����	
		callingCnt = 45;
	}
	else {
		//��γ��30����	
		callingCnt = 25;
	}
	if (this->notComeStu[clnb-1].empty()) {
		//������Ϊ�գ��ʹ�ȫ���
		int rolled[90] = { 0 };//��������Ѿ�����һ�γ���е㵽����
		for (int i = 0; i < callingCnt;) {
			int index = rand() % 90;
			if (rolled[index] == 0) {
				//�޸ı��㵽����
				this->veClass5[index].setCalledCnt();
				int state = this->veClass5[index].getState(claAount);
				//���㵽������û����ͬѧ���м����������ͬʱ�޸�û������
				if (state == 0) {
					this->veClass5[index].setNotComeCnt();
					this->notComeStu[clnb-1].push_back(&(this->veClass5[index]));

					sum++;
				}
				rolled[index] = 1;
				i++;
			}
		}
	}
	else {
		//��������Ϊ�գ�һ���ִӺ������飬һ���ִӺ�����֮����˳�
		//��������
		for (int i = 0; i < this->notComeStu[clnb-1].size(); i++) {
			//�޸ı������
			(this->notComeStu[clnb-1][i])->setCalledCnt();
			int state = (this->notComeStu[clnb-1][i])->getState(claAount);
			//���û�����޸�û������
			if (state == 0) {
				(this->notComeStu[clnb-1][i])->setNotComeCnt();
				sum++;
			}
		}
		for (int i = 0; i < callingCnt - (this->notComeStu[clnb-1].size());) {
			int index = rand() % 90;
			int flag = 0;//��Ǹ����Ƿ��ں�������
			for (Student* s : this->notComeStu[clnb-1]) {
				if (s->getNum().compare(this->veClass5[index].getNum()) == 0) {
					flag = 1;//˵��index������ں�������
					break;
				}
			}
			if (flag == 0) {
				//���ں�������
				//�޸ı������
				this->veClass5[index].setCalledCnt();
				int state = this->veClass5[index].getState(claAount);
				//���û���޸�û������,���Ҽ��������
				if (state == 0) {
					this->veClass5[index].setNotComeCnt();
					this->notComeStu[clnb-1].push_back(&(this->veClass5[index]));
					sum++;
				}
				i++;
			}
		}
	}
	if (claAount % 5 == 0 && claAount < 20) {
		if (!(this->notComeStu[clnb-1].empty())) {
			for (auto it = this->notComeStu[clnb-1].begin(); it != this->notComeStu[clnb-1].end(); it++) {
				if ((*it)->getNotComeCnt() < 3) {
					//û������С�����ε����Ƴ�������
					this->notComeStu[clnb-1].erase(it);
					it = this->notComeStu[clnb-1].begin();
				}
			}
		}
	}
	//д���ļ�������
	ofs << clnb << "���" << claAount << "�γ�� ���" << callingCnt << "�� δ��" << sum << "��" << endl;
}