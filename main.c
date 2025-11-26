\
    #include <stdio.h>
    #include <stdlib.h>
    #include "student.h"

    void printMenu() {
        printf("\n==== Student Record Management System ====\n");
        printf("1. Add new student\n");
        printf("2. List all students\n");
        printf("3. Search student by ID\n");
        printf("4. Update student by ID\n");
        printf("5. Delete student by ID\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
    }

    int main() {
        int choice;
        const char *fileName = "students.dat";

        while (1) {
            printMenu();
            if (scanf("%d", &choice) != 1) {
                printf("Invalid input. Exiting.\n");
                break;
            }
            getchar(); // clear newline from buffer

            switch (choice) {
                case 1:
                    addStudent(fileName);
                    break;
                case 2:
                    listStudents(fileName);
                    break;
                case 3:
                    searchStudent(fileName);
                    break;
                case 4:
                    updateStudent(fileName);
                    break;
                case 5:
                    deleteStudent(fileName);
                    break;
                case 0:
                    printf("Exiting program. Goodbye!\n");
                    exit(0);
                default:
                    printf("Invalid choice. Please try again.\n");
            }
        }

        return 0;
    }
