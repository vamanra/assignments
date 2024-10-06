
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

// A Tree node
struct Node {
    char ch;
    int freq;
    Node *left, *right;

    Node(char character, int frequency) {
        ch = character;
        freq = frequency;
        left = right = nullptr;
    }
};

// Comparison object to order the heap
struct compare {
    bool operator()(Node* left, Node* right) {
        return left->freq > right->freq;
    }
};

// Function to generate Huffman codes
void generateCodes(Node* root, string code, unordered_map<char, string>& huffmanCode) {
    if (!root) return;

    // Leaf node
    if (!root->left && !root->right) {
        huffmanCode[root->ch] = code;
    }

    generateCodes(root->left, code + "0", huffmanCode);
    generateCodes(root->right, code + "1", huffmanCode);
}

// Function to print Huffman codes in preorder traversal
void preorderTraversal(Node* root, string code) {
    if (!root) return;

    // Leaf node
    if (!root->left && !root->right) {
        cout << code << " ";
    }

    preorderTraversal(root->left, code + "0");
    preorderTraversal(root->right, code + "1");
}

// Builds the Huffman tree and prints codes
void buildHuffmanTree(string S, vector<int> freq) {
    priority_queue<Node*, vector<Node*>, compare> pq;

    // Create a leaf node for each character and add it to the priority queue.
    for (size_t i = 0; i < S.length(); ++i) {
        pq.push(new Node(S[i], freq[i]));
    }

    // Iterate until only one node is left in the queue (the root of the tree).
    while (pq.size() != 1) {
        Node *left = pq.top(); pq.pop();
        Node *right = pq.top(); pq.pop();

        // Create a new internal node with a frequency equal to the sum of the two nodes' frequencies.
        int sum = left->freq + right->freq;
        Node *node = new Node('$', sum);

        node->left = left;
        node->right = right;

        pq.push(node);
    }

    // Root node of the Huffman Tree
    Node* root = pq.top();

    // Preorder traversal of the tree to print Huffman codes
    preorderTraversal(root, "");
}

int main() {
    string S = "abcdef";
    vector<int> freq = {5, 9, 12, 13, 16, 45};

    buildHuffmanTree(S, freq);

    return 0;
}
