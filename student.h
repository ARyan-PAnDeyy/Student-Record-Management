\
    #ifndef STUDENT_H
    #define STUDENT_H

    typedef struct {
        int id;
        char name[50];
        char course[30];
        int year;
        float cgpa;
    } Student;

    void addStudent(const char *fileName);
    void listStudents(const char *fileName);
    void searchStudent(const char *fileName);
    void updateStudent(const char *fileName);
    void deleteStudent(const char *fileName);

    #endif // STUDENT_H
