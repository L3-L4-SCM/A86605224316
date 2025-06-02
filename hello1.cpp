
//adding update feature
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>

using namespace std;

class Student {
public:
    int id;
    string name;
    int age;
    string course;

    void input() {
        cout << "Enter Student ID: ";
        while (!(cin >> id)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Enter a valid integer ID: ";
        }
        cin.ignore();

        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Age: ";
        while (!(cin >> age)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Enter a valid age: ";
        }
        cin.ignore();

        cout << "Enter Course: ";
        getline(cin, course);
    }

    void display() const {
        cout << "ID: " << id
             << " | Name: " << name
             << " | Age: " << age
             << " | Course: " << course << endl;
    }
};

class StudentManager {
OAOAOAOAOAprivate:
    vector<Student> students;
    const string filename = "students.txt";
OAOA
OAOAOApublic:
    StudentManager() {
OAOA        loadFromFile();
OAOAOA    }
OAOAOA
OAOAOA    void addStudent() {
        Student s;
OAOAOA        s.input();
        students.push_back(s);
OAOAOAOAOA        saveToFile();
OAOAOA        cout << "Student added successfully.\n";
OAOAOA    }

OAOAOAOAOAOAOAOAOAOAOA    void displayStudents() const {
        if (students.empty()) {
            cout << "No student records found.\n";
OAOAOA            return;
OAOAOAOAOA        }
        cout << "\n--- Student List ---\n";
        for (const auto& s : students) {
OAOAOAOAOAOAOAOAOA            s.display();
        }
        cout << "---------------------\n";
OAOAOAOAOAOAOAOAOA    }

OAOAOAOAOAOAOAOAOAOA    void searchById(int searchId) const {
        auto it = find_if(students.begin(), students.end(), [searchId](const Student& s) {
OA            return s.id == searchId;
OAOAOAOAOAOA        });

OA        if (it != students.end()) {
            cout << "Student found:\n";
OAOAOAOA            it->display();
        } else {
            cout << "Student with ID " << searchId << " not found.\n";
OA        }
    }
OA
OAOA    void deleteStudentById(int deleteId) {
        auto it = remove_if(students.begin(), students.end(), [deleteId](const Student& s) {
            return s.id == deleteId;
        });

        if (it != students.end()) {
            students.erase(it, students.end());
            saveToFile();
            cout << "Student with ID " << deleteId << " deleted successfully.\n";
        } else {
            cout << "No student found with ID " << deleteId << ".\n";
        }
    }

    void updateStudentById(int updateId) {
        auto it = find_if(students.begin(), students.end(), [updateId](const Student& s) {
            return s.id == updateId;
        });

        if (it != students.end()) {
            cout << "Current details:\n";
            it->display();

            cout << "\nEnter new details:\n";
            Student updatedStudent;
            updatedStudent.id = updateId; // Preserve the original ID
            updatedStudent.input();

            *it = updatedStudent;
            saveToFile();
            cout << "Student record updated successfully.\n";
        } else {
            cout << "No student found with ID " << updateId << ".\n";
        }
    }

    void saveToFile() const {
        ofstream outFile(filename);
        for (const auto& s : students) {
            outFile << s.id << ',' << s.name << ',' << s.age << ',' << s.course << '\n';
        }
    }

    void loadFromFile() {
        ifstream inFile(filename);
        students.clear();
        string line;

        while (getline(inFile, line)) {
            Student s;
            size_t pos = 0;

            // Parse ID
            pos = line.find(',');
            s.id = stoi(line.substr(0, pos));
            line.erase(0, pos + 1);

            // Parse Name
            pos = line.find(',');
            s.name = line.substr(0, pos);
            line.erase(0, pos + 1);

            // Parse Age
            pos = line.find(',');
            s.age = stoi(line.substr(0, pos));
            line.erase(0, pos + 1);

            // Remaining is Course
            s.course = line;

            students.push_back(s);
        }
    }
};

// ---------- Main Program ----------
int main() {
    StudentManager manager;
    int choice;

    do {
        cout << "\n===== Student Management Menu =====\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student by ID\n";
        cout << "4. Exit\n";
        cout << "5. Delete Student by ID\n";
        cout << "6. Update Student by ID\n"; // ✅ New Menu Option
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                manager.addStudent();
                break;
            case 2:
                manager.displayStudents();
                break;
            case 3: {
                int id;
                cout << "Enter ID to search: ";
                cin >> id;
                manager.searchById(id);
                break;
            }
            case 4:
                cout << "Exiting the program.\n";
                break;
            case 5: {
                int id;
                cout << "Enter ID to delete: ";
                cin >> id;
                manager.deleteStudentById(id);
                break;
            }
            case 6: {
                int id;
                cout << "Enter ID to update: ";
                cin >> id;
                manager.updateStudentById(id);
                break;
            }
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}

