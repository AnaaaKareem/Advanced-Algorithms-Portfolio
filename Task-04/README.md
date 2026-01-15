# Task 4 - Anagrams

# **1. Task Overview and Algorithm Selection**

The purpose of this task is to discuss a solution used to solve the anagram problem. Anagrams are two different word which share similar letters or characters but ordered differently for example, “Listen” and “Silent”. This implementation utilizes insertion sort to sort the two words and check if they are anagrams by checking both strings at the same time after they have been sorted.

# **2. Code & Detailed Explanation**

```cpp
// Sort string function
void sortString(string &s) {
    // Pass Through Characters Based on the String's Length
    for (int i = 0; i < s.length(); i++) { 
        // Compare Character With The Next Character
        for (int j = 0; j < s.length() - 1 - i; j++) { 
            // If Current Character is bigger than the next character Perform A Swap Operation
            if (s[j] > s[j+1]) {
                // Swap Characters
                int temp = s[j]; 
                s[j] = s[j+1];
                s[j+1] = temp;
            }
        }
    }
}
```

```cpp
// Anagrams function
bool anagrams(string &word1, string &word2) {

    // Check if both words have equal lengths 
    if (word1.length() != word2.length()) {
        return false;
    }

    // Sort both words
    sortString(word1);
    sortString(word2);

    // Return if the words are an anagram
    return word1 == word2;
}
```

```cpp
int main() {

    // Initialize word variables
    string word1, word2, w1, w2;

    // Take user's first word
    cout << "Enter first word: ";
    cin >> word1;
    w1 = word1;

    // Take user's second word
    cout << "Enter second word: ";
    cin >> word2;
    w2 = word2;

    // Check if the two words are anagrams and print to the user the message
    if (anagrams(word1, word2)) {
        cout << w1 << " and " << w2 << " are anagrams!";
    } else {
        cout << w1 << " and " << w2 << " are not anagrams!";
    }

    return 0;
}
```

# **3. Complexity Analysis**

This implementation uses an iterative approach as it is easier to use in character manipulation in strings. A recursive approach would take up $O(n)$ space complexity.

1. **Time Complexity:** $O(n^2)$ is the Big O time complexity for this solution were n represents the length of the word.
2. **Space Complexity:** $O(1)$ is the Big O space complexity for this solution as string modifications are done in place.
