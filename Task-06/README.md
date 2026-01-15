# Task 6 - The Fake Coin Problem

# **1. Task Overview and Algorithm Selection**

The purpose of this task is to invent and investigate an algorithm that determines the weight of a fake coin in a pile of genuine coins in a time complexity of $O(1)$. In the task it is assumed that the number of coins are $n>2$, were n is the number of coins. All coins “look” identical except the fake coin for this demonstration the coins are represented as integers and the value is the weight of the coin (Every element in the program including weight value for the real and fake coins including the fake coin index shall be randomly generated). The fake coin could be lighter or heavier that the rest of the coins. A two-pan balance scale is used to determine if the two piles are equal, or if the left pan is heavier or lighter than the right pan.

# 2. Investigating The Feasibility Of Such a Solution

## I. How does the solution work?

For finding the fake coins in a pile of coins, the pile must be split in three piles such that each pile is represented as $k=n/3$, where k is the divided pile and n is the full pile of coins. The weighing must be done at least twice and at most three times if the fake coin exists in a remainder pile were the first weighing determine the two piles that are equal, the second compares one of the piles that is real and the pile containing the fake coin, the third may happen in the case the pile has a remainder and the fake coin exist in that pile. Hence, This will determine if the fake coin in that pile if lighter or heavier than the $n-1$ real coins.

## II. Does there exist a solution for this problem?

If we assume that one of the solutions include an array, vector or a container data structure inside the program which uniquely identifies each coin, this already entails that an iteration element is required in the program to get the specific weight of each pile assuming that assigning the total pile beforehand is done without iteration, it is logarithmically impossible to craft such a solution so that the entire algorithm runs in $O(1)$.

## III. What solutions are theoretical possible?

The main issue to craft such a solution so that the entire algorithm runs in $O(1)$ is in the lines of summation of the coins in a “container” data structure. Hence, To circumvent this issue there are two methods.

### i. Measuring only three coins

This violates the task’s rule of the number of coins being bigger than three, locking the number of coins to be always three. Nevertheless, The time complexity of the entire algorithm and the weighing would be done in $O(1)$.

### ii. Assuming the sum of weight before the weighing

Rather than using an array or vector, the program assumes a coin weight and the number of coins in the entire pile using normal variables and pick a random pile and subtract or add a specific value onto it. Then, do the weighing to determine the weight of the fake coin. Although, This technically satisfies all the requirements of the task but this method doesn’t consider remainders as the entire pile in this method is design to be in $n\%3$ where n is the entire pile of coins. It is incredibly difficult to model a solution for this method so that the pile is not always divisible by 3 and make it deal with remainders properly.

# **3. Code & Detailed Explanation**

**Note: Some parts in the code are shared between the three implementations mentioned above hence, the sections for this report would be represented differently than previous reports**

## Shared Across the three implementations

### Scale Enum

```cpp
// Initialize an enum for scale values
enum Scale {
    EQUAL,
    LIGHTER,
    HEAVIER
};
```

### Weighing Function

```cpp
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
```

### Detect Fake Coin

```cpp
// Function to detect if the fake coin is heavier or lighter by using three coins/piles
Scale detectFakeCoin(int first, int second, int third) {

    // Weigh the first and second coins/piles
    Scale weight = weigh(first, second);

    // Check if the first and second coins/piles are equal
    if (weight == EQUAL) {
        // Weigh the third coin/pile against the first
        weight = weigh(third, first);
        // Check if third is heavier
        if (weight == HEAVIER) {
            return HEAVIER;
        // Check if third is lighter
        } else if (weight == LIGHTER) {
            return LIGHTER;
        }
    }

    // Weigh the first coin/pile against the third
    weight = weigh(first, third);

    // Check if the first and third coins/piles are equal
    if (weight == EQUAL) {
        // Weigh the second coin/pile against the first
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
```

## Three Coin Only Main Function Implementation

```cpp
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
```

## Pile Simulation Main Function Implementation

```cpp
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
```

## Get Pile Weight Vector Function

```cpp
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
```

## Vector Main Function Implementation

```cpp
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
```

# **4. Summary**

As showcased above weighing could theoretically be done in $O(1)$ time complexity however, The actual problem is gathering the coins themselves which would cost $O(n)$. The simulations proved that if these variables were precalculated or assumed before the weighing the algorithm would satisfy the time complexity requirement. The vector implementation is the most accurate as it deals with remainders better and does not have any precalculated or assumed variables.
