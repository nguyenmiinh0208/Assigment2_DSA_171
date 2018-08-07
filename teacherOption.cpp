#include "teacher.h"
#include <iomanip>
using namespace std;

void teacher::ShowOption_Teacher(string acc) {
	cout << "--------------------------------FACULTY: " << acc << "------------------------------------------" << endl;
	cout << setiosflags(ios::left) << setw(30) << "1. Change PassWord";
	cout << setiosflags(ios::left) << setw(30) << "2. View My Coures";
	cout << setiosflags(ios::left) << setw(30) << "3. Open Course" << endl;
	cout << setiosflags(ios::left) << setw(30) << "4. Summarize & Modify Score";
	cout << setiosflags(ios::left) << setw(30) << "5. Logout";
	cout << setiosflags(ios::left) << setw(30) << "6. Exit" << endl;
}

void teacher::ViewMyCourse(vector<course> &courseList) {
	cout << "---------------------------------------------------MY COURSE-------------------------------------------------------" << endl;
	cout << setiosflags(ios::left) << setw(15) << "Course ID";
	cout << setiosflags(ios::left) << setw(35) << "Subject";
	cout << setiosflags(ios::left) << setw(25) << "Number of student";
	cout << setiosflags(ios::left) << setw(20) << "Slot";
	cout << setiosflags(ios::left) << setw(20) << "Semester";
	cout << endl;
	cout << "-------------------------------------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < courseList.size(); i++) {
		if (account == courseList[i].getIDteacher()) {
			cout << setiosflags(ios::left) << setw(15) << courseList[i].getCourse();
			cout << setiosflags(ios::left) << setw(35) << courseList[i].getNameSubject();
			cout << setiosflags(ios::left) << setw(25) << courseList[i].getN_student();
			cout << setiosflags(ios::left) << setw(20) << courseList[i].getSlot();
			cout << setiosflags(ios::left) << setw(20) << courseList[i].getSemesterID();
			cout << endl;
		}
	}
	return;
}

void ModiFy_FileCoure(char *fName, course c) {
	fstream fileCoure;
	fileCoure.open(fName, ios::app);
	
	fileCoure << c.getCourse() << "," << c.getIDteacher() << "," << c.getNameSubject() << ","
		<< c.getN_student() << "," << c.getSlot() << "," << c.getSemesterID() << "," << c.getState() << endl;

	fileCoure.close();
}

//Hàm này giúp nhận biết được đang ở học kì nào
int setSemeter(string &sem, string account, vector<course> &courseList) {
	for (int i = 0; i < courseList.size(); i++){
		if (account == courseList[i].getIDteacher()) sem = courseList[i].getSemesterID();// Lấy ra học kì hiện tại
	}
	//Nếu trong một học kì, số khóa học = 5 thì giảng viên không được đăng kí môn học
	int count_numberOfCourse = 0;
	for (int i = 0; i < courseList.size(); i++) {
		if (account == courseList[i].getIDteacher()) {
			if (sem == courseList[i].getSemesterID()) {
				count_numberOfCourse++;
			}
		}
	}

	//Trong trường hợp nếu số khóa học = 5 nhưng tất cả đã đều kết thúc thì giảng viên được phép mở môn học cho kì tiếp theo
	if (count_numberOfCourse == 5) {
		// Nếu trong 1 học kì, số khóa học == 5 và đều ở trạng thái disable (tức là đã kết thúc khóa học) thì giảng viên mới được mở môn học
		bool check = true;
		for (int i = 0; i < courseList.size(); i++) {
			if (account == courseList[i].getIDteacher()) {
				if (sem == courseList[i].getSemesterID()) {
					if (courseList[i].getState() == UNABLE) {
						check = false;
						break;
					}
					//Tức là vẫn còn khóa học chưa kết thúc, nên giảng viên vẫn chưa được mở môn học cho học kì tiếp theo
				}
			}
		}
		if (check == false) return -1; //Thông báo rằng là giảng viên vẫn chưa được mở môn học (trường hợp 1) vì đã đủ 5 môn học
		else return 1; //Thông báo rằng giảng viên được phép mở môn học cho học kì tiếp theo (trường hợp 2) -> update học kì
	}

	else if (count_numberOfCourse < 5) {	
		//Nếu số khóa học trong kì hiện tại < 5 thì sẽ có 3 trường hợp:
		//1: Tất cả khóa học đều đã kết thúc (DISABLE) thì mới được mở môn học cho kì tiếp theo -> update học kì
		//2: Nếu trong số đó vẫn còn khóa học chưa kết thúc (UNABLE) thì vẫn chưa được mở môn học mới
		//3: Nếu tất cả đang ở trạng thái đang mở (UNABLE) thì giảng viên vẫn được tiếp tục mở môn học trong kì đó
		bool checkDisable = true;
		for (int i = 0; i < courseList.size(); i++) {
			if (account == courseList[i].getIDteacher()) {
				if (sem == courseList[i].getSemesterID()) {
					if (courseList[i].getState() == UNABLE) {
						checkDisable = false;
						break;
					}
					//Tức là vẫn còn khóa học chưa kết thúc, nên giảng viên vẫn chưa được mở môn học cho học kì tiếp theo
				}
			}
		}


		bool checkUnable = true;
		for (int i = 0; i < courseList.size(); i++) {
			if (account == courseList[i].getIDteacher()) {
				if (sem == courseList[i].getSemesterID()) {
					if (courseList[i].getState() == DISABLE) {
						checkUnable = false;
						break;
					}
				}
			}
		}
		if (checkDisable) return 2; //Thông báo rằng là giảng viên được mở môn học cho kì tiếp theo -> update học kì
		if (!checkDisable && checkUnable) return 3; //Thông báo rằng là giảng viên được mở môn học cho kì hiện tại
		if (!checkDisable && !checkUnable) return -3; //Thông báo rằng là giảng viên không được mở môn học cho kì tiếp theo bởi vì học kì chưa kết thúc
	}
}

string UpdateSemester(string &semester) {
	string ss;
	if (semester[semester.length() - 1] == '1') {
		int ssNum = atoi(semester.c_str());
		ssNum++;
		stringstream a;
		a << ssNum;
		ss = a.str();
	}
	else if (semester[semester.length() - 1] = '2') {
		int ssNum = atoi(semester.c_str());
		ssNum += 9;
		stringstream a;
		a << ssNum;
		ss = a.str();
	}

	return ss;
}

void open_course(vector<subject> &SjList, vector<course> &courseList, string &acc, string &strS) {
	string code;
	string nameSubject;
	while (true) {
		cout << "Enter Subject code: "; cin >> code;
		bool checkExist = false; // KIểm tra xem mã môn học người dùng nhập có trong danh sách môn học hay không
		for (int i = 0; i < SjList.size(); i++) {
			if (code == SjList[i].getIDSubject()) {
				checkExist = true;
				nameSubject = SjList[i].getNameSubject();
			}
		}
		if (checkExist) break;
		else {
			cout << "The subject does not exist ! ";
			cout << "Continue (Y/N) ?" << endl;
			string ch;
			while (true) {
				cin >> ch;
				if (ch == "Y" || ch == "y" || ch == "N" || ch == "n") break;
				else {
					cout << "Invalid charracter" << endl;
					continue;
				}
			}
			if (ch == "Y" || ch == "y") continue;
			else if (ch == "N" || ch == "n") return;
		}
	}

	cout << "Are you sure want to open the course ? (Y/N)" << endl;
	string k;
	while (true) {
		cin >> k;
		if (k == "Y" || k == "y" || k == "N" || k == "n") break;
		else {
			cout << "Invalid charracter" << endl;
			continue;
		}
	}
	if (k == "Y" || k == "y") {
		course c;
		c.setCourseID(code);
		c.setIDteacher(acc);
		c.setNameSubject(nameSubject);
		c.setN_student(MIN_N_STUDENT);
		UpdateSemester(strS);
		c.setSemester_ID(strS);
		c.setSlot(MAX_SLOT);
		c.setState(UNABLE);
		courseList.push_back(c);
		ModiFy_FileCoure((char*)"course.csv", c);
		cout << "Open course successfully..." << endl;
	}
	else if (k == "N" || k == "n") return;
}

void teacher::OpenCourse(vector<subject> &SjList, vector<course> &courseList, vector<object> &ObjectList) {
	cout << "1) Show list of subject." << endl;
	cout << "2) Search for subjects." << endl;
	cout << "3) Exit" << endl;
	string choice;
	while (true) {
		cout << "Your choice: ";
		cin >> choice;
		if (choice == "1" || choice == "2" || choice == "3") break;
		else {
			cout << "Invalid value ! Continue ? (Y/N) ";
			string ch;
			while (true) {
				cin >> ch;
				if (ch == "Y" || ch == "y" || ch == "N" || ch == "n") break;
				else {
					cout << "Invalid charracter" << endl;
					continue;
				}
			}
			if (ch == "Y" || ch == "y") continue;
			else if (ch == "N" || ch == "n") return;
		}
	}
	if (choice == "1") {
		cout << "------------------------------------LIST SUBJECT--------------------------------------" << endl;
		cout << setiosflags(ios::left) << setw(25) << "Subject code";
		cout << setiosflags(ios::left) << setw(35) << "Name";
		cout << setiosflags(ios::left) << setw(40) << "Number of credits";
		cout << endl;
		cout << "--------------------------------------------------------------------------------------" << endl;
		for (int i = 0; i < SjList.size(); i++) {
			cout << setiosflags(ios::left) << setw(25) << SjList[i].getIDSubject();
			cout << setiosflags(ios::left) << setw(35) << SjList[i].getNameSubject();
			cout << setiosflags(ios::left) << setw(40) << SjList[i].getNumberOfCredits();
			cout << endl;
		}
		cout << "--------------------------------------------------------------------------------------" << endl;
		cout << "Open course ? (Y/N)";
		string ch;
		while (true) {
			cin >> ch;
			if (ch == "Y" || ch == "y" || ch == "N" || ch == "n") break;
			else {
				cout << "Invalid charracter" << endl;
				continue;
			}
		}
		if (ch == "Y" || ch == "y") {
			//Tiến hành đếm số khóa học hiện tại giảng viên đang có
			//Trong 1 học kì, giảng viên chỉ có thể mở tối đa 5 môn học
			string strS;
			//Giảng viên đã mở số môn học >=5
			int checkState = setSemeter(strS, account, courseList);
			if (checkState == -1) {
				cout << "Your current course number in semester " << strS << " is 5" << endl;
				cout << "You can not open courses." << endl;
			}
			else if (checkState == 1 || checkState == 2) {
				//Được phép mở môn học cho học kì tiếp theo
				strS = UpdateSemester(strS);
				open_course(SjList, courseList, account, strS);
			}
			else if (checkState == 3) {
				//Được phép mở môn học ở học kì hiện tại
				open_course(SjList, courseList, account, strS);
			}
			else if (checkState == -2 || checkState == -3) {
				cout << "The current semester has not ended." << endl;
				cout << "You can not open courses." << endl;
			}
		}
		else if (ch == "N" || ch == "n") return;
	}
	else if (choice == "2") {
		cout << "Enter code of subject: ";
		string code; cin >> code;
		cout << setiosflags(ios::left) << setw(25) << "ID of subject";
		cout << setiosflags(ios::left) << setw(35) << "Name subject";
		cout << setiosflags(ios::left) << setw(40) << "Number of credits";
		cout << endl;
		bool check = false;
		string nameSubject;
		for (int i = 0; i < SjList.size(); i++) {
			if (code == SjList[i].getIDSubject()) {
				check = true;
				nameSubject = SjList[i].getNameSubject();
				cout << setiosflags(ios::left) << setw(25) << SjList[i].getIDSubject();
				cout << setiosflags(ios::left) << setw(35) << SjList[i].getNameSubject();
				cout << setiosflags(ios::left) << setw(40) << SjList[i].getNumberOfCredits();
				cout << endl;
				break;
			}
		}

		if (check) {
			cout << "Are you sure want to open the course ? (Y/N)" << endl;
			string ch;
			while (true) {
				cin >> ch;
				if (ch == "Y" || ch == "y" || ch == "N" || ch == "n") break;
				else {
					cout << "Invalid charracter" << endl;
					continue;
				}
			}
			if (ch == "Y" || ch == "y") {
				string strS;
				//Giảng viên đã mở số môn học >=5
				int checkState = setSemeter(strS, account, courseList);
				if (checkState == -1) {
					cout << "Your current course number in semester " << strS << " is 5" << endl;
					cout << "You can not open courses." << endl;
				}
				else if (checkState == 1 || checkState == 2) {
					//Được phép mở môn học cho học kì tiếp theo
					strS = UpdateSemester(strS);
					cout << "Are you sure want to open the course ? (Y/N)" << endl;
					string k;
					while (true) {
						cin >> ch;
						if (k == "Y" || k == "y" || k == "N" || k == "n") break;
						else {
							cout << "Invalid charracter" << endl;
							continue;
						}
					}
					if (k == "Y" || k == "y") {
						course c;
						c.setCourseID(code);
						c.setIDteacher(account);
						c.setNameSubject(nameSubject);
						c.setN_student(MIN_N_STUDENT);
						UpdateSemester(strS);
						c.setSemester_ID(strS);
						c.setSlot(MAX_SLOT);
						c.setState(UNABLE);
						courseList.push_back(c);
						ModiFy_FileCoure((char*)"course.csv", c);
						cout << "Open course successfully..." << endl;
					}
					else if (k == "N" || k == "n") return;
				}
				else if (checkState == 3) {
					//Được phép mở môn học ở học kì hiện tại
					cout << "Are you sure want to open the course ? (Y/N)" << endl;
					char ch; cin >> ch;
					if (ch == 'Y' || ch == 'y') {
						course c;
						c.setCourseID(code);
						c.setIDteacher(account);
						c.setNameSubject(nameSubject);
						c.setN_student(MIN_N_STUDENT);
						UpdateSemester(strS);
						c.setSemester_ID(strS);
						c.setSlot(MAX_SLOT);
						c.setState(UNABLE);
						courseList.push_back(c);
						ModiFy_FileCoure((char*)"course.csv", c);
						cout << "Open course successfully..." << endl;
					}
					else if (ch == 'N' || ch == 'n') return;
				}
				else if (checkState == -2 || checkState == -3) {
					cout << "The current semester has not ended." << endl;
					cout << "You can not open courses." << endl;
				}
			}
			else if (ch == "N" || ch == "n") return;
		}
		else {
			cout << "The subject does not exist." << endl;
		}
	}
	else if (choice == "3") return;
	system("pause");
}

//Giảng viên có thể trực tiếp chỉnh sửa và điểm tổng kết sẽ tự động cập nhật
void teacher::SummaryScore(vector<course> &courseList, vector<object> &ObjectList) {
	cout << "1. Summary score" << "\t\t\t" << "2. Exit" << endl;
	string choice;
	while (true) {
		cout << "Your choice: ";
		cin >> choice;
		if (choice == "1" || choice == "2") break;
		else {
			cout << "Invalid value ! Continue ? (Y/N) ";
			string ch;
			while (true) {
				cin >> ch;
				if (ch == "Y" || ch == "y" || ch == "N" || ch == "n") break;
				else {
					cout << "Invalid charracter" << endl;
					continue;
				}
			}
			if (ch == "Y" || ch == "y") continue;
			else if (ch == "N" || ch == "n") return;
		}
	}
	if (choice == "1") {
		ViewMyCourse(courseList);
		cout << "Continue ? (Y/N) " << endl;
		string ch;
		while (true) {
			cin >> ch;
			if (ch == "Y" || ch == "y" || ch == "N" || ch == "n") break;
			else {
				cout << "Invalid charracter" << endl;
				continue;
			}
		}
		if (ch == "Y" || ch == "y") {
			string code, nameSubject;
			int n_student = 0;
			while (true) {
				cout << "Enter course id: "; cin >> code;
				bool checkExist = false; // KIểm tra xem mã môn học người dùng nhập có trong danh sách môn học hay không
				for (int i = 0; i < courseList.size(); i++) {
					if (code == courseList[i].getCourse() && account == courseList[i].getIDteacher()) {
						n_student = courseList[i].getN_student();
						checkExist = true;
						nameSubject = courseList[i].getNameSubject();
					}
				}
				if (checkExist) break;
				else {
					cout << "The course does not exist ! ";
					cout << "Continue (Y/N) ?" << endl;
					string ch;
					while (true) {
						cin >> ch;
						if (ch == "Y" || ch == "y" || ch == "N" || ch == "n") break;
						else {
							cout << "Invalid charracter" << endl;
							continue;
						}
					}
					if (ch == "Y" || ch == "y") continue;
					else if (ch == "N" || ch == "n") return;
				}
			}

			cout << "----------------------------------------- " << code << ": " << nameSubject << " ----------------------------------------" << endl;
			cout << setiosflags(ios::left) << setw(20) << "Student ID";
			cout << setiosflags(ios::left) << setw(20) << "Mid-term test";
			cout << setiosflags(ios::left) << setw(20) << "Assignment";
			cout << setiosflags(ios::left) << setw(20) << "Final test";
			cout << setiosflags(ios::left) << setw(20) << "Summary Score";
			cout << setiosflags(ios::left) << setw(20) << "Semester ID";
			cout << endl;
			for (int i = 0; i < ObjectList.size(); i++) {
				if (code == ObjectList[i].getCourse_id() && account == ObjectList[i].gettID_teacher()) {
					cout << setiosflags(ios::left) << setw(20) << ObjectList[i].getID_student();
					cout << setiosflags(ios::left) << setw(20) << ObjectList[i].getMid_Score();
					cout << setiosflags(ios::left) << setw(20) << ObjectList[i].getAssignment_Score();
					cout << setiosflags(ios::left) << setw(20) << ObjectList[i].getFinalScore();
					cout << setiosflags(ios::left) << setw(20) << ObjectList[i].getAverage_score();
					cout << setiosflags(ios::left) << setw(20) << ObjectList[i].getSemeter_ID();
					cout << endl;
				}
			}

			if (n_student > 0) {
				cout << "Summary or modify ? (Y/N) ";
				string ch;
				while (true) {
					cin >> ch;
					if (ch == "Y" || ch == "y" || ch == "N" || ch == "n") break;
					else {
						cout << "Invalid charracter" << endl;
						continue;
					}
				}
				if (ch == "Y" || ch == "y") {
					string id;
					while (true) {
						cout << "Enter the student id: ";  cin >> id;
						bool check = false;
						for (int i = 0; i < ObjectList.size(); i++) {
							if (id == ObjectList[i].getID_student() && code == ObjectList[i].getCourse_id()) {
								check = true;
								break;
							}
						}

						if (check) break;
						else {
							cout << "The student id does not exist." << endl;
							continue;
						}
					}

					for (int i = 0; i < ObjectList.size(); i++) {
						if (id == ObjectList[i].getID_student() && code == ObjectList[i].getCourse_id() && account == ObjectList[i].gettID_teacher()) {
							cout << setiosflags(ios::left) << setw(20) << ObjectList[i].getID_student();
							cout << setiosflags(ios::left) << setw(20) << ObjectList[i].getMid_Score();
							cout << setiosflags(ios::left) << setw(20) << ObjectList[i].getAssignment_Score();
							cout << setiosflags(ios::left) << setw(20) << ObjectList[i].getFinalScore();
							cout << setiosflags(ios::left) << setw(20) << ObjectList[i].getAverage_score();
							cout << setiosflags(ios::left) << setw(20) << ObjectList[i].getSemeter_ID();
							if (ObjectList[i].getMid_Score() == -1 || ObjectList[i].getAssignment_Score() == -1 || ObjectList[i].getFinalScore() == -1) {
								cout << "You cannot summary score, because not enough values." << endl;
								cout << "Do you want to update score ? (Y/N) " << endl;
								string k;
								while (true) {
									cin >> k;
									if (k == "Y" || k == "y") break;
									else if (k == "N" || k == "n") 	return;
									else {
										cout << "Invalid charracter" << endl;
										continue;
									}
								}

								cout << "1. Mid-term test" << endl;
								cout << "2. Assignment" << endl;
								cout << "3. Final test" << endl;
								cout << endl;

								while (true) {
									string choice;
									cout << "Choose colums to update: ";
									while (true) {
										cin >> choice;
										if (choice == "1" || choice == "2" || choice == "3") break;
										else {
											cout << "Invalid value" << endl;
											continue;
										}
									}

									double sc;
									cout << "Enter score: ";
									while (true) {
										cin >> sc;
										if (sc >= 0 && sc <= 10) break;
										else {
											cout << "Invalid value" << endl;
											continue;
										}
									}

									if (choice == "1") ObjectList[i].setMidSCore(sc); 	//cập nhật điểm giữa kì
									else if (choice == "2") ObjectList[i].setAssignment_Score(sc);
									else if (choice == "3") ObjectList[i].setFinalScore(sc);

									if (ObjectList[i].getMid_Score() != -1 && ObjectList[i].getAssignment_Score() != -1 && ObjectList[i].getFinalScore() != -1) {
										double average = 0.3*ObjectList[i].getMid_Score() + 0.2*ObjectList[i].getAssignment_Score() + 0.5*ObjectList[i].getFinalScore();
										ObjectList[i].setAverage_score(average);
										cout << "Update successfully" << endl;
										break;
									}
									else {
										cout << "Would you like to keep updating ? (Y/N)" << endl;
										string k;
										while (true) {
											cin >> k;
											if (k == "Y" || k == "y") break;
											else if (k == "N" || k == "n") {
												system("pause");
												return;
											}
											else {
												cout << "Invalid charracter" << endl;
												continue;
											}
										}
										continue;
									}
								}
							}

							//Nếu đã đủ 3 cột điểm nhưng vẫn chưa có điểm tổng kết thì cập nhật điểm tổng kết
							else if (ObjectList[i].getAverage_score() == -1) {
								double average = 0.3*ObjectList[i].getMid_Score() + 0.2*ObjectList[i].getAssignment_Score() + 0.5*ObjectList[i].getFinalScore();
								ObjectList[i].setAverage_score(average);
								cout << "Update successfully" << endl;
							}

							//Nếu đã đủ 4 cột điểm nhưng muốn chỉnh sửa thì tiếp tụp update
							else {
								cout << "1. Mid-term test" << endl;
								cout << "2. Assignment" << endl;
								cout << "3. Final test" << endl;
								cout << endl;

								while (true) {
									string choice;
									while (true) {
										cout << "Choose colums to update: ";  cin >> choice;
										if (choice == "1" || choice == "2" || choice == "3") break;
										else {
											cout << "Invalid value" << endl;
											continue;
										}
									}

									double sc;
									while (true) {
										cout << "Enter score: ";  cin >> sc;
										if (sc >= 0 && sc <= 10) break;
										else {
											cout << "Invalid value" << endl;
											continue;
										}
									}

									if (choice == "1") ObjectList[i].setMidSCore(sc); 	//cập nhật điểm giữa kì
									else if (choice == "2") ObjectList[i].setAssignment_Score(sc);
									else if (choice == "3") ObjectList[i].setFinalScore(sc);

									if (ObjectList[i].getMid_Score() != -1 && ObjectList[i].getAssignment_Score() != -1 && ObjectList[i].getFinalScore() != -1) {
										double average = 0.3*ObjectList[i].getMid_Score() + 0.2*ObjectList[i].getAssignment_Score() + 0.5*ObjectList[i].getFinalScore();
										ObjectList[i].setAverage_score(average);
										cout << "Update successfully" << endl;
										break;
									}
									else {
										cout << "Would you like to keep updating ? (Y/N)" << endl;
										string k;
										while (true) {
											cin >> k;
											if (k == "Y" || k == "y") break;
											else if (k == "N" || k == "n") {
												system("pause");
												return;
											}
											else {
												cout << "Invalid charracter" << endl;
												continue;
											}
										}
										continue;
									}
								}
							}
							break;
						}
					}

					//Cập nhật lại file object
					fstream fileObject;
					fileObject.open("tmp.csv", ios::out);

					fileObject << "course_id,id_student,id_teacher,midterm_test,assignment,final_test,summary_score,semester_id" << endl;
					for (int i = 0; i < ObjectList.size(); i++) {
						fileObject << ObjectList[i].getCourse_id() << ",";
						fileObject << ObjectList[i].getID_student() << ",";
						fileObject << ObjectList[i].gettID_teacher() << ",";
						fileObject << ObjectList[i].getMid_Score() << ",";
						fileObject << ObjectList[i].getAssignment_Score() << ",";
						fileObject << ObjectList[i].getFinalScore() << ",";
						fileObject << ObjectList[i].getAverage_score() << ",";
						fileObject << ObjectList[i].getSemeter_ID() << endl;
					}

					fileObject.close();
					remove("object.csv");
					rename("tmp.csv", "object.csv");
				}
				else if (ch == "N" || ch == "n") return;
			}
			else {
				cout << "No students" << endl;
			}
		}
		else if (ch == "N" || ch == "n") return;
	}
	else if (choice == "2") return;
	system("pause");
}