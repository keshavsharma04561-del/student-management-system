#include <stdio.h>
#include <string.h>
#define MAX 100

struct Student {
    int roll;
    char name[50];
    float marks;
};

struct Student students[MAX];
int count = 0;

void saveToFile() {
    FILE *fp = fopen("students.dat", "wb");
    if (fp == null) return;
    fwrite(&count, sizeof(int), 1, fp);
    fwrite(students, sizeof(struct Student), count, fp);
    fclose(fp);
}

void loadFromFile() {
    FILE *fp = fopen("students.dat", "rb");
    if (fp == null) return;
    fread(&count, sizeof(int), 1, fp);
    fread(students, sizeof(struct Student), count, fp);
    fclose(fp);
}

int login() {
    char username[20], password[20];
    printf("\n===== LOGIN =====\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);
    if (strcmp(username, "admin") == 0 && strcmp(password, "1234") == 0) {
        printf("Login successful!\n");
        return 1;
    }
    printf("Invalid credentials!\n");
    return 0;
}

void addStudent() {
    if (count >= MAX) {
        printf("Storage full!\n");
        return;
    }

    printf("\nEnter Roll Number: ");
    scanf("%d", &students[count].roll);

    for (int i = 0; i < count; i++) {
        if (students[i].roll == students[count].roll) {
            printf("Duplicate roll not allowed!\n");
            return;
        }
    }

    printf("Enter Name: ");
    scanf(" %[^\n]", students[count].name);

    printf("Enter Marks: ");
    scanf("%f", &students[count].marks);

    count++;
    saveToFile();
    printf("Student added!\n");
}

void displayStudents() {
    if (count == 0) {
        printf("No records found!\n");
        return;
    }

    printf("\n----- STUDENT LIST -----\n");
    for (int i = 0; i < count; i++) {
        printf("\nRoll: %d\n", students[i].roll);
        printf("Name: %s\n", students[i].name);
        printf("Marks: %.2f\n", students[i].marks);
    }
}

void searchByRoll() {
    int roll, found = 0;
    printf("Enter roll number: ");
    scanf("%d", &roll);

    for (int i = 0; i < count; i++) {
        if (students[i].roll == roll) {
            printf("\nFound:\n");
            printf("Roll: %d\n", students[i].roll);
            printf("Name: %s\n", students[i].name);
            printf("Marks: %.2f\n", students[i].marks);
            found = 1;
            break;
        }
    }

    if (!found) printf("Not found!\n");
}

void searchByName() {
    char name[50];
    int found = 0;
    printf("Enter name: ");
    scanf(" %[^\n]", name);

    for (int i = 0; i < count; i++) {
        if (strstr(students[i].name, name) != NULL) {
            printf("\nMatch Found:\n");
            printf("Roll: %d\n", students[i].roll);
            printf("Name: %s\n", students[i].name);
            printf("Marks: %.2f\n", students[i].marks);
            found = 1;
        }
    }

    if (!found) printf("No matching student found!\n");
}

void deleteStudent() {
    int roll, found = 0;
    printf("Enter roll to delete: ");
    scanf("%d", &roll);

    for (int i = 0; i < count; i++) {
        if (students[i].roll == roll) {
            for (int j = i; j < count - 1; j++) {
                students[j] = students[j + 1];
            }
            count--;
            saveToFile();
            printf("Deleted!\n");
            found = 1;
            break;
        }
    }

    if (!found) printf("Not found!\n");
}

void updateStudent() {
    int roll, found = 0;
    printf("Enter roll to update: ");
    scanf("%d", &roll);

    for (int i = 0; i < count; i++) {
        if (students[i].roll == roll) {
            printf("Enter new name: ");
            scanf(" %[^\n]", students[i].name);

            printf("Enter new marks: ");
            scanf("%f", &students[i].marks);

            saveToFile();
            printf("Updated!\n");
            found = 1;
            break;
        }
    }

    if (!found) printf("Not found!\n");
}

void sortStudents() {
    struct Student temp;
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (students[i].marks < students[j].marks) {
                temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
    saveToFile();
    printf("Sorted!\n");
}

int main() {
    int choice;
    loadFromFile();

    if (!login()) return 0;

    while (1) {
        printf("\n===== STUDENT MANAGEMENT SYSTEM =====\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search by Roll\n");
        printf("4. Search by Name\n");
        printf("5. Delete Student\n");
        printf("6. Update Student\n");
        printf("7. Sort by Marks\n");
        printf("8. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchByRoll(); break;
            case 4: searchByName(); break;
            case 5: deleteStudent(); break;
            case 6: updateStudent(); break;
            case 7: sortStudents(); break;
            case 8: return 0;
            default: printf("Invalid choice!\n");
        }
    }
}
