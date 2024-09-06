
#include <iostream>
using namespace std;

// Node structure for the linked list implementation of sparse matrix
struct Node {
    int row, col, value;
    Node* next;
};

// Function to create a new node
Node* createNode(int row, int col, int value) {
    Node* newNode = new Node();
    newNode->row = row;
    newNode->col = col;
    newNode->value = value;
    newNode->next = nullptr;
    return newNode;
}

// Function to insert a node in the linked list
void insertNode(Node*& head, int row, int col, int value) {
    if (value == 0) return; // Skip zero elements

    Node* newNode = createNode(row, col, value);
    if (!head) {
        head = newNode;
        return;
    }

    Node* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// Function to display the sparse matrix in linked list form
void displaySparseMatrix(Node* head) {
    if (!head) {
        cout << "Sparse matrix is empty or has only zero elements." << endl;
        return;
    }

    cout << "Row	Col	Value" << endl;
    while (head != nullptr) {
        cout << head->row << "	" << head->col << "	" << head->value << endl;
        head = head->next;
    }
}

int main() {
    // Example matrix as described in the document
    int rows = 4, cols = 5;
    int matrix[4][5] = {
        {0, 0, 3, 0, 0},
        {0, 0, 5, 7, 0},
        {0, 0, 0, 0, 0},
        {0, 2, 6, 0, 9}
    };

    Node* sparseMatrix = nullptr;

    // Insert non-zero elements into the linked list
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] != 0) {
                insertNode(sparseMatrix, i, j, matrix[i][j]);
            }
        }
    }

    // Display the sparse matrix
    displaySparseMatrix(sparseMatrix);

    return 0;
}
