#include "object.h"

using namespace std;

void object::setCourse_id(string id) { course_id = id; }
void object::setID_teacher(string idT) { id_teacher = idT; }
void object::setID_student(string idS) { id_student = idS; }
void object::setMidSCore(double mid) { score.midterm = mid; }
void object::setAssignment_Score(double ass) { score.assignment = ass; }
void object::setFinalScore(double f) { score.finalScore = f; }
void object::setAverage_score(double a) { score.average_score = a; }
void object::setSemeter_ID(string smID) { semeter_ID = smID; }

string object::getCourse_id() { return course_id; }
string object::gettID_teacher() { return id_teacher; }
string object::getID_student() { return id_student; }
string object::getSemeter_ID() { return semeter_ID; }
double object::getMid_Score() { return score.midterm; }
double object::getAssignment_Score() { return score.assignment; }
double object::getFinalScore() { return score.finalScore; }
double object::getAverage_score() { return score.average_score; }

//-----------------------------------------------------------------------------

int LoadFileObject(char *fName, vector<object> &ListObject) {
	fstream fileObject;
	fileObject.open(fName);
	if (!fileObject.is_open()) {
		return -1;
	}
	string str;
	getline(fileObject, str);
	while (getline(fileObject, str)) {
		if (str.length() == 0) break;
		object o;
		int pos;
		pos = str.find(',');
		o.setCourse_id(str.substr(0, pos));//Set id_course

		str.erase(0, pos + 1);
		pos = str.find(',');
		o.setID_student(str.substr(0, pos)); //set id_student

		str.erase(0, pos + 1);
		pos = str.find(',');
		o.setID_teacher(str.substr(0, pos)); //set id_teacher

		str.erase(0, pos + 1);
		pos = str.find(',');
		o.setMidSCore(stod(str.substr(0, pos).c_str()));//midterm

		str.erase(0, pos + 1);
		pos = str.find(',');
		o.setAssignment_Score(stod(str.substr(0, pos).c_str()));//assignment

		str.erase(0, pos + 1);
		pos = str.find(',');
		o.setFinalScore(stod(str.substr(0, pos).c_str()));//final

		str.erase(0, pos + 1);
		pos = str.find(',');
		o.setAverage_score(stod(str.substr(0, pos).c_str()));//average
		
		str.erase(0, pos + 1);
		o.setSemeter_ID(str.substr(0));//set score
		ListObject.push_back(o);//add vào list
	}
	fileObject.close();
	return 0;
}