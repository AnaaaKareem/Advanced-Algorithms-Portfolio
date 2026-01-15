# Task 3 - Word Autocomplete

# **1. Task Overview and Algorithm Selection**

The purpose of this task is to build a simple word autocomplete that suggests words from a predefined set of words found a dictionary text file used to load an AVL tree which is an auto balancing tree. The program should take users input in form of letter and on each letter a list of words is suggested from the words stored in the tree. The algorithm should also stop searching for more words in the tree if words to longer match the initial characters of the strings.

# **2. Code & Detailed Explanation**

```cpp
// Node class represents each element of the dictionary tree
class Node {
    public:
        // Word in dictionary
        string value;
        // Pointer to left leaf
        Node* left;
        // Pointer to right leaf
        Node* right;
        // Node Height
        int height;

    // Constructor to initialize tree
    Node(string val) : value(val), left(nullptr), right(nullptr), height(1) {}
};
```

```cpp
// AVL class Initialization
class AVL {
    public:
        // Initialize root node
        Node* root;

    // Initialize a constructor with root node to null
    AVL() {
        root = nullptr;
    }

    ~AVL() {
        deleteTree(root);
    }

    // Return node height
    int height(Node *node) {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }

    // Right Rotation Function
    Node* rightRotate(Node* root) {
        // Left leaf of the root
        Node* x = root->left;
        // Right leaf of left leaf
        Node* y = x->right;

        // Right leaf of left points to the root
        x->right = root;
        // Left leaf points to it's right leaf
        root->left = y;

        // Update heights after rotation
        root->height = 1 + max(height(root->left), height(root->right));
        x->height = 1 + max(height(x->left), height(x->right));

        // Return corrected node
        return x;
    }

    // Left Rotation Function
    Node* leftRotate(Node* root) {
        // Right leaf of the root
        Node* x = root->right;
        // Left leaf of right leaf
        Node* y = x->left;

        // Left leaf of right points to the root
        x->left = root;
        // Right leaf of left points to the root
        root->right = y;

        // Update heights after rotation
        root->height = 1 + max(height(root->left), height(root->right));
        x->height = 1 + max(height(x->left), height(x->right));

        // Return corrected node
        return x;
    }

    // Calculate balance factor
    int getBalance(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return height(node->left) - height(node->right);
    }

    // Insert value into tree
    Node* insert(Node* node, string value) {

        // Check if node is null to point to the node directly
        if (node == nullptr) {
            return new Node(value);
        }

        // Check of the value smaller than the parent
        if (value < node->value) {
            // Add node to the left of the parent
            node->left = insert(node->left, value);
            // Check of the value bigger than the parent
        } else if (value > node->value) {
            // Add node to the right of the parent
            node->right = insert(node->right, value);
        } else {
            // Add node directly to tree
            return node;
        }

        // Update tree height
        node->height = 1 + max(height(node->left), height(node->right));

        // Check tree balance
        int balance = getBalance(node);

        // If left branch is bigger than right branch and value is smaller 
        // than the value of the left node. (Left Left Imbalance)
        if (balance > 1 && value < node->left->value) {
          // Perform a right rotation
            return rightRotate(node);
        }

        // If right branch is bigger than left branch and value is bigger
        // than the value of the right node. (Right Right Imbalance)
        if (balance < -1 && value > node->right->value) {
          // Perform a left rotation
            return leftRotate(node);
        }

        // If left branch is bigger than right branch and value is bigger
        // than the value of the left node. (Left Right Imbalance)
        if (balance > 1 && value > node->left->value) {
          // Perform a left rotation
            node->left = leftRotate(node->left);
            // Perform a right rotation
            return rightRotate(node);
        }

        // If right branch is bigger than left branch and value is smaller
        // than the value of the right node. (Right Left Imbalance)
        if (balance < -1 && value < node->right->value) {
          // Perform a right rotation
            node->right = rightRotate(node->right);
            // Perform a left rotation
            return leftRotate(node);
        }

        // No imbalance Case
        return node;
    }

    // Wrapper insert function
    void insert(string value) {
        root = insert(root, value);
    }

    // traverseTree with prefix checking
    void traverseTree(Node* node, string& p) {
        // If tree is empty don't search
        if (node == nullptr) {
            return;
        }
        
        // Initialize a match prefix variable and set it to true
        bool match = true;
        // Check if the typed text length is smaller or equal to value found in nodes
        if (node->value.length() >= p.length()) {
            // Iterate over the characters of the typed string and word in node
            for (int i = 0; i < p.length(); i++) {
                // Check if there exists a character mismatch
                if (p[i] != node->value[i]) {
                    // set match to false and stop iteration
                    match = false;
                    break;
                }
            }
            // Print all possible matches if found
            if (match) {
                cout << node->value << endl;
            }
        }
        
        // If the current prefix is smaller than the current node's value traverse right
        if (p < node->value) {
            traverseTree(node->left, p);
        }
        
        // If the current prefix is bigger than the current node's value traverse left
        if (p > node->value || match) {
            traverseTree(node->right, p);
        }
    }

    // Find prefix function
    void find_all_with_prefix(string prefix) {
        // Check if the tree is empty or if no string has been entered
        if (prefix.length() == 0 || root == nullptr) {
            return;
        }
        // Traverse tree from root to find all prefixes
        traverseTree(root, prefix);
        cout << endl;
    }

    // Delete Tree
    void deleteTree(Node* node) {
        if (node == nullptr) {
            return;
        }
        // Traverse to the right leaf
        deleteTree(node->right);
        // Traverse to the left leaf
        deleteTree(node->left);
        // Delete node
        delete node;
        node = nullptr;
    }
};
```

```cpp
int main() {

    // Initialize an AVL tree dictionary
    AVL dictionary;

    // Load file containing the list of words
    ifstream file("dictionary.txt");
    // Initialize word variable
    string word;
    // Initialize line variable to load words from text file
    string line;

    // Check if file is open
    if (file.is_open()) {
        // Iterate over the text document to find words line by line
        while (getline(file, line)) {
            // Insert words to tree
            dictionary.insert(line);
        }
        // Close File
        file.close();
    } else {
        // Print error message and end the program
        cout << "Unable to find or open file" << endl;
        return -1;
    }

    // Prompt user to start typing
    cout << "Search: " << endl;

    // Start auto complete progran
    while (true) {
        // Check for input
        if (_kbhit()) {
            // Clear console/terminal
            system("cls");

            // Get character input
            char c = _getch(); 

            // Check for enter key to list words found and end program
            if (c == 13) {
                cout << "Search: " << word << endl << endl;
                cout << "Words Found: " << endl;
                dictionary.find_all_with_prefix(word);
                break;
            }

            // Check for escape key to end the program
            if (c == 27) {
                system("cls");
                break;
            }

            // Check for backspace key and if word is not empty
            if (c == 8 && !word.empty()) {
                // Remove last character inserted
                word.pop_back();
            }
            // Only add character to word if it is alphabetical
            else if (isalpha(c)) {
                // Add character to word
                word += c;
            }

            // Print live word typing
            cout << "Search: " << word << endl << endl;

            // Check if the user typed characters
            if (!word.empty()) {
                // Output all words that matched the prefix entered by the user
                cout << "Words Found: " << endl;
                dictionary.find_all_with_prefix(word);
            }
            cout << endl;
        }
    }

    return 0;
}
```

# **3. Time and Space Complexity**

The self-balancing of the AVL tree is the main factor for having a node search in tree being $O(logn)$. Due to keeping the height of both the left and right branches from every node balanced (within a difference of one). However, For our implementation the time complexity for searching would be $O(p*logn)$ in which n represents the number of node, and p represents the number of characters in the prefix to be searched since a for loop is required to check if character of the prefix and word in each node. While the Space Complexity would be $O(h)$ since the traversing of the tree requires a recursive algorithm to explore each node were h represents the height of the AVL tree.
