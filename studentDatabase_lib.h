#ifndef STUDENTDATABASE_LIB_H
#define STUDENTDATABASE_LIB_H

// header files
#include <stdio.h>
#include <ctype.h>

// global constants
#define MAX_COURSES 3 // Maximum number of courses a student can enroll in
#define MAX_SIZE 100  // Maximum size for a student's name

// Enum for Grade values
enum Grade
{
    Char_A = 'A', // Grade A
    Char_B = 'B', // Grade B
    Char_C = 'C', // Grade C
    Char_D = 'D', // Grade D
    Char_F = 'F'  // Grade F
};

// Enum for Course values
enum Course
{
    MATH,    // Course: Math
    PHYSICS, // Course: Physics
    BIOLOGY  // Course: Biology
};

// Struct to represent a report (course and grade)
struct report
{
    enum Course courseName; // The course the student is enrolled in
    enum Grade grade;       // The grade the student received in the course
};

// Struct to represent a student
struct student
{
    int ID;                       // The unique ID of the student
    char name[MAX_SIZE];          // The name of the student
    int courseCount;              // The number of courses the student is enrolled in
    struct report transcript[MAX_COURSES]; // The courses and grades the student has
};

/**
 * Adds a new student to the student database.
 * 
 * Parameters:
 * - studentDatabase: A pointer to an array of struct student where the new student 
 *   will be added.
 * - count: A pointer to the number of students in the database. This is updated when 
 *   a new student is added.
 * 
 * The function will prompt the user to input the student's name, ID, number of courses 
 * enrolled in, and the courses along with the grades for each course. The student 
 * information is then stored in the student database.
 */
void addStudent(struct student *studentDatabase, int *count);

/**
 * Displays all students' information including their courses and grades.
 * 
 * Parameters:
 * - studentDatabase: A pointer to the array of struct student which holds all student data.
 * - count: A pointer to the number of students in the student database.
 * 
 * This function loops through all students and displays their name, ID, enrolled 
 * courses, and grades. It uses a nested loop to go through each student and their courses.
 */
void displayAllStudents(struct student *studentDatabase, int *count);

#endif // STUDENTDATABASE_LIB_H
