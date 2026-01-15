# Task 7 - Shop Optimizer

# **1. Task Overview**

The purpose of this task is to create a shopping optimizer that works by maximizing the profit by setting a budget of an item count, a classic knapsack problem that can be solved using two methods. Firstly, Dynamic Programming or the 0/1 Knapsack which picks a certain count of items within a certain budget to maximize value for profit. Second, the Greedy Approach or the Fractional Knapsack in which the item’s value to weight ratio is calculated, sorted in descending order, and fills the knapsack from the biggest value per weight items until full were taking a fraction of the last item if needed. This report investigates both approaches.

# **2. Code & Detailed Explanation**

## Item Structure

```cpp
struct Item {
    // Item name
    string name;
    // Item Price
    int price;
    // Item Value
    int value;
};
```

## Print Results

```cpp
// Print Result using items, costs and scores gained from the shop optimizer function
void printResults(vector<Item> items, int totalPrice, int totalValue) {
    // Check it any items exist
    if (items.size() == 0) {
        // Print no items picked
        cout << "No items picked" << endl;
    } else {
        cout << "Items Picked: " << endl;
        // Go through each item and print it's details
        for (int i = 0; i < items.size(); i++) {
            cout << "Item #" << i+1 << ": " << items[i].name 
            << ", Price: $" << items[i].price 
            << ", Rating: " << items[i].value << endl << endl;
        }
    }

    // Print total price and value gained
    cout << "Total Price: $" << totalPrice << endl;
    cout << "Total Value Gained: " << totalValue << endl;
}
```

## Dynamic Programming Shop Optimizer

```cpp
// Initialize Dynamic Programming Shop Optimizer
void DPShopOptimizer(int budget, vector<Item>& items) {

    // Initialize knapsack table using the number of items and the user's budget, each cell being initialized to zero
    vector<vector<int>> dp(items.size() + 1, vector<int>(budget + 1, 0));

    // Iterate over the number of items
    for (int i = 1; i <= items.size(); i++) {
        // Iterate over multiple budgets
        for (int b = 0; b <= budget; b++) {
            // Record the current price and value
            int price = items[i - 1].price;
            int value = items[i - 1].value;

            // Check if the price of the current items does not exceed the budget
            if (price <= b) {
                // Select the maximum value between including the current item or keeping the previous
                dp[i][b] = max(value + dp[i - 1][b - price], dp[i - 1][b]);
            } else {
                // We have reached maximum budget, exclude current items
                dp[i][b] = dp[i - 1][b];
            }
        }
    }

    // Initialize a vector for selected items
    vector<Item> selectedItems;

    // Initialize a copy budget variable to keep track of budget while picking selected items
    int b = budget;
    // Initialize total price variable to keep track of items prices
    int totalPrice = 0;
    // Initialize total value using the dp table after calculations
    int totalValue = dp[items.size()][budget];

    // Iterate backwards from the last item to the first to reconstruct the solution
    for (int i = items.size(); i > 0; i--) {
        if (dp[i][b] != dp[i - 1][b]) {
            // Add the item to the list of selected items
            selectedItems.push_back(items[i - 1]);
            // Update the total price
            totalPrice += items[i - 1].price;
            // Decrease budget by price of the selected item
            b = b - items[i - 1].price;
        }
    }

    // Print final results using the selected items, total price and value
    printResults(selectedItems, totalPrice, totalValue);
}
```

## Descending Function

```cpp
// Initialize a function to sort items in descending order
bool desc(const Item& a, const Item& b) {
    // Calculate the value per price for the first item
    double r1 = (double)a.value / a.price;
    // Calculate the value per price for the second item
    double r2 = (double)b.value / b.price;
    // Return higher ratio item
    return r1 > r2;
}
```

## Greedy Method Shop Optimizer

```cpp
// Initialize Greedy Shop Optimizer
void greedyShopOptimizer(int budget, vector<Item>& items) {
    // Sort items using the desc function
    sort(items.begin(), items.end(), desc);

    // Initialize vector to store the selected items
    vector<Item> selectedItems;

    // Initialize a variable to track current spending
    int totalPrice = 0;
    // Initialize a variable to track total value gained
    int totalValue = 0;

    // Iterate through the sorted items
    for (int i = 0; i < items.size(); i++) {
        // Check if the current item's price fits within the remaining budget
        if (totalPrice + items[i].price <= budget) {
            // Add the item to the list of selected items
            selectedItems.push_back(items[i]);
            
            // Update the current spending
            totalPrice += items[i].price;
            // Update total value
            totalValue += items[i].value;
        }
    }

    // Print final results using the selected items, total price and value
    printResults(selectedItems, totalPrice, totalValue);
}
```

## Main

```cpp
int main() {
    // Declare variables for budget and number of items
    int budget, nItems;

    // Prompt user for shopping budget and read input
    cout << "Enter Shopping Budget: ";
    cin >> budget;

    // Prompt user for number of items and read input
    cout << "Number of Items Picked ";
    cin >> nItems;

    // Clear input buffer before reading item's name
    cin.ignore();

    // Initialize a vector to store the store items
    vector<Item> storeItems(nItems);

    for (int i = 0; i < nItems; i++) {

        // Prompt user to input item's name
        cout << "\nItem #" << (i + 1) << " Name: ";
        getline(cin, storeItems[i].name);

        // Prompt user to input item's price and value
        cout << " Price & Value: ";
        cin >> storeItems[i].price >> storeItems[i].value;

        // Clear input buffer
        cin.ignore();
    }

    // Print Dynammic Programming Optimizer Results
    cout << endl << "------------------------------------" << endl;
    cout << "Dynamic Programming Shop Optimizer" << endl;
    cout << "------------------------------------" << endl;
    // Utilize the DPShopOptimizer to solve and print results
    DPShopOptimizer(budget, storeItems);

    // Print Greedy Optimizer Results
    cout << endl << "------------------------------------" << endl;
    cout << "Greedy Shop Optimizer" << endl;
    cout << "------------------------------------" << endl;
    // Utilize the greedyShopOptimizer to solve and print results
    greedyShopOptimizer(budget, storeItems);

    return 0;
}
```

# **3. Time and Space Complexity**

We have to take into consideration to types of inputs before the time complexity and auxiliary space are calculated.

$N$ = Number of items

$W$ = The maximum weight allowed. In this instance it is the budget

## Dynamic Programming Approach

1. **Time Complexity:** $O(N \times W)$ Since the computation is done for every item through every possible budget.
2. **Space Complexity:** $O(N \times W)$ The vector in the program always stores the value of every possible item to weight computation hence it remain always at this complexity.

## Greedy Approach

1. **Time Complexity:** $O(N \log N)$ Since the greedy approach requires the sort() function it runs in $N \log N$. The main greedy function runs in $O(N)$
2. **Space Complexity:** $O(N)$ Due to the vector that store all $N$ items.

## Efficiency and Use Cases

### Dynamic Programming Approach

From the complexity analysis this approach is the least efficient and the most computationally expensive approach to tackle such problems however, It gives the most accurate item list possible. This method is better utilized with low weight (budget) and low number of items or if the most accurate result needed is a requirement.

### Greedy Approach

This approach is the most efficient and is less computationally expensive than the Dynamic Programming approach however, It gives the least accurate item list possible. This method is better utilized with high weight (budget) and high number of items or when approximated results are allowed.
