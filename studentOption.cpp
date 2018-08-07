#include "student.h"
using namespace std;

void student::ShowOption_Student(string acc) {
	cout << "-----------------------------------------------STUDENT: " << acc << "-----------------------------------------------------" << endl;
	cout << setiosflags(ios::left) << setw(30) << "1. Change PassWord";
	cout << setiosflags(ios::left) << setw(30) << "2. View My Coures";
	cout << setiosflags(ios::left) << setw(30) << "3. Join course" << endl;
	cout << setiosflags(ios::left) << setw(30) << "4. Canceled course";
	cout << setiosflags(ios::left) << setw(30) << "5. Logout";
	cout << setiosflags(ios::left) << setw(30) << "6. Exit" << endl;
}

//Hàm chuyển chữ hoa sang thường
string To_Lower(string str) {
	string s;
	for (int i = 0; i < str.length(); i++) {
		char k;
		if (str[i] >= 'A' && str[i] <= 'Z') {
			k = char(int(str[i]) + 32);
			s += k;
		}
		else s += str[i];
	}
	return s;
}

//Đăng kí môn học
//Có 2 lựa chọn là show ra màn hình tất cả các khóa học được giảng viên mở và tìm kiểm 1 lúc nhiều môn học theo tên
//Sinh viên có thể đăng kí môn học với điều kiện tối đa 20 tín chỉ trong 1 học kì và khóa học đó vẫn còn slot (chưa full)
void student::JoinCoure(vector<course> &courseList, vector<object> &ObjectList, vector<subject> &SubjectList) {
	cout << "--------------------------------------------------JOIN COURSE-----------------------------------------------------" << endl;
	cout << setiosflags(ios::left) << setw(30) << "1. Show list course";
	cout << setiosflags(ios::left) << setw(30) << "2. Search subject";
	cout << setiosflags(ios::left) << setw(30) << "3. Exit" << endl;
	string choice;
	while (true) {
		cout << "Your choice: "; cin >> choice;
		if (choice == "1" || choice == "2" || choice == "3") break;
		else {
			cout << "Invalid value" << endl;
			continue;
		}
	}
	//Tiến hành kiểm tra số tín chỉ mà sinh viên đã đăng kí trong một học kì
	//Kiểm tra xem học kì của sinh viên đã bắt đầu hay chưa
	int numberOfCredits = 0;
	string semester, course_tmp;
	for (int i = 0; i < ObjectList.size(); i++) {
		if (account == ObjectList[i].getID_student()) {
			if (ObjectList[i].getAverage_score() == -1) {
				course_tmp = ObjectList[i].getCourse_id();
				break;
			}
		}
	}
	for (int i = 0; i < courseList.size(); i++) {
		if (courseList[i].getCourse() == course_tmp && courseList[i].getState() == UNABLE) {
			semester = courseList[i].getSemesterID();
		}
	}

	//Điểm trung bình các môn đăng kí trong học kì phải đồng thời = -1 (tức là học kì đó chưa bắt đầu)
	//Nếu 1 trong các môn đã có điểm (học kì đã bắt đầu) thì sinh viên không được phép đăng kí môn học
	bool checkSemester = true;
	for (int i = 0; i < ObjectList.size(); i++) {
		if (account == ObjectList[i].getID_student() && ObjectList[i].getSemeter_ID() == semester) {
			if (ObjectList[i].getAssignment_Score() != -1 || ObjectList[i].getAverage_score() != -1 || ObjectList[i].getFinalScore() != -1 || ObjectList[i].getMid_Score() != -1) {
				checkSemester = false;
			}
		}
	}

	for (int i = 0; i < ObjectList.size(); i++) {
		if (account == ObjectList[i].getID_student() && ObjectList[i].getSemeter_ID() == semester) {
			for (int j = 0; j < SubjectList.size(); j++) {
				if (SubjectList[j].getIDSubject() == ObjectList[i].getCourse_id()) {
					int n = SubjectList[j].getNumberOfCredits();
					numberOfCredits += n;
					break;
				}
			}
		}
	}

	//Lựa chọn show ra tất cả những khóa học hiện tại đang được mở
	if (choice == "1") {
		cout << setiosflags(ios::left) << setw(15) << "Course ID";
		cout << setiosflags(ios::left) << setw(35) << "Subject";
		cout << setiosflags(ios::left) << setw(25) << "Number of student";
		cout << setiosflags(ios::left) << setw(20) << "Slot";
		cout << endl;
		cout << "-------------------------------------------------------------------------------------------------------------------" << endl;
		for (int i = 0; i < courseList.size(); i++) {
			if (courseList[i].getState() == UNABLE) {
				cout << setiosflags(ios::left) << setw(15) << courseList[i].getCourse();
				cout << setiosflags(ios::left) << setw(35) << courseList[i].getNameSubject();
				cout << setiosflags(ios::left) << setw(25) << courseList[i].getN_student();
				cout << setiosflags(ios::left) << setw(20) << courseList[i].getSlot();
				cout << endl;
			}
		}

		cout << "Join course ? (Y/N) ";
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
			if (checkSemester) {
				string strIDCourse;
				int pos;
				while (true) {
					cout << "Enter course id: "; cin >> strIDCourse;
					bool checkExist = false; // KIểm tra xem mã môn học người dùng nhập có trong danh sách môn học hay không
					for (int i = 0; i < courseList.size(); i++) {
						if (strIDCourse == courseList[i].getCourse()) {
							pos = i;
							checkExist = true;
						}
					}
					if (checkExist) break;
					else {
						cout << "The course does not exist ! ";
						cout << "Continue (Y/N) ?" << endl;
						char k; cin >> k;
						if (k == 'Y' || k == 'y') continue;
						else if (k == 'N' || k == 'n') return;
					}
				}
				cout << "Are you sure want to join the course ? (Y/N)" << endl;

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
					if (checkSemester) {
						if (courseList[pos].getN_student() < courseList[pos].getSlot()) {
							int n = numberOfCredits;//Lấy số tín chỉ hiện tại
							for (int i = 0; i < SubjectList.size(); i++) {
								if (courseList[pos].getCourse() == SubjectList[i].getIDSubject()) {
									n += SubjectList[i].getNumberOfCredits();
									break;
								}
							}
							if (n <= 20) {
								int n = courseList[pos].getN_student(); n += 1;//Khi có sinh viên tham gia khóa học thì cập nhật số sinh viên trong khóa học đó
								courseList[pos].setN_student(n);

								//Cập nhật listObject
								object o;
								o.setCourse_id(courseList[pos].getCourse());
								o.setID_student(account);
								o.setID_teacher(courseList[pos].getIDteacher());
								o.setMidSCore(-1);
								o.setFinalScore(-1);
								o.setAssignment_Score(-1);
								o.setAverage_score(-1);
								o.setSemeter_ID(courseList[pos].getSemesterID());
								ObjectList.push_back(o);

								//Cập nhật file Object khi có sinh viên đăng kí khóa học
								fstream fileObject;
								fileObject.open("object.csv", ios::app);
								fileObject << courseList[pos].getCourse() << "," << account << "," << courseList[pos].getIDteacher() << ","
									<< -1 << "," << -1 << "," << -1 << "," << -1 << "," << courseList[pos].getSemesterID() << endl;
								fileObject.close();

								//Cập nhật file khóa học
								fstream fileCourse;
								fileCourse.open("tmp.csv", ios::out);
								fileCourse << "Course_ID" << "," << "Teacher_ID" << "," << "Name" << "," << "n_student" << "," << "slot" << "," << "semesterID" << "," << "state" << endl;
								for (int i = 0; i < courseList.size(); i++) {
									fileCourse << courseList[i].getCourse() << ","
										<< courseList[i].getIDteacher() << "," << courseList[i].getNameSubject() << ","
										<< courseList[i].getN_student() << "," << courseList[i].getSlot() << ","
										<< courseList[i].getSemesterID() << "," << courseList[i].getState() << endl;
								}
								fileCourse.close();
								remove("course.csv");
								rename("tmp.csv", "course.csv");
								cout << "Join course successfully..." << endl;
							}
							else {
								cout << "You can not join course. The maximum number of credits is 20" << endl;
							}

						}
						else {
							cout << "You can not join course because the course was full (" << courseList[pos].getN_student() << "/" << courseList[pos].getSlot() << ")" << endl;
						}
					}
				}
				if (ch == "N" || ch == "n") return;
			}
			else {
				cout << "The current semester has not ended." << endl;
				cout << "You can not join courses." << endl;
			}
		}
		else if (ch == "N" || ch == "n") return;
	}
	//Lựa chọn cho tìm kiếm 1 lúc nhiều môn học để có thể xem và đăng kí
	else if (choice == "2") {
		fflush(stdin);
		string nameSj = "";
		cout << "Please enter name subject to search: ";
		cin.ignore();
		getline(cin, nameSj);
		string strNameSubject = To_Lower(nameSj);
		cout << setiosflags(ios::left) << setw(15) << "Course ID";
		cout << setiosflags(ios::left) << setw(35) << "Subject";
		cout << setiosflags(ios::left) << setw(25) << "Number of Credits";
		cout << endl;
		bool checkSubject_exits = false; //kiểm tra môn học có tồn tại hay không
		for (int i = 0; i < SubjectList.size(); i++) {
			string s = SubjectList[i].getNameSubject();
			string ss = To_Lower(s);
			if (strstr(ss.c_str(), strNameSubject.c_str()) != NULL) {
				checkSubject_exits = true;
				cout << setiosflags(ios::left) << setw(15) << SubjectList[i].getIDSubject();
				cout << setiosflags(ios::left) << setw(35) << SubjectList[i].getNameSubject();
				cout << setiosflags(ios::left) << setw(25) << SubjectList[i].getNumberOfCredits();
				cout << endl;
				break;
			}
		}
		if (checkSubject_exits) {
			cout << "Join course ? (Y/N)" << endl;
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

				//Nếu học kì đã bắt đầu thì không được đăng kí
				if (checkSemester) {
					string strIDCourse;
					int pos;
					while (true) {
						cout << "Enter course id: "; cin >> strIDCourse;
						bool checkExist = false; // KIểm tra xem mã môn học người dùng nhập có trong danh sách môn học hay không
						for (int i = 0; i < courseList.size(); i++) {
							if (strIDCourse == courseList[i].getCourse()) {
								pos = i;
								checkExist = true;
							}
						}

						if (checkExist) {
							cout << setiosflags(ios::left) << setw(15) << "Course ID";
							cout << setiosflags(ios::left) << setw(35) << "Subject";
							cout << setiosflags(ios::left) << setw(25) << "Number of student";
							cout << setiosflags(ios::left) << setw(20) << "Slot";
							cout << endl;
							cout << "-------------------------------------------------------------------------------------------------------------------" << endl;
							cout << setiosflags(ios::left) << setw(15) << courseList[pos].getCourse();
							cout << setiosflags(ios::left) << setw(35) << courseList[pos].getNameSubject();
							cout << setiosflags(ios::left) << setw(25) << courseList[pos].getN_student();
							cout << setiosflags(ios::left) << setw(20) << courseList[pos].getSlot();
							cout << endl;
							break;
						}
						else {
							cout << "This course has not yet been opened ? Continue (Y/N) ?" << endl;
							char k; cin >> k;
							if (k == 'Y' || k == 'y') continue;
							else if (k == 'N' || k == 'n') return;
						}
					}
					cout << "Are you sure want to join the course ? (Y/N) " << endl;
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
						if (courseList[pos].getN_student() < courseList[pos].getSlot()) {
							//Tiến hành cập nhật số tín chỉ, nếu > 20 thì không được tham gia khóa học
							int n = numberOfCredits;//Lấy số tín chỉ hiện tại
							for (int i = 0; i < SubjectList.size(); i++) {
								if (courseList[pos].getCourse() == SubjectList[i].getIDSubject()) {
									n += SubjectList[i].getNumberOfCredits();
									break;
								}
							}
							if (n <= 20) {
								int n = courseList[pos].getN_student(); n += 1;//Khi có sinh viên tham gia khóa học thì cập nhật số sinh viên trong khóa học đó
								courseList[pos].setN_student(n);

								//Cập nhật listObject
								object o;
								o.setCourse_id(courseList[pos].getCourse());
								o.setID_student(account);
								o.setID_teacher(courseList[pos].getIDteacher());
								o.setMidSCore(-1);
								o.setFinalScore(-1);
								o.setAssignment_Score(-1);
								o.setAverage_score(-1);
								o.setSemeter_ID(courseList[pos].getSemesterID());
								ObjectList.push_back(o);

								//Cập nhật file Object khi có sinh viên đăng kí khóa học
								fstream fileObject;
								fileObject.open("object.csv", ios::app);
								fileObject << courseList[pos].getCourse() << "," << account << "," << courseList[pos].getIDteacher() << ","
									<< -1 << "," << -1 << "," << -1 << "," << -1 << "," << courseList[pos].getSemesterID() << endl;
								fileObject.close();

								//Cập nhật file khóa học
								fstream fileCourse;
								fileCourse.open("tmp.csv", ios::out);
								fileCourse << "Course_ID" << "," << "Teacher_ID" << "," << "Name" << "," << "n_student" << "," << "slot" << "," << "semesterID" << "," << "state" << endl;
								for (int i = 0; i < courseList.size(); i++) {
									fileCourse << courseList[i].getCourse() << ","
										<< courseList[i].getIDteacher() << "," << courseList[i].getNameSubject() << ","
										<< courseList[i].getN_student() << "," << courseList[i].getSlot() << ","
										<< courseList[i].getSemesterID() << "," << courseList[i].getState() << endl;
								}
								fileCourse.close();
								remove("course.csv");
								rename("tmp.csv", "course.csv");
								cout << "Join course successfully..." << endl;
							}
							else {
								cout << "You can not join course. The maximum number of credits is 20" << endl;
							}

						}
						else {
							cout << "You can not join course because the course was full (" << courseList[pos].getN_student() << "/" << courseList[pos].getSlot() << ")" << endl;
						}
					}
					else if (k == "N" || k == "n") return;
				}
				else {
					cout << "The current semester has not ended." << endl;
					cout << "You can not join courses." << endl;
				}
			}
			else if (ch == "N" || ch == "n") return;
		}
		else {
			cout << "This subject does not exist" << endl;
		}
	}
	else if (choice == "3") return;
	
	system("pause");
}

//Hủy môn học
//Tiến hành duyệt file object và xem thử khóa học nào chưa có điểm (tất cả cột điểm đều là -1) thì mới được phép hủy
//Nếu 1 trong 4 cột (khóa học đang diễn ra) hoặc tất cả đều đã có điểm (học kì đã kết thúc) thì không xuất ra màn hình để lựa chọn hủy khóa học
void student::CancelCoure(vector<course> &CourseList, vector<object> &ObjectList, vector<subject> &ListSubject) {
	cout << "--------------------------------------------------CANCEL COURSE-----------------------------------------------------" << endl;
	cout << "-------------------------------------------------MY CURRENT COURSES--------------------------------------------------" << endl;
	cout << setiosflags(ios::left) << setw(14) << "Course ID";
	cout << setiosflags(ios::left) << setw(35) << "Subject";
	cout << setiosflags(ios::left) << setw(10) << "Semester";
	cout << endl;
	bool check = false;
	for (int i = 0; i < ObjectList.size(); i++) {
		if (account == ObjectList[i].getID_student()) {
			if (ObjectList[i].getAverage_score() == -1 && ObjectList[i].getMid_Score() == -1 && ObjectList[i].getAssignment_Score() == -1 && ObjectList[i].getFinalScore() == -1) {
				check = true;
				cout << setiosflags(ios::left) << setw(14) << ObjectList[i].getCourse_id();
				for (int j = 0; j < ListSubject.size(); j++) {
					if (ObjectList[i].getCourse_id() == ListSubject[j].getIDSubject())
						cout << setiosflags(ios::left) << setw(35) << ListSubject[j].getNameSubject();
				}
				for (int j = 0; j < CourseList.size(); j++) {
					if (ObjectList[i].getCourse_id() == CourseList[j].getCourse()) {
						cout << setiosflags(ios::left) << setw(10) << CourseList[j].getSemesterID();
						break;
					}
				}
				cout << endl;
			}
			
		}
	}

	//Tiến hành kiểm tra số tín chỉ mà sinh viên đã đăng kí trong một học kì
	//Kiểm tra xem học kì của sinh viên đã bắt đầu hay chưa
	int numberOfCredits = 0;
	string semester, course_tmp;
	for (int i = 0; i < ObjectList.size(); i++) {
		if (account == ObjectList[i].getID_student()) {
			if (ObjectList[i].getAverage_score() == -1) {
				course_tmp = ObjectList[i].getCourse_id();
				break;
			}
		}
	}
	for (int i = 0; i < CourseList.size(); i++) {
		if (CourseList[i].getCourse() == course_tmp && CourseList[i].getState() == UNABLE) {
			semester = CourseList[i].getSemesterID();
		}
	}

	//Điểm trung bình các môn đăng kí trong học kì phải đồng thời = -1 (tức là học kì đó chưa bắt đầu)
	bool checkSemester = true;
	for (int i = 0; i < ObjectList.size(); i++) {
		if (account == ObjectList[i].getID_student() && ObjectList[i].getSemeter_ID() == semester) {
			if (ObjectList[i].getAssignment_Score() != -1 || ObjectList[i].getAverage_score() != -1 || ObjectList[i].getFinalScore() != -1 || ObjectList[i].getMid_Score() != -1) {
				checkSemester = false;
			}
		}
	}

	for (int i = 0; i < ObjectList.size(); i++) {
		if (account == ObjectList[i].getID_student() && ObjectList[i].getSemeter_ID() == semester) {
			for (int j = 0; j < ListSubject.size(); j++) {
				if (ListSubject[j].getIDSubject() == ObjectList[i].getCourse_id()) {
					int n = ListSubject[j].getNumberOfCredits();
					numberOfCredits += n;
					break;
				}
			}
		}
	}

	if (check) {
		cout << "Cancel course ? (Y/N) ";
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
			if (checkSemester) {
				string strIDCourse;
				int pos;
				while (true) {
					cout << "Please enter course id: "; cin >> strIDCourse;
					bool checkExist = false; // KIểm tra xem mã môn học người dùng nhập có trong danh sách môn học hay không
					for (int i = 0; i < CourseList.size(); i++) {
						if (strIDCourse == CourseList[i].getCourse()) {
							pos = i;
							checkExist = true;
						}
					}
					if (checkExist) break;
					else {
						cout << "The course does not exist or is ongoing during your semester! ";
						cout << "Continue (Y/N) ?" << endl;
						char k; cin >> k;
						if (k == 'Y' || k == 'y') continue;
						else if (k == 'N' || k == 'n') return;
					}
				}
				cout << "Are you sure want to cancel the course ? (Y/N)" << endl;
				char ch;
				while (true) {
					cin >> ch;
					if (ch == 'Y' || ch == 'y' || ch == 'N' || ch == 'n') break;
					else {
						cout << "Invalid charracter" << endl;
						continue;
					}
				}
				if (ch == 'Y' || ch == 'y') {
					//Tiến hành xóa thông tin trong file object, trong list object
					//Xóa trong list Object
					for (int i = 0; i < ObjectList.size(); i++) {
						if (account == ObjectList[i].getID_student()) {
							if (ObjectList[i].getCourse_id() == CourseList[pos].getCourse()) {
								ObjectList.erase(ObjectList.begin() + i);
								break;
							}
						}
					}

					//Cập nhật lại file object
					fstream fileObject;
					fileObject.open("tmp.csv", ios::out);
					//course_id,id_student,id_teacher,midterm_test,assignment,final_test,summary_score,semester_id
					fileObject << "course_id" << "," << "id_student" << "," << "id_teacher" << "," << "midterm_test" << ","
						<< "assignment" << "," << "final_test" << "," << "summary_score" << "," << "semester_id" << endl;
					for (int i = 0; i < ObjectList.size(); i++) {
						fileObject << ObjectList[i].getCourse_id() << ","
							<< ObjectList[i].getID_student() << "," << ObjectList[i].gettID_teacher() << ","
							<< ObjectList[i].getMid_Score() << "," << ObjectList[i].getAssignment_Score() << ","
							<< ObjectList[i].getFinalScore() << "," << ObjectList[i].getAverage_score() << "," << ObjectList[i].getSemeter_ID() << endl;
					}
					fileObject.close();
					remove("object.csv");
					rename("tmp.csv", "object.csv");
					cout << "Cancel course successfully..." << endl;

					//Cập nhật lại n_student trong file course
					int s = CourseList[pos].getN_student();
					CourseList[pos].setN_student(s - 1);
					fstream fileCourse;
					fileCourse.open("tmp.csv", ios::out);

					//Course_ID,Teacher_ID,Name,n_student,slot,semesterID,state
					fileCourse << "Course_ID" << "," << "Teacher_ID" << "," << "Name" << "," << 
						"n_student" << "," <<  "slot" << "," << "semesterID" << "," << "state" << endl;
					for (int i = 0; i < CourseList.size(); i++) {
						fileCourse << CourseList[i].getCourse() << ",";
						fileCourse << CourseList[i].getIDteacher() << ",";
						fileCourse << CourseList[i].getNameSubject() << ",";
						fileCourse << CourseList[i].getN_student() << ",";
						fileCourse << CourseList[i].getSlot() << ",";
						fileCourse << CourseList[i].getSemesterID() << ",";
						fileCourse << CourseList[i].getState() << endl;
					}
					fileCourse.close();
					remove("course.csv");
					rename("tmp.csv", "course.csv");
				}
				else if (ch == 'N' || ch == 'n') return;
			}
			else {
				cout << "The current semester has not ended." << endl;
				cout << "You can not cancel courses." << endl;
			}
			
		}
		else if (ch == "N" || ch == "n") return;
	}
	else cout << "You have not joined any courses yet" << endl;
	
	system("pause");
}

//Với lựa chọn 1: xem các môn học đã đăng kí (tức là xem tất cả các khóa học kể cả môn học đã qua và môn đang học)
//Lựa chọn 2: xem các môn đang học (duyệt xem các khóa học nào chưa đủ cột điểm và chưa có điểm trung bình thì môn học đó vẫm còn đang diễn ra)
void student::ViewMyCoure(vector<object> & ObjectList, vector<subject>ListSubject, vector<course> &CourseList) {
	cout << "1. View all course" << endl;
	cout << "2. View current course" << endl;
	cout << "3. Exit" << endl;
	string choice;
	while (true) {
		cin >> choice;
		if (choice == "1" || choice == "2" || choice == "3") break;
		else {
			cout << "Invalid value" << endl;
			continue;
		}
	}

	bool checkObject = false; //Kiểm tra xem sinh viên có tham gia khóa học nào chưa
	for (int i = 0; i < ObjectList.size(); i++) {
		if (account == ObjectList[i].getID_student()) checkObject = true;
	}
	if (checkObject) {
		string semester, course_tmp;
		bool checkA = true;
		int pos;
		for (int i = 0; i < ObjectList.size(); i++) {
			if (account == ObjectList[i].getID_student()) {
				pos = i;
				if (ObjectList[i].getAverage_score() == -1) {
					checkA = false;
					break;
				}
			}
		}

		if (checkA) {
			course_tmp = ObjectList[pos].getCourse_id();
		}

		for (int i = 0; i < ObjectList.size(); i++) {
			if (account == ObjectList[i].getID_student()) {
				if (ObjectList[i].getAverage_score() == -1) {
					course_tmp = ObjectList[i].getCourse_id();
					break;
				}
			}
		}
		for (int i = 0; i < CourseList.size(); i++) {
			if (CourseList[i].getCourse() == course_tmp && CourseList[i].getState() == UNABLE) {
				semester = CourseList[i].getSemesterID();
			}
		}

		//Xem tất cả những môn học đã đăng kí (bao gồm tất cả những môn đã học, đang học và mới đăng kí)
		if (choice == "1") {
			cout << "----------------------------------------------------ALL MY COURSES-----------------------------------------------" << endl;
			cout << setiosflags(ios::left) << setw(14) << "Course ID";
			cout << setiosflags(ios::left) << setw(35) << "Subject";
			cout << setiosflags(ios::left) << setw(10) << "Mid-term";
			cout << setiosflags(ios::left) << setw(12) << "Assgnment";
			cout << setiosflags(ios::left) << setw(10) << "Final";
			cout << setiosflags(ios::left) << setw(16) << "Summary score";
			cout << setiosflags(ios::left) << setw(10) << "Semester";
			cout << endl;
			bool check = false;
			for (int i = 0; i < ObjectList.size(); i++) {
				if (account == ObjectList[i].getID_student()) {
					check = true;
					cout << setiosflags(ios::left) << setw(14) << ObjectList[i].getCourse_id();
					for (int j = 0; j < ListSubject.size(); j++) {
						if (ObjectList[i].getCourse_id() == ListSubject[j].getIDSubject())
							cout << setiosflags(ios::left) << setw(35) << ListSubject[j].getNameSubject();
					}
					cout << setiosflags(ios::left) << setw(10) << ObjectList[i].getMid_Score();
					cout << setiosflags(ios::left) << setw(12) << ObjectList[i].getAssignment_Score();
					cout << setiosflags(ios::left) << setw(10) << ObjectList[i].getFinalScore();
					cout << setiosflags(ios::left) << setw(16) << ObjectList[i].getAverage_score();
					for (int j = 0; j < CourseList.size(); j++) {
						if (ObjectList[i].getCourse_id() == CourseList[j].getCourse()) {
							cout << setiosflags(ios::left) << setw(10) << CourseList[j].getSemesterID();
							break;
						}
					}
					cout << endl;
				}
			}
			if (!check) {
				cout << "You have not joined any courses yet" << endl;
			}
		}

		//Xem những khóa học hiện tại đang học
		else if (choice == "2") {
			cout << "---------------------------------------------MY CURRENT COURSES-------------------------------------------" << endl;
			cout << setiosflags(ios::left) << setw(14) << "Course ID";
			cout << setiosflags(ios::left) << setw(35) << "Subject";
			cout << setiosflags(ios::left) << setw(10) << "Mid-term";
			cout << setiosflags(ios::left) << setw(12) << "Assgnment";
			cout << setiosflags(ios::left) << setw(10) << "Final";
			cout << setiosflags(ios::left) << setw(16) << "Summary score";
			cout << setiosflags(ios::left) << setw(10) << "Semester";
			cout << endl;
			bool check = false;

			for (int i = 0; i < ObjectList.size(); i++) {
				if (ObjectList[i].getSemeter_ID() == semester && account == ObjectList[i].getID_student()) {
					check = true;
					cout << setiosflags(ios::left) << setw(14) << ObjectList[i].getCourse_id();
					for (int j = 0; j < ListSubject.size(); j++) {
						if (ObjectList[i].getCourse_id() == ListSubject[j].getIDSubject())
							cout << setiosflags(ios::left) << setw(35) << ListSubject[j].getNameSubject();
					}
					cout << setiosflags(ios::left) << setw(10) << ObjectList[i].getMid_Score();
					cout << setiosflags(ios::left) << setw(12) << ObjectList[i].getAssignment_Score();
					cout << setiosflags(ios::left) << setw(10) << ObjectList[i].getFinalScore();
					cout << setiosflags(ios::left) << setw(16) << ObjectList[i].getAverage_score();
					for (int j = 0; j < CourseList.size(); j++) {
						if (ObjectList[i].getCourse_id() == CourseList[j].getCourse()) {
							cout << setiosflags(ios::left) << setw(10) << CourseList[j].getSemesterID();
							break;
						}
					}
					cout << endl;
				}
			}
			if (!check) {
				cout << "You have not joined any courses yet" << endl;
			}
		}
		int numberOfCredits_cumulative = 0;//Tính số tín chỉ sinh viên đã tích lũy
		int numberOfCredits_pass = 0; //Tính số tín chỉ sinh viên đã đạt được trong học kì
		int semester_Credits = 0;//Số tín chỉ đăng kí trong học kì
								 //Số tín chỉ chỉ được tích lũy khi môn học nào có điểm tổng kết >= 5, nếu < 5 thì coi như sinh viên chưa đạt
		double sumScore = 0;//Tính điểm trung bình tích lũy
		double average = 0; //Tính điểm trung bình học kì
		int tmp = 0;

		//Đếm số tín chỉ đã đăng kí trong học kì và số tín chỉ tích lũy được trong học kỳ
		for (int i = 0; i < ObjectList.size(); i++) {
			if (account == ObjectList[i].getID_student() && ObjectList[i].getSemeter_ID() == semester) {
				int n;//Lấy ra số tín chỉ
				for (int j = 0; j < ListSubject.size(); j++) {
					if (ListSubject[j].getIDSubject() == ObjectList[i].getCourse_id()) {
						n = ListSubject[j].getNumberOfCredits();
						semester_Credits += n;
						if (ObjectList[i].getAverage_score() >= 5) {
							numberOfCredits_pass += n;
						}
					}
				}
			}
		}
		cout << fixed << setprecision(1);
		cout << "Semester credits registered: " << semester_Credits << endl;

		for (int i = 0; i < ObjectList.size(); i++) {
			if (account == ObjectList[i].getID_student() && ObjectList[i].getAverage_score() != -1) {
				double score = ObjectList[i].getAverage_score();
				int n = 0;
				for (int j = 0; j < ListSubject.size(); j++) {
					if (ListSubject[j].getIDSubject() == ObjectList[i].getCourse_id()) {
						n = ListSubject[j].getNumberOfCredits();
						tmp += n;
						if (ObjectList[i].getAverage_score() >= 5) {
							numberOfCredits_cumulative += n;//Số tín chỉ tích lũy
							break;
						}
					}
				}
				sumScore += score * n;
			}
		}

		cout << "Number of credits cumulated in the semester: " << numberOfCredits_cumulative << endl;

		//Kiểm tra xem tất cả các môn trong học kỳ đã đủ điểm hay chưa
		bool checkAverage = true;
		for (int i = 0; i < ObjectList.size(); i++) {
			if (account == ObjectList[i].getID_student() && ObjectList[i].getSemeter_ID() == semester) {
				if (ObjectList[i].getAverage_score() == -1) checkAverage = false;
			}
		}
		if (checkAverage) {
			for (int i = 0; i < ObjectList.size(); i++) {
				if (account == ObjectList[i].getID_student() && ObjectList[i].getSemeter_ID() == semester) {
					double sc = ObjectList[i].getAverage_score();
					int n;//Lấy ra số tín chỉ
					for (int j = 0; j < ListSubject.size(); j++) {
						if (ListSubject[j].getIDSubject() == ObjectList[i].getCourse_id()) {
							n = ListSubject[j].getNumberOfCredits();
						}
					}
					average += sc * n;
				}
			}
			cout << "Semester GPA: " << average / semester_Credits << endl;

		}
		else cout << "Semester GPA: " << -1 << "(The current semester has not ended)" << endl;

		cout << "Total accumulated credits: " << numberOfCredits_cumulative << endl;
		if (sumScore == 0) {
			cout << "Average cumulative score : " << -1 << endl;
		}
		else {
			cout << "Average cumulative score : " << sumScore / tmp << endl;
		}
	}
	else {
		cout << "You have not joined any courses yet" << endl;
	}
	if (choice == "3") return;

	system("pause");
}