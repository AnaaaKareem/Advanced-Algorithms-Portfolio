#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

// Initialize an enum for scale values
enum Scale {
    EQUAL,
    LIGHTER,
    HEAVIER
};

// Function to calculate the total weight of a specific range of coins in a vector
int getPileWeight(vector<int> coins, int left, int right) {
    // Initialize total weight counter
    int totalWeight = 0;
    // Iterate through the full pile till a specific range
    for (int i = left; i < right; i++) {
        // Add current coin's weight to total
        totalWeight += coins[i];
    }
    // Return the total weight
    return totalWeight;
}

// Function to compare the weights of two piles of coins
Scale weigh(int firstPile, int secondPile) {
    // Check if both piles have equal weight
    if (firstPile == secondPile) {
        return EQUAL;
    // Check if the first pile is heavier
    } else if (firstPile > secondPile) {
        return HEAVIER;
    // Default to first pile being lighter
    } else {
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

    // Initialize variable for total number of coins
    int num;

    // Capture the number of coins per pile from user's input
    cout << "Enter total number of coins: ";
    cin >> num;

    // Check if there are enough coins
    if (num < 3) {
        // Print error message
        cout << "Need at least 3 coins." << endl;
        // Exit program with error code
        return 1;
    }

    // Initialize coin weight
    int baseWeight = 10;
    // Initialize vector with the coin weight with the number coins in the vector
    vector<int> coins(num, baseWeight);

    // Select a random index for the fake coin
    int fakeIndex = rand() % num;
    // Randomly decide if fake is heavier or lighter
    int fakeWeight = rand() % 2;

    // Check if fake pile should be lighter
    if (fakeWeight == 0) {
        // Increase weight of the fake coin
        coins[fakeIndex] += (1 + rand() % 5);
      // Check if the fake pile should be heavier
    } else if (fakeWeight == 1) {
        // Decrease weight of the fake coin
        coins[fakeIndex] -= (1 + rand() % 5);
    }

    // Calculate size of each of pile
    int pileSize = num / 3;
    // Calculate remainder
    int remainderCount = num % 3;
    
    // Calculate weight of the first pile
    int p1_weight = getPileWeight(coins, 0, pileSize);
    
    // Calculate weight of the second pile
    int p2_weight = getPileWeight(coins, pileSize, pileSize * 2);
    
    // Calculate weight of the third pile
    int p3_weight = getPileWeight(coins, pileSize * 2, pileSize * 3);

    // Print the weights of the three piles (For testing purposes)
    cout << "Pile Sums: " << p1_weight << " " << p2_weight << " " << p3_weight << endl;

    // Get the result of weighing the three piles
    Scale result = detectFakeCoin(p1_weight, p2_weight, p3_weight);

    // Check if the result is heavier
    if (result == HEAVIER) {
        cout << "Fake coin is Heavier" << endl;
    } 
    // Check if the result indicates a lighter pile
    else if (result == LIGHTER) {
        cout << "Fake coin is Lighter" << endl;
      // The fake coin is in the remainder and not the original three piles
    } else {
        // Check if there are remainder coins to test
        if (remainderCount > 0) {

            // Calculate weight of the remainder pile 
            int remainderWeight = getPileWeight(coins, pileSize * 3, num);
            
            // Calculate a sample weight of the safe coins
            int safeCoinsWeight = getPileWeight(coins, 0, remainderCount);

            // Weigh both the safe coins pile and the remainder pile to determine the weight of the fake coin
            Scale remainderResult = weigh(remainderWeight, safeCoinsWeight);

            // Check if remainder is heavier
            if (remainderResult == HEAVIER) {
                cout << "Fake coin is Heavier" << endl;
            // Check if remainder is lighter
            } else if (remainderResult == LIGHTER) {
                cout << "Fake coin is Lighter" << endl;
            }
        }
    }

    return 0;
}