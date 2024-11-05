/*
    Author: Francis James Lagang
    Date: November 29, 2024

    Description:
    The data will contain the priority, the traffic movement (sign, primary lane and secondary lanes, direction), and the time. This will be stored in the file called “traffic.dat”.
    Find the total time before a main pedestrian will be able to cross the road.
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "heap.h"

// Function to process traffic data from a file
void processTrafficData(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("Unable to open file");
        return;
    }

    Heap H;
    initHeap(&H);
    TrafficMovement data;

    // Read data from the file and insert into the heap
    while (fscanf(file, "%49s %49s %d", data.type, data.lane, &data.time) != EOF)
    {
        insertHeap(data, &H);
    }
    fclose(file);

    // Calculate total time for pedestrians on the main lane
    int totalTime = 0;

    while (!isEmpty(&H))
    {
        TrafficMovement movement = deleteMin(&H);
        if (strcmp(movement.type, "pedestrian") == 0 && strcmp(movement.lane, "main") == 0)
        {
            totalTime += movement.time;
        }
    }

    printf("Total time before a main pedestrian can cross: %d seconds\n", totalTime);
}

int main()
{
    processTrafficData("traffic.dat");
    return 0;
}
