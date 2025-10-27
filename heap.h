//
// Created by Manju Muralidharan on 10/19/25.
//

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

struct MinHeap {
    int data[64];
    int size;

    MinHeap() { size = 0; }

    void push(int idx, int weightArr[]) {
        // TODO: insert index at end of heap, restore order using upheap()
        data[size] = idx;
        size++;
        upheap(idx, weightArr);
    }

    int pop(int weightArr[]) {
        // TODO: remove and return smallest index
        // Replace root with last element, then call downheap()
        return -1; // placeholder
    }

    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent
        while ((pos-1)/2 > 0) {
            if (weightArr[pos] < weightArr[(pos-1)/2]) { //checks if child is less than parent using the weights
                int temp = data[pos];
                data[pos] = data[(pos-1)/2];
                data[(pos-1)/2] = temp;
            }
            else {
                return;
            }
        }
    }

    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
        while (pos*2+1 > size) {
            int smallestChildIndex;
            if (weightArr[pos*2+1] < weightArr[pos*2+2]) {
                smallestChildIndex = pos*2+1;
            }
            else {
                smallestChildIndex = pos*2+2;
            }
            if (weightArr[smallestChildIndex] < weightArr[pos]) { //compare smallest child with original
                int temp = data[pos];
                data[pos] = data[pos*2+1];
                data[pos*2+1] = temp;
        }
    }
};

#endif