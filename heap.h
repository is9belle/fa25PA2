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
        upheap(size, weightArr);
        ++size;
    }

    int pop(int weightArr[]) {
        // TODO: remove and return smallest index
        // Replace root with last element, then call downheap()
        if (size <= 0) {return -1;} //if empty, return -1

        int oldRoot = data[0]; //save root to return
        data[0] = data[size-1]; //move last to root
        downheap(0, weightArr); //restore order after switching
        --size; //decrement size, "erases" the last index
        return oldRoot;
    }

    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent
        while ((pos-1)/2 >= 0 && pos >= 0) { //check if parent exists
            if (weightArr[data[(pos-1)/2]] > weightArr[data[pos]]) { //checks if child is less than parent using the weights
                int temp = data[pos]; //switch the indices in data
                data[pos] = data[(pos-1)/2];
                data[(pos-1)/2] = temp;
                pos = (pos-1)/2;
            }
            else {
                return;
            }
        }
    }

    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
        while (pos*2+1 < size) { //while a left child exists, continue checking if parent greater than child
            int smallestChildIndex;

            if (pos*2+2 < size) { //if a right child exists, it will find the smaller of the two. otherwise, it will default to the left child.
                if (weightArr[data[pos*2+1]] < weightArr[data[pos*2+2]]) { //if left is smaller than right, set smallestChildIndex to left
                    smallestChildIndex = pos*2+1;
                }
                else {
                    smallestChildIndex = pos*2+2; //else set to right
                }
            }
            else {
                smallestChildIndex = pos*2+1;
            }

            //compare the smallest child's weight with parent's weight, if smaller then swap & check again with new children
            if (weightArr[data[smallestChildIndex]] < weightArr[data[pos]]) {
                int temp = data[pos];
                data[pos] = data[smallestChildIndex];
                data[smallestChildIndex] = temp;
                pos = smallestChildIndex;
            }
            else {
                return;
            }
        }
    }
};

#endif