//**************************************************************************
// This program reads students information from the file Stud.txt, and calculates 
// their cumulative GPA, and produces an updated grade report to display on the 
// monitor as well as to write to the output file ReportsOut.txt
//**************************************************************************

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

//Prints out student id, name, phone number, gender, and class level to monitor and output file.
void display(string id, string last_name, string first_name, char middle_initial,
        string phone_number, char sex, string class_level, ifstream& input_file, 
        ofstream& output_file);

//Converts grade A to 4, B to 3, C to 2, D to 1, and F to 1 for GPA calculation.
int grade_to_point(char grade);

int main() {
    ifstream input_file;
    ofstream output_file;
    
    input_file.open("Stud.txt");
    output_file.open("ReportsOut.txt");

    if (input_file.is_open() && output_file.is_open()) {
        string line;
        string id, last_name, first_name, phone_number, class_level;
        char middle_initial, sex;
        int credits_by_spring, fall_courses;
        double gpa_by_spring, gpa_by_fall;
        while (getline(input_file, line)) {
            stringstream ss;
            ss << line;
            ss >> id >> last_name >> first_name >> middle_initial >> phone_number
                    >> sex >> class_level >> credits_by_spring >> gpa_by_spring >>
                    fall_courses;
            
            display(id, last_name, first_name, middle_initial, phone_number, sex,
                    class_level, input_file, output_file);
            
            if (fall_courses != 0) {
                cout << "Registration of fall 2016: Yes" << endl;
                output_file << "Registration of fall 2016: Yes" << "\r\n";
                cout << "        Unofficial Report Card" << endl;
                output_file << "        Unofficial Report Card" << "\r\n";
                cout << "Course     Credits     Grade" << endl;
                output_file << "Course     Credits     Grade" << "\r\n";
                string subject;
                int credit;
                char grade; 
                int sum = 0, gpa_points = 0;
                for (int i = 1; i <= fall_courses; i++) {
                    ss >> subject >> credit >> grade;
                    cout << subject << "        " << credit << "         " << grade << endl;
                    output_file << subject << "        " << credit << "         " << grade << "\r\n";
                    if (grade != 'W'){
                        sum = sum + credit;
                        gpa_points = gpa_points + (credit * grade_to_point(grade));
                    }
                }
                cout << "Credits for Fall 16: " << sum << endl;
                output_file << "Credits for Fall 16: " << sum << "\r\n";
                cout << "Spring 16 Semester GPA: " << gpa_by_spring << endl;
                output_file << "Spring 16 Semester GPA: " << gpa_by_spring << "\r\n";
                cout << "Total credits: " << credits_by_spring + sum << endl;
                output_file << "Total credits: " << credits_by_spring + sum << "\r\n";
                cout.setf(ios::fixed);
                output_file.setf(ios::fixed);
                cout.setf(ios::showpoint);
                output_file.setf(ios::showpoint);
                cout.precision(2);
                output_file.precision(2);
                gpa_by_fall = ((gpa_by_spring * credits_by_spring) + gpa_points)/ (credits_by_spring + sum); 
                cout << "New cumulative GPA: " << gpa_by_fall << endl;
                output_file << "New cumulative GPA: " << gpa_by_fall << "\r\n";
            } else {
                cout << "Registration of fall 2016: No" << endl;
                output_file << "Registration of fall 2016: No" << "\r\n";
                cout << "Spring 16 Semester GPA: " << gpa_by_spring << endl;
                output_file << "Spring 16 Semester GPA: " << gpa_by_spring << "\r\n";
                cout << "Total credits: " << credits_by_spring << endl;
                output_file << "Total credits: " << credits_by_spring << "\r\n";
            }
        }
    } else {
        cout << "Stud.txt and/or ReportsOut.txt file is not open." << endl;
        output_file << "Stud.txt and/or ReportsOut.txt file is not open." << "\\r\n";
    }
    input_file.close();
    output_file.close();
    return 0;
}

void display(string id, string last_name, string first_name, char middle_initial,
        string phone_number, char sex, string class_level, ifstream& input_file, 
        ofstream& output_file) {
    cout << "***************************************************" << endl;
    output_file << "***************************************************" << "\r\n";
    cout << "Student ID number: " << id << endl;
    output_file << "Student ID number: " << id << "\r\n";
    cout << "Name: " << last_name << ", " << first_name << " " << middle_initial << endl;
    output_file << "Name: " << last_name << ", " << first_name << " " << middle_initial << "\r\n";
    cout << "Tel: " << phone_number << endl;
    output_file << "Tel: " << phone_number << "\r\n";
    cout << "Gender: ";
    output_file << "Gender: ";
    if (sex == 'M') {
        cout << "Male" << endl;
        output_file << "Male" << "\r\n";
    } else {
        cout << "Female" << endl;
        output_file << "Female" << "\r\n";
    }
    cout << "Class Level: ";
    output_file << "Class Level: ";
    if (class_level == "FR") {
        cout << "Freshman" << endl;
        output_file << "Freshman" << "\r\n";
    } else if (class_level == "SO") {
        cout << "Sophomore" << endl;
        output_file << "Sophomore" "\r\n";
    } else if (class_level == "JR") {
        cout << "Junior" << endl;
        output_file << "Junior" "\r\n";
    } else {
        cout << "Senior" << endl;
        output_file << "Senior" "\r\n";
    }
}

int grade_to_point(char grade){
    switch(grade){
        case 'A':
            return 4;
            break;
        case 'B':
            return 3;
            break;
        case 'C':
            return 2;
            break;
        case 'D':
            return 1;
            break;
        case 'F':
            return 0;
            break;
    }
}



