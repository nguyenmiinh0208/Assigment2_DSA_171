#include "student.h"
#include "teacher.h"
#include "user.h"
#include "admin.h"
#include <iostream>

using namespace std;

int option_admin(admin &a, vector<users> &ListUser, vector<teacher> &TList, vector<student> &StList, vector<subject> &SubjectList, vector<object> &objectList) {
	while (true) {
		char ch;
		cin >> ch;

		switch (ch) {
		case '1': {
			a.showUser(ListUser);
			system("cls");
			a.ShowOption_Admin();
			break;
		}
		case '2': {
			a.Search_User(ListUser, TList, StList);
			system("cls");
			a.ShowOption_Admin();
			break;
		}
		case '3': {
			a.Add_Users(ListUser, TList, StList);
			system("cls");
			a.ShowOption_Admin();
			break;
		}
		case '4': {
			a.Delete_Users(ListUser, TList, StList);
			system("cls");
			a.ShowOption_Admin();
			break;
		}

		case '5': {
			a.ChangePassWord(ListUser);
			system("cls");
			a.ShowOption_Admin();
			break;
		}
		case '6': {
			a.Multiple_Delete(ListUser, StList, SubjectList, objectList);
			system("cls");
			a.ShowOption_Admin();
			break;
		}
		case 'l': return LOGOUT;
		case '7': return LOGOUT;
		case '8': return EXIT;
		case 'q': return EXIT;
		default:
			cout << "Invalid selection !" << endl;
			continue;
		}
	}
}

int option_teacher(teacher &t, vector<users> &ListUser, vector<teacher> &TList, vector<course> &CList, vector<subject> &SjList, vector<object> &ObjectList) {
	while (true) {
		char ch;
		cin >> ch;

		switch (ch)
		{
		case '1': {
			t.ChangePassWord(ListUser);
			system("cls");
			t.ShowOption_Teacher(t.getAccount());
			break;
		}
		case '2': {
			t.ViewMyCourse(CList);
			system("pause");
			system("cls");
			t.ShowOption_Teacher(t.getAccount());
			break;
		}
		case '3': {
			t.OpenCourse(SjList, CList, ObjectList);
			system("cls");
			t.ShowOption_Teacher(t.getAccount());
			break;
		}
		case '4': {
			t.SummaryScore(CList, ObjectList);
			system("cls");
			t.ShowOption_Teacher(t.getAccount());
			break;
		}	
		case '5': return LOGOUT;
		case 'l': return LOGOUT;
		case '6': return EXIT;
		default:
			cout << "Invalid selection !" << endl;
			continue;
		}
	}
}

int option_student(student &st, vector<users> &ListUser, vector<student> &StList, vector<course> &CList, vector<subject> &SjList, vector<object> &ObjectList) {
	while (true) {
		char ch;
		cin >> ch;

		switch (ch)
		{
		case '1': {
			st.ChangePassWord(ListUser);
			system("cls");
			st.ShowOption_Student(st.getAccount());
			break;
		}
		case '2': {
			st.ViewMyCoure(ObjectList, SjList, CList);
			system("cls");
			st.ShowOption_Student(st.getAccount());
			break;
		}
		case '3': {
			st.JoinCoure(CList, ObjectList, SjList);
			system("cls");
			st.ShowOption_Student(st.getAccount());
			break;
		}
		case '4': {
			st.CancelCoure(CList, ObjectList, SjList);
			system("cls");
			st.ShowOption_Student(st.getAccount());
			break;
		}
		case '5': return LOGOUT;
		case 'l': return LOGOUT;
		case '6': return EXIT;
		case 'q': return EXIT;
		default:
			cout << "Invalid selection !" << endl;
			continue;
		}
	}
}