#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50

typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    int age;
    float grade;
} Student;


void displayMenu() {
    printf("\nStudent Record Management System\n");
    printf("1. Add Student\n");
    printf("2. View All Students\n");
    printf("3. Search Student by ID\n");
    printf("4. Update Student\n");
    printf("5. Delete Student\n");
    printf("6. Save Records to File\n");
    printf("7. Load Records from File\n");
    printf("8. Exit\n");
    printf("Enter your choice: ");
}

Student* addStudent(Student* students, int* count) {
    students = realloc(students, (*count + 1) * sizeof(Student));
    if (students == NULL) {
        printf("Memory allocation failed!\n");
        return students;
    }

    printf("Enter ID: ");
    scanf("%d", &students[*count].id);
    printf("Enter Name: ");
    scanf("%s", students[*count].name);
    printf("Enter Age: ");
    scanf("%d", &students[*count].age);
    printf("Enter Grade: ");
    scanf("%f", &students[*count].grade);

    (*count)++;
    return students;
}

void viewStudents(Student* students, int count) {
    if (count == 0) {
        printf("No records found!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        printf("\nStudent %d:\n", i + 1);
        printf("ID: %d\n", students[i].id);
        printf("Name: %s\n", students[i].name);
        printf("Age: %d\n", students[i].age);
        printf("Grade: %.2f\n", students[i].grade);
    }
}

void searchStudent(Student* students, int count, int id) {
    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            printf("\nStudent Found:\n");
            printf("ID: %d\n", students[i].id);
            printf("Name: %s\n", students[i].name);
            printf("Age: %d\n", students[i].age);
            printf("Grade: %.2f\n", students[i].grade);
            return;
        }
    }
    printf("Student with ID %d not found!\n", id);
}

void updateStudent(Student* students, int count, int id) {
    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            printf("Enter new Name: ");
            scanf("%s", students[i].name);
            printf("Enter new Age: ");
            scanf("%d", &students[i].age);
            printf("Enter new Grade: ");
            scanf("%f", &students[i].grade);
            printf("Record updated successfully!\n");
            return;
        }
    }
    printf("Student with ID %d not found!\n", id);
}

Student* deleteStudent(Student* students, int* count, int id) {
    int found = 0;
    for (int i = 0; i < *count; i++) {
        if (students[i].id == id) {
            found = 1;
            for (int j = i; j < *count - 1; j++) {
                students[j] = students[j + 1];
            }
            (*count)--;
            students = realloc(students, (*count) * sizeof(Student));
            printf("Student deleted successfully!\n");
            break;
        }
    }
    if (!found) {
        printf("Student with ID %d not found!\n", id);
    }
    return students;
}

void saveToFile(Student* students, int count, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fwrite(&count, sizeof(int), 1, file); // Save the number of records
    fwrite(students, sizeof(Student), count, file); // Save the records
    fclose(file);
    printf("Records saved to %s successfully!\n", filename);
}

Student* loadFromFile(Student* students, int* count, const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error opening file!\n");
        return students;
    }

    fread(count, sizeof(int), 1, file); // Read the number of records
    students = realloc(students, (*count) * sizeof(Student));
    fread(students, sizeof(Student), *count, file); // Read the records
    fclose(file);
    printf("Records loaded from %s successfully!\n", filename);
    return students;
}

int main() {
    Student* students = NULL;
    int count = 0;
    int choice, id;
    const char* filename = "students.dat";

    while (1) {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                students = addStudent(students, &count);
                break;
            case 2:
                viewStudents(students, count);
                break;
            case 3:
                printf("Enter ID to search: ");
                scanf("%d", &id);
                searchStudent(students, count, id);
                break;
            case 4:
                printf("Enter ID to update: ");
                scanf("%d", &id);
                updateStudent(students, count, id);
                break;
            case 5:
                printf("Enter ID to delete: ");
                scanf("%d", &id);
                students = deleteStudent(students, &count, id);
                break;
            case 6:
                saveToFile(students, count, filename);
                break;
            case 7:
                students = loadFromFile(students, &count, filename);
                break;
            case 8:
                free(students);
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}