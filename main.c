#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <float.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
                                                                /* JO PROJET INFORMATIQUE */

/*we are going to do structures to help us in the conception of the program*/

#define MAX_TRAINING 100 // line to define the maximum of training for an athlete
#define MAX_PARTICIPANTS 4 // Maximum number of participants in a relay

// ENUMERATION for EVENTS 
typedef enum {
    EVENT_100M,
    EVENT_400M,
    EVENT_5000M,
    EVENT_MARATHON,
    EVENT_RELAY
} EventType;

// STRUCTURE for TRAINING 
typedef struct{
    char date[50]; // date format to be defined 
    EventType event_type; // type of event among "100m", "400" ,etc.
    float time; // time achieved by the athlete 
}Training;

// STRUCTURE for ATHLETE
typedef struct{
    char name[50]; 
    char surname[50]; 
    int age; 
    int weight; 
    char gender[10]; // 'Male' or 'Female'
    char performance_type[50];
    Training trainings[MAX_TRAINING];
    int num_training;
}Athlete;

// STRUCTURE of RELAY (we make a different structure to treat this kind of event)
typedef struct{
    char date[50];
    float split_time[MAX_PARTICIPANTS]; // "split_time[0]" for the first athlete, "split_time[1]" for the second one, etc.
    int position[MAX_PARTICIPANTS];
}RelayTraining;

// STRUCTURE of PERFORMANCES 
typedef struct {
    char date[50];
    float performance;
} Performance;

// Function to validate date format (YYYY-MM-DD)
bool isValidDateFormat(const char *date) {
    if (strlen(date) != 10)
        return false;

    int year, month, day;
    if (sscanf(date, "%d-%d-%d", &year, &month, &day) != 3)
        return false;

    if (year < 0) // negative year
        return false;
    if (month < 1 || month > 12) // month not valid
        return false;
    if (day < 1 || day > 31) // day not valid
        return false;

    // verify day according to the month
    switch(month) {
        case 2: // February
            if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) { // bissextil year
                if (day > 29)
                    return false;
            } else {
                if (day > 28)
                    return false;
            }
            break;
        case 4: // April
        case 6: // June
        case 9: // September
        case 11: // November
            if (day > 30)
                return false;
            break;
    }

    return true;
}


// FUNCTION to calculate LINEAR REGRESSION
void linearRegression(Performance performances[], int num_performances, float *slope, float *intercept) {
    float sum_x = 0, sum_y = 0, sum_xy = 0, sum_x_squared = 0; // we introduce variables important for the linear regression equation

    for (int i = 0; i < num_performances; ++i) {
        float x = i + 1;
        float y = performances[i].performance;
        sum_x += x;
        sum_y += y;
        sum_xy += x * y;
        sum_x_squared += x * x;
    }

    *slope = (num_performances * sum_xy - sum_x * sum_y) / (num_performances * sum_x_squared - sum_x * sum_x); // we apply the formula and stock the result in *slope
    *intercept = (sum_y - (*slope) * sum_x) / num_performances; // stock the result in *intercept
}

void enterAthleteData(Athlete *athlete) {
    char filename[100];
    FILE *file;
    printf("---------------------------------CREATE YOUR ATHLETE--------------------------------- \n");
    while (1) {
        printf("Enter athlete's name: ");
        scanf("%s", athlete->name);

        printf("Enter athlete's surname: ");
        scanf("%s", athlete->surname);

        // Vérification de l'existence du fichier
        sprintf(filename, "%s_%s.txt", athlete->name, athlete->surname);
        file = fopen(filename, "r");
        if (file != NULL) {
            printf("Error: An athlete with the name '%s %s' already exists.\n", athlete->name, athlete->surname);
            fclose(file);
        } else {
            break; // Le fichier n'existe pas, on peut continuer
        }
    }

    while (1) {
        printf("Enter athlete's age: ");
        scanf("%d", &athlete->age);
        if (athlete->age >= 18) {
            break;
        } else {
            printf("Error: Athlete must be at least 18 years old.\n");
        }
    }

    printf("Enter athlete's weight: ");
    scanf("%d", &athlete->weight);

    while (1) {
        printf("Enter athlete's gender (Male/Female): ");
        scanf("%s", athlete->gender);
        if (strcmp(athlete->gender, "Male") == 0 || strcmp(athlete->gender, "Female") == 0) {
            break;
        } else {
            printf("Error: Gender must be either 'Male' or 'Female'.\n");
        }
    }

    printf("Enter athlete's performance type: ");
    scanf("%s", athlete->performance_type);

    athlete->num_training = 0; // Initialize number of trainings to 0
}

// FUNCTION to CREATE FILE 
void createAthleteFile(Athlete athlete) {
    FILE *file;
    char filename[100]; // Nom du fichier
    sprintf(filename, "%s_%s.txt", athlete.name, athlete.surname); // creation of the file by the name and surname of the athlete concerned 
    file = fopen(filename, "w"); // Ouverture du fichier en mode écriture
    if (file != NULL) {
        // write information of athlete in the file
        fprintf(file, "Name: %s\nSurname: %s\nAge: %d\nWeight: %d\nGender: %s\nPerformance Type: %s\n",
                athlete.name, athlete.surname, athlete.age, athlete.weight, athlete.gender, athlete.performance_type);
        fclose(file); // file closing 
        printf("file for %s create with success.\n", athlete.name);
    } else {
        printf("Error: Impossible to creat file for %s.\n", athlete.name);
    }
}

// FUNCTION to READ FILE 
void readAthleteFile(char *filename) {
    FILE *file;
    char line[1000];
    file = fopen(filename, "r"); // open file in lecture mode
    if (file != NULL) {
        printf("Informations of the athlete :\n");
        // print data of file line by line 
        while (fgets(line, sizeof(line), file) != NULL) {
            printf("%s", line);
        }
        fclose(file); // close file after lecture
    } else {
        printf("Error: Impossible to open the file of the athlete.\n");
    }
}

Athlete loadExistingAthlete(Athlete *athlete) {
    
    printf("Enter athlete's name: ");
    scanf("%s", athlete->name);

    printf("Enter athlete's surname: ");
    scanf("%s", athlete->surname);
    
}

void addRelayTraining(Athlete *athlete, const char *training_date) {
    RelayTraining new_relay_training;

    // Copy the training date from addTraining
    strcpy(new_relay_training.date, training_date);

    // Input split time and position for each participant
    for (int i = 0; i < MAX_PARTICIPANTS; ++i) {
        printf("Enter split time for participant %d: ", i + 1);
        scanf("%f", &(new_relay_training.split_time[i]));
        printf("Enter position for participant %d: ", i + 1);
        scanf("%d", &(new_relay_training.position[i]));
    }

    // Ask the user for their position in the relay
    int user_position;
    do {
        printf("Enter your position in the relay (1 to %d): ", MAX_PARTICIPANTS);
        scanf("%d", &user_position);
    } while (user_position < 1 || user_position > MAX_PARTICIPANTS);

    // Add the relay training to athlete's file
    FILE *file;
    char filename[100];
    sprintf(filename, "%s_%s.txt", athlete->name, athlete->surname);
    file = fopen(filename, "a");
    if (file != NULL) {
        fprintf(file, "Date: %s\tEvent Type: %d\t", new_relay_training.date, EVENT_RELAY);
        for (int i = 0; i < MAX_PARTICIPANTS; ++i) {
            fprintf(file, "Participant %d - Split Time: %.2f, Position: %d\t", i + 1, new_relay_training.split_time[i], new_relay_training.position[i]);
        }
        fprintf(file, "\n");
        fclose(file);
        printf("Relay training added to the file of %s successfully.\n", athlete->name);
        // Update the athlete's trainings array
        athlete->trainings[athlete->num_training].event_type = EVENT_RELAY;
        strcpy(athlete->trainings[athlete->num_training].date, new_relay_training.date);
        athlete->num_training++;
    } else {
        printf("Error: Could not open %s's file to add relay training.\n", athlete->name);
    }
}


void addTraining(Athlete *athlete) {
    printf("\n---------------------------------LET'S ADD YOUR TRAINING !---------------------------------\n");
    Training new_training;
    do {
        // Input the training date
        printf("Enter training date (YYYY-MM-DD): ");
        scanf("%s", new_training.date);
    } while (!isValidDateFormat(new_training.date));

    // Input the event type
    int event_choice;
    printf("Select event type:\n");
    printf("0. 100m\n");
    printf("1. 400m\n");
    printf("2. 5000m\n");
    printf("3. Marathon\n");
    printf("4. Relay\n");
    scanf("%d", &event_choice);
    switch (event_choice) {
        case 0:
            new_training.event_type = EVENT_100M;
            break;
        case 1:
            new_training.event_type = EVENT_400M;
            break;
        case 2:
            new_training.event_type = EVENT_5000M;
            break;
        case 3:
            new_training.event_type = EVENT_MARATHON;
            break;
        case 4:
            addRelayTraining(athlete, new_training.date); // Pass the date to addRelayTraining
            return; // Return after adding relay training
        default:
            printf("Invalid choice. Defaulting to 100m.\n");
            new_training.event_type = EVENT_100M;
            break;
    }

    // Input the time achieved
    printf("Enter time achieved: ");
    scanf("%f", &(new_training.time));

    // Add the training to athlete's file
    FILE *file;
    char filename[100];
    sprintf(filename, "%s_%s.txt", athlete->name, athlete->surname);
    file = fopen(filename, "a");
    if (file != NULL) {
        fprintf(file, "Date: %s\tEvent Type: %d\tTime: %.2f\n", new_training.date, new_training.event_type, new_training.time);
        fclose(file);
        printf("Training added to the file of %s successfully.\n", athlete->name);
        // Update the athlete's trainings array
        athlete->trainings[athlete->num_training] = new_training;
        athlete->num_training++;
    } else {
        printf("Error: Could not open %s's file to add training.\n", athlete->name);
    }
}

// FUNCTION to READ ATHLETE TRAINING HISTORY
void readAthleteTrainingHistory(char *filename) {
    FILE *file;
    char line[1000];
    int trainingInfoStarted = 0; // Flag to indicate when training information starts
    file = fopen(filename, "r"); // Open the file in read mode
    if (file != NULL) {
        printf("---------------------------------TRAINING HISTORY OF THE ATHLETE---------------------------------\n");
        while (fgets(line, sizeof(line), file) != NULL) {
            // Check if the line contains the start of training information
            if (strstr(line, "Date:") != NULL) {
                trainingInfoStarted = 1; // Set flag to indicate start of training information
            }
            // If training information has started, then display the line
            if (trainingInfoStarted) {
                char eventType[50];
                if (sscanf(line, "Event Type: %[^\n]", eventType) == 1) {
                    printf("Event Type: %s\n", eventType);
                } else {
                    printf("%s", line); // Display each line of the file
                }
            }
        }
        fclose(file); // Close the file after reading
    } else {
        printf("Error: Unable to open the athlete's file.\n");
    }
}



// FUNCTION to READ ATHLETE RELAY TRAINING HISTORY
void readAthleteRelayTrainingHistory(char *filename) {
    FILE *file;
    char line[1000];
    char date[50];
    file = fopen(filename, "r"); // Open the file in read mode
    if (file != NULL) {
        printf("---------------------------------RELAY TRAINING HISTORY OF THE ATHLETE---------------------------------\n");
        while (fgets(line, sizeof(line), file) != NULL) {
            // Check if the line contains relay training data
            if (strstr(line, "Event Type: 4") != NULL) { // Event Type 4 corresponds to Relay
                printf("%s", line); // Display the relay training data
            }
        }
        fclose(file); // Close the file after reading
    } else {
        printf("Error: Unable to open the athlete's file.\n");
    }
}

// FUNCTION to READ ATHLETE TRAINING HISTORY BY DATE
void readAthleteTrainingHistoryByDate(char *filename) {
    char searchDate[50];
    printf("Enter the date to search for training history (YYYY-MM-DD): ");
    scanf("%s", searchDate);
    
    if (!isValidDateFormat(searchDate)) {
        printf("Error: Invalid date format.\n");
        return;
    }

    FILE *file;
    char line[1000];
    int trainingInfoStarted = 0; // Flag to indicate when training information starts
    file = fopen(filename, "r"); // Open the file in read mode
    if (file != NULL) {
        printf("---------------------------------TRAINING HISTORY OF THE ATHLETE FOR DATE %s---------------------------------\n", searchDate);
        while (fgets(line, sizeof(line), file) != NULL) {
            // Check if the line contains the start of training information
            if (strstr(line, "Date:") != NULL) {
                trainingInfoStarted = 1; // Set flag to indicate start of training information
            }
            // If training information has started and the line contains the search date, then display the line
            if (trainingInfoStarted && strstr(line, searchDate) != NULL) {
                printf("%s", line); // Display each line of the file
            }
        }
        fclose(file); // Close the file after reading
    } else {
        printf("Error: Unable to open the athlete's file.\n");
    }
}

// FUNCTION to READ ATHLETE RELAY TRAINING HISTORY BY DATE
void readAthleteRelayTrainingHistoryByDate(char *filename, char *searchDate) {
    FILE *file;
    char line[1000];
    char date[50];
    file = fopen(filename, "r"); // Open the file in read mode
    if (file != NULL) {
        printf("---------------------------------RELAY TRAINING HISTORY OF THE ATHLETE FOR DATE %s---------------------------------\n", searchDate);
        while (fgets(line, sizeof(line), file) != NULL) {
            // Check if the line contains relay training data and the search date
            if (strstr(line, "Event Type: 4") != NULL && strstr(line, searchDate) != NULL) { // Event Type 4 corresponds to Relay
                printf("%s", line); // Display the relay training data
            }
        }
        fclose(file); // Close the file after reading
    } else {
        printf("Error: Unable to open the athlete's file.\n");
    }
}

// FUNCTION to calculate the best, worst, and average time for a given event
void athletePerformanceSummary(Athlete athlete, EventType event_type) {
    float best_time = FLT_MAX;
    float worst_time = 0;
    float total_time = 0;
    int num_times = 0;
    
    for (int i = 0; i < athlete.num_training; ++i) {
        if (athlete.trainings[i].event_type == event_type) {
            float time = athlete.trainings[i].time;
            if (time < best_time) {
                best_time = time;
            }
            if (time > worst_time) {
                worst_time = time;
            }
            total_time += time;
            num_times++;
        }
    }
    
    if (num_times > 0) {
        float average_time = total_time / num_times;
        printf("Athlete: %s %s\n", athlete.name, athlete.surname);
        printf("Event: ");
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
        printf("Best Time: %.2f\n", best_time);
        printf("Worst Time: %.2f\n", worst_time);
        printf("Average Time: %.2f\n", average_time);
    } else {
        printf("No training records found for this event.\n");
    }
}

// FUNCTION to find the three best athletes for a given event
void findTopAthletesForEvent(Athlete *athletes, int num_athletes, EventType event_type) {
    // Create an array to store the average times of each athlete
    float average_times[num_athletes];
    for (int i = 0; i < num_athletes; ++i) {
        float total_time = 0;
        int num_times = 0;
        for (int j = 0; j < athletes[i].num_training; ++j) {
            if (athletes[i].trainings[j].event_type == event_type) {
                total_time += athletes[i].trainings[j].time;
                num_times++;
            }
        }
        if (num_times > 0) {
            average_times[i] = total_time / num_times;
        } else {
            average_times[i] = FLT_MAX; // If no records found, set average time to maximum float value
        }
    }

    // Sort athletes based on average times
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

    // Print the top three athletes
    printf("---------------------------------TOP THREE ATHLETES FOR ");
    switch (event_type) { // we search all cases 
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
    for (int i = 0; i < num_athletes && i < 3; ++i) {
        printf("%d. %s %s\n", i + 1, athletes[i].name, athletes[i].surname); // we print in order the top three athletes 
    }
}

// FUNCTION to display the time difference for an athlete between two dates
void athleteProgression(Athlete athlete, char *start_date, char *end_date, EventType event_type) {
    float start_time = 0, end_time = 0;
    int found_start = 0, found_end = 0;
    
    for (int i = 0; i < athlete.num_training; ++i) {
        if (!found_start && strcmp(athlete.trainings[i].date, start_date) == 0 && athlete.trainings[i].event_type == event_type) {
            start_time = athlete.trainings[i].time;
            found_start = 1;
        }
        if (!found_end && strcmp(athlete.trainings[i].date, end_date) == 0 && athlete.trainings[i].event_type == event_type) {
            end_time = athlete.trainings[i].time;
            found_end = 1;
        }
        if (found_start && found_end) {
            break;
        }
    }
    
    if (found_start && found_end) {
        printf("Athlete: %s %s\n", athlete.name, athlete.surname); // print athlete's name
        printf("Event: ");
        switch (event_type) { // we search all the cases
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
        printf("Time difference between %s and %s: %.2f\n", start_date, end_date, end_time - start_time); // print the difference between the two dates
    } else {
        printf("No records found for the specified dates and event type.\n"); // if there is no trainings found 
    }
}

// MAIN
int main() {
    // Initialize some athletes
    Athlete athlete1;
    Athlete athlete2;
    Athlete athlete3;
    enterAthleteData(&athlete1);
    enterAthleteData(&athlete2);
    enterAthleteData(&athlete3);

    int number;
    printf("Do you want to find back a file of an athlete ? YES : 1 \n");
    scanf("%d",&number);
    if(number == 1){
        Athlete athlete4 = loadExistingAthlete(&athlete4);
        addTraining(&athlete4);
    }
    

    char athlete1_filename[100];
    sprintf(athlete1_filename, "%s_%s.txt", athlete1.name, athlete1.surname);
    char athlete2_filename[100];
    sprintf(athlete2_filename, "%s_%s.txt", athlete2.name, athlete2.surname);
    char athlete3_filename[100];
    sprintf(athlete3_filename, "%s_%s.txt", athlete3.name, athlete3.surname);


    // Add training records for athletes
    addTraining(&athlete1);
    addTraining(&athlete2);
    
    
    
    // Display athlete files
    readAthleteFile(athlete2_filename);
    
    
    

    // Display training history for athlete4 for a specific date
    readAthleteTrainingHistoryByDate(athlete2_filename);
    
    

    // Display performance summary for athletes
    athletePerformanceSummary(athlete1, EVENT_100M);
    

    // Find top athletes for specific events
    Athlete athletes[] = {athlete1, athlete2, athlete3};
    findTopAthletesForEvent(athletes, sizeof(athletes) / sizeof(athletes[0]), EVENT_100M);
    

    // Display athlete progression between two dates
    athleteProgression(athlete2, "2024-05-05", "2024-05-07", EVENT_100M);

    // exemple of a tab named "performances" thanks to structure "Performance"
    Performance performances[] = {
        {"2024-01-01", 10.2},
        {"2024-02-01", 9.8},
        {"2024-03-01", 9.5},
        {"2024-04-01", 9.3},
        {"2024-05-01", 9.1}
    };
    int num_performances = sizeof(performances) / sizeof(performances[0]);

    float slope, intercept;
    linearRegression(performances, num_performances, &slope, &intercept); // execute the function linearRegression
    printf("equation of linear regression : y = %.2fx + %.2f\n", slope, intercept); // print results of linear equation

    return 0;
}
