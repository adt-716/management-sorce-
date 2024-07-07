#include<string.h>
#include<iostream>
#include <fstream>
using namespace std;

class Student {
public:
    char id_num[30];
    char name[30];
    char gender[10];
    char date_of_birth[30];
    float gpa;
    Student() {}

};

class Subject{
public:
    char id_sub[30];
    char name_sub[30];
    int credit;
    Subject() {}

};

class Grade
{
public:
    char id_num[30];
    char id_sub[30];
    float mark;
    Grade() {}

};

//creat an array with 100 elements
Student student[100];
Subject subject[100];
Grade grade[100];



int nsv, nhp, ndt;
int stt;
int temp[3];


/////////////////////////////////////////////// Student ///////////////////////////////////////////



int checkValidDate(char* buf) {
    int i = 0, j = 0, sum = 0;
    while (*buf)
    {
        if (*buf == '/' || (*buf - '0' >= 0 && *buf - '0' <= 9)) {
            if (*buf == '/') {
                temp[i++] = sum;
                sum = 0;
            }
            else {
                sum = sum * 10 + *buf - '0';
            }
        }
        else {
            return 0;
        }
        *buf++;
    }
    temp[i++] = sum;
    if (i != 3) {

        return 0;
    }
    else {
        if (temp[0] < 1 || temp[0]>31) {    // ngay
            return 0;
        }
        if (temp[1] < 1 || temp[1]>13) { // thang
            return 0;
        }
        if (temp[2] < 1900 && temp[2]>2022) {//nam
            return 0;
        }
    }
    return 1;
}

int checkIDNum(char* buf) {

    for (int i = 0; i < nsv; i++) {
        if (strcmp(student[i].id_num, buf) == 0)
            return i;
    }
    return -1;
}
int checkSVHPDT(char *msv,char *mhp){
    for(int i=0;i<ndt;i++){
        if( strcmp(grade[i].id_num,msv)==0 && strcmp(grade[i].id_num,mhp)==0 ) return i;
    }
    return -1;
}
void insertStudentData() {

    int isvalid = 0;
    char id_num[30];
    char name[30];
    char gender[10];
    char date_of_birth[30];
    cout << "Enter Student's ID:" ;
    cin >> id_num;
    isvalid = checkIDNum(id_num);
    if (isvalid != -1) {
        cout << "Student already Exists." << endl;
        return;
    }

    cout << "Name: " ;

    cin >> name;
    cout << "Gender: " ;

    cin >>gender;
    cout << "Date of Birth: " ;

    while (cin >> date_of_birth)
    {
        isvalid = checkValidDate(date_of_birth);
        if (isvalid) {
            break;
        }
        else {
            cout << "Not valid. Try again: " << endl;
        }
    }
    cout << "Added new student successfully." << endl;

    ofstream outfile;
    outfile.open("SV.BIN", ios_base::app);

    outfile << id_num << " " << name << " " << gender << " " << date_of_birth << endl;
    strcpy(student[nsv].gender, gender);
    strcpy(student[nsv].name, name);
    strcpy(student[nsv].date_of_birth, date_of_birth);
    strcpy(student[nsv].id_num, id_num);
    student[nsv].gpa = 0;
    nsv++;

    outfile.close();
}


void addStudentDetail() {
    char id_num[30];
    char name[30];
    char gender[10];

    cout << "Enter Students's ID" << endl;
    cin >> id_num;
    int idx = checkIDNum(id_num);
    if (idx != -1) {
        int choice;

        do{
            cout << " 1  - Add name" << endl;
            cout << " 2  - Add gender" << endl;
            cin >> choice;
        }while ((choice != 1) && (choice != 2));

        switch (choice)
        {
            case 1:
                cout << "Enter name" << endl;
                cin >> name;
                strcpy(student[idx].name, name);
                break;
            case 2:
                cout << "Enter gender" << endl;
                cin >> gender;
                strcpy(student[idx].gender, gender);
                break;
        }
    }
    else cout << "Can't find Student" << endl;
}

void modifyStudent() {
    char id_num[30];
    int isFound = 0;
    int isvalid;
    cout << "Enter Students's ID:" << endl;
    cin >> id_num;
    for (int i = 0; i < nsv; i++) {
        if (strcmp(student[i].id_num, id_num) == 0) {
            isFound = 1;
            char id_num1[30];
            char name[30];
            char gender[10];
            char date_of_birth[30];
            cout << "Enter Students's ID" << endl;
            cin >> id_num1;
            isvalid = checkIDNum(id_num1);
            if (isvalid != -1){
                cout << "Student already Exists." << endl;
                return;
            }
            cout << "Name:" << endl;
            cin >> name;
            cout << "Gender:" << endl;
            cin >> gender;
            cout << "Date of Birth:" << endl;

            while (cin >> date_of_birth){
                isvalid = checkValidDate(date_of_birth);
                if (isvalid) {
                    break;
                }
                else {
                    cout << "Date of Birth not Valid. Try again: " << endl;
                }
            }

            cout << "Modified Student Data Successfull" << endl;
            ofstream outfile;
            outfile.open("SV.BIN", ios_base::app);
            outfile << id_num << " " << name << " " << gender << " " << date_of_birth << endl;
            strcpy(student[i].gender, gender);
            strcpy(student[i].name, name);
            strcpy(student[i].date_of_birth, date_of_birth);
            strcpy(student[i].id_num, id_num1);

            outfile.close();
            break;
        }
    }
    if (!isFound) {
        cout << "Student not Exist" << endl;
    }
    else cout << " Modified Student Data" << endl;
}

void deleteStudentData() {
    char id_num[30];
    int isFound = 0;
    cout << "Enter ID's Student: " << endl;
    cin.ignore();
    cin.getline(id_num,30);

    for (int i = 0; i < nsv; i++) {
        if (strcmp(student[i].id_num, id_num) == 0) {
            isFound = 1;
            student[i] = student[nsv - 1];
            nsv--;
            for (int j = 0; j < ndt;) {
                if (strcmp(grade[j].id_num, id_num) == 0) {
                    grade[j] = grade[ndt - 1];
                    ndt--;
                }
                else j++;
            }
            break;
        }
    }

    if (!isFound) {
        cout << "Student not Exist" << endl;
    }
    else cout <<"Deleted student\n";
}

////////////////////////////////////////// Subject ////////////////////////////////////////



int checkIDSub(char* buf) {

    for (int i = 0; i < nhp; i++) {
        if (strcmp(subject[i].id_sub, buf) == 0)
            return i;
    }
    return -1;
}

void  insertSubjectData() {

    int isvalid = 0;
    char id_sub[30];
    char name_sub[30];
    int credit;
    cout << "Enter Subject's ID: " << endl;
    cin >> id_sub;
    isvalid = checkIDSub(id_sub);
    if (isvalid != -1) {
        cout << "Subject already Exists" << endl;
        return;
    }
    cout << "Subject's name: " << endl;
    cin >> name_sub;
    cout << "Subject's credit: " << endl;
    cin >> credit;
    cout << "Added new Subject successfully." << endl;

    ofstream outfile;
    outfile.open("HP.BIN", ios_base::app);

    outfile << id_sub << " " << name_sub << " " << credit << endl;
    strcpy(subject[nhp].id_sub, id_sub);
    strcpy(subject[nhp].name_sub, name_sub);
    subject[nhp].credit = credit;
    nhp++;

    outfile.close();
}

void  addSubjectDetail() {

    char id_sub[30];
    char name_sub[30];
    int credit;

    cout << "Enter Subject's ID: " << endl;
    cin >> id_sub;
    int idx = checkIDSub(id_sub);
    if (idx != -1) {
        int choice;

        do{
            cout << " 1  - Add Subject's name" << endl;
            cout << " 2  - Add Subject Credit" << endl;
            cin >> choice;
        }while((choice != 1) && (choice != 2));

        switch (choice)
        {
            case 1:
                cout << "Subject's name: " << endl;
                cin >> name_sub;
                strcpy(subject[idx].name_sub, name_sub);
                break;
            case 2:
                cout << "Subject's credit: " << endl;
                cin >> credit;
                subject[idx].credit = credit;
                break;
        }
    }
    else cout << "Can't find Student" << endl;
}

void  modifySubject() {

    char id_sub[30];
    int isFound = 0;
    int isvalid;
    cout << "Enter Subject's ID: " << endl;
    cin >> id_sub;
    for (int i = 0; i < nhp; i++) {
        if (strcmp(subject[i].id_sub, id_sub) == 0) {
            isFound = 1;
            char id_sub1[30];
            char name_sub[30];
            int credit;
            cout << "Enter new Subject's ID: " << endl;
            cin >> id_sub1;
            isvalid = checkIDSub(id_sub1);
            if (isvalid != -1) {
                cout << "Subject already exist" << endl;
                return;
            }
            cout << "Subject's name: " << endl;
            cin >> name_sub;
            cout << "Subject's credit: " << endl;
            cin >> credit;
            cout << "Modified Subject successfully." << endl;
            ofstream outfile;
            outfile.open("HP.BIN", ios_base::app);
            outfile << id_sub << " " << name_sub << " " << credit << endl;
            strcpy(subject[i].id_sub, id_sub1);
            strcpy(subject[i].name_sub, name_sub);
            subject[i].credit = credit;

            outfile.close();
        }
    }
    if (!isFound) {
        cout << "Subject not exist" << endl;
    }
    else cout << "Modified Subject" << endl;
}

void  deleteSubjectData() {
    char id_sub[30];
    int isFound = 0;
    cout << "Enter Subject's ID: " << endl;
    cin.getline(id_sub,30);
    cin.ignore();

    for (int i = 0; i < nhp; i++) {
        if (strcmp(subject[i].id_sub, id_sub) == 0) {
            isFound = 1;
            subject[i] = subject[nhp - 1];
            nsv--;
            for (int j = 0; j < ndt;) {
                if (strcmp(grade[j].id_sub, id_sub) == 0) {
                    grade[j] = grade[ndt - 1];
                    ndt--;
                }
                else j++;
            }
            break;
        }
    }
    if (isFound!=0) {
        cout << "Subject not Exist" << endl;
    } else{
        cout << "Deleted Subject";
    }
}


////////////////////////////////////////// Grade ////////////////////////////////////////



float roundIt(float x){
    float frac = x - (int) x;
    if(frac < 0.299)
        return (int) x;
    if((frac >= 0.299) && (frac <= 0.699))
        return (int) x + 0.5;
    if(frac > 0.699)
        return (int) x + 1;
}
bool checkValidGrade(float mark){
    if (mark < 0|| mark > 10)
        return 0;
    return 1;
}
void insertGradeData() {

    int isvalid = 0;
    char id_num[30];
    char id_sub[30];
    float mark;
    cout << "Enter Subject's ID: " << endl;
    cin >> id_sub;
    isvalid = checkIDSub(id_sub);
    if (isvalid == -1) {
        cout << "Subject Not Exist." << endl;
        return;
    }
    cout << "Enter Student's ID: " << endl;

    while (cin >> id_num)
    {
        isvalid = checkIDNum(id_num);
        if (isvalid != -1) {
            break;
        }
        else {
            cout << "Student Not Exist. Try again: " << endl;
        }
    }
    isvalid = checkSVHPDT(id_num, id_sub);
    if (isvalid != -1) {
        cout << "Grade already Exists." << endl;
    }
    // Enter Grade that is not negative
    do{
        cout << "Enter Student's Grade for this Subject: " << endl;

        cin >> mark;
    }while (!checkValidGrade(mark));
    cout << "Added new Grade successfully." << endl;

    ofstream outfile;
    outfile.open("DT.BIN", ios_base::app);


    outfile << id_sub << " " << id_num << " " << mark << endl;
    strcpy(grade[ndt].id_sub, id_sub);
    strcpy(grade[ndt].id_num, id_num);
    grade[ndt].mark = roundIt(mark);
    ndt++;

    outfile.close();

}
void  addGradeDetail() {

    char id_num[30];
    char id_sub[30];
    float mark;
    cout << "Enter Students's ID" << endl;
    cin >> id_num;
    cout << "Enter Subject's ID: " << endl;
    cin >> id_sub;
    int idx = checkSVHPDT(id_num, id_sub);
    if (idx != -1) {

        // Enter Grade that is not negative
        do{
            cout << "Enter Student's Grade for this Subject: " << endl;

            cin >> mark;
        }while (!checkValidGrade(mark));
        grade[idx].mark = roundIt(mark);
    }
    else cout << "Can't find Student." << endl;
}

void  modifyGrade(){
    int isFound = 0;
    char id_num1[30];
    char id_sub1[30];

    cout << "Enter Students's ID" << endl;
    cin.ignore();
    cin.getline(id_num1,30);
    cout << "Enter Subject's ID: " << endl;
    cin.ignore();
    cin.getline(id_sub1,30);

    for (int i = 0; i < nsv; i++) {
        if (strcmp(grade[i].id_sub, id_sub1) == 0 && strcmp(grade[i].id_num, id_num1) == 0) {
            isFound = 1;
            int isvalid = 0;
            char id_num[30];
            char id_sub[30];
            float mark;
            cout << "Enter Subject's ID: " << endl;
            cin.getline(id_sub,30);
            isvalid = checkIDSub(id_sub);
            if (isvalid == -1) {
                cout << "Subject not Exist." << endl;
                return;
            }
            cout << "Enter Students's ID" << endl;

            while (cin >> id_num)
            {
                isvalid = checkIDNum(id_num);
                if (isvalid != -1) {
                    break;
                }
                else {
                    cout << "Student not Exist. Try again: " << endl;
                }
            }

            isvalid = checkSVHPDT(id_num, id_sub);
            if (isvalid != -1) {
                cout << "Grade arealdy exist." << endl;
            }
            // Enter Grade that is not negative
            do{
                cout << "Enter Student's Grade for this Subject: " << endl;

                cin >> mark;
            }while (!checkValidGrade(mark));
            cout << "Modified Grade successfully." << endl;
            ofstream outfile;
            outfile.open("DT.BIN", ios_base::app);
            outfile << id_sub << " " << id_num << " " << mark << endl;
            strcpy(grade[i].id_sub, id_sub);
            strcpy(grade[i].id_num, id_num);
            grade[i].mark = roundIt(mark);
            outfile.close();
        }
    }
    if (!isFound) {
        cout << "Grade not Exist" << endl;
    }
    else cout << "Modified Grade." << endl;
}

void deleteGradeData() {
    char id_num[30];
    int isFound = 0;
    cout << "Enter Student's ID: " << endl;
    cin.getline(id_num,30);
    cin.ignore();

    for (int j = 0; j < ndt;) {
        if (strcmp(grade[j].id_num, id_num) == 0) {
            isFound = 1;
            grade[j] = grade[ndt - 1];
            ndt--;
        }
        else j++;
    }
    if (!isFound) {
        cout << "Student not Exist" << endl;
    }
    else cout << "Deleted Student's Grade" << endl;
}

////////////////////////////////////// Statistics///////////////////////////////////////////

void showStudentFailed() {
    char id_sub[30];
    int isFound = 0;
    cout << "Enter Subject's ID: " << endl;
    cin >> id_sub;
    cout << "ID Number \t" << "Full name \t" << endl;
    for (int i = 0; i < ndt; i++) {
        if (strcmp(grade[i].id_sub, id_sub) == 0 && grade[i].mark < 4) {
            int idx = checkIDNum(grade[i].id_num);
            if (idx != -1) cout << grade[i].id_num << "\t" << student[idx].name << endl;
        }
    }
}

void showSubjectFailed() {

    char id_num[30];
    int isFound = 0;
    cout << "Enter Subject's ID: " << endl;
    cin >> id_num;
    cout << "Subjects which has failing students:" << endl;
    for (int i = 0; i < ndt; i++) {
        if (strcmp(grade[i].id_num, id_num) == 0 && grade[i].mark < 4) {
            cout << "- " << grade[i].id_sub << endl;
        }
    }
}

void showGPA() {
    char id_num[30];
    int isFound = 0;
    cout << "Enter Student's ID: " << endl;
    cin >> id_num;
    for (int i = 0; i < nsv; i++) {
        if (strcmp(student[i].id_num, id_num) == 0) {
            isFound = 1;
            cout << "Student's GPA " << id_num << " :" << student[i].gpa << endl;

            break;
        }
    }
    if (!isFound) {
        cout << "Student not Exist" << endl;
    }
}

//Rounding Floating Point Number To two Decimal Places
float roundGPA(float var)
{
    float value = (int)(var * 100 + .5);
    return (float)value / 100;
}


void calculateGPA() {

    for (int i = 0; i < nsv; i++) {
        float sum_grade = 0;
        float sum_credit = 0;
        for (int j = 0; j < ndt; j++){
            if(strcmp(student[i].id_num, grade[j].id_num) == 0){
                for(int k = 0; k < nhp; k++){
                    if(strcmp(grade[j].id_sub, subject[k].id_sub) == 0){
                        sum_grade += grade[j].mark * subject[k].credit;
                        sum_credit += subject[k].credit;
                    }
                }
            }
        }
        student[i].gpa = roundGPA(sum_grade / sum_credit);
    }
}


//////////////////////////////////////// Control Menu ///////////////////////////////////

void mainMenu();

void insertData() {
    int choice;

    do {
        cout << "*******************************************************************" << endl;
        cout << " 1  - Input Student Data" << endl;
        cout << " 2  - Input Subject Data" << endl;
        cout << " 3  - Input Grade Data" << endl;
        cout << " 4  - Back " << endl;
        cout << " 0  - End program" << endl;
        cout << " Your choice: ";
        cin >> choice;
        cout << "*******************************************************************" << endl;

        switch (choice)
        {
            case 1:
                cout << " 1  - Input Student Data" << endl;
                //st.loadStudent();
                insertStudentData();
                break;
            case 2:
                cout << " 2  - Input Subject Data" << endl;
                //sj.loadSubject();
                insertSubjectData();
                //sj.saveToFileSubject();
                break;
            case 3:
                cout << " 3  - Input Grade Data" << endl;
                //gr.loadGrade();
                insertGradeData();
                //gr.saveToFileGrade();
                break;
            case 4:
                mainMenu();
                break;
            case 0:
                cout << "End of Program.\n";
                exit(0);
            default:
                cout << "Not a Valid Choice. \n";
                cout << "Choose again.\n";
                cin >> choice;
                break;
        }
        system("pause");
        system("cls");
    } while ((choice != 0) && (choice != 4));
}

void updateData();

void addDetails() {
    int choice;

    do {
        cout << "*******************************************************************" << endl;
        cout << " 1  - Add Student's Details" << endl;
        cout << " 2  - Add Subject's Details" << endl;
        cout << " 3  - Add Grade's Details" << endl;
        cout << " 4  - Back" << endl;
        cout << " 0  - End program " << endl;
        cout << " Your choice: ";
        cin >> choice;
        cout << "*******************************************************************" << endl;

        switch (choice)
        {
            case 1:
                addStudentDetail();
                break;
            case 2:
                addSubjectDetail();
                break;
            case 3:
                addGradeDetail();
                break;
            case 4:
                mainMenu();
            case 0:
                cout << "End of Program.\n";
                exit(0);
            default:
                cout << "Not a Valid Choice. \n";
                cout << "Choose again.\n";
                cin >> choice;
                break;
        }
        system("pause");
        system("cls");
    } while ((choice != 4) && (choice != 0));
}

void modify() {
    int choice;

    do {
        cout << "*******************************************************************" << endl;
        cout << " 1  - Modify Student" << endl;
        cout << " 2  - Modify Subject" << endl;
        cout << " 3  - Modify Grade" << endl;
        cout << " 4  - Back " << endl;
        cout << " 0  - End program" << endl;
        cout << " Your choice: ";
        cin >> choice;
        cout << "*******************************************************************" << endl;

        switch (choice)
        {
            case 1:
                modifyStudent();
                break;
            case 2:
                modifySubject();
                break;
            case 3:
                modifyGrade();

                break;
            case 4:
                updateData();
                break;
            case 0:
                cout << "End of Program.\n";
                exit(0);
            default:
                cout << "Not a Valid Choice. \n";
                cout << "Choose again.\n";
                cin >> choice;
                break;
        }
        system("pause");
        system("cls");
    }while ((choice != 4) && (choice != 0));
}

void deleteData() {
    int choice;

    do {
        cout << "*******************************************************************" << endl;
        cout << " 1  - Delete Student" << endl;
        cout << " 2  - Delete Subject" << endl;
        cout << " 3  - Delete Grade" << endl;
        cout << " 4  - Back " << endl;
        cout << " 0  - End Program" << endl;
        cout << " Your choice: ";
        cin >> choice;
        cout << "*******************************************************************" << endl;

        switch (choice)
        {
            case 1:
                deleteStudentData();
                break;
            case 2:
                deleteSubjectData();
                break;
            case 3:
                deleteGradeData();
                break;
            case 4:
                updateData();
                break;
            case 0:
                cout << "End of Program.\n";
                exit(0);
            default:
                cout << "Not a Valid Choice. \n";
                cout << "Choose again.\n";
                break;
        }
        system("pause");
        system("cls");
    }while ((choice != 4) && (choice != 0));
}

void updateData(){

    int choice;

    do {
        cout << "*******************************************************************" << endl;
        cout << " 1  - Add details" << endl;
        cout << " 2  - Delete" << endl;
        cout << " 3  - Modify" << endl;
        cout << " 4  - Back " << endl;
        cout << " 0  - End Program" << endl;
        cout << " Your choice: ";
        cin >> choice;
        cout << "*******************************************************************" << endl;
        switch (choice)
        {
            case 1:
                addDetails();
                break;
            case 2:
                deleteData();
                break;
            case 3:
                modify();
                break;
            case 4:
                mainMenu();
                break;
            case 0:
                cout << "End of Program.\n";
                exit(0);
            default:
                cout << "Not a Valid Choice. \n";
                cout << "Choose again.\n";
                cin >> choice;
                break;
        }
        system("pause");
        system("cls");
    } while ((choice != 4) && (choice != 0));
}

void mainMenu(){
    int choice;

    do {
        cout << "************** POINT MANAGEMENT PROGRAM***************************" << endl;
        cout << " 1  - Insert Data" << endl;
        cout << " 2  - Update Data" << endl;
        cout << " 3  - Calculate GPA" << endl;
        cout << " 4  - Show Failing Student" << endl;
        cout << " 5  - Show Subjects that has Failing Student" << endl;
        cout << " 6  - Show GPA" << endl;
        cout << " 0  - End Program " << endl;
        cout << "Your choice: ";
        cin >> choice;
        cout << "*******************************************************************" << endl;

        switch (choice)
        {
            case 1:
                cout << " 1  - Insert Data" << endl;
                insertData();
                break;
            case 2:
                cout << " 2  - Update Data" << endl;
                updateData();
                break;
            case 3:
                cout << " 3  - Calculate GPA" << endl;
                calculateGPA();
                cout << "Calculated Successfully" << endl;
                break;
            case 4:
                cout << " 4  - Show Failing Student" << endl;
                showStudentFailed();
                break;
            case 5:
                cout << " 5  - Show Subjects that has Failing Student" << endl;
                showSubjectFailed();
                break;
            case 6:
                cout << " 6  - Show GPA" << endl;
                break;
            case 0:
                cout << "End of Program.\n";
                exit(0);
            default:
                cout << "Not a Valid Choice. \n";
                cout << "Choose again.\n";
                cin >> choice;
                break;
        }
        system("pause");
        system("cls");
    }while (choice != 0);
}

int main() {
    ofstream file("output1.txt");
    if (!file)
    {
        cout << "Khong the mo file.";
        return 1;
    }
    nsv = 0; // so luong sinh vien
    nhp = 0; // so luong hoc phan
    ndt = 0; // so luong diem thi

    stt = 0;

    mainMenu();
    file.close();
    cout << "Da ghi quá trình nhập và kết quả vào tệp output.txt." << endl;
    return 0;
}

