# Task 8 - Ball Sorting Game

# **1. Task Overview**

The purpose of this task is to design a solver for the well-known Ball Sorting Game, a puzzle in which coloured balls are arranged across multiple stacks and must be reorganized such that every stack contains balls of only one colour. The user inputs total number of stacks, the number of balls in each stack, the number of colours, and the number of initially empty stacks. Then, The puzzle gets solved using Depth First Search to generate a sequence of moves to solve the puzzle.

# **2. Code & Detailed Explanation**

## Grid Initialization

```cpp
using Grid = vector<vector<string>>;

// Converts an array of tubes into a Grid
Grid configureGrid(vector<string> tubes[], int numberOfTubes) {
    // Initialize a Grid object to store tubes
    Grid grid;

    // Iterate through the total number of tubes provided
    for (int i = 0; i < numberOfTubes; i++) {
        // Add the current tube from the array to the grid
        grid.push_back(tubes[i]);
    }

    // Return the final configured grid
    return grid;
}
```

## Get Maximum Height

```cpp
// Get the maximum height (number of items) in the series of tubes
int getMaxHeight(Grid grid) {
    // Initialize the max variable
    int maxHeight = 0;
    // Go over every tube in the grid
    for (int i = 0; i < grid.size(); i++) {
        // Check if the height (number of items) in the current tube is larger than maximum stored
        if (maxHeight < grid[i].size()) {
            // Update max height
            maxHeight = grid[i].size();
        }
    }
    // Return maximum height
    return maxHeight;
}
```

## Stack to String

```cpp
// Initialize a function to convert items in the tube to a string 
string stackToString(vector<string> tube) {
    // Initialize a string variable to store the colour sequence
    string result = "";

    // Iterate through each element in the tube vector
    for (int i = 0; i < tube.size(); i++) {
        // Append the current item to the result string
        result += tube[i] + ",";
    }

    // Return the final string representation of the tube
    return result;
}
```

## Generate Grid State

```cpp
// Initialize a function to generate grid state
string generateGridState(Grid grid) {
    // Initialize a final string variable that will store the whole grid representation
    string finalString;

    // Sort the grid vectors to ensure identical states produce the same string regardless of tube order
    sort(grid.begin(), grid.end());

    // Iterate over every tube in the grid
    for (int i = 0; i < grid.size(); i++) {
        // Convert the current tube to a string using the helper function
        finalString += (stackToString(grid[i]) + ";");
    }

    // Return grid state
    return finalString;
}
```

## Is Grid Solved

```cpp
// Initialize a function to check whether the puzzle is solved
bool isSolved(Grid grid, int stackHeight) {
    // Iterate over every tube in the grid
    for (int i = 0; i < grid.size(); i++) {

        // Check if the current tube is empty
        if (grid[i].empty()) {
            // Skip to the next iteration if the tube is empty
            continue;
        }

        // Check if the current tube contains the required number of balls
        if (grid[i].size() != stackHeight) {
            // Return false if the tube is not completely full
            return false;
        }

        // Initialize a variable to store the colour of the first ball as a reference
        string colour = grid[i][0];

        // Iterate through all the balls in the current tube
        for (int j = 0; j < grid[i].size(); j++) {
            // Check if the current ball matches the reference colour
            if (grid[i][j] != colour) {
                // Return false if a mismatch is found
                return false;
            }
        }
    }
    
    // Return true as all tubes satisfy the solving conditions
    return true;
}
```

## Is Tube Uniform

```cpp
// Initialize a function to check if all balls in a given tube have the same colour
bool isTubeUniform(vector<string> tube) {
    // Check if the tube is empty
    if (tube.empty()) {
        // Return true as an empty tube is considered uniform
        return true;
    }

    // Initialize a variable to store the colour of the first ball as a reference
    string colour = tube[0];

    // Iterate through all the balls in the tube
    for (int i = 0; i < tube.size(); i++) {
        // Check if the current ball matches the reference colour
        if (tube[i] != colour) {
            // Return false if a mismatch is found
            return false;
        }
    }

    // Return true if all balls had the same colour
    return true;
}
```

## Is Valid Move

```cpp
// Initialize a function to check move validity from source to destination tubes
bool isValidMove(vector<string> sourceTube, vector<string> destinationTube, int height) {

    // Check if the source tube is empty or if the destination tube has reached max height
    if (sourceTube.empty() or destinationTube.size() == height) {
        // Return false indicating an Invalid Move
        return false;
    }

    // Check if the source tube is full and contains uniform balls
    if (sourceTube.size() == height and isTubeUniform(sourceTube)) {
        // Return false since tube is already solved
        return false;
    }

    // Check if the destination tube is currently empty
    if (destinationTube.empty()) {
        // Check if the source tube contains a uniform stack of balls
        if (isTubeUniform(sourceTube)) {
            // Return false to avoid moving a uniform stack into an empty tube
            return false;
        }
        // Return true indicating a Valid Move
        return true;
    }

    // Compare the top ball of the source tube with the top ball of the destination tube
    return (sourceTube[sourceTube.size() - 1] == destinationTube[destinationTube.size() - 1]);
}
```

## Solve Puzzle (DFS)

```cpp
// Initialize a function to solve the puzzle using DFS search with pruning
bool solvePuzzle(Grid& grid, int stackHeight, unordered_set<string>& visited, vector<vector<int>>& answerMod) {
    // Generate grid state
    string state = generateGridState(grid);

    // Check if the current state has already been visited
    if (visited.count(state)) {
        // Return false to prune this branch and avoid infinite loops
        return false;
    }

    // Mark the current state as visited by inserting it into the set
    visited.insert(state);

    // Check if the puzzle is solved in the current state
    if (isSolved(grid, stackHeight)) {
        // Return true indicating a solution has been found
        return true;
    } 

    // Iterate through all tubes to select a source tube
    for (int i = 0; i < grid.size(); i++) {
        // Check if the current source tube is empty
        if (grid[i].empty()) {
            // Skip to the next iteration if the source tube has no balls
            continue;
        }

        // Iterate through all tubes to select a destination tube
        for (int j = 0; j < grid.size(); j++) {
            // Check if the source and destination tubes are the same
            if (i == j) {
                // Skip self-moves
                continue;
            } 

            // Check if moving a ball from the source tube to the destination tube is valid
            if (isValidMove(grid[i], grid[j], stackHeight)) {
                
                // Retrieve the top ball from the source tube
                string ball = grid[i].back(); 
                // Remove the ball from the source tube
                grid[i].pop_back();
                // Add the ball to the destination tube
                grid[j].push_back(ball);

                // Recursively call the solvePuzzle function to explore the next state
                if (solvePuzzle(grid, stackHeight, visited, answerMod)) {
                    
                    // Check if the answer vector is not empty and if the previous move is identical to the current one
                    if (!answerMod.empty() && answerMod.back()[0] == i && answerMod.back()[1] == j) {
                        // Increment the ball count for the previous move instead of creating a new entry
                        answerMod.back()[2]++;
                    } else {
                        // Otherwise, record the move as a new entry with a count of 1
                        answerMod.push_back({i, j, 1});
                    }
                    // Return true to continue recursion
                    return true;
                }

                // Remove the ball from the destination tube
                grid[j].pop_back();
                // Place the ball back into the source tube to restore the previous state
                grid[i].push_back(ball);
            }
        }
    }
    // Return false if no solution is found from the current state
    return false;
}
```

## Check Grid

```cpp
// Initialize a function to check whether the grid is valid before solving
bool checkGrid(Grid grid, int numEmptyTubes) {
    // Get the total number of tubes in the grid
    int numberOfTubes = grid.size();
    
    // Get the maximum height among all tubes to determine standard stack height
    int stackHeight = getMaxHeight(grid);

    // Calculate the expected total number of balls in the grid based on non-empty tubes
    int numBallsExpected = ((numberOfTubes - numEmptyTubes) * stackHeight);

    // Initialize a variable to count the actual number of balls in the grid
    int numBalls = 0;

    // Iterate through each tube in the grid to count total balls
    for (int i = 0; i < grid.size(); i++) {
        // Add the size of the current tube to the total ball count
        numBalls += grid[i].size();
    }

    // Check if the actual ball count matches the expected number
    if (numBalls != numBallsExpected) {
        // Print an error message if the ball count is incorrect
        cout << "Grid has incorrect number of balls" << endl;
        // Return false indicating the grid is invalid
        return false;
    }

    // Initialize a map to count the frequency of each ball colour
    map<string, int> ballColourFrequency;

    // Iterate through each tube in the grid to scan ball colours
    for (int i = 0; i < grid.size(); i++) {

        // Iterate through all balls in the current tube
        for (int j = 0; j < grid[i].size(); j++) {
            // Get the colour string of the current ball
            string ball = grid[i][j];

            // Check if the colour is already in the map
            if (ballColourFrequency.find(ball) != ballColourFrequency.end()) {
                // Increment the frequency count for this existing colour
                ballColourFrequency[ball] += 1;
            } else {
                // Initialize the frequency count for this new colour
                ballColourFrequency[ball] = 1;
            }
        }
    }

    // Iterate through the map to ensure each colour appears the correct number of times
    for (map<string, int>::iterator it = ballColourFrequency.begin(); it != ballColourFrequency.end(); it++) {
        // Check if the frequency of the current colour matches the stack height
        if (it->second != stackHeight) {
            // Print an error message if the colour count is mismatching
            cout << "Colour " << it->first << " is not " << stackHeight << endl;
            // Return false indicating the grid is invalid
            return false;
        }
    }

    // Return true indicating the grid is valid
    return true;
```

## Main

```cpp
int main() {
    // Declare variables for game configuration parameters and counters
    int numberOfTubes, stackHeight, numEmptyTubes, numColours;
    int totalMoves = 0;
    
    // Prompt user to enter the total number of tubes
    cout << "Enter number of tubes: ";
    cin >> numberOfTubes;

    // Prompt user to enter the height of each stack
    cout << "Enter height of each stack: ";
    cin >> stackHeight;

    // Prompt user to enter the number of unique colours
    cout << "Enter number of colours: ";
    cin >> numColours;
    
    // Prompt user to enter the number of empty tubes
    cout << "Enter number of empty tubes: ";
    cin >> numEmptyTubes;

    // Allocate an array of tubes (Grid) based on user input size
    Grid grid(numberOfTubes);
    // Calculate the number of tubes that need to be filled with input
    int filledTubes = numberOfTubes - numEmptyTubes;

    // Prompt user to enter the colours for each filled stack
    cout << "Enter the colours for each stack (from bottom to top): " << endl;
    
    // Iterate through the number of filled tubes
    for (int i = 0; i < filledTubes; i++) {
        // Prompt user for the current stack's colours
        cout << "Tube " << (i + 1) << ": ";
        // Iterate through each slot in the tube up to the maximum height
        for (int j = 0; j < stackHeight; j++) {
            // Declare a string to hold the input colour
            string colour;
            cin >> colour;
            // Push the colour into the current tube
            grid[i].push_back(colour);
        }
    }

    // Validate the grid configuration to ensure ball counts and colours are correct
    if (!checkGrid(grid, numEmptyTubes)) {
        // Print error message for invalid configuration
        cout << "Invalid Grid Configuration." << endl;
        return 1;
    }

    // Check if the puzzle is already in a solved state
    if (isSolved(grid, stackHeight)) {
        // Print message indicating the problem is already solved
        cout << "Problem is already solved" << endl;
        return 0;
    }

    // A set to keep track of visited states to avoid clashed
    unordered_set<string> visited;
    // A vector to store the solution sequence of moves
    vector<vector<int>> answerMod;

    // Solve the puzzle and store the result
    bool solved = solvePuzzle(grid, stackHeight, visited, answerMod);

    // Check if a solution was found
    if (solved) {
        // Reverse the solution vector to display moves from Start to Finish
        reverse(answerMod.begin(), answerMod.end());

        cout << endl;

        // Iterate through the solution steps
        for (int i = 0; i < answerMod.size(); i++) {
            // Print the details of each move source, destination, and number of moves 
            cout << "Move " << answerMod[i][0] + 1 << " to " << answerMod[i][1] + 1 << " " << answerMod[i][2] << " times" << endl;
            // Add the number of movements to the total moves count
            totalMoves += answerMod[i][2];
        }

        // Print the total number of moves made
        cout << endl << "Total Number of Moves Made: " << totalMoves;
    } else {
        // Print no solution found
        cout << "No solution found." << endl;
    }

    return 0;
}
```

# **3. Time and Space Complexity**

1. **Time Complexity:** $O(n!)$ Where n represents the number of tubes * heights of each tube.
2. **Space Complexity:** $O(n^2)$ Expresses all visited states.
