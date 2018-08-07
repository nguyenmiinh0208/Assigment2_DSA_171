#include "admin.h"
#include "user.h"
#include <cstdint>

#define MAX_CREDITS 139
using namespace std;

bool addFileTeacher(vector<users> &ListUser, vector<teacher> &TList) {
	//Nhập thông tin giảng viên
	teacher t;
	cout << "--Enter teacher information: " << endl;
	string name, Bdate, address, account, phoneNumber;
	cout << "1) Name: ";
	cin.ignore();
	getline(cin, name); t.setName(name);
	fflush(stdin);

	cout << "2) Bdate: ";
	getline(cin, Bdate); t.setBdate(Bdate);
	fflush(stdin);

	cout << "3) Address: ";
	getline(cin, address); t.setAddress(address);
	fflush(stdin);

	cout << "4) Phone: "; cin >> phoneNumber; t.setPhone(phoneNumber);
	cout << "--------------------------------" << endl;

	while (true) {
		cout << "Enter account: ";
		cout << "+) Account: "; cin >> account;
		bool check = true;
		//Kiểm tra xem trong list user đã tồn tại account hay chưa, nếu có yêu cầu đặt tên khác
		//Nếu tên tài khoản hợp lệ thì biến check = true và thoát ra ngoài vòng lặp
		for (int i = 0; i < ListUser.size(); i++) {
			if (account == ListUser[i].getAccount()) {
				check = false;
				break;
			}
		}
		if (check) break;
		else {
			cout << "The username already exists !!" << endl;
			continue;
		}
	}
	cout << "Account: " << account << endl;
	cout << "Password: " << account << endl;
	t.setAccount(account);
	t.setPassWord(account);
	cout << "User password will be same as account." << endl;
	TList.push_back(t);//add vào list teacher
					   //Mở file teacher.csv và ghi thông tin vào
	fstream fileTeacher;
	fileTeacher.open("teacher.csv", ios::app);
	fileTeacher << account << "," << name << "," << Bdate << "," << phoneNumber << "," << address << endl;
	fileTeacher.close();

	//Thêm vào list user và file user
	users u;
	u.setAccount(account);
	u.setPassWord(account);
	u.setRole(TEACHER);
	ListUser.push_back(u);//add vào list

	fstream fileUser;
	fileUser.open("user.csv", ios::app);
	fileUser << account << "," << account << "," << "teacher" << endl;
	fileUser.close();
	cout << "Add user successfully..." << endl;
	return true;
}

bool addFileStudent(vector<users> &ListUser, vector<student> &StList) {
	//Nhập thông tin sinh viên
	cout << "--Enter student information: " << endl;
	string name, Bdate, address, password, mssv;

	student st;
	cout << "1) Name: ";
	cin.ignore();
	getline(cin, name); st.setName(name);
	fflush(stdin);

	cout << "2) Bdate: ";
	getline(cin, Bdate); st.setBdate(Bdate);
	fflush(stdin);

	cout << "3) Address: ";
	getline(cin, address); st.setAddress(address);
	fflush(stdin);

	while (true) {
		cout << "4) MSSV: "; cin >> mssv;
		bool check = true;
		//Kiểm tra xem trong list user đã tồn tại account hay chưa, nếu có yêu cầu đặt tên khác
		//Nếu tên tài khoản hợp lệ thì biến check = true và thoát ra ngoài vòng lặp
		for (int i = 0; i < ListUser.size(); i++) {
			if (mssv == ListUser[i].getAccount()) {
				check = false;
				break;
			}
		}
		if (check) break;
		else {
			cout << "The username already exists !!" << endl;
			continue;
		}
	}
	st.setMssv(mssv);
	st.setAccount(mssv);
	st.setPassWord(mssv);
	cout << "User: " << mssv << endl;
	cout << "Password: " << mssv << endl;
	cout << "User password will be same as account." << endl;
	StList.push_back(st);//add vào list student
						 //Mở file student.csv và ghi thông tin vào
	fstream fileStudent;
	fileStudent.open("student.csv", ios::app);
	fileStudent << mssv << "," << name << "," << Bdate << "," << address << endl;
	fileStudent.close();

	users u;
	u.setAccount(mssv);
	u.setPassWord(mssv);
	u.setRole(STUDENT);
	ListUser.push_back(u);//add vào list

	fstream fileUser;
	fileUser.open("user.csv", ios::app);
	fileUser << mssv << "," << mssv << "," << "student" << endl;
	fileUser.close();
	cout << "-------------------------------------" << endl;
	cout << "Add user successfully..." << endl;
	return true;
}

bool updateFileUser(vector<users> &ListUser) {
	//Cập nhật lại file user
	fstream fileUser;
	fileUser.open("user_Tmp.csv", ios::out);
	if (!fileUser.is_open()) {
		cout << "Not Found !" << endl;
		return false;
	}
	for (int i = 0; i < ListUser.size(); i++) {
		fileUser << ListUser[i].getAccount() << "," << ListUser[i].getPassWord() << ",";
		if (ListUser[i].getRole() == ADMIN) {
			fileUser << "admin";
		}
		if (ListUser[i].getRole() == TEACHER) {
			fileUser << "teacher";
		}
		if (ListUser[i].getRole() == STUDENT) {
			fileUser << "student";
		}
		fileUser << endl;
	}
	fileUser.close();
	remove("user.csv");
	rename("user_Tmp.csv", "user.csv");
	return true;
}

bool updateFileStudent(vector<student> &StList) {
	fstream fileStudent;
	fileStudent.open("student_Tmp.csv", ios::out);
	if (!fileStudent.is_open()) {
		cout << "Not Found !" << endl;
		return false;
	}
	for (int i = 0; i < StList.size(); i++) {
		fileStudent << StList[i].getMssv() << ",";
		fileStudent << StList[i].getName() << ",";
		fileStudent << StList[i].getBdate() << ",";
		fileStudent << StList[i].getAddress();
		fileStudent << endl;
	}
	fileStudent.close();
	remove("student.csv");
	rename("student_Tmp.csv", "student.csv");
	return true;
}

bool updateFileTeacher(vector<teacher> &TList) {
	fstream fileTeacher;
	fileTeacher.open("teacher_Tmp.csv", ios::out);
	if (!fileTeacher.is_open()) {
		cout << "Not Found !" << endl;
		return false;
	}

	for (int i = 0; i < TList.size(); i++) {
		fileTeacher << TList[i].getAccount() << ",";
		fileTeacher << TList[i].getName() << ",";
		fileTeacher << TList[i].getBdate() << ",";
		fileTeacher << TList[i].getPhone() << ",";
		fileTeacher << TList[i].getAddress();
		fileTeacher << endl;
	}

	fileTeacher.close();
	remove("teacher.csv");
	rename("teacher_Tmp.csv", "teacher.csv");
	return true;
}

bool updateFileObject(vector<object> &ObjectList) {
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
	fileObject.close();
	return true;
}

void admin::ShowOption_Admin() {
	cout << "-------------------------------------------ADMIN----------------------------------------------------" << endl;
	cout << setiosflags(ios::left) << setw(30) << "1. Show User";
	cout << setiosflags(ios::left) << setw(30) << "2. Search User";
	cout << setiosflags(ios::left) << setw(30) << "3. Add User";
	cout << setiosflags(ios::left) << setw(30) << "4. Delete User" << endl;
	cout << setiosflags(ios::left) << setw(30) << "5. Change password";
	cout << setiosflags(ios::left) << setw(30) << "6. Multiple delete";
	cout << setiosflags(ios::left) << setw(30) << "7. Logout";
	cout << setiosflags(ios::left) << setw(30) << "8. Exit" << endl;
}

void admin::Add_Users(vector<users> &ListUser, vector<teacher> &TList, vector<student> &StList) {
	cout << "----------------------------------------------ADD USER--------------------------------------" << endl;
	cout << "--------------------------------------------------------------------------------------------" << endl;
	cout << "Do you want to add teachers or student ?" << endl;
	cout << "1. Add teacher" << "\t\t\t" << "2. Add student" << "\t\t\t" <<"3. Exit" <<endl;
	char choice;
	while (true) {
		cout << "Your choice: ";
		cin >> choice;
		if (choice == '1' || choice == '2' || choice == '3') break;
		else {
			cout << "Invalid value ! Continue ? (Y/N) ";
			char ch;
			while (true) {
				cin >> ch;
				if (ch == 'Y' || ch == 'y' || ch == 'N' || ch == 'n') break;
				else {
					cout << "Invalid charracter" << endl;
					continue;
				}
			}
			if (ch == 'Y' || ch == 'y') continue;
			else if (ch == 'N' || ch == 'n') return;
		}
	}
	if (choice == '1') addFileTeacher(ListUser, TList);
	else if (choice == '2') addFileStudent(ListUser, StList);
	else if (choice == '3') return;
	system("pause");
}

void admin::Delete_Users(vector<users> &ListUser, vector<teacher> &TList, vector<student> &StList) {
	cout << "---------------------------------------DELETE USER------------------------------------------" << endl;
	cout << "--------------------------------------------------------------------------------------------" << endl;
	cout << "1.Delete user" << "\t\t\t" << "2. Exit" << endl;
	char choice;
	while (true) {
		cout << "Your choice: ";
		cin >> choice;
		if (choice == '1' || choice == '2') break;
		else {
			cout << "Invalid value ! Continue ? (Y/N) ";
			char ch;
			while (true) {
				cin >> ch;
				if (ch == 'Y' || ch == 'y' || ch == 'N' || ch == 'n') break;
				else {
					cout << "Invalid charracter" << endl;
					continue;
				}
			}
			if (ch == 'Y' || ch == 'y') continue;
			else if (ch == 'N' || ch == 'n') return;
		}
	}
	if (choice == '1') {
		string strUserDel;
		int role_DelUser;//Lưu vai trò của user
		bool checkDel = false;//pos dùng để lưu vị trí của user cần xóa.
		cout << "Enter the username to delete: "; cin >> strUserDel;
		for (int i = 0; i < ListUser.size(); i++) {
			//Duyệt tìm có user cần xóa hay không
			if (strUserDel == ListUser[i].getAccount()) {
				role_DelUser = ListUser[i].getRole();
				checkDel = true;//Tìm được user cần xóa
				ListUser.erase(ListUser.begin() + i);//Xóa User
				break;
			}
		}
		if (checkDel) {
			updateFileUser(ListUser);
			//Sau khi xử lí bên user (List và file csv) xong, tiếp tục xử lí file thông tin user (teacher.csv và student.csv)
			//Duyệt file thông tin người dùng để xóa thông tin, nếu user là teacher thì vào file teacher.csv xóa thông tin và tương tự cho student

			if (role_DelUser == TEACHER) {
				for (int i = 0; i < TList.size(); i++) {
					if (strUserDel == TList[i].getAccount()) {
						//Tìm được thông tin user cần xóa --> tiến hành xóa khỏi list
						TList.erase(TList.begin() + i);//Xóa
						break;
					}
				}

				//Cập nhật lại file teacher.csv
				updateFileTeacher(TList);
			}

			else if (role_DelUser == STUDENT) {
				for (int i = 0; i < StList.size(); i++) {
					if (strUserDel == StList[i].getAccount()) {
						//Tìm được thông tin user cần xóa --> tiến hành xóa khỏi list
						StList.erase(StList.begin() + i);
						break;
					}
				}
				//Cập nhật lại file student.csv
				updateFileStudent(StList);
			}

			cout << "Delete user successfully..." << endl;
		}

		else cout << "User not found !" << endl;
	}
	else if (choice == '2') return;
	system("pause");
	return;
}

//Hàm chuyển chữ hoa sang thường
string Lower(string str) {
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

//Có 2 lựa chọn (tìm kiếm theo account và tìm kiếm 1 lúc nhiều user theo tên)
void admin::Search_User(vector<users> &ListUser, vector<teacher> &TList, vector<student> &StList) {
	cout << "-----------------------------------------SEARCH USER---------------------------------------------" << endl;
	cout << "--------------------------------------------------------------------------------------------------" << endl;
	cout << "1) Search by account" << endl;
	cout << "2) Search by name" << endl;
	cout << "3) Exit" << endl;
	char choice;
	while (true) {
		cout << "Your choice: ";
		cin >> choice;
		if (choice == '1' || choice == '2' || choice == '3') break;
		else {
			cout << "Invalid value ! Continue ? (Y/N) ";
			char ch;
			while (true) {
				cin >> ch;
				if (ch == 'Y' || ch == 'y' || ch == 'N' || ch == 'n') break;
				else {
					cout << "Invalid charracter" << endl;
					continue;
				}
			}
			if (ch == 'Y' || ch == 'y') continue;
			else if (ch == 'N' || ch == 'n') return;
		}
	}

	if (choice == '1') {
		string strUserName;
		cout << "Enter username: "; cin >> strUserName;
		bool checkUser = false;//Kiểm tra xem có user cần tìm hay không, nếu có trả về true và ngược lại
		for (int i = 0; i < ListUser.size(); i++) {
			if (strUserName.compare(ListUser[i].getAccount()) == 0) {
				checkUser = true;
				cout << "Successfully..." << endl;
				cout << "-----------------------------" << endl;
				if (ListUser[i].getRole() == TEACHER) {
					cout << "teacher: ";
					cout << ListUser[i].getAccount() << endl;
					cout << "........................." << endl;
					for (int j = 0; j < TList.size(); j++) {
						if (strUserName == TList[j].getAccount()) {
							cout << "Name: " << TList[j].getName() << endl;
							cout << "Birthday: " << TList[j].getBdate() << endl;
							cout << "Address: " << TList[j].getAddress() << endl;
							cout << "Phone number: " << TList[j].getPhone() << endl;
							break;
						}
					}
				}
				if (ListUser[i].getRole() == STUDENT) {
					cout << "student: ";
					cout << ListUser[i].getAccount() << endl;
					cout << "........................." << endl;
					for (int j = 0; j < StList.size(); j++) {
						if (strUserName == StList[j].getMssv()) {
							cout << "Name: " << StList[j].getName() << endl;
							cout << "Student ID: " << StList[j].getMssv() << endl;
							cout << "Birthday: " << StList[j].getBdate() << endl;
							cout << "Address: " << StList[j].getAddress() << endl;
							break;
						}
					}
				}
				break;
			}
		}

		if (!checkUser) {
			cout << "User not found !" << endl;
		}
	}
	else if (choice == '2') {
		fflush(stdin);
		string name;
		cout << "Enter name: ";
		cin.ignore();
		getline(cin, name);
		string nameUser = Lower(name);
		bool checkExits = false;
		cout << setiosflags(ios::left) << setw(25) << "Name";
		cout << setiosflags(ios::left) << setw(15) << "Birthday";
		cout << setiosflags(ios::left) << setw(45) << "Address";
		cout << setiosflags(ios::left) << setw(8) << "Job";
		cout << endl;
		cout << "-------------------------------------------------------------------------------------------------" << endl;
		for (int i = 0; i < TList.size(); i++) {
			string s = TList[i].getName();
			string ss = Lower(s);
			if (strstr(ss.c_str(), nameUser.c_str()) != NULL) {
				checkExits = true;
				cout << setiosflags(ios::left) << setw(25) << TList[i].getName();
				cout << setiosflags(ios::left) << setw(15) << TList[i].getBdate();
				cout << setiosflags(ios::left) << setw(45) << TList[i].getAddress();
				cout << setiosflags(ios::left) << setw(8) << "Teacher";
				cout << endl;
			}
		}

		for (int i = 0; i < StList.size(); i++) {
			string s = StList[i].getName();
			string ss = Lower(s);
			if (strstr(ss.c_str(), nameUser.c_str()) != NULL) {
				checkExits = true;
				cout << setiosflags(ios::left) << setw(25) << StList[i].getName();
				cout << setiosflags(ios::left) << setw(15) << StList[i].getBdate();
				cout << setiosflags(ios::left) << setw(45) << StList[i].getAddress();
				cout << setiosflags(ios::left) << setw(8) << "Student";
				cout << endl;
			}
		}
		if (!checkExits) cout << "User not found..." << endl;
	}
	else if (choice == '3') return;
	system("pause");
	return;
}

void admin::showUser(vector<users> &ListUser) {
	cout << "ACCOUNT" << "\t\t\t" << "ROLE" << endl;
	cout << "-----------------------------" << endl;
	for (int i = 1; i < ListUser.size(); i++) {
		cout << ListUser[i].getAccount() << "\t\t\t";
		if (ListUser[i].getRole() == STUDENT) {
			cout << "Student";
		}
		if (ListUser[i].getRole() == TEACHER) {
			cout << "Teacher";
		}
		cout << endl;
	}
	system("pause");
}

//Chức năng xóa 1 lúc nhiều sinh viên đã tốt nghiệp
//Chức năng xóa 1 lúc nhiều sinh viên theo yêu cầu (Nhập 1 chuỗi gồm các mã số sinh viên)
void admin::Multiple_Delete(vector<users> &ListUser, vector<student> &StList, vector<subject> &SubjectList, vector<object> &ObjectList) {
	cout << "1) Remove graduated students " << endl;
	cout << "2) Remove the students on request" << endl;
	cout << "3) Exit" << endl;
	char choice;
	while (true) {
		cout << "Your choice: "; cin >> choice;
		if (choice == '1' || choice == '2' || choice == '3') break;
		else {
			cout << "Invalid value" << endl;
			continue;
		}
	}

	if (choice == '1') {
		cout << "Are you sure want to delete ? (Y/N)" << endl;
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
			//Xóa những sinh viên đã tốt nghiệp (sinh viên nào tích lũy đủ 139 tín chỉ)
			vector<string> listStudent_delete;
			for (int i = StList.size() - 1; i >= 0; i--) {
				int numberCredits = 0;
				for (int j = 0; j < ObjectList.size(); j++) {
					if (StList[i].getAccount() == ObjectList[j].getID_student()) {
						if (ObjectList[j].getAverage_score() >= 5) {
							for (int k = 0; k < SubjectList.size(); k++) {
								if (ObjectList[j].getCourse_id() == SubjectList[k].getIDSubject()) {
									int n = SubjectList[i].getNumberOfCredits();
									numberCredits += n;
								}
							}
						}
					}
				}
				if (numberCredits >= 139) {
					listStudent_delete.push_back(StList[i].getAccount());
					StList.erase(StList.begin() + i);
				}
			}

			if (listStudent_delete.size() > 0) {
				cout << "List student deleted: " << endl;
				for (int i = 0; i < listStudent_delete.size(); i++) {
					cout << listStudent_delete[i] << endl;
				}
				cout << "Delete successfully..." << endl;
			}
			else {
				cout << "No students" << endl;
			}
		}
		else if (ch == 'N' || ch == 'n') return;
		
	}
	else if (choice == '2') {
		//Tiến hành nhập các chuỗi mã số sinh viên (các mã số cách nhau bằng dấu cách)
		fflush(stdin);
		cout << "Import student id list (Note: The ids are separated by a space): " << endl;
		string strList;
		cin.ignore();
		getline(cin, strList);
		vector<string> listStudent_delete;

		//Cắt chuỗi ra từng mã số sinh viên, cho vào list listStudent_delete để xóa
		while (strList.length() > 0) {
			int pos;
			pos = strList.find(' ');
			if (pos != -1) {
				listStudent_delete.push_back(strList.substr(0, pos));
				strList.erase(0, pos + 1);
			}
			else {
				listStudent_delete.push_back(strList.substr(0));
				strList.erase(0);
			}
		}
		
		//Xóa thông tin trong list user, list student, list object
		for (int i = 0; i < listStudent_delete.size(); i++) {
			bool checkExist = false;
			for (int j = ListUser.size() - 1; j >= 0; j--) {
				if (listStudent_delete[i] == ListUser[j].getAccount()) {
					checkExist = true;
					ListUser.erase(ListUser.begin() + j);
					break;
				}
			}
			for (int k = StList.size() - 1; k >= 0; k--) {
				if (checkExist && listStudent_delete[i] == StList[k].getMssv()) {
					StList.erase(StList.begin() + k);
					break;
				}
			}
			for (int k = ObjectList.size() - 1; k >= 0; k--) {
				if (checkExist && listStudent_delete[i] == ObjectList[k].getID_student()) {
					ObjectList.erase(ObjectList.begin() + k);
					break;
				}
			}
			if (checkExist) {
				cout << "Deleted - " << listStudent_delete[i] << endl;
			}
			else {
				cout << "Not found - " << listStudent_delete[i] << endl;
			}
		}
		//Tiến hành update file student, file user, file object
		updateFileUser(ListUser);
		updateFileStudent(StList);
		updateFileObject(ObjectList);
	}
	else if (choice == '3') return;
	system("pause");
	return;
}
