//adding sort feature
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
private:
    vector<Student> students;
    const string filename = "students.txt";

public:
    StudentManager() {
        loadFromFile();
    }

    void addStudent() {
        Student s;
OAOAOAOAOAOA        s.input();
OAOA        students.push_back(s);
OAOAOA        saveToFile();
OAOA        cout << "Student added successfully.\n";
    }
OAOAOA
    void displayStudents() const {
OAOAOAOAOAOA        if (students.empty()) {
OAOA            cout << "No student records found.\n";
            return;
OAOAOA        }
OAOA        cout << "\n--- Student List ---\n";
OAOA        for (const auto& s : students) {
OA            s.display();
        }
OAOAOAOAOA        cout << "---------------------\n";
OAOAOAOAOA    }

OAOAOA    void searchById(int searchId) const {
        auto it = find_if(students.begin(), students.end(), [searchId](const Student& s) {
OAOAOAOAOAOAOAOAOA            return s.id == searchId;
        });

OAOAOA        if (it != students.end()) {
OAOAOAOAOAOA            cout << "Student found:\n";
            it->display();
OAOA        } else {
            cout << "Student with ID " << searchId << " not found.\n";
OAOAOAOAOAOA        }
OAOAOAOA    }

OA    void deleteStudentById(int deleteId) {
OAOAOA        auto it = remove_if(students.begin(), students.end(), [deleteId](const Student& s) {
            return s.id == deleteId;
OAOA        });
OAOAOAOAOA
        if (it != students.end()) {
OAOA            students.erase(it, students.end());
OAOAOA            saveToFile();
OAOAOA            cout << "Student with ID " << deleteId << " deleted successfully.\n";
OAOAOAOA        } else {
            cout << "No student found with ID " << deleteId << ".\n";
        }
OAOAOA    }
OAOAOBOBOB
OAOAOAOAOAOAOA    void updateStudentById(int updateId) {
OAOAOAOAOAOAOAOAOAOAOA        auto it = find_if(students.begin(), students.end(), [updateId](const Student& s) {
            return s.id == updateId;
OAOAOAOAOAOAOAOAOAOAOAOAOAOAOA        });

OAOAOAOA        if (it != students.end()) {
            cout << "Current details:\n";
            it->display();

OAOA            cout << "\nEnter new details:\n";
            Student updatedStudent;
OAOAOAOAOAOAOAOAOA            updatedStudent.id = updateId; // Preserve the original ID
OAOAOAOA            updatedStudent.input();

OBOBOB            *it = updatedStudent;
OBOB            saveToFile();
OBOBOBOBOBOBOB            cout << "Student record updated successfully.\n";
        } else {
OBOBOB            cout << "No student found with ID " << updateId << ".\n";
OBOBOB        }
    }
OBOBOB
    void sortByName() {
OBOBOBOBOBOBOBOBOBOBOBOBOB        sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
            return a.name < b.name;
OBOBOBOBOBOB        });
OBOBOBOBOBOBOBOBOB        cout << "Students sorted by name.\n";
        displayStudents();
OBOBOBOBOBOBOBOBOBOBOBOBOBOBOBOB    }

OBOBOBOB    void sortByAge() {
        sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
OBOBOBOB            return a.age < b.age;
OBOBOBOBOBOBOBOBOBOBOBOBOB        });
        cout << "Students sorted by age.\n";
        displayStudents();
OBOBOBOB    }

OBOBOBOBOBOBOB    void saveToFile() const {
        ofstream outFile(filename);
OBOBOBOB        for (const auto& s : students) {
OBOB            outFile << s.id << ',' << s.name << ',' << s.age << ',' << s.course << '\n';
        }
    }

OB    void loadFromFile() {
        ifstream inFile(filename);
OB        students.clear();
        string line;

        while (getline(inFile, line)) {
OB            Student s;
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
        cout << "6. Update Student by ID\n";
        cout << "7. Sort Students by Name\n";
        cout << "8. Sort Students by Age\n";
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
            case 7:
                manager.sortByName();
                break;
            case 8:
                manager.sortByAge();
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}

