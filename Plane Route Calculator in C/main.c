#include "planerecord.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void printMenu()
{
    printf("\n\n######### Airline Route Records Database MENU #########\n");
    printf("1. Search by Route\n");
    printf("2. Search by Origin Airport\n");
    printf("3. Search by Destination Airport\n");
    printf("4. Search by Airline\n");
    printf("5. Quit\n");
    printf("Enter your selection: ");
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s data.csv\n", argv[0]);
        return 1;
    }

    FILE *fileIn = fopen(argv[1], "r");

    if (fileIn == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    printf("Opening %s...\n", argv[1]);

    RouteRecord *routeRecords = createRecords(fileIn);

    if (routeRecords == NULL)
    {
        fclose(fileIn);
        return 1;
    }

    int recordsUsed = fillRecords(routeRecords, fileIn);
    fclose(fileIn);

    printf("Unique routes operated by airlines: %d\n", recordsUsed);

    int choice;
    char input1[4];
    char input2[4];

    while (1)
    {
        printMenu();
        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input. Please enter a valid choice.\n");
            while (getchar() != '\n')
                ;
            continue;
        }

        switch (choice)
        {
        case 1:
            printf("Enter origin: ");
            scanf("%s", input1);
            printf("Enter destination: ");
            scanf("%s", input2);
            searchRecords(routeRecords, recordsUsed, input1, input2, ROUTE);
            break;
        case 2:
            printf("Enter origin: ");
            scanf("%s", input1);
            searchRecords(routeRecords, recordsUsed, input1, NULL, ORIGIN);
            break;
        case 3:
            printf("Enter destination: ");
            scanf("%s", input1);
            searchRecords(routeRecords, recordsUsed, input1, NULL, DESTINATION);
            break;
        case 4:
            printf("Enter airline: ");
            scanf("%s", input1);
            searchRecords(routeRecords, recordsUsed, input1, NULL, AIRLINE);
            break;
        case 5:
            free(routeRecords);
            return 0;
        default:
            printf("Invalid choice. Please enter a valid choice.\n");
            break;
        }
    }
}
