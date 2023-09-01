/*
    THE PASSWORD FOR THE ADMIN PORTAL IS "admin"
*/

#include <stdio.h>   // Include the standard input/output library
#include <stdlib.h>  // Include the standard library
#include <string.h>  // Include the string library
#include <windows.h> // Include the Windows library for using functions related to the console window

// Define constants for the number of rows and columns in the console window
#define ROWS 75
#define COLS 3

// Define structures for Room, Student, and Booking
struct Room {
    int roomNumber;  // The room number
    int capacity;    // The capacity of the room
    int isAvailable; // Whether or not the room is available
};

struct Student {
    char name[50];   // The name of the student
    int roomNumber;  // The room number of the student
};

struct Booking {
    char name[50];   // The name of the student who booked the room
    int roomNumber;  // The room number that was booked
};


// function prototypes
void readRooms(struct Room rooms[], int *numRooms);
void writeRooms(struct Room rooms[], int numRooms);
void addRoom(struct Room rooms[], int *numRooms);
void viewRoomDetails(struct Room rooms[], int numRooms);
void assignOccupant(struct Student students[], int *numStudents, int roomNumber);
void searchRooms(struct Room rooms[], int numRooms, int capacity);
void bookRoom(struct Room rooms[], int numRooms, struct Booking bookings[], int *numBookings);
void homeScreen(void);
void homeScreenMenu(void);
void studentScreen(void);
void adminScreen(void);
void endScreen(void);

// variables to store choice, capacity and room number
int choice, roomNumber, capacity;

int main() {
    HWND hWnd = GetConsoleWindow(); // Get a handle to the console window

    ShowWindow(hWnd, SW_MAXIMIZE); // Maximize the console window


    struct Room rooms[100];        // Declare an array of Room structures with a capacity of 50
    int numRooms = 0;             // Declare a variable to keep track of the number of rooms and initialize it to 0

    struct Student students[50];  // Declare an array of Student structures with a capacity of 50
    int numStudents = 0;          // Declare a variable to keep track of the number of students and initialize it to 0

    struct Booking bookings[50];  // Declare an array of Booking structures with a capacity of 50
    int numBookings = 0;          // Declare a variable to keep track of the number of bookings and initialize it to 0


    readRooms(rooms, &numRooms);  // read initial hostel data from file

    homeScreen();                 // displays the home screen

    mainApp:                      // label for the main app
        homeScreenMenu();         // displays the home screen menu

        // STUDENT SIDE
        if (choice == 1){         // if user is a student
            studentInterface:     // label for student interface
                system("cls");    // clears screen
                studentScreen();  // displays students' portal screen

                scanf("%d", &choice);  // allows student to enter what they want to do

                // conditions for student options
                if (choice == 1){
                    // search rooms
                    printf("\t\t\t\tEnter the capacity of the room you want\n\t\t\t\t");
                    scanf("%d", &capacity);   // takes the capacity of the room the user wants to search for
                    searchRooms(rooms, numRooms, capacity);   // calls the search room function and passes the arguments: rooms, numRooms and capacity

                    // STUDENT WILL BE ABLE TO BOOK A ROOM BASED ON SEARCH RESULTS
                    printf("\n\n\t\t\t\tWould you like to book a room\?\n"
                           "\t\t\t\t1. Yes\n"
                           "\t\t\t\t2. No\n\t\t\t\t");
                    scanf("%d", &choice); // allows student to enter whether or not they'll book a room based on the search results

                    switch (choice){
                    case 1: // book a room
                        bookRoom(rooms, numRooms, bookings, &numBookings);  // calls the bookRoom function with the arguments: rooms, numRooms, bookings and the address of numBookings
                        break;

                    case 2:
                        goto studentInterface; // takes student back to student portal if they don't want to book a room

                    default:
                        printf("\t\t\t\tInvalid entry!\n");  // if user enters neither of the options
                    }

                    // allows student to perform another function
                    printf("\n\n\t\t\t\tWould you like to do something else\?\n"
                           "\t\t\t\t1. Yes\n"
                           "\t\t\t\t2. No\n\t\t\t\t");
                    scanf("%d", &choice);

                    switch (choice){
                    case 1:
                        goto studentInterface;  // if student wants to do something else, take student to student portal
                        break;

                    case 2:
                        goto endApp; // if student won't do anything else, end app
                        break;

                    default:
                        printf("Invalid Entry!\n"); // if student enters neither of the options
                    }
                }

                else if (choice == 2){
                    // book a room
                    bookRoom(rooms, numRooms, bookings, &numBookings); // calls the bookRoom function with arguments: rooms, numRooms, bookings and the address of numBookings

                    // allows student to perform another function
                    printf("\n\n\t\t\t\tWould you like to do something else\?\n"
                           "\t\t\t\t1. Yes\n"
                           "\t\t\t\t2. No\n\t\t\t\t");
                    scanf("%d", &choice);

                    switch (choice){
                    case 1:
                        goto studentInterface;    // if student wants to do something else, go to student interface
                        break;

                    case 2:                       // if student doesn't want to do anything else, end app
                        goto endApp;
                        break;

                    default:                      // if student enters neither 1 or 2
                        printf("\t\t\t\tInvalid Entry!\n");
                    }
                }

                else if (choice == 3){
                    goto mainApp; // takes user back to home screen
                }

                else if (choice == 4){
                    goto endApp; // ends app
                }

                // invalid student choice
                else printf("\t\t\t\tInvalid Entry!\n");
            }

        // ADMIN SIDE
        else if (choice == 2){
            int numTries = 0;
            enterPwd: // label to enter password section. If user enters a wring password, he will be referred back here
                printf("\t\t\t\tEnter password to proceed\n\t\t\t\t");

                // variables to hold pwd and user entry
                char pwd[] = "admin";
                char userEntry[20];

                scanf("%s", &userEntry);           // allows user to enter password

                if (!strcmp(pwd, userEntry)){  // compares password to what the user entered and if true:
                    system("cls");                 // clears screen
                    adminInterface:                // label for admin interface
                        adminScreen();             // displays admin portal

                        scanf("%d", &choice);      // allows admin to enter what they want to do

                        if (choice == 1){
                            // add room
                            addRoom(rooms, &numRooms);  // calls add room function with arguments: rooms and the address of numRooms

                            // allows admin to perform another function
                            printf("\n\t\t\t\tWould you like to do something else\?\n"
                                   "\t\t\t\t1. Yes\n"
                                   "\t\t\t\t2. No\n\t\t\t\t");
                            scanf("%d", &choice);

                            switch (choice){
                            case 1:
                                goto adminInterface;                   // if admin wants to do something else, go to the admin interface
                                break;

                            case 2:
                                goto endApp;                           // if admin doesn't want to do anything else, end app
                                break;

                            default:
                                printf("\t\t\t\tInvalid Entry!\n");    // if admin enters neither 1 or 2
                            }
                        }

                        else if (choice == 2){
                            system("cls");
                            // remove a room
                            printf("\t\t\t\t*************************************************\n"
                                   "\t\t\t\t\t\tREMOVE A ROOM\n"
                                   "\t\t\t\t*************************************************\n");
                            printf("\t\t\t\tEnter the room number of the room you want to remove\n\t\t\t\t");

                            scanf("%d", &roomNumber);
                            removeRoom(rooms, &numRooms, roomNumber);  // calls remove room function with arguments: rooms, address of numRooms and roomNumber

                            // allows admin to perform another function
                            printf("\n\t\t\t\tWould you like to do something else\?\n"
                                   "\t\t\t\t1. Yes\n"
                                   "\t\t\t\t2. No\n\t\t\t\t");
                            scanf("%d", &choice);

                            switch (choice){
                            case 1:
                                goto adminInterface;             // if admin wants to do something else, go to the admin interface
                                break;

                            case 2:
                                goto endApp;                    // if admin doesn't want to do anything else, end app
                                break;

                            default:
                                printf("Invalid Entry!\n");     // if admin enters neither 1 or 2
                            }
                        }

                        else if (choice == 3){
                            // View all rooms
                            viewRoomDetails(rooms, numRooms);  // calls vieRoomDetails function with arguments: rooms and numRooms

                            // allows admin to perform another function
                            printf("\n\t\t\t\tWould you like to do something else\?\n"
                                   "\t\t\t\t1. Yes\n"
                                   "\t\t\t\t2. No\n\t\t\t\t");
                            scanf("%d", &choice);

                            switch (choice){
                            case 1:
                                goto adminInterface;                // if admin wants to do something else, go to the admin interface
                                break;

                            case 2:
                                goto endApp;                        // if admin doesn't want to do anything else, end app
                                break;

                            default:
                                printf("Invalid Entry!\n");         // if admin enters neither 1 or 2
                            }
                        }

                        else if (choice == 4){
                            system("cls");
                            // assign occupant
                            printf("\t\t\t\t*************************************************\n"
                                   "\t\t\t\t\tASSIGN AN OCCUPANT TO A ROOM\n"
                                   "\t\t\t\t*************************************************\n");
                            printf("\n\t\t\t\tEnter room number: \n\t\t\t\t");
                            scanf("%d", &roomNumber);
                            assignOccupant(students, &numStudents, roomNumber);  // calls assignRoom function with arguments; students address of numStudents and roomNumber

                            // allows admin to perform another function
                            printf("\n\t\t\t\tWould you like to do something else\?\n"
                                   "\t\t\t\t1. Yes\n"
                                   "\t\t\t\t2. No\n\t\t\t\t");
                            scanf("%d", &choice);

                            switch (choice){
                            case 1:
                                goto adminInterface;             // if admin wants to do something else, go to the admin interface
                                break;

                            case 2:
                                goto endApp;                     // if admin doesn't want to do anything else, end app
                                break;

                            default:
                                printf("Invalid Entry!\n");      // if admin enters neither 1 or 2
                            }
                        }

                        else if (choice == 5)
                            goto mainApp;                     // back to home screen

                        else if (choice == 6)                 // end app
                            goto endApp;

                        // invalid admin options entry
                        else
                            printf("Invalid Entry!\n");

                    }

                // invalid pwd for admin
                else {
                    printf("\t\t\t\tIncorrect password!\n\n");
                    numTries++;
                    if (numTries == 5){
                        goto mainApp;   // if user enter a wrong pwd for 5 times, the app goes back to the main screen
                    }
                    goto enterPwd;      // if the number of tries is not up to 5, allows user to re-enter pwd
                }
        }

        // invalid selection for std or admin
        else printf("\t\t\t\tInvalid Entry!\n");

    endApp:                     // go to label for end app
        system("cls");          // clear screen
        endScreen();            // calls endScreen function
    return 0;
}


// function to read hostel data
void readRooms(struct Room rooms[], int *numRooms) {
    FILE *fp;                               // declares pointer variable of type FILE
    fp = fopen("hostelData.txt", "r");      // opens the file "hostelData.txt in read mode"

    if (fp == NULL) {
        printf("Error opening file\n");     // if there is no such file, display "Error opening file" and end the function
        return;
    }

    int roomNumber, capacity, isAvailable;  // declare int variables roomNumber, capacity and isAvailable

    // Loop through file while there are three integers to read
    while (fscanf(fp, "%d %d %d", &roomNumber, &capacity, &isAvailable) == 3) {
        rooms[*numRooms].roomNumber = roomNumber;        // Store room number in struct at index numRooms in array rooms
        rooms[*numRooms].capacity = capacity;            // Store room capacity in struct at index numRooms in array rooms
        rooms[*numRooms].isAvailable = isAvailable;      // Store room availability status in struct at index numRooms in array rooms
        (*numRooms)++;                                   // Increment number of rooms counter
    }

    // close the file pointer
    fclose(fp);
}

// Function to write the room data to a file
void writeRooms(struct Room rooms[], int numRooms) {

    // Declare a file pointer variable
    FILE *fp;

    // Open the file in write mode
    fp = fopen("hostelData.txt", "w");

    // Check if file opened successfully
    if (fp == NULL) {

        // Print an error message and return if file opening failed
        printf("Error opening file\n");
        return;
    }

    // Loop through the array of rooms
    for (int i = 0; i < numRooms; i++) {

        // Write the room data to the file in the specified format
        fprintf(fp, "%d %d %d\n", rooms[i].roomNumber, rooms[i].capacity, rooms[i].isAvailable);
    }

    // Close the file pointer
    fclose(fp);
}


// function to add a new room to the hostel
void addRoom(struct Room rooms[], int *numRooms) {

    // Clear the console screen
    system("cls");

    // Print a header for the add room section
    printf("\t\t\t\t*****************************************\n"
           "\t\t\t\t\t\tADD A ROOM\n"
           "\t\t\t\t*****************************************\n");

    // Prompt the user to enter the room number and read it in
    int roomNumber;
    printf("\t\t\t\tEnter room number: \n\t\t\t\t");
    scanf("%d", &roomNumber);

    // Check if the room number already exists
    for (int i = 0; i < *numRooms; i++) {
        if (rooms[i].roomNumber == roomNumber) {
            printf("\n\t\t\t\tRoom already exists\n");
            return;
        }
    }

    // Assign the room number to the new room
    rooms[*numRooms].roomNumber = roomNumber;

    // Prompt the user to enter the room capacity and read it in
    printf("\t\t\t\tEnter capacity: \n\t\t\t\t");
    scanf("%d", &rooms[*numRooms].capacity);

    // Prompt the user to enter the room availability status and read it in
    printf("\t\t\t\tEnter availability (0 = unavailable, 1 = available): \n\t\t\t\t");
    scanf("%d", &rooms[*numRooms].isAvailable);

    // Print a confirmation message that the room has been added
    printf("\n\t\t\t\tRoom %d has successfully been added.\n", rooms[*numRooms].roomNumber);

    // Increment the number of rooms counter
    (*numRooms)++;

    // Write the updated room data to the file
    writeRooms(rooms, *numRooms);
}



// function to remove a room
void removeRoom(struct Room rooms[], int *numRooms, int roomNum) {
    // Find the index of the room to be removed
    int index = -1;
    for (int i = 0; i < *numRooms; i++) {
        if (rooms[i].roomNumber == roomNum) {
            index = i;
            break;
        }
    }

    // If the room is not found, return an error message
    if (index == -1) {
        printf("Error: Room not found\n");
        return;
    }

    // Shift all subsequent rooms back by one index
    for (int i = index; i < *numRooms - 1; i++) {
        rooms[i] = rooms[i + 1];
    }

    // Decrement the numRooms variable
    (*numRooms)--;

    printf("\n\t\t\t\tRoom %d has successfully been removed\n", roomNum);

    // Save the updated rooms array to the file
    writeRooms(rooms, *numRooms);
}





// function to view all room details in the hostel
void viewRoomDetails(struct Room rooms[], int numRooms) {
    // Clear the screen and print a header for the list of rooms
    system("cls");
    printf("\t\t\t\t**************************************************\n"
           "\t\t\t\t\tLIST OF ALL ROOMS IN THE HOSTEL\n"
           "\t\t\t\t**************************************************\n");
    // Print a table header for the room details
    printf("\t\t\t\t\tRoom\tCapacity\tAvailability\n");
    // Loop through all the rooms and print their details
    for (int i = 0; i < numRooms; i++) {
        // Print the room number, capacity, and availability. If the room is available, print "available", otherwise print "unavailable"
        printf("\t\t\t\t\t%d\t%d\t\t%s\n", rooms[i].roomNumber, rooms[i].capacity, rooms[i].isAvailable ? "available" : "unavailable");
    }
}


// function to assign an occupant to a room
void assignOccupant(struct Student students[], int *numStudents, int roomNumber) {

    // Prompt the user to enter the student's name and read it in
    printf("\n\t\t\t\tEnter student name (separated by underscores): \n\t\t\t\t");
    scanf("%s", students[*numStudents].name);

    // Assign the student to the specified room
    students[*numStudents].roomNumber = roomNumber;

    // Increment the number of students counter
    (*numStudents)++;

    // Print a confirmation message that the student has been assigned to the room
    printf("\n\t\t\t\tYou have successfully assigned an occupant to room %d\n", roomNumber);
}


// function to search for available rooms based on capacity
void searchRooms(struct Room rooms[], int numRooms, int capacity) {
    // Clear the console screen
    system("cls");

    // Print a header for the search rooms section with the specified capacity
    printf("\n\n\t\t\t\t*****************************************************\n"
           "\t\t\t\t     LIST OF AVAILABLE ROOMS WITH MAX CAPACITY OF %d\n"
           "\t\t\t\t*****************************************************\n", capacity);

    // Print the table headers for room details
    printf("\t\t\t\tRoom\tCapacity\tAvailability\n");

    // Loop through all rooms to find available rooms with the specified capacity
    for (int i = 0; i < numRooms; i++) {
        // Check if the room has the specified capacity and is available
        if (rooms[i].capacity == capacity && rooms[i].isAvailable) {
            // If the room is available, print its details in the table format
            printf("\t\t\t\t%d\t%d\t\t%s\n", rooms[i].roomNumber, rooms[i].capacity, "available");
        }
    }
}


// function to book a room
void bookRoom(struct Room rooms[], int numRooms, struct Booking bookings[], int *numBookings) {
    system("cls"); // clear the console screen

    char name[50]; // declare a string variable to store the name of the booker
    int roomNumber; // declare an integer variable to store the desired room number

    // print a header for the booking menu
    printf("\n\n\t\t\t\t********************************************************************\n"
           "\t\t\t\t\t\t\t\tBOOK A ROOM\n"
           "\t\t\t\t********************************************************************\n");

    // prompt the user to enter their name
    printf("\n\t\t\t\tEnter your name(separated by underscores): ");
    scanf("%s", &name); // read the name from the user input

    // prompt the user to enter the room number they want to book
    printf("\n\t\t\t\tEnter room number: ");
    scanf("%d", &roomNumber); // read the room number from the user input

    // loop through all the rooms to find the room that matches the entered room number
    for (int i = 0; i < numRooms; i++) {
        if (rooms[i].roomNumber == roomNumber && rooms[i].isAvailable) { // check if the room is available
            // assign the name and room number to the booking record and mark the room as booked
            strcpy(bookings[*numBookings].name, name);
            bookings[*numBookings].roomNumber = roomNumber;
            rooms[i].isAvailable = 0;

            (*numBookings)++; // increment the number of bookings and write the rooms data to the file
            writeRooms(rooms, numRooms);

            // print a success message to the user
            printf("\n\t\t\t\t%s, you have successfully booked room %d\n", name, roomNumber);
            return;
        }
    }

    // if the loop ends without finding an available room, print an error message
    printf("\t\t\t\tRoom not available.\n");
}


// home screen
void homeScreen(void){
    printf("\n\n");
    printf("\t\t\t\t\t ::::::::      :::      ::::::::      :::                         \n");
    printf("\t\t\t\t\t:+:    :+:   :+: :+:   :+:    :+:   :+: :+:                       \n");
    printf("\t\t\t\t\t+:+         +:+   +:+  +:+         +:+   +:+                      \n");
    printf("\t\t\t\t\t+#+        +#++:++#++: +#++:++#++ +#++:++#++:                     \n");
    printf("\t\t\t\t\t+#+        +#+     +#+        +#+ +#+     +#+                     \n");
    printf("\t\t\t\t\t#+#    #+# #+#     #+# #+#    #+# #+#     #+#                     \n");
    printf("\t\t\t\t\t ########  ###     ###  ########  ###     ###                     \n");
    printf("\n");
    printf("\t\t\t\t:::    :::  ::::::::   :::::::: ::::::::::: :::::::::: :::        \n");
    printf("\t\t\t\t:+:    :+: :+:    :+: :+:    :+:    :+:     :+:        :+:        \n");
    printf("\t\t\t\t+:+    +:+ +:+    +:+ +:+           +:+     +:+        +:+        \n");
    printf("\t\t\t\t+#++:++#++ +#+    +:+  #++:++#+     +#+     +#++:++#   +#+        \n");
    printf("\t\t\t\t+#+    +#+ +#+    +#+        +#+    +#+     +#+        +#+        \n");
    printf("\t\t\t\t#+#    #+# #+#    #+# #+#    #+#    #+#     #+#        #+#        \n");
    printf("\t\t\t\t###    ###  ########   ########     ###     ########## ########## \n\n");
    printf("\t\t\t\t                            /\\                                      \n"
           "\t\t\t\t                           /  \\                                     \n"
           "\t\t\t\t                          / /\\ \\                                   \n"
           "\t\t\t\t                         / /__\\ \\                                  \n"
           "\t\t\t\t                   _____/________\\_____                             \n"
           "\t\t\t\t                  /                    \\                            \n"
           "\t\t\t\t                 /                      \\                           \n"
           "\t\t\t\t                /________________________\\                          \n"
           "\t\t\t\t                   |                  |                              \n"
           "\t\t\t\t                   | ||     ||     || |                              \n"
           "\t\t\t\t                   | ||     ||     || |                              \n"
           "\t\t\t\t                   | ||     ||     || |                              \n"
           "\t\t\t\t                   | ||     ||     || |                              \n"
           "\t\t\t\t                   | ||     ||     || |                              \n"
           "\t\t\t\t                   | ||     __     || |                              \n"
           "\t\t\t\t                   | ||    |  |    || |                              \n"
           "\t\t\t\t                   | ||    |  |    || |                              \n"
           "\t\t\t\t                   | ||    |  |    || |                              \n"
           "\t\t\t\t                   |_______|__|_______|                              \n\n\n"
           "\t\t\t\t            Press the \"ENTER\" key to continue\n");

           char anyKey;       // just in case user enters something before pressing enter, the character array takes care of that
           scanf("%c", &anyKey);
}


void homeScreenMenu(void){
    system("cls");
    printf("\n\n\n\n"
           "\t\t\t\t ______________________________________________________________\n"
           "\t\t\t\t|                                                              |\n"
           "\t\t\t\t|         -------------------------------------------          |\n"
           "\t\t\t\t|          WELCOME TO THE CASA HOSTEL MANAGEMENT APP!          |\n"
           "\t\t\t\t|         -------------------------------------------          |\n"
           "\t\t\t\t|                                                              |\n"
           "\t\t\t\t|    Please note that this app is available for use to both    |\n"
           "\t\t\t\t|                                                              |\n"
           "\t\t\t\t|             students and hostel administrators.              |\n"
           "\t\t\t\t|                                                              |\n"
           "\t\t\t\t|                                                              |\n"
           "\t\t\t\t|                        Explore as a:                         |\n"
           "\t\t\t\t|                                                              |\n"
           "\t\t\t\t|                                                              |\n"
           "\t\t\t\t|                         1. Student                           |\n"
           "\t\t\t\t|                                                              |\n"
           "\t\t\t\t|                   2. Hostel administrator                    |\n"
           "\t\t\t\t|______________________________________________________________|\n"
           "\n\t\t\t\t");

           // takes user input for student or admin
           scanf("%d", &choice);
}

// student portal
void studentScreen(void){
    // header text
    printf("  _______ _________          ______   _______  _       _________ _______  _    _______  _______  _______ _________ _______  _       \n"
           " (  ____ \\\\__   __/|\\     /|(  __  \\ (  ____ \\( (    /|\\__   __/(  ____ \\( )  (  ____ )(  ___  )(  ____ )\\__   __/(  ___  )( \\      \n"
           " | (    \\/   ) (   | )   ( || (  \\  )| (    \\/|  \\  ( |   ) (   | (    \\/|/   | (    )|| (   ) || (    )|   ) (   | (   ) || (      \n"
           " | (_____    | |   | |   | || |   ) || (__    |   \\ | |   | |   | (_____      | (____)|| |   | || (____)|   | |   | (___) || |      \n"
           " (_____  )   | |   | |   | || |   | ||  __)   | (\\ \\) |   | |   (_____  )     |  _____)| |   | ||     __)   | |   |  ___  || |      \n"
           "       ) |   | |   | |   | || |   ) || (      | | \\   |   | |         ) |     | (      | |   | || (\\ (      | |   | (   ) || |      \n"
           " /\\____) |   | |   | (___) || (__/  )| (____/\\| )  \\  |   | |   /\\____) |     | )      | (___) || ) \\ \\__   | |   | )   ( || (____/\\\n"
           " \\_______)   )_(   (_______)(______/ (_______/|/    )_)   )_(   \\_______)     |/       (_______)|/   \\__/   )_(   |/     \\|(_______/\n"
           " ====================================================================================================================================\n\n\n");

    // menu items
    printf("\t\t\t\t ______________________________________________________________ \n"
           "\t\t\t\t|                                                              |\n"
           "\t\t\t\t|              ----------------------------------              |\n"
           "\t\t\t\t|               WELCOME TO THE STUDENTS' PORTAL!               |\n"
           "\t\t\t\t|              ----------------------------------              |\n"
           "\t\t\t\t|                                                              |\n"
           "\t\t\t\t|                 What would you like to do\?                   |\n"
           "\t\t\t\t|                                                              |\n"
           "\t\t\t\t|                                                              |\n"
           "\t\t\t\t|          1. Search for available rooms by capacity           |\n"
           "\t\t\t\t|                                                              |\n"
           "\t\t\t\t|                        2. Book a room                        |\n"
           "\t\t\t\t|                                                              |\n"
           "\t\t\t\t|                    3. Back to home screen                    |\n"
           "\t\t\t\t|                                                              |\n"
           "\t\t\t\t|                         4. Exit app.                         |\n"
           "\t\t\t\t|______________________________________________________________|\n\n"
           "\n\t\t\t\t");
}

void adminScreen(void){
    system("cls");
    printf("\t _______  ______   _______ _________ _        _______  _    _______  _______  _______ _________ _______  _       \n"
           "\t(  ___  )(  __  \\ (       )\\__   __/( (    /|(  ____ \\( )  (  ____ )(  ___  )(  ____ )\\__   __/(  ___  )( \\      \n"
           "\t| (   ) || (  \\  )| () () |   ) (   |  \\  ( || (    \\/|/   | (    )|| (   ) || (    )|   ) (   | (   ) || (      \n"
           "\t| (___) || |   ) || || || |   | |   |   \\ | || (_____      | (____)|| |   | || (____)|   | |   | (___) || |      \n"
           "\t|  ___  || |   | || |(_)| |   | |   | (\\ \\) |(_____  )     |  _____)| |   | ||     __)   | |   |  ___  || |      \n"
           "\t| (   ) || |   ) || |   | |   | |   | | \\   |      ) |     | (      | |   | || (\\ (      | |   | (   ) || |      \n"
           "\t| )   ( || (__/  )| )   ( |___) (___| )  \\  |/\\____) |     | )      | (___) || ) \\ \\__   | |   | )   ( || (____/\\\n"
           "\t|/     \\|(______/ |/     \\|\\_______/|/    )_)\\_______)     |/       (_______)|/   \\__/   )_(   |/     \\|(_______/\n"
           "\t=================================================================================================================\n\n\n");

    printf("\t\t\t\t ______________________________________________________________ \n"
           "\t\t\t\t|                                                              |\n"
           "\t\t\t\t|              ----------------------------------              |\n"
           "\t\t\t\t|                WELCOME TO THE ADMINS' PORTAL!                |\n"
           "\t\t\t\t|              ----------------------------------              |\n"
           "\t\t\t\t|                                                              |\n"
           "\t\t\t\t|                 What would you like to do\?                   |\n"
           "\t\t\t\t|                                                              |\n"
           "\t\t\t\t|                                                              |\n"
           "\t\t\t\t|                        1. Add a room                         |\n"
           "\t\t\t\t|                                                              |\n"
           "\t\t\t\t|                       2. Remove a room                       |\n"
           "\t\t\t\t|                                                              |\n"
           "\t\t\t\t|                      3. View all rooms                       |\n"
           "\t\t\t\t|                                                              |\n"
           "\t\t\t\t|                  4. Assign occupant to a room                |\n"
           "\t\t\t\t|                                                              |\n"
           "\t\t\t\t|                    5. Back to home screen                    |\n"
           "\t\t\t\t|                                                              |\n"
           "\t\t\t\t|                         6. Exit app                          |\n"
           "\t\t\t\t|______________________________________________________________|\n\n"
           "\t\t\t\t");
}

void endScreen(void){
    printf("\n\n\n\n\n\n\n\n\n\n"
           "\t\t\t\t\t ________________________________________________________\n"
           "\t\t\t\t\t|                                                        |\n"
           "\t\t\t\t\t|     THANK YOU FOR USING CASA HOSTEL MANAGEMENT APP     |\n"
           "\t\t\t\t\t|________________________________________________________|\n"
           "\n\n\n\n\n\n\n\n\n\n");
}



