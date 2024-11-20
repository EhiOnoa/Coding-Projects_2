/*
Lab 13 - Problem 1: Student Database Management System
Driver: <Ehidiamen D. Onoabhagbe> <6174056>
Navigator: <Ehidiamen D. Onoabhagbe <6174056>
*/

#include <stdio.h>
#include "studentDatabase_lib.h"

int main() 
{
    // Array to hold student data
    struct student studentDatabase[MAX_SIZE]; 

    // Counter to keep track of the number of students
    int studentCount = 0;

    // Variable to store user's choice from menu
    int choice;

    // Welcome message and menu
    do 
    {
        printf("Welcome to Student Database Management System\n");
        printf("-----------------------------------------------------\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Exit\n");
        printf("Input your choice: ");
        
        // Get the user's choice
        scanf("%d", &choice);

        // Consume the newline character left by scanf
        getchar(); 

        switch (choice) 
        {
            case 1:
                // Add a new student
                addStudent(studentDatabase, &studentCount);
                break;

            case 2:
                // Display all students' data
                displayAllStudents(studentDatabase, &studentCount);
                break;

            case 3:
                // Exit the program
                printf("Exiting program!\n");
                break;

            default:
                // Invalid choice
                printf("Invalid choice! Please enter a number between 1 and 3.\n");
                break;
        }

    } 
    while (choice != 3); // Repeat until the user chooses to exit

    return 0;
}
