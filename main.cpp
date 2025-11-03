#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "heap.h"

// Global arrays for node information
const static int MAX_NODES = 64;
int weightArr[MAX_NODES];
int leftArr[MAX_NODES];
int rightArr[MAX_NODES];
char charArr[MAX_NODES];

// Function prototypes
void buildFrequencyTable(int freq[], const string& filename);
int createLeafNodes(int freq[]);
int buildEncodingTree(int nextFree);
void generateCodes(int root, string codes[]);
void encodeMessage(const string& filename, string codes[]);

int main() {
    int freq[26] = {0};

    // Step 1: Read file and count letter frequencies
    buildFrequencyTable(freq, "input.txt");

    // Step 2: Create leaf nodes for each character with nonzero frequency
    int nextFree = createLeafNodes(freq);

    // Step 3: Build encoding tree using your heap
    int root = buildEncodingTree(nextFree);

    // Step 4: Generate binary codes using an STL stack
    string codes[26];
    generateCodes(root, codes);

    // Step 5: Encode the message and print output
    encodeMessage("input.txt", codes);

    return 0;
}

/*------------------------------------------------------
    Function Definitions (Students will complete logic)
  ------------------------------------------------------*/

// Step 1: Read file and count frequencies
void buildFrequencyTable(int freq[], const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    char ch;
    while (file.get(ch)) {
        // Convert uppercase to lowercase
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';

        // Count only lowercase letters
        if (ch >= 'a' && ch <= 'z')
            freq[ch - 'a']++;
    }
    file.close();

    cout << "Frequency table built successfully.\n";
}

// Step 2: Create leaf nodes for each character
int createLeafNodes(int freq[]) {
    int nextFree = 0;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] > 0) {
            charArr[nextFree] = 'a' + i;
            weightArr[nextFree] = freq[i];
            leftArr[nextFree] = -1;
            rightArr[nextFree] = -1;
            nextFree++;
        }
    }
    cout << "Created " << nextFree << " leaf nodes.\n";
    return nextFree;
}

// Step 3: Build the encoding tree using heap operations
int buildEncodingTree(int nextFree) {
    // TODO:
    //creates minHeap object
    MinHeap *minHeap = new MinHeap();
    //leaf node indices pushed into heap
    for (int i = 0; i<nextFree; i++) {
        minHeap->push(i,weightArr);
    }

    //while size > 1, so when there is more than just the one root
    while (minHeap->size > 1) {
        int smallest1 = minHeap->pop(weightArr);
        int smallest2 = minHeap->pop(weightArr);

        //creates parent node with combines weight of two smallest
        int parent = weightArr[smallest1] + weightArr[smallest2];
        weightArr[nextFree] = parent; //sets parent weight
        leftArr[nextFree] = smallest1; //sets left child pointer w/ index
        rightArr[nextFree] = smallest2; //sets right child pointer
        charArr[nextFree] = ' '; //placeholder
        minHeap->push(nextFree, weightArr); //push next free index into the heap using weights
        nextFree++;
    }
    //returns the index of the last remaining node (root)
    return minHeap->pop(weightArr);
}

// Step 4: Use an STL stack to generate codes
void generateCodes(int root, string codes[]) {
    // TODO:
    // Use stack<pair<int, string>> to simulate DFS traversal.
    stack<pair<int, string>> codesStack;
    codesStack.push({root, ""});

    int current;
    string currentString;
    char currentChar;
    // Left edge adds '0', right edge adds '1'.
    while (!codesStack.empty()) {
        current = codesStack.top().first; //holds the current index
        currentString = codesStack.top().second; //holds the current code string
        codesStack.pop();
        if (leftArr[current] == -1 && rightArr[current] == -1) { //if it is a leaf node, record the code
            currentChar = charArr[current]; //find the currentChar using the previous array holding the characters that correspond to the index
            if (currentChar>='a' && currentChar<='z') {
                codes[currentChar - 'a'] = currentString; //put the code string into the corresponding codes array, not according to index b/c encode message loops through all 26 letters instead of using indexes
            }
        }
        else { //if it is not a leaf, then push to children
            if (rightArr[current] != -1) { //if it has a right child, push its index in and add 1 to count the right edge
                codesStack.push({rightArr[current], currentString+"1"});
            }
            if (leftArr[current] != -1) {
                codesStack.push({leftArr[current], currentString+"0"});
            }
        }
    }
}

// Step 5: Print table and encoded message
void encodeMessage(const string& filename, string codes[]) {
    cout << "\nCharacter : Code\n";
    for (int i = 0; i < 26; ++i) {
        if (!codes[i].empty())
            cout << char('a' + i) << " : " << codes[i] << "\n";
    }

    cout << "\nEncoded message:\n";

    ifstream file(filename);
    char ch;
    while (file.get(ch)) {
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';
        if (ch >= 'a' && ch <= 'z')
            cout << codes[ch - 'a'];
    }
    cout << "\n";
    file.close();
}