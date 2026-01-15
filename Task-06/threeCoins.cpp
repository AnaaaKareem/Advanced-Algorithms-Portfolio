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

// Function to compare the weights of two coins
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

// Function to detect if the fake coin is heavier or lighter by using three coins
Scale detectFakeCoin(int first, int second, int third) {

    // Weigh the first and second coins
    Scale weight = weigh(first, second);

    // Check if the first and second coins are equal
    if (weight == EQUAL) {
        // Weigh the third coin against the first
        weight = weigh(third, first);
        // Check if third is heavier
        if (weight == HEAVIER) {
            return HEAVIER;
        // Check if third is lighter
        } else if (weight == LIGHTER) {
            return LIGHTER;
        }
    }

    // Weigh the first coin against the third
    weight = weigh(first, third);

    // Check if the first and third coins are equal
    if (weight == EQUAL) {
        // Weigh the second coin against the first
        weight = weigh(second, first);

        // Check if second is heavier
        if (weight == HEAVIER) {
            return HEAVIER;
        // Check if second is lighter
        } else if (weight == LIGHTER) {
            return LIGHTER;
        }
    } else {
        // Return the original weighings of the first and second coins (The first coin is the fake one)
        return weight;
    }
}

int main() {

    // Seed the random number generator
    srand(time(0));

    // Initialize an array for three coins
    int coins[3];

    // Generate a random weight for the real coins
    int randomCoinWeight = rand() % 11;

    // Set all coins to the real coin weight
    coins[0] = randomCoinWeight;
    coins[1] = randomCoinWeight;
    coins[2] = randomCoinWeight;

    // Select a random index for the fake coin
    int fakeIndex = rand() % 3;
    // Randomly decide if fake is heavier or lighter
    int fakeWeight = rand() % 2;

    // Check if fake coin should be lighter
    if (fakeWeight == 0) {
        // Decrease the weight of the fake coin
        coins[fakeIndex] -= 1 + rand() % 5;
      // Check if the fake coin should be heavier
    } else if (fakeWeight == 1) {
        // Increase the weight of the fake coin
        coins[fakeIndex] += 1 + rand() % 5;
    }
    
    // Print the weights of the coins (For testing purposes)
    cout << coins[0] << " " << coins[1] << " " << coins[2] << " " << endl;

    // Get the result of weighing the three coins
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