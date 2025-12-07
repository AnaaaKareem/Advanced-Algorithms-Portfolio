#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// Item Structure
struct Item {
    // Item name
    string name;
    // Item Price
    int price;
    // Item Value
    int value;
};

// Print Result using items, costs and scores gained from the shop optimizer function
void printResults(vector<Item>& items, int totalPrice, int totalValue) {
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

// Initialize a function to sort items in descending order
bool desc(const Item& a, const Item& b) {
    // Calculate the value per price for the first item
    double r1 = (double)a.value / a.price;
    // Calculate the value per price for the second item
    double r2 = (double)b.value / b.price;
    // Return higher ratio item
    return r1 > r2;
}

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
            totalPrice  += items[i].price;
            // Update total value
            totalValue += items[i].value;
        }
    }

    // Print final results using the selected items, total price and value
    printResults(selectedItems, totalPrice, totalValue);
}

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