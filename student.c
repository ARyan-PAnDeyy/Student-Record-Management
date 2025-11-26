\
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "student.h"

    void readString(const char *prompt, char *buffer, int size) {
        printf("%s", prompt);
        if (fgets(buffer, size, stdin) != NULL) {
            size_t len = strlen(buffer);
            if (len > 0 && buffer[len - 1] == '\n') {
                buffer[len - 1] = '\0';
            }
        }
    }

    void addStudent(const char *fileName) {
        FILE *fp = fopen(fileName, "ab");
        if (!fp) {
            printf("Error opening file for writing.\n");
            return;
        }

        Student s;
        printf("\n=== Add New Student ===\n");
        printf("Enter ID (integer): ");
        scanf("%d", &s.id);
        getchar(); // consume newline

        readString("Enter name: ", s.name, sizeof(s.name));
        readString("Enter course: ", s.course, sizeof(s.course));
        printf("Enter year of study: ");
        scanf("%d", &s.year);
        printf("Enter CGPA: ");
        scanf("%f", &s.cgpa);
        getchar(); // consume newline

        fwrite(&s, sizeof(Student), 1, fp);
        fclose(fp);

        printf("Student record added successfully.\n");
    }

    void listStudents(const char *fileName) {
        FILE *fp = fopen(fileName, "rb");
        if (!fp) {
            printf("No records found. File does not exist yet.\n");
            return;
        }

        Student s;
        printf("\n=== All Student Records ===\n");
        printf("%-5s %-20s %-15s %-6s %-6s\n", "ID", "Name", "Course", "Year", "CGPA");
        printf("----------------------------------------------------------\n");

        while (fread(&s, sizeof(Student), 1, fp) == 1) {
            printf("%-5d %-20s %-15s %-6d %-6.2f\n", s.id, s.name, s.course, s.year, s.cgpa);
        }

        fclose(fp);
    }

    void searchStudent(const char *fileName) {
        FILE *fp = fopen(fileName, "rb");
        if (!fp) {
            printf("No records found. File does not exist yet.\n");
            return;
        }

        int id;
        printf("\nEnter student ID to search: ");
        scanf("%d", &id);
        getchar(); // consume newline

        Student s;
        int found = 0;
        while (fread(&s, sizeof(Student), 1, fp) == 1) {
            if (s.id == id) {
                printf("\nRecord found:\n");
                printf("ID: %d\nName: %s\nCourse: %s\nYear: %d\nCGPA: %.2f\n",
                       s.id, s.name, s.course, s.year, s.cgpa);
                found = 1;
                break;
            }
        }

        if (!found) {
            printf("No student found with ID %d.\n", id);
        }

        fclose(fp);
    }

    void updateStudent(const char *fileName) {
        FILE *fp = fopen(fileName, "rb+");
        if (!fp) {
            printf("No records found. File does not exist yet.\n");
            return;
        }

        int id;
        printf("\nEnter student ID to update: ");
        scanf("%d", &id);
        getchar(); // consume newline

        Student s;
        int found = 0;
        long pos;
        while ((pos = ftell(fp)) >= 0 && fread(&s, sizeof(Student), 1, fp) == 1) {
            if (s.id == id) {
                printf("\nCurrent details:\n");
                printf("ID: %d\nName: %s\nCourse: %s\nYear: %d\nCGPA: %.2f\n",
                       s.id, s.name, s.course, s.year, s.cgpa);

                printf("\nEnter new details:\n");
                printf("Enter ID (integer): ");
                scanf("%d", &s.id);
                getchar(); // consume newline

                readString("Enter name: ", s.name, sizeof(s.name));
                readString("Enter course: ", s.course, sizeof(s.course));
                printf("Enter year of study: ");
                scanf("%d", &s.year);
                printf("Enter CGPA: ");
                scanf("%f", &s.cgpa);
                getchar(); // consume newline

                fseek(fp, pos, SEEK_SET);
                fwrite(&s, sizeof(Student), 1, fp);
                printf("Record updated successfully.\n");
                found = 1;
                break;
            }
        }

        if (!found) {
            printf("No student found with ID %d.\n", id);
        }

        fclose(fp);
    }

    void deleteStudent(const char *fileName) {
        FILE *fp = fopen(fileName, "rb");
        if (!fp) {
            printf("No records found. File does not exist yet.\n");
            return;
        }

        int id;
        printf("\nEnter student ID to delete: ");
        scanf("%d", &id);
        getchar(); // consume newline

        FILE *temp = fopen("temp.dat", "wb");
        if (!temp) {
            printf("Error creating temporary file.\n");
            fclose(fp);
            return;
        }

        Student s;
        int found = 0;
        while (fread(&s, sizeof(Student), 1, fp) == 1) {
            if (s.id == id) {
                found = 1; // skip writing this record
            } else {
                fwrite(&s, sizeof(Student), 1, temp);
            }
        }

        fclose(fp);
        fclose(temp);

        if (found) {
            remove(fileName);
            rename("temp.dat", fileName);
            printf("Record deleted successfully.\n");
        } else {
            remove("temp.dat");
            printf("No student found with ID %d.\n", id);
        }
    }
