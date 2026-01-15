#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// Initialize Number of Disks
int N = 0;

// Create Stacks of Rods and store them in a Vector
vector<stack<int>> rods(3);

// Assign Start (From) Rod
void assignRod(int n) {
    // Check if no disks have been assigned
    if (n == 0) {
        return;
    }
    // Place disks on the first rod (start rod)
    rods[0].push(n); 
    // Recursively add next smaller disk
    return assignRod(n-1);
}

// Print Next Move
void printMove(int disk, int p1, int p2) {
    // Use disk, first and second position as parameters to output in console
    cout << "Moving Disk " << disk << " From " << p1 << " -> " << p2 << endl;
}

// Move the disk located in the vector
void moveDisk(int a, int b) {
    // Check if destination rod is empty or top disk on source is smaller than top on destination
    if (rods[b-1].empty() || (!rods[a-1].empty() && rods[a-1].top() < rods[b-1].top())) {
        // Move top disk from source rod to destination rod assigned to function
        rods[b-1].push(rods[a-1].top()); 
        // Print disk moved and it's directions before it's popped
        printMove(rods[a-1].top(), a, b);
        // Remove disk from source rod assigned to function
        rods[a-1].pop(); 
    }  
}


// Print Hanoi Towers
void showTowers(const vector<stack<int>>& rods, int n) {
    // Create a copy of rods to avoid modifying the original stacks
    vector<stack<int>> temp_rods = rods;

    // Print each level of the rods from top to bottom
    for (int lvl = n; lvl > 0; lvl--) {
        // Loop over the length of the rod
        for (int j = 0; j < rods.size(); j++) {
            // Check if the current rod has a disk at this level
            if (temp_rods[j].size() >= lvl) {
                // Print the disk's value
                cout << temp_rods[j].top() << "  ";
                // Pop disk after printing
                temp_rods[j].pop(); 
            } else {
                // Print pipe if no disk is at this level
                cout << "|  "; 
            }
        }
        // Break line for next level
        cout << endl; 
    }
    // Break line to separate the boards
    cout << endl; 
}

void twistedhanoi(int n, int start, int mid, int end) {
    // Base case
    if (n == 1) {
        // Move disk from start rod to middle rod
        moveDisk(start, mid);
        // Update current state of the board
        showTowers(rods, N);
        // Move disk from mid rod to end rod 
        moveDisk(mid, end);
        // Update current state of the board
        showTowers(rods, N);
        // End Program
        return;
    }

    // Move n-1 disks from start to mid via end
    twistedhanoi(n-1, start, mid, end);
    // Move nth disk from start to mid
    moveDisk(start, mid);
    // Update current board state     
    showTowers(rods, N);

    // Move n-1 disks from end to mid via start
    twistedhanoi(n-1, end, mid, start);
    // Move nth disk from mid to end
    moveDisk(mid, end);
    // Update current board state
    showTowers(rods, N);

    // Move n-1 disks from start to mid via end again
    twistedhanoi(n-1, start, mid, end);
}

int main() {

    // Take Users Input
    cout << "Enter Number of Disks: ";
    cin >> N;

    // Create Board based on user's disk number
    assignRod(N);
    // Print Current Board State
    showTowers(rods, N);
    // Start the Twisted Hanoi Program
    twistedhanoi(N, 1, 2, 3);

    return 0;
}