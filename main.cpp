#include <iostream>
#include "user.h"
#include "admin.h"
#include "teacher.h"
#include "student.h"
#include "subject.h"
#include "object.h"
#include "course.h"
using namespace std;

int main() {
	vector<users> UserList;
	vector<teacher> TeacherList;
	vector<student> StudentList;
	vector<subject> SubjectList;
	vector<object> ObjectList;
	vector<course> CourseList;
	//Load file user vào list
	int checkLoadUser = LoadAccoutUser((char*)"user.csv", UserList);
	if (checkLoadUser == -1) {
		cout << "File user not found !" << endl;
		system("pause");
		return 0;
	}

	//Load file teacher
	int checkLoadTeacherList = LoadInfo_Teacher((char*)"teacher.csv", TeacherList);
	if (checkLoadTeacherList == -1) {
		cout << "File teacher not found !" << endl;
		system("pause");
		return 0;
	}
	
	//Load file student
	int checkLoadStudentList = LoadInfo_Student((char*)"student.csv", StudentList);
	if (checkLoadStudentList == -1) {
		cout << "File teacher not found !" << endl;
		system("pause");
		return 0;
	}

	//Load file subject
	int checkLoadFileSubject = LoadInfo_Subject((char*)"subject.csv", SubjectList);
	if (checkLoadFileSubject == -1) {
		cout << "File subject not found !" << endl;
		system("pause");
		return 0;
	}

	int checkLoadFileObject = LoadFileObject((char*)"object.csv", ObjectList);
	if (checkLoadFileObject == -1) {
		cout << "File object not found !" << endl;
		system("pause");
		return 0;
	}

	int checkLoadFileCourse = LoadFileCourse((char*)"course.csv", CourseList);
	if (checkLoadFileCourse == -1) {
		cout << "File course not found !" << endl;
		system("pause");
		return 0;
	}

	users u;
	ReLogin: u = Login(UserList); // Tại đây return user khi đăng nhập thành công

	//Đăng nhập thất bại
	if (u.getRole() == -1) {
		system("pause");
		return 0;
	}

	if (u.getRole() == ADMIN) {
		admin a;
		a.setAccount(u.getAccount());
		a.setPassWord(u.getPassWord());
		a.setRole(u.getRole());
		a.ShowOption_Admin();
		int choice = option_admin(a, UserList, TeacherList, StudentList, SubjectList, ObjectList);
		if (choice == LOGOUT) {
			goto ReLogin;
		}
		else if (choice == EXIT) {
			system("pause");
			return 0;
		}
	}

	if (u.getRole() == TEACHER) {
		teacher t;
		t.setAccount(u.getAccount());
		t.setPassWord(u.getPassWord());
		t.setRole(u.getRole());
		t.ShowOption_Teacher(t.getAccount());
		int choice = option_teacher(t, UserList, TeacherList, CourseList, SubjectList, ObjectList);
		if (choice == LOGOUT) {
			goto ReLogin;
		}
		else if (choice == EXIT) {
			system("pause");
			return 0;
		}
	}

	if (u.getRole() == STUDENT) {
		student st;
		st.setAccount(u.getAccount());
		st.setPassWord(u.getPassWord());
		st.setRole(u.getRole());
		st.ShowOption_Student(st.getAccount());
		int choice = option_student(st, UserList, StudentList, CourseList, SubjectList, ObjectList);
		if (choice == LOGOUT) {
			goto ReLogin;
		}
		else if (choice == EXIT) {
			system("pause");
			return 0;
		}
	}
	
	system("pause");
	return 0;
}
