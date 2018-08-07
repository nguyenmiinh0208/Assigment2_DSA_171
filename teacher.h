#ifndef TEACHER_H
#define TEACHER_H

#include "user.h"
#include "course.h"
#include "subject.h"
#include "object.h"
using namespace std;

class teacher : public users {
private:
	string name;
	string Bdate;
	string phoneNumBer;
	string address;
public:
	teacher() {
		account = "";
		passWord = "";
		role = -1;
		name = "";
		Bdate = "";
		phoneNumBer = "";
		address = "";
	}
	~teacher() {};
	void setName(string name);
	void setBdate(string date);
	void setAddress(string add);
	void setPhone(string num);

	string getName();
	string getBdate();
	string getAddress();
	string getPhone();

	void ViewMyCourse(vector<course> &courseList);
	void OpenCourse(vector<subject> &SjList, vector<course> &courseList, vector<object> &ObjectList);
	void SummaryScore(vector<course> &courseList, vector<object> &ObjectList);
	//void ModifyScore();
	void ShowOption_Teacher(string acc);
};

int LoadInfo_Teacher(char *fName, vector<teacher> &ListTeacher);
int option_teacher(teacher &t, vector<users> &ListUser, vector<teacher> &TList, vector<course> &CList, vector<subject> &SjList, vector<object> &ObjectList);



#endif