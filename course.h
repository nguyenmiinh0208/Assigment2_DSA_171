#ifndef COURSE_H
#define COURSE_H

#include "user.h"
using namespace std;
#define MAX_SLOT 40
#define MIN_N_STUDENT 0
#define UNABLE 1
#define DISABLE 0
class course {
private:
	string course_id;
	string id_teacher;
	string name_Subject;
	string id_semester;
	int n_student;
	int slot;
	int state;
public:
	course() {
		course_id = "";
		id_teacher = "";
		name_Subject = "";
		n_student = -1;
		slot = -1;
		id_semester = "";
	}
	~course() {};
	void setCourseID(string id);
	void setIDteacher(string idT);
	void setNameSubject(string n);
	void setN_student(int n);
	void setSlot(int sl);
	void setSemester_ID(string st);
	void setState(int st);

	string getCourse();
	string getIDteacher();
	string getNameSubject();
	string getSemesterID();
	int getN_student();
	int getSlot();
	int getState();
};

int LoadFileCourse(char *fName, vector<course> &ListCourse);

#endif // !COURSE_H

