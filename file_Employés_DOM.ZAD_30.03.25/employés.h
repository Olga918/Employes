#pragma once
#ifndef EMPLOYEE_H
#define EMPLOYEE_H

const int MAX_EMPLOYEES = 100;
const int MAX_LENGTH = 50;

struct Employee {
    char lastName[MAX_LENGTH];
    char firstName[MAX_LENGTH];
    int age;
    char position[MAX_LENGTH];
};

extern Employee employees[MAX_EMPLOYEES];
extern int employeeCount;

void loadFromFile(const char* filename);
void saveToFile(const char* filename);
void addEmployee();
void editEmployee(const char* lastName);
void deleteEmployee(const char* lastName);
void searchByLastName(const char* lastName);
void filterEmployees(int age = -1, char startsWith = '\0');
void menu(const char* filename);

#endif