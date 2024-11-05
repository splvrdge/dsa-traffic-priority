#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "heap.h"

// Initialize the heap
void initHeap(Heap *H)
{
    H->lastNdx = -1;
}

// Insert an element into the heap
void insertHeap(TrafficMovement x, Heap *H)
{
    if (H->lastNdx >= HEAP_MAX - 1)
    {
        printf("Heap is full!\n");
        return;
    }

    H->lastNdx++;
    int childNdx = H->lastNdx;
    H->Elem[childNdx] = x;

    int parentNdx = (childNdx - 1) / 2;
    while (childNdx > 0 && H->Elem[childNdx].time < H->Elem[parentNdx].time)
    {
        // Swap
        TrafficMovement temp = H->Elem[childNdx];
        H->Elem[childNdx] = H->Elem[parentNdx];
        H->Elem[parentNdx] = temp;

        childNdx = parentNdx;
        parentNdx = (childNdx - 1) / 2;
    }
}

// Delete the minimum element from the heap
TrafficMovement deleteMin(Heap *H)
{
    if (H->lastNdx == -1)
    {
        printf("Heap is empty!\n");
        TrafficMovement empty = {"", "", 0}; // Return an empty TrafficMovement
        return empty;
    }

    TrafficMovement minElem = H->Elem[0];
    H->Elem[0] = H->Elem[H->lastNdx--]; // Replace root with last element

    int parentNdx = 0;
    while (true)
    {
        int leftChild = 2 * parentNdx + 1;
        int rightChild = 2 * parentNdx + 2;
        int smallest = parentNdx;

        if (leftChild <= H->lastNdx && H->Elem[leftChild].time < H->Elem[smallest].time)
        {
            smallest = leftChild;
        }
        if (rightChild <= H->lastNdx && H->Elem[rightChild].time < H->Elem[smallest].time)
        {
            smallest = rightChild;
        }
        if (smallest == parentNdx)
            break;

        // Swap
        TrafficMovement temp = H->Elem[parentNdx];
        H->Elem[parentNdx] = H->Elem[smallest];
        H->Elem[smallest] = temp;
        parentNdx = smallest;
    }

    return minElem;
}

// Check if the heap is empty
bool isEmpty(Heap *H)
{
    return H->lastNdx == -1;
}
