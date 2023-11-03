#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define an appropriate struct
typedef struct {
	char date[11];
	char time[6];
	int steps;
} FITNESS_DATA;

// Define any additional variables here



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

int main() {

    // Open the actual file in read mode

    char filename [] = "FitnessData_2023.csv";
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error has occurred, could not open the file.\n");
        return 1;
    }

    int numRecords = 0;
    int buffer_size = 100;
    char line_buffer[buffer_size];

    // Count the number of records in the file
    while (fgets(line_buffer, buffer_size, file) != NULL) {
        numRecords++;
    }

    printf("Number of records in file: %d\n", numRecords);

    // Reset the file pointer to the beginning of the file because first while loop makes it so that file pointer reaches the end of the file and then the while loop below this will not print anything
    fseek(file, 0, SEEK_SET);

    char date[11];
    char time[6];
    char steps_str[10];
    int steps_int;
    int line_counter = 0;

    // First 3 lines in correct format printed
    while (fgets(line_buffer, buffer_size, file) != NULL && line_counter < 3) {
        tokeniseRecord(line_buffer, ",", date, time, steps_str);
        steps_int = atoi(steps_str); // Convert to int as had problem with grade scope told me to change it
        printf("%s/%s/%d\n", date, time, steps_int);
        line_counter++;
    }

    fclose(file);
    return 0;

}