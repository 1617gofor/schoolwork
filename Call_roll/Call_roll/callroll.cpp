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
//初始化班级，即把输入的数据分配给对应的班级
void Roll::Init() {
	ifstream ifs;
	ifs.open("../../schooldata/Name1.txt", ios::in);
	if (!ifs.is_open()) {
		//文件打开失败给出提示
		cout << "Init中文件打开失败" << endl;
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
		//读取状态
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
	//对每个班进行按照学号升序排序
	sort(veClass[0].begin(), veClass[0].end(), Greater());
	sort(veClass[1].begin(), veClass[1].end(), Greater());
	sort(veClass[2].begin(), veClass[2].end(), Greater());
	sort(veClass[3].begin(), veClass[3].end(), Greater());
	sort(veClass[4].begin(), veClass[4].end(), Greater());
	//*********************测试
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
//单次点名并且把点到的名单输出到文件
void Roll::Callcl(int claAount, ofstream& ofs, int clnb) {
	int sum = 0;//记录有效点名次数
	int callingCnt = 0;
	if (claAount <= 3) {
		//前3次课抽点n个人	
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
		//黑名单为空，就从全班抽
		int rolled[90] = { 0 };//用来标记已经在这一次抽点中点到的人
		for (int i = 0; i < callingCnt;) {
			int index = rand() % 90;
			if (rolled[index] == 0) {
				//修改被点到次数
				this->veClass[clnb-1][index].setCalledCnt();
				int state = this->veClass[clnb-1][index].getState(claAount);
				//被点到，但是没来的同学进行加入黑名单，同时修改没来次数
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
		//黑名单不为空，一部分从黑名单抽，一部分从黑名单之外的人抽
		//抽点黑名单
		int ncsize = this->notComeStu[clnb - 1].size();
		if (claAount <= 3) {
			//黑名单部分抽
			int ar = ncsize * 2 / 3;
			for (int i = 0; i <= ar; i++) {
				//修改被点次数
				int index = rand() % ncsize;
				this->notComeStu[clnb - 1][index]->setCalledCnt();
				int state = (this->notComeStu[clnb - 1][index])->getState(claAount);
				//如果没来就修改没来次数
				if (state == 0) {
					(this->notComeStu[clnb - 1][index])->setNotComeCnt();
					sum++;
				}
			}
		}
		else {
			for (int i = 0; i < this->notComeStu[clnb - 1].size(); i++) {
				//修改被点次数
				this->notComeStu[clnb - 1][i]->setCalledCnt();
				int state = (this->notComeStu[clnb - 1][i])->getState(claAount);
				//如果没来就修改没来次数
				if (state == 0) {
					(this->notComeStu[clnb - 1][i])->setNotComeCnt();
					sum++;
				}
			}
		}
		//在第2次之后就优先抽未被抽到的
		int sumCal = callingCnt - (this->notComeStu[clnb - 1].size());//还需抽点的人数
		int sumNotNeverCalled = this->getNeverNotCalledCnt(this->veClass[clnb - 1]);//没被点过的人数
		if (sumNotNeverCalled > 0) {
			//只要有从来没有被点过的学生就要优先点
			int minI = sumCal;
			if (sumNotNeverCalled < sumCal) {
				minI = sumNotNeverCalled;
			}
			int rooled[90] = { 0 };
			for (int i = 0; i < minI;) {
				int index = rand() % 90;
				if (this->veClass[clnb - 1][index].getCalledCnt() == 0) {
					//这个学生没有被点过,可以推出这个学生肯定不是黑名单的
					//点这个学生，修改被点次数
					this->veClass[clnb - 1][index].setCalledCnt();
					int state = this->veClass[clnb - 1][index].getState(claAount);
					rooled[index] = 1;
					if (state == 0) {
						//被点到，但是没来，就要加入黑名单
						sum++;//有效点名加一
						this->veClass[clnb - 1][index].setNotComeCnt();
						this->notComeStu[clnb - 1].push_back(&(this->veClass[clnb - 1][index]));
					}
					i++;
					sumCal--;
				}
			}
			//点完从来没有被点过的学生后还没有够人数，就继续点其他的非黑名单人
			while (sumCal>0) {
				int index = rand() % 90;
				int flag = 0;//标记该人是否在黑名单中
				for (Student* s : this->notComeStu[clnb - 1]) {
					if (s->getNum().compare(this->veClass[clnb - 1][index].getNum()) == 0) {
						flag = 1;//说明index这个人在黑名单中
						break;
					}
				}
				if (flag == 0&&rooled[index]==0) {
					//不在黑名单中并且刚刚没有被点过
					//修改被点次数
					rooled[index] = 1;
					this->veClass[clnb - 1][index].setCalledCnt();
					int state = this->veClass[clnb - 1][index].getState(claAount);
					//如果没来修改没来次数,并且加入黑名单
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
			//所有学生都已经被点过至少一次了
			int rooled[90] = { 0 };
			int sumCal1 = this->getNotComeCntOne(this->veClass[clnb - 1]);
			if (sumCal1 > 0) {
				//优先点以前有过缺课记录的人
				int index = 0;
				while (sumCal > 0) {
					int flag = 0;//标记该人是否在黑名单中
					for (Student* s : this->notComeStu[clnb - 1]) {
						if (s->getNum().compare(this->veClass[clnb - 1][index].getNum()) == 0) {
							flag = 1;//说明index这个人在黑名单中
							break;
						}
					}
					if (flag == 0 && rooled[index] == 0 && (this->veClass[clnb - 1][index].getNotComeCnt() == 1)) {
						//不在黑名单中并且刚刚没有被点过并且有过缺课记录的
						//修改被点次数
						this->veClass[clnb - 1][index].setCalledCnt();
						int state = this->veClass[clnb - 1][index].getState(claAount);
						rooled[index] = 1;
						//如果没来修改没来次数,并且加入黑名单
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
				//其余的随机点
				int index = rand() % 90;
				int flag = 0;//标记该人是否在黑名单中
				for (Student* s : this->notComeStu[clnb - 1]) {
					if (s->getNum().compare(this->veClass[clnb - 1][index].getNum()) == 0) {
						flag = 1;//说明index这个人在黑名单中
						break;
					}
				}
				if (flag == 0 && rooled[index] == 0) {
					//不在黑名单中并且刚刚没有被点过
					//修改被点次数
					this->veClass[clnb - 1][index].setCalledCnt();
					int state = this->veClass[clnb - 1][index].getState(claAount);
					rooled[index] = 1;
					//如果没来修改没来次数,并且加入黑名单
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
					//没到次数小于2次的先移出黑名单
					it=this->notComeStu[clnb-1].erase(it);
					
				}
				else {
					++it;
				}
			}
		}	
	}
	//保存抽点人数和有效点名次数
	pair<int, int> p = make_pair(callingCnt, sum);
	this->scheme[clnb-1].push_back(p);
	//写入文件保存结果
	ofs <<clnb<< "班第" << claAount << "次抽点 抽点" << callingCnt << "人 未到" << sum << "人" << endl;


}
//void Roll::Callcl2(int claAount, ofstream& ofs, int clnb) {
//	int sum = 0;//记录有效点名次数
//	int callingCnt = 0;
//	if (claAount <= 5) {
//		//前五次课抽点45个人	
//		callingCnt = 45;
//	}
//	else {
//		//后课抽点30个人	
//		callingCnt = 25;
//	}
//	if (this->notComeStu[clnb-1].empty()) {
//		//黑名单为空，就从全班抽
//		int rolled[90] = { 0 };//用来标记已经在这一次抽点中点到的人
//		for (int i = 0; i < callingCnt;) {
//			int index = rand() % 90;
//			if (rolled[index] == 0) {
//				//修改被点到次数
//				this->veClass2[index].setCalledCnt();
//				int state = this->veClass2[index].getState(claAount);
//				//被点到，但是没来的同学进行加入黑名单，同时修改没来次数
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
//		//黑名单不为空，一部分从黑名单抽，一部分从黑名单之外的人抽
//		//抽点黑名单
//		for (int i = 0; i < this->notComeStu[clnb-1].size(); i++) {
//			//修改被点次数
//			(this->notComeStu[clnb-1][i])->setCalledCnt();
//			int state = (this->notComeStu[clnb-1][i])->getState(claAount);
//			//如果没来就修改没来次数
//			if (state == 0) {
//				(this->notComeStu[clnb-1][i])->setNotComeCnt();
//				sum++;
//			}
//		}
//		for (int i = 0; i < callingCnt - (this->notComeStu[clnb-1].size());) {
//			int index = rand() % 90;
//			int flag = 0;//标记该人是否在黑名单中
//			for (Student* s : this->notComeStu[clnb-1]) {
//				if (s->getNum().compare(this->veClass2[index].getNum()) == 0) {
//					flag = 1;//说明index这个人在黑名单中
//					break;
//				}
//			}
//			if (flag == 0) {
//				//不在黑名单中
//				//修改被点次数
//				this->veClass2[index].setCalledCnt();
//				int state = this->veClass2[index].getState(claAount);
//				//如果没来修改没来次数,并且加入黑名单
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
//					//没到次数小于三次的先移出黑名单
//					this->notComeStu[clnb-1].erase(it);
//					it = this->notComeStu[clnb-1].begin();
//				}
//			}
//		}
//	}
//	//保存抽点人数和有效点名次数
//	pair<int, int> p = make_pair(callingCnt, sum);
//	this->scheme[clnb - 1].push_back(p);
//	//写入文件保存结果
//	ofs << clnb << "班第" << claAount << "次抽点 抽点" << callingCnt << "人 未到" << sum << "人" << endl;
//}
//void Roll::Callcl3(int claAount, ofstream& ofs, int clnb) {
//	int sum = 0;//记录有效点名次数
//	int callingCnt = 0;
//	if (claAount <= 5) {
//		//前五次课抽点45个人	
//		callingCnt = 45;
//	}
//	else {
//		//后课抽点30个人	
//		callingCnt = 25;
//	}
//	if (this->notComeStu[clnb-1].empty()) {
//		//黑名单为空，就从全班抽
//		int rolled[90] = { 0 };//用来标记已经在这一次抽点中点到的人
//		for (int i = 0; i < callingCnt;) {
//			int index = rand() % 90;
//			if (rolled[index] == 0) {
//				//修改被点到次数
//				this->veClass3[index].setCalledCnt();
//				int state = this->veClass3[index].getState(claAount);
//				//被点到，但是没来的同学进行加入黑名单，同时修改没来次数
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
//		//黑名单不为空，一部分从黑名单抽，一部分从黑名单之外的人抽
//		//抽点黑名单
//		for (int i = 0; i < this->notComeStu[clnb-1].size(); i++) {
//			//修改被点次数
//			(this->notComeStu[clnb-1][i])->setCalledCnt();
//			int state = (this->notComeStu[clnb-1][i])->getState(claAount);
//			//如果没来就修改没来次数
//			if (state == 0) {
//				(this->notComeStu[clnb-1][i])->setNotComeCnt();
//				sum++;
//			}
//		}
//		for (int i = 0; i < callingCnt - (this->notComeStu[clnb-1].size());) {
//			int index = rand() % 90;
//			int flag = 0;//标记该人是否在黑名单中
//			for (Student* s : this->notComeStu[clnb-1]) {
//				if (s->getNum().compare(this->veClass3[index].getNum()) == 0) {
//					flag = 1;//说明index这个人在黑名单中
//					break;
//				}
//			}
//			if (flag == 0) {
//				//不在黑名单中
//				//修改被点次数
//				this->veClass3[index].setCalledCnt();
//				int state = this->veClass3[index].getState(claAount);
//				//如果没来修改没来次数,并且加入黑名单
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
//					//没到次数小于三次的先移出黑名单
//					this->notComeStu[clnb-1].erase(it);
//					it = this->notComeStu[clnb-1].begin();
//				}
//			}
//		}
//	}
//	//保存抽点人数和有效点名次数
//	pair<int, int> p = make_pair(callingCnt, sum);
//	this->scheme[clnb - 1].push_back(p);
//	//写入文件保存结果
//	ofs << clnb << "班第" << claAount << "次抽点 抽点" << callingCnt << "人 未到" << sum << "人" << endl;
//}
//void Roll::Callcl4(int claAount, ofstream& ofs, int clnb) {
//	int sum = 0;//记录有效点名次数
//	int callingCnt = 0;
//	if (claAount <= 5) {
//		//前五次课抽点45个人	
//		callingCnt = 45;
//	}
//	else {
//		//后课抽点30个人	
//		callingCnt = 25;
//	}
//	if (this->notComeStu[clnb-1].empty()) {
//		//黑名单为空，就从全班抽
//		int rolled[90] = { 0 };//用来标记已经在这一次抽点中点到的人
//		for (int i = 0; i < callingCnt;) {
//			int index = rand() % 90;
//			if (rolled[index] == 0) {
//				//修改被点到次数
//				this->veClass4[index].setCalledCnt();
//				int state = this->veClass4[index].getState(claAount);
//				//被点到，但是没来的同学进行加入黑名单，同时修改没来次数
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
//		//黑名单不为空，一部分从黑名单抽，一部分从黑名单之外的人抽
//		//抽点黑名单
//		for (int i = 0; i < this->notComeStu[clnb-1].size(); i++) {
//			//修改被点次数
//			(this->notComeStu[clnb-1][i])->setCalledCnt();
//			int state = (this->notComeStu[clnb-1][i])->getState(claAount);
//			//如果没来就修改没来次数
//			if (state == 0) {
//				(this->notComeStu[clnb-1][i])->setNotComeCnt();
//				sum++;
//			}
//		}
//		for (int i = 0; i < callingCnt - (this->notComeStu[clnb-1].size());) {
//			int index = rand() % 90;
//			int flag = 0;//标记该人是否在黑名单中
//			for (Student* s : this->notComeStu[clnb-1]) {
//				if (s->getNum().compare(this->veClass4[index].getNum()) == 0) {
//					flag = 1;//说明index这个人在黑名单中
//					break;
//				}
//			}
//			if (flag == 0) {
//				//不在黑名单中
//				//修改被点次数
//				this->veClass4[index].setCalledCnt();
//				int state = this->veClass4[index].getState(claAount);
//				//如果没来修改没来次数,并且加入黑名单
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
//					//没到次数小于三次的先移出黑名单
//					this->notComeStu[clnb-1].erase(it);
//					it = this->notComeStu[clnb-1].begin();
//				}
//			}
//		}
//	}
//	//保存抽点人数和有效点名次数
//	pair<int, int> p = make_pair(callingCnt, sum);
//	this->scheme[clnb - 1].push_back(p);
//	//写入文件保存结果
//	ofs << clnb << "班第" << claAount << "次抽点 抽点" << callingCnt << "人 未到" << sum << "人" << endl;
//}
//void Roll::Callcl5(int claAount, ofstream& ofs, int clnb) {
//	int sum = 0;//记录有效点名次数
//	int callingCnt = 0;
//	if (claAount <= 5) {
//		//前五次课抽点45个人	
//		callingCnt = 45;
//	}
//	else {
//		//后课抽点30个人	
//		callingCnt = 25;
//	}
//	if (this->notComeStu[clnb-1].empty()) {
//		//黑名单为空，就从全班抽
//		int rolled[90] = { 0 };//用来标记已经在这一次抽点中点到的人
//		for (int i = 0; i < callingCnt;) {
//			int index = rand() % 90;
//			if (rolled[index] == 0) {
//				//修改被点到次数
//				this->veClass5[index].setCalledCnt();
//				int state = this->veClass5[index].getState(claAount);
//				//被点到，但是没来的同学进行加入黑名单，同时修改没来次数
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
//		//黑名单不为空，一部分从黑名单抽，一部分从黑名单之外的人抽
//		//抽点黑名单
//		for (int i = 0; i < this->notComeStu[clnb-1].size(); i++) {
//			//修改被点次数
//			(this->notComeStu[clnb-1][i])->setCalledCnt();
//			int state = (this->notComeStu[clnb-1][i])->getState(claAount);
//			//如果没来就修改没来次数
//			if (state == 0) {
//				(this->notComeStu[clnb-1][i])->setNotComeCnt();
//				sum++;
//			}
//		}
//		for (int i = 0; i < callingCnt - (this->notComeStu[clnb-1].size());) {
//			int index = rand() % 90;
//			int flag = 0;//标记该人是否在黑名单中
//			for (Student* s : this->notComeStu[clnb-1]) {
//				if (s->getNum().compare(this->veClass5[index].getNum()) == 0) {
//					flag = 1;//说明index这个人在黑名单中
//					break;
//				}
//			}
//			if (flag == 0) {
//				//不在黑名单中
//				//修改被点次数
//				this->veClass5[index].setCalledCnt();
//				int state = this->veClass5[index].getState(claAount);
//				//如果没来修改没来次数,并且加入黑名单
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
//					//没到次数小于三次的先移出黑名单
//					this->notComeStu[clnb-1].erase(it);
//					it = this->notComeStu[clnb-1].begin();
//				}
//			}
//		}
//	}
//	//保存抽点人数和有效点名次数
//	pair<int, int> p = make_pair(callingCnt, sum);
//	this->scheme[clnb - 1].push_back(p);
//	//写入文件保存结果
//	ofs << clnb << "班第" << claAount << "次抽点 抽点" << callingCnt << "人 未到" << sum << "人" << endl;
//}
//计算每次点名的E值
double Roll::Calcu(int claAount) {
	double callingCnt = 0;//抽点总人数
	double sum = 0;//有效点名次数
	for (int i = 0; i < 5; i++) {
		callingCnt += this->scheme[i][claAount-1].first;
		sum += this->scheme[i][claAount-1].second;
	}
	return sum / callingCnt;
}
//计算到目前为止没有被抽到过的人数
int Roll::getNeverNotCalledCnt(vector<Student>& veClass) {
	int cnt = 0;
	for (int i = 0; i < 90; i++) {
		if (veClass[i].getCalledCnt() == 0) {
			cnt++;
		}
	}
	return cnt;
}
//计算总的名的E值
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
//计算有过缺课1次或者2次的人数
int Roll::getNotComeCntOne(vector<Student>& veClass) {
	int sum = 0;
	for (Student s : veClass) {
		if (s.getNotComeCnt() == 1) {
			sum++;
		}
	}
	return sum;
}