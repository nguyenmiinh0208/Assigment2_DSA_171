#include "user.h"
#include "admin.h"
#include "student.h"
#include "teacher.h"
#include <cstdint>
#include <iostream>
using namespace std;

int checkLogin(string userName, string passWord, vector<users> &ListUser) {
	bool checkLog = false;
	int pos; //lấy vị trí users trong vecto
	for (int i = 0; i < ListUser.size(); i++) {
		if (userName == ListUser[i].getAccount()) {
			if (passWord == ListUser[i].getPassWord()) {
				pos = i;
				checkLog = true;
			}
		}
	}
	if (checkLog) return pos;
	else return -1;
	
}

users Login(vector<users> &ListUser) {
	fflush(stdin);
	string acc;
	string pass;
	int position;
	while (true) {
		system("cls");
		cout << "User name: ";
		cin >> acc;

		cout << "PassWord: ";
		cin >> pass;
		position = checkLogin(acc, pass, ListUser);//Nếu đăng nhập thành công thì checkLogin sẽ return vị trí account trong list
		if (position != -1) {
			cout << "Login Success..." << endl;
			break;
		}
		else ReLogin:{
			cout << "Login Failed !" << endl;
			cout << "Continue ? (Y/N) ";
			char k;
			fflush(stdin);
			cin >> k;
			if (k == 'Y' || k == 'y') continue;
			else if (k == 'N' || k == 'n') {
				users failed;
				return failed;
			}
			else {
				cout << "Error - (Character input error)" << endl;
				goto ReLogin;
			}
		}
	}
	return ListUser[position];
}