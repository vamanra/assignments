#include <iostream>
using namespace std;

// Structure to represent a sparse matrix element
struct SparseMatrix {
    int row;
    int col;
    int value;
};

// Function to display the sparse matrix
void displaySparseMatrix(SparseMatrix sm[], int nonZeroElements) {
    cout << "Sparse Matrix Representation: (row, col, value)" << endl;
    for (int i = 0; i < nonZeroElements; i++) {
        cout << "(" << sm[i].row << ", " << sm[i].col << ", " << sm[i].value << ")" << endl;
    }
}

int main() {
    // Define a 2D matrix with mostly zero elements
    int rows = 4, cols = 5;
    int matrix[4][5] = {
        {0, 0, 3, 0, 0},
        {0, 0, 5, 7, 0},
        {0, 0, 0, 0, 0},
        {0, 2, 6, 0, 9}
    };

    // Count non-zero elements
    int nonZeroElements = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] != 0) {
                nonZeroElements++;
            }
        }
    }

    // Create an array of structures to hold non-zero elements
    SparseMatrix sm[nonZeroElements];
    int index = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] != 0) {
                sm[index].row = i;
                sm[index].col = j;
                sm[index].value = matrix[i][j];
                index++;
            }
        }
    }

    // Display the sparse matrix
    displaySparseMatrix(sm, nonZeroElements);

    return 0;
}
