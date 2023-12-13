#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "FitnessDataStruct.h"

#define MAX_RECORDS 1000

// Struct moved to header file

// Define any additional variables here
// Global variables for filename and FITNESS_DATA array
char filename[100];
FITNESS_DATA fitnessData[MAX_RECORDS];
int numRecords = 0;


// This is your helper function. Do not change it in any way.
// Inputs: character array representing a row; the delimiter character
// Ouputs: date character array; time character array; steps character array
void tokeniseRecord(const char *input, const char *delimiter,
                    char *date, char *time, char *steps) {
    // Create a copy of the input string as strtok modifies the string
    char *inputCopy = strdup(input);
    
    // Tokenize the copied string
    char *token = strtok(inputCopy, delimiter);
    if (token != NULL) {        strcpy(date, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(time, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(steps, token);
    }
    
    // Free the duplicated string
    free(inputCopy);

                    }


void displayMenu() {   // Display Menu function prints out all options
    printf("\nMenu Options:\n");
    printf("A: Specify the filename to be imported\n");
    printf("B: Display the total number of records in the file\n");
    printf("C: Find the date and time of the timeslot with the fewest steps\n");
    printf("D: Find the date and time of the timeslot with the largest number of steps\n");
    printf("E: Find the mean step count of all the records in the file\n");
    printf("F: Find the longest continuous period where the step count is above 500 steps\n");
    printf("Q: Quit\n");
    printf("Enter choice: ");
}



void importFile() { 
    printf("Input filename: ");
    scanf("%s", filename); // Read the filename

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error has occurred, could not open the file.\n");
        exit(1);
    } // Opens actual file in read mode and then if error occurs stops the program

    numRecords = 0; // Makes sure each time file is read the number of records is reset to 0 so global variable is 0
    int buffer_size = 100;
    char line_buffer[buffer_size];

    // Count the number of records in the file
    while (fgets(line_buffer, buffer_size, file) != NULL) {
        numRecords++;
    }

    // Reset the file pointer to the beginning of the file
    fseek(file, 0, SEEK_SET);

    char steps_str[10];
    int line_counter = 0;  // Read all records from the fitness data file and store them in the araray
    while (fgets(line_buffer, buffer_size, file) != NULL && line_counter < numRecords) {
        tokeniseRecord(line_buffer, ",", fitnessData[line_counter].date, fitnessData[line_counter].time, steps_str);
        fitnessData[line_counter].steps = atoi(steps_str);
        line_counter++;
    }

    printf("File successfully loaded.\n");
    fclose(file);
}


void displayTotalRecords() { // Prints the global variable num records so shows all records in file
    printf("Number of records in file: %d\n", numRecords);
}

void findFewestSteps() {
    if (numRecords == 0) { // Check if records are 0 as if case either file is empty or not loaded in to not cause errros
        printf("No data available.\n");
        return;
    }

    int minSteps = fitnessData[0].steps;
    int minIndex = 0;

    for (int i = 1; i < numRecords; ++i) { // Look for lowest number of steps by checking each record in the file in order and if the next record is lower than current replace it
        if (fitnessData[i].steps < minSteps) {
            minSteps = fitnessData[i].steps;
            minIndex = i;
        }
    }

    printf("Fewest steps: %s %s\n", fitnessData[minIndex].date, fitnessData[minIndex].time);
}

void findLargestSteps() {
    if (numRecords == 0) { // Check if records are 0 as if case either file is empty or not loaded in to not cause errros
        printf("No data available.\n");
        return;
    }

    int maxSteps = fitnessData[0].steps;
    int maxIndex = 0;

    for (int i = 1; i < numRecords; ++i) { // // Look for largest number of steps by checking each record in the file in order and if the next record is larger than current replace it
        if (fitnessData[i].steps > maxSteps) {
            maxSteps = fitnessData[i].steps;
            maxIndex = i;
        }
    }

    printf("Largest steps: %s %s\n", fitnessData[maxIndex].date, fitnessData[maxIndex].time); 
}

void calculateMeanStepCount() {
    if (numRecords == 0) { // Check if records are 0 as if case either file is empty or not loaded in to not cause errros
        printf("No data available.\n");
        return;
    }

    int totalSteps = 0; // Goes through all fitness data and adds the steps in each record to total steps and later works out average by dividing number of steps by the total record and rounding it
    for (int i = 0; i < numRecords; ++i) {
        totalSteps += fitnessData[i].steps;
    }

    int meanSteps = (int)round(totalSteps / numRecords);
    printf("Mean step count: %d\n", meanSteps);
}

void findLongestPeriodAbove500() {
    if (numRecords == 0) { // Check if records are 0 as if case either file is empty or not loaded in to not cause errors
        printf("No data available.\n");
        return;
    }

    int longestStartIndex = -1, longestEndIndex = -1;
    int currentStartIndex = -1, currentEndIndex = -1;
    int longestDuration = 0;

    for (int i = 0; i < numRecords; ++i) {
        if (fitnessData[i].steps > 500) {
            if (currentStartIndex == -1) {
                currentStartIndex = i;  // Start of new period
            }
            currentEndIndex = i; // Continue current period
        } else {
            if (currentStartIndex != -1) {
                int currentDuration = currentEndIndex - currentStartIndex;
                if (currentDuration > longestDuration) {
                    longestDuration = currentDuration; // Update longest duration
                    longestStartIndex = currentStartIndex; // Update the start index of longest period
                    longestEndIndex = currentEndIndex; // Update the end index of longest period
                }
                currentStartIndex = -1; // Reset for next period
            }
        }
    }

    // Check for a period extending to the last record
    if (currentStartIndex != -1) {
        int currentDuration = currentEndIndex - currentStartIndex;
        if (currentDuration > longestDuration) {
            longestDuration = currentDuration; // Update longest duration
            longestStartIndex = currentStartIndex; // Update the start index of longest period
            longestEndIndex = currentEndIndex; // Update the end index of longest period
        }
    }

    if (longestStartIndex == -1) {
        printf("No continuous period found where step count is above 500.\n"); // No period found
    } else {
        printf("Longest period start: %s %s\n", fitnessData[longestStartIndex].date, fitnessData[longestStartIndex].time);
        printf("Longest period end: %s %s\n", fitnessData[longestEndIndex].date, fitnessData[longestEndIndex].time);
    }
}

void handleOption(char option) {
    switch(option) {
        case 'A':
        case 'a':
            importFile();
            break;
        case 'B':
        case 'b':
            displayTotalRecords();
            break;
        case 'C':
        case 'c':
            findFewestSteps();
            break;
        case 'D':
        case 'd':
            findLargestSteps();
            break;
        case 'E':
        case 'e':
            calculateMeanStepCount();
            break;
        case 'F':
        case 'f':
            findLongestPeriodAbove500();
            break;
        case 'Q':
        case 'q':
            printf("Exiting Program.\n");
            exit(0);
        default:
            printf("Invalid choice. Try again.\n");
            displayMenu();
    }
}

int main() {
    char option;

    do {
        displayMenu();
        scanf(" %c", &option); // Read user's choice from single character and then pass it into the handleOption function
        handleOption(option);
    } while (option != 'Q' && option != 'q');

    return 0;
}