#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "heap.h"

// Function to process multiple traffic scenarios from a file
void processTrafficData(const char *inputFile, const char *outputFile)
{
    FILE *file = fopen(inputFile, "r");
    if (!file)
    {
        perror("Unable to open input file");
        return;
    }

    FILE *output = fopen(outputFile, "w");
    if (!output)
    {
        perror("Unable to open output file");
        fclose(file);
        return;
    }

    char line[256];
    Heap H;

    // Process each line (scenario)
    while (fgets(line, sizeof(line), file))
    {
        initHeap(&H);
        int totalTime = 0;

        // Tokenize each line into traffic movements
        char *token = strtok(line, "\n");    // Remove newline
        char *movement = strtok(token, ","); // Get the first movement

        while (movement != NULL)
        {
            TrafficMovement data;
            sscanf(movement, "%49[^,],%49[^,],%d", data.type, data.lane, &data.time);
            insertHeap(data, &H);
            movement = strtok(NULL, ","); // Move to the next movement
        }

        // Calculate total time for pedestrians on the main lane
        while (!isEmpty(&H))
        {
            TrafficMovement movement = deleteMin(&H);
            if (strcmp(movement.type, "pedestrian") == 0 && strcmp(movement.lane, "main") == 0)
            {
                totalTime += movement.time;
            }
        }

        fprintf(output, "Total time for scenario: %d seconds\n", totalTime);
    }

    fclose(file);
    fclose(output);
}

int main()
{
    processTrafficData("traffic_scenarios.dat", "traffic_result.dat");
    return 0;
}
