/*******************************************************************************
 * Name    : Student.cpp
 * Author  : Michael Reilly
 * Version : 1.0
 * Date    : September 6, 2019
 * Description : Makes students with their name, gpa, and id# and finds all the failing students.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
 
#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>

using namespace std;

class Student {

private:
	// Member variables
	string first_, last_;
	float gpa_;
	int id_;
	
public:
	//Constructor using an initializer list
	Student(string first, string last, float gpa, int id): first_{first}, last_{last}, gpa_{gpa}, id_{id} {};
	string full_name() const{
		string first = first_+" "+last_;
		return first;
	}
	
	int id() const{
		return id_;
	}
	
	float gpa() const{
		float gpa=(int)(gpa_*100+.5);
		return (float)gpa/100;
	}
	
	void print_info() const{
		cout << first_ << " " << last_ << ", GPA: " << fixed << setprecision(2) << gpa_ << ", ID: " << id_ << endl;
	}
	};
	/** 
	 * Takes a vector of Student objects, returns a new vector
	 * with all Students whose GPA is < 1.0.
	 */
	vector<Student> find_failing_students(const vector<Student> &students) {
		// Iterates through the students vector, appending each student whose gpa is
		// less than 1.0 to the failing_students vector
		vector<Student> failing_students;
		for(size_t i = 0; i < students.size(); i++){
			if(students[i].gpa() < 1.0){
				failing_students.push_back(students[i]);
			}
		}
		return failing_students;
	}
	/**
	 * Takes a vector of Student objects and prints them to the screen
	 */
	void print_students(const vector<Student> &students){
		for(size_t i = 0; i < students.size(); i++){
			students[i].print_info();
		}
	}
	/**
	 * Allows the user to enter information for multiple students, then
	 * find those students whose GPA is below 1.0 and prints them to the screen
	 */
int main() {
	string first_name, last_name;
	float gpa;
	int id;
	char repeat;
	vector<Student> students;
		
	do{
		cout << "Enter student's first name: ";
		cin >> first_name;
		cout << "Enter student's last name: ";
		cin >> last_name;
		gpa=-1;
		while (gpa <0 || gpa>4){
			cout << "Enter student's GPA (0.0-4.0): ";
			cin >> gpa;
		}
		cout << "Enter student's ID: ";
		cin >> id;
		students.push_back(Student(first_name, last_name, gpa, id));
		cout <<  "Add another student to database (Y/N)? ";
		cin >> repeat;
	}
	while(repeat == 'Y' || repeat =='y');
	
	cout << endl << "All students:" << endl;
	print_students(students);
	
	cout << endl << "Failing students:";
	// Prints a space and the word 'None' on the same line if no students are failing
	// Otherwise, print each failing student on a seperate line
	vector<Student> failing_students=find_failing_students(students);
	if(failing_students.size()==0){
		cout << " None" << endl;
	}
	else{
		cout << endl;
		for(size_t i = 0; i < failing_students.size(); i++){
			failing_students[i].print_info();
			}
	}
	return 0;
}