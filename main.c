#include <stdio.h>
#include <stdlib.h>
#include<windows.h>

COORD coord={0,0};

 void gotoxy(int x,int y)
 {
   coord.X=x;
   coord.Y=y;
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
 }

void SetColor(int ForgC)
 {
    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}

typedef struct subject subject;
typedef struct student student;

struct subject
{
    char subName[100];
    float score;
};

enum Grade
{
    A,B,C,D,F
};

struct student
{
    int ID;
    char name[100];
    subject *subjects;
    float average;
    enum Grade grade;
};

float calculateAverage(subject* subjects,int numOfSubjects)
{
    float sum =0;
    for(int i=0; i<numOfSubjects; i++)
    {
        sum+= subjects[i].score;
    }
    return (sum / numOfSubjects);
}

char calculateGrade(float average)
{
    if(average >= 90)
    {
        return 'A';
                }
    else if (average >= 80 && average <90)
    {
        return 'B';
    }
    else if (average >= 70 && average <80)
    {
        return 'C';
    }
    else if (average >= 60 && average <70)
    {
        return 'D';
    }
    else if (average < 60)
    {
        return 'F';
    }
}

void addStudent(student** studentsArray, int *numOfStudents, int *numOfSubjects)
{
    printf(" Please enter student Details\n");
    *studentsArray = realloc(*studentsArray, (*numOfStudents+1)* sizeof(student));
    int sID;
                printf("   Student ID: ");
                scanf("%d", &sID);
                for(int i=0; i<*numOfStudents; i++)
                {
                    while((*studentsArray)[i].ID == sID)
                    {
                        SetColor(4);
                        printf("ID is already used. Please enter another ID.\n");
                        SetColor(255);
                        printf("   Student ID: ");
                        scanf("%d", &sID);
                    }
                }
                (*studentsArray)[*numOfStudents].ID = sID;
                printf("   Student name: ");
                scanf("%s", (*studentsArray)[*numOfStudents].name);
                printf("   Number of subjects: ");
                scanf("%d", numOfSubjects);
                (*studentsArray)[*numOfStudents].subjects = (subject *) malloc(*numOfSubjects * sizeof(subject));

                for(int i=0; i<*numOfSubjects; i++)
                {
                    float subscore;
                    printf("   Subject %d name: ",i+1);
                    scanf("%s", (*studentsArray)[*numOfStudents].subjects[i].subName);
                    printf("   Subject %d score: ",i+1);
                    scanf("%f", &subscore);
                    while(!(subscore>=0 && subscore<=100))
                    {
                        SetColor(4);
                        printf("*================================================*\n");
                        printf("     Score must be between 0 and 100.\n");
                        SetColor(255);
                        printf("   Subject %d score: ",i+1);
                        scanf("%f", &subscore);
                    }
                    (*studentsArray)[*numOfStudents].subjects[i].score = subscore;
                }
                (*studentsArray)[*numOfStudents].average= calculateAverage((*studentsArray)[*numOfStudents].subjects,*numOfSubjects);
                (*studentsArray)[*numOfStudents].grade = calculateGrade((*studentsArray)[*numOfStudents].average);
                (*numOfStudents)++;
                SetColor(2);
                printf("*================================================*\n");
                printf("     ADDED SUCCESSFULLY");
                getch();
}

void search(student** studentsArray,int *numOfStudents)
{
    if(*numOfStudents == 0)
                {
                    SetColor(4);
                    printf("**********************************************************************\n");
                    printf(" Add student first\n");
                    printf("**********************************************************************\n");
                }
                else
                {
                    printf("Enter student ID: ");
                    int temp;
                    scanf("%d",&temp);
                    int check=0;
                    for(int i=0; i<*numOfStudents; i++)
                    {
                        if((*studentsArray)[i].ID==temp)
                        {
                            printf("  ID: %d\n", (*studentsArray)[i].ID);
                            printf("  Name: %s\n", (*studentsArray)[i].name);
                            printf("  Average: %.2f\n", (*studentsArray)[i].average);
                            printf("  Grade: %c\n", (*studentsArray)[i].grade);
                            check++;
                        }
                    }
                    if(check==0)
                    {
                        SetColor(4);
                        printf("  There is no student with that ID\n");
                    }
                }

                getch();
}

void edit(student** studentsArray,int *numOfStudents, int *numOfSubjects)
{
    printf("%d",*numOfSubjects);
    if(*numOfStudents == 0)
                {
                    SetColor(4);
                    printf("**********************************************************************\n");
                    printf(" Add student first\n");
                    printf("**********************************************************************\n");
                }
                else
                {
                    printf("Enter student ID: ");
                    int temp;
                    scanf("%d",&temp);
                    int Sflag=0;
                    for(int i=0; i<*numOfStudents; i++)
                    {
                        if((*studentsArray)[i].ID == temp)
                        {
                            Sflag=1;
                            printf("Enter the subject name: ");
                            char subjectName[100];
                            scanf("%s",subjectName);
                            int subflag=0;
                            for(int j=0; j<*numOfSubjects;j++)
                            {
                                if(strcmp((*studentsArray)[i].subjects[j].subName,subjectName)==0)
                                {
                                    subflag++;
                                    printf("Enter the new score: ");
                                    float newScore;
                                    scanf("%f",&newScore);
                                    while(!(newScore>=0 && newScore<=100))
                                    {
                                        SetColor(4);
                                        printf("*================================================*\n");
                                        printf("     Score must be between 0 and 100.\n");
                                        SetColor(255);
                                        printf("Enter the new score: ");
                                        scanf("%f", &newScore);
                                    }
                                    (*studentsArray)[i].subjects[j].score = newScore;
                                    SetColor(2);
                                    printf("*================================================*\n");
                                    printf("     UPDATED SUCCESSFULLY");
                                    (*studentsArray)[i].average= calculateAverage((*studentsArray)[i].subjects,*numOfSubjects);
                                    (*studentsArray)[i].grade = calculateGrade((*studentsArray)[i].average);
                                }
                            }
                            if(subflag==0)
                            {
                                printf("  There is no subject with that name\n");
                            }
                        }
                    }
                    if(Sflag == 0)
                    {
                        printf("  There is no student with that ID\n");
                    }
                }

                getch();
}

void list(student** studentsArray,int *numOfStudents)
{
    if(*numOfStudents == 0)
                {
                    SetColor(4);
                    printf(" Empty...");
                }
                else
                {
                    for(int i=0; i<*numOfStudents; i++)
                    {
                        SetColor(4);
                        printf(" Student %d\n", i+1);
                        SetColor(255);
                        printf("  ID: %d\n", (*studentsArray)[i].ID);
                        printf("  Name: %s\n", (*studentsArray)[i].name);
                        printf("  Average: %.2f\n", (*studentsArray)[i].average);
                        printf("  Grade: %c\n", (*studentsArray)[i].grade);
                        SetColor(4);
                        printf("=======================================================================\n");
                    }
                }

                getch();
}

void highestAverage(student **studentsArray,int *numOfStudents)
{
    if(*numOfStudents == 0)
                {
                    SetColor(4);
                    printf(" Empty...");
                }
                else
                {
                    student s;
                    s.average =0;
                    for(int i=0; i<*numOfStudents; i++)
                    {
                        if((*studentsArray)[i].average> s.average)
                        {
                            s = (*studentsArray)[i];
                        }
                    }
                    SetColor(3);
                    printf("**********************************************************************\n");
                    printf(" Student with the highest average score information\n");
                    printf("**********************************************************************\n");
                    SetColor(255);
                    printf("  ID: %d\n", s.ID);
                    printf("  Name: %s\n", s.name);
                    printf("  Average: %.2f\n", s.average);
                    printf("  Grade: %c\n", s.grade);
                }
                getch();
}

void averageScore(student **studentsArray, int *numOfStudents)
{
    if(*numOfStudents == 0)
                {
                    SetColor(4);
                    printf(" Empty...");
                }
                else
                {
                    float sumAver=0;
                    for(int i=0; i<*numOfStudents; i++)
                    {
                        sumAver += (*studentsArray)[i].average;
                    }
                    printf("**********************************************************************\n");
                    printf("  The average score of all students = %.2f\n", sumAver/ *numOfStudents);
                    printf("**********************************************************************\n\n\n\n");
                }

                getch();
}

void passedStudents(student** studentsArray,int *numOfStudents)
{
    if(*numOfStudents == 0)
                {
                    SetColor(4);
                    printf(" Empty...");
                }
                else
                {
                    SetColor(3);
                    printf("********************************Passed students*****************************\n");
                    SetColor(255);
                    int Pflag=0;
                    for(int i=0; i<*numOfStudents; i++)
                    {
                        if((*studentsArray)[i].grade != 'F')
                        {
                            printf("  Student ID: %d\t", (*studentsArray)[i].ID);
                            printf("  Student Name: %s\n", (*studentsArray)[i].name);
                            Pflag++;
                        }
                    }
                    if(Pflag == 0)
                    {
                        printf("  No student passed.\n");
                    }
                }

                getch();
}

void failedStudents(student** studentsArray,int *numOfStudents)
{
    if(*numOfStudents == 0)
                {
                    SetColor(4);
                    printf(" Empty...");
                }
                else
                {
                    SetColor(3);
                    printf("********************************Failed students*****************************\n");
                    SetColor(255);
                    int Fflag=0;
                    for(int i=0; i<*numOfStudents; i++)
                    {
                        if((*studentsArray)[i].grade == 'F')
                        {
                            printf("  Student ID: %d\t", (*studentsArray)[i].ID);
                            printf("  Student Name: %s\n", (*studentsArray)[i].name);
                            Fflag++;
                        }
                    }
                    if(Fflag == 0)
                    {
                        printf("  No student failed.\n");
                    }
                }

                getch();
}

int main()
{
    int flag=1;
    char ch;
    student *studentsArray=NULL;
    int numOfStudents =0;
    int numOfSubjects =0;
    int chooseColor = 6;
    int mainColor = 255;

    char Menu[10][100] = {"  ================================== SGMS ===================================",
                          "   [1] Add a new student.",
                          "   [2] Search for a student.",
                          "   [3] Update a student's grade.",
                          "   [4] List of all students.",
                          "   [5] Show the highest score.",
                          "   [6] Show the average score.",
                          "   [7] List of passed students.",
                          "   [8] List of failed students.",
                          "   [9] Exit."};

    do{
        system("cls");
        for(int i=0; i<10; i++)
        {
            if(i == 0)
            {
                SetColor(3);
            }
            if(flag == i)
            {
                SetColor(chooseColor);
            }
            else if(flag != i && i != 0)
            {
                SetColor(mainColor);
            }
            printf("%s\n",Menu[i]);
        }

        ch = getch();
        if(ch == -32)
        {
            ch = getch();
            system("cls");
            if(ch == 80)
            {
                flag++;
                if(flag > 9)
                {
                    flag = 1;
                }
            }
            else if(ch == 72)
            {
                flag--;
                if(flag < 1)
                {
                    flag = 9;
                }
            }
        }
        else if(ch == 13)
        {
            system("cls");
            switch (flag)
            {
            case 1:
                addStudent(&studentsArray,&numOfStudents,&numOfSubjects);
                break;


            case 2:
                search(&studentsArray,&numOfStudents);
                break;


            case 3:
                edit(&studentsArray,&numOfStudents,&numOfSubjects);
                break;


            case 4:
                list(&studentsArray,&numOfStudents);
                break;


            case 5:
                highestAverage(&studentsArray,&numOfStudents);
                break;

            case 6:
                averageScore(&studentsArray,&numOfStudents);
                break;

            case 7:
                passedStudents(&studentsArray,&numOfStudents);
                break;


            case 8:
                failedStudents(&studentsArray,&numOfStudents);
                break;


            case 9:
                SetColor(3);
                printf("**********************************************************************\n");
                printf("          Thanks for using our system <3\n");
                printf("**********************************************************************\n\n\n\n");
                return 0;
            }
        }
    }while(1);

    return 0;
}

