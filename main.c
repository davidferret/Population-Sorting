#include <stdio.h>
#include <string.h>
#define MAXLINE 100
#define MAXCHAR 30

void readData(char country[][MAXCHAR], float pop[], int *size);
void sortData(char country[][MAXCHAR], float pop[], int size, int sortBy);
void displayData(char country[][MAXCHAR], float pop[], int size);
void saveToFile(char country[][MAXCHAR], float pop[], int size);

int main() {
    char country[MAXLINE][MAXCHAR];
    float pop[MAXLINE];
    int size, sortBy;
    
    readData(country, pop, &size);
    
    printf("Choose sorting method:\n");
    printf("1 - Sort by Country (Alphabetically)\n");
    printf("2 - Sort by Population (Ascending)\n");
    printf("3 - Sort by Population (Descending)\n");
    printf("Enter choice: ");
    scanf("%d", &sortBy);
    
    sortData(country, pop, size, sortBy);
    displayData(country, pop, size);
    saveToFile(country, pop, size);
    
    printf("Data saved to 'sorted_population.txt'.\n");
    return 0;
}

void readData(char country[][MAXCHAR], float pop[], int *size) {
    FILE *fp = fopen("population.txt", "r");
    if (fp == NULL) {
        printf("File Not Found.\n");
        return;
    }
    
    *size = 0;
    while (fscanf(fp, "%s %f", country[*size], &pop[*size]) != EOF) {
        (*size)++;
    }
    fclose(fp);
}

void sortData(char country[][MAXCHAR], float pop[], int size, int sortBy) {
    char temp_country[MAXCHAR];
    float temp_pop;
    
    for (int iter = 0; iter < size - 1; iter++) {
        for (int i = 0; i < size - 1 - iter; i++) {
            int condition = 0;
            
            if (sortBy == 1) {
                condition = strcmp(country[i], country[i + 1]) > 0;
            } else if (sortBy == 2) {
                condition = pop[i] > pop[i + 1];
            } else if (sortBy == 3) {
                condition = pop[i] < pop[i + 1];
            }
            
            if (condition) {
                strcpy(temp_country, country[i]);
                strcpy(country[i], country[i + 1]);
                strcpy(country[i + 1], temp_country);
                temp_pop = pop[i];
                pop[i] = pop[i + 1];
                pop[i + 1] = temp_pop;
            }
        }
    }
}

void displayData(char country[][MAXCHAR], float pop[], int size) {
    printf("%-15s%12s\n", "Country", "Population (Millions)");
    for (int j = 0; j < size; j++) {
        printf("%-15s%2.2f\n", country[j], pop[j]);
    }
}

void saveToFile(char country[][MAXCHAR], float pop[], int size) {
    FILE *file = fopen("sorted_population.txt", "w");
    if (!file) {
        printf("Error creating file!\n");
        return;
    }
    
    fprintf(file, "%-15s%12s\n", "Country", "Population (Millions)");
    for (int j = 0; j < size; j++) {
        fprintf(file, "%-15s%2.2f\n", country[j], pop[j]);
    }
    fclose(file);
}
