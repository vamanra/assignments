
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Function to find the longest common substring
string longestCommonSubstring(const string &s1, const string &s2) {
    int m = s1.size();
    int n = s2.size();

    // Create a 2D table to store the lengths of common substrings
    vector<vector<int>> table(m + 1, vector<int>(n + 1, 0));
    int maxLength = 0;
    int endIndex = 0;

    // Fill in the table using dynamic programming
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (s1[i - 1] == s2[j - 1]) {
                table[i][j] = table[i - 1][j - 1] + 1;
                if (table[i][j] > maxLength) {
                    maxLength = table[i][j];
                    endIndex = i;
                }
            } else {
                table[i][j] = 0;
            }
        }
    }

    // Output the table
    cout << "DP Table:" << endl;
    for (int i = 0; i <= m; ++i) {
        for (int j = 0; j <= n; ++j) {
            cout << table[i][j] << " ";
        }
        cout << endl;
    }

    // Extract the longest common substring
    return s1.substr(endIndex - maxLength, maxLength);
}

int main() {
    string str1, str2;
    cout << "Enter first string: ";
    cin >> str1;
    cout << "Enter second string: ";
    cin >> str2;

    string lcs = longestCommonSubstring(str1, str2);
    cout << "The longest common substring is: " << lcs << endl;
    cout << "Length of the longest common substring: " << lcs.length() << endl;

    return 0;
}
