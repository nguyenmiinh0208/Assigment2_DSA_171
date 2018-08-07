#ifndef USER_H
#define USER_H

#include <string>
#include <string.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdint>
using namespace std;

#define ADMIN 0
#define TEACHER 1
#define STUDENT 2

#define LOGOUT 1
#define EXIT 2
class users {
protected:
	string account;
	string passWord;
	int role;
public:
	users() {
		account = "";
		passWord = "";
		role = -1;
	}
	~users() {};
	void setAccount(string Acc);
	void setPassWord(string pass);
	void setRole(int r);

	//string getPassWord() { return passWord; }
	string getAccount() { return account; }
	int getRole() { return role; }
	string getPassWord() { return passWord; }
	void ChangePassWord(vector<users> &ListUser);
};

int LoadAccoutUser(char *fName, vector<users> &ListUser);
users Login(vector<users> &ListUser);

#endif // !USER_H

#pragma once
