#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <windows.h> // For Sleep and color (optional, can be removed for portability)

using namespace std;

class Student {
public:
    string name;
    int id;
    string branch;

    // Default constructor
    Student() : id(0) {}
};

void menu();
void addStudentData();
void removeStudentData();
void updateStudentData();
void viewRecord();
void clearRecord();

int choice;

void menu() {
    system("cls"); // Optional: Clears console (Windows-specific)
    Sleep(100);    // Optional: Adds a small delay
    system("color 0b"); // Optional: Sets console color (Windows-specific)
    cout << "\n\t---Student Management System---\n\n";
    cout << "1. View record\n";
    cout << "2. Add student data\n";
    cout << "3. Remove student data\n";
    cout << "4. Update student data\n";
    cout << "5. Clear record\n";
    cout << "6. Exit\n\n";
    cout << "Enter your choice: ";
    cin >> choice;

    // Clear input buffer to avoid issues with next input
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    system("cls"); // Clear screen after input for better UX
    switch (choice) {
        case 1: viewRecord(); break;
        case 2: addStudentData(); break;
        case 3: removeStudentData(); break;
        case 4: updateStudentData(); break;
        case 5: clearRecord(); break;
        case 6:
            system("color 0f"); // Reset color (Windows-specific)
            exit(0);
        default:
            cout << "\n\tInvalid choice...\n";
    }

    cout << "\n\nPress Enter to continue...";
    cin.get();
    menu();
}

void addStudentData() {
    Student s;
    ofstream outFile("Student_record.bin", ios::binary | ios::app);
    if (!outFile) {
        cout << "\n\tERROR 404...\n";
        return;
    }
    cout << "\n\t---Add Student Record---\n\n";
    cout << "Name    : ";
    getline(cin, s.name);
    cout << "Id      : ";
    cin >> s.id;
    cin.ignore(); // Clear buffer
    cout << "Branch  : ";
    getline(cin, s.branch);

    outFile.write(reinterpret_cast<char*>(&s), sizeof(s));
    outFile.close();
    cout << "\nStudent data added successfully!\n";
}

void viewRecord() {
    Student s;
    ifstream inFile("Student_record.bin", ios::binary);
    bool found = false;
    if (!inFile) {
        cout << "\n\tERROR 404...\n";
        return;
    }
    cout << "\n\t---View Record---\n\n";
    while (inFile.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        cout << "Name    : " << s.name << "\nId      : " << s.id << "\nBranch  : " << s.branch << "\n-----------------------\n";
        found = true;
    }
    if (!found) {
        cout << "No record found...\n";
    }
    inFile.close();
}

void removeStudentData() {
    Student s;
    ifstream inFile("Student_record.bin", ios::binary);
    ofstream outFile("temp.bin", ios::binary);
    int id, found = 0;

    if (!inFile || !outFile) {
        cout << "\n\tERROR 404...\n";
        return;
    }
    cout << "\n\t---Remove Student Data---\n\n";
    cout << "Enter Student ID: ";
    cin >> id;
    cin.ignore();

    while (inFile.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        if (s.id != id) {
            outFile.write(reinterpret_cast<char*>(&s), sizeof(s));
        } else {
            found = 1;
        }
    }
    inFile.close();
    outFile.close();

    if (!found) {
        cout << "\nSorry record not found :(\n";
        remove("temp.bin"); // Clean up temp file
        return;
    }

    remove("Student_record.bin");
    rename("temp.bin", "Student_record.bin");
    cout << "\nRecord is successfully deleted :)\n";
}

void updateStudentData() {
    Student s;
    fstream file("Student_record.bin", ios::binary | ios::in | ios::out);
    int id, found = 0;

    if (!file) {
        cout << "\n\tERROR 404...\n";
        return;
    }
    cout << "\n\t---Update Student Record---\n\n";
    cout << "Enter Student ID: ";
    cin >> id;
    cin.ignore();

    while (file.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        if (s.id == id) {
            found = 1;
            break;
        }
    }
    if (!found) {
        cout << "\nSorry record not found :(\n";
        file.close();
        return;
    }
    file.seekg(-static_cast<int>(sizeof(s)), ios::cur);

    cout << "\n\tEnter new details\n\n";
    cout << "Name    : ";
    getline(cin, s.name);
    cout << "Id      : ";
    cin >> s.id;
    cin.ignore();
    cout << "Branch  : ";
    getline(cin, s.branch);

    file.write(reinterpret_cast<char*>(&s), sizeof(s));
    file.close();
    cout << "\nStudent details updated successfully..\n";
}

void clearRecord() {
    ofstream file("Student_record.bin", ios::trunc);
    if (!file) {
        cout << "\n\tERROR 404...\n";
        return;
    }
    cout << "\n\t---Clear Record---\n\n";
    file.close();
    cout << "Record deleted successfully...\n";
}

int main() {
    menu();
    return 0;
}