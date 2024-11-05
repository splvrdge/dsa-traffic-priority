#ifndef HEAP_H
#define HEAP_H

#define HEAP_MAX 100 // Maximum number of elements in the heap

typedef struct {
    char type[50];   // Type of vehicle (e.g., "pedestrian", "car")
    char lane[50];   // Lane description (e.g., "main", "diversion")
    int time;        // Time in seconds
} TrafficMovement;

typedef struct {
    TrafficMovement Elem[HEAP_MAX];
    int lastNdx; // Index of the last element
} Heap;

// Function prototypes
void initHeap(Heap *H);
void insertHeap(TrafficMovement x, Heap *H);
TrafficMovement deleteMin(Heap *H);
bool isEmpty(Heap *H);

#endif // HEAP_H
