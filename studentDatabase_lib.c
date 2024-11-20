#ifndef STUDENTDATABASE_LIB_H
#define STUDENTDATABASE_LIB_H

// header files
#include <stdio.h>
#include <ctype.h>
#include <string.h>

// global constants
#define MAX_COURSES 3 // Maximum number of courses
#define MAX_SIZE 100  // Maximum size of student database

enum Grade
{
	Char_A = 'A',
	Char_B = 'B',
	Char_C = 'C',
	Char_D = 'D',
	Char_F = 'F'
};

enum Course
{
	MATH,
	PHYSICS,
	BIOLOGY
};

struct report
{
	enum Course courseName;
	enum Grade grade;
};

struct student
{
	int ID;
	char name[MAX_SIZE];
	int courseCount;
	struct report transcript[MAX_COURSES];
};

void addStudent(struct student *studentDatabase, int *count)
{
	struct student curStudent;

	// Enter student's name
	printf("Enter the Student's name: ");
	// Request User to input the student's name and store it
	fgets(curStudent.name, MAX_SIZE, stdin);
	// Remove newline character
	curStudent.name[strcspn(curStudent.name, "\n")] = '\0';

	// Enter student's ID
	printf("Enter the student's ID: ");
	// Request user to input the student's ID and store it
	// Check to see if any value other than an integer is returned
	while(scanf("%d", &curStudent.ID) != 1)
	{
		// Print an error message if a non-integer was typed in
		printf("Error! Please enter a valid student ID: ");
		// Clear the buffer
		while(getchar() != '\n');
	}

	int totalCourses;
	// Enter the number of courses the student enrolled in
	printf("Enter the number of courses the student enrolled in: ");
	// Request the user to input the total number of enrolled courses and store
	// Check to see if any non-integer value was returned and if it's in range
	while(scanf("%d", &totalCourses) != 1 || totalCourses <= 0 || 
		totalCourses > MAX_COURSES)
	{
		printf("Error! Please enter a valid number of courses within range "
			"(1 to %d): ", MAX_COURSES);

		// Clear the buffer
		while(getchar() != '\n');
	}

	curStudent.courseCount = totalCourses; // store the total number

	// Loop to gather course selections and grades
	for (int i = 0; i < curStudent.courseCount; i++)
	{
		// Create an integer to store the numbers corresponding with the course
		int courseInput;

		// Request the user to select the course (make sure the input is valid)
		printf("Enter the course number (0 for MATH, 1 for PHYSICS, "
			"or 2 for BIOLOGY): ");
		// Check if the input is valid for the courses
		while(scanf("%d", &courseInput) != 1 || courseInput < 0 || 
			courseInput > 2)
		{
			// Print message indicating an error/invalid input
			printf("Invalid Input! Please enter 0 for MATH, 1 for PHYSICS, "
				"or 2 for BIOLOGY: ");
			// Clear the buffer
			while (getchar() != '\n');
		}

		// Store the selected course
		curStudent.transcript[i].courseName = (enum Course)courseInput; 

		// Create a char variable to store the grades
		char gradeInput;

		// Request and store the grade for the selected course
		printf("Enter the grade for the course (A, B, C, D, F): ");
		// check to see if the grade input is valid
		while(scanf(" %c", &gradeInput) != 1 || 
			gradeInput != 'A' && gradeInput != 'B' && gradeInput != 'C' && 
			gradeInput != 'D' && gradeInput != 'F')
		{
			// **[Correction]**: Fixed broken printf for error message
			printf("Invalid Input! Please enter a valid grade "
				"(A, B, C, D, F): ");
		}

		// Store the grade
		curStudent.transcript[i].grade = (enum Grade)gradeInput;
	}

	// Add the current student database and update the student count
	// Store the student's name in the database
	studentDatabase[*count] = curStudent;

	// Increment the student count
	(*count)++;
}

void displayAllStudents(struct student *studentDatabase, int *count)
{
	// Loop through each student
	printf("Transcript of all students:\n"); // print the header
	for (int i = 0; i < *count; i++)
	{
		// Display the student's name and ID
		printf("----------------------------------------------------\n");
		printf("Student Name: %-30s Student ID: %-10d\n", 
			studentDatabase[i].name, studentDatabase[i].ID);
		printf("----------------------------------------------------\n");

        // Loop through each course in the student's transcript
        for(int j = 0; j < studentDatabase[i].courseCount; j++)
        {
        	// Print the course name
        	printf("Course %d: ", j + 1);

        	// Convert the course enum into a readable string
        	switch(studentDatabase[i].transcript[j].courseName)
			{

				case MATH:
					printf("MATH: ");
					break;

				case PHYSICS:
				printf("PHYSICS: ");
				break;

				case BIOLOGY:
				printf("BIOLOGY: ");
				break;

				default:
				printf("UNKNOWN COURSE: ");
			}


			// Print the corresponding grade for the course
			printf("%-3c\n", studentDatabase[i].transcript[j].grade);
        }

		// Add newline between each student's info
		printf("------------------------------------------------------\n");	
	}
}

#endif