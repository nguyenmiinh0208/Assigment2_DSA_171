#include "user.h"
#include "teacher.h"
#include "student.h"
using namespace std;


void users::setAccount(string Acc) { account = Acc; }
void users::setPassWord(string pass) { passWord = pass; }
void users::setRole(int r) { role = r; }
void users::ChangePassWord(vector<users> &ListUser) {
	cout << "----------CHANGE PASSWORD----------" << endl;
	cout << "-----------------------------------" << endl;
	string curPass;
	string newPass;
	string confirmPass;
	int pos;//Lưu lại vị trí account đã đổi mật khẩu
	while (true) {
		cout << "Current pasword: "; cin >> curPass;
		bool checkPass = false;
		for (int i = 0; i < ListUser.size(); i++) {
			if (account == ListUser[i].getAccount()) {
				if (curPass == passWord) {
					pos = i;
					checkPass = true;
				}
			}
		}
		if (checkPass) break;
		else {
			cout << "Incorrect password !" << endl;
			cout << "Please enter the correct password. Continue (Y/N) ?" << endl;
			char k; cin >> k;
			if (k == 'Y' || k == 'y') continue;
			else if (k == 'N' || k == 'n') {
				system("pause");
				return;
			}
		}
	}

	while (true) {
		cout << "New password: "; cin >> newPass;
		cout << "Confirm new password: "; cin >> confirmPass;
		if (newPass.compare(confirmPass) != 0) {
			cout << "Please confirm password correctly!!" << endl;
			continue;
		}
		else break;
	}
	cout << "Change password successfully!" << endl;
	ListUser[pos].setPassWord(newPass);

	fstream fileUser;
	fileUser.open("user_Tmp.csv", ios::out);
	if (!fileUser.is_open()) {
		cout << "Not Found !" << endl;
		return;
	}
	for (int i = 0; i < ListUser.size(); i++) {
		fileUser << ListUser[i].getAccount() << "," << ListUser[i].getPassWord() << ",";
		if (ListUser[i].getRole() == ADMIN) {
			fileUser << "admin";
		}
		if (ListUser[i].getRole() == TEACHER) {
			fileUser << "teacher";
		}
		if (ListUser[i].getRole() == STUDENT) {
			fileUser << "student";
		}
		fileUser << endl;
	}

	fileUser.close();

	remove("user.csv");
	rename("user_Tmp.csv", "user.csv");
	system("pause");
	return;
}
//---------------------------------------------------------------------------------------------

void teacher::setName(string n) { name = n; }
void teacher::setBdate(string date) {Bdate = date;}
void teacher::setAddress(string add) { address = add; }
void teacher::setPhone(string num) { phoneNumBer = num; }

string teacher::getName() { return name; }
string teacher::getBdate() { return Bdate; }
string teacher::getAddress() { return address; }
string teacher::getPhone() { return phoneNumBer; }

//-----------------------------------------------------------------------------------------------

void student::setName(string n) { name = n; }
void student::setBdate(string date) { Bdate = date; }
void student::setAddress(string add) { address = add; }
void student::setMssv(string id) { mssv = id; }

string student::getName() { return name; }
string student::getBdate() { return Bdate; }
string student::getAddress() { return address; }
string student::getMssv() { return mssv; }

//-----------------------------------------------------------------------------------------------

int LoadAccoutUser(char *fName, vector<users> &ListUser) {
	fstream fileUser;
	fileUser.open(fName);
	if (!fileUser.is_open()) {
		return -1;
	}
	string str;
	while (getline(fileUser, str)) {
		users user;
		int pos; //Lấy vị trí dấu phẩy
		pos = str.find(',');
		user.setAccount(str.substr(0, pos));//set account
		
		str.erase(0, pos + 1);
		pos = str.find(',');
		user.setPassWord(str.substr(0, pos));//set passWord

		str.erase(0, pos + 1);
		if (str == "admin") user.setRole(ADMIN); //set role
		else if (str == "teacher") user.setRole(TEACHER);
		else if (str == "student") user.setRole(STUDENT);
		ListUser.push_back(user);
	}
	fileUser.close();
	return 0;
}

int LoadInfo_Teacher(char *fName, vector<teacher> &ListTeacher) {
	fstream fileTeacher;
	fileTeacher.open(fName);

	if (!fileTeacher.is_open()) {
		return -1;
	}

	string str;
	while (getline(fileTeacher, str)) {
		teacher tea;
		int pos;
		pos = str.find(',');
		tea.setAccount(str.substr(0, pos)); //set acount

		str.erase(0, pos + 1);
		pos = str.find(',');
		tea.setName(str.substr(0, pos)); //set name

		str.erase(0, pos + 1);
		pos = str.find(',');
		tea.setBdate(str.substr(0, pos)); //set birthdate

		str.erase(0, pos + 1);
		pos = str.find(',');
		tea.setPhone(str.substr(0, pos)); //set phone number

		str.erase(0, pos + 1);
		tea.setAddress(str.substr(0)); //set address

		tea.setRole(TEACHER);

		ListTeacher.push_back(tea);
	}
	fileTeacher.close();
	return 0;
}

int LoadInfo_Student(char *fName, vector<student> &ListStudent) {
	fstream fileStudent;
	fileStudent.open(fName);

	if (!fileStudent.is_open()) {
		return -1;
	}

	string str;
	while (getline(fileStudent, str)) {
		student student;
		int pos;
		pos = str.find(',');
		student.setMssv(str.substr(0, pos)); //set mssv

		str.erase(0, pos + 1);
		pos = str.find(',');
		student.setName(str.substr(0, pos)); //set name

		str.erase(0, pos + 1);
		pos = str.find(',');
		student.setBdate(str.substr(0, pos)); //set birthdate

		str.erase(0, pos + 1);
		student.setAddress(str.substr(0)); //set address

		student.setRole(STUDENT);

		ListStudent.push_back(student);
	}
	fileStudent.close();
	return 0;
}