#ifndef ADMIN_H
#define ADMIN_H

#include "user.h"
#include "student.h"
#include "teacher.h"
using namespace std;


class admin : public users {
public:
	admin() {
		account = "";
		passWord = "";
		role = -1;
	}
	~admin() {};
	void Add_Users(vector<users> &ListUser, vector<teacher> &TList, vector<student> &StList);
	void Delete_Users(vector<users> &ListUser, vector<teacher> &TList, vector<student> &StList);
	void Search_User(vector<users> &ListUser, vector<teacher> &TList, vector<student> &StList);
	void showUser(vector<users> &ListUser);
	void Multiple_Delete(vector<users> &ListUser, vector<student> &StList, vector<subject> &SubjectList, vector<object> &ObjectList);
	void ShowOption_Admin();
};

int option_admin(admin &a, vector<users> &ListUser, vector<teacher> &TList, vector<student> &StList, vector<subject> &SubjectList, vector<object> &objectList);

#endif // !ADMIN_H
