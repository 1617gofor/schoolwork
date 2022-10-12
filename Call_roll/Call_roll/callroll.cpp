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
	ifs.open("../../schooldata/Name1.txt", ios::in);
	if (!ifs.is_open()) {
		//�ļ���ʧ�ܸ�����ʾ
		cout << "Init���ļ���ʧ��" << endl;
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
			this->veClass[0].push_back(sd);
		}
		else if (clN1 == 2) {
			this->veClass[1].push_back(sd);
		}
		else if (clN1 == 3) {
			this->veClass[2].push_back(sd);
		}
		else if (clN1 == 4) {
			this->veClass[3].push_back(sd);
		}
		else if (clN1 == 5) {
			this->veClass[4].push_back(sd);
		}
		sum--;

	}
	ifs.close();
	//��ÿ������а���ѧ����������
	sort(veClass[0].begin(), veClass[0].end(), Greater());
	sort(veClass[1].begin(), veClass[1].end(), Greater());
	sort(veClass[2].begin(), veClass[2].end(), Greater());
	sort(veClass[3].begin(), veClass[3].end(), Greater());
	sort(veClass[4].begin(), veClass[4].end(), Greater());
	//*********************����
	/*for (Student s : this->veClass[0]) {
		cout << s.getClassNumber() << " " << s.getNum() << " "
			<< s.getName()<<" ";
		for (int i = 1; i <= 20; i++) {
			cout << s.getState(i) << " ";
		}
		cout << endl;
	}
	for (Student s : this->veClass[1]) {
		cout << s.getClassNumber() << " " << s.getNum() << " "
			<< s.getName() << " ";
		for (int i = 1; i <= 20; i++) {
			cout << s.getState(i) << " ";
		}
		cout << endl;
	}
	for (Student s : this->veClass[2]) {
		cout << s.getClassNumber() << " " << s.getNum() << " "
			<< s.getName() << " ";
		for (int i = 1; i <= 20; i++) {
			cout << s.getState(i) << " ";
		}
		cout << endl;
	}
	for (Student s : this->veClass[3]) {
		cout << s.getClassNumber() << " " << s.getNum() << " "
			<< s.getName() << " ";
		for (int i = 1; i <= 20; i++) {
			cout << s.getState(i) << " ";
		}
		cout << endl;
	}
	for (Student s : this->veClass[4]) {
		cout << s.getClassNumber() << " " << s.getNum() << " "
			<< s.getName() << " ";
		for (int i = 1; i <= 20; i++) {
			cout << s.getState(i) << " ";
		}
		cout << endl;
	}*/
}
//���ε������Ұѵ㵽������������ļ�
void Roll::Callcl(int claAount, ofstream& ofs, int clnb) {
	int sum = 0;//��¼��Ч��������
	int callingCnt = 0;
	if (claAount <= 3) {
		//ǰ3�ογ��n����	
		if (claAount == 1)
			callingCnt =60;
		else if (claAount == 2) 
			callingCnt = this->notComeStu[clnb - 1].size()+10;
		else 
			callingCnt = this->notComeStu[clnb - 1].size()+5;
	}
	else {	
		callingCnt = this->notComeStu[clnb-1].size();
	}
	if (this->notComeStu[clnb-1].empty()) {
		//������Ϊ�գ��ʹ�ȫ���
		int rolled[90] = { 0 };//��������Ѿ�����һ�γ���е㵽����
		for (int i = 0; i < callingCnt;) {
			int index = rand() % 90;
			if (rolled[index] == 0) {
				//�޸ı��㵽����
				this->veClass[clnb-1][index].setCalledCnt();
				int state = this->veClass[clnb-1][index].getState(claAount);
				//���㵽������û����ͬѧ���м����������ͬʱ�޸�û������
				if (state == 0) {
					this->veClass[clnb-1][index].setNotComeCnt();
					this->notComeStu[clnb-1].push_back(&(this->veClass[clnb-1][index]));
					
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
		int ncsize = this->notComeStu[clnb - 1].size();
		if (claAount <= 3) {
			//���������ֳ�
			int ar = ncsize * 2 / 3;
			for (int i = 0; i <= ar; i++) {
				//�޸ı������
				int index = rand() % ncsize;
				this->notComeStu[clnb - 1][index]->setCalledCnt();
				int state = (this->notComeStu[clnb - 1][index])->getState(claAount);
				//���û�����޸�û������
				if (state == 0) {
					(this->notComeStu[clnb - 1][index])->setNotComeCnt();
					sum++;
				}
			}
		}
		else {
			for (int i = 0; i < this->notComeStu[clnb - 1].size(); i++) {
				//�޸ı������
				this->notComeStu[clnb - 1][i]->setCalledCnt();
				int state = (this->notComeStu[clnb - 1][i])->getState(claAount);
				//���û�����޸�û������
				if (state == 0) {
					(this->notComeStu[clnb - 1][i])->setNotComeCnt();
					sum++;
				}
			}
		}
		//�ڵ�2��֮������ȳ�δ���鵽��
		int sumCal = callingCnt - (this->notComeStu[clnb - 1].size());//�����������
		int sumNotNeverCalled = this->getNeverNotCalledCnt(this->veClass[clnb - 1]);//û�����������
		if (sumNotNeverCalled > 0) {
			//ֻҪ�д���û�б������ѧ����Ҫ���ȵ�
			int minI = sumCal;
			if (sumNotNeverCalled < sumCal) {
				minI = sumNotNeverCalled;
			}
			int rooled[90] = { 0 };
			for (int i = 0; i < minI;) {
				int index = rand() % 90;
				if (this->veClass[clnb - 1][index].getCalledCnt() == 0) {
					//���ѧ��û�б����,�����Ƴ����ѧ���϶����Ǻ�������
					//�����ѧ�����޸ı������
					this->veClass[clnb - 1][index].setCalledCnt();
					int state = this->veClass[clnb - 1][index].getState(claAount);
					rooled[index] = 1;
					if (state == 0) {
						//���㵽������û������Ҫ���������
						sum++;//��Ч������һ
						this->veClass[clnb - 1][index].setNotComeCnt();
						this->notComeStu[clnb - 1].push_back(&(this->veClass[clnb - 1][index]));
					}
					i++;
					sumCal--;
				}
			}
			//�������û�б������ѧ����û�й��������ͼ����������ķǺ�������
			while (sumCal>0) {
				int index = rand() % 90;
				int flag = 0;//��Ǹ����Ƿ��ں�������
				for (Student* s : this->notComeStu[clnb - 1]) {
					if (s->getNum().compare(this->veClass[clnb - 1][index].getNum()) == 0) {
						flag = 1;//˵��index������ں�������
						break;
					}
				}
				if (flag == 0&&rooled[index]==0) {
					//���ں������в��Ҹո�û�б����
					//�޸ı������
					rooled[index] = 1;
					this->veClass[clnb - 1][index].setCalledCnt();
					int state = this->veClass[clnb - 1][index].getState(claAount);
					//���û���޸�û������,���Ҽ��������
					if (state == 0) {
						this->veClass[clnb - 1][index].setNotComeCnt();
						this->notComeStu[clnb - 1].push_back(&(this->veClass[clnb - 1][index]));
						sum++;
					}
					sumCal--;
				}
			}

		}
		else {
			//����ѧ�����Ѿ����������һ����
			int rooled[90] = { 0 };
			int sumCal1 = this->getNotComeCntOne(this->veClass[clnb - 1]);
			if (sumCal1 > 0) {
				//���ȵ���ǰ�й�ȱ�μ�¼����
				int index = 0;
				while (sumCal > 0) {
					int flag = 0;//��Ǹ����Ƿ��ں�������
					for (Student* s : this->notComeStu[clnb - 1]) {
						if (s->getNum().compare(this->veClass[clnb - 1][index].getNum()) == 0) {
							flag = 1;//˵��index������ں�������
							break;
						}
					}
					if (flag == 0 && rooled[index] == 0 && (this->veClass[clnb - 1][index].getNotComeCnt() == 1)) {
						//���ں������в��Ҹո�û�б���������й�ȱ�μ�¼��
						//�޸ı������
						this->veClass[clnb - 1][index].setCalledCnt();
						int state = this->veClass[clnb - 1][index].getState(claAount);
						rooled[index] = 1;
						//���û���޸�û������,���Ҽ��������
						if (state == 0) {
							this->veClass[clnb - 1][index].setNotComeCnt();
							this->notComeStu[clnb - 1].push_back(&(this->veClass[clnb - 1][index]));
							sum++;
						}
						sumCal--;
						sumCal1--;
					}
					if (sumCal == 0) {
						break;
					}
					index++;
					if (index == 90) {
						break;
					}
				}
			}
			while (sumCal>0) {
				//����������
				int index = rand() % 90;
				int flag = 0;//��Ǹ����Ƿ��ں�������
				for (Student* s : this->notComeStu[clnb - 1]) {
					if (s->getNum().compare(this->veClass[clnb - 1][index].getNum()) == 0) {
						flag = 1;//˵��index������ں�������
						break;
					}
				}
				if (flag == 0 && rooled[index] == 0) {
					//���ں������в��Ҹո�û�б����
					//�޸ı������
					this->veClass[clnb - 1][index].setCalledCnt();
					int state = this->veClass[clnb - 1][index].getState(claAount);
					rooled[index] = 1;
					//���û���޸�û������,���Ҽ��������
					if (state == 0) {
						this->veClass[clnb - 1][index].setNotComeCnt();
						this->notComeStu[clnb - 1].push_back(&(this->veClass[clnb - 1][index]));
						sum++;
					}
					sumCal--;
				}
			}		
		}
		
	}
	if (claAount==4 ) {
		if (!(this->notComeStu[clnb-1].empty())) {
			for (auto it = this->notComeStu[clnb-1].begin(); it != this->notComeStu[clnb-1].end();) {
				if (((*it)->getNotComeCnt()<=1)) {
					//û������С��2�ε����Ƴ�������
					it=this->notComeStu[clnb-1].erase(it);
					
				}
				else {
					++it;
				}
			}
		}	
	}
	//��������������Ч��������
	pair<int, int> p = make_pair(callingCnt, sum);
	this->scheme[clnb-1].push_back(p);
	//д���ļ�������
	ofs <<clnb<< "���" << claAount << "�γ�� ���" << callingCnt << "�� δ��" << sum << "��" << endl;


}
//void Roll::Callcl2(int claAount, ofstream& ofs, int clnb) {
//	int sum = 0;//��¼��Ч��������
//	int callingCnt = 0;
//	if (claAount <= 5) {
//		//ǰ��ογ��45����	
//		callingCnt = 45;
//	}
//	else {
//		//��γ��30����	
//		callingCnt = 25;
//	}
//	if (this->notComeStu[clnb-1].empty()) {
//		//������Ϊ�գ��ʹ�ȫ���
//		int rolled[90] = { 0 };//��������Ѿ�����һ�γ���е㵽����
//		for (int i = 0; i < callingCnt;) {
//			int index = rand() % 90;
//			if (rolled[index] == 0) {
//				//�޸ı��㵽����
//				this->veClass2[index].setCalledCnt();
//				int state = this->veClass2[index].getState(claAount);
//				//���㵽������û����ͬѧ���м����������ͬʱ�޸�û������
//				if (state == 0) {
//					this->veClass2[index].setNotComeCnt();
//					this->notComeStu[clnb-1].push_back(&(this->veClass2[index]));
//
//					sum++;
//				}
//				rolled[index] = 1;
//				i++;
//			}
//		}
//	}
//	else {
//		//��������Ϊ�գ�һ���ִӺ������飬һ���ִӺ�����֮����˳�
//		//��������
//		for (int i = 0; i < this->notComeStu[clnb-1].size(); i++) {
//			//�޸ı������
//			(this->notComeStu[clnb-1][i])->setCalledCnt();
//			int state = (this->notComeStu[clnb-1][i])->getState(claAount);
//			//���û�����޸�û������
//			if (state == 0) {
//				(this->notComeStu[clnb-1][i])->setNotComeCnt();
//				sum++;
//			}
//		}
//		for (int i = 0; i < callingCnt - (this->notComeStu[clnb-1].size());) {
//			int index = rand() % 90;
//			int flag = 0;//��Ǹ����Ƿ��ں�������
//			for (Student* s : this->notComeStu[clnb-1]) {
//				if (s->getNum().compare(this->veClass2[index].getNum()) == 0) {
//					flag = 1;//˵��index������ں�������
//					break;
//				}
//			}
//			if (flag == 0) {
//				//���ں�������
//				//�޸ı������
//				this->veClass2[index].setCalledCnt();
//				int state = this->veClass2[index].getState(claAount);
//				//���û���޸�û������,���Ҽ��������
//				if (state == 0) {
//					this->veClass2[index].setNotComeCnt();
//					this->notComeStu[clnb-1].push_back(&(this->veClass2[index]));
//					sum++;
//				}
//				i++;
//			}
//		}
//	}
//	if (claAount % 8 == 0 && claAount < 20) {
//		if (!(this->notComeStu[clnb-1].empty())) {
//			for (auto it = this->notComeStu[clnb-1].begin(); it != this->notComeStu[clnb-1].end(); it++) {
//				if ((*it)->getNotComeCnt() < 3) {
//					//û������С�����ε����Ƴ�������
//					this->notComeStu[clnb-1].erase(it);
//					it = this->notComeStu[clnb-1].begin();
//				}
//			}
//		}
//	}
//	//��������������Ч��������
//	pair<int, int> p = make_pair(callingCnt, sum);
//	this->scheme[clnb - 1].push_back(p);
//	//д���ļ�������
//	ofs << clnb << "���" << claAount << "�γ�� ���" << callingCnt << "�� δ��" << sum << "��" << endl;
//}
//void Roll::Callcl3(int claAount, ofstream& ofs, int clnb) {
//	int sum = 0;//��¼��Ч��������
//	int callingCnt = 0;
//	if (claAount <= 5) {
//		//ǰ��ογ��45����	
//		callingCnt = 45;
//	}
//	else {
//		//��γ��30����	
//		callingCnt = 25;
//	}
//	if (this->notComeStu[clnb-1].empty()) {
//		//������Ϊ�գ��ʹ�ȫ���
//		int rolled[90] = { 0 };//��������Ѿ�����һ�γ���е㵽����
//		for (int i = 0; i < callingCnt;) {
//			int index = rand() % 90;
//			if (rolled[index] == 0) {
//				//�޸ı��㵽����
//				this->veClass3[index].setCalledCnt();
//				int state = this->veClass3[index].getState(claAount);
//				//���㵽������û����ͬѧ���м����������ͬʱ�޸�û������
//				if (state == 0) {
//					this->veClass3[index].setNotComeCnt();
//					this->notComeStu[clnb-1].push_back(&(this->veClass3[index]));
//
//					sum++;
//				}
//				rolled[index] = 1;
//				i++;
//			}
//		}
//	}
//	else {
//		//��������Ϊ�գ�һ���ִӺ������飬һ���ִӺ�����֮����˳�
//		//��������
//		for (int i = 0; i < this->notComeStu[clnb-1].size(); i++) {
//			//�޸ı������
//			(this->notComeStu[clnb-1][i])->setCalledCnt();
//			int state = (this->notComeStu[clnb-1][i])->getState(claAount);
//			//���û�����޸�û������
//			if (state == 0) {
//				(this->notComeStu[clnb-1][i])->setNotComeCnt();
//				sum++;
//			}
//		}
//		for (int i = 0; i < callingCnt - (this->notComeStu[clnb-1].size());) {
//			int index = rand() % 90;
//			int flag = 0;//��Ǹ����Ƿ��ں�������
//			for (Student* s : this->notComeStu[clnb-1]) {
//				if (s->getNum().compare(this->veClass3[index].getNum()) == 0) {
//					flag = 1;//˵��index������ں�������
//					break;
//				}
//			}
//			if (flag == 0) {
//				//���ں�������
//				//�޸ı������
//				this->veClass3[index].setCalledCnt();
//				int state = this->veClass3[index].getState(claAount);
//				//���û���޸�û������,���Ҽ��������
//				if (state == 0) {
//					this->veClass3[index].setNotComeCnt();
//					this->notComeStu[clnb-1].push_back(&(this->veClass3[index]));
//					sum++;
//				}
//				i++;
//			}
//		}
//	}
//	if (claAount % 8 == 0 && claAount < 20) {
//		if (!(this->notComeStu[clnb-1].empty())) {
//			for (auto it = this->notComeStu[clnb-1].begin(); it != this->notComeStu[clnb-1].end(); it++) {
//				if ((*it)->getNotComeCnt() < 3) {
//					//û������С�����ε����Ƴ�������
//					this->notComeStu[clnb-1].erase(it);
//					it = this->notComeStu[clnb-1].begin();
//				}
//			}
//		}
//	}
//	//��������������Ч��������
//	pair<int, int> p = make_pair(callingCnt, sum);
//	this->scheme[clnb - 1].push_back(p);
//	//д���ļ�������
//	ofs << clnb << "���" << claAount << "�γ�� ���" << callingCnt << "�� δ��" << sum << "��" << endl;
//}
//void Roll::Callcl4(int claAount, ofstream& ofs, int clnb) {
//	int sum = 0;//��¼��Ч��������
//	int callingCnt = 0;
//	if (claAount <= 5) {
//		//ǰ��ογ��45����	
//		callingCnt = 45;
//	}
//	else {
//		//��γ��30����	
//		callingCnt = 25;
//	}
//	if (this->notComeStu[clnb-1].empty()) {
//		//������Ϊ�գ��ʹ�ȫ���
//		int rolled[90] = { 0 };//��������Ѿ�����һ�γ���е㵽����
//		for (int i = 0; i < callingCnt;) {
//			int index = rand() % 90;
//			if (rolled[index] == 0) {
//				//�޸ı��㵽����
//				this->veClass4[index].setCalledCnt();
//				int state = this->veClass4[index].getState(claAount);
//				//���㵽������û����ͬѧ���м����������ͬʱ�޸�û������
//				if (state == 0) {
//					this->veClass4[index].setNotComeCnt();
//					this->notComeStu[clnb-1].push_back(&(this->veClass4[index]));
//
//					sum++;
//				}
//				rolled[index] = 1;
//				i++;
//			}
//		}
//	}
//	else {
//		//��������Ϊ�գ�һ���ִӺ������飬һ���ִӺ�����֮����˳�
//		//��������
//		for (int i = 0; i < this->notComeStu[clnb-1].size(); i++) {
//			//�޸ı������
//			(this->notComeStu[clnb-1][i])->setCalledCnt();
//			int state = (this->notComeStu[clnb-1][i])->getState(claAount);
//			//���û�����޸�û������
//			if (state == 0) {
//				(this->notComeStu[clnb-1][i])->setNotComeCnt();
//				sum++;
//			}
//		}
//		for (int i = 0; i < callingCnt - (this->notComeStu[clnb-1].size());) {
//			int index = rand() % 90;
//			int flag = 0;//��Ǹ����Ƿ��ں�������
//			for (Student* s : this->notComeStu[clnb-1]) {
//				if (s->getNum().compare(this->veClass4[index].getNum()) == 0) {
//					flag = 1;//˵��index������ں�������
//					break;
//				}
//			}
//			if (flag == 0) {
//				//���ں�������
//				//�޸ı������
//				this->veClass4[index].setCalledCnt();
//				int state = this->veClass4[index].getState(claAount);
//				//���û���޸�û������,���Ҽ��������
//				if (state == 0) {
//					this->veClass4[index].setNotComeCnt();
//					this->notComeStu[clnb-1].push_back(&(this->veClass4[index]));
//					sum++;
//				}
//				i++;
//			}
//		}
//	}
//	if (claAount % 8 == 0 && claAount < 20) {
//		if (!(this->notComeStu[clnb-1].empty())) {
//			for (auto it = this->notComeStu[clnb-1].begin(); it != this->notComeStu[clnb-1].end(); it++) {
//				if ((*it)->getNotComeCnt() < 3) {
//					//û������С�����ε����Ƴ�������
//					this->notComeStu[clnb-1].erase(it);
//					it = this->notComeStu[clnb-1].begin();
//				}
//			}
//		}
//	}
//	//��������������Ч��������
//	pair<int, int> p = make_pair(callingCnt, sum);
//	this->scheme[clnb - 1].push_back(p);
//	//д���ļ�������
//	ofs << clnb << "���" << claAount << "�γ�� ���" << callingCnt << "�� δ��" << sum << "��" << endl;
//}
//void Roll::Callcl5(int claAount, ofstream& ofs, int clnb) {
//	int sum = 0;//��¼��Ч��������
//	int callingCnt = 0;
//	if (claAount <= 5) {
//		//ǰ��ογ��45����	
//		callingCnt = 45;
//	}
//	else {
//		//��γ��30����	
//		callingCnt = 25;
//	}
//	if (this->notComeStu[clnb-1].empty()) {
//		//������Ϊ�գ��ʹ�ȫ���
//		int rolled[90] = { 0 };//��������Ѿ�����һ�γ���е㵽����
//		for (int i = 0; i < callingCnt;) {
//			int index = rand() % 90;
//			if (rolled[index] == 0) {
//				//�޸ı��㵽����
//				this->veClass5[index].setCalledCnt();
//				int state = this->veClass5[index].getState(claAount);
//				//���㵽������û����ͬѧ���м����������ͬʱ�޸�û������
//				if (state == 0) {
//					this->veClass5[index].setNotComeCnt();
//					this->notComeStu[clnb-1].push_back(&(this->veClass5[index]));
//
//					sum++;
//				}
//				rolled[index] = 1;
//				i++;
//			}
//		}
//	}
//	else {
//		//��������Ϊ�գ�һ���ִӺ������飬һ���ִӺ�����֮����˳�
//		//��������
//		for (int i = 0; i < this->notComeStu[clnb-1].size(); i++) {
//			//�޸ı������
//			(this->notComeStu[clnb-1][i])->setCalledCnt();
//			int state = (this->notComeStu[clnb-1][i])->getState(claAount);
//			//���û�����޸�û������
//			if (state == 0) {
//				(this->notComeStu[clnb-1][i])->setNotComeCnt();
//				sum++;
//			}
//		}
//		for (int i = 0; i < callingCnt - (this->notComeStu[clnb-1].size());) {
//			int index = rand() % 90;
//			int flag = 0;//��Ǹ����Ƿ��ں�������
//			for (Student* s : this->notComeStu[clnb-1]) {
//				if (s->getNum().compare(this->veClass5[index].getNum()) == 0) {
//					flag = 1;//˵��index������ں�������
//					break;
//				}
//			}
//			if (flag == 0) {
//				//���ں�������
//				//�޸ı������
//				this->veClass5[index].setCalledCnt();
//				int state = this->veClass5[index].getState(claAount);
//				//���û���޸�û������,���Ҽ��������
//				if (state == 0) {
//					this->veClass5[index].setNotComeCnt();
//					this->notComeStu[clnb-1].push_back(&(this->veClass5[index]));
//					sum++;
//				}
//				i++;
//			}
//		}
//	}
//	if (claAount % 8 == 0 && claAount < 20) {
//		if (!(this->notComeStu[clnb-1].empty())) {
//			for (auto it = this->notComeStu[clnb-1].begin(); it != this->notComeStu[clnb-1].end(); it++) {
//				if ((*it)->getNotComeCnt() < 3) {
//					//û������С�����ε����Ƴ�������
//					this->notComeStu[clnb-1].erase(it);
//					it = this->notComeStu[clnb-1].begin();
//				}
//			}
//		}
//	}
//	//��������������Ч��������
//	pair<int, int> p = make_pair(callingCnt, sum);
//	this->scheme[clnb - 1].push_back(p);
//	//д���ļ�������
//	ofs << clnb << "���" << claAount << "�γ�� ���" << callingCnt << "�� δ��" << sum << "��" << endl;
//}
//����ÿ�ε�����Eֵ
double Roll::Calcu(int claAount) {
	double callingCnt = 0;//���������
	double sum = 0;//��Ч��������
	for (int i = 0; i < 5; i++) {
		callingCnt += this->scheme[i][claAount-1].first;
		sum += this->scheme[i][claAount-1].second;
	}
	return sum / callingCnt;
}
//���㵽ĿǰΪֹû�б��鵽��������
int Roll::getNeverNotCalledCnt(vector<Student>& veClass) {
	int cnt = 0;
	for (int i = 0; i < 90; i++) {
		if (veClass[i].getCalledCnt() == 0) {
			cnt++;
		}
	}
	return cnt;
}
//�����ܵ�����Eֵ
double Roll::Calcu1() {
	double sum = 0;
	double callcnt=0;
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 5; j++) {
			callcnt += this->scheme[j][i].first;
			sum += this->scheme[j][i].second;
		}
	}
	return sum / callcnt;
}
//�����й�ȱ��1�λ���2�ε�����
int Roll::getNotComeCntOne(vector<Student>& veClass) {
	int sum = 0;
	for (Student s : veClass) {
		if (s.getNotComeCnt() == 1) {
			sum++;
		}
	}
	return sum;
}