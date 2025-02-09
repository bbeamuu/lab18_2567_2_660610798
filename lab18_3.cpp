#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <iomanip>

using namespace std;

struct student {
    string name;
    int id; 
    char gender;
    float gpa;      
};

struct course {
    string name;                     
    int id;                           
    vector<string> lecture_list;          
    vector<student*> student_list;       
};

student* findstudent(const vector<student>& allstudents, int key) {
    for (const auto& s : allstudents) {
        if (s.id == key) return const_cast<student*>(&s); 
    }
    return nullptr; 
}

void printreport(const vector<course>& allcourses) {
    for (const auto& c : allcourses) {
        cout << "-----------------------------------------------------------------------------\n";
        cout << left << setw(20) << "Course:" << c.name << " (" << c.id << ")\n\n";
        cout << left << setw(20) << "Lecturers:";
        for (size_t j = 0; j < c.lecture_list.size(); j++) {
            if (j != 0) cout << ", ";
            cout << c.lecture_list[j];
        }
        cout << "\n\n";
        
        cout << left << setw(20) << "Students:"; 
        if (!c.student_list.empty()) {
            cout << left << setw(20) << c.student_list[0]->name;
            cout << left << setw(10) << c.student_list[0]->id;
            cout << left << setw(3) << c.student_list[0]->gender;
            cout << left << setw(5) << setprecision(2) << fixed << c.student_list[0]->gpa; 
        }
        

        for (size_t i = 1; i < c.student_list.size(); i++) {
            cout << "\n" << left << setw(20) << " "; 
            cout << left << setw(20) << c.student_list[i]->name; 
            cout << left << setw(10) << c.student_list[i]->id; 
            cout << left << setw(3) << c.student_list[i]->gender; 
            cout << left << setw(5) << setprecision(2) << fixed << c.student_list[i]->gpa; 
        } 
        cout << "\n"; 
    }
    cout << "-----------------------------------------------------------------------------\n";
}


int main() {
    ifstream student_file("students.txt");
    ifstream course_file("courses.txt");
    vector<student> allstudents;
    vector<course> allcourses;

    string textline;


    while (getline(student_file, textline)) {
        student s; 
        char name[100];
        sscanf(textline.c_str(), "%[^,],%d,%c,%f", name, &s.id, &s.gender, &s.gpa);
        s.name = name;
        allstudents.push_back(s); 		
    }
    
    int state = 1;
    while (getline(course_file, textline)) {
        if (state == 1) {
            course c;
            int loc = textline.find_first_of('(');
            c.name = textline.substr(0, loc - 1);
            c.id = atoi(textline.substr(loc + 1, 5).c_str());
            allcourses.push_back(c);
            state = 2;			
        } else if (state == 2) {
            if (textline == "> Students") {
                state = 3;
            } else if (textline != "> Lectures") {
                allcourses.back().lecture_list.push_back(textline);
            }			
        } else {
            if (textline == "---------------------------------------") {
                state = 1;
            } else {
                int student_id = atoi(textline.c_str());
                student *p = findstudent(allstudents, student_id);
                if (p != nullptr) {
                    allcourses.back().student_list.push_back(p);
                }
            }
        }
    }
    
    printreport(allcourses);
    
    return 0;
}
