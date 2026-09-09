#include <stdio.h>
#include <stdlib.h>

struct Student
{
    int rollNo;
    char name[50];
    int age;
    char course[50];
    float marks;
};

void addStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();

int main()
{
    int choice;

    while (1)
    {
        printf("\n====================================\n");
        printf("   STUDENT RECORD MANAGEMENT SYSTEM\n");
        printf("====================================\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("====================================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateStudent();
                break;

            case 5:
                deleteStudent();
                break;

            case 6:
                printf("\nProgram exited successfully.\n");
                return 0;

            default:
                printf("\nInvalid choice!\n");
        }
    }
}

void addStudent()
{
    struct Student s;
    FILE *fp;

    fp = fopen("students.dat", "ab");

    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    printf("\nEnter Roll Number: ");
    scanf("%d", &s.rollNo);

    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);

    printf("Enter Age: ");
    scanf("%d", &s.age);

    printf("Enter Course: ");
    scanf(" %[^\n]", s.course);

    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(s), 1, fp);

    fclose(fp);

    printf("\nStudent added successfully!\n");
}

void displayStudents()
{
    struct Student s;
    FILE *fp;

    fp = fopen("students.dat", "rb");

    if (fp == NULL)
    {
        printf("\nNo student records found.\n");
        return;
    }

    printf("\n========== STUDENT RECORDS ==========\n");

    while (fread(&s, sizeof(s), 1, fp) == 1)
    {
        printf("\nRoll Number : %d", s.rollNo);
        printf("\nName        : %s", s.name);
        printf("\nAge         : %d", s.age);
        printf("\nCourse      : %s", s.course);
        printf("\nMarks       : %.2f", s.marks);
        printf("\n-------------------------------------\n");
    }

    fclose(fp);
}

void searchStudent()
{
    struct Student s;
    FILE *fp;
    int rollNo;
    int found = 0;

    fp = fopen("students.dat", "rb");

    if (fp == NULL)
    {
        printf("\nNo student records found.\n");
        return;
    }

    printf("\nEnter Roll Number to search: ");
    scanf("%d", &rollNo);

    while (fread(&s, sizeof(s), 1, fp) == 1)
    {
        if (s.rollNo == rollNo)
        {
            printf("\nStudent Found!\n");
            printf("Roll Number : %d\n", s.rollNo);
            printf("Name        : %s\n", s.name);
            printf("Age         : %d\n", s.age);
            printf("Course      : %s\n", s.course);
            printf("Marks       : %.2f\n", s.marks);

            found = 1;
            break;
        }
    }

    if (found == 0)
        printf("\nStudent not found.\n");

    fclose(fp);
}

void updateStudent()
{
    struct Student s;
    FILE *fp;
    int rollNo;
    int found = 0;

    fp = fopen("students.dat", "rb+");

    if (fp == NULL)
    {
        printf("\nNo student records found.\n");
        return;
    }

    printf("\nEnter Roll Number to update: ");
    scanf("%d", &rollNo);

    while (fread(&s, sizeof(s), 1, fp) == 1)
    {
        if (s.rollNo == rollNo)
        {
            printf("Enter New Name: ");
            scanf(" %[^\n]", s.name);

            printf("Enter New Age: ");
            scanf("%d", &s.age);

            printf("Enter New Course: ");
            scanf(" %[^\n]", s.course);

            printf("Enter New Marks: ");
            scanf("%f", &s.marks);

            fseek(fp, -(long)sizeof(s), SEEK_CUR);

            fwrite(&s, sizeof(s), 1, fp);

            printf("\nStudent updated successfully!\n");

            found = 1;
            break;
        }
    }

    if (found == 0)
        printf("\nStudent not found.\n");

    fclose(fp);
}

void deleteStudent()
{
    struct Student s;
    FILE *fp;
    FILE *temp;
    int rollNo;
    int found = 0;

    fp = fopen("students.dat", "rb");

    if (fp == NULL)
    {
        printf("\nNo student records found.\n");
        return;
    }

    temp = fopen("temp.dat", "wb");

    if (temp == NULL)
    {
        printf("\nError creating temporary file!\n");
        fclose(fp);
        return;
    }

    printf("\nEnter Roll Number to delete: ");
    scanf("%d", &rollNo);

    while (fread(&s, sizeof(s), 1, fp) == 1)
    {
        if (s.rollNo == rollNo)
        {
            found = 1;
        }
        else
        {
            fwrite(&s, sizeof(s), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found == 1)
        printf("\nStudent deleted successfully!\n");
    else
        printf("\nStudent not found.\n");
}
