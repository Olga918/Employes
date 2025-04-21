
#include <iostream>
#include <fstream>
#include <cstring>
#include "employés.h"

using namespace std;

Employee employees[MAX_EMPLOYEES];
int employeeCount = 0;

void loadFromFile(const char* filename) {
    ifstream file(filename);
    if (!file) {
        cout << "File not found.\n";
        return;
    }

    employeeCount = 0;
    while (file >> employees[employeeCount].lastName
        >> employees[employeeCount].firstName
        >> employees[employeeCount].age
        >> employees[employeeCount].position) {
        employeeCount++;
    }

    file.close();
}

void saveToFile(const char* filename) {
    ofstream file(filename);
    for (int i = 0; i < employeeCount; i++) {
        file << employees[i].lastName << " "
            << employees[i].firstName << " "
            << employees[i].age << " "
            << employees[i].position << "\n";
    }
    file.close();
}

void addEmployee() {
    if (employeeCount >= MAX_EMPLOYEES) {
        cout << "Employee limit exceeded.\n";
        return;
    }

    cout << "Surname: ";
    cin >> employees[employeeCount].lastName;
    cout << "Name: ";
    cin >> employees[employeeCount].firstName;
    cout << "Age: ";
    cin >> employees[employeeCount].age;
    cout << "Job title: ";
    cin >> employees[employeeCount].position;

    employeeCount++;
}

void editEmployee(const char* lastName) {
    for (int i = 0; i < employeeCount; i++) {
        if (strcmp(employees[i].lastName, lastName) == 0) {
            cout << "Job title: ";
            cin >> employees[i].firstName;
            cout << "New age: ";
            cin >> employees[i].age;
            cout << "New position: ";
            cin >> employees[i].position;
            return;
        }
    }
    cout << "Employee not found.\n";
}

void deleteEmployee(const char* lastName) {
    for (int i = 0; i < employeeCount; i++) {
        if (strcmp(employees[i].lastName, lastName) == 0) {
            for (int j = i; j < employeeCount - 1; j++) {
                employees[j] = employees[j + 1];
            }
            employeeCount--;
            cout << "The employee has been removed..\n";
            return;
        }
    }
    cout << "Employee not found.\n";
}

void searchByLastName(const char* lastName) {
    for (int i = 0; i < employeeCount; i++) {
        if (strcmp(employees[i].lastName, lastName) == 0) {
            cout << employees[i].lastName << " "
                << employees[i].firstName << ", "
                << employees[i].age << ", "
                << employees[i].position << "\n";
        }
    }
}

void filterEmployees(int age, char startsWith) {
    for (int i = 0; i < employeeCount; i++) {
        if ((age != -1 && employees[i].age == age) ||
            (startsWith != '\0' && employees[i].lastName[0] == startsWith)) {
            cout << employees[i].lastName << " "
                << employees[i].firstName << ", "
                << employees[i].age << ", "
                << employees[i].position << "\n";
        }
    }
}

void menu(const char* filename) {
    int choice;
    do {
        cout << "\n1. Add\n2. Edit\n3. Delete\n4. Search by last name\n";
        cout << "5. Output by age or first letter\n6. Save to file\n0. Exit\n";
        cout << "Choice: ";
        cin >> choice;
        char input[MAX_LENGTH];
        int age;
        switch (choice) {
        case 1: addEmployee(); break;
        case 2:
            cout << "Employee's last name: ";
            cin >> input;
            editEmployee(input);
            break;
        case 3:
            cout << "Employee's last name: ";
            cin >> input;
            deleteEmployee(input);
            break;
        case 4:
            cout << "Surname: ";
            cin >> input;
            searchByLastName(input);
            break;
        case 5:
            cout << "Filter (1 - By age, 2 - By letter): ";
            cin >> choice;
            if (choice == 1) {
                cout << "Age: ";
                cin >> age;
                filterEmployees(age, '\0');
            }
            else {
                char ch;
                cout << "Letter: ";
                cin >> ch;
                filterEmployees(-1, ch);
            }
            break;
        case 6:
            saveToFile(filename);
            break;
        }
    } while (choice != 0);

    saveToFile(filename);
}
