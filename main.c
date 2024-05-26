#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <float.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>

/* JO PROJECT */

/* The following code defines structures and enumerations to assist in the design of a program 
   for managing athlete training and performance data. */

#define MAX_TRAINING 100 // Maximum number of training records for an athlete
#define MAX_PARTICIPANTS 4 // Maximum number of participants in a relay race

// ENUMERATION for different types of events an athlete can participate in
typedef enum {
    EVENT_100M,     // 100 meters race
    EVENT_400M,     // 400 meters race
    EVENT_5000M,    // 5000 meters race
    EVENT_MARATHON, // Marathon race
    EVENT_RELAY     // Relay race
} EventType;

// STRUCTURE to record training information for an athlete
typedef struct {
    char date[50];       // Date of the training session (format to be defined)
    EventType event_type;// Type of event (e.g., 100m, 400m, etc.)
    float time;          // Time achieved by the athlete in the training session
} Training;

// STRUCTURE to represent an athlete's personal and training information
typedef struct {
    char name[50];            // Athlete's first name
    char surname[50];         // Athlete's last name
    int age;                  // Athlete's age
    int weight;               // Athlete's weight
    char gender[10];          // Athlete's gender (e.g., 'Male' or 'Female')
    char performance_type[50];// Type of performance (e.g., 'Sprinter', 'Distance Runner')
    Training trainings[MAX_TRAINING]; // Array to hold the athlete's training sessions
    int num_training;         // Number of training sessions recorded
} Athlete;

// STRUCTURE to handle relay race training sessions separately
typedef struct {
    char date[50];             // Date of the relay training session
    float split_time[MAX_PARTICIPANTS]; // Array of split times for each participant in the relay
    int position[MAX_PARTICIPANTS];     // Array of positions for each participant in the relay
} RelayTraining;

// STRUCTURE to record performance data for an athlete
typedef struct {
    char date[50];     // Date of the performance
    float performance; // Performance measurement (e.g., time, distance)
} Performance;


// Function to validate date format (YYYY-MM-DD)
bool isValidDateFormat(const char *date) {
    // Check if the length of the date string is exactly 10 characters
    if (strlen(date) != 10)
        return false;

    int year, month, day;
    // Parse the date string to extract year, month, and day
    if (sscanf(date, "%d-%d-%d", &year, &month, &day) != 3)
        return false;

    // Check if the year is non-negative
    if (year < 0)
        return false;
    // Check if the month is within the valid range (1 to 12)
    if (month < 1 || month > 12)
        return false;
    // Check if the day is within the valid range (1 to 31)
    if (day < 1 || day > 31)
        return false;

    // Verify that the day is valid according to the specific month
    switch (month) {
        case 2: // February
            // Check for leap year
            if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) { // Leap year
                if (day > 29)
                    return false; // Invalid day for February in a leap year
            } else {
                if (day > 28)
                    return false; // Invalid day for February in a common year
            }
            break;
        case 4: // April
        case 6: // June
        case 9: // September
        case 11: // November
            if (day > 30)
                return false; // Invalid day for months with 30 days
            break;
    }

    // If all checks pass, return true indicating a valid date format
    return true;
}


// FUNCTION to calculate LINEAR REGRESSION
void linearRegression(Performance performances[], int num_performances, float *slope, float *intercept) {
    // Initialize variables to store sums needed for the linear regression calculation
    float sum_x = 0, sum_y = 0, sum_xy = 0, sum_x_squared = 0;

    // Loop through each performance record
    for (int i = 0; i < num_performances; ++i) {
        float x = i + 1; // x represents the index (starting from 1)
        float y = performances[i].performance; // y is the performance value
        sum_x += x; // Sum of x values
        sum_y += y; // Sum of y values
        sum_xy += x * y; // Sum of products of x and y
        sum_x_squared += x * x; // Sum of squares of x values
    }

    // Calculate the slope using the linear regression formula
    *slope = (num_performances * sum_xy - sum_x * sum_y) / 
             (num_performances * sum_x_squared - sum_x * sum_x);

    // Calculate the intercept using the linear regression formula
    *intercept = (sum_y - (*slope) * sum_x) / num_performances;
}

void enterAthleteData(Athlete *athlete) {
    char filename[100]; // Buffer to hold the filename
    FILE *file; // File pointer
    printf("---------------------------------CREATE YOUR ATHLETE--------------------------------- \n");
    
    // Loop to ensure a unique athlete name and surname
    while (1) {
        printf("Enter athlete's name: ");
        scanf("%s", athlete->name); // Read athlete's name

        printf("Enter athlete's surname: ");
        scanf("%s", athlete->surname); // Read athlete's surname

        // Construct the filename based on the athlete's name and surname
        sprintf(filename, "%s_%s.txt", athlete->name, athlete->surname);
        
        // Check if a file with this name already exists
        file = fopen(filename, "r");
        if (file != NULL) {
            // If the file exists, print an error message and close the file
            printf("Error: An athlete with the name '%s %s' already exists.\n", athlete->name, athlete->surname);
            fclose(file);
        } else {
            // If the file does not exist, break out of the loop to continue
            break;
        }
    }

    // Loop to ensure the athlete's age is at least 18
    while (1) {
        printf("Enter athlete's age: ");
        scanf("%d", &athlete->age); // Read athlete's age
        if (athlete->age >= 18 && athlete->age <= 40) {
            break; // Age is valid, break out of the loop
        } else {
            // Age is not valid, print an error message
            printf("Error: Athlete must be at least 18 years old or less than 40 years old\n");
        }
    }

    // Loop to ensure the athlete's weight is between 50 and 90 kilograms
    while (1) {
        printf("Enter athlete's weight: ");
        scanf("%d", &athlete->weight); // Read athlete's weight
        if (athlete->weight >= 50 && athlete->weight <= 90) {
            break; // Weight is valid, break out of the loop
        } else {
            // Weight is not valid, print an error message
            printf("Error: Athlete's weight must be between 50 and 90 kilograms.\n");
        }
    }

    // Loop to ensure the athlete's gender is either 'Male' or 'Female'
    while (1) {
        printf("Enter athlete's gender (Male/Female): ");
        scanf("%s", athlete->gender); // Read athlete's gender
        if (strcmp(athlete->gender, "Male") == 0 || strcmp(athlete->gender, "Female") == 0) {
            break; // Gender is valid, break out of the loop
        } else {
            // Gender is not valid, print an error message
            printf("Error: Gender must be either 'Male' or 'Female'.\n");
        }
    }

    // Loop to ensure the athlete's performance type is either 'sprint' or 'stamina'
    while (1) {
        printf("Enter athlete's performance type (sprint/stamina): ");
        scanf("%s", athlete->performance_type); // Read athlete's performance type
        if (strcmp(athlete->performance_type, "sprint") == 0 || strcmp(athlete->performance_type, "stamina") == 0) {
            break; // Performance type is valid, break out of the loop
        } else {
            // Performance type is not valid, print an error message
            printf("Error: Performance type must be either 'sprint' or 'stamina'.\n");
        }
    }

    athlete->num_training = 0; // Initialize the number of training sessions to 0
}

// FUNCTION to CREATE FILE
void createAthleteFile(Athlete athlete) {
    FILE *file; // File pointer
    char filename[100]; // File name
    // Construct the filename based on the athlete's name and surname
    sprintf(filename, "%s_%s.txt", athlete.name, athlete.surname);
    // Open the file in write mode
    file = fopen(filename, "w");
    if (file != NULL) {
        // Write athlete information to the file
        fprintf(file, "Name: %s\nSurname: %s\nAge: %d\nWeight: %d\nGender: %s\nPerformance Type: %s\n",
                athlete.name, athlete.surname, athlete.age, athlete.weight, athlete.gender, athlete.performance_type);
        fclose(file); // Close the file
        printf("File for %s created successfully.\n", athlete.name);
    } else {
        printf("Error: Unable to create file for %s.\n", athlete.name);
    }
}

// FUNCTION to READ FILE
void readAthleteFile(char *filename) {
    FILE *file; // File pointer
    char line[1000]; // Buffer to store each line of the file
    // Open the file in read mode
    file = fopen(filename, "r");
    if (file != NULL) {
        printf("Athlete's information:\n");
        // Read and print each line of the file
        while (fgets(line, sizeof(line), file) != NULL) {
            printf("%s", line);
        }
        fclose(file); // Close the file after reading
    } else {
        printf("Error: Unable to open the athlete's file.\n");
    }
}


// FUNCTION to load EXISTING ATHLETE
Athlete loadExistingAthlete() {
    Athlete athlete; // Declare a variable of type Athlete to store the athlete's data
    char filename[100]; // Declare a buffer to hold the filename
    FILE *file; // Declare a file pointer

    char choice;

    printf("Do you want to load an existing athlete? (y/n): ");
    scanf(" %c", &choice);

    if (choice != 'y') {
        printf("Exiting without loading an athlete.\n");
        exit(0); // Quitte la fonction sans rien si l'utilisateur ne veut pas charger d'athlète
    }

    printf("Enter athlete's name: ");
    scanf("%s", athlete.name); // Prompt the user to enter the athlete's name and read it

    printf("Enter athlete's surname: ");
    scanf("%s", athlete.surname); // Prompt the user to enter the athlete's surname and read it

    // Construct the filename using the athlete's name and surname
    sprintf(filename, "%s_%s.txt", athlete.name, athlete.surname);

    // Try to open the file in read mode
    file = fopen(filename, "r");
    if (file == NULL) {
        // If the file does not exist, print an error message and exit the function
        printf("Error: No athlete found with the name '%s %s'.\n", athlete.name, athlete.surname);
        exit(1); // Exit the function with an error code
    } else {
        // If the file exists, close it and print a message indicating the athlete was found
        fclose(file);
        printf("Athlete '%s %s' found.\n", athlete.name, athlete.surname);
    }

    // Return the athlete structure containing the loaded data
    return athlete;
}

void addRelayTraining(Athlete *athlete, const char *training_date) {
    RelayTraining new_relay_training; // Declare a variable to store the new relay training data

    // Copy the training date from the parameter to the new relay training
    strcpy(new_relay_training.date, training_date);

    // Input split time and position for each participant
    for (int i = 0; i < MAX_PARTICIPANTS; ++i) {
        printf("Enter split time for participant %d: ", i + 1);
        scanf("%f", &(new_relay_training.split_time[i])); // Prompt the user for split time
        printf("Enter position for participant %d: ", i + 1);
        scanf("%d", &(new_relay_training.position[i])); // Prompt the user for position
    }

    // Ask the user for their position in the relay
    int user_position;
    do {
        printf("Enter your position in the relay (1 to %d): ", MAX_PARTICIPANTS);
        scanf("%d", &user_position); // Prompt the user for their position
    } while (user_position < 1 || user_position > MAX_PARTICIPANTS); // Ensure the position is within valid range

    // Add the relay training to the athlete's file
    FILE *file; // File pointer
    char filename[100]; // Buffer to hold the filename
    // Construct the filename using the athlete's name and surname
    sprintf(filename, "%s_%s.txt", athlete->name, athlete->surname);
    // Open the file in append mode
    file = fopen(filename, "a");
    if (file != NULL) {
        // Write the relay training details to the file
        fprintf(file, "Date: %s\tEvent Type: %d\t", new_relay_training.date, EVENT_RELAY);
        for (int i = 0; i < MAX_PARTICIPANTS; ++i) {
            fprintf(file, "Participant %d - Split Time: %.2f, Position: %d\t", i + 1, new_relay_training.split_time[i], new_relay_training.position[i]);
        }
        fprintf(file, "\n"); // Add a new line
        fclose(file); // Close the file
        printf("Relay training added to %s's file successfully.\n", athlete->name);
        // Update the athlete's trainings array with the new relay training
        athlete->trainings[athlete->num_training].event_type = EVENT_RELAY;
        strcpy(athlete->trainings[athlete->num_training].date, new_relay_training.date);
        athlete->num_training++; // Increment the number of trainings
    } else {
        printf("Error: Could not open file to add relay training for %s.\n", athlete->name);
    }
}


void addTraining(Athlete *athlete) {
    printf("\n---------------------------------LET'S ADD YOUR TRAINING !---------------------------------\n");
    Training new_training; // Declare a variable to store the new training data
    
    // Loop to ensure valid date format
    do {
        // Input the training date
        printf("Enter training date (YYYY-MM-DD): ");
        scanf("%s", new_training.date); // Prompt the user to enter the training date
    } while (!isValidDateFormat(new_training.date)); // Validate the date format using isValidDateFormat function

    // Input the event type
    int event_choice; // Variable to store the user's event choice
    printf("Select event type:\n");
    printf("0. 100m\n");
    printf("1. 400m\n");
    printf("2. 5000m\n");
    printf("3. Marathon\n");
    printf("4. Relay\n");
    scanf("%d", &event_choice); // Prompt the user to select an event type
    switch (event_choice) {
        case 0:
            new_training.event_type = EVENT_100M; // Set event type to 100m
            break;
        case 1:
            new_training.event_type = EVENT_400M; // Set event type to 400m
            break;
        case 2:
            new_training.event_type = EVENT_5000M; // Set event type to 5000m
            break;
        case 3:
            new_training.event_type = EVENT_MARATHON; // Set event type to Marathon
            break;
        case 4:
            addRelayTraining(athlete, new_training.date); // Call addRelayTraining function for relay event, passing the date
            return; // Return after adding relay training
        default:
            printf("Invalid choice. Defaulting to 100m.\n");
            new_training.event_type = EVENT_100M; // Default event type to 100m for invalid choices
            break;
    }

    // Input the time achieved
    printf("Enter time achieved: ");
    scanf("%f", &(new_training.time)); // Prompt the user to enter the time achieved

    // Add the training to athlete's file
    FILE *file; // File pointer
    char filename[100]; // Buffer to hold the filename
    sprintf(filename, "%s_%s.txt", athlete->name, athlete->surname); // Construct the filename using athlete's name and surname
    file = fopen(filename, "a"); // Open the file in append mode
    if (file != NULL) {
        // Write the training details to the file
        fprintf(file, "Date: %s\tEvent Type: %d\tTime: %.2f\n", new_training.date, new_training.event_type, new_training.time);
        fclose(file); // Close the file
        printf("Training added to %s's file successfully.\n", athlete->name);
        // Update the athlete's trainings array with the new training
        athlete->trainings[athlete->num_training] = new_training;
        athlete->num_training++; // Increment the number of trainings
    } else {
        printf("Error: Could not open %s's file to add training.\n", athlete->name);
    }
}


// FUNCTION to READ ATHLETE TRAINING HISTORY
void readAthleteTrainingHistory(char *filename) {
    FILE *file; // File pointer
    char line[1000]; // Buffer to store each line of the file
    int trainingInfoStarted = 0; // Flag to indicate when training information starts
    
    // Open the file in read mode
    file = fopen(filename, "r");
    if (file != NULL) {
        printf("---------------------------------TRAINING HISTORY OF THE ATHLETE---------------------------------\n");
        // Iterate through each line of the file
        while (fgets(line, sizeof(line), file) != NULL) {
            // Check if the line contains the start of training information
            if (strstr(line, "Date:") != NULL) {
                trainingInfoStarted = 1; // Set flag to indicate the start of training information
            }
            // If training information has started, then display the line
            if (trainingInfoStarted) {
                char eventType[50]; // Buffer to store the event type
                // Attempt to extract the event type from the line
                if (sscanf(line, "Event Type: %[^\n]", eventType) == 1) {
                    printf("Event Type: %s\n", eventType); // Print the event type
                } else {
                    printf("%s", line); // Display each line of the file
                }
            }
        }
        fclose(file); // Close the file after reading
    } else {
        printf("Error: Unable to open the athlete's file.\n"); // Print an error message if the file cannot be opened
    }
}




// FUNCTION to READ ATHLETE RELAY TRAINING HISTORY
void readAthleteRelayTrainingHistory(char *filename) {
    FILE *file; // File pointer
    char line[1000]; // Buffer to store each line of the file
    
    // Open the file in read mode
    file = fopen(filename, "r");
    if (file != NULL) {
        printf("---------------------------------RELAY TRAINING HISTORY OF THE ATHLETE---------------------------------\n");
        // Iterate through each line of the file
        while (fgets(line, sizeof(line), file) != NULL) {
            // Check if the line contains relay training data by searching for the event type
            if (strstr(line, "Event Type: 4") != NULL) { // Event Type 4 corresponds to Relay
                printf("%s", line); // Display the relay training data
            }
        }
        fclose(file); // Close the file after reading
    } else {
        printf("Error: Unable to open the athlete's file.\n"); // Print an error message if the file cannot be opened
    }
}


// FUNCTION to READ ATHLETE TRAINING HISTORY BY DATE
void readAthleteTrainingHistoryByDate(char *filename) {
    char searchDate[50]; // Variable to store the date to search for
    printf("Enter the date to search for training history (YYYY-MM-DD): ");
    scanf("%s", searchDate); // Prompt the user to enter the date
    
    // Validate the date format using the isValidDateFormat function
    if (!isValidDateFormat(searchDate)) {
        printf("Error: Invalid date format.\n"); // Print an error message if the date format is invalid
        return; // Return from the function
    }

    FILE *file; // File pointer
    char line[1000]; // Buffer to store each line of the file
    int trainingInfoStarted = 0; // Flag to indicate when training information starts
    
    // Open the file in read mode
    file = fopen(filename, "r");
    if (file != NULL) {
        printf("---------------------------------TRAINING HISTORY OF THE ATHLETE FOR DATE %s---------------------------------\n", searchDate);
        // Iterate through each line of the file
        while (fgets(line, sizeof(line), file) != NULL) {
            // Check if the line contains the start of training information
            if (strstr(line, "Date:") != NULL) {
                trainingInfoStarted = 1; // Set flag to indicate the start of training information
            }
            // If training information has started and the line contains the search date, then display the line
            if (trainingInfoStarted && strstr(line, searchDate) != NULL) {
                printf("%s", line); // Display each line of the file
            }
        }
        fclose(file); // Close the file after reading
    } else {
        printf("Error: Unable to open the athlete's file.\n"); // Print an error message if the file cannot be opened
    }
}

// FUNCTION to READ ATHLETE RELAY TRAINING HISTORY BY DATE
void readAthleteRelayTrainingHistoryByDate(char *filename, char *searchDate) {
    FILE *file; // File pointer
    char line[1000]; // Buffer to store each line of the file
    
    // Open the file in read mode
    file = fopen(filename, "r");
    if (file != NULL) {
        printf("---------------------------------RELAY TRAINING HISTORY OF THE ATHLETE FOR DATE %s---------------------------------\n", searchDate);
        // Iterate through each line of the file
        while (fgets(line, sizeof(line), file) != NULL) {
            // Check if the line contains relay training data and matches the search date
            if (strstr(line, "Event Type: 4") != NULL && strstr(line, searchDate) != NULL) { // Event Type 4 corresponds to Relay
                printf("%s", line); // Display the relay training data
            }
        }
        fclose(file); // Close the file after reading
    } else {
        printf("Error: Unable to open the athlete's file.\n"); // Print an error message if the file cannot be opened
    }
}


// FUNCTION to calculate the best, worst, and average time for a given event
void athletePerformanceSummary(Athlete athlete, EventType event_type) {
    float best_time = FLT_MAX; // Initialize the best time to the maximum float value
    float worst_time = 0; // Initialize the worst time to 0
    float total_time = 0; // Initialize the total time to 0
    int num_times = 0; // Initialize the number of times for the event to 0
    
    // Iterate through each training record of the athlete
    for (int i = 0; i < athlete.num_training; ++i) {
        // Check if the event type of the training matches the given event type
        if (athlete.trainings[i].event_type == event_type) {
            float time = athlete.trainings[i].time; // Get the time for the training
            // Update the best time if the current time is less than the current best time
            if (time < best_time) {
                best_time = time;
            }
            // Update the worst time if the current time is greater than the current worst time
            if (time > worst_time) {
                worst_time = time;
            }
            total_time += time; // Add the time to the total time
            num_times++; // Increment the number of times for the event
        }
    }
    
    // Check if there are any training records for the event
    if (num_times > 0) {
        float average_time = total_time / num_times; // Calculate the average time
        // Print athlete and event information
        printf("Athlete: %s %s\n", athlete.name, athlete.surname);
        printf("Event: ");
        // Print the event type based on the given event type
        switch (event_type) {
            case EVENT_100M:
                printf("100m\n");
                break;
            case EVENT_400M:
                printf("400m\n");
                break;
            case EVENT_5000M:
                printf("5000m\n");
                break;
            case EVENT_MARATHON:
                printf("Marathon\n");
                break;
            case EVENT_RELAY:
                printf("Relay\n");
                break;
        }
        // Print the best, worst, and average times
        printf("Best Time: %.2f\n", best_time);
        printf("Worst Time: %.2f\n", worst_time);
        printf("Average Time: %.2f\n", average_time);
    } else {
        printf("No training records found for this event.\n"); // Print a message if no training records are found
    }
}

// FUNCTION to find the three best athletes for a given event
void findTopAthletesForEvent(Athlete *athletes, int num_athletes, EventType event_type) {
    // Create an array to store the average times of each athlete
    float average_times[num_athletes];
    
    // Calculate the average times for each athlete
    for (int i = 0; i < num_athletes; ++i) {
        float total_time = 0; // Initialize the total time for the athlete
        int num_times = 0; // Initialize the number of times for the athlete
        // Iterate through the athlete's trainings
        for (int j = 0; j < athletes[i].num_training; ++j) {
            // Check if the event type matches the given event type
            if (athletes[i].trainings[j].event_type == event_type) {
                total_time += athletes[i].trainings[j].time; // Add the time to the total time
                num_times++; // Increment the number of times
            }
        }
        // Calculate the average time for the athlete and store it in the array
        if (num_times > 0) {
            average_times[i] = total_time / num_times;
        } else {
            average_times[i] = FLT_MAX; // If no records found, set average time to maximum float value
        }
    }

    // Sort athletes based on average times (using bubble sort algorithm)
    for (int i = 0; i < num_athletes - 1; ++i) {
        for (int j = 0; j < num_athletes - i - 1; ++j) {
            if (average_times[j] > average_times[j + 1]) {
                // Swap average times
                float temp_time = average_times[j];
                average_times[j] = average_times[j + 1];
                average_times[j + 1] = temp_time;
                // Swap athletes
                Athlete temp_athlete = athletes[j];
                athletes[j] = athletes[j + 1];
                athletes[j + 1] = temp_athlete;
            }
        }
    }

    // Print the top three athletes for the given event
    printf("---------------------------------TOP THREE ATHLETES FOR ");
    switch (event_type) { // Print the event type based on the given event type
        case EVENT_100M:
            printf("100m:\n");
            break;
        case EVENT_400M:
            printf("400m:\n");
            break;
        case EVENT_5000M:
            printf("5000m:\n");
            break;
        case EVENT_MARATHON:
            printf("Marathon:\n");
            break;
        case EVENT_RELAY:
            printf("Relay:\n");
            break;
    }
    // Iterate through the top three athletes and print their names
    for (int i = 0; i < num_athletes && i < 3; ++i) {
        printf("%d. %s %s\n", i + 1, athletes[i].name, athletes[i].surname);
    }
}


// FUNCTION to display the time difference for an athlete between two dates
void athleteProgression(Athlete athlete, char *start_date, char *end_date, EventType event_type) {
    float start_time = 0, end_time = 0; // Initialize start and end times
    int found_start = 0, found_end = 0; // Flags to indicate if start and end dates are found
    
    // Iterate through the athlete's training records
    for (int i = 0; i < athlete.num_training; ++i) {
        // Check if start date and event type match and start time is not found yet
        if (!found_start && strcmp(athlete.trainings[i].date, start_date) == 0 && athlete.trainings[i].event_type == event_type) {
            start_time = athlete.trainings[i].time; // Assign start time
            found_start = 1; // Set flag for start date found
        }
        // Check if end date and event type match and end time is not found yet
        if (!found_end && strcmp(athlete.trainings[i].date, end_date) == 0 && athlete.trainings[i].event_type == event_type) {
            end_time = athlete.trainings[i].time; // Assign end time
            found_end = 1; // Set flag for end date found
        }
        // If both start and end times are found, break out of the loop
        if (found_start && found_end) {
            break;
        }
    }
    
    // Check if both start and end times are found
    if (found_start && found_end) {
        printf("Athlete: %s %s\n", athlete.name, athlete.surname); // Print athlete's name
        printf("Event: ");
        switch (event_type) { // Print the event type based on the given event type
            case EVENT_100M:
                printf("100m\n");
                break;
            case EVENT_400M:
                printf("400m\n");
                break;
            case EVENT_5000M:
                printf("5000m\n");
                break;
            case EVENT_MARATHON:
                printf("Marathon\n");
                break;
            case EVENT_RELAY:
                printf("Relay\n");
                break;
        }
        // Print the time difference between start and end dates
        printf("Time difference between %s and %s: %.2f\n", start_date, end_date, end_time - start_time);
    } else {
        printf("No records found for the specified dates and event type.\n"); // Print a message if no records found
    }
}


// MAIN
int main() {

    // Initialize some athletes
    Athlete athlete1;
    Athlete athlete2;
    Athlete athlete3;
    
    

    enterAthleteData(&athlete1); // Enter data for athlete 1
    enterAthleteData(&athlete2); // Enter data for athlete 2
    enterAthleteData(&athlete3); // Enter data for athlete 3
    
    // Create filenames for athletes
    char athlete1_filename[100];
    sprintf(athlete1_filename, "%s_%s.txt", athlete1.name, athlete1.surname);
    char athlete2_filename[100];
    sprintf(athlete2_filename, "%s_%s.txt", athlete2.name, athlete2.surname);
    char athlete3_filename[100];
    sprintf(athlete3_filename, "%s_%s.txt", athlete3.name, athlete3.surname);

    // Add training records for athletes
    int num_trainings;

    printf("Enter the number of trainings you want to add for athlete 1: ");
    scanf("%d", &num_trainings);
    for (int i = 0; i < num_trainings; ++i) {
        addTraining(&athlete1);
    }

    printf("Enter the number of trainings you want to add for athlete 2: ");
    scanf("%d", &num_trainings);
    for (int i = 0; i < num_trainings; ++i) {
        addTraining(&athlete2);
    }

    printf("Enter the number of trainings you want to add for athlete 3: ");
    scanf("%d", &num_trainings);
    for (int i = 0; i < num_trainings; ++i) {
        addTraining(&athlete3);
    }

    int choice;

    // Display athlete file

    printf("athlete 1, do you want to READ the FILE or not ? YES : 1 | NO : 2 \n");
    scanf("%d",&choice);
    if(choice == 1){
        readAthleteFile(athlete1_filename);
    }
    printf("athlete 2, do you want to READ the FILE or not ? YES : 1 | NO : 2 \n");
    scanf("%d",&choice);
    if(choice == 1){
        readAthleteFile(athlete2_filename);
    }
    printf("athlete 3, do you want to READ the FILE or not ? YES : 1 | NO : 2 \n");
    scanf("%d",&choice);
    if(choice == 1){
        readAthleteFile(athlete3_filename);
    }

    
    // Display training history for athlete2 for a specific date
    printf("athlete 1, do you want to search a training by a DATE or not ? YES : 1 | NO : 2 \n");
    scanf("%d",&choice);
    if(choice == 1){
        readAthleteTrainingHistoryByDate(athlete1_filename);
    }
    printf("athlete 2, do you want to search a training by a DATE or not ? YES : 1 | NO : 2 \n");
    scanf("%d",&choice);
    if(choice == 1){
        readAthleteTrainingHistoryByDate(athlete2_filename);
    }
    printf("athlete 3, do you want to search a training by a DATE or not ? YES : 1 | NO : 2 \n");
    scanf("%d",&choice);
    if(choice == 1){
        readAthleteTrainingHistoryByDate(athlete3_filename);
    }
    
    // Display performance summary for athletes
    printf("athlete 1, do you want to read SUMMARY performances ? YES : 1 | NO : 2 \n");
    scanf("%d",&choice);
    if(choice == 1){
        athletePerformanceSummary(athlete1, EVENT_100M);
    }

    printf("athlete 2, do you want to read SUMMARY performances ? YES : 1 | NO : 2 \n");
    scanf("%d",&choice);
    if(choice == 1){
        athletePerformanceSummary(athlete2, EVENT_100M);
    }
    printf("athlete 3, do you want to read SUMMARY performances ? YES : 1 | NO : 2 \n");
    scanf("%d",&choice);
    if(choice == 1){
        athletePerformanceSummary(athlete3, EVENT_100M);
    }
    
    
    // Find top athletes for specific events
    // example with 3 athletes
    Athlete athletes[] = {athlete1, athlete2, athlete3};
    findTopAthletesForEvent(athletes, sizeof(athletes) / sizeof(athletes[0]), EVENT_100M);
    
    // Display athlete progression between two dates
    athleteProgression(athlete2, "2024-05-05", "2024-05-07", EVENT_100M);

    // Example of a table named "performances" using the structure "Performance"
    Performance performances[] = {
        {"2024-01-01", 10.2},
        {"2024-02-01", 9.8},
        {"2024-03-01", 9.5},
        {"2024-04-01", 9.3},
        {"2024-05-01", 9.1}
    };
    int num_performances = sizeof(performances) / sizeof(performances[0]);

    float slope, intercept;
    linearRegression(performances, num_performances, &slope, &intercept); // Execute the linear regression function
    printf("Equation of linear regression: y = %.2fx + %.2f\n", slope, intercept); // Print results of linear equation

    // If the user wants to find an athlete, load existing athlete data and add training
    Athlete athlete5 = loadExistingAthlete(); // Load existing athlete data
    addTraining(&athlete5); // Add training for the existing athlete

    return 0; // End of main function
}
