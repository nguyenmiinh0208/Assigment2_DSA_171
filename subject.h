#ifndef SUBJECT_H
#define SUBJECT_H

#include "user.h"
using namespace std;

class subject {
private:
	string id_subject;
	string name_subject;
	int credits;
public:
	subject() {
		id_subject = "";
		name_subject = "";
		credits = -1;
	}
	~subject() {};
	void setID(string id);
	void setName_sj(string name_sj);
	void setNumberOfCredits(int credits);

	string getIDSubject();
	string getNameSubject();
	int getNumberOfCredits();
};

int LoadInfo_Subject(char *fName, vector<subject> &ListSubject);
#endif // !SUBJECT_H

