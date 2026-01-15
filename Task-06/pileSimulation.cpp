#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Initialize an enum for scale values
enum Scale {
    EQUAL,
    LIGHTER,
    HEAVIER
};

// Function to compare the weights of two piles of coins
Scale weigh(int first, int second) {
    // Check if weights are equal
    if (first == second) {
        return EQUAL;
    // Check if first is heavier
    } else if (first > second) {
        return HEAVIER;
    // Check if first is lighter
    } else if (first < second) {
        return LIGHTER;
    }
}

// Function to detect if the pile containing the fake coin is heavier or lighter by using three piles
Scale detectFakeCoin(int first, int second, int third) {

    // Weigh the first and second piles
    Scale weight = weigh(first, second);

    // Check if the first and second piles are equal
    if (weight == EQUAL) {
        // Weigh the third pile against the first
        weight = weigh(third, first);
        // Check if third is heavier
        if (weight == HEAVIER) {
            return HEAVIER;
        // Check if third is lighter
        } else if (weight == LIGHTER) {
            return LIGHTER;
        }
    }

    // Weigh the first pile against the third
    weight = weigh(first, third);

    // Check if the first and third piles are equal
    if (weight == EQUAL) {
        // Weigh the second pile against the first
        weight = weigh(second, first);

        // Check if second is heavier
        if (weight == HEAVIER) {
            return HEAVIER;
        // Check if second is lighter
        } else if (weight == LIGHTER) {
            return LIGHTER;
        }
    } else {
        // Return the original weighings of the first and second pile of coins (The first pile contains the fake coin)
        return weight;
    }
}

int main() {

    // Seed the random number generator
    srand(time(0));

    // Initialize an array for three piles
    int coins[3];

    // Initialize a variable for the number of coins per pile
    int numOfCoins = 0;

    // Capture the number of coins per pile from user's input
    cout << "Enter the number of coins per pile: ";
    cin >> numOfCoins;

    // Check if there are enough coins
    if (numOfCoins <= 0) {
        // Print error message
        cout << "Need at least 1 coin." << endl;
        // Exit program with error code
        return 1;
    }

    // Generate a random weight for a coin
    int randomCoinWeight = rand() % 11;
    // Calculate the total weight for a pile of real coins
    int randomPile = randomCoinWeight * numOfCoins;

    // Set all piles to the calculated real weight
    coins[0] = randomPile;
    coins[1] = randomPile;
    coins[2] = randomPile;

    // Select a random index for the fake pile
    int fakeIndex = rand() % 3;
    // Randomly decide if fake is heavier or lighter
    int fakeWeight = rand() % 2;

    // Check if fake pile should be lighter
    if (fakeWeight == 0) {
        // Decrease the weight of the fake pile
        coins[fakeIndex] -= 1 + rand() % 5;
      // Check if the fake pile should be heavier
    } else if (fakeWeight == 1) {
        // Increase the weight of the fake pile
        coins[fakeIndex] += 1 + rand() % 5;
    }
    
    // Print the weights of the three piles (For testing purposes)
    cout << coins[0] << " " << coins[1] << " " << coins[2] << " " << endl;

    // Get the result of weighing the three piles
    Scale result = detectFakeCoin(coins[0], coins[1], coins[2]);

    // Check if the result is heavier
    if (result == HEAVIER) {
        cout << "Fake coin is Heavier" << endl;
    } 
    // Check if the result is lighter
    else if (result == LIGHTER) {
        cout << "Fake coin is Lighter" << endl;
    }

    return 0;
}