#include "course.h"
using namespace std;

void course::setCourseID(string id) { course_id = id; }
void course::setIDteacher(string idT) { id_teacher = idT; }
void course::setNameSubject(string n) { name_Subject = n; }
void course::setN_student(int n) { n_student = n; }
void course::setSlot(int sl) { slot = sl; }
void course::setSemester_ID(string st) { id_semester = st; }
void course::setState(int st) { state = st; }

string course::getCourse() { return course_id; }
string course::getIDteacher() { return id_teacher; }
string course::getNameSubject() { return name_Subject; }
string course::getSemesterID() { return id_semester; }
int course::getN_student() { return n_student; }
int course::getSlot() { return slot; }
int course::getState() { return state; }

//--------------------------------------------------------------------------------
int LoadFileCourse(char *fName, vector<course> &ListCourse) {
	fstream fileCourse;
	fileCourse.open(fName);
	
	if (!fileCourse.is_open()) {
		return -1;
	}

	string str;
	getline(fileCourse, str);
	while (getline(fileCourse, str)) {
		course c;
		int pos;
		pos = str.find(',');
		c.setCourseID(str.substr(0, pos));//Set id_course

		str.erase(0, pos + 1);
		pos = str.find(',');
		c.setIDteacher(str.substr(0, pos)); //set id_teacher

		str.erase(0, pos + 1);
		pos = str.find(',');
		c.setNameSubject(str.substr(0, pos)); //set name subject

		str.erase(0, pos + 1);
		pos = str.find(',');
		c.setN_student(atoi(str.substr(0, pos).c_str()));//set score

		str.erase(0, pos + 1);
		pos = str.find(',');
		c.setSlot(atoi(str.substr(0, pos).c_str()));//set score

		str.erase(0, pos + 1);
		pos = str.find(',');
		c.setSemester_ID(str.substr(0, pos)); // set semester id

		str.erase(0, pos + 1);
		c.setState(atoi(str.substr(0).c_str()));
		ListCourse.push_back(c);//add vào list
	}
	fileCourse.close();
	return 0;
}