#include <iostream>
using namespace std;

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