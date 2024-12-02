#include <iostream>
#include <string>
using namespace std;

// Node of the Suffix Tree
class SuffixTreeNode {
public:
    SuffixTreeNode *children[52];  // Array to store child nodes (for 'a' to 'z' and 'A' to 'Z')
    int start;  // Start index of the substring represented by this node
    int *end;   // End index (inclusive) of the substring represented by this node
    int suffixIndex; // Suffix index, used to mark leaf nodes

    SuffixTreeNode(int start, int *end) {
        this->start = start;
        this->end = end;
        this->suffixIndex = -1;  // Default value (not a leaf node)
        for (int i = 0; i < 52; i++) {
            children[i] = NULL; // Initialize all children as null
        }
    }
};

// Suffix Tree class
class SuffixTree {
public:
    string text;  // Input string for which suffix tree is built
    SuffixTreeNode *root;

    SuffixTree(string txt) {
        this->text = txt;
        this->root = new SuffixTreeNode(-1, new int(-1));
        buildSuffixTree();
    }

    // Helper function to build the suffix tree using brute force method
    void buildSuffixTree() {
        int n = text.length();
        // Iterate over all suffixes of the text
        for (int i = 0; i < n; i++) {
            insertSuffix(i);
        }
    }

    // Insert a suffix into the suffix tree starting at position 'i'
    void insertSuffix(int i) {
        SuffixTreeNode *currentNode = root;
        int n = text.length();
        
        // Traverse the suffix and add it to the tree
        for (int j = i; j < n; j++) {
            char currentChar = text[j];
            int index = getCharIndex(currentChar);  // Get index for both lowercase and uppercase letters

            if (currentNode->children[index] == NULL) {
                // If the character is not already a child, create a new node
                SuffixTreeNode *newNode = new SuffixTreeNode(j, new int(n - 1));
                currentNode->children[index] = newNode;
            }
            currentNode = currentNode->children[index];
        }
        // Mark the leaf node with the suffix index
        currentNode->suffixIndex = i;
    }

    // Function to get index for both lowercase and uppercase letters
    int getCharIndex(char c) {
        if (c >= 'a' && c <= 'z') {
            return c - 'a';  // Index for lowercase letters
        }
        if (c >= 'A' && c <= 'Z') {
            return c - 'A' + 26;  // Index for uppercase letters (26-51)
        }
        return -1;  // Invalid character (not part of the expected input)
    }

    // Function to print the suffix tree
    void printSuffixTree() {
        printSuffixTree(root, text);
    }

    // Helper function for printing
    void printSuffixTree(SuffixTreeNode *node, string &txt) {
        if (node == NULL) {
            return;
        }

        // If the node is a leaf node, print the suffix starting from the index
        if (node->suffixIndex != -1) {
            cout << "Suffix starting at index " << node->suffixIndex << ": " << txt.substr(node->suffixIndex) << endl;
        }

        // Recurse for each child
        for (int i = 0; i < 52; i++) {
            if (node->children[i] != NULL) {
                printSuffixTree(node->children[i], txt);
            }
        }
    }
};

int main() {
    string text;
    cout << "Enter the text: ";
    cin >> text;

    // Create the Suffix Tree
    SuffixTree suffixTree(text);

    // Print the Suffix Tree (all suffixes)
    cout << "Suffix Tree (all suffixes):" << endl;
    suffixTree.printSuffixTree();

    return 0;
}

