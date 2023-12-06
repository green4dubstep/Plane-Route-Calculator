#include "planerecord.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

RouteRecord *createRecords(FILE *fileIn)
{
    char buffer[256];
    fgets(buffer, sizeof(buffer), fileIn);

    int recordCount = 0;
    while (fgets(buffer, sizeof(buffer), fileIn) != NULL)
    {
        recordCount++;
    }

    rewind(fileIn);

    RouteRecord *routeRecords = (RouteRecord *)malloc(recordCount * sizeof(RouteRecord));

    for (int i = 0; i < recordCount; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            routeRecords[i].passengers[j] = 0;
        }
    }

    return routeRecords;
}

int fillRecords(RouteRecord *r, FILE *fileIn)
{
    return 0;
}

int findAirlineRoute(RouteRecord *r, int length, const char *origin, const char *destination, const char *airline, int curIdx)
{
    if (curIdx < length)
    {
        if (strcmp(r[curIdx].origin, origin) == 0 &&
            strcmp(r[curIdx].destination, destination) == 0 &&
            strcmp(r[curIdx].airline, airline) == 0)
        {
            return curIdx;
        }
        else
        {

            return findAirlineRoute(r, length, origin, destination, airline, curIdx + 1);
        }
    }
    else
    {
        return -1;
    }
}

void searchRecords(RouteRecord *r, int length, const char *key1, const char *key2, SearchType st)
{
    int totalPassengers = 0;
    int totalPassengersByMonth[6] = {0};

    for (int i = 0; i < length; i++)
    {
        int match = 0;

        switch (st)
        {
        case ROUTE:
            match = (strcmp(r[i].origin, key1) == 0 && strcmp(r[i].destination, key2) == 0);
            break;
        case ORIGIN:
            match = (strcmp(r[i].origin, key1) == 0);
            break;
        case DESTINATION:
            match = (strcmp(r[i].destination, key1) == 0);
            break;
        case AIRLINE:
            match = (strcmp(r[i].airline, key1) == 0);
            break;
        }

        if (match)
        {
            printf("%s (%s-%s) ", r[i].airline, r[i].origin, r[i].destination);

            totalPassengers += r[i].passengers[0] + r[i].passengers[1] + r[i].passengers[2] +
                               r[i].passengers[3] + r[i].passengers[4] + r[i].passengers[5];

            for (int j = 0; j < 6; j++)
            {
                totalPassengersByMonth[j] += r[i].passengers[j];
            }
        }
    }

    if (totalPassengers > 0)
    {
        printf("\nStatistics\n");
        printf("Total Passengers: %d\n", totalPassengers);

        for (int i = 0; i < 6; i++)
        {
            printf("Total Passengers in Month %d: %d\n", i + 1, totalPassengersByMonth[i]);
        }

        printf("Average Passengers per Month: %.2f\n", (float)totalPassengers / 6);
    }
    else
    {
        printf("No matches found.\n");
    }
}
