#include"student.h"
#include<vector>
#include<fstream>
#include<algorithm>
using namespace std;
//生成测试数据并保存到文件
void DataG() {
	vector<string> veName;
	vector<Student>veStu;
	ifstream ifs;
	//写对应的名单文件路径
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
	//cout << "未到人数" << cnt << "个" << endl;
	//把名字封装成学生对象，并且放入学生集合veStu中
	int clnumber = 1;
	for (int i = 0; i < 450; i++) {
		string num = "032006";
		int index = rand() % len;
		string name = veName[index];//随机取一个名字
		vector<string>::iterator it = veName.begin();
		int num1 = num0 + i;
		num += to_string(num1);//生成学号
		int state = 1;
		////cnt表示缺课的人数
		//if (cnt[clnumber-1])
		//{
		//	state = 0;
		//	cnt[clnumber-1]--;
		//}
		//限制每个班只有90人
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
	//分配state状态
	int index = 0;
	for (int i = 1; i <= 5; i++){
		auto begin = veStu.begin() + 90 * (i - 1);
		auto end = veStu.begin() + 90 * i;
		random_shuffle(begin, end);//对学生容器进行洗牌操作
		int badmenCount = rand() % 4 + 5;//坏学生人数
		int badmenCount2 = badmenCount;
		//对每个班级状态分配
		for (; index < veStu.size(); index++) {
			//先分配坏学生
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
			//每次课程
			else {
				break;
			}
		}
		//选出每次课会其他0-3名未到同学
		for (int j = 1; j <= 20; j++) {
			int index2;
			int notComeN = rand() % 4;
			while (notComeN) {
				//选出每次课因其他原因未到的同学
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
	


	//生成学生数据文件
	ofstream ofs;
	//写班级名单文件存放的路径
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
	cout << "名单生成成功" << endl;
}

int main() {
	srand((unsigned int)time(NULL));
	DataG();
	system("pause");
	return 0;
}