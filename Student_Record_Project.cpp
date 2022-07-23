#include <iostream>
#include <fstream>
#include<tuple>
#include <vector>
#include<random>
#include<ctime>
using namespace std;


class STUDENT {
	public:
		string studName, dept;
		int id;

} studDetail;
int ID;
tuple<string, string> studInfo();

tuple<bool, int> isFound(vector<STUDENT> &studRecord, int ID);

void addStud(vector<STUDENT> &studRecord);

void editStud(vector<STUDENT> &studRecord,int ID);

void deleteStud(vector<STUDENT> &studRecord,int ID);

void displayDetl(vector<STUDENT> &studRecord,int ID);

void fetchData(vector<STUDENT> &studRecord, string filename);

void updateRecFile(vector<STUDENT> &studRecord, string filename);

int main() {
	
	const string RECORD_NAME = "studantRec.txt";
	int option;
	vector<STUDENT> studRecord;
	fetchData(studRecord, RECORD_NAME);
START:
	cout << "1 _ Add new studant \t";
	cout << "2 _ Show studant detail\n";
	cout << "3 _ Edit studant detail\t";
	cout << "4 _ Delete studant detail\n";
	cout << "5 _ Exit \n";

	cin >> option;
	switch (option) {
		case 1:
			addStud(studRecord);
			updateRecFile(studRecord, RECORD_NAME);
			break;

		case 2:
			cout << "Enter the ID : ";
			cin >> ID;
			displayDetl(studRecord, ID);
			break;

		case 3:
			cout << "Enter the ID : ";
			cin >> ID;
			editStud(studRecord, ID);
			updateRecFile(studRecord, RECORD_NAME);
			break;

		case 4:
			cout << "Enter the ID : ";
			cin >> ID;
			deleteStud(studRecord, ID);
			updateRecFile(studRecord, RECORD_NAME);
			break;
		case 5:
			return 0;
		default:
			system("cls");
			cout << "not allowd!\n";
			break;
	}
	goto START;
}
void addStud(vector<STUDENT> &studRecord) {
tryAgain:
	srand(time(0));
	ID = rand() % 1000;
	auto [found, index] = isFound(studRecord, ID);
	if(found) goto tryAgain;
	cout << "Your ID is : " << ID <<endl;
	cout << "--------Entet new student detail-------\n";
	auto [name, dept] = studInfo();
	studDetail.id = ID;
	studDetail.studName = name;
	studDetail.dept = dept;

	studRecord.push_back(studDetail);

	//system("cls");
	cout << "Addding done successfully!\n";
}

void editStud(vector<STUDENT> &studRecord,int ID) {
	auto [found, index] = isFound(studRecord, ID);
	if (!found) return;
	cout << "--------Edit student detail-------\n";
	auto [name, dept] = studInfo();
	studRecord.at(index).studName = name;
	studRecord.at(index).dept = dept;

	system("cls");
	cout << "Editing done successful!\n";
}

void deleteStud(vector<STUDENT> &studRecord,int ID) {
	auto [found, index] = isFound(studRecord, ID);
	if (!found) return;
	cout<<index<<endl;
	studRecord.erase(studRecord.begin() + index);
	cout << "successful deleted \n";
}

void displayDetl(vector<STUDENT> &studRecord,int ID) {
	auto [found, index] = isFound(studRecord, ID);
	if (!found) return;
	cout << "ID    : " << studRecord.at(index).id << endl;
	cout << "Name  : " << studRecord.at(index).studName << endl;
	cout << "Dept  : " << studRecord.at(index).dept << endl;
}

tuple<bool, int> isFound(vector<STUDENT> &studRecord, int ID) {
	for (int index = 0; index < studRecord.size(); index++) {
		if (ID == studRecord[index].id)
			return {true, index};
	}
	cout << "No student has this ID! \n";
	return {false, 0};
}

void updateRecFile(vector<STUDENT> &studRecord, string filename) {
	ofstream updateRecord(filename);
	for (int index = 0; index < studRecord.size(); index++) {
		updateRecord << studRecord.at(index).id << "\t" << studRecord.at(index).studName << "\t" << studRecord.at(index).dept << endl;
	}
}

void fetchData(vector<STUDENT> &studRecord, string filename) {
	ifstream readRecord(filename);
	while (!readRecord.eof()) {
		readRecord >> studDetail.id;
		readRecord >> studDetail.studName;
		readRecord >> studDetail.dept;
		studRecord.push_back(studDetail);
	}
	studRecord.pop_back();
}

tuple<string, string> studInfo() {
	int option;
	string name, dept;
	cout << "Enter studant name : ";
	cin >> name;
opt:
cout<<12;
	cout << "1 == IT\t 2 == CS\t 3 == SE\n";
	cout << "Enter department : ";
	cin >> option;
	switch (option) {
		case 1:
			dept = "IT";
			break;
		case 2:
			dept = "CS";
			break;
		case 3:
			dept = "SE";
			break;
		default:
			cout << "wrong option!\n";
			goto opt;
	}
	return {name, dept};
	
	
}