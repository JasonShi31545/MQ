// C++ code for the above approach:
#include <bits/stdc++.h>
using namespace std;

int levenshteinTwoMatrixRows(const string& str1,
							const string& str2)
{
	int m = str1.length();
	int n = str2.length();

	vector<int> prevRow(n + 1, 0);
	vector<int> currRow(n + 1, 0);

	for (int j = 0; j <= n; j++) {
		prevRow[j] = j;
	}

	for (int i = 1; i <= m; i++) {
		currRow[0] = i;

		for (int j = 1; j <= n; j++) {
			if (str1[i - 1] == str2[j - 1]) {
				currRow[j] = prevRow[j - 1];
			}
			else {
				currRow[j] = 1
							+ min(

								// Insert
								currRow[j - 1],
								min(

									// Remove
									prevRow[j],

									// Replace
									prevRow[j - 1]));
			}
		}

		prevRow = currRow;
	}

	return currRow[n];
}

// // Drivers code
// int main()
// {
// 	string str1 = "kitten";
// 	string str2 = "sitting";

// 	// Function Call
// 	int distance = levenshteinTwoMatrixRows(str1, str2);
// 	cout << "Levenshtein Distance: " << distance;
// 	return 0;
// }
