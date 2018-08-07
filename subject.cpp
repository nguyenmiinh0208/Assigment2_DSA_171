#include "subject.h"
using namespace std;

void subject::setID(string id) { id_subject = id; }
void subject::setName_sj(string name_sj) { name_subject = name_sj; }
void subject::setNumberOfCredits(int cre) { credits = cre; }

string subject::getIDSubject() { return id_subject; }
string subject::getNameSubject() { return name_subject; }
int subject::getNumberOfCredits() { return credits; }

int LoadInfo_Subject(char *fName, vector<subject> &ListSubject) {
	fstream fileSubject;
	fileSubject.open(fName);
	if (!fileSubject.is_open()) {
		return -1;
	}
	string str;
	while (getline(fileSubject, str)) {
		subject s;
		int pos;
		pos = str.find(',');
		
		s.setID(str.substr(0, pos));//set id_subject
		str.erase(0, pos + 1);
		pos = str.find(',');
		s.setName_sj(str.substr(0, pos)); //set name

		str.erase(0, pos + 1);
		s.setNumberOfCredits(atoi(str.substr(0).c_str())); //set number of credits
		ListSubject.push_back(s);//add vào list
	}
	fileSubject.close();
	return 0;
}

