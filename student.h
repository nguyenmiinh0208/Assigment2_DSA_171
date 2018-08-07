#ifndef STUDENT_H
#define STUDENT_H

#include "user.h"
#include "object.h"
#include "course.h"
#include "subject.h"
using namespace std;

class student : public users {
	string mssv;
	string name;
	string Bdate;
	string address;
public:
	student() {
		account = "";
		passWord = "";
		role = -1;
		mssv = "";
		name = "";
		Bdate = "";
		address = "";
	}
	~student() {};
	void setName(string name);
	void setBdate(string date);
	void setAddress(string add);
	void setMssv(string id);

	string getName();
	string getBdate();
	string getAddress();
	string getMssv();

	void JoinCoure(vector<course> &courseList, vector<object> &ObjectList, vector<subject> &SubjectList);
	void CancelCoure(vector<course> &courseList, vector<object> &ObjectList, vector<subject> &ListSubject);
	void ViewMyCoure(vector<object> & ObjectList, vector<subject>ListSubject, vector<course> &CourseList);
	void ShowOption_Student(string acc);

};

int LoadInfo_Student(char *fName, vector<student> &ListStudent);
int option_student(student &st, vector<users> &ListUser, vector<student> &StList, vector<course> &CList, vector<subject> &SjList, vector<object> &ObjectList);
#endif