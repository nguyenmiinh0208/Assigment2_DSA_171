#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <string>
#include "user.h"
#define PASS 1
#define FAILED 0
using namespace std;

struct Score {
	double midterm, assignment, finalScore, average_score;
	Score() {
		midterm = assignment = finalScore = average_score = -1;
	}
};

class object {
private:
	string course_id;
	string id_student;
	string id_teacher;
	Score score;
	string semeter_ID;
public:
	object() {
		course_id = "";
		id_student = "";
		id_teacher = "";
		semeter_ID = "";
	}
	~object() {};
	void setCourse_id(string id);
	void setID_teacher(string idT);
	void setID_student(string idS);
	void setSemeter_ID(string smID);
	void setMidSCore(double mid);
	void setAssignment_Score(double ass);
	void setFinalScore(double f);
	void setAverage_score(double a);

	string getCourse_id();
	string gettID_teacher();
	string getID_student();
	string getSemeter_ID();
	double getMid_Score();
	double getAssignment_Score();
	double getFinalScore();
	double getAverage_score();
};
int LoadFileObject(char *fName, vector<object> &ListObject);

#endif // !OBJECT_H
