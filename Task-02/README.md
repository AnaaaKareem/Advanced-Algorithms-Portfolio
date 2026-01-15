# Task 2 - Twisted Tower of Hanoi Analysis

# **1. Task Overview and Algorithm Selection**

Task’s purpose is to design a recursive algorithm for a type of the Tower of Hanoi puzzle known as the Restrictive Tower of Hanoi or (Twisted Tower of Hanoi) in which the disks must be moved from the starting peg (A) to the ending peg (C) through the middle/auxiliary peg (B) applying this rule wither the movement is done from beginning peg (A) to ending ped (C) or ending peg (C) to beginning peg (A) respectively while applying the standard hanoi tower rule of never putting a larger disk on top of a smaller disk. The goal is to develop an algorithm that counts the number of moves it takes to solve the problem, and visualize process.

# **2. The Restricted (Twisted) Hanoi Algorithm vs. Standard Hanoi**

**Standard Tower of Hanoi Algorithm:**

1. Move **$n-1$** disks from A to B.
2. Move the largest disk **$n$** from A to C.
3. Move **$n-1$** disks from B to C.
4. Repeat previous steps until all pegs are moved from the start to the end pegs.

**Restricted Tower of Hanoi Algorithm:**
The restriction means that all disks moving from starting peg (A) to ending peg (C) and from ending peg (C) to starting peg (A) cannot be done unless they pass through the middle/auxiliary peg (B).

1. Move **$n-1$** disks from A to C (passing through B as intermediate)
2. Move **$n$** disks from A to B
3. Move **$n-1$** disks from C to A (passing through B as intermediate)
4. Move disk $n$ from B to C
5. Move $n-1$ disks from A to C (passing through B as intermediate)
6. Repeat previous steps until all pegs are moved from the start to the end pegs always passing through the middle/auxiliary peg.

# **3. Code & Detailed Explanation**

```cpp
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
```

```cpp
// Print Next Move
void printMove(int disk, int p1, int p2) {
    // Use disk, first and second position as parameters to output in console
    cout << "Moving Disk " << disk << " From " << p1 << " -> " << p2 << endl;
}
```

```cpp
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
```

```cpp
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
```

```cpp
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
```

```cpp
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
```

# **4. Iterative vs. Recursive Complexity Analysis**

The implementation provided is **recursive**. An iterative solution could also be designed, though it would be less attractive.

**How does complexity differ?**

Both methods don’t have much of a difference in both time and space complexity.

1. **Time Complexity:** $O(3^n)$ is the Big O time complexity for this solution is where n represents number of disks and three representing the number of movements that have to be done for each disk regardless of implementation types being used.
2. **Space Complexity:** A recursive implementation require the steps to be saved and used for the next function call. Meaning that each function is added to a call stack for each disk that require space in the memory growing linearly with the number of disks ergo, making the space complexity of this algorithm $O(n)$. Similarly, for an iterative solution it requires a multiple stacks and each disk is stored somewhere in these stacks in all times, it follows the same linearity as the recursive implementation. Hence, the space complexity remains the same $O(n)$.
