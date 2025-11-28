#include <iostream>
#include <vector>
using namespace std;

// Function to arrange disks using vector reference
int arrangeDisks(vector<char>& disks) {
    // Initialize moves count
    int moves = 0;
    // Initialize sort check
    bool is_sorted = false;
    // Initialize current state
    int current_state = 0;

    // Keep looping until the vector is sorted
    while (!is_sorted) {
        // Set sort checker to true 
        is_sorted = true;
        // Loop the entire vector size except last index
        for (int i = 0; i < disks.size() - 1; i++) {
            // Check if there exists a A darking disk following a light disk
            if (disks[i] == 'D' && disks[i+1] == 'L') {
                // Swap disks
                char temp = disks[i];
                disks[i] = disks[i+1];
                disks[i+1] = temp;
                // Increment moves counter
                moves++;
                // Set false checker to false meaning that the array is still not sorted
                is_sorted = false;
            }
        }
            // Print the row current arrangement
            cout << "State " << current_state << ": ";
            for (int i = 0; i < disks.size(); i++) {
                cout << disks[i] << " ";
            }
            // Add to the current state counter
            current_state += 1;
            cout << endl;
    }
    cout << endl;
    // Return number of moves
    return moves;
}

int main() {

    // Initilaize a variable for number of pairs
    int num;

    // Get the number of pairs from the user 
    cout << "Enter the number of pairs: ";
    cin >> num;

    // Initialize a vector of the number of pairs
    vector<char> disks(2 * num);

    // Fill the vector with Dark and Light disks
    for (int i = 0; i < 2 * num; i += 2) {
        disks[i] = 'D';
        disks[i+1] = 'L';
    }

    // Print the row before rearrangement
    cout << "Start State: ";
    for (int i = 0; i < disks.size(); i++) {
        cout << disks[i] << " ";
    }
    cout << endl << endl;

    // Get the number of moves from the arrange function
    int total_moves = arrangeDisks(disks);

    // Print the row after rearrangement
    cout << "Final State: ";
    for (int i = 0; i < disks.size(); i++) {
        cout << disks[i] << " ";
    }
    cout << endl;
    
    // Print number of moves
    cout << "Total Moves: " << total_moves << endl;

    return 0;
}
