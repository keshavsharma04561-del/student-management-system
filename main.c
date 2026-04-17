
//mannu
//Title explation && overview of code 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100
#define USERNAME "admin"
#define PASSWORD "1234"

struct Student {
    int roll;
    char name[50];
    float marks;
    char grade;
};

struct Student students[MAX];
int count = 0;

/* Grade calculation */
char computeGrade(float marks) {
    if (marks >= 90) return 'A';
    else if (marks >= 75) return 'B';
    else if (marks >= 60) return 'C';
    else if (marks >= 45) return 'D';
    else return 'F';
}
//abishek

/* File handling */
void saveToFile() {
    FILE *fp = fopen("students.dat", "wb");
    if (fp == NULL) return;
    fwrite(&count, sizeof(int), 1, fp);
    fwrite(students, sizeof(struct Student), count, fp);
    fclose(fp);
}

void loadFromFile() {
    FILE *fp = fopen("students.dat", "rb");
    if (fp == NULL) return;
    fread(&count, sizeof(int), 1, fp);
    if (count < 0 || count > MAX) count = 0;
    fread(students, sizeof(struct Student), count, fp);
    fclose(fp);
}

//keshav

/* Safe input helpers */
int inputInt() {
    char buffer[50];
    fgets(buffer, sizeof(buffer), stdin);
    int x;
    if (sscanf(buffer, "%d", &x) != 1) return -1;
    return x;
}

float inputFloat() {
    char buffer[50];
    fgets(buffer, sizeof(buffer), stdin);
    float x;
    if (sscanf(buffer, "%f", &x) != 1) return -1;
    return x;
}

/* Login (unlimited attempts) */
int login() {
    char username[30], password[30];

    printf("\n===== STUDENT MANAGEMENT SYSTEM =====\n");

    while (1) {
        printf("\n--- Login ---\n");

        printf("Username: ");
        fgets(username, sizeof(username), stdin);
        username[strcspn(username, "\n")] = '\0';

        printf("Password: ");
        fgets(password, sizeof(password), stdin);
        password[strcspn(password, "\n")] = '\0';

        if (strcmp(username, USERNAME) == 0 &&
            strcmp(password, PASSWORD) == 0) {
            printf("\nLogin successful!\n");
            return 1;
        }

        printf("Invalid credentials! Try again.\n");
    }
}
//priyansh

/* Add Student */
void addStudent() {
    if (count >= MAX) {
        printf("Storage full!\n");
        return;
    }

    printf("Enter Roll Number: ");
    int roll = inputInt();
    if (roll == -1) { printf("Invalid input!\n"); return; }

    for (int i = 0; i < count; i++) {
        if (students[i].roll == roll) {
            printf("Roll already exists!\n");
            return;
        }
    }

    printf("Enter Name: ");
    fgets(students[count].name, 50, stdin);
    students[count].name[strcspn(students[count].name, "\n")] = '\0';

    printf("Enter Marks (0-100): ");
    float marks = inputFloat();
    if (marks < 0 || marks > 100) {
        printf("Invalid marks!\n");
        return;
    }

    students[count].roll = roll;
    students[count].marks = marks;
    students[count].grade = computeGrade(marks);
    count++;

    saveToFile();
    printf("Student added successfully!\n");
}

/* Display */
void displayStudents() {
    if (count == 0) {
        printf("No records!\n");
        return;
    }

    printf("\n%-6s %-20s %-8s %-6s\n", "Roll", "Name", "Marks", "Grade");
    for (int i = 0; i < count; i++) {
        printf("%-6d %-20s %-8.2f %-6c\n",
               students[i].roll,
               students[i].name,
               students[i].marks,
               students[i].grade);
    }
}
//hiren
/* Search by Roll */
void searchByRoll() {
    printf("Enter roll: ");
    int roll = inputInt();

    for (int i = 0; i < count; i++) {
        if (students[i].roll == roll) {
            printf("\nFound:\n");
            printf("Name: %s\nMarks: %.2f\nGrade: %c\n",
                   students[i].name,
                   students[i].marks,
                   students[i].grade);
            return;
        }
    }
    printf("Not found!\n");
}

/* Delete */
void deleteStudent() {
    printf("Enter roll to delete: ");
    int roll = inputInt();

    for (int i = 0; i < count; i++) {
        if (students[i].roll == roll) {
            for (int j = i; j < count - 1; j++) {
                students[j] = students[j + 1];
            }
            count--;
            saveToFile();
            printf("Deleted successfully!\n");
            return;
        }
    }
    printf("Not found!\n");
}

/* Update */
void updateStudent() {
    printf("Enter roll to update: ");
    int roll = inputInt();

    for (int i = 0; i < count; i++) {
        if (students[i].roll == roll) {

            printf("Enter new name: ");
            fgets(students[i].name, 50, stdin);
            students[i].name[strcspn(students[i].name, "\n")] = '\0';

            printf("Enter new marks: ");
            float marks = inputFloat();
            if (marks >= 0 && marks <= 100) {
                students[i].marks = marks;
                students[i].grade = computeGrade(marks);
            }

            saveToFile();
            printf("Updated successfully!\n");
            return;
        }
    }
    printf("Not found!\n");
}
//vaibhav

/* Sort */
void sortStudents() {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (students[i].marks < students[j].marks) {
                struct Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
    saveToFile();
    printf("Sorted by marks!\n");
}

/* Stats */
void showStats() {
    if (count == 0) return;

    float total = 0, max = students[0].marks, min = students[0].marks;

    for (int i = 0; i < count; i++) {
        total += students[i].marks;
        if (students[i].marks > max) max = students[i].marks;
        if (students[i].marks < min) min = students[i].marks;
    }

    printf("\nAverage: %.2f\n", total / count);
    printf("Highest: %.2f\n", max);
    printf("Lowest : %.2f\n", min);
}

/* Main */
int main() {
    loadFromFile();

    if (!login()) return 1;

    int choice;

    while (1) {
        printf("\n1.Add 2.Display 3.Search 4.Delete 5.Update 6.Sort 7.Stats 8.Exit\n");
        printf("Enter choice: ");

        choice = inputInt();

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchByRoll(); break;
            case 4: deleteStudent(); break;
            case 5: updateStudent(); break;
            case 6: sortStudents(); break;
            case 7: showStats(); break;
            case 8: return 0;
            default: printf("Invalid choice!\n");
        }
    }
}                                 | **Person** | **Name** | **Contribution**                                                                                                      |
| ---------- | -------- | --------------------------------------------------------------------------------------------------------------------- |
| Person 1   | Mannu    | Designed program structure, defined `struct Student`, macros (`MAX`, login credentials), and handled global variables |
| Person 2   | Abhishek | Implemented grade calculation (`computeGrade`) and file handling (`saveToFile`, `loadFromFile`)                       |
| Person 3   | Keshav   | Developed safe input functions (`inputInt`, `inputFloat`) and login system                                            |
| Person 4   | Priyansh | Built core features: adding students (`addStudent`) and displaying records (`displayStudents`)                        |
| Person 5   | Hiren    | Implemented record operations: search, delete, and update functionalities                                             |
| Person 6   | Vaibhav  | Developed sorting, statistics, and main program control (`main` function)                                             |
